#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/actions.h"
#include "enow.h"
#include "constants.h"
#include <freertos/queue.h>

#define SWITCH_LEVEL 0 // реле: 1 - высокого уровня (или мосфет), 0 - низкого

extern uint32_t dw_time[PUMP_AMOUNT];
extern uint32_t cw_time[PUMP_AMOUNT];
extern uint32_t pump_timers[PUMP_AMOUNT];
extern boolean pump_state[PUMP_AMOUNT];
extern boolean pump_finished[PUMP_AMOUNT]; // зона уже полита
extern uint32_t zone_pause;
extern uint32_t programm_time;
extern uint32_t start_time;
extern uint32_t zoneTimer;
extern uint32_t k_dw_time;
extern int8_t thisH, thisM, thisS;
extern boolean now_pumping;
extern boolean dryState;
extern bool show_log;
extern int minutes;
int current_zone = 255;
uint32_t ping_timer;
extern QueueHandle_t esp_now_queue;
extern const char *Message;
void update_log();

void MessageToLog(String Message)
{
    const char *text = Message.c_str();
    xQueueSendFromISR(esp_now_queue, &text, NULL); // Send to queue from ISR
    Serial.println(Message);
    delay(10);
    update_log();
}

void zone_off(int i)
{
    send_command(i, false);
    MessageToLog("выключить зону " + String(i + 1));
}

void zone_on(int i)
{
    send_command(i, true);
    MessageToLog("включить  зону " + String(i + 1));
}

void pump_on()
{
    send_command(PUMP_RELAY, true);
    MessageToLog("включить  насос ");
    lv_obj_remove_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

void pump_off()
{
    send_command(PUMP_RELAY, false);
    MessageToLog("выключить насос ");
    lv_obj_add_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

void dry_water_on()
{
    send_command(WATER_RELAY, false);
    MessageToLog("выключить чистую воду");
    lv_obj_add_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    dryState = true; // флаг грязной воды поднять
}

void clear_water_on()
{
    send_command(WATER_RELAY, true);
    MessageToLog("включить чистую воду");
    lv_obj_add_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    dryState = false;
}

void pump_setup()
{
    // --------------------- КОНФИГУРИРУЕМ ПИНЫ ---------------------
    for (byte i = 0; i < PUMP_AMOUNT; i++)
    { // пробегаем по всем помпам

        pump_finished[i] = true;
        pump_state[i] = !SWITCH_LEVEL;
    }
    pump_state[WATER_RELAY] = !SWITCH_LEVEL; // выкл
    pump_state[PUMP_RELAY] = !SWITCH_LEVEL;  // выкл
}

void periodTick()
{
    for (byte i = 0; i < PUMP_AMOUNT; i++)
    { // пробегаем по всем помпам
        if (millis() - zoneTimer < zone_pause * 1000 * minutes)
            break;                             // если пауза не закончилась - выход из цикла
        if ((dw_time[i] > 0 || cw_time[i] > 0) // если грязная или чистая вода не ноль
                                               // если время полива зоны не ноль
            && !pump_finished[i]               // если зона еще не поливалась
            && !now_pumping)                   // если никакая зона не включена
        {
            current_zone = i;             //
            pump_state[i] = SWITCH_LEVEL; // зона поливается в данный момент
            pump_timers[i] = millis();    // сброс счетчика полива зоны
            now_pumping = true;           // идет полив
            if (dw_time[i] > 0)           // если будет полив грязой
            {                             //
                if (!dryState)
                    dry_water_on(); // если включена чистая вода
            }
            else
            {
                if (dryState)
                    clear_water_on(); // если включена грязная вода
            }
            if (zone_pause > 0) // если есть пауза между зонами -
                pump_on();
            zone_on(i);
        }
        // ------------------переключение воды с грязной на чистую
        uint32_t dw_t = dw_time[i] * 1000 * minutes / 100 * k_dw_time;
        if (dw_time[i] > 0 && millis() - pump_timers[i] >= dw_t // если время полива грязной вышло
            && pump_state[i] == SWITCH_LEVEL                    // если зона поливается в данный момент
            && cw_time[i] > 0                                   // если время чистой воды больше нуля
            && (dryState))                                      // если включена грязная
            clear_water_on();
    }
}

void flowTick()
{ // выключение зоны
    for (byte i = 0; i < PUMP_AMOUNT; i++)
    {
        uint32_t dw_t = dw_time[i] * 1000 * minutes / 100 * k_dw_time;         // пробегаем по всем помпам
        if ((dw_time[i] > 0 || cw_time[i] > 0)                                 // если время полива больше нуля
            && millis() - pump_timers[i] >= dw_t + cw_time[i] * 1000 * minutes // если время полива вышло
            && pump_state[i] == SWITCH_LEVEL)                                  // если зона поливается в данный момент
        {                                                                      //
            pump_state[i] = !SWITCH_LEVEL;                                     // зона не поливается в данный момент
            if (zone_pause > 0)                                                // если есть пауза между зонами -
                pump_off();                                                    // выключить насос
            zone_off(i);                                                       // выключить зону
            now_pumping = false;                                               // полив остановлен
            zoneTimer = millis();                                              // обнуляем таймер паузы между зонами
            pump_finished[i] = true;                                           // зона помечается политой

            // -----------------------------------------проверка на конец заданий--------------------------------------------
            for (byte n = 0; n < PUMP_AMOUNT; n++)
            {                                                                // пробегаем по всем помпам
                if (!pump_finished[n] && (dw_time[n] > 0 || cw_time[n] > 0)) // если нашли не политую - выходим
                    break;                                                   //
                if (n == PUMP_AMOUNT - 1)                                    // если нет не политых
                {

                    action_stop(NULL);
                    // lv_obj_remove_flag(objects.message_box, LV_OBJ_FLAG_HIDDEN);
                    // lv_msgbox_add_close_button(objects.message_box);
                }
            }
            // ---------------------------------------------------------------------------------------------------------------
        }
    }
}

void update_bars()
{
    if (lv_obj_has_flag(objects.stop, LV_OBJ_FLAG_HIDDEN))
        return;
    uint32_t prog_pass = millis() - start_time;
    if (current_zone != 255)
    {
        uint32_t dw_t = dw_time[current_zone] * 1000 * minutes / 100 * k_dw_time;
        uint32_t time = dw_t + (cw_time[current_zone] + zone_pause) * 1000 * minutes;
        if (programm_time - prog_pass <= dw_t + cw_time[current_zone] * 1000 * minutes)
        {
            time = time - zone_pause * 1000;
        }
        uint32_t time_pass = millis() - pump_timers[current_zone];
        lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, current_zone);
        lv_bar_set_value(bar, map(time_pass, 0, time, 0, 100), LV_ANIM_ON);
        int8_t H = floor((long)prog_pass / 3600 / 1000); // секунды в часы
        int8_t M = floor((prog_pass / 1000 - (long)H * 3600) / 60);
        int8_t S = prog_pass / 1000 - (long)H * 3600 - M * 60;
        lv_label_set_text_fmt(objects.bar_label, "%d:%02d:%02d / %d:%02d", H, M, S, thisH, thisM);
    }
    lv_bar_set_value(objects.prog_bar, prog_pass, LV_ANIM_OFF);
}

// void send_ping()
// {
//     if (current_zone == 255 && lv_obj_has_flag(objects.relay_zone_led, LV_OBJ_FLAG_HIDDEN))
//     {
//         if (millis() - ping_timer < 1000)
//             return;
//         send_command(0, false);
//         ping_timer = millis();
//     }
// }

void update_log()
{
    // char Message;
    if (xQueueReceive(esp_now_queue, &Message, 0) == pdTRUE)
        if (show_log)
        {
            lv_textarea_add_text(objects.log, Message);
        }
}

void pump_loop()
{
    periodTick();
    flowTick();
    update_bars();
    // send_ping();
    update_log();
}

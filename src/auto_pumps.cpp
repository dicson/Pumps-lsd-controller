#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/actions.h"
#include "enow.h"
#include "constants.h"
#include <freertos/queue.h>

#define SWITCH_LEVEL 0 // реле: 1 - высокого уровня (или мосфет), 0 - низкого

extern uint32_t dw_time[PUMP_AMOUNT], cw_time[PUMP_AMOUNT], pump_timers[PUMP_AMOUNT];
extern uint32_t zone_pause, programm_time, start_time, zoneTimer, k_dw_time;
extern boolean pump_state[PUMP_AMOUNT], pump_finished[PUMP_AMOUNT], now_pumping, dryState;
extern int8_t thisH, thisM, thisS;
extern bool show_log;
extern int minutes;
int current_zone = 255;
boolean pump_water_state;
void update_log();
void update_bars();
void send_message_to_pult(void *pvParameters);
extern void lora_send_status(const struct_message_pult &toPult);

void MessageToLog(String Message)
{
    Serial.println(Message);
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
    pump_water_state = true;
    send_command(PUMP_RELAY, true);
    MessageToLog("включить  насос ");
    lv_obj_remove_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

void pump_off()
{
    pump_water_state = false;
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

    xTaskCreatePinnedToCore(send_message_to_pult /*Task function*/, "SendMessagesToPult" /* Name*/,
                            2048 /*Stack size*/, NULL /*SParameters*/, 1 /*SPriority*/, NULL /*STask handle*/, 0);
}

void periodTick()
{
    for (byte i = 0; i < PUMP_AMOUNT; i++)
    { // пробегаем по всем помпам
        if (millis() - zoneTimer < zone_pause * 1000 * minutes)
            break;                             // если пауза не закончилась - выход из цикла
        if ((dw_time[i] > 0 || cw_time[i] > 0) // если грязная или чистая вода не ноль
            && !pump_finished[i]               // если зона еще не поливалась
            && !now_pumping)                   // если никакая зона не включена
        {
            current_zone = i;                  //
            pump_state[i] = SWITCH_LEVEL;      // зона поливается в данный момент
            pump_timers[i] = millis();         // сброс счетчика полива зоны
            now_pumping = true;                // идет полив
            if ((dw_time[i] > 0) && !dryState) // если будет полив грязой и если включена чистая вода
                dry_water_on();                // включить грязную
            if ((dw_time[i] == 0) && dryState) // если будет полив чистой и если включена грязная вода
                clear_water_on();
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
                    delay(900);
                    update_bars();
                    action_stop(NULL);
                }
            }
            // ---------------------------------------------------------------------------------------------------------------
        }
    }
}

void send_message_to_pult(void *pvParameters)
{
    struct_message_pult message;

    while (true)
    {
        // Ждем данные из очереди (блокировка до появления данных)
        if (xQueueReceive(esp_now_queue_to_pult, &message, portMAX_DELAY) == pdPASS)
        {
            // Передаем полученную структуру в функцию
            if (esp_now)
                send_to_pult(message);
            else
                lora_send_status(message);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void send_status_to_pult(struct_message_pult msg = {SYNC_WORD, false, pump_water_state, !dryState, 0, 0, 0, 0, 0})
{
    static uint32_t ping_timer;
    if (!use_pult)
        return;
    if (millis() - ping_timer < 1000)
        return;

    xQueueSend(esp_now_queue_to_pult, &msg, 0);
    ping_timer = millis();
}

void update_bars()
{
    if (lv_obj_has_flag(objects.stop, LV_OBJ_FLAG_HIDDEN))
    {
        send_status_to_pult();
        return;
    }
    uint32_t prog_pass = millis() - start_time;
    uint32_t dw_t = dw_time[current_zone] * 1000 * minutes / 100 * k_dw_time;
    uint32_t time = dw_t + (cw_time[current_zone] + zone_pause) * 1000 * minutes;
    if (programm_time < prog_pass)
        prog_pass = programm_time;
    if (programm_time - prog_pass <= dw_t + cw_time[current_zone] * 1000 * minutes)
        time = time - zone_pause * 1000;
    uint32_t time_pass = millis() - pump_timers[current_zone];
    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, current_zone);
    lv_bar_set_value(bar, map(time_pass, 0, time, 0, 100), LV_ANIM_ON);
    unsigned long allSeconds = prog_pass / 1000;
    int8_t H = (allSeconds / 3600) % 24;
    int8_t M = (allSeconds / 60) % 60;
    int8_t S = allSeconds % 60; // Секунды
    lv_label_set_text_fmt(objects.bar_label, "%d:%02d:%02d / %d:%02d:%02d", H, M, S, thisH, thisM, thisS);
    lv_bar_set_value(objects.prog_bar, prog_pass, LV_ANIM_OFF);
    struct_message_pult message1 = {SYNC_WORD, true, pump_water_state, !dryState, current_zone, time_pass, time, prog_pass, programm_time};
    send_status_to_pult(message1);
}

bool system_error_state = false;

void update_log()
{
    EnowMessage msg;
    if (xQueueReceive(esp_now_queue, &msg, 0) == pdTRUE)
    {
        if (msg == EnowMessage::SEND_FAIL)
        {
            if (!system_error_state)
            {
                system_error_state = true;
                ledcWrite(2, 70);
                lv_obj_remove_flag(objects.message_box, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
                // pump_off(); // Ensure pumps are off for safety
            }
        }
    }

    EnowMessage pultMsg;
    if (xQueueReceive(esp_now_queue_from_pult, &pultMsg, 0) == pdTRUE)
    {
        if (pultMsg == EnowMessage::START)
            action_start(NULL);
        if (pultMsg == EnowMessage::STOP)
            action_stop(NULL);
    }
}

void pump_loop()
{
    if (system_error_state)
    {
        // In error state, we only allow UI updates or critical checks, no pump logic
        return;
    }
    periodTick();
    flowTick();
    update_bars();
    update_log();
}

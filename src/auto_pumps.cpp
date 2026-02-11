#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/actions.h"
#include "enow.h"

#define PUPM_AMOUNT 16 // количество помп, подключенных через реле/мосфет
#define SWITCH_LEVEL 0 // реле: 1 - высокого уровня (или мосфет), 0 - низкого
#define WATER_PUMP 4   // это реле, ведущее на насос
#define PUMP_PIN1 5    // это реле, ведущее на чистую воду помпу

extern uint32_t dw_time[PUPM_AMOUNT];
extern uint32_t cw_time[PUPM_AMOUNT];
extern uint32_t pump_timers[PUPM_AMOUNT];
extern boolean pump_state[PUPM_AMOUNT];
extern boolean pump_finished[PUPM_AMOUNT]; // зона уже полита

extern uint32_t zone_pause;
extern uint32_t programm_time;
extern uint32_t start_time;
extern uint32_t zoneTimer;
extern uint32_t k_dw_time;

extern int8_t thisH, thisM, thisS;
extern boolean now_pumping;
extern boolean dryState;
extern int minutes;
int current_zone = 255;

void zone_off(int i)
{
    send_command(i, false);
    Serial.print("выключить зону ");
    Serial.print(i + 1);
    Serial.print("\r\n");
}

void zone_on(int i)
{
    send_command(i, true);
    Serial.print("включить зону ");
    Serial.print(i + 1);
    Serial.print("\r\n");
}

void pump_on()
{
    // send_command(0, true); //
    Serial.println("включить насос");
    lv_obj_remove_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

void pump_off()
{
    send_command(0, false);
    Serial.println("выключить насос");
    lv_obj_add_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

void dry_water_on()
{
    lv_obj_add_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    Serial.println("включить грязную воду"); //
    dryState = true;                         // флаг грязной воды поднять
}

void clear_water_on()
{
    lv_obj_add_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    Serial.println("включить чистую воду");
    dryState = false;
}

void pump_setup()
{
    // --------------------- КОНФИГУРИРУЕМ ПИНЫ ---------------------
    for (byte i = 0; i < PUPM_AMOUNT; i++)
    { // пробегаем по всем помпам

        pump_finished[i] = true;
        if (SWITCH_LEVEL) // вырубить все помпы
            pump_state[i] = 0;
        else
            pump_state[i] = 1;
    }
}

void periodTick()
{
    for (byte i = 0; i < PUPM_AMOUNT; i++)
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
    for (byte i = 0; i < PUPM_AMOUNT; i++)
    {
        uint32_t dw_t = dw_time[i] * 1000 * minutes / 100 * k_dw_time;         // пробегаем по всем помпам
        if ((dw_time[i] > 0 || cw_time[i] > 0)                                 // если время полива больше нуля
            && millis() - pump_timers[i] >= dw_t + cw_time[i] * 1000 * minutes // если время полива вышло
            && pump_state[i] == SWITCH_LEVEL)                                  // если зона поливается в данный момент
        {                                                                      //
            pump_state[i] = !SWITCH_LEVEL;                                     // зона не поливается в данный момент
            if (zone_pause > 0)                                                // если есть пауза между зонами -
                pump_off();
            zone_off(i);
            now_pumping = false;     // полив остановлен
            zoneTimer = millis();    // обнуляем таймер паузы между зонами
            pump_finished[i] = true; // зона помечается политой

            // -----------------------------------------проверка на конец заданий--------------------------------------------
            for (byte n = 0; n < PUPM_AMOUNT; n++)
            {                                                                // пробегаем по всем помпам
                if (!pump_finished[n] && (dw_time[n] > 0 || cw_time[n] > 0)) // если нашли не политую - выходим
                    break;                                                   //
                if (n == PUPM_AMOUNT - 1)
                {
                    action_stop(NULL);
                    //                   Serial.print("stop ");
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

void pump_loop()
{
    periodTick();
    flowTick();
    update_bars();
}

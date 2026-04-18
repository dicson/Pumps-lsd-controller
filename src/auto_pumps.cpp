#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/actions.h"
#include "enow.h"
#include "constants.h"
#include <freertos/queue.h>

extern void save_k_dw_time();

#define SWITCH_LEVEL 0 // реле: 1 - высокого уровня (или мосфет), 0 - низкого

extern uint32_t dw_time[PUMP_AMOUNT], cw_time[PUMP_AMOUNT], pump_timers[PUMP_AMOUNT];
extern uint32_t zone_pause, programm_time, start_time, zoneTimer, k_dw_time;
extern boolean pump_state[PUMP_AMOUNT], pump_finished[PUMP_AMOUNT], now_pumping, dryState;
extern int8_t thisH, thisM, thisS;
extern bool show_log;
extern int minutes;
int current_zone = 255;
boolean pump_water_state;
void handle_messages();
void update_bars();
void send_message_to_pult(void *pvParameters);
extern void lora_send_status(const struct_message_pult &toPult);

/**
 * @brief Выводит текстовое сообщение в последовательный порт.
 * @param Message Текст сообщения для логирования.
 */
void MessageToLog(String Message)
{
    Serial.println(Message);
}

/**
 * @brief Выключает указанную зону полива.
 * @param i Индекс зоны (от 0 до PUMP_AMOUNT-1).
 */
void zone_off(int i)
{
    send_command(i, false);
    MessageToLog("выключить зону " + String(i + 1));
}

/**
 * @brief Включает указанную зону полива.
 * @param i Индекс зоны (от 0 до PUMP_AMOUNT-1).
 */
void zone_on(int i)
{
    send_command(i, true);
    MessageToLog("включить  зону " + String(i + 1));
}

/**
 * @brief Включает основной водяной насос и отображает иконку в UI.
 */
void pump_on()
{
    pump_water_state = true;
    send_command(PUMP_RELAY, true);
    MessageToLog("включить  насос ");
    lv_obj_remove_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Выключает основной водяной насос и скрывает иконку в UI.
 */
void pump_off()
{
    pump_water_state = false;
    send_command(PUMP_RELAY, false);
    MessageToLog("выключить насос ");
    lv_obj_add_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Переключает подачу на "грязную" воду (отключает реле чистой воды).
 */
void dry_water_on()
{
    send_command(WATER_RELAY, false);
    MessageToLog("выключить чистую воду");
    lv_obj_add_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    dryState = true; // флаг грязной воды поднять
}

/**
 * @brief Переключает подачу на "чистую" воду (включает реле чистой воды).
 */
void clear_water_on()
{
    send_command(WATER_RELAY, true);
    MessageToLog("включить чистую воду");
    lv_obj_add_flag(objects.pipe, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.osmos, LV_OBJ_FLAG_HIDDEN);
    dryState = false;
}

/**
 * @brief Начальная настройка системы полива. Конфигурирует состояния зон и создает задачу связи с пультом.
 */
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

    xTaskCreatePinnedToCore(send_message_to_pult /*Функция задачи*/, "SendMessagesToPult" /* Имя*/,
                            2048 /*Размер стека*/, NULL /*Параметры*/, 1 /*Приоритет*/, NULL /*Дескриптор задачи*/, 0);
}

/**
 * @brief Проверяет таймеры и условия для начала полива зон по очереди.
 */
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
        uint32_t dw_t = (dw_time[i] * 1000 * minutes / 100) * k_dw_time;
        if (dw_time[i] > 0 && millis() - pump_timers[i] >= dw_t // если время полива грязной вышло
            && pump_state[i] == SWITCH_LEVEL                    // если зона поливается в данный момент
            && cw_time[i] > 0                                   // если время чистой воды больше нуля
            && (dryState))                                      // если включена грязная
            clear_water_on();
    }
}

/**
 * @brief Контролирует завершение полива зоны и переход к следующей.
 */
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

/**
 * @brief Задача FreeRTOS для отправки сообщений на пульт через ESP-NOW или LoRa.
 * @param pvParameters Параметры задачи (не используются).
 */
void send_message_to_pult(void *pvParameters)
{
    struct_message_pult message;

    // Ждём стабилизации WiFi
    vTaskDelay(pdMS_TO_TICKS(3000));

    while (true)
    {
        // Ждем данные из очереди (блокировка до появления данных)
        if (xQueueReceive(esp_now_queue_to_pult, &message, portMAX_DELAY) == pdPASS)
        {
            if (esp_now)
                espnow_send_status(message);
            else
                lora_send_status(message);
        }
    }
}

/**
 * @brief Формирует и отправляет текущий статус системы в очередь для передачи на пульт.
 * @param msg Структура сообщения (по умолчанию пустая с синхронизацией).
 */
void send_status_to_pult(struct_message_pult msg = {
                             SYNC_WORD, 0, 0, 0, 0, 0, 0, 0, 0, 0})
{
    static uint32_t ping_timer;

    if (!use_pult)
        return;
    if (millis() - ping_timer < 1000)
        return;

    // Значения по умолчанию, если функция вызвана без аргументов
    if (msg.sync == SYNC_WORD && msg.time == 0)
    {
        msg.state = false;
        msg.pump_state = pump_water_state;
        msg.osmos_state = !dryState;
        msg.k_dw_time = k_dw_time;
    }

    xQueueSend(esp_now_queue_to_pult, &msg, 0);
    ping_timer = millis();
}

/**
 * @brief Обновляет графические индикаторы (бары) зон и прогресса в UI, а также отправляет статус на пульт.
 */
void update_bars()
{
    if (current_zone >= PUMP_AMOUNT || lv_obj_has_flag(objects.stop, LV_OBJ_FLAG_HIDDEN))
    {
        send_status_to_pult();
        return;
    }
    static int last_zone = -1;
    uint32_t prog_pass = millis() - start_time;
    uint32_t dw_t = dw_time[current_zone] * 1000 * minutes / 100 * k_dw_time;
    uint32_t time = dw_t + (cw_time[current_zone] + zone_pause) * 1000 * minutes;
    if (programm_time < prog_pass)
        prog_pass = programm_time;
    if (programm_time - prog_pass <= dw_t + cw_time[current_zone] * 1000 * minutes)
        time = time - zone_pause * 1000;
    uint32_t time_pass = millis() - pump_timers[current_zone];
    if (time_pass > time)
        time_pass = time;

    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, current_zone);
    // Обновляем настройки градиента только при смене зоны
    if (current_zone != last_zone)
    {
        last_zone = current_zone;
        static lv_grad_dsc_t bars_grads[PUMP_AMOUNT];
        lv_grad_dsc_t *grad = &bars_grads[current_zone];

        grad->dir = LV_GRAD_DIR_HOR;
        grad->stops_count = 2;

        uint32_t sp = 255;
        if (time > 0)
        {
            sp = (uint32_t)((uint64_t)dw_t * 255 / time);
            if (sp > 255)
                sp = 255;
        }

        // Цвет грязной воды (до границы sp)
        grad->stops[0].color = lv_color_hex(ZONE_BAR_COLOR_DW);
        grad->stops[0].frac = 0;
        grad->stops[0].opa = 255;
        grad->stops[1].color = lv_color_hex(ZONE_BAR_COLOR_DW);
        grad->stops[1].frac = (uint8_t)sp;
        grad->stops[1].opa = 255;
        // Цвет чистой воды (после границы sp)
        if (grad->stops[1].frac < 255)
        {
            grad->stops_count = 4;
            grad->stops[2].color = lv_color_hex(0x2196F3);
            grad->stops[2].frac = (uint8_t)sp;
            grad->stops[2].opa = 255;
            grad->stops[3].color = lv_color_hex(0x2196F3);
            grad->stops[3].frac = 255;
            grad->stops[3].opa = 255;
        }

        lv_obj_set_style_bg_grad(bar, grad, LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(bar, 255, LV_PART_INDICATOR);
    }
    lv_bar_set_value(bar, map(time_pass, 0, time, 0, 100), LV_ANIM_OFF);
    lv_bar_set_value(objects.prog_bar, prog_pass, LV_ANIM_OFF);
    static uint32_t last_update = 0;
    if (millis() - last_update < 1000)
        return;
    last_update = millis();
    unsigned long allSeconds = prog_pass / 1000;
    int8_t H = (allSeconds / 3600) % 24;
    int8_t M = (allSeconds / 60) % 60;
    int8_t S = allSeconds % 60; // Секунды
    lv_label_set_text_fmt(objects.bar_label, "%d:%02d:%02d / %d:%02d:%02d", H, M, S, thisH, thisM, thisS);
    struct_message_pult message1 = {SYNC_WORD, 1, (uint8_t)pump_water_state, (uint8_t)!dryState, (int32_t)current_zone,
                                    time_pass, time, prog_pass, programm_time, k_dw_time};
    send_status_to_pult(message1);
}

bool system_error_state = false;

/**
 * @brief Обрабатывает входящие сообщения из очередей ESP-NOW (ошибки передачи и команды с пульта).
 */
void handle_messages()
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
            }
        }
    }

    QueuePultMessage qpMsg;
    if (xQueueReceive(esp_now_queue_from_pult, &qpMsg, 0) == pdTRUE)
    {
        if (esp_now && use_pult)
        {
            if (qpMsg.type == EnowMessage::START)
                action_start(NULL);
            if (qpMsg.type == EnowMessage::STOP)
                action_stop(NULL);
            if (qpMsg.type == EnowMessage::SET_K)
            {
                k_dw_time = qpMsg.value;
                save_k_dw_time();
            }
        }
    }
}

/**
 * @brief Основной цикл управления помпами. Выполняет логику полива, обновление UI и обработку сообщений.
 */
void pump_loop()
{
    if (system_error_state)
    {
        // В состоянии ошибки разрешены только обновления интерфейса или критические проверки, логика насоса отключена
        return;
    }
    periodTick();
    flowTick();
    update_bars();
    handle_messages();
}

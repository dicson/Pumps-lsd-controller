#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "ui/actions.h"
#include "enow.h"
#include "constants.h"
#include <freertos/queue.h>
#include "lora.h"
#include "auto_pumps.h"

int current_zone = 255;
bool pump_water_state;
bool system_error_state = false;
float pump_sensor = 0;
uint32_t pump_sensor_timer = millis();

void send_message_to_pult(void *pvParameters);

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
    Serial.printf("выключить зону %d\n", i + 1);
}

/**
 * @brief Включает указанную зону полива.
 * @param i Индекс зоны (от 0 до PUMP_AMOUNT-1).
 */
void zone_on(int i)
{
    send_command(i, true);
    Serial.printf("включить зону %d\n", i + 1);
}

/**
 * @brief Включает основной водяной насос и отображает иконку в UI.
 */
void pump_on()
{
    pump_water_state = true;
    send_root_command(PUMP_RELAY, true);
    MessageToLog("включить  насос ");
    lv_obj_remove_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Выключает основной водяной насос и скрывает иконку в UI.
 */
void pump_off()
{
    pump_water_state = false;
    send_root_command(PUMP_RELAY, false);
    MessageToLog("выключить насос ");
    lv_obj_add_flag(objects.pump, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Переключает подачу на "грязную" воду (отключает реле чистой воды).
 */
void dry_water_on()
{
    send_root_command(WATER_RELAY, false);
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
    send_root_command(WATER_RELAY, true);
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
 * @brief Рассчитывает длительность фазы грязной воды в миллисекундах.
 */
uint32_t getDirtyWaterDurationMs(int zone)
{
    if (zone < 0 || zone >= PUMP_AMOUNT)
        return 0;
    // Приведение к uint64_t исключает переполнение при больших значениях dw_time и minutes,
    // а единый порядок операций с calculate_program_time() гарантирует совпадение суммы.
    return (uint64_t)dw_time[zone] * MS_PER_SECOND * minutes * k_dw_time / 100;
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
        uint32_t dw_t = getDirtyWaterDurationMs(i);
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
        uint32_t dw_t = getDirtyWaterDurationMs(i);                            // пробегаем по всем помпам
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
                    lv_bar_set_value(objects.prog_bar, programm_time, LV_ANIM_OFF);
                    lv_label_set_text_fmt(objects.bar_label, "%d:%02d:%02d / %d:%02d:%02d",
                                          thisH, thisM, thisS, thisH, thisM, thisS);
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
 * @param msg Структура сообщения.
 */
void send_status_to_pult(struct_message_pult msg)
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
 * @brief Настраивает двухцветный градиент для баров (грязная/чистая вода).
 */
void update_zone_bar_style(lv_obj_t *bar, int zone, uint32_t dw_duration, uint32_t total_duration)
{
    static lv_grad_dsc_t bars_grads[PUMP_AMOUNT];
    lv_grad_dsc_t *grad = &bars_grads[zone];

    grad->dir = LV_GRAD_DIR_HOR;
    grad->stops_count = 2;

    uint8_t split_pos = 255;
    if (total_duration > 0)
    {
        uint64_t calc = (uint64_t)dw_duration * 255 / total_duration;
        split_pos = (calc > 255) ? 255 : (uint8_t)calc;
    }

    // Цвет грязной воды
    grad->stops[0].color = lv_color_hex(ZONE_BAR_COLOR_DW);
    grad->stops[0].frac = 0;
    grad->stops[0].opa = LV_OPA_COVER;
    grad->stops[1].color = lv_color_hex(ZONE_BAR_COLOR_DW);
    grad->stops[1].frac = split_pos;
    grad->stops[1].opa = LV_OPA_COVER;

    // Добавляем цвет чистой воды, если фаза есть
    if (split_pos < 255)
    {
        grad->stops_count = 4;
        grad->stops[2].color = lv_color_hex(0x2196F3); // Blue
        grad->stops[2].frac = split_pos;
        grad->stops[2].opa = LV_OPA_COVER;
        grad->stops[3].color = lv_color_hex(0x2196F3);
        grad->stops[3].frac = 255;
        grad->stops[3].opa = LV_OPA_COVER;
    }

    lv_obj_set_style_bg_grad(bar, grad, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);
}

/**
 * @brief Форматирует и обновляет текстовую метку общего прогресса.
 */
void update_progress_time_label(uint32_t prog_pass_ms)
{
    static uint32_t last_label_update = 0;
    if (millis() - last_label_update < 1000)
        return;
    last_label_update = millis();

    uint32_t allSeconds = prog_pass_ms / 1000;
    int8_t H = (allSeconds / 3600) % 24;
    int8_t M = (allSeconds / 60) % 60;
    int8_t S = allSeconds % 60;

    lv_label_set_text_fmt(objects.bar_label, "%d:%02d:%02d / %d:%02d:%02d",
                          H, M, S, thisH, thisM, thisS);
}

/**
 * @brief Обновляет графические индикаторы (бары) зон и прогресса в UI, а также отправляет статус на пульт.
 */
void update_bars(bool resetFlag)
{
    static int last_zone_styled = -1;
    static uint32_t last_ui_update = 0;

    // Если передан флаг сброса, обнуляем переменную
    if (resetFlag)
    {
        last_zone_styled = -1;
        return;
    }

    // Ограничение частоты обновления UI (20 Гц)
    if (millis() - last_ui_update < 50)
    {
        return;
    }
    last_ui_update = millis();

    if (current_zone >= PUMP_AMOUNT || lv_obj_has_flag(objects.stop, LV_OBJ_FLAG_HIDDEN))
    {
        send_status_to_pult();
        return;
    }

    // 1. Расчет таймингов
    uint32_t prog_pass = millis() - start_time;
    if (prog_pass > programm_time)
        prog_pass = programm_time;

    uint32_t dw_t = getDirtyWaterDurationMs(current_zone);
    uint32_t time = dw_t + cw_time[current_zone] * 1000 * minutes;
    uint32_t time_pass = millis() - pump_timers[current_zone] + 50;
    if (time_pass > time)
        time_pass = time;

    // 2. Обновление UI Баров
    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, current_zone);

    if (current_zone != last_zone_styled)
    {
        update_zone_bar_style(bar, current_zone, dw_t, time);
        last_zone_styled = current_zone;
    }

    lv_bar_set_value(bar, map(time_pass, 0, time, 0, 100), LV_ANIM_OFF);
    lv_bar_set_value(objects.prog_bar, prog_pass, LV_ANIM_OFF);

    // 3. Текстовая информация и синхронизация
    update_progress_time_label(prog_pass);

    struct_message_pult message1 = {SYNC_WORD, 1, (uint8_t)pump_water_state, (uint8_t)!dryState, (int32_t)current_zone,
                                    time_pass, time, prog_pass, programm_time, k_dw_time};
    send_status_to_pult(message1);
}

/**
 * @brief Обрабатывает входящие сообщения из очередей ESP-NOW (ошибки передачи и команды с пульта).
 */
void handle_messages()
{
    EnowStatusMessage msg;
    if (xQueueReceive(esp_now_queue, &msg, 0) == pdPASS)
    {
        if (msg.status == EnowMessage::SEND_FAIL)
        {
            // Уходим в ошибку только если не удалось достучаться до реле (игнорируем ошибки связи с пультом)
            bool is_relay1 = (memcmp(msg.mac, relay1Address, 6) == 0);
            bool is_relay2 = (memcmp(msg.mac, relay2Address, 6) == 0);

            if ((is_relay1 || is_relay2) && minutes == REAL_TIME_MINUTES)
            {
                if (!system_error_state)
                {
                    system_error_state = true;
                    analogWrite(2, 70); // Снижаем яркость подсветки

                    // Пытаемся найти метку внутри контейнера message_box и обновить текст
                    lv_obj_t *label = lv_obj_get_child(objects.message_box, 0);
                    if (label)
                    {
                        lv_label_set_text_fmt(label, "Связь потеряна: %s\n\nПерезапустите систему.",
                                              is_relay1 ? "реле 1" : "реле 2");
                    }

                    lv_obj_remove_flag(objects.message_box, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_add_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
                    MessageToLog("Ошибка связи с " + String(is_relay1 ? "relay1" : "relay2"));
                }
            }
        }
    }

    QueuePultMessage qpMsg;
    if (xQueueReceive(esp_now_queue_from_pult, &qpMsg, 0) == pdPASS)
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
    // сообщение от датчика тока насоса
    QueueSensorMessage qpMsg1;
    if (xQueueReceive(esp_now_queue_from_sensor, &qpMsg1, 0) == pdPASS)
    {
        if (qpMsg1.type == EnowMessage::PUMP_I && use_pump_sensor)
        {
            pump_sensor = qpMsg1.value;
            pump_sensor_timer = millis();
            lv_label_set_text_fmt(objects.pump_i, "%.1f A", pump_sensor);
            if (pump_sensor > 14 && minutes == REAL_TIME_MINUTES)
            {
                static bool inited = false;
                static int pass = 0;
                static uint32_t last_event_time = 0;
                uint32_t current_time = millis();
                // 1. Проверяем таймаут. Если времени прошло много — сбрасываем счетчик событий
                if (current_time - last_event_time > 2500)
                {
                    pass = 0;
                }
                last_event_time = current_time; // В любом случае обновляем время последнего события
                // 2. Считаем шаги
                if (pass < 2)
                {
                    pass++;
                    return; // Блокируем выполнение основного кода, пока не накопим 3 быстрых события
                }
                pass = 0;

                if (!inited)
                {
                    lv_obj_remove_flag(objects.sensor_msgbox, LV_OBJ_FLAG_HIDDEN);
                    inited = true;
                }
            }
        }
    }
}

/**
 * @brief проверка работы насоса и изменение цвта прогрессбара зоны
 */
void check_pump(bool resetFlag)
{
    static uint32_t last_check = 0;
    static int changed_zone = -1;

    // Если передан флаг сброса, обнуляем переменную
    if (resetFlag)
    {
        changed_zone = -1;
        return;
    }
    if (millis() - last_check < 4000)
        return;
    if (!use_pump_sensor || !pump_water_state || changed_zone == current_zone)
        return;
    uint32_t time_pass = millis() - pump_timers[current_zone];
    if (time_pass < 6000)
        return;

    last_check = millis();
    if (pump_sensor < MINIMAL_CURRENT)
    {
        lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, current_zone);
        lv_obj_set_style_bg_grad(bar, NULL, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(bar, lv_color_hex(0xff0000), LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR); // Ensure opacity is visible
        changed_zone = current_zone;
        Serial.println("Насос не качает");
    }
}

/**
 * @brief проверка работы датчика насоса
 */
void check_pump_sensor()
{
    if ((millis() - pump_sensor_timer) < 5000 || !use_pump_sensor)
        return;
    static bool inited = false;
    if (!inited)
    {
        lv_obj_remove_flag(objects.sensor_msgbox_1, LV_OBJ_FLAG_HIDDEN);
        inited = true;
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
    check_pump();
    check_pump_sensor();
}

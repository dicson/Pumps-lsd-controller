#ifndef ENOW_H
#define ENOW_H
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_now.h>

constexpr uint8_t relay1Address[] = {0xa4, 0xf0, 0x0f, 0x8d, 0x02, 0xec}; // 5v relay
constexpr uint8_t pultAddress[] = {0x58, 0x8c, 0x81, 0x52, 0xec, 0x84};      // pult

/**
 * @brief Функция обратного вызова, которая выполняется после отправки данных.
 * Используется для отслеживания успешности доставки сообщений.
 * 
 * @param tx_info Информация о передаче.
 * @param status Статус доставки (ESP_NOW_SEND_SUCCESS или ESP_NOW_SEND_FAIL).
 */
void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status);

/**
 * @brief Функция обратного вызова, которая выполняется при получении данных по протоколу ESP-NOW.
 * Обрабатывает команды, поступающие от пульта управления (START, STOP, SET_K).
 * 
 * @param info Информация о отправителе (включая MAC-адрес).
 * @param incomingData Указатель на входящий буфер данных.
 * @param len Длина полученных данных.
 */
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len);

/**
 * @brief Инициализация протокола ESP-NOW.
 * Настраивает WiFi в режиме станции, регистрирует коллбэки и добавляет пиры (узлы) для связи.
 */
void esp_now_setup();

/**
 * @brief Отправляет команду управления конкретным реле (зоной).
 * 
 * @param relay Номер реле или индекс зоны.
 * @param state Состояние (true - включить, false - выключить).
 */
void send_command(int relay, bool state);

/**
 * @brief Отправляет команду управления реле насоса(осмоса) или обновления.
 * 
 * @param relay Номер реле.
 * @param state Состояние (true - включить, false - выключить).
 */
void send_root_command(int relay, bool state);

extern bool use_pult, lora, esp_now;

// Queue handles
extern QueueHandle_t esp_now_queue;
extern QueueHandle_t esp_now_queue_from_pult;
extern QueueHandle_t esp_now_queue_to_pult;

enum class EnowMessage
{
    NONE,
    OK,
    SEND_FAIL,
    START,
    STOP,
    SET_K
};

typedef struct __attribute__((packed))
{
    int32_t relay;   // номер реле (255 = установка K)
    uint8_t state;   // вкл/выкл
    uint32_t k_value; // коэффициент K (используется при relay == 255)
} struct_message;

typedef struct __attribute__((packed))
{
    EnowMessage type;
    uint32_t value; // payload (e.g. K value)
} QueuePultMessage;

typedef struct __attribute__((packed))
{
    uint16_t sync;          // Маркер начала (0xABCD)
    uint8_t state;          // вкл/выкл
    uint8_t pump_state;     // вкл/выкл
    uint8_t osmos_state;    // вкл/выкл
    int32_t current_zone;   // номер реле
    uint32_t time_pass;     // прошло полива зоны
    uint32_t time;          // время полива зоны
    uint32_t prog_pass;     // прошло полива зоны
    uint32_t programm_time; // время полива зоны
    uint32_t k_dw_time;     // коэффициент полива зоны
} struct_message_pult;

const uint16_t SYNC_WORD = 0xABCD;

/**
 * @brief Отправляет полный статус системы на пульт управления.
 * 
 * @param toPult Структура с данными о состоянии системы (прогресс, активная зона и т.д.).
 */
void espnow_send_status(const struct_message_pult &toPult);

extern uint32_t k_dw_time;

#endif // ENOW_H
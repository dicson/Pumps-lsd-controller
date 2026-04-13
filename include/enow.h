#ifndef ENOW_H
#define ENOW_H
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

constexpr uint8_t broadcastAddress[] = {0xa4, 0xf0, 0x0f, 0x8d, 0x02, 0xec}; // 5v relay
constexpr uint8_t pultAddress[] = {0x58, 0x8c, 0x81, 0x52, 0xec, 0x84};      // pult

void esp_now_setup();
void send_command(int relay, bool state);

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
    STOP
};

typedef struct struct_message
{
    int relay;  // номер реле
    bool state; // вкл/выкл
} struct_message;

typedef struct struct_message_pult
{
    uint16_t sync;          // Маркер начала (0xABCD)
    bool state;             // вкл/выкл
    bool pump_state;        // вкл/выкл
    bool osmos_state;       // вкл/выкл
    int current_zone;       // номер реле
    uint32_t time_pass;     // прошло полива зоны
    uint32_t time;          // время полива зоны
    uint32_t prog_pass;     // прошло полива зоны
    uint32_t programm_time; // время полива зоны
    uint32_t k_dw_time;     // коэффициент полива зоны
} struct_message_pult;

const uint16_t SYNC_WORD = 0xABCD;

void espnow_send_status(const struct_message_pult &toPult);
#endif // ENOW_H
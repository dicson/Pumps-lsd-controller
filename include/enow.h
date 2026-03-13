#ifndef ENOW_H
#define ENOW_H
#include <stdint.h>
//  uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
//  uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xF1, 0x20, 0xA8};   12v relay
constexpr uint8_t broadcastAddress[] = {0xa4, 0xf0, 0x0f, 0x8d, 0x02, 0xec}; // a4:f0:0f:8d:02:ec 5v relay
constexpr uint8_t pultAddress[] = {0x58, 0x8c, 0x81, 0x52, 0xec, 0x84};      // 58:8c:81:52:ec:84 pult
// void requestData(void *pvParameters);
void esp_now_setup();
void send_command(int relay, bool state);
void send_to_pult(bool state, bool pump_state, bool osmos_state, int current_zone,
                  uint32_t time_pass, uint32_t time, uint32_t prog_pass, uint32_t programm_time);

extern const char *Message, *Message_from_pult;

// // Define a queue handle
extern QueueHandle_t esp_now_queue;
extern QueueHandle_t esp_now_queue_from_pult;

typedef struct struct_message
{
    int relay;  // номер реле
    bool state; // вкл/выкл
} struct_message;

typedef struct struct_message_pult
{
    bool state;             // вкл/выкл
    bool pump_state;        // вкл/выкл
    bool osmos_state;       // вкл/выкл
    int current_zone;       // номер реле
    uint32_t time_pass;     // прошло полива зоны
    uint32_t time;          // время полива зоны
    uint32_t prog_pass;     // прошло полива зоны
    uint32_t programm_time; // время полива зоны
} struct_message_pult;

#endif // ENOW_H
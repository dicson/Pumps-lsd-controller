#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "enow.h"

// Дескрипторы очередей
QueueHandle_t esp_now_queue;
QueueHandle_t esp_now_queue_from_pult;
QueueHandle_t esp_now_queue_to_pult;

// Флаг: ESP-NOW полностью инициализирован
static bool esp_now_ready = false;

extern void save_k_dw_time();

// Функция обратного вызова, которая выполняется при получении данных
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len)
{
    if (info == NULL || info->src_addr == NULL || incomingData == NULL)
        return;

    if (memcmp(info->src_addr, pultAddress, 6) != 0 || !use_pult)
        return;

    struct_message fromPult;
    if (len != sizeof(fromPult))
        return;

    memcpy(&fromPult, incomingData, sizeof(fromPult));

    QueuePultMessage qMsg;
    qMsg.type = EnowMessage::NONE;
    qMsg.value = 0;

    // Команда установки K (relay == 255)
    if (fromPult.relay == 255)
    {
        qMsg.type = EnowMessage::SET_K;
        qMsg.value = fromPult.k_value;
        xQueueSendFromISR(esp_now_queue_from_pult, &qMsg, NULL);
        return;
    }

    if (fromPult.relay == 0 && fromPult.state == false)
        qMsg.type = EnowMessage::STOP;
    else if (fromPult.relay == 1 && fromPult.state == true)
        qMsg.type = EnowMessage::START;

    if (qMsg.type != EnowMessage::NONE)
        xQueueSendFromISR(esp_now_queue_from_pult, &qMsg, NULL);
}

// Обратный вызов при отправке данных
void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    EnowMessage msg = (status == ESP_NOW_SEND_SUCCESS) ? EnowMessage::OK : EnowMessage::SEND_FAIL;
    xQueueSendFromISR(esp_now_queue, &msg, NULL);
}

void esp_now_setup()
{
    // Настройка устройства как Wi-Fi станции
    WiFi.mode(WIFI_STA);
    WiFi.enableAP(false);

    if (esp_now_init() != ESP_OK)
    {
        return;
    }

    // Устанавливаем канал 1
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

    // Регистрация обратных вызовов
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);

    // Регистрация узла реле (Peer)
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Регистрация узла пульта (Peer)
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, pultAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Также добавляем broadcast peer для надёжности приёма
    memset(&peerInfo, 0, sizeof(peerInfo));
    uint8_t broadcast_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    memcpy(peerInfo.peer_addr, broadcast_mac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Создание очередей
    esp_now_queue = xQueueCreate(10, sizeof(EnowMessage));
    esp_now_queue_from_pult = xQueueCreate(10, sizeof(QueuePultMessage));
    esp_now_queue_to_pult = xQueueCreate(10, sizeof(struct_message_pult));

    esp_now_ready = true;
}

void send_command(int relay, bool state)
{
    struct_message myData;
    myData.relay = relay;
    myData.state = state;

    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}

void espnow_send_status(const struct_message_pult &toPult)
{
    if (!esp_now_ready)
    {
        return;
    }

    // Копируем в локальный буфер
    uint8_t send_buffer[sizeof(toPult)];
    memcpy(send_buffer, &toPult, sizeof(toPult));

    esp_now_send(pultAddress, send_buffer, sizeof(send_buffer));
}

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "enow.h"

// Дескрипторы очередей для обмена данными между задачами и прерываниями
QueueHandle_t esp_now_queue;
QueueHandle_t esp_now_queue_from_pult;
QueueHandle_t esp_now_queue_to_pult;

// Флаг: ESP-NOW полностью инициализирован и готов к работе
static bool esp_now_ready = false;

extern void save_k_dw_time();

/**
 * @brief Функция обратного вызова, которая выполняется при получении данных по протоколу ESP-NOW.
 * Обрабатывает команды, поступающие от пульта управления (START, STOP, SET_K).
 * 
 * @param info Информация о отправителе (включая MAC-адрес).
 * @param incomingData Указатель на входящий буфер данных.
 * @param len Длина полученных данных.
 */
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len)
{
    if (info == NULL || info->src_addr == NULL || incomingData == NULL)
        return;

    // Проверяем, что данные пришли именно от пульта и пульт разрешен в настройках
    if (memcmp(info->src_addr, pultAddress, 6) != 0 || !use_pult)
        return;

    struct_message fromPult;
    if (len != sizeof(fromPult))
        return;

    memcpy(&fromPult, incomingData, sizeof(fromPult));

    QueuePultMessage qMsg;
    qMsg.type = EnowMessage::NONE;
    qMsg.value = 0;

    // Команда установки коэффициента K (используется спец. номер реле 255)
    if (fromPult.relay == 255)
    {
        qMsg.type = EnowMessage::SET_K;
        qMsg.value = fromPult.k_value;
        xQueueSendFromISR(esp_now_queue_from_pult, &qMsg, NULL);
        return;
    }

    // Обработка команд СТАРТ и СТОП
    if (fromPult.relay == 0 && fromPult.state == false)
        qMsg.type = EnowMessage::STOP;
    else if (fromPult.relay == 1 && fromPult.state == true)
        qMsg.type = EnowMessage::START;

    if (qMsg.type != EnowMessage::NONE)
        xQueueSendFromISR(esp_now_queue_from_pult, &qMsg, NULL);
}

/**
 * @brief Функция обратного вызова, которая выполняется после отправки данных.
 * Используется для отслеживания успешности доставки сообщений.
 * 
 * @param tx_info Информация о передаче.
 * @param status Статус доставки (ESP_NOW_SEND_SUCCESS или ESP_NOW_SEND_FAIL).
 */
void OnDataSent(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    EnowMessage msg = (status == ESP_NOW_SEND_SUCCESS) ? EnowMessage::OK : EnowMessage::SEND_FAIL;
    xQueueSendFromISR(esp_now_queue, &msg, NULL);
}

/**
 * @brief Инициализация протокола ESP-NOW.
 * Настраивает WiFi в режиме станции, регистрирует коллбэки и добавляет пиры (узлы) для связи.
 */
void esp_now_setup()
{
    // Настройка устройства как Wi-Fi станции (обязательно для ESP-NOW)
    WiFi.mode(WIFI_STA);
    WiFi.enableAP(false);

    if (esp_now_init() != ESP_OK)
    {
        return;
    }

    // Устанавливаем канал 1 для совпадения с другими устройствами
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

    // Регистрация функций обратного вызова
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);

    // Регистрация узла реле (используется broadcast адрес для управления исполнительными модулями)
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Регистрация конкретного адреса пульта
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, pultAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Регистрация общего широковещательного адреса для входящих пакетов
    memset(&peerInfo, 0, sizeof(peerInfo));
    uint8_t broadcast_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    memcpy(peerInfo.peer_addr, broadcast_mac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    // Создание очередей для межзадачного взаимодействия
    esp_now_queue = xQueueCreate(10, sizeof(EnowMessage));
    esp_now_queue_from_pult = xQueueCreate(10, sizeof(QueuePultMessage));
    esp_now_queue_to_pult = xQueueCreate(10, sizeof(struct_message_pult));

    esp_now_ready = true;
}

/**
 * @brief Отправляет команду управления конкретным реле (зоной).
 * 
 * @param relay Номер реле или индекс зоны.
 * @param state Состояние (true - включить, false - выключить).
 */
void send_command(int relay, bool state)
{
    struct_message myData;
    myData.relay = relay;
    myData.state = state;

    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}

/**
 * @brief Отправляет полный статус системы на пульт управления.
 * 
 * @param toPult Структура с данными о состоянии системы (прогресс, активная зона и т.д.).
 */
void espnow_send_status(const struct_message_pult &toPult)
{
    if (!esp_now_ready)
    {
        return;
    }

    // Копируем данные в локальный буфер для безопасной отправки
    uint8_t send_buffer[sizeof(toPult)];
    memcpy(send_buffer, &toPult, sizeof(toPult));

    esp_now_send(pultAddress, send_buffer, sizeof(send_buffer));
}

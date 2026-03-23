#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "enow.h"

// Queue handles
QueueHandle_t esp_now_queue;
QueueHandle_t esp_now_queue_from_pult;
QueueHandle_t esp_now_queue_to_pult;

// Callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len)
{
    const uint8_t *mac_addr = info->src_addr;
    if ((memcmp(mac_addr, pultAddress, 6) != 0) || !use_pult)
        return;

    struct_message fromPult;
    if (len != sizeof(fromPult)) return; // Safety check
    memcpy(&fromPult, incomingData, sizeof(fromPult));

    EnowMessage msg = EnowMessage::NONE;

    if (fromPult.relay == 0 && fromPult.state == false)
    {
        msg = EnowMessage::STOP;
    }
    else if (fromPult.relay == 1 && fromPult.state == true)
    {
        msg = EnowMessage::START;
    }

    if (msg != EnowMessage::NONE) {
        xQueueSendFromISR(esp_now_queue_from_pult, &msg, NULL);
    }
}

// Callback when data is sent
void OnDataSent(const esp_now_recv_info_t *info, esp_now_send_status_t status)
{
    const uint8_t *mac_addr = info->src_addr;
    // Check if the message was sent to the broadcast address (relays)
    if (memcmp(mac_addr, broadcastAddress, 6) == 0)
    {
        EnowMessage msg = (status == ESP_NOW_SEND_SUCCESS) ? EnowMessage::OK : EnowMessage::SEND_FAIL;
        xQueueSendFromISR(esp_now_queue, &msg, NULL);
    }
}

void esp_now_setup()
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    WiFi.enableAP(false);
    // esp_wifi_set_channel(0, WIFI_SECOND_CHAN_NONE); // Ensure channel matches peers if not using CSP

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register callbacks
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

    // Register Relay Peer
    esp_now_peer_info_t peerInfo = {}; // Zero-initialize
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add relay peer");
    }

    // Register Pult Peer
    memset(&peerInfo, 0, sizeof(peerInfo)); // Reset for safety
    memcpy(peerInfo.peer_addr, pultAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add pult peer");
    }

    // Create queues
    esp_now_queue = xQueueCreate(10, sizeof(EnowMessage));
    esp_now_queue_from_pult = xQueueCreate(10, sizeof(EnowMessage));
    esp_now_queue_to_pult = xQueueCreate(10, sizeof(struct_message_pult));
}

void send_command(int relay, bool state)
{
    struct_message myData;
    myData.relay = relay;
    myData.state = state;

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

    if (result != ESP_OK)
    {
        Serial.println("Error sending command to relays");
    }
}

void send_to_pult(const struct_message_pult &toPult)
{
    esp_err_t result = esp_now_send(pultAddress, (uint8_t *)&toPult, sizeof(toPult));

    if (result != ESP_OK)
    {
        Serial.println("Error sending data to pult");
    }
}

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"
// uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
// uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xF1, 0x20, 0xA8};   12v relay
uint8_t broadcastAddress[] = {0xa4, 0xf0, 0x0f, 0x8d, 0x02, 0xec}; // a4:f0:0f:8d:02:ec 5v relay

typedef struct struct_message
{
  int a;
  bool b;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const esp_now_recv_info_t *info, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == ESP_NOW_SEND_SUCCESS)
  {
    lv_obj_remove_flag(objects.relay_zone_led, LV_OBJ_FLAG_HIDDEN);
  }
}

void esp_now_setup()
{
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.enableAP(false);
  // WiFi.disconnect(false, true);
  esp_wifi_set_channel(0, WIFI_SECOND_CHAN_NONE);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void send_command(int relay, bool state)
{
  // Set values to send
  myData.a = relay;
  myData.b = state;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }
}

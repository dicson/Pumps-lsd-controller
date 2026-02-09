#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
 
typedef struct struct_message
{
  int a;
  bool b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const esp_now_recv_info_t *info, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void esp_now_setup()
{
  // REPLACE WITH YOUR RECEIVER MAC Address
  // uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  //uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
  uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xF1, 0x20, 0xA8};

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect (false, true);

  // Init ESP-NOW

  esp_wifi_set_channel(0,  WIFI_SECOND_CHAN_NONE);
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


// void requestData(void *params)
// {
//   (void)params;

//   uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
//   // Set values to send
//   myData.a = 0;
//   myData.b = true;

//   esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

//   if (result == ESP_OK)
//   {
//     Serial.println("Sent with success");
//   }
//   else
//   {
//     Serial.println("Error sending the data");
//   }
//   vTaskDelete(NULL);
// }


void send_command(int relay, bool state)
{
  //xTaskCreate(requestData, "Request Data", 2048 * 8, NULL, 1, NULL);
  // REPLACE WITH YOUR RECEIVER MAC Address
  // uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  // 68:25:DD:FD:24:97
  //uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
  uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xF1, 0x20, 0xA8};
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

// xTaskCreate(requestData,"Request Data",2048 * 8, NULL, 1, NULL);


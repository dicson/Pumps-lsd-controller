#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"
#include "enow.h"

// // Define a queue handle
QueueHandle_t esp_now_queue;
QueueHandle_t esp_now_queue_from_pult;
QueueHandle_t esp_now_queue_to_pult;
const char *Message;
const char *Message_from_pult;

struct_message myData;
struct_message fromPult;
struct_message_pult toPult;
esp_now_peer_info_t peerInfo;

// callback function that will be executed when data is received
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len)
{
  const uint8_t *mac_addr = info->src_addr;
  if ((memcmp(mac_addr, pultAddress, 6) != 0) || !use_pult)
    return;
  memcpy(&fromPult, incomingData, sizeof(fromPult));
  if (fromPult.relay == 0 && fromPult.state == false)
  {
    const char *Message_from_pult = "stop";
    xQueueSendFromISR(esp_now_queue_from_pult, &Message_from_pult, NULL); // Send to queue from ISR}
  }
  if (fromPult.relay == 1 && fromPult.state == true)
  {
    const char *Message_from_pult = "start";
    xQueueSendFromISR(esp_now_queue_from_pult, &Message_from_pult, NULL); // Send to queue from ISR}
  }
}

// callback when data is sent
void OnDataSent(const esp_now_recv_info_t *info, esp_now_send_status_t status)
{
  const char *Message = status == ESP_NOW_SEND_SUCCESS ? "\r\n" : " - не выполнено\r\n";
  const uint8_t *mac_addr = info->src_addr;
  if (!memcmp(mac_addr, broadcastAddress, sizeof(mac_addr)))
    xQueueSendFromISR(esp_now_queue, &Message, NULL); // Send to queue from ISR
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
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
  }
  // Register peer
  memcpy(peerInfo.peer_addr, pultAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
  }
  esp_now_queue = xQueueCreate(10, sizeof(Message));                     // Queue for 10 messages
  esp_now_queue_from_pult = xQueueCreate(10, sizeof(Message_from_pult)); // Queue for 10 messages
  esp_now_queue_to_pult = xQueueCreate(10, sizeof(struct_message_pult)); // Queue for 10 messages
}

void send_command(int relay, bool state)
{
  // Set values to send
  myData.relay = relay;
  myData.state = state;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK)
  {
    // Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }
}

void send_to_pult(struct_message_pult &toPult)
{
  esp_err_t result = esp_now_send(pultAddress, (uint8_t *)&toPult, sizeof(toPult));

  if (result == ESP_OK)
  {
  }
  else
  {
    Serial.println("Error sending the data");
  }
}

// // Define a queue handle
// QueueHandle_t esp_now_queue;

// // Structure to receive data, must match the sender structure
// typedef struct {
//     int id;
//     float temp;
//     float hum;
//     int readingId;
// } struct_message;

// static lv_obj_t * table1;
// static lv_obj_t * table2;

// // Callback function executed when data is received
// void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
//   // Copy incoming data to myData structure
//   struct_message myData;
//   memcpy(&myData, incomingData, sizeof(myData));
//   xQueueSendFromISR(esp_now_queue, &myData, NULL); // Send to queue from ISR

//   // Get sender's MAC address from recv_info
//   const uint8_t *mac_addr = recv_info->src_addr;

//   // Convert sender's MAC address to a string for display
//   char macStr[18];
//   snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
//            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

//   // Print received data to Serial Monitor
//   Serial.println("Received data:");
//   Serial.print("  Sender MAC: ");
//   Serial.println(macStr);
//   Serial.print("  Board ID: ");
//   Serial.println(myData.id);
//   Serial.print("  Temperature: ");
//   Serial.print(myData.temp);
//   Serial.println(" °C");
//   Serial.print("  Humidity: ");
//   Serial.print(myData.hum);
//   Serial.println(" %");
//   Serial.print("  Reading ID: ");
//   Serial.println(myData.readingId);
//   Serial.println("-------------------");
// }

// void update_table_values(struct_message *myData) {

//   String temp_value = String(myData->temp) + degree_symbol;
//   String humi_value = String(myData->hum) + "%";

//   if(myData->id == 1) {
//     lv_table_set_cell_value(table1, 0, 1, temp_value.c_str());
//     lv_table_set_cell_value(table1, 1, 1, humi_value.c_str());
//     lv_table_set_cell_value(table1, 2, 1, String(myData->readingId).c_str());
//   }
//   else if(myData->id == 2) {
//     lv_table_set_cell_value(table2, 0, 1, temp_value.c_str());
//     lv_table_set_cell_value(table2, 1, 1, humi_value.c_str());
//     lv_table_set_cell_value(table2, 2, 1, String(myData->readingId).c_str());
//   }
// }

// void setup() {

//   // Register callback function to handle received data
//   esp_now_register_recv_cb(OnDataRecv);

//   esp_now_queue = xQueueCreate(10, sizeof(struct_message)); // Queue for 10 messages
//   if (esp_now_queue == NULL) {
//     Serial.println("Error creating queue");
//     return;
//   }
// }

// void loop() {
//   lv_task_handler();  // let the GUI do its work
//   lv_tick_inc(5);     // tell LVGL how much time has passed
//   delay(5);           // let this time pass

//   struct_message myData;
//   if (xQueueReceive(esp_now_queue, &myData, 0) == pdTRUE) {
//     // Process and display the data
//     update_table_values(&myData);
//   }
// }
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <lvgl.h>
#include "ui/screens.h"

//  uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0xFD, 0x24, 0x94};
//  uint8_t broadcastAddress[] = {0xD4, 0xE9, 0xF4, 0xF1, 0x20, 0xA8};   12v relay
uint8_t broadcastAddress[] = {0xa4, 0xf0, 0x0f, 0x8d, 0x02, 0xec}; // a4:f0:0f:8d:02:ec 5v relay
uint8_t pultAddress[] = {0x58, 0x8c, 0x81, 0x52, 0xec, 0x84};      // 58:8c:81:52:ec:84 pult
//
// // Define a queue handle
QueueHandle_t esp_now_queue;
const char *Message;

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

struct_message myData;
struct_message_pult toPult;
esp_now_peer_info_t peerInfo;
extern QueueHandle_t esp_now_queue;

// callback when data is sent
void OnDataSent(const esp_now_recv_info_t *info, esp_now_send_status_t status)
{
  const char *Message = status == ESP_NOW_SEND_SUCCESS ? "\r\n" : " - не выполнено\r\n";
  const uint8_t *mac_addr = info->src_addr;
  if (!memcmp(mac_addr, broadcastAddress, sizeof(mac_addr)))
    // char macStr[18];
    // snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
    //          mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    // Serial.println(macStr);
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
  esp_now_queue = xQueueCreate(50, sizeof(Message)); // Queue for 10 messages
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

void send_to_pult(bool state, bool pump_state, bool osmos_state, int current_zone,
                  uint32_t time_pass, uint32_t time, uint32_t prog_pass, uint32_t programm_time)
{
  // Set values to send
  toPult.state = state;
  toPult.pump_state = pump_state;
  toPult.osmos_state = osmos_state;
  toPult.current_zone = current_zone;
  toPult.time_pass = time_pass;
  toPult.time = time;
  toPult.prog_pass = prog_pass;
  toPult.programm_time = programm_time;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(pultAddress, (uint8_t *)&toPult, sizeof(toPult));

  if (result == ESP_OK)
  {
    //  Serial.println("Sent with success(pult)");
    //  Serial.println(state);
    //  Serial.println(pump_state);
    //  Serial.println(osmos_state);
    //  Serial.println(current_zone);
    //  Serial.println(time_pass);
    //  Serial.println(time);
    //  Serial.println(prog_pass);
    //  Serial.println(programm_time);
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
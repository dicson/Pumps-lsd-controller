//void requestData(void *pvParameters);
void esp_now_setup();
void send_command(int relay, bool state);
void send_to_pult(bool state, bool pump_state, bool osmos_state, int current_zone,
                  uint32_t time_pass, uint32_t time, uint32_t prog_pass, uint32_t programm_time);
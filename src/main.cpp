#include "display.h"
#include "ui/ui.h"
#include "settings.h"
#include "auto_pumps.h"
#include "enow.h"
#include "elegantota.h"

void setup()
{
  Serial.begin(115200);
  delay(500); // Short delay to ensure serial is ready
  setup_settings();
  setup_display();
  ui_init();
  fill_widgets();
  pump_setup();
  esp_now_setup();
}

void loop()
{
  loop_display();
  pump_loop();
  ota_loop();
}

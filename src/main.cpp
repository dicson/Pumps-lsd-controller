#include "display.h"
#include "ui/ui.h"
#include "auto_pumps.h"
#include "elegantota.h"
#include "enow.h"
#include "lora.h"

extern void setup_settings();
extern void fill_widgets();

void setup()
{
  Serial.begin(115200);
  delay(500); // Короткая задержка для готовности последовательного порта
  setup_settings();
  setup_display();
  ui_init();
  lv_timer_handler(); // Принудительная отрисовка первого кадра

  // Плавное включение подсветки
  for (int duty = 0; duty <= GFX_BL_VALUE; duty++)
  {
    analogWrite(GFX_BL, duty);
    delay(4);
  }

  fill_widgets();
  esp_now_setup();
  pump_setup();
  lora_setup();
}

void loop()
{
  loop_display();
  pump_loop();
  ota_loop();
  lora_loop();
}

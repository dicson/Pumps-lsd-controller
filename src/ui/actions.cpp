#include <lvgl.h>
#include "actions.h"
#include "ui.h"
#include "screens.h"
#include <Arduino.h>
#include "vars.h"
#include <Preferences.h>
#include "auto_pumps.h"

#define PUPM_AMOUNT 16
#define RW_MODE false
#define RO_MODE true
#define GFX_BL 2
#define SWITCH_LEVEL 0 // реле: 1 - высокого уровня (или мосфет), 0 - низкого
// String myString;
extern Preferences settings;
extern int32_t GFX_BL_VALUE; // brightness
extern int32_t GFX_BL_TIME;
extern boolean h_zone13;
extern boolean h_zone14;
extern boolean h_zone16;
extern uint32_t dw_time[PUPM_AMOUNT];
extern uint32_t cw_time[PUPM_AMOUNT];
extern uint32_t zoneTimer, zone_pause;
extern boolean pump_finished[PUPM_AMOUNT];
extern boolean pump_state[PUPM_AMOUNT];
extern boolean now_pumping;
extern lv_obj_t *bar_list[PUPM_AMOUNT];
extern uint32_t k_dw_time;
int dw_time_;
int cw_time_;
lv_obj_t *obj;
lv_obj_t *obj1;
uint32_t start_time;
uint32_t programm_time;
extern int minutes;
int8_t thisH, thisM, thisS;

void update_zone_list()
{
  for (int i = 0; i < PUPM_AMOUNT; i++)
  {
    lv_obj_t *bar_list[PUPM_AMOUNT] = {
        objects.bar_0,
        objects.bar_1,
        objects.bar_2,
        objects.bar_3,
        objects.bar_4,
        objects.bar_5,
        objects.bar_6,
        objects.bar_7,
        objects.bar_8,
        objects.bar_9,
        objects.bar_10,
        objects.bar_11,
        objects.bar_12,
        objects.bar_13,
        objects.bar_14,
        objects.bar_15,
    };
    if (cw_time[i] != 0 || dw_time[i] != 0)
    {
      lv_obj_remove_flag(bar_list[i], LV_OBJ_FLAG_HIDDEN);
    }
    else
      lv_obj_add_flag(bar_list[i], LV_OBJ_FLAG_HIDDEN);
  }
}

void action_debug(lv_event_t *e)
{
  if (lv_obj_has_state(objects.debug, LV_STATE_CHECKED))
    minutes = 1;
  else
    minutes = 60;
}

void action_bl_changed(lv_event_t *e)
{
  GFX_BL_VALUE = lv_slider_get_value(objects.bl);
  ledcWrite(GFX_BL, GFX_BL_VALUE);
}

void action_bl_released(lv_event_t *e)
{
  GFX_BL_VALUE = lv_slider_get_value(objects.bl);
  settings.begin("Settings", RW_MODE);
  settings.putLong("GFX_BL_VALUE", GFX_BL_VALUE);
  settings.end();
}

void action_dw(lv_event_t *e)
{
  if (lv_obj_has_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN) &&
      lv_obj_has_flag(objects.keyboard_1, LV_OBJ_FLAG_HIDDEN))
  {
    lv_obj_remove_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.input_area, LV_OBJ_FLAG_HIDDEN);
    obj = lv_event_get_current_target_obj(e);
    dw_time_ = (int)lv_event_get_user_data(e);
  }
}

void action_cw(lv_event_t *e)
{
  if (lv_obj_has_flag(objects.keyboard_1, LV_OBJ_FLAG_HIDDEN) &&
      lv_obj_has_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN))
  {
    lv_obj_remove_flag(objects.keyboard_1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.input_area_1, LV_OBJ_FLAG_HIDDEN);
    obj1 = lv_event_get_current_target_obj(e);
    cw_time_ = (int)lv_event_get_user_data(e);
  }
}

void action_input_done(lv_event_t *e)
{
  const char *txt = lv_textarea_get_text(objects.input_area);
  if ((int)txt[0] == 0 || String(txt) == "0" || String(txt) == "00")
  {
    txt = "0";
    lv_obj_t *ob = lv_obj_get_child(lv_obj_get_parent(obj), 2);
    const char *txt1 = lv_label_get_text(ob);
    if (String(txt1) == "0")
      lv_obj_set_style_bg_opa(lv_obj_get_parent(obj), 100, LV_PART_MAIN);
  }
  else
    lv_obj_set_style_bg_opa(lv_obj_get_parent(obj), 255, LV_PART_MAIN);
  lv_obj_add_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.input_area, LV_OBJ_FLAG_HIDDEN);
  dw_time[dw_time_] = atol(txt);
  lv_label_set_text(obj, txt);
  lv_textarea_set_text(objects.input_area, "");
  settings.begin("Settings", RW_MODE);
  settings.putBytes("dw_time", dw_time, PUPM_AMOUNT * 4);
  settings.end();
  update_zone_list();
}

void action_input_done1(lv_event_t *e)
{
  const char *txt = lv_textarea_get_text(objects.input_area_1);
  if ((int)txt[0] == 0 || String(txt) == "0" || String(txt) == "00")
  {
    txt = "0";
    lv_obj_t *ob = lv_obj_get_child(lv_obj_get_parent(obj1), 1);
    const char *txt1 = lv_label_get_text(ob);
    if (String(txt1) == "0")
      lv_obj_set_style_bg_opa(lv_obj_get_parent(obj1), 100, LV_PART_MAIN);
  }
  else
    lv_obj_set_style_bg_opa(lv_obj_get_parent(obj1), 255, LV_PART_MAIN);
  lv_obj_add_flag(objects.keyboard_1, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.input_area_1, LV_OBJ_FLAG_HIDDEN);
  cw_time[cw_time_] = atol(txt);
  lv_label_set_text(obj1, txt);
  lv_textarea_set_text(objects.input_area_1, "");
  settings.begin("Settings", RW_MODE);
  settings.putBytes("cw_time", cw_time, PUPM_AMOUNT * 4);
  settings.end();
  update_zone_list();
  // for (int i = 0; i < sizeof(dw_time) / sizeof(int); i++)
  // {
  //   Serial.print(dw_time[i]);
  //   Serial.print(", ");
  // }
  // Serial.println(sizeof(dw_time));
  // Serial.println("   ");
  // Serial.println("\r\n");
}

void action_idle_time_focused(lv_event_t *e)
{
  lv_keyboard_set_textarea(objects.settings_kb, objects.bl_idle);
  lv_obj_remove_flag(objects.settings_kb, LV_OBJ_FLAG_HIDDEN);
  lv_textarea_set_cursor_pos(objects.bl_idle, LV_TEXTAREA_CURSOR_LAST);
}

void action_pause_released(lv_event_t *e)
{
  lv_keyboard_set_textarea(objects.settings_kb, objects.pause);
  lv_obj_remove_flag(objects.settings_kb, LV_OBJ_FLAG_HIDDEN);
  lv_textarea_set_cursor_pos(objects.pause, LV_TEXTAREA_CURSOR_LAST);
}

void action_pause_ready(lv_event_t *e)
{
  lv_obj_add_flag(objects.settings_kb, LV_OBJ_FLAG_HIDDEN);
  const char *txt = lv_textarea_get_text(objects.pause);
  zone_pause = atol(lv_textarea_get_text(objects.pause));
  if (String(txt) == "")
  {
    zone_pause = 0;
    lv_textarea_set_text(objects.pause, String("0").c_str());
  }
  // lv_obj_clear_state(objects.bl_idle, LV_STATE_FOCUSED);
  settings.begin("Settings", RW_MODE);
  settings.putLong("zone_pause", zone_pause);
  settings.end();
}

void action_idle_time_unfocused(lv_event_t *e)
{
  lv_obj_add_flag(objects.settings_kb, LV_OBJ_FLAG_HIDDEN);
  GFX_BL_TIME = atol(lv_textarea_get_text(objects.bl_idle));
  if (GFX_BL_TIME < 10)
  {
    GFX_BL_TIME = 10;
    lv_textarea_set_text(objects.bl_idle, String("10").c_str());
  }
  // lv_obj_clear_state(objects.bl_idle, LV_STATE_FOCUSED);
  settings.begin("Settings", RW_MODE);
  // Serial.println(settings.freeEntries());
  settings.putLong("GFX_BL_TIME", GFX_BL_TIME);
  settings.end();
}

void action_start(lv_event_t *e)
{
  lv_obj_add_flag(objects.start, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_state(objects.start, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(objects.stop, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.spinner, LV_OBJ_FLAG_HIDDEN);

  zoneTimer = millis() - zone_pause * 1000 * minutes; // убираем паузу перед запуском полива
  pump_on();

  now_pumping = true;
  programm_time = 0;
  for (byte i = 0; i < PUPM_AMOUNT; i++)
  {                           // пробегаем по всем помпам
    pump_finished[i] = false; // сброс переменных политых зон(старт полива)
    if (dw_time[i] > 0 || cw_time[i] > 0)
    {
      programm_time = programm_time + (dw_time[i] + cw_time[i] + zone_pause) * 1000 * minutes;
      // lcd.setCursor(i, 3);                          // заполняем индикатор заданий
      // if (pumping_time[i] > 0)                      // если время полива зоны больше нуля
      //   lcd.print("0");
      // else
      //   lcd.print("*");
    }
  }
  programm_time = programm_time - (zone_pause * 1000 * minutes);
  thisH = floor((long)programm_time / 3600 / 1000); // секунды в часы
  thisM = floor((programm_time / 1000 - (long)thisH * 3600) / 60);
  lv_bar_set_range(objects.prog_bar, 0, programm_time);
  lv_obj_remove_flag(objects.prog_bar, LV_OBJ_FLAG_HIDDEN);
  start_time = millis();
  now_pumping = false;
}

void action_stop(lv_event_t *e)
{
  lv_obj_t *bar_list[PUPM_AMOUNT] = {
      objects.bar_0,
      objects.bar_1,
      objects.bar_2,
      objects.bar_3,
      objects.bar_4,
      objects.bar_5,
      objects.bar_6,
      objects.bar_7,
      objects.bar_8,
      objects.bar_9,
      objects.bar_10,
      objects.bar_11,
      objects.bar_12,
      objects.bar_13,
      objects.bar_14,
      objects.bar_15,
  };
  pump_off();
  dry_water_on();
  for (byte i = 0; i < PUPM_AMOUNT; i++)
  {
    lv_bar_set_value(bar_list[i], 0, LV_ANIM_ON);
    pump_finished[i] = true;
    if (pump_state[i] == SWITCH_LEVEL)
    {
      pump_state[i] = !SWITCH_LEVEL;
      Serial.print("stop ");
      Serial.print(i + 1);
      Serial.print("\n");
    }
  }
  now_pumping = false;
  lv_bar_set_value(objects.prog_bar, 0, LV_ANIM_OFF);
  lv_obj_add_flag(objects.prog_bar, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_state(objects.stop, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.start, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(objects.start, LV_STATE_DISABLED);
  lv_obj_add_flag(objects.spinner, LV_OBJ_FLAG_HIDDEN);
}

void save_k_reset()
{
  lv_label_set_text(objects.k_dw_time, String(k_dw_time).c_str());
  settings.begin("Settings", RW_MODE);
  settings.putLong("k_dw_time", k_dw_time);
  settings.end();
}

void action_spinbox_decrement_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    if (k_dw_time > 50)
    {
      --k_dw_time;
      save_k_reset();
    }
  }
}

void action_spinbox_increment_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    if (k_dw_time < 200)
    {
      ++k_dw_time;
      save_k_reset();
    }
  }
}

void action_k_reset(lv_event_t *e)
{
  k_dw_time = 100;
  save_k_reset();
}

void action_tab_changed(lv_event_t *e)
{

  // for (int i = 0; i < PUPM_AMOUNT; i++)
  // {
  //   lv_obj_t *bar_list[PUPM_AMOUNT] = {
  //       objects.bar_0,
  //       objects.bar_1,
  //       objects.bar_2,
  //       objects.bar_3,
  //       objects.bar_4,
  //       objects.bar_5,
  //       objects.bar_6,
  //       objects.bar_7,
  //       objects.bar_8,
  //       objects.bar_9,
  //       objects.bar_10,
  //       objects.bar_11,
  //       objects.bar_12,
  //       objects.bar_13,
  //       objects.bar_14,
  //       objects.bar_15,
  //   };
  //   if (cw_time[i] != 0 || dw_time[i] != 0)
  //   {
  //     lv_obj_remove_flag(bar_list[i], LV_OBJ_FLAG_HIDDEN);
  //   }
  //   else
  //     lv_obj_add_flag(bar_list[i], LV_OBJ_FLAG_HIDDEN);
  // }
}

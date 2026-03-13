#include <lvgl.h>
#include "ui/actions.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include <Arduino.h>
#include <Preferences.h>
#include "auto_pumps.h"
#include "elegantota.h"
#include "constants.h"
#include "enow.h"

#define RW_MODE false
#define RO_MODE true
#define GFX_BL 2

extern Preferences settings;
extern uint32_t dw_time[PUMP_AMOUNT], cw_time[PUMP_AMOUNT], zoneTimer, zone_pause;
extern int32_t GFX_BL_VALUE, GFX_BL_TIME, k_dw_time;
extern boolean pump_finished[PUMP_AMOUNT], pump_state[PUMP_AMOUNT], now_pumping;
extern lv_obj_t *bar_list[PUMP_AMOUNT];
extern int current_zone, minutes;

uint32_t water_num;
lv_obj_t *obj;
uint32_t start_time;
uint32_t programm_time;
int8_t thisH, thisM, thisS;

void hide_k_buttons()
{
  lv_obj_add_flag(objects.button10, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.button_10, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.button_dec, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.button_inc, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.button_reset, LV_OBJ_FLAG_HIDDEN);
}

void show_k_buttons()
{
  lv_obj_remove_flag(objects.button10, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.button_10, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.button_dec, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.button_inc, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.button_reset, LV_OBJ_FLAG_HIDDEN);
}

void update_zone_list()
{
  for (int i = 0; i < PUMP_AMOUNT; i++)
  {
    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, i);
    lv_obj_t *button = lv_obj_get_child(objects.tab_1, i);
    lv_obj_t *checkbox = lv_obj_get_child(button, 1);

    if (cw_time[i] != 0 || dw_time[i] != 0)
    {
      lv_obj_remove_flag(bar, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_opa(button, 255, LV_PART_MAIN);
      lv_obj_remove_flag(checkbox, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
      lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_opa(button, 100, LV_PART_MAIN);
      lv_obj_add_flag(checkbox, LV_OBJ_FLAG_HIDDEN);
    }
    lv_task_handler();
  }
}

void action_debug(lv_event_t *e)
{
  if (lv_obj_has_state(objects.debug, LV_STATE_CHECKED))
    minutes = 1;
  else
    minutes = 60;
}

void action_use_pult(lv_event_t *e)
{
  use_pult = lv_obj_has_state(objects.pult, LV_STATE_CHECKED);
  settings.begin("Settings", RW_MODE);
  settings.putBool("use_pult", use_pult);
  settings.end();
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
  start_time = millis();
  lv_obj_add_flag(objects.tab_1, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.tab_2, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.tab_settings, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.start, LV_OBJ_FLAG_HIDDEN);
  hide_k_buttons();
  lv_obj_add_state(objects.start, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(objects.stop, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.spinner, LV_OBJ_FLAG_HIDDEN);
  lv_bar_set_value(objects.prog_bar, 0, LV_ANIM_OFF);

  zoneTimer = millis() - zone_pause * 1000 * minutes; // убираем паузу перед запуском полива
  pump_on();
  now_pumping = true;
  programm_time = 0;
  for (byte i = 0; i < PUMP_AMOUNT; i++) // считаем время программы
  {                                      // пробегаем по всем помпам
    pump_finished[i] = false;            // сброс переменных политых зон(старт полива)
    if (dw_time[i] > 0 || cw_time[i] > 0)
    {
      uint32_t dw_t = dw_time[i] * 1000 * minutes / 100 * k_dw_time;
      programm_time = programm_time + dw_t + (cw_time[i] + zone_pause) * 1000 * minutes;
    }
    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, i);
    lv_bar_set_value(bar, 0, LV_ANIM_OFF);
  }
  programm_time = programm_time - (zone_pause * 1000 * minutes);
  thisH = floor((long)programm_time / 3600 / 1000); // секунды в часы
  thisM = floor((programm_time / 1000 - (long)thisH * 3600) / 60);
  thisS = programm_time / 1000 - (long)thisH * 3600 - thisM * 60;
  lv_bar_set_range(objects.prog_bar, 0, programm_time);
  lv_obj_remove_flag(objects.prog_bar, LV_OBJ_FLAG_HIDDEN);
  now_pumping = false;
}

void action_stop(lv_event_t *e)
{
  pump_off();
  update_log();
  dry_water_on();
  if (!pump_finished[current_zone])
    zone_off(current_zone);
  for (byte i = 0; i < PUMP_AMOUNT; i++)
  {
    // lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, i);
    // lv_bar_set_value(bar, 0, LV_ANIM_ON);
    lv_obj_t *zone_button = lv_obj_get_child(objects.tab_1, i);
    if (!lv_obj_has_flag(zone_button, LV_OBJ_FLAG_CHECKABLE))
    {
      lv_obj_t *check_box = lv_obj_get_child(zone_button, 1);
      lv_obj_add_flag(check_box, LV_OBJ_FLAG_CLICKABLE);
      lv_obj_remove_state(check_box, LV_STATE_CHECKED);
    }
    pump_finished[i] = true;
    if (pump_state[i] == SWITCH_LEVEL)
    {
      pump_state[i] = !SWITCH_LEVEL;
    }
  }
  now_pumping = false;
  // lv_bar_set_value(objects.prog_bar, 0, LV_ANIM_OFF);
  // lv_obj_add_flag(objects.prog_bar, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_state(objects.stop, LV_STATE_DISABLED);
  lv_obj_remove_flag(objects.start, LV_OBJ_FLAG_HIDDEN);
  show_k_buttons();
  lv_obj_remove_flag(objects.tab_1, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.tab_2, LV_OBJ_FLAG_HIDDEN);
  lv_obj_remove_flag(objects.tab_settings, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_state(objects.start, LV_STATE_DISABLED);
  lv_obj_add_flag(objects.spinner, LV_OBJ_FLAG_HIDDEN);
  update_zone_list();
}

void save_k_dw_time()
{
  lv_label_set_text(objects.k_dw_time, String(k_dw_time).c_str());
  settings.begin("Settings", RW_MODE);
  settings.putLong("k_dw_time", k_dw_time);
  settings.end();
}

void action_decrement_10(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    k_dw_time = k_dw_time - 10;
    if (k_dw_time < 50)
      k_dw_time = 50;
    save_k_dw_time();
  }
}

void action_spinbox_decrement_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    if (k_dw_time > 50)
    {
      --k_dw_time;
      save_k_dw_time();
    }
  }
}

void action_increment_10(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LONG_PRESSED_REPEAT)
  {
    k_dw_time = k_dw_time + 10;
    if (k_dw_time > 200)
      k_dw_time = 200;
    save_k_dw_time();
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
      save_k_dw_time();
    }
  }
}

void action_k_reset(lv_event_t *e)
{
  k_dw_time = 100;
  save_k_dw_time();
}

void action_tab_changed(lv_event_t *e)
{
}

void action_update_back(lv_event_t *e)
{
  lv_screen_load_anim(objects.main, LV_SCREEN_LOAD_ANIM_OUT_RIGHT, 1000, 0, true);
}

void action_update_relay_back(lv_event_t *e)
{
  lv_screen_load_anim(objects.main, LV_SCREEN_LOAD_ANIM_OUT_RIGHT, 1000, 0, true);
}

void action_update(lv_event_t *e)
{
  create_screen_update_selector();
  loadScreen(SCREEN_ID_UPDATE_SELECTOR);
}

void action_update_display(lv_event_t *e)
{
  create_screen_update_display();
  loadScreen(SCREEN_ID_UPDATE_DISPLAY);
  lv_label_set_text(objects.version, VERSION);
  ota_setup();
}

void action_update_relay(lv_event_t *e)
{
  create_screen_update_relay();
  loadScreen(SCREEN_ID_UPDATE_RELAY);
}

void action_update_relay_1(lv_event_t *e)
{
  send_command(255, false);
}

void action_zone_selected(lv_event_t *e)
{
  lv_obj_t *zone_button = lv_event_get_current_target_obj(e);
  int32_t zone_num = lv_obj_get_index(zone_button);
  lv_obj_remove_flag(lv_event_get_target_obj(e), LV_OBJ_FLAG_CLICKABLE);
  pump_finished[zone_num] = false;
  if (lv_obj_has_flag(objects.stop, LV_OBJ_FLAG_HIDDEN))
  {
    start_time = millis();
    lv_obj_add_flag(objects.tab_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.tab_settings, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.start, LV_OBJ_FLAG_HIDDEN);
    hide_k_buttons();
    lv_obj_add_state(objects.start, LV_STATE_DISABLED);
    lv_obj_remove_flag(objects.stop, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_state(objects.stop, LV_STATE_DISABLED);
    lv_obj_remove_flag(objects.spinner, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.prog_bar, LV_OBJ_FLAG_HIDDEN);
    for (byte i = 0; i < PUMP_AMOUNT; i++) // считаем время программы
    {                                      // пробегаем по всем помпам
      lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, i);
      lv_bar_set_value(bar, 0, LV_ANIM_OFF);
    }
    zoneTimer = millis() - zone_pause * 1000 * minutes; // убираем паузу перед запуском полива
    pump_on();
  }
  programm_time = 0;
  for (byte i = 0; i < PUMP_AMOUNT; i++) // считаем время программы
  {                                      // пробегаем по всем помпам
    lv_obj_t *bar = lv_obj_get_child(objects.bars_panel, i);
    if ((dw_time[i] > 0 || cw_time[i] > 0) && pump_finished[i] == false)
    {
      uint32_t dw_t = dw_time[i] * 1000 * minutes / 100 * k_dw_time;
      programm_time = programm_time + dw_t + (cw_time[i] + zone_pause) * 1000 * minutes;
      lv_obj_remove_flag(bar, LV_OBJ_FLAG_HIDDEN);
    }
    else
      lv_obj_add_flag(bar, LV_OBJ_FLAG_HIDDEN);
  }
  programm_time = programm_time - (zone_pause * 1000 * minutes);
  thisH = floor((long)programm_time / 3600 / 1000); // секунды в часы
  thisM = floor((programm_time / 1000 - (long)thisH * 3600) / 60);
  thisS = programm_time / 1000 - (long)thisH * 3600 - thisM * 60;
  lv_bar_set_range(objects.prog_bar, 0, programm_time);
}

void action_zone_time_clicked(lv_event_t *e)
{
  obj = lv_event_get_current_target_obj(e); // zone
  water_num = lv_obj_get_index(lv_event_get_target_obj(e));
  if (lv_obj_has_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN))
  {
    lv_obj_remove_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(objects.input_area, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(objects.input_area, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/
  }
}

void action_input_done(lv_event_t *e)
{
  const char *txt = lv_textarea_get_text(objects.input_area);
  lv_obj_t *ob = lv_obj_get_child(obj, water_num);
  if ((int)txt[0] == 0 || String(txt) == "0" || String(txt) == "00")
    txt = "0";
  lv_obj_add_flag(objects.keyboard, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(objects.input_area, LV_OBJ_FLAG_HIDDEN);
  settings.begin("Settings", RW_MODE);
  int zone_num = (int)lv_obj_get_index(obj);
  if (water_num == 1)
  {
    dw_time[zone_num] = atol(txt);
    settings.putBytes("dw_time", dw_time, PUMP_AMOUNT * 4);
  }
  else
  {
    cw_time[zone_num] = atol(txt);
    settings.putBytes("cw_time", cw_time, PUMP_AMOUNT * 4);
  }
  settings.end();
  lv_label_set_text(ob, txt);
  lv_textarea_set_text(objects.input_area, "");
  if (cw_time[zone_num] == 0 && dw_time[zone_num] == 0)
    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN);
  else
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
  update_zone_list();
}
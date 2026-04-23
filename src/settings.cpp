#include <lvgl.h>
#include <Preferences.h>
#include "constants.h"
#include "ui/screens.h"

#define RW_MODE false
#define RO_MODE true

uint32_t GFX_BL_VALUE, GFX_BL_TIME;     // яркость, время подсветки экрана
uint32_t dw_time[PUMP_AMOUNT];          // время полива грязной водой
uint32_t cw_time[PUMP_AMOUNT];          // время полива чистой водой
uint32_t pump_timers[PUMP_AMOUNT];      // таймеры зон
boolean pump_state[PUMP_AMOUNT];        // состояние помпы
boolean pump_finished[PUMP_AMOUNT];     // зона уже полита
uint32_t zone_pause;                    // пауза между зонами
uint32_t zoneTimer;                     // таймер паузы
boolean now_pumping = false;            // идет полив
boolean dryState = true;                // какой клапан открыт. true - dry(грязная) false - чистая
uint32_t k_dw_time = DEFAULT_K_DW_TIME; // коэффициент
int minutes = DEFAULT_MINUTES;          // отладка
int ROTATION = 0;                       // поворот экрана
bool use_pult, lora, esp_now;
extern void update_zone_list();

Preferences settings;

void setup_settings()
{
    settings.begin("Settings", RO_MODE);
    bool tpInit = settings.isKey("nvsInit");

    if (!tpInit)
    {
        settings.end();
        settings.begin("Settings", RW_MODE);

        settings.putInt("ROTATION", 0);
        settings.putLong("GFX_BL_VALUE", DEFAULT_GFX_BL_VALUE);
        settings.putLong("GFX_BL_TIME", DEFAULT_GFX_BL_TIME);
        settings.putLong("zone_pause", DEFAULT_ZONE_PAUSE);
        settings.putLong("k_dw_time", DEFAULT_K_DW_TIME);

        // Обнуление глобальных массивов и их сохранение
        memset(dw_time, 0, sizeof(dw_time));
        memset(cw_time, 0, sizeof(cw_time));

        settings.putBytes("dw_time", dw_time, sizeof(dw_time));
        settings.putBytes("cw_time", cw_time, sizeof(cw_time));
        settings.putBool("use_pult", false);
        settings.putBool("lora", false);
        settings.putBool("esp_now", true);

        settings.putBool("nvsInit", true);
        settings.end();
        settings.begin("Settings", RO_MODE);
    }

    ROTATION = settings.getInt("ROTATION", 0);
    zone_pause = settings.getLong("zone_pause");
    GFX_BL_VALUE = settings.getLong("GFX_BL_VALUE");
    GFX_BL_TIME = settings.getLong("GFX_BL_TIME");
    k_dw_time = settings.getLong("k_dw_time");
    use_pult = settings.getBool("use_pult");
    lora = settings.getBool("lora");
    esp_now = settings.getBool("esp_now");

    settings.getBytes("dw_time", dw_time, sizeof(dw_time));
    settings.getBytes("cw_time", cw_time, sizeof(cw_time));
    settings.end();
}

void fill_widgets()
{
    /* Расширение области нажатия с помощью констант */
    lv_obj_set_ext_click_area(objects.pult, EXT_CLICK_AREA_SMALL);
    lv_obj_set_ext_click_area(objects.debug, EXT_CLICK_AREA_SMALL);
    lv_obj_set_ext_click_area(objects.bl, EXT_CLICK_AREA_SMALL);
    lv_obj_set_ext_click_area(objects.button_10, EXT_CLICK_AREA_LARGE);
    lv_obj_set_ext_click_area(objects.button_dec, EXT_CLICK_AREA_LARGE);
    lv_obj_set_ext_click_area(objects.button_reset, EXT_CLICK_AREA_LARGE);
    lv_obj_set_ext_click_area(objects.button_inc, EXT_CLICK_AREA_LARGE);
    lv_obj_set_ext_click_area(objects.button10, EXT_CLICK_AREA_LARGE);

    if (use_pult)
    {
        lv_obj_add_state(objects.pult, LV_STATE_CHECKED);
        lv_obj_remove_flag(objects.esp_lora, LV_OBJ_FLAG_HIDDEN);
    }
    if (esp_now)
        lv_obj_add_state(objects.esp_now, LV_STATE_CHECKED);
    lv_obj_set_radio_button(objects.esp_now, true);
    if (lora)
        lv_obj_add_state(objects.lora, LV_STATE_CHECKED);
    lv_obj_set_radio_button(objects.lora, true);
    lv_slider_set_value(objects.bl, GFX_BL_VALUE, LV_ANIM_OFF);
    lv_textarea_set_text(objects.bl_idle, String(GFX_BL_TIME).c_str());
    lv_textarea_set_text(objects.pause, String(zone_pause).c_str());
    lv_label_set_text(objects.k_dw_time, String(k_dw_time).c_str());

    for (int i = 0; i < PUMP_AMOUNT; i++)
    {
        lv_obj_t *button = lv_obj_get_child(objects.zone_times, i);

        lv_obj_t *dw = lv_obj_get_child(button, 1);
        lv_label_set_text(dw, String(dw_time[i]).c_str());
        lv_obj_set_ext_click_area(dw, EXT_CLICK_AREA_SMALL);

        lv_obj_t *cw = lv_obj_get_child(button, 2);
        lv_label_set_text(cw, String(cw_time[i]).c_str());
        lv_obj_set_ext_click_area(cw, EXT_CLICK_AREA_SMALL);

        if (cw_time[i] != 0 || dw_time[i] != 0)
            lv_obj_set_style_bg_opa(button, FULL_OPACITY, LV_PART_MAIN);
        else
            lv_obj_set_style_bg_opa(button, LOW_OPACITY, LV_PART_MAIN);
    }
    update_zone_list();
}
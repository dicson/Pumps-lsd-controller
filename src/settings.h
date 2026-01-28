#include <Preferences.h>

#define RW_MODE false
#define RO_MODE true
#define PUPM_AMOUNT 16
int32_t GFX_BL_VALUE, GFX_BL_TIME;    // яркость, время подсветки экрана
uint32_t dw_time[PUPM_AMOUNT];        // время полива грязной водой
uint32_t cw_time[PUPM_AMOUNT];        // время полива чистой водой
boolean h_zone13, h_zone14, h_zone16; // отображение зон
uint32_t pump_timers[PUPM_AMOUNT];    // таймеры зон
boolean pump_state[PUPM_AMOUNT];      //
boolean pump_finished[PUPM_AMOUNT];   // зона уже полита
uint32_t zone_pause;                  // пауза между зонами
uint32_t zoneTimer;                   // таймер паузы
boolean now_pumping = false;          // идет полив
boolean dryState = true;              // какой клапан открыт. true - dry(грязная) false - чистая
uint32_t k_dw_time = 100;             // коэффициент

Preferences settings;
int minutes = 60; //

void setup_settings()
{
    settings.begin("Settings", RO_MODE);
    bool tpInit = settings.isKey("nvsInit");

    if (tpInit == false)
    {
        settings.end();
        settings.begin("Settings", RW_MODE);

        settings.putLong("GFX_BL_VALUE", 200);
        settings.putLong("GFX_BL_TIME", 30);
        settings.putLong("zone_pause", zone_pause);
        settings.putLong("k_dw_time", 100);
        uint32_t dw_time[PUPM_AMOUNT];
        settings.putBytes("dw_time", dw_time, PUPM_AMOUNT * 4);
        uint32_t cw_time[PUPM_AMOUNT];
        settings.putBytes("cw_time", cw_time, PUPM_AMOUNT * 4);

        settings.putBool("nvsInit", true);
        settings.end();
        settings.begin("Settings", RO_MODE);
    }

    zone_pause = settings.getLong("zone_pause");
    GFX_BL_VALUE = settings.getLong("GFX_BL_VALUE");
    GFX_BL_TIME = settings.getLong("GFX_BL_TIME");
    k_dw_time = settings.getLong("k_dw_time", 100);
    settings.getBytes("dw_time", dw_time, PUPM_AMOUNT * 4);
    settings.getBytes("cw_time", cw_time, PUPM_AMOUNT * 4);
    settings.end();
}

void fill_widgets()
{
    lv_slider_set_value(objects.bl, GFX_BL_VALUE, LV_ANIM_ON);
    lv_textarea_set_text(objects.bl_idle, String(GFX_BL_TIME).c_str());
    lv_textarea_set_text(objects.pause, String(zone_pause).c_str());
    lv_obj_t *dw_list[PUPM_AMOUNT] = {
        objects.d_1,
        objects.d_2,
        objects.d_3,
        objects.d_4,
        objects.d_5,
        objects.d_6,
        objects.d_7,
        objects.d_8,
        objects.d_9,
        objects.d_10,
        objects.d_11,
        objects.d_12,
        objects.d_13,
        objects.d_14,
        objects.d_15,
        objects.d_16,
    };
    for (int i = 0; i < PUPM_AMOUNT; i++)
    {
        lv_label_set_text(dw_list[i], String(dw_time[i]).c_str());
        if (dw_time[i] == 0)
        {
            lv_obj_set_style_bg_opa(lv_obj_get_parent(dw_list[i]), 100, LV_PART_MAIN);
        }
    }
    lv_task_handler();
    lv_obj_t *cw_list[PUPM_AMOUNT] = {
        objects.c_1,
        objects.c_2,
        objects.c_3,
        objects.c_4,
        objects.c_5,
        objects.c_6,
        objects.c_7,
        objects.c_8,
        objects.c_9,
        objects.c_10,
        objects.c_11,
        objects.c_12,
        objects.c_13,
        objects.c_14,
        objects.c_15,
        objects.c_16,
    };
    for (int i = 0; i < PUPM_AMOUNT; i++)
    {
        lv_label_set_text(cw_list[i], String(cw_time[i]).c_str());
        if (cw_time[i] != 0)
        {
            lv_obj_set_style_bg_opa(lv_obj_get_parent(cw_list[i]), 255, LV_PART_MAIN);
        }
    }

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
    for (int i = 0; i < PUPM_AMOUNT; i++)
    {

        if (cw_time[i] != 0 || dw_time[i] != 0)
        {
            lv_obj_remove_flag(bar_list[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
    lv_label_set_text(objects.k_dw_time, String(k_dw_time).c_str());
}
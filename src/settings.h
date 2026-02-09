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
int minutes = 60;                     // отладка
extern void update_zone_list();

Preferences settings;

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

    for (int i = 0; i < PUPM_AMOUNT; i++)
    {
        lv_obj_t *button = lv_obj_get_child(objects.tab_2, i);

        lv_obj_t *dw = lv_obj_get_child(button, 1);
        lv_label_set_text(dw, String(dw_time[i]).c_str());

        lv_obj_t *cw = lv_obj_get_child(button, 2);
        lv_label_set_text(cw, String(cw_time[i]).c_str());

        if (cw_time[i] != 0 || dw_time[i] != 0)
        {
            lv_obj_set_style_bg_opa(lv_obj_get_parent(cw), 255, LV_PART_MAIN);
        }
        else
            lv_obj_set_style_bg_opa(lv_obj_get_parent(dw), 100, LV_PART_MAIN);
        lv_task_handler();
    }

    update_zone_list();
    lv_label_set_text(objects.k_dw_time, String(k_dw_time).c_str());
}
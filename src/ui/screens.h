#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *tabview;
    lv_obj_t *prog_bar;
    lv_obj_t *bar_label;
    lv_obj_t *spinner;
    lv_obj_t *stop;
    lv_obj_t *start;
    lv_obj_t *obj0;
    lv_obj_t *pump;
    lv_obj_t *pipe;
    lv_obj_t *osmos;
    lv_obj_t *obj1;
    lv_obj_t *bar_0;
    lv_obj_t *obj2;
    lv_obj_t *bar_1;
    lv_obj_t *obj3;
    lv_obj_t *bar_2;
    lv_obj_t *obj4;
    lv_obj_t *bar_3;
    lv_obj_t *obj5;
    lv_obj_t *bar_4;
    lv_obj_t *obj6;
    lv_obj_t *bar_5;
    lv_obj_t *obj7;
    lv_obj_t *bar_6;
    lv_obj_t *obj8;
    lv_obj_t *bar_7;
    lv_obj_t *obj9;
    lv_obj_t *bar_8;
    lv_obj_t *obj10;
    lv_obj_t *bar_9;
    lv_obj_t *obj11;
    lv_obj_t *bar_10;
    lv_obj_t *obj12;
    lv_obj_t *bar_11;
    lv_obj_t *obj13;
    lv_obj_t *bar_12;
    lv_obj_t *obj14;
    lv_obj_t *bar_13;
    lv_obj_t *obj15;
    lv_obj_t *bar_14;
    lv_obj_t *obj16;
    lv_obj_t *bar_15;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *k_dw_time;
    lv_obj_t *k_container;
    lv_obj_t *obj19;
    lv_obj_t *k_reset;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *zone13_1;
    lv_obj_t *zone14_1;
    lv_obj_t *zone16_1;
    lv_obj_t *zone1;
    lv_obj_t *d_1;
    lv_obj_t *c_1;
    lv_obj_t *zone2;
    lv_obj_t *d_2;
    lv_obj_t *c_2;
    lv_obj_t *zone3;
    lv_obj_t *d_3;
    lv_obj_t *c_3;
    lv_obj_t *zone4;
    lv_obj_t *d_4;
    lv_obj_t *c_4;
    lv_obj_t *zone5;
    lv_obj_t *d_5;
    lv_obj_t *c_5;
    lv_obj_t *zone6;
    lv_obj_t *d_6;
    lv_obj_t *c_6;
    lv_obj_t *zone7;
    lv_obj_t *d_7;
    lv_obj_t *c_7;
    lv_obj_t *zone8;
    lv_obj_t *d_8;
    lv_obj_t *c_8;
    lv_obj_t *zone9;
    lv_obj_t *d_9;
    lv_obj_t *c_9;
    lv_obj_t *zone10;
    lv_obj_t *d_10;
    lv_obj_t *c_10;
    lv_obj_t *zone11;
    lv_obj_t *d_11;
    lv_obj_t *c_11;
    lv_obj_t *zone12;
    lv_obj_t *d_12;
    lv_obj_t *c_12;
    lv_obj_t *zone12_1;
    lv_obj_t *zone13;
    lv_obj_t *d_13;
    lv_obj_t *c_13;
    lv_obj_t *zone14;
    lv_obj_t *d_14;
    lv_obj_t *c_14;
    lv_obj_t *zone15;
    lv_obj_t *d_15;
    lv_obj_t *c_15;
    lv_obj_t *zone16;
    lv_obj_t *d_16;
    lv_obj_t *c_16;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *input_area;
    lv_obj_t *keyboard_1;
    lv_obj_t *input_area_1;
    lv_obj_t *keyboard;
    lv_obj_t *settings;
    lv_obj_t *obj41;
    lv_obj_t *debug;
    lv_obj_t *bl;
    lv_obj_t *textlabel;
    lv_obj_t *bl_idle;
    lv_obj_t *pause;
    lv_obj_t *update;
    lv_obj_t *settings_kb;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
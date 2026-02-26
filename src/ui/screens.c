#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // tabview
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.tabview = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_BOTTOM);
            lv_tabview_set_tab_bar_size(obj, 32);
            lv_obj_add_event_cb(obj, action_tab_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_FOCUSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // tab_main
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Программа");
                    objects.tab_main = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_margin_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                        lv_obj_set_style_grid_row_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                    {
                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                        lv_obj_set_style_grid_column_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // prog_bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.prog_bar = obj;
                            lv_obj_set_pos(obj, 128, 359);
                            lv_obj_set_size(obj, 447, 51);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // bar_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.bar_label = obj;
                                    lv_obj_set_pos(obj, 169, 14);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffeceff0), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1.11 / 1.11");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 586, 356);
                            lv_obj_set_size(obj, 184, 57);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spinner
                                    lv_obj_t *obj = lv_spinner_create(parent_obj);
                                    objects.spinner = obj;
                                    lv_obj_set_pos(obj, 589, 378);
                                    lv_obj_set_size(obj, 44, 45);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                }
                                {
                                    // Stop
                                    lv_obj_t *obj = lv_button_create(parent_obj);
                                    objects.stop = obj;
                                    lv_obj_set_pos(obj, 663, 363);
                                    lv_obj_set_size(obj, 100, 50);
                                    lv_obj_add_event_cb(obj, action_stop, LV_EVENT_RELEASED, (void *)0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_add_state(obj, LV_STATE_DISABLED);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe30029), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Стоп");
                                        }
                                    }
                                }
                                {
                                    // Start
                                    lv_obj_t *obj = lv_button_create(parent_obj);
                                    objects.start = obj;
                                    lv_obj_set_pos(obj, 663, 363);
                                    lv_obj_set_size(obj, 100, 50);
                                    lv_obj_add_event_cb(obj, action_start, LV_EVENT_RELEASED, (void *)0);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Старт");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, 586, -20);
                            lv_obj_set_size(obj, 184, 166);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_1style(obj);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 593, -4);
                                    lv_obj_set_size(obj, 170, 29);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 26, 13);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Насос");
                                        }
                                        {
                                            // pump
                                            lv_obj_t *obj = lv_led_create(parent_obj);
                                            objects.pump = obj;
                                            lv_obj_set_pos(obj, 149, 8);
                                            lv_obj_set_size(obj, 23, 22);
                                            lv_led_set_color(obj, lv_color_hex(0xffff0000));
                                            lv_led_set_brightness(obj, 200);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                            lv_obj_set_style_shadow_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 593, 36);
                                    lv_obj_set_size(obj, 170, 29);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 186, -15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Скважина");
                                        }
                                        {
                                            // pipe
                                            lv_obj_t *obj = lv_led_create(parent_obj);
                                            objects.pipe = obj;
                                            lv_obj_set_pos(obj, 149, 7);
                                            lv_obj_set_size(obj, 23, 22);
                                            lv_led_set_color(obj, lv_color_hex(0xff449dda));
                                            lv_led_set_brightness(obj, 200);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 593, 75);
                                    lv_obj_set_size(obj, 170, 29);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 186, -15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Осмос");
                                        }
                                        {
                                            // osmos
                                            lv_obj_t *obj = lv_led_create(parent_obj);
                                            objects.osmos = obj;
                                            lv_obj_set_pos(obj, 149, 8);
                                            lv_obj_set_size(obj, 23, 22);
                                            lv_led_set_color(obj, lv_color_hex(0xff449dda));
                                            lv_led_set_brightness(obj, 200);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 593, -4);
                                    lv_obj_set_size(obj, 170, 29);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 26, 13);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Реле зон");
                                        }
                                        {
                                            // relay_zone_led
                                            lv_obj_t *obj = lv_led_create(parent_obj);
                                            objects.relay_zone_led = obj;
                                            lv_obj_set_pos(obj, 149, 8);
                                            lv_obj_set_size(obj, 23, 22);
                                            lv_led_set_color(obj, lv_color_hex(0xff00ff00));
                                            lv_led_set_brightness(obj, 200);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                            lv_obj_set_style_shadow_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 593, -4);
                                    lv_obj_set_size(obj, 170, 29);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 26, 13);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Реле насоса");
                                        }
                                        {
                                            // relay_water_led
                                            lv_obj_t *obj = lv_led_create(parent_obj);
                                            objects.relay_water_led = obj;
                                            lv_obj_set_pos(obj, 149, 8);
                                            lv_obj_set_size(obj, 23, 22);
                                            lv_led_set_color(obj, lv_color_hex(0xff00ff00));
                                            lv_led_set_brightness(obj, 200);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                            lv_obj_set_style_shadow_width(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // bars_panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.bars_panel = obj;
                            lv_obj_set_pos(obj, -20, -20);
                            lv_obj_set_size(obj, 144, 433);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC);
                            add_style_1style(obj);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // bar_0
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_0 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj1 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  1");
                                        }
                                    }
                                }
                                {
                                    // bar_1
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_1 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj2 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  2");
                                        }
                                    }
                                }
                                {
                                    // bar_2
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_2 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj3 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  3");
                                        }
                                    }
                                }
                                {
                                    // bar_3
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_3 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj4 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  4");
                                        }
                                    }
                                }
                                {
                                    // bar_4
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_4 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj5 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  5");
                                        }
                                    }
                                }
                                {
                                    // bar_5
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_5 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj6 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  6");
                                        }
                                    }
                                }
                                {
                                    // bar_6
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_6 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj7 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  7");
                                        }
                                    }
                                }
                                {
                                    // bar_7
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_7 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj8 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  8");
                                        }
                                    }
                                }
                                {
                                    // bar_8
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_8 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj9 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА  9");
                                        }
                                    }
                                }
                                {
                                    // bar_9
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_9 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj10 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 10");
                                        }
                                    }
                                }
                                {
                                    // bar_10
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_10 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj11 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 11");
                                        }
                                    }
                                }
                                {
                                    // bar_11
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_11 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj12 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 12");
                                        }
                                    }
                                }
                                {
                                    // bar_12
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_12 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj13 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 13");
                                        }
                                    }
                                }
                                {
                                    // bar_13
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_13 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj14 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 14");
                                        }
                                    }
                                }
                                {
                                    // bar_14
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_14 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj15 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 15");
                                        }
                                    }
                                }
                                {
                                    // bar_15
                                    lv_obj_t *obj = lv_bar_create(parent_obj);
                                    objects.bar_15 = obj;
                                    lv_obj_set_pos(obj, 136, -2);
                                    lv_obj_set_size(obj, 110, 19);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
                                    lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff087343), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj16 = obj;
                                            lv_obj_set_pos(obj, 20, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "ЗОНА 16");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj17 = obj;
                            lv_obj_set_pos(obj, 134, -20);
                            lv_obj_set_size(obj, 450, 125);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_1style(obj);
                            lv_obj_set_style_pad_top(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_width(obj, 450, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_x(obj, 130, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 5, 9);
                                    lv_obj_set_size(obj, 208, 73);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_REVERSE, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_obj_create(parent_obj);
                                            lv_obj_set_pos(obj, 6216, 6);
                                            lv_obj_set_size(obj, 59, 32);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_column(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // k_dw_time
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.k_dw_time = obj;
                                                    lv_obj_set_pos(obj, 17, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_label_set_text(obj, "100");
                                                }
                                                {
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    lv_obj_set_pos(obj, 53, 4);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_label_set_text(obj, "%");
                                                }
                                            }
                                        }
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Коэффициент");
                                        }
                                    }
                                }
                                {
                                    // k_container
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.k_container = obj;
                                    lv_obj_set_pos(obj, 6, 86);
                                    lv_obj_set_size(obj, 207, 29);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            lv_obj_set_pos(obj, -327, 3);
                                            lv_obj_set_size(obj, 45, 30);
                                            lv_obj_add_event_cb(obj, action_spinbox_decrement_event_cb, LV_EVENT_SHORT_CLICKED, (void *)0);
                                            lv_obj_add_event_cb(obj, action_spinbox_decrement_event_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.obj18 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            lv_obj_set_pos(obj, 125, 3);
                                            lv_obj_set_size(obj, 80, 30);
                                            lv_obj_add_event_cb(obj, action_k_reset, LV_EVENT_PRESSED, (void *)0);
                                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // k_reset
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.k_reset = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "сброс");
                                                }
                                            }
                                        }
                                        {
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            lv_obj_set_pos(obj, 238, 3);
                                            lv_obj_set_size(obj, 45, 30);
                                            lv_obj_add_event_cb(obj, action_spinbox_increment_event_cb, LV_EVENT_SHORT_CLICKED, (void *)0);
                                            lv_obj_add_event_cb(obj, action_spinbox_increment_event_cb, LV_EVENT_LONG_PRESSED_REPEAT, (void *)0);
                                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
                                            lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.obj19 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                {
                    // tab_1
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Выбрать и полить");
                    objects.tab_1 = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj20 = obj;
                            lv_obj_set_pos(obj, -12, -11);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj21 = obj;
                            lv_obj_set_pos(obj, -12, 44);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "2");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 119, 43);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj22 = obj;
                            lv_obj_set_pos(obj, -12, 99);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "3");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 109, 45);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj23 = obj;
                            lv_obj_set_pos(obj, -12, 154);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "4");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 114, 39);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj24 = obj;
                            lv_obj_set_pos(obj, -12, 210);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "5");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj25 = obj;
                            lv_obj_set_pos(obj, -12, 265);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "6");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj26 = obj;
                            lv_obj_set_pos(obj, -12, 320);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "7");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj27 = obj;
                            lv_obj_set_pos(obj, -12, 375);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "8\n");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            // _9
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects._9 = obj;
                            lv_obj_set_pos(obj, 181, -11);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "9");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj28 = obj;
                            lv_obj_set_pos(obj, 181, 44);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "10");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 119, 43);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj29 = obj;
                            lv_obj_set_pos(obj, 181, 99);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "11");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 109, 45);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj30 = obj;
                            lv_obj_set_pos(obj, 181, 154);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "12");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 114, 39);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj31 = obj;
                            lv_obj_set_pos(obj, 181, 210);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "13");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj32 = obj;
                            lv_obj_set_pos(obj, 181, 265);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "14");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj33 = obj;
                            lv_obj_set_pos(obj, 181, 320);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "15");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 112, 53);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.obj34 = obj;
                            lv_obj_set_pos(obj, 181, 375);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_selected, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_max_width(obj, 536870911, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "16");
                                }
                                {
                                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                    lv_obj_set_pos(obj, 104, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_checkbox_set_text(obj, "поливать");
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                                }
                            }
                        }
                    }
                }
                {
                    // tab_2
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Настройка зон");
                    objects.tab_2 = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // zone1
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone1 = obj;
                            lv_obj_set_pos(obj, -12, -11);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1");
                                }
                                {
                                    // d_4
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_4 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_4
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_4 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone2
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone2 = obj;
                            lv_obj_set_pos(obj, -12, 45);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "2");
                                }
                                {
                                    // d_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_2 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_2 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone3
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone3 = obj;
                            lv_obj_set_pos(obj, -12, 100);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "3");
                                }
                                {
                                    // d_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_3 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_3 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone4
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone4 = obj;
                            lv_obj_set_pos(obj, -12, 156);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "4");
                                }
                                {
                                    // d_5
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_5 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_5
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_5 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone5
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone5 = obj;
                            lv_obj_set_pos(obj, -12, 211);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "5");
                                }
                                {
                                    // d_6
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_6 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_6
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_6 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone6
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone6 = obj;
                            lv_obj_set_pos(obj, -12, 267);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "6");
                                }
                                {
                                    // d_7
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_7 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_7
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_7 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone7
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone7 = obj;
                            lv_obj_set_pos(obj, -12, 322);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "7");
                                }
                                {
                                    // d_8
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_8 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_8
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_8 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone8
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone8 = obj;
                            lv_obj_set_pos(obj, -12, 378);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "8");
                                }
                                {
                                    // d_9
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_9 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_9
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_9 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone9
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone9 = obj;
                            lv_obj_set_pos(obj, 180, -11);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "9");
                                }
                                {
                                    // d_10
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_10 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_10
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_10 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone10
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone10 = obj;
                            lv_obj_set_pos(obj, 180, 45);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "10");
                                }
                                {
                                    // d_11
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_11 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_11
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_11 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone11
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone11 = obj;
                            lv_obj_set_pos(obj, 180, 100);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "11");
                                }
                                {
                                    // d_12
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_12 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_12
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_12 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone12
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone12 = obj;
                            lv_obj_set_pos(obj, 180, 156);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "12");
                                }
                                {
                                    // d_13
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_13 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_13
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_13 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone13
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone13 = obj;
                            lv_obj_set_pos(obj, 180, 211);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "13");
                                }
                                {
                                    // d_14
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_14 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_14
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_14 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone14
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone14 = obj;
                            lv_obj_set_pos(obj, 180, 267);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "14");
                                }
                                {
                                    // d_15
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_15 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_15
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_15 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone15
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone15 = obj;
                            lv_obj_set_pos(obj, 180, 322);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "15");
                                }
                                {
                                    // d_16
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_16 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_16
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_16 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // zone16
                            lv_obj_t *obj = lv_button_create(parent_obj);
                            objects.zone16 = obj;
                            lv_obj_set_pos(obj, 180, 378);
                            lv_obj_set_size(obj, 185, 45);
                            lv_obj_add_event_cb(obj, action_zone_time_clicked, LV_EVENT_RELEASED, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1c6a44), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "16");
                                }
                                {
                                    // d_17
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.d_17 = obj;
                                    lv_obj_set_pos(obj, -6, -6);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0");
                                }
                                {
                                    // c_17
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.c_17 = obj;
                                    lv_obj_set_pos(obj, 2, 23);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE|LV_OBJ_FLAG_CLICKABLE);
                                    lv_obj_set_style_pad_bottom(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0b16cd), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_pad(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_outline_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "25");
                                }
                            }
                        }
                        {
                            // input_area
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.input_area = obj;
                            lv_obj_set_pos(obj, 465, 185);
                            lv_obj_set_size(obj, 40, 36);
                            lv_textarea_set_accepted_chars(obj, "0123456789");
                            lv_textarea_set_max_length(obj, 2);
                            lv_textarea_set_placeholder_text(obj, "минут");
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_column(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // keyboard
                            lv_obj_t *obj = lv_keyboard_create(parent_obj);
                            objects.keyboard = obj;
                            lv_obj_set_pos(obj, 451, 227);
                            lv_obj_set_size(obj, 292, 193);
                            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                            lv_obj_add_event_cb(obj, action_input_done, LV_EVENT_READY, (void *)0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // tab_settings
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Настройки");
                    objects.tab_settings = obj;
                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_margin_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj35 = obj;
                            lv_obj_set_pos(obj, -20, -17);
                            lv_obj_set_size(obj, 324, 430);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_1style(obj);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_row(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, -14, 112);
                                    lv_obj_set_size(obj, 312, 32);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // debug
                                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                            objects.debug = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_checkbox_set_text(obj, "Отладка");
                                            lv_obj_add_event_cb(obj, action_debug, LV_EVENT_VALUE_CHANGED, (void *)0);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, -14, 112);
                                    lv_obj_set_size(obj, 312, 32);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // show_log
                                            lv_obj_t *obj = lv_checkbox_create(parent_obj);
                                            objects.show_log = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_checkbox_set_text(obj, "Выводить лог");
                                            lv_obj_add_event_cb(obj, action_show_log, LV_EVENT_VALUE_CHANGED, (void *)0);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 300, 66);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN_REVERSE, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // bl
                                            lv_obj_t *obj = lv_slider_create(parent_obj);
                                            objects.bl = obj;
                                            lv_obj_set_pos(obj, 53, 90);
                                            lv_obj_set_size(obj, 275, 10);
                                            lv_slider_set_range(obj, 50, 253);
                                            lv_slider_set_value(obj, 200, LV_ANIM_ON);
                                            lv_obj_add_event_cb(obj, action_bl_released, LV_EVENT_RELEASED, (void *)0);
                                            lv_obj_add_event_cb(obj, action_bl_changed, LV_EVENT_VALUE_CHANGED, (void *)0);
                                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Яркость экрана");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, -203, -17);
                                    lv_obj_set_size(obj, 309, 32);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_column(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, -4, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Автовыключение экрана ");
                                        }
                                        {
                                            // bl_idle
                                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                                            objects.bl_idle = obj;
                                            lv_obj_set_pos(obj, 222, -2);
                                            lv_obj_set_size(obj, 30, 26);
                                            lv_textarea_set_accepted_chars(obj, "0123456789");
                                            lv_textarea_set_max_length(obj, 2);
                                            lv_textarea_set_text(obj, "10");
                                            lv_textarea_set_one_line(obj, true);
                                            lv_textarea_set_password_mode(obj, false);
                                            lv_obj_add_event_cb(obj, action_idle_time_unfocused, LV_EVENT_READY, (void *)0);
                                            lv_obj_add_event_cb(obj, action_idle_time_focused, LV_EVENT_RELEASED, (void *)0);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 253, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "сек.");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    lv_obj_set_pos(obj, -2489, 25);
                                    lv_obj_set_size(obj, 309, 217);
                                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_column(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                                        lv_obj_set_style_grid_row_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    }
                                    {
                                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                                        lv_obj_set_style_grid_column_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    }
                                    lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, -4, -2);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Пауза между зонами    ");
                                        }
                                        {
                                            // pause
                                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                                            objects.pause = obj;
                                            lv_obj_set_pos(obj, 222, -2);
                                            lv_obj_set_size(obj, 30, 26);
                                            lv_textarea_set_accepted_chars(obj, "0123456789");
                                            lv_textarea_set_max_length(obj, 2);
                                            lv_textarea_set_text(obj, "10");
                                            lv_textarea_set_one_line(obj, true);
                                            lv_textarea_set_password_mode(obj, false);
                                            lv_obj_add_event_cb(obj, action_pause_ready, LV_EVENT_READY, (void *)0);
                                            lv_obj_add_event_cb(obj, action_pause_released, LV_EVENT_RELEASED, (void *)0);
                                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 253, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "мин.");
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_button_create(parent_obj);
                                    lv_obj_set_pos(obj, -646, 1000);
                                    lv_obj_set_size(obj, 300, 32);
                                    lv_obj_add_event_cb(obj, action_update, LV_EVENT_PRESSED, (void *)0);
                                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // update
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.update = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Обновление прошивки");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // settings_kb
                            lv_obj_t *obj = lv_keyboard_create(parent_obj);
                            objects.settings_kb = obj;
                            lv_obj_set_pos(obj, 335, 179);
                            lv_obj_set_size(obj, 300, 204);
                            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj36 = obj;
                            lv_obj_set_pos(obj, 317, -16);
                            lv_obj_set_size(obj, 453, 429);
                            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_1style(obj);
                            lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                                lv_obj_set_style_grid_column_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                            }
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // log
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.log = obj;
                                    lv_obj_set_pos(obj, 360, 1112);
                                    lv_obj_set_size(obj, 430, 404);
                                    lv_textarea_set_max_length(obj, 12800);
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // message_box
            lv_obj_t *obj = lv_msgbox_create(parent_obj);
            objects.message_box = obj;
            lv_obj_set_pos(obj, 208, 183);
            lv_obj_set_size(obj, 344, 140);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 105, 51);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Полив окончен");
                }
            }
        }
    }
    lv_keyboard_set_textarea(objects.keyboard, objects.input_area);
    
    tick_screen_main();
}

void delete_screen_main() {
    lv_obj_delete(objects.main);
    objects.main = 0;
    objects.tabview = 0;
    objects.tab_main = 0;
    objects.prog_bar = 0;
    objects.bar_label = 0;
    objects.spinner = 0;
    objects.stop = 0;
    objects.start = 0;
    objects.obj0 = 0;
    objects.pump = 0;
    objects.pipe = 0;
    objects.osmos = 0;
    objects.relay_zone_led = 0;
    objects.relay_water_led = 0;
    objects.bars_panel = 0;
    objects.bar_0 = 0;
    objects.obj1 = 0;
    objects.bar_1 = 0;
    objects.obj2 = 0;
    objects.bar_2 = 0;
    objects.obj3 = 0;
    objects.bar_3 = 0;
    objects.obj4 = 0;
    objects.bar_4 = 0;
    objects.obj5 = 0;
    objects.bar_5 = 0;
    objects.obj6 = 0;
    objects.bar_6 = 0;
    objects.obj7 = 0;
    objects.bar_7 = 0;
    objects.obj8 = 0;
    objects.bar_8 = 0;
    objects.obj9 = 0;
    objects.bar_9 = 0;
    objects.obj10 = 0;
    objects.bar_10 = 0;
    objects.obj11 = 0;
    objects.bar_11 = 0;
    objects.obj12 = 0;
    objects.bar_12 = 0;
    objects.obj13 = 0;
    objects.bar_13 = 0;
    objects.obj14 = 0;
    objects.bar_14 = 0;
    objects.obj15 = 0;
    objects.bar_15 = 0;
    objects.obj16 = 0;
    objects.obj17 = 0;
    objects.k_dw_time = 0;
    objects.k_container = 0;
    objects.obj18 = 0;
    objects.k_reset = 0;
    objects.obj19 = 0;
    objects.tab_1 = 0;
    objects.obj20 = 0;
    objects.obj21 = 0;
    objects.obj22 = 0;
    objects.obj23 = 0;
    objects.obj24 = 0;
    objects.obj25 = 0;
    objects.obj26 = 0;
    objects.obj27 = 0;
    objects._9 = 0;
    objects.obj28 = 0;
    objects.obj29 = 0;
    objects.obj30 = 0;
    objects.obj31 = 0;
    objects.obj32 = 0;
    objects.obj33 = 0;
    objects.obj34 = 0;
    objects.tab_2 = 0;
    objects.zone1 = 0;
    objects.d_4 = 0;
    objects.c_4 = 0;
    objects.zone2 = 0;
    objects.d_2 = 0;
    objects.c_2 = 0;
    objects.zone3 = 0;
    objects.d_3 = 0;
    objects.c_3 = 0;
    objects.zone4 = 0;
    objects.d_5 = 0;
    objects.c_5 = 0;
    objects.zone5 = 0;
    objects.d_6 = 0;
    objects.c_6 = 0;
    objects.zone6 = 0;
    objects.d_7 = 0;
    objects.c_7 = 0;
    objects.zone7 = 0;
    objects.d_8 = 0;
    objects.c_8 = 0;
    objects.zone8 = 0;
    objects.d_9 = 0;
    objects.c_9 = 0;
    objects.zone9 = 0;
    objects.d_10 = 0;
    objects.c_10 = 0;
    objects.zone10 = 0;
    objects.d_11 = 0;
    objects.c_11 = 0;
    objects.zone11 = 0;
    objects.d_12 = 0;
    objects.c_12 = 0;
    objects.zone12 = 0;
    objects.d_13 = 0;
    objects.c_13 = 0;
    objects.zone13 = 0;
    objects.d_14 = 0;
    objects.c_14 = 0;
    objects.zone14 = 0;
    objects.d_15 = 0;
    objects.c_15 = 0;
    objects.zone15 = 0;
    objects.d_16 = 0;
    objects.c_16 = 0;
    objects.zone16 = 0;
    objects.d_17 = 0;
    objects.c_17 = 0;
    objects.input_area = 0;
    objects.keyboard = 0;
    objects.tab_settings = 0;
    objects.obj35 = 0;
    objects.debug = 0;
    objects.show_log = 0;
    objects.bl = 0;
    objects.bl_idle = 0;
    objects.pause = 0;
    objects.update = 0;
    objects.settings_kb = 0;
    objects.obj36 = 0;
    objects.log = 0;
    objects.message_box = 0;
}

void tick_screen_main() {
}

void create_screen_page_update() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_update = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_1style(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.obj38 = obj;
                    lv_obj_set_pos(obj, -22, -22);
                    lv_obj_set_size(obj, 800, 480);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                        lv_obj_set_style_grid_row_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                    {
                        static lv_coord_t dsc[] = {0, LV_GRID_TEMPLATE_LAST};
                        lv_obj_set_style_grid_column_dsc_array(obj, dsc, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj39 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 400, 480);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.obj40 = obj;
                                    lv_obj_set_pos(obj, 3, 11);
                                    lv_obj_set_size(obj, 369, 222);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_text(obj, "WiFi сеть  (SSID): Pump_controller\nПароль Wi-Fi сети: 80100000");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                                    objects.obj41 = obj;
                                    lv_obj_set_pos(obj, 3, 257);
                                    lv_obj_set_size(obj, 369, 171);
                                    lv_textarea_set_max_length(obj, 128);
                                    lv_textarea_set_text(obj, "Перейти на страницу:\nhttp://192.168.4.1/update");
                                    lv_textarea_set_one_line(obj, false);
                                    lv_textarea_set_password_mode(obj, false);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // version
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.version = obj;
                                    lv_obj_set_pos(obj, 15, 445);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Текущая версия прошивки 0,0");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj42 = obj;
                            lv_obj_set_pos(obj, 400, 0);
                            lv_obj_set_size(obj, 400, 480);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_SPACE_AROUND, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_END, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_qrcode_create(parent_obj);
                                    objects.obj43 = obj;
                                    lv_obj_set_pos(obj, 2435, -996);
                                    lv_obj_set_size(obj, 211, 213);
                                    lv_qrcode_set_size(obj, 211);
                                    lv_qrcode_set_dark_color(obj, lv_color_hex(0xff20429f));
                                    lv_qrcode_set_light_color(obj, lv_color_hex(0xffe2f5fe));
                                    lv_qrcode_update(obj, "WIFI:S:Pump_controller;T:WPA2;P:80100000;;", 42);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                }
                                {
                                    lv_obj_t *obj = lv_qrcode_create(parent_obj);
                                    objects.obj44 = obj;
                                    lv_obj_set_pos(obj, -11, 72);
                                    lv_obj_set_size(obj, 211, 209);
                                    lv_qrcode_set_size(obj, 209);
                                    lv_qrcode_set_dark_color(obj, lv_color_hex(0xff20429f));
                                    lv_qrcode_set_light_color(obj, lv_color_hex(0xffe2f5fe));
                                    lv_qrcode_update(obj, "http://192.168.4.1/update", 25);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_update();
}

void delete_screen_page_update() {
    lv_obj_delete(objects.page_update);
    objects.page_update = 0;
    objects.obj37 = 0;
    objects.obj38 = 0;
    objects.obj39 = 0;
    objects.obj40 = 0;
    objects.obj41 = 0;
    objects.version = 0;
    objects.obj42 = 0;
    objects.obj43 = 0;
    objects.obj44 = 0;
}

void tick_screen_page_update() {
}

typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_main,
    create_screen_page_update,
};
void create_screen(int screen_index) {
    create_screen_funcs[screen_index]();
}
void create_screen_by_id(enum ScreensEnum screenId) {
    create_screen_funcs[screenId - 1]();
}

typedef void (*delete_screen_func_t)();
delete_screen_func_t delete_screen_funcs[] = {
    delete_screen_main,
    delete_screen_page_update,
};
void delete_screen(int screen_index) {
    delete_screen_funcs[screen_index]();
}
void delete_screen_by_id(enum ScreensEnum screenId) {
    delete_screen_funcs[screenId - 1]();
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_page_update,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "ubuntu 20", &ui_font_ubuntu_20 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_page_update();
}
#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_bl_changed(lv_event_t * e);
extern void action_bl_released(lv_event_t * e);
extern void action_input_done(lv_event_t * e);
extern void action_input_done1(lv_event_t * e);
extern void action_idle_time_focused(lv_event_t * e);
extern void action_idle_time_unfocused(lv_event_t * e);
extern void action_dw(lv_event_t * e);
extern void action_cw(lv_event_t * e);
extern void action_start(lv_event_t * e);
extern void action_stop(lv_event_t * e);
extern void action_tab_changed(lv_event_t * e);
extern void action_debug(lv_event_t * e);
extern void action_pause_ready(lv_event_t * e);
extern void action_pause_released(lv_event_t * e);
extern void action_spinbox_decrement_event_cb(lv_event_t * e);
extern void action_spinbox_increment_event_cb(lv_event_t * e);
extern void action_k_reset(lv_event_t * e);
extern void action_update(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/
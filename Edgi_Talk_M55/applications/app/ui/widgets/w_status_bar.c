#include "w_status_bar.h"

#include <lvgl.h>
#include <rtthread.h>
#include <stdio.h>

#define TOPBAR_BATTERY_TEXT   "78%"

static lv_obj_t *s_time_label = RT_NULL;
static lv_timer_t *s_time_timer = RT_NULL;

static void on_time_label_deleted(lv_event_t *e)
{
    LV_UNUSED(e);
    s_time_label = RT_NULL;

    if (s_time_timer != RT_NULL)
    {
        lv_timer_del(s_time_timer);
        s_time_timer = RT_NULL;
    }
}

static void update_time_label(void)
{
    if (s_time_label == RT_NULL)
    {
        return;
    }

    if (!lv_obj_is_valid(s_time_label))
    {
        s_time_label = RT_NULL;
        return;
    }

    rt_tick_t tick = rt_tick_get();
    rt_uint32_t sec = (rt_uint32_t)(tick / RT_TICK_PER_SECOND);

    rt_uint32_t hour = (sec / 3600U) % 24U;
    rt_uint32_t min = (sec / 60U) % 60U;

    char time_buf[6];
    rt_snprintf(time_buf, sizeof(time_buf), "%02u:%02u", hour, min);
    lv_label_set_text(s_time_label, time_buf);
}

static void time_timer_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    update_time_label();
}

lv_obj_t *w_status_bar_create(lv_obj_t *parent, const char *title)
{
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, LV_PCT(100), 54);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_radius(bar, 0, 0);
    lv_obj_set_style_border_width(bar, 0, 0);
    lv_obj_set_style_pad_left(bar, 12, 0);
    lv_obj_set_style_pad_right(bar, 12, 0);
    lv_obj_set_style_pad_top(bar, 4, 0);
    lv_obj_set_style_pad_bottom(bar, 4, 0);
    lv_obj_set_style_bg_color(bar, lv_color_hex(0xF7FAFD), 0);
    lv_obj_set_layout(bar, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(bar, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(bar, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(bar, 2, 0);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *top = lv_obj_create(bar);
    lv_obj_set_size(top, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(top, LV_OPA_0, 0);
    lv_obj_set_style_border_width(top, 0, 0);
    lv_obj_set_style_pad_all(top, 0, 0);
    lv_obj_set_layout(top, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(top, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(top, LV_OBJ_FLAG_SCROLLABLE);

    s_time_label = lv_label_create(top);
    lv_obj_set_style_text_font(s_time_label, &lv_font_montserrat_16, 0);
    lv_obj_add_event_cb(s_time_label, on_time_label_deleted, LV_EVENT_DELETE, RT_NULL);
    update_time_label();

    if (s_time_timer == RT_NULL)
    {
        s_time_timer = lv_timer_create(time_timer_cb, 1000, RT_NULL);
    }

    lv_obj_t *state_wrap = lv_obj_create(top);
    lv_obj_set_size(state_wrap, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(state_wrap, LV_OPA_0, 0);
    lv_obj_set_style_border_width(state_wrap, 0, 0);
    lv_obj_set_style_pad_all(state_wrap, 0, 0);
    lv_obj_set_style_pad_column(state_wrap, 6, 0);
    lv_obj_set_layout(state_wrap, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(state_wrap, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(state_wrap, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(state_wrap, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *wifi_label = lv_label_create(state_wrap);
    lv_label_set_text(wifi_label, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_font(wifi_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(wifi_label, lv_palette_main(LV_PALETTE_BLUE), 0);

    lv_obj_t *bt_label = lv_label_create(state_wrap);
    lv_label_set_text(bt_label, LV_SYMBOL_BLUETOOTH);
    lv_obj_set_style_text_font(bt_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(bt_label, lv_palette_main(LV_PALETTE_INDIGO), 0);

    lv_obj_t *battery_icon = lv_label_create(state_wrap);
    lv_label_set_text(battery_icon, LV_SYMBOL_BATTERY_3);
    lv_obj_set_style_text_font(battery_icon, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(battery_icon, lv_palette_main(LV_PALETTE_GREEN), 0);

    lv_obj_t *battery_text = lv_label_create(state_wrap);
    lv_label_set_text(battery_text, TOPBAR_BATTERY_TEXT);
    lv_obj_set_style_text_font(battery_text, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(battery_text, lv_palette_darken(LV_PALETTE_GREY, 2), 0);

    lv_obj_t *title_label = lv_label_create(bar);
    lv_label_set_text(title_label, title);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(title_label, lv_palette_darken(LV_PALETTE_BLUE, 3), 0);

    return bar;
}

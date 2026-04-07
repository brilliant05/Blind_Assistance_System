#include "page_owner_info.h"

#include <lvgl.h>

#include "../ui_router.h"

static void on_back_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_router_show_home();
}

static lv_obj_t *create_info_row(lv_obj_t *parent, const char *key, const char *value)
{
    lv_obj_t *row = lv_obj_create(parent);
    lv_obj_set_size(row, LV_PCT(100), 58);
    lv_obj_set_style_radius(row, 10, 0);
    lv_obj_set_style_border_width(row, 1, 0);
    lv_obj_set_style_border_color(row, lv_palette_lighten(LV_PALETTE_GREY, 2), 0);
    lv_obj_set_style_pad_all(row, 8, 0);
    lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *k = lv_label_create(row);
    lv_label_set_text(k, key);
    lv_obj_set_style_text_color(k, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    lv_obj_align(k, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *v = lv_label_create(row);
    lv_label_set_text(v, value);
    lv_obj_set_style_text_font(v, &lv_font_montserrat_16, 0);
    lv_obj_align(v, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    return row;
}

lv_obj_t *page_owner_info_create(lv_obj_t *parent)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(page, lv_color_hex(0xF4F7FB), 0);
    lv_obj_set_style_pad_all(page, 12, 0);
    lv_obj_set_style_pad_row(page, 10, 0);
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "Owner Profile");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);

    lv_obj_t *hint = lv_label_create(page);
    lv_label_set_text(hint, "Static demo values, replace with backend data later");
    lv_obj_set_style_text_color(hint, lv_palette_darken(LV_PALETTE_GREY, 1), 0);

    create_info_row(page, "Name", "Zhang San");
    create_info_row(page, "Age", "65");
    create_info_row(page, "Emergency Contact", "Li Si 138-0000-0000");
    create_info_row(page, "Device ID", "E84-DEV-0001");
    create_info_row(page, "Last Location", "N31.2304, E121.4737");

    lv_obj_t *back_btn = lv_button_create(page);
    lv_obj_set_size(back_btn, LV_PCT(100), 48);
    lv_obj_set_style_radius(back_btn, 12, 0);
    lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, 0);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Back To Home");
    lv_obj_center(back_label);

    return page;
}

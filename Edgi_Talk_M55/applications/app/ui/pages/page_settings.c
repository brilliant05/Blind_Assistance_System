#include "page_settings.h"

#include <lvgl.h>

#include "../ui_router.h"

static void anim_translate_y_cb(void *obj, int32_t v)
{
    lv_obj_set_style_translate_y((lv_obj_t *)obj, v, 0);
}

static void play_entry_anim(lv_obj_t *obj, uint32_t delay)
{
    lv_anim_t a;

    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 20, 0);
    lv_anim_set_time(&a, 260);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, anim_translate_y_cb);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_start(&a);
}

static void on_back_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_router_show_home();
}

static lv_obj_t *create_setting_card(lv_obj_t *parent, const char *title, const char *subtitle, bool enabled)
{
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, LV_PCT(100), 78);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_pad_all(card, 10, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_palette_lighten(LV_PALETTE_GREY, 2), 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title_label = lv_label_create(card);
    lv_label_set_text(title_label, title);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_16, 0);
    lv_obj_align(title_label, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *subtitle_label = lv_label_create(card);
    lv_label_set_text(subtitle_label, subtitle);
    lv_obj_set_style_text_color(subtitle_label, lv_palette_darken(LV_PALETTE_GREY, 1), 0);
    lv_obj_align(subtitle_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    lv_obj_t *sw = lv_switch_create(card);
    lv_obj_align(sw, LV_ALIGN_RIGHT_MID, 0, 0);
    if (enabled)
    {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    }

    return card;
}

lv_obj_t *page_settings_create(lv_obj_t *parent)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_pad_all(page, 12, 0);
    lv_obj_set_style_pad_row(page, 10, 0);
    lv_obj_set_style_bg_color(page, lv_color_hex(0xF4F7FB), 0);
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "Settings");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);

    lv_obj_t *hint = lv_label_create(page);
    lv_label_set_text(hint, "Connectivity and location collaboration");
    lv_obj_set_style_text_color(hint, lv_palette_darken(LV_PALETTE_GREY, 1), 0);

    lv_obj_t *wifi_card = create_setting_card(page, "Wi-Fi", "Enable cloud sync and upload", true);
    lv_obj_t *bt_card = create_setting_card(page, "Bluetooth", "Connect to phone for location", true);
    lv_obj_t *loc_card = create_setting_card(page, "Phone Location", "Use phone GPS as location source", true);

    lv_obj_t *back_btn = lv_button_create(page);
    lv_obj_set_size(back_btn, LV_PCT(100), 48);
    lv_obj_set_style_radius(back_btn, 12, 0);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0x0A8FDB), 0);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0x066AA4), LV_STATE_PRESSED);
    lv_obj_clear_state(back_btn, LV_STATE_DISABLED);
    lv_obj_add_flag(back_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, 0);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Back To Home");
    lv_obj_set_style_text_color(back_label, lv_color_white(), 0);
    lv_obj_center(back_label);

    play_entry_anim(wifi_card, 30);
    play_entry_anim(bt_card, 90);
    play_entry_anim(loc_card, 150);
    play_entry_anim(back_btn, 210);

    return page;
}

#include "page_home.h"

#include <lvgl.h>
#include <stdlib.h>
#include <string.h>

#include "../ui_router.h"
#include "../widgets/w_status_bar.h"

typedef enum
{
    CARD_STATE_OK = 0,
    CARD_STATE_WARN,
    CARD_STATE_RISK
} card_state_t;

static void on_action_clicked(lv_event_t *e)
{
    const char *btn_text = (const char *)lv_event_get_user_data(e);

    if (btn_text != 0 && strcmp(btn_text, "SelfTest") == 0)
    {
        ui_router_show_self_test();
    }
    else if (btn_text != 0 && strcmp(btn_text, "Owner") == 0)
    {
        ui_router_show_owner_info();
    }
    else if (btn_text != 0 && strcmp(btn_text, "Settings") == 0)
    {
        ui_router_show_settings();
    }
}

static lv_obj_t *create_status_card(lv_obj_t *parent, const char *name, const char *value)
{
    card_state_t state = CARD_STATE_OK;
    lv_color_t accent = lv_palette_main(LV_PALETTE_GREEN);
    lv_color_t bg = lv_palette_lighten(LV_PALETTE_GREEN, 5);

    if (strcmp(name, "Network") == 0 && strcmp(value, "Online") != 0)
    {
        state = CARD_STATE_RISK;
    }
    else if (strcmp(name, "Battery") == 0)
    {
        int battery = atoi(value);
        if (battery <= 20)
        {
            state = CARD_STATE_RISK;
        }
        else if (battery <= 40)
        {
            state = CARD_STATE_WARN;
        }
    }

    if (state == CARD_STATE_WARN)
    {
        accent = lv_palette_main(LV_PALETTE_ORANGE);
        bg = lv_palette_lighten(LV_PALETTE_ORANGE, 5);
    }
    else if (state == CARD_STATE_RISK)
    {
        accent = lv_palette_main(LV_PALETTE_RED);
        bg = lv_palette_lighten(LV_PALETTE_RED, 5);
    }

    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, LV_PCT(48), 92);
    lv_obj_set_style_radius(card, 12, 0);
    lv_obj_set_style_pad_all(card, 10, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_palette_lighten(LV_PALETTE_GREY, 2), 0);
    lv_obj_set_style_bg_color(card, bg, 0);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *dot = lv_obj_create(card);
    lv_obj_set_size(dot, 10, 10);
    lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(dot, 0, 0);
    lv_obj_set_style_bg_color(dot, accent, 0);
    lv_obj_align(dot, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_t *name_label = lv_label_create(card);
    lv_label_set_text(name_label, name);
    lv_obj_set_style_text_color(name_label, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    lv_obj_align(name_label, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *value_label = lv_label_create(card);
    lv_label_set_text(value_label, value);
    lv_obj_set_style_text_font(value_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(value_label, lv_palette_darken(LV_PALETTE_GREY, 4), 0);
    lv_obj_align(value_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);

    return card;
}

static lv_obj_t *create_action_btn(lv_obj_t *parent, const char *icon, const char *text)
{
    lv_obj_t *btn = lv_button_create(parent);
    lv_obj_set_size(btn, LV_PCT(32), 60);
    lv_obj_set_style_radius(btn, 12, 0);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x0A8FDB), 0);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x066AA4), LV_STATE_PRESSED);
    lv_obj_set_style_pad_all(btn, 4, 0);

    lv_obj_t *icon_label = lv_label_create(btn);
    lv_label_set_text(icon_label, icon);
    lv_obj_set_style_text_color(icon_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(icon_label, &lv_font_montserrat_16, 0);
    lv_obj_align(icon_label, LV_ALIGN_TOP_MID, 0, 4);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -2);

    lv_obj_add_event_cb(btn, on_action_clicked, LV_EVENT_CLICKED, (void *)text);
    return btn;
}

lv_obj_t *page_home_create(lv_obj_t *parent)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_pad_all(page, 0, 0);
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(page, 0, 0);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);

    w_status_bar_create(page, "Blind Assistant");

    lv_obj_t *content = lv_obj_create(page);
    lv_obj_set_width(content, LV_PCT(100));
    lv_obj_set_flex_grow(content, 1);
    lv_obj_set_style_bg_opa(content, LV_OPA_0, 0);
    lv_obj_set_style_border_width(content, 0, 0);
    lv_obj_set_style_pad_top(content, 12, 0);
    lv_obj_set_style_pad_left(content, 12, 0);
    lv_obj_set_style_pad_right(content, 12, 0);
    lv_obj_set_style_pad_bottom(content, 12, 0);
    lv_obj_set_style_pad_row(content, 10, 0);
    lv_obj_set_layout(content, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(content, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(content);
    lv_label_set_text(title, "Device Dashboard");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_22, 0);

    lv_obj_t *subtitle = lv_label_create(content);
    lv_label_set_text(subtitle, "Local-first safety status");
    lv_obj_set_style_text_color(subtitle, lv_palette_darken(LV_PALETTE_GREY, 1), 0);

    lv_obj_t *status_row = lv_obj_create(content);
    lv_obj_set_size(status_row, LV_PCT(100), 102);
    lv_obj_set_style_bg_opa(status_row, LV_OPA_0, 0);
    lv_obj_set_style_border_width(status_row, 0, 0);
    lv_obj_set_style_pad_all(status_row, 0, 0);
    lv_obj_set_style_pad_column(status_row, 8, 0);
    lv_obj_set_layout(status_row, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(status_row, LV_FLEX_FLOW_ROW);
    lv_obj_clear_flag(status_row, LV_OBJ_FLAG_SCROLLABLE);

    create_status_card(status_row, "Network", "Online");
    create_status_card(status_row, "Battery", "78%");

    lv_obj_t *actions = lv_obj_create(content);
    lv_obj_set_size(actions, LV_PCT(100), 72);
    lv_obj_set_style_bg_opa(actions, LV_OPA_0, 0);
    lv_obj_set_style_border_width(actions, 0, 0);
    lv_obj_set_style_pad_all(actions, 0, 0);
    lv_obj_set_style_pad_column(actions, 8, 0);
    lv_obj_set_layout(actions, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(actions, LV_FLEX_FLOW_ROW);
    lv_obj_clear_flag(actions, LV_OBJ_FLAG_SCROLLABLE);

    create_action_btn(actions, LV_SYMBOL_OK, "SelfTest");
    create_action_btn(actions, LV_SYMBOL_HOME, "Owner");
    create_action_btn(actions, LV_SYMBOL_SETTINGS, "Settings");

    lv_obj_t *event_panel = lv_obj_create(content);
    lv_obj_set_size(event_panel, LV_PCT(100), 88);
    lv_obj_set_style_radius(event_panel, 10, 0);
    lv_obj_set_style_pad_all(event_panel, 10, 0);
    lv_obj_clear_flag(event_panel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *event_title = lv_label_create(event_panel);
    lv_label_set_text(event_title, "Latest Event");
    lv_obj_set_style_text_color(event_title, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    lv_obj_align(event_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *event_text = lv_label_create(event_panel);
    lv_label_set_text(event_text, "No active alert. Last self-check: PASS");
    lv_obj_set_style_text_font(event_text, &lv_font_montserrat_16, 0);
    lv_obj_align_to(event_text, event_title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 8);

    lv_obj_t *tip_panel = lv_obj_create(content);
    lv_obj_set_width(tip_panel, LV_PCT(100));
    lv_obj_set_flex_grow(tip_panel, 1);
    lv_obj_set_style_radius(tip_panel, 10, 0);
    lv_obj_set_style_pad_all(tip_panel, 10, 0);
    lv_obj_clear_flag(tip_panel, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *tip_title = lv_label_create(tip_panel);
    lv_label_set_text(tip_title, "Quick Tip");
    lv_obj_set_style_text_color(tip_title, lv_palette_darken(LV_PALETTE_GREY, 2), 0);
    lv_obj_align(tip_title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *tip_text = lv_label_create(tip_panel);
    lv_label_set_text(tip_text, "Press SelfTest to verify sensor/network/audio status.");
    lv_obj_set_style_text_font(tip_text, &lv_font_montserrat_14, 0);
    lv_obj_set_width(tip_text, LV_PCT(100));
    lv_label_set_long_mode(tip_text, LV_LABEL_LONG_WRAP);
    lv_obj_align_to(tip_text, tip_title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 8);

    return page;
}

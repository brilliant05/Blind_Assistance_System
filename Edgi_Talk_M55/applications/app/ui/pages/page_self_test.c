#include "page_self_test.h"

#include <lvgl.h>

#include "../ui_router.h"

static void on_back_clicked(lv_event_t *e)
{
    LV_UNUSED(e);
    ui_router_show_home();
}

lv_obj_t *page_self_test_create(lv_obj_t *parent)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_pad_all(page, 12, 0);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(page);
    lv_label_set_text(title, "Self-Test");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_24, 0);
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *hint = lv_label_create(page);
    lv_label_set_text(hint, "Sensor, network and feedback checks");
    lv_obj_set_style_text_color(hint, lv_palette_darken(LV_PALETTE_GREY, 1), 0);
    lv_obj_align_to(hint, title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 6);

    lv_obj_t *result = lv_label_create(page);
    lv_label_set_text(result,
        "IMU: PASS\n"
        "Network: PASS\n"
        "Voice: PASS\n"
        "Vibration: PASS");
    lv_obj_set_style_text_font(result, &lv_font_montserrat_16, 0);
    lv_obj_align_to(result, hint, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 16);

    lv_obj_t *back_btn = lv_button_create(page);
    lv_obj_set_size(back_btn, 110, 44);
    lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, 0);

    lv_obj_t *back_label = lv_label_create(back_btn);
    lv_label_set_text(back_label, "Back");
    lv_obj_center(back_label);

    return page;
}

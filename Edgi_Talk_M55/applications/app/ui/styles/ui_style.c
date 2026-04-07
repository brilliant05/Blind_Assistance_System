#include "ui_style.h"

#include <lvgl.h>

void ui_style_init(void)
{
    lv_theme_t *theme = lv_theme_default_init(
        lv_display_get_default(),
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_GREY),
        false,
        LV_FONT_DEFAULT);

    lv_display_set_theme(lv_display_get_default(), theme);
}

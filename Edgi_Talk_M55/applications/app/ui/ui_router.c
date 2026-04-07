#include "ui_router.h"

#include <lvgl.h>

#include "pages/page_home.h"
#include "pages/page_owner_info.h"
#include "pages/page_settings.h"
#include "pages/page_self_test.h"

static lv_obj_t *s_current_page = 0;

void ui_router_init(void)
{
    s_current_page = 0;
}

void ui_router_show_home(void)
{
    if (s_current_page != 0)
    {
        lv_obj_del(s_current_page);
        s_current_page = 0;
    }

    s_current_page = page_home_create(lv_screen_active());
}

void ui_router_show_self_test(void)
{
    if (s_current_page != 0)
    {
        lv_obj_del(s_current_page);
        s_current_page = 0;
    }

    s_current_page = page_self_test_create(lv_screen_active());
}

void ui_router_show_settings(void)
{
    if (s_current_page != 0)
    {
        lv_obj_del(s_current_page);
        s_current_page = 0;
    }

    s_current_page = page_settings_create(lv_screen_active());
}

void ui_router_show_owner_info(void)
{
    if (s_current_page != 0)
    {
        lv_obj_del(s_current_page);
        s_current_page = 0;
    }

    s_current_page = page_owner_info_create(lv_screen_active());
}

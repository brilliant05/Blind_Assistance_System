#include "ui_app.h"

#include "styles/ui_style.h"
#include "ui_router.h"

void ui_app_init(void)
{
    ui_style_init();
    ui_router_init();
    ui_router_show_home();
}

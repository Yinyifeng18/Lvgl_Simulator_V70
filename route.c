#include "route.h"
#include "lvgl/src/lv_framework/lvf.h"


#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#include "lvgl/src/lv_view/lv_view_main.h"
#include "lvgl/src/lv_view/lv_view_menu.h"

lvf_route_t lvf_routes[] = {
    {
        .path = "/main",
        .v    = &main_view,
    },
    {
        .path = "/main/menu",
        .v    = &menu_view,
    },
    {
            NULL,
        }
};


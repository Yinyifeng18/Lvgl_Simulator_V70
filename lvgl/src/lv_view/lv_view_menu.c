#include "lv_view_menu.h"
#include <stdio.h>
#include <stdlib.h>

static void menu_created(struct lvf_view_ins *vi);
static void menu_destroyed(struct lvf_view_ins *vi);
static void menu_mounted(struct lvf_view_ins *vi);
static void menu_unmounted(struct lvf_view_ins *vi);
static void menu_before_destroy(struct lvf_view_ins *vi);
static void menu_btn_event_handler(lv_obj_t *obj, lv_event_t event);



/*********************事件****************************/
lvf_view_t menu_view = {
    .created        = menu_created,
    .before_mount   = NULL,
    .mounted        = menu_mounted,
    .unmounted      = menu_unmounted,
    .before_destroy = menu_before_destroy,
    .destroyed      = menu_destroyed,
};


static void menu_created(struct lvf_view_ins *vi)
{
    static lv_style_t style_menu_default;
        lv_style_reset(&style_menu_default);
        lv_style_set_bg_opa(&style_menu_default, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(vi->o, LV_OBJ_PART_MAIN, &style_menu_default);

    lv_obj_t *menu_cont_1 = lv_cont_create(vi->o, NULL);
    lv_obj_set_click(menu_cont_1, false);

    lv_cont_set_fit(menu_cont_1, LV_FIT_NONE);
    lv_obj_set_pos(menu_cont_1, 0, 0);
    lv_obj_set_size(menu_cont_1, 800, 480);

    lv_obj_t * label;

            lv_obj_t * btn1 = lv_btn_create(menu_cont_1, NULL);
            lv_obj_set_event_cb(btn1, menu_btn_event_handler);
            lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

            label = lv_label_create(btn1, NULL);
            lv_label_set_text(label, "456");


}

static void menu_btn_event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (LV_EVENT_CLICKED == event) {
        lvf_router_push("/main", NULL);
    }
}

static void menu_mounted(struct lvf_view_ins *vi)
{
}


static void menu_before_destroy(struct lvf_view_ins *vi)
{
}

static void menu_destroyed(struct lvf_view_ins *vi)
{
}


static void menu_unmounted(struct lvf_view_ins *vi)
{
}


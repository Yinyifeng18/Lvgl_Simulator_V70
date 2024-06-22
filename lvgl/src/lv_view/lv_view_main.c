#include "lv_view_main.h"
#include <stdio.h>
#include <stdlib.h>

static void main_created(struct lvf_view_ins *vi);
static void main_destroyed(struct lvf_view_ins *vi);
static void main_mounted(struct lvf_view_ins *vi);
static void main_unmounted(struct lvf_view_ins *vi);
static void main_before_destroy(struct lvf_view_ins *vi);
static void main_btn_event_handler(lv_obj_t *obj, lv_event_t event);



/*********************事件****************************/
lvf_view_t main_view = {
    .created        = main_created,
    .before_mount   = NULL,
    .mounted        = main_mounted,
    .unmounted      = main_unmounted,
    .before_destroy = main_before_destroy,
    .destroyed      = main_destroyed,
};


static void main_created(struct lvf_view_ins *vi)
{
    static lv_style_t style_main_default;
        lv_style_reset(&style_main_default);
        lv_style_set_bg_opa(&style_main_default, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(vi->o, LV_OBJ_PART_MAIN, &style_main_default);

    lv_obj_t *main_cont_1 = lv_cont_create(vi->o, NULL);
    lv_obj_set_click(main_cont_1, false);

    lv_cont_set_fit(main_cont_1, LV_FIT_NONE);
    lv_obj_set_pos(main_cont_1, 0, 0);
    lv_obj_set_size(main_cont_1, 800, 480);



        lv_obj_t * label;

            lv_obj_t * btn1 = lv_btn_create(main_cont_1, NULL);
            lv_obj_set_event_cb(btn1, main_btn_event_handler);
            lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

            label = lv_label_create(btn1, NULL);
            lv_label_set_text(label, "123");


}

static void main_btn_event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (LV_EVENT_CLICKED == event) {
        lvf_router_push("/main/menu", NULL);
    }
}

static void main_mounted(struct lvf_view_ins *vi)
{
}


static void main_before_destroy(struct lvf_view_ins *vi)
{
}

static void main_destroyed(struct lvf_view_ins *vi)
{
}


static void main_unmounted(struct lvf_view_ins *vi)
{
}


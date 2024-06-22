#ifndef LVF_VIEW_H
#define LVF_VIEW_H


#include "lvgl/lvgl.h"


struct lvf_view;
struct lvf_view_ins;

typedef void (*lvf_view_hook)(struct lvf_view_ins *vi);

typedef struct lvf_view {
    lvf_view_hook created;
    lvf_view_hook before_mount;
    lvf_view_hook mounted;
    lvf_view_hook unmounted;
    lvf_view_hook before_destroy;
    lvf_view_hook destroyed;
} lvf_view_t;

typedef struct lvf_view_ins {
    lv_obj_t *o;
    lvf_view_t *v;
    void *user;

    int mounted;
} lvf_view_ins_t;


void lvf_view_init(void);
lvf_view_ins_t *lvf_view_create(lv_obj_t *c, lvf_view_t *v);
void lvf_view_destroy(lvf_view_ins_t *vi);
void lvf_view_mount(lvf_view_ins_t *vi);
void lvf_view_unmount(lvf_view_ins_t *vi);


#endif /* end of include guard: LVF_VIEW_H */

#ifndef LVF_COVER_H
#define LVF_COVER_H


#include "lvgl/lvgl.h"


struct lvf_cover;
struct lvf_cover_ins;

typedef void (*lvf_cover_hook)(struct lvf_cover_ins *ci);

typedef struct lvf_cover {
    lvf_cover_hook created;
    lvf_cover_hook before_mount;
    lvf_cover_hook mounted;
    lvf_cover_hook unmounted;
    lvf_cover_hook before_destroy;
    lvf_cover_hook destroyed;
} lvf_cover_t;

typedef struct lvf_cover_ins {
    lv_obj_t *o;
    lvf_cover_t *c;
    void *user;

    int mounted;

    unsigned int zindex;
} lvf_cover_ins_t;


void lvf_cover_init(void);
lvf_cover_ins_t *lvf_cover_create(lv_obj_t *cont, lvf_cover_t *c);
void lvf_cover_destroy(lvf_cover_ins_t *ci);
void lvf_cover_mount(lvf_cover_ins_t *ci);
void lvf_cover_unmount(lvf_cover_ins_t *ci);
void lvf_cover_set_zindex(lvf_cover_ins_t *ci, unsigned zindex);
unsigned int lvf_cover_get_zindex(lvf_cover_ins_t *ci);


#endif /* end of include guard: LVF_COVER_H */

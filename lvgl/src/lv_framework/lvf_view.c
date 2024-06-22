#include "lvf_view.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static lv_style_t style_view;

void lvf_view_init(void)
{
    lv_style_init(&style_view);
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
}

lvf_view_ins_t *lvf_view_create(lv_obj_t *c, lvf_view_t *v)
{
    lvf_view_ins_t *vi;
    
    vi = malloc(sizeof(*vi));
    if (NULL == vi) {
        return NULL;
    }
    memset(vi, 0, sizeof(*vi));

    vi->mounted = 0;

    vi->v = malloc(sizeof(*vi->v));
    if (NULL == vi->v) {
        free(vi->v);
        free(vi);
        return NULL;
    }
    memset(vi->v, 0, sizeof(*vi->v));
    vi->v->created        = v->created;
    vi->v->before_mount   = v->before_mount;
    vi->v->mounted        = v->mounted;
    vi->v->unmounted      = v->unmounted;
    vi->v->before_destroy = v->before_destroy;
    vi->v->destroyed      = v->destroyed;

    vi->o = lv_obj_create(c, NULL);
    lv_obj_set_user_data(vi->o, vi);

    lv_obj_reset_style_list(vi->o, LV_OBJ_PART_MAIN);
    lv_obj_add_style(vi->o, LV_OBJ_PART_MAIN, &style_view);
    lv_obj_set_size(vi->o, lv_obj_get_width(c), lv_obj_get_height(c));
    lv_obj_set_click(vi->o, false);
    lv_obj_align(vi->o, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_hidden(vi->o, true);
    lv_obj_set_top(vi->o, false);

    if (vi->v->created) {
        vi->v->created(vi);
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    return vi;
}

void lvf_view_destroy(lvf_view_ins_t *vi)
{
    if (vi->v->before_destroy) {
        vi->v->before_destroy(vi);
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lv_obj_del(vi->o);
    vi->o = NULL;

    if (vi->v->destroyed) {
        vi->v->destroyed(vi);
    }

    free(vi->v);
    free(vi);
}

void lvf_view_mount(lvf_view_ins_t *vi)
{
    if (vi->mounted) {
        return;
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    if (vi->v->before_mount) {
        vi->v->before_mount(vi);
    }

    lv_obj_set_hidden(vi->o, false);
    vi->mounted = 1;

    if (vi->v->mounted) {
        vi->v->mounted(vi);
    }
}

void lvf_view_unmount(lvf_view_ins_t *vi)
{
    if (!vi->mounted) {
        return;
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lv_obj_set_hidden(vi->o, true);
    vi->mounted = 0;

    if (vi->v->unmounted) {
        vi->v->unmounted(vi);
    }
}

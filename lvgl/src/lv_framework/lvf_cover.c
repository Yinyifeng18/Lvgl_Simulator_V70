#include "lvf_cover.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lv_core/lv_debug.h"

#define LV_OBJX_NAME "lvf_cover"


static lv_style_t style_cover;
static lv_signal_cb_t ancestor_signal;

static lv_res_t lvf_cover_signal(lv_obj_t * co, lv_signal_t sign, void * param);
static lv_style_list_t * lvf_cover_get_style(lv_obj_t * cont, uint8_t type);

void lvf_cover_init(void)
{
    lv_style_init(&style_cover);
}

lvf_cover_ins_t *lvf_cover_create(lv_obj_t *cont, lvf_cover_t *c)
{
    lvf_cover_ins_t *ci;
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    ci = malloc(sizeof(*ci));
    if (NULL == ci) {
        return NULL;
    }
    memset(ci, 0, sizeof(*ci));

    ci->mounted = 0;

    ci->c = malloc(sizeof(*ci->c));
    if (NULL == ci->c) {
        free(ci->c);
        free(ci);
        return NULL;
    }
    memset(ci->c, 0, sizeof(*ci->c));
    ci->c->created        = c->created;
    ci->c->before_mount   = c->before_mount;
    ci->c->mounted        = c->mounted;
    ci->c->unmounted      = c->unmounted;
    ci->c->before_destroy = c->before_destroy;
    ci->c->destroyed      = c->destroyed;

    ci->o = lv_obj_create(cont, NULL);
    lv_obj_set_user_data(ci->o, ci);

    if(ancestor_signal == NULL) ancestor_signal = lv_obj_get_signal_cb(ci->o);
    lv_obj_set_signal_cb(ci->o, lvf_cover_signal);

    lv_obj_reset_style_list(ci->o, LV_OBJ_PART_MAIN);
    lv_obj_add_style(ci->o, LV_OBJ_PART_MAIN, &style_cover);
    lv_obj_set_size(ci->o, lv_obj_get_width(cont), lv_obj_get_height(cont));
    lv_obj_set_click(ci->o, false);
    lv_obj_align(ci->o, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_hidden(ci->o, true);
    lv_obj_set_top(ci->o, false);

    ci->zindex = 0;

    lv_obj_move_background(ci->o);

    if (ci->c->created) {
        ci->c->created(ci);
    }

    return ci;
}

void lvf_cover_destroy(lvf_cover_ins_t *ci)
{
    if (ci->c->before_destroy) {
        ci->c->before_destroy(ci);
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lv_obj_del(ci->o);
    ci->o = NULL;

    if (ci->c->destroyed) {
        ci->c->destroyed(ci);
    }

    free(ci->c);
    free(ci);
}

void lvf_cover_mount(lvf_cover_ins_t *ci)
{
    if (ci->mounted) {
        return;
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    if (ci->c->before_mount) {
        ci->c->before_mount(ci);
    }

    lv_obj_set_hidden(ci->o, false);
    ci->mounted = 1;

    if (ci->c->mounted) {
        ci->c->mounted(ci);
    }
}

void lvf_cover_unmount(lvf_cover_ins_t *ci)
{
    if (!ci->mounted) {
        return;
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lv_obj_set_hidden(ci->o, true);
    ci->mounted = 0;

    if (ci->c->unmounted) {
        ci->c->unmounted(ci);
    }
}

void lvf_cover_set_zindex(lvf_cover_ins_t *ci, unsigned zindex)
{
    ci->zindex = zindex;

    LV_ASSERT_OBJ(ci->o, LV_OBJX_NAME);

    lv_obj_t * parent = lv_obj_get_parent(ci->o);

    /*Do nothing of already in the background*/
    if(_lv_ll_get_tail(&parent->child_ll) == ci->o) return;

    lv_obj_invalidate(parent);

    _lv_ll_chg_list(&parent->child_ll, &parent->child_ll, ci->o, false);

    /*Notify the new parent about the child*/
    parent->signal_cb(parent, LV_SIGNAL_CHILD_CHG, ci->o);

    lv_obj_invalidate(parent);
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
}

unsigned int lvf_cover_get_zindex(lvf_cover_ins_t *ci)
{
    return ci->zindex;
}

static lv_res_t lvf_cover_signal(lv_obj_t * co, lv_signal_t sign, void * param)
{
    if(sign == LV_SIGNAL_GET_STYLE) {
        lv_get_style_info_t * info = param;
        info->result = lvf_cover_get_style(co, info->part);
        if(info->result != NULL) return LV_RES_OK;
        else return ancestor_signal(co, sign, param);
    }

    lv_res_t res;

    res = ancestor_signal(co, sign, param);
    if(res != LV_RES_OK) return res;
    if(sign == LV_SIGNAL_GET_TYPE) return lv_obj_handle_get_type_signal(param, LV_OBJX_NAME);
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    return res;
}

static lv_style_list_t * lvf_cover_get_style(lv_obj_t * co, uint8_t type)
{
    lv_style_list_t * style_dsc_p;
    switch(type) {
        case LV_CONT_PART_MAIN:
            style_dsc_p = &co->style_list;
            break;
        default:
            style_dsc_p = NULL;
    }
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    return style_dsc_p;
}

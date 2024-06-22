#include "lvf_router.h"
#include "lvf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define bool	_Bool
#define true	1
#define false	0

static int routing = false;

static lvf_route_info_t route_info = {
    .op        = LVF_ROUTER_OP_NONE,
    .cur_path  = NULL,
    .last_path = NULL,
    .param     = NULL,
};

typedef struct history_node {
    struct history_node *next;
    char *path;
    lvf_view_ins_t *vi;
} history_node_t;

static history_node_t history = { NULL };

static void async_destroy_view(void *vi);

void lvf_router_init(void)
{
  printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
}

lvf_route_info_t *lvf_router_get_route_info(void)
{
    return &route_info;
}

int lvf_router_push(char *path, void *param)
{
    if (true == routing) {
        return -1;
    }

    routing = true;

    lvf_view_t *v = NULL;
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lvf_route_t *route = lvf_routes;
    while (route->path) {
        if (0 == strcmp(path, route->path)) {
            v = route->v;
        printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
            break;
        }
        route++;
    }

    if (NULL == v) {
        routing = false;
        return -1;
    }

    history_node_t *cur = history.next;
    history_node_t *new = malloc(sizeof(*new));
    if (NULL == new) {
        routing = false;
        return -1;
    }
    memset(new, 0, sizeof(*new));

    if (cur) {
      printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
      lvf_view_unmount(cur->vi);
    }

    route_info.op        = LVF_ROUTER_OP_PUSH;
    route_info.cur_path  = path;
    if (cur) {
        route_info.last_path = cur->path;
    } else {
        route_info.last_path = NULL;
    }
    route_info.param     = param;

    lvf_view_ins_t *vi = lvf_view_create(lv_scr_act(), v);
    if (NULL == vi) {
        printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
        free(new);
        routing = false;
        return -1;
    }

    lvf_view_mount(vi);

    route_info.param = NULL;

    new->path    = path;
    new->vi      = vi;
    new->next    = cur;
    history.next = new;

    routing = false;

    return 0;
}

int lvf_router_back(void *param)
{
    if (true == routing) {
        return -1;
    }

    routing = true;
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    history_node_t *cur = history.next;

    if (NULL == cur) {
        routing = false;
        return 0;
    }

    history_node_t *new = cur->next;

    lvf_view_unmount(cur->vi);
    lv_async_call(async_destroy_view, cur->vi);

    route_info.op = LVF_ROUTER_OP_BACK;
    if (new) {
        route_info.cur_path = new->path;
    } else {
        route_info.cur_path = NULL;
    }
    route_info.last_path = cur->path;
    route_info.param     = param;

    if (new) {
        lvf_view_mount(new->vi);
    }

    route_info.param = NULL;

    history.next = cur->next;

    free(cur);

    routing = false;

    return 0;
}

int lvf_router_replace(char *path, void *param)
{
    if (true == routing) {
        return -1;
    }

    routing = true;
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lvf_view_t *v = NULL;

    lvf_route_t *route = lvf_routes;
    while (route->path) {
        if (0 == strcmp(path, route->path)) {
            printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
            v = route->v;
            break;
        }
        route++;
    }

    if (NULL == v) {
        routing = false;
        return -1;
    }

    history_node_t *new = malloc(sizeof(*new));
    if (NULL == new)  {
        routing = false;
        return -1;
    }
    memset(new, 0, sizeof(*new));

    history_node_t *cur = history.next;

    if (cur) {
        printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
        history.next = cur->next;
        lvf_view_unmount(cur->vi);
        lv_async_call(async_destroy_view, cur->vi);
    }

    route_info.op = LVF_ROUTER_OP_REPLACE;
    route_info.cur_path = path;
    if (cur) {
        route_info.last_path = cur->path;
    } else {
        route_info.last_path = NULL;
    }
    route_info.param     = param;

    free(cur);
    cur = NULL;

    lvf_view_ins_t *vi = lvf_view_create(lv_scr_act(), v);
    if (NULL == vi) {
        printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
        free(new);
        routing = false;
        return -1;
    }

    lvf_view_mount(vi);

    route_info.param = NULL;

    new->path    = path;
    new->vi      = vi;
    new->next    = history.next;
    history.next = new;

    routing = false;

    return 0;
}

int lvf_router_replace_all(char *path, void *param)
{
    if (true == routing) {
        return -1;
    }

    routing = true;

    lvf_view_t *v = NULL;
    printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
    lvf_route_t *route = lvf_routes;
    while (route->path) {
        if (0 == strcmp(path, route->path)) {
            v = route->v;
            break;
        }
        route++;
    }

    if (NULL == v) {
        routing = false;
        return -1;
    }

    history_node_t *new = malloc(sizeof(*new));
    if (NULL == new)  {
        routing = false;
        return -1;
    }
    memset(new, 0, sizeof(*new));

    char *last_path = NULL;
    history_node_t *cur = history.next;
    if (cur) {
        last_path = cur->path;
    }

    history_node_t *node = cur;
    cur = NULL;
    while (node) {
        history_node_t *next = node->next;
        lvf_view_unmount(node->vi);
        lv_async_call(async_destroy_view, node->vi);
        free(node);
        node = next;
    }
    history.next = NULL;

    route_info.op        = LVF_ROUTER_OP_REPLACE;
    route_info.cur_path  = path;
    route_info.last_path = last_path;
    route_info.param     = param;

    lvf_view_ins_t *vi = lvf_view_create(lv_scr_act(), v);
    if (NULL == vi) {
        free(new);
        routing = false;
        return -1;
    }

    lvf_view_mount(vi);

    route_info.param = NULL;

    new->path    = path;
    new->vi      = vi;
    new->next    = history.next;
    history.next = new;

    routing = false;

    return 0;
}

static void async_destroy_view(void *vi)
{
	lvf_view_destroy((lvf_view_ins_t *)vi);
  printf("==>: FILE[%s] FUNC[%s] LINE[%d]!\n", __FILE__, __FUNCTION__, __LINE__);
}

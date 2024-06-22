#ifndef LVF_ROUTER_H
#define LVF_ROUTER_H


#include "lvf_view.h"


typedef enum lvf_router_op {
    LVF_ROUTER_OP_NONE = 0,
    LVF_ROUTER_OP_PUSH,
    LVF_ROUTER_OP_BACK,
    LVF_ROUTER_OP_REPLACE,
    LVF_ROUTER_OP_REPLACE_ALL,
} lvf_router_op_e;

typedef struct lvf_route_info {
    lvf_router_op_e op;
    char *cur_path;
    char *last_path;
    void *param;
} lvf_route_info_t;

typedef struct lvf_route {
    char *path;
    lvf_view_t *v;
} lvf_route_t;

extern lvf_route_t lvf_routes[];

void lvf_router_init(void);

lvf_route_info_t *lvf_router_get_route_info(void);
int lvf_router_push(char *path, void *param);
int lvf_router_back(void *param);
int lvf_router_replace(char *path, void *param);
int lvf_router_replace_all(char *path, void *param);


#endif /* end of include guard: LVF_ROUTER_H */

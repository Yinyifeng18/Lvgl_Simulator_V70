# Lvgl_Simulator_V70
 LVGL页面管理器
增加了framework层，只适用于7.0版本
1、初始化
lvf_init();
lvf_router_replace_all("/main", NULL);
2、切换
lvf_router_push("/main", NULL);

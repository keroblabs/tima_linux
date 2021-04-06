#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "bitmap_draw_class.h"
#include "sections.h"

////////////////////////////////////////////////////////////////////

#ifdef CREATE_CLASS
#undef CREATE_CLASS
#endif
#define CREATE_CLASS(t)        CREATE_CLASS_EX(t, api_##t##_class)

#ifdef CREATE_CLASS_EX
#undef CREATE_CLASS_EX
#endif
#define CREATE_CLASS_EX(t,api) \
    static api_##t _local_api_##t##_class; \
    static void class_##t##_global_init( void ) { \
    api = &_local_api_##t##_class; \
    api->creator_bitmap = creator_bitmap; \
    api->delete_bitmap = delete_bitmap; \
    api->fill_box = fill_box; \
    api->draw_line = draw_line; \
    api->draw_rectangle = draw_rectangle; \
    api->draw_circle = draw_circle; \
    api->draw_circle_arc = draw_circle_arc; \
    api->flood_fill = flood_fill; \
    api->set_bitmap_rgb = set_bitmap_rgb; \
    api->get_bitmap_rgb = get_bitmap_rgb; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_PRIVATE_H

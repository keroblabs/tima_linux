#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "bitmap_class.h"
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
    api->from_driver = from_driver; \
    api->claim = claim; \
    api->release = release; \
    api->clear = clear; \
    api->get_width = get_width; \
    api->get_height = get_height; \
    api->get_pixel = get_pixel; \
    api->set_pixel = set_pixel; \
    api->set_pixel_index = set_pixel_index; \
    api->get_buffer = get_buffer; \
    api->get_frame = get_frame; \
    api->copy_bitmap = copy_bitmap; \
    api->draw_1bbp = draw_1bbp; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_PRIVATE_H

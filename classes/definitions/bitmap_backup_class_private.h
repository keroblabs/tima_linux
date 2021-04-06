#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "bitmap_backup_class.h"
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
    api->create_backup = create_backup; \
    api->delete_backup = delete_backup; \
    api->reset = reset; \
    api->apply_to = apply_to; \
    api->apply = apply; \
    api->draw_1bbp_collect_from = draw_1bbp_collect_from; \
    api->draw_1bbp_collect = draw_1bbp_collect; \
    api->draw_1bbp_merge = draw_1bbp_merge; \
    api->set_pixel = set_pixel; \
    api->set_pixel_index = set_pixel_index; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_PRIVATE_H

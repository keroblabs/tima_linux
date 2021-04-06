#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "lcd_driver_class.h"
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
    api->creator = creator; \
    api->get_width = get_width; \
    api->get_height = get_height; \
    api->get_pixel = get_pixel; \
    api->set_pixel = set_pixel; \
    api->get_buffer = get_buffer; \
    api->release = release; \
    api->process = process; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_PRIVATE_H

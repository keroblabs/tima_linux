#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_TIMER_DRIVER_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_TIMER_DRIVER_CLASS_H

////////////////////////////////////////////////////////////////////

#include "timer_driver_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_timer_driver_class_t
{
    CREATOR void ( * creator )( timer_driver_class_t * _data_timer_driver_class_t );
    METHOD uint32_t ( * get_ms )( timer_driver_class_t * _data_timer_driver_class_t );
    METHOD uint64_t ( * get_us )( timer_driver_class_t * _data_timer_driver_class_t );
} api_timer_driver_class_t;

////////////////////////////////////////////////////////////////////

extern api_timer_driver_class_t * api_timer_driver_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_timer_driver_class_t( void );
void * _instance_new_timer_driver_class_t_ex( void * api_timer_driver_class_t_class );
void * _instance_static_timer_driver_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_TIMER_DRIVER_CLASS_H

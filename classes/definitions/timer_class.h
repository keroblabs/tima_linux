#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_TIMER_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_TIMER_CLASS_H

////////////////////////////////////////////////////////////////////

#include "timer_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_timer_class_t
{
    CREATOR void ( * creator )( timer_class_t * _data_timer_class_t, uint32_t period );
    METHOD void ( * start )( timer_class_t * _data_timer_class_t, uint32_t period );
    METHOD void ( * reload )( timer_class_t * _data_timer_class_t );
    METHOD void ( * stop )( timer_class_t * _data_timer_class_t );
    METHOD void ( * expire )( timer_class_t * _data_timer_class_t );
    METHOD bool_t ( * check )( timer_class_t * _data_timer_class_t );
    METHOD uint32_t ( * get_counter )( timer_class_t * _data_timer_class_t );
} api_timer_class_t;

////////////////////////////////////////////////////////////////////

extern api_timer_class_t * api_timer_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_timer_class_t( uint32_t period );
void * _instance_new_timer_class_t_ex( void * api_timer_class_t_class, uint32_t period );
void * _instance_static_timer_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_TIMER_CLASS_H

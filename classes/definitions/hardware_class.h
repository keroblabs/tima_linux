#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_HARDWARE_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_HARDWARE_CLASS_H

////////////////////////////////////////////////////////////////////

#include "hardware_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_hardware_class_t
{
    CREATOR void ( * creator )( hardware_class_t * _data_hardware_class_t );
    METHOD timer_driver_class_t * ( * get_timer_driver )( hardware_class_t * _data_hardware_class_t );
    METHOD adc_driver_class_t * ( * get_adc_driver )( hardware_class_t * _data_hardware_class_t, uint8_t index );
    METHOD lcd_driver_class_t * ( * get_lcd_driver )( hardware_class_t * _data_hardware_class_t );
    STATIC CLASS(hardware_class_t) * ( * get_class )( void );
    STATIC void ( * init )( void );
} api_hardware_class_t;

////////////////////////////////////////////////////////////////////

extern api_hardware_class_t * api_hardware_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_hardware_class_t( void );
void * _instance_new_hardware_class_t_ex( void * api_hardware_class_t_class );
void * _instance_static_hardware_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_HARDWARE_CLASS_H

#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_ADC_DRIVER_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_ADC_DRIVER_CLASS_H

////////////////////////////////////////////////////////////////////

#include "adc_driver_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_adc_driver_class_t
{
    CREATOR void ( * init )( adc_driver_class_t * _data_adc_driver_class_t, uint8_t index );
    METHOD void ( * start )( adc_driver_class_t * _data_adc_driver_class_t );
    METHOD bool_t ( * is_ready )( adc_driver_class_t * _data_adc_driver_class_t );
    METHOD uint16_t ( * read )( adc_driver_class_t * _data_adc_driver_class_t );
} api_adc_driver_class_t;

////////////////////////////////////////////////////////////////////

extern api_adc_driver_class_t * api_adc_driver_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_adc_driver_class_t( uint8_t index );
void * _instance_new_adc_driver_class_t_ex( void * api_adc_driver_class_t_class, uint8_t index );
void * _instance_static_adc_driver_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_ADC_DRIVER_CLASS_H

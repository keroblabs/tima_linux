#ifndef hardware_class_definition_h
#define hardware_class_definition_h

////////////////////////////////////////////////////////////////////////

#include "lcd_driver_class.h"
#include "timer_driver_class.h"
#include "adc_driver_class.h"

////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 1

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

typedef CLASS(hardware_class_t)
{
    CLASS_DATA * p_data;
    
    CREATOR void ( *creator )( void );
    METHOD timer_driver_class_t * ( *get_timer_driver )( void );
    METHOD adc_driver_class_t * ( *get_adc_driver )( uint8_t index );
    METHOD lcd_driver_class_t * ( *get_lcd_driver )( void );
    STATIC CLASS(hardware_class_t) * ( *get_class )( void );
    STATIC void ( *init )( void );
    
} hardware_class_t;

////////////////////////////////////////////////////////////////////////

hardware_class_t * hardware_get_class( void );

////////////////////////////////////////////////////////////////////////

#endif /* hardware_class_definition_h */

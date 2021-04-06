#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_H

////////////////////////////////////////////////////////////////////

#include "lcd_driver_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_lcd_driver_class_t
{
    CREATOR void ( * creator )( lcd_driver_class_t * _data_lcd_driver_class_t );
    METHOD uint16_t ( * get_width )( lcd_driver_class_t * _data_lcd_driver_class_t );
    METHOD uint16_t ( * get_height )( lcd_driver_class_t * _data_lcd_driver_class_t );
    METHOD uint32_t ( * get_pixel )( lcd_driver_class_t * _data_lcd_driver_class_t, uint16_t posx, uint16_t posy );
    METHOD void ( * set_pixel )( lcd_driver_class_t * _data_lcd_driver_class_t, uint16_t posx, uint16_t posy, uint32_t pixel );
    METHOD void * ( * get_buffer )( lcd_driver_class_t * _data_lcd_driver_class_t );
    METHOD void ( * release )( lcd_driver_class_t * _data_lcd_driver_class_t );
    METHOD void ( * process )( lcd_driver_class_t * _data_lcd_driver_class_t );
} api_lcd_driver_class_t;

////////////////////////////////////////////////////////////////////

extern api_lcd_driver_class_t * api_lcd_driver_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_lcd_driver_class_t( void );
void * _instance_new_lcd_driver_class_t_ex( void * api_lcd_driver_class_t_class );
void * _instance_static_lcd_driver_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_DRIVERS_LCD_DRIVER_CLASS_H

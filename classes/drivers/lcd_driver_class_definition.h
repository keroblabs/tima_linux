#ifndef BOARD_LCD_DRIVER_H_
#define BOARD_LCD_DRIVER_H_

////////////////////////////////////////////////////////////////////////////////////////

#include "class_framework.h"

////////////////////////////////////////////////////////////////////////////////////////

#define FRAME_PERIOD        15

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES       1

////////////////////////////////////////////////////////////////////////////////////////

typedef CLASS(lcd_driver_class_t)
{
    CLASS_DATA_VOID;

    uint16_t width;
    uint16_t height;
    void * buffer;
    
    CREATOR void ( *creator )( void );
    METHOD uint16_t ( *get_width )( void );
    METHOD uint16_t ( *get_height )( void );
    METHOD uint32_t ( *get_pixel )( uint16_t posx, uint16_t posy );
    METHOD void     ( *set_pixel )( uint16_t posx, uint16_t posy, uint32_t pixel );
    METHOD void * ( *get_buffer )( void );
    METHOD void   ( *release )( void );
    METHOD void   ( *process )( void );
} lcd_driver_class_t;

/*
uint16_t lcd_driver_width( void );

uint16_t lcd_driver_height( void );

void * lcd_driver_get_buffer( void );

void lcd_driver_release_frame( void );

int lcd_driver_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz );

int lcd_driver_init( void );

void lcd_driver_process( void );
*/

////////////////////////////////////////////////////////////////////////////////////////

#endif /* BOARD_LCD_DRIVER_H_ */

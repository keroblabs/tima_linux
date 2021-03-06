#ifndef BOARD_LCD_DRIVER_H_
#define BOARD_LCD_DRIVER_H_

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

#define FRAME_PERIOD        15

////////////////////////////////////////////////////////////////////////////////////////

uint16_t lcd_driver_width( void );

uint16_t lcd_driver_height( void );

void * lcd_driver_get_buffer( void );

void lcd_driver_release_frame( void );

int lcd_driver_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz );

int lcd_driver_init( void );
int lcd_driver_mouse_init( const char * dev );

void lcd_driver_process( void );

void lcd_driver_flip_frame( uint8_t frame);

////////////////////////////////////////////////////////////////////////////////////////

#endif /* BOARD_LCD_DRIVER_H_ */

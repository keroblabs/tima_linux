#ifndef __lcd_layer_h__
#define __lcd_layer_h__

///////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////

typedef struct _lcd_driver_api_t
{
	uint16_t width;
	uint16_t height;

	void ( *init )( void );
	void ( *clear_lcd )( void );
	void ( *finish )( void );
	void ( *update )( void );
	bool_t ( *ready )( void );

	void ( *set_contrast)( uint8_t value );
	void ( *set_backlight)( bool_t state );

	uint16_t * ( *get_buffer )( void );

	uint16_t ( *get_pixel )( uint16_t posx, uint16_t posy );

	void ( *set_pixel )( uint16_t posx, uint16_t posy, uint16_t colour );
	void ( *set_bitmap_rgb )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, uint16_t * data, int transparent );
	void ( *get_bitmap_rgb )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, uint16_t * data );
	void ( *set_fill_box )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, uint16_t colour );

	int ( *input_ts )( uint16_t * posx, uint16_t * posy, uint16_t * posz );

} lcd_driver_api_t;

///////////////////////////////////////////////////////////////

// extern lcd_driver_t * lcd_driver;

///////////////////////////////////////////////////////////////

lcd_driver_api_t * lcd_layer_get_driver( void );

///////////////////////////////////////////////////////////////

#endif // __lcd_layer_h__

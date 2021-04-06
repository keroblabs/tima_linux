#include "system.h"
#include "SDL_screen.h"
#include "lcd_driver_class_private.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static void creator( lcd_driver_class_t * driver )
{
    sdl_lcd_init();
    driver->width = _USE_SCREEN_WIDTH;
    driver->height = _USE_SCREEN_HEIGHT;
    driver->buffer = sdl_get_buffer();
}

static uint16_t get_width( lcd_driver_class_t * driver )
{
    return driver->width;
}

static uint16_t get_height( lcd_driver_class_t * driver )
{
    return driver->height;
}

static void * get_buffer( lcd_driver_class_t * driver )
{
    return driver->buffer;
}

static void set_pixel( lcd_driver_class_t * driver, uint16_t posx, uint16_t posy, uint32_t colour )
{
    uint32_t index;

#if LCD_PIXEL_SIZE==32
    uint32_t * buffer = ( uint32_t * )driver->buffer;
#elif LCD_PIXEL_SIZE==16
    uint16_t * buffer = ( uint16_t * )driver->buffer;
#else
#error "Unknown pixel configuration"
#endif

    index = ((uint32_t)posy * driver->width) + (uint32_t)posx;
    buffer[index] = colour;
}

static uint32_t get_pixel( lcd_driver_class_t * driver, uint16_t posx, uint16_t posy )
{
    uint32_t index;
    
#if LCD_PIXEL_SIZE==32
    uint32_t * buffer = ( uint32_t * )driver->buffer;
#elif LCD_PIXEL_SIZE==16
    uint16_t * buffer = ( uint16_t * )driver->buffer;
#else
#error "Unknown pixel configuration"
#endif
    
    index = ((uint32_t)posy * driver->width) + (uint32_t)posx;
    return buffer[index];
}

static void release( lcd_driver_class_t * driver )
{
}

static void process( lcd_driver_class_t * driver )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS(lcd_driver_class_t);

uint16_t lcd_driver_width( void )
{
    return _USE_SCREEN_WIDTH;
}

uint16_t lcd_driver_height( void )
{
    return _USE_SCREEN_HEIGHT;
}

void * lcd_driver_get_buffer( void )
{
    return sdl_get_buffer();
}

void lcd_driver_release_frame( void )
{
}

int lcd_driver_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
    return 0;
}

int lcd_driver_init( void )
{
    sdl_lcd_init();
    return 0;
}

void lcd_driver_process( void )
{
}


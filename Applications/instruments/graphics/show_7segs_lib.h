#ifndef _segs_lib_h
#define _segs_lib_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "graphics.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef struct digits_data_t_
{
    uint16_t posx;
    uint16_t posy;
    
    uint8_t num_digits;

    pixel_t colour;
    
    graphics_backup_t * backup;
    
} digits_data_t;

////////////////////////////////////////////////////////////////////////////////////////

uint16_t show_7seg_draw_digits( void * p_lcd, uint16_t posx, uint16_t posy, char * value, pixel_t colour, void * data, graphics_backup_t * backup );

void show_7segs_small_digits( void * p_lcd, uint16_t posx, uint16_t posy, uint16_t value, char * str_unit, pixel_t colour, graphics_backup_t * backup );

void show_7segs_digits_create_data( digits_data_t * data, uint16_t posx, uint16_t posy, uint8_t num_digits, pixel_t colour );
uint16_t show_7seg_collect_backup( void * p_lcd, uint16_t posx, uint16_t posy, uint8_t num_digits, void * data, graphics_backup_t * backup );

void show_7segs_large_digits_show( void * p_lcd, digits_data_t * data, uint16_t value );
void show_7segs_large_digits_collect_backup( void * p_lcd, digits_data_t * data );

bitmap_t * show_7seg_create_bitmap( pixel_t back_colour );

void show_7segs_small_digits_fraction( void * p_lcd, uint16_t posx, uint16_t posy, uint32_t value, uint32_t div, pixel_t colour, pixel_t back_colour );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* _segs_lib_h */

#ifndef _DRAW_H
#define _DRAW_H

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "graphics.h"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct _font_data_t
{
	uint16_t width;
	uint16_t height;
	uint16_t offset;
	uint16_t size;

	const uint8_t * data;

} font_data_t;

//////////////////////////////////////////////////////////////////////////////////////

enum
{
	FONT_4x6,
	FONT_5x12,
	FONT_6x8,
	FONT_8x8,
	FONT_10x18,
	FONT_12x16,
};

//////////////////////////////////////////////////////////////////////////////////////

extern const font_data_t font_12x16;
extern const font_data_t font_8x8;

//////////////////////////////////////////////////////////////////////////////////////

void draw_font_init( uint8_t index );

void draw_line( bitmap_t * curr_driver, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, pixel_t colour );
void draw_text( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, pixel_t back_colour );

void draw_text_ex( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, graphics_backup_t * backup );

void draw_text_vertical( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, pixel_t back_colour );

void draw_rectangle( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );

uint32_t draw_get_text_height( char * text );
uint32_t draw_get_text_width( char * text );

void draw_circle( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, int ratio, pixel_t colour, graphics_backup_t * backup );
void draw_circle_arc( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour );

int draw_text_printk( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char *fmt, ... );

void draw_line_backup( bitmap_t * curr_driver, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, pixel_t colour, graphics_backup_t * backup );

//////////////////////////////////////////////////////////////////////////////////////

#endif

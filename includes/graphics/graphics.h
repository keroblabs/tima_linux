#ifndef __graphics_h__
#define __graphics_h__

///////////////////////////////////////////////////////////////

#include "types.h"
#include "lcd_driver.h"

///////////////////////////////////////////////////////////////

typedef uint32_t pixel_t;

///////////////////////////////////////////////////////////////

typedef struct
{
	pixel_t * buffer;

    uint16_t width;
    uint16_t height;

    pixel_t background_colour;

} bitmap_t;

typedef struct _lcd_pixel_t
{
    uint32_t index;
    pixel_t pixel;
    
} lcd_pixel_t;

typedef struct graphics_backup_t_
{
    lcd_pixel_t * pixels;
    uint32_t max_size;
    uint32_t curr_size;
    uint32_t limit_size;
    
} graphics_backup_t;

///////////////////////////////////////////////////////////////

bitmap_t * graphics_init( void );

void * graphics_claim( void );
void graphics_release( void );

void graphics_set_landscape( void );
void graphics_set_portrait( void );
void graphics_init_auto_vsync( void );

void graphics_clear_screen( bitmap_t * curr_driver );

bool_t graphics_driver_ready( void );

void graphics_process( void );

pixel_t graphics_get_pixel( bitmap_t * curr_driver, uint16_t posx, uint16_t posy );

void graphics_show_bitmap( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap, bool_t use_transparent );
void graphics_set_pixel( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, pixel_t colour );
void graphics_show_bitmap_raw( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data );
void graphics_show_bitmap_bitblt( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap );

void graphics_set_bitmap_rgb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height,
						      pixel_t * data, pixel_t transparent, bool_t use_transparent );

void graphics_get_bitmap_rgb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data );

void graphics_fill_box( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );

void graphics_copy_bitmap( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap );

int graphics_read_ts( uint16_t * posx, uint16_t * posy, uint16_t * posz );

pixel_t * graphics_get_target( bitmap_t * curr_driver );

uint16_t graphics_width( bitmap_t * curr_driver );
uint16_t graphics_height( bitmap_t * curr_driver );

void graphics_bitmap_1bb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
					      uint8_t *input, pixel_t back_colour, pixel_t fore_colour );

void graphics_bitmap_1bb_ex( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
                                 uint8_t *input, pixel_t fore_colour, graphics_backup_t * backup );
void graphics_bitmap_1bb_ex_backup_merge( bool_t is_skip, uint16_t width, uint16_t heigth, uint8_t *input, pixel_t fore_colour, 
                                 graphics_backup_t * backup, graphics_backup_t * output );
void graphics_bitmap_1bb_ex_collect_backup( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
                                 uint8_t *input, graphics_backup_t * backup );

graphics_backup_t * graphics_backup_create( uint32_t max_size );
void graphics_set_pixel_backup( bitmap_t * curr_driver, graphics_backup_t * backup, uint16_t posx, uint16_t posy, pixel_t colour );
void graphics_set_pixel_index_backup( bitmap_t * curr_driver, graphics_backup_t * backup, uint32_t index, pixel_t colour );
void graphics_restore_backup( bitmap_t * curr_driver, graphics_backup_t * backup );
void graphics_reset_backup( graphics_backup_t * backup );
void graphics_destroy_backup( graphics_backup_t * backup );

///////////////////////////////////////////////////////////////

#endif // __graphics_h__

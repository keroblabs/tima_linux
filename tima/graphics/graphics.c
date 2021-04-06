#include "system.h"
#include "graphics.h"
#include "timer.h"

#include "debug.h"

///////////////////////////////////////////////////////////////

enum
{
    LCD_MODE_DISABLED,
    LCD_MODE_API,
    LCD_MODE_FRAMEBUFFER,
};

enum
{
    LCD_VIEW_LANDSCAPE,
    LCD_VIEW_PORTRAIT,
};

///////////////////////////////////////////////////////////////

#define POST_FLIP_INITIAL_SIZE          10000
#define POST_FLIP_ADDITIONAL_SIZE       5000

///////////////////////////////////////////////////////////////

static bool_t lcd_ready = FALSE;
static uint8_t lcd_mode;
static bitmap_t lcd_buffer;
static void * gr_mutex;

///////////////////////////////////////////////////////////////

static void graphics_add_backup( graphics_backup_t * backup, uint32_t index, pixel_t colour )
{
    if( backup && backup->curr_size < backup->max_size )
    {
        backup->pixels[backup->curr_size].pixel = colour;
        backup->pixels[backup->curr_size].index = index;
        backup->curr_size++;

        if( backup->curr_size == backup->max_size )
        {
            lcd_pixel_t * new_pixels = ( lcd_pixel_t * )malloc( sizeof( lcd_pixel_t ) * ( backup->max_size + POST_FLIP_ADDITIONAL_SIZE ) );
            if( new_pixels != NULL )
            {
                memcpy( new_pixels, backup->pixels, sizeof( lcd_pixel_t ) * backup->max_size );
                backup->max_size += POST_FLIP_ADDITIONAL_SIZE;
                free( backup->pixels );
                backup->pixels = new_pixels;
            }
        }
    }    
}

bitmap_t * graphics_init( void )
{
    lcd_mode = LCD_MODE_DISABLED;

    lcd_ready = FALSE;

	if( lcd_driver_init() < 0 )
	{
		//DEBUG_PRINTK( "LCD failed\r\n" );
		return NULL;
	}

#if 0
	curr_driver = &lcd_driver;

    curr_driver->width = lcd_driver_width();
    curr_driver->height = lcd_driver_height();
    curr_driver->buffer = lcd_driver_get_buffer();
#endif
    
    lcd_buffer.width = lcd_driver_width();
    lcd_buffer.height = lcd_driver_height();
    lcd_buffer.buffer = lcd_driver_get_buffer();
    graphics_clear_screen( &lcd_buffer );

    lcd_ready = TRUE;
    gr_mutex = tthread_mutex_init();

    return &lcd_buffer;
}

bool_t graphics_driver_ready( void )
{
	return TRUE;
}

void * graphics_claim( void )
{
    tthread_mutex_lock( gr_mutex );
    lcd_buffer.buffer  = lcd_driver_get_buffer();
    return &lcd_buffer;
}

void graphics_release( void )
{
    lcd_driver_release_frame();
    tthread_mutex_unlock( gr_mutex );
}

void graphics_process( void )
{
    tthread_mutex_lock( gr_mutex );
    lcd_driver_process();
    tthread_mutex_unlock( gr_mutex );
}

pixel_t * graphics_get_target( bitmap_t * curr_driver )
{
	if( !lcd_ready ) return NULL;
    return curr_driver->buffer;
}

uint16_t graphics_width( bitmap_t * curr_driver )
{
	if( !lcd_ready ) return 0;
    return curr_driver->width;
}

uint16_t graphics_height( bitmap_t * curr_driver )
{
	if( !lcd_ready ) return 0;
    return curr_driver->height;
}

void graphics_clear_screen( bitmap_t * curr_driver )
{
    graphics_fill_box(curr_driver, 0, 0, curr_driver->width, curr_driver->height, 0);
}

void graphics_set_pixel( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, pixel_t colour )
{
	uint32_t index;

	if( !lcd_ready ) return;
	if( posx >= curr_driver->width ) return;
	if( posy >= curr_driver->height ) return;

	index = ((uint32_t)posy * curr_driver->width) + (uint32_t)posx;

	curr_driver->buffer[index] = colour;
}

pixel_t graphics_get_pixel( bitmap_t * curr_driver, uint16_t posx, uint16_t posy )
{
	uint32_t index;

	if( !lcd_ready ) return 0;
    if( posx >= curr_driver->width ) return 0;
    if( posy >= curr_driver->height ) return 0;
    
	index = ((uint32_t)posy * curr_driver->width) + (uint32_t)posx;

	return curr_driver->buffer[index];
}

void graphics_copy_bitmap( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap )
{
	pixel_t * lcd_buffer_margin = curr_driver->buffer;
	uint16_t width;
	uint16_t height;
	pixel_t * data;

	if( !lcd_ready ) return;

	lcd_buffer_margin += ( uint32_t )( posy * curr_driver->width );
	lcd_buffer_margin += ( uint32_t )( posx );

	width = bitmap->width;
	height = bitmap->height;
	data = bitmap->buffer;

	while( height-- )
	{
        memcpy( lcd_buffer_margin, data, width * sizeof( pixel_t ) );
		lcd_buffer_margin += curr_driver->width;
		data += ( width );
	}
}

void graphics_get_frame( bitmap_t * curr_driver, bitmap_t * bitmap, uint16_t posx, uint16_t posy )
{
    uint16_t width = bitmap->width;
    uint16_t height = bitmap->height;
    pixel_t * lcd_buffer_margin = curr_driver->buffer;
    pixel_t * data = bitmap->buffer;

    lcd_buffer_margin += ( uint32_t )( posy * curr_driver->width );
    lcd_buffer_margin += ( uint32_t )( posx );

    while( height-- )
    {
        memcpy( data, lcd_buffer_margin, sizeof( pixel_t ) * width );

        lcd_buffer_margin += curr_driver->width;
        data += width;
    }
}

void graphics_show_bitmap_raw( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data )
{
    pixel_t * lcd_buffer_margin = curr_driver->buffer;
    
    if( !lcd_ready ) return;
    
    lcd_buffer_margin += ( uint32_t )( posy * curr_driver->width );
    lcd_buffer_margin += ( uint32_t )( posx );
    
    while( height-- )
    {
        memcpy( lcd_buffer_margin, data, width * sizeof( pixel_t ) );
        lcd_buffer_margin += curr_driver->width;
        data += ( width );
    }
}

void graphics_show_bitmap( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap, bool_t use_transparent )
{
	if( !lcd_ready ) return;
    if( bitmap == NULL ) return;
    
	graphics_set_bitmap_rgb( curr_driver, posx, posy, bitmap->width, bitmap->height, bitmap->buffer, bitmap->background_colour, use_transparent );
}

void graphics_show_bitmap_bitblt( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const bitmap_t * bitmap )
{
    pixel_t * lcd_buffer_margin = curr_driver->buffer;
    uint16_t width = bitmap->width;
    uint16_t height = bitmap->height;
    pixel_t * data = bitmap->buffer;
    
    if( !lcd_ready ) return;
    
    lcd_buffer_margin += ( uint32_t )( posy * curr_driver->width );
    lcd_buffer_margin += ( uint32_t )( posx );
    
    while( height-- )
    {
        memcpy( lcd_buffer_margin, data, sizeof( pixel_t ) * width );
        
        lcd_buffer_margin += curr_driver->width;
        data += width;
    }
}

void graphics_set_bitmap_rgb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height,
									pixel_t * data, pixel_t transparent, bool_t is_transparent )
{
	pixel_t * lcd_buffer_margin;
	uint16_t counter;
	uint32_t index;

	if( !lcd_ready ) return;

	index = ( uint32_t )( posy * curr_driver->width ) + posx;
	lcd_buffer_margin = &curr_driver->buffer[ index ];

	while( height-- )
	{
        for( counter = 0; counter < width; counter++ )
        {
            if( ( data[ counter ] != transparent ) || ( is_transparent == FALSE ) )
            {
                lcd_buffer_margin[ counter ] = data[ counter ];
            }
        }

        lcd_buffer_margin += curr_driver->width;
		data += width;
	}
}

void graphics_get_bitmap_rgb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data )
{
	uint16_t x,y,i;
	pixel_t * p_pixel;
	pixel_t * d_pixel;
	uint32_t index;

	if( !lcd_ready ) return;
	if( posx >= lcd_driver_width() ) return;
	if( posy >= lcd_driver_height() ) return;

	p_pixel = curr_driver->buffer;

	for( i = y = 0; y < height; y++ )
	{
		if( ( y + posy ) >= curr_driver->height ) break;

		index = ((uint32_t)(posy+y) * curr_driver->width) + (uint32_t)posx;
		d_pixel = &p_pixel[index];

		for( x = 0; x < width; x++ )
		{
			if( ( x + posx ) < curr_driver->width )
			{
				data[i] = d_pixel[x];
			}

			i++;
		}
	}
}

void graphics_fill_box( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
	uint16_t x,y;
	pixel_t * d_pixel;
	uint32_t index;

	if( !lcd_ready ) return;
	if( posx >= curr_driver->width ) return;
	if( posy >= curr_driver->height ) return;

	if( ( posx + width ) > curr_driver->width ) width = curr_driver->width - posx;
    if( ( posy + height ) > curr_driver->height ) height = curr_driver->height - posy;

    index = ((uint32_t)(posy+y) * curr_driver->width) + (uint32_t)posx;
    d_pixel = &curr_driver->buffer[index];

    for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
		    d_pixel[x] = colour;
		}

		d_pixel += curr_driver->width;
	}
}

int graphics_read_ts( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
	return 0;
}

void graphics_bitmap_1bb( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
					      uint8_t *input, pixel_t back_colour, pixel_t fore_colour )
{
	uint16_t x;
	uint16_t y;
	uint16_t bit_mask;
	uint32_t index;
	uint8_t * ptr_pixel;

	if( !lcd_ready ) return;
	index = ( posy * curr_driver->width ) + posx;

	for( y = 0; y < heigth; y++ )
	{
		if( y > curr_driver->height ) break;

		ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
		bit_mask = 0x01 << ( y & 0x07 );
		
		for( x = 0; x < width; x++ )
		{
			if( x > curr_driver->width ) break;

			if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
			{
				curr_driver->buffer[index+x] = fore_colour;

			}
			else
			{
				curr_driver->buffer[index+x] = back_colour;
			}		
		}

		index += curr_driver->width;
	}
}

void graphics_bitmap_1bb_ex_backup_merge( bool_t is_skip, uint16_t width, uint16_t heigth, uint8_t *input, pixel_t fore_colour, 
                                 graphics_backup_t * backup, graphics_backup_t * output )
{
    uint16_t x;
    uint16_t y;
    uint32_t backup_index;
    uint16_t bit_mask;
    uint8_t * ptr_pixel;

    if( !lcd_ready || ( backup == NULL ) || ( output == NULL ) ) return;

    uint32_t first_index = output->curr_size;

    for( y = 0; y < heigth; y++ )
    {
        ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
        bit_mask = 0x01 << ( y & 0x07 );

        for( x = 0; x < width; x++ )
        {
            if( output->curr_size < output->max_size )
            {
                if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
                {
                    output->pixels[output->curr_size].pixel = ( is_skip == FALSE ) ? fore_colour : backup->pixels[output->curr_size].pixel;
                    output->pixels[output->curr_size].index = backup->pixels[output->curr_size].index;
                    output->curr_size++;
                }
            }
        }
    }
}

void graphics_bitmap_1bb_ex_collect_backup( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
                                 uint8_t *input, graphics_backup_t * backup )
{
    uint16_t x;
    uint16_t y;
    uint16_t bit_mask;
    uint32_t index;
    uint8_t * ptr_pixel;

    if( !lcd_ready || ( backup == NULL ) ) return;

    index = ( posy * curr_driver->width ) + posx;

    for( y = 0; y < heigth; y++ )
    {
        ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
        bit_mask = 0x01 << ( y & 0x07 );

        for( x = 0; x < width; x++ )
        {
            if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
            {
                graphics_add_backup( backup, index+x, curr_driver->buffer[index+x] );
            }
        }

        index += curr_driver->width;
    }
}

void graphics_bitmap_1bb_ex( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth,
		    			         uint8_t *input, pixel_t fore_colour, graphics_backup_t * backup )
{
	uint16_t x;
	uint16_t y;
	uint16_t bit_mask;
	uint32_t index;
	uint8_t * ptr_pixel;

	if( !lcd_ready ) return;

	index = ( posy * curr_driver->width ) + posx;

	for( y = 0; y < heigth; y++ )
	{
		if( y > curr_driver->height ) break;

		ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
		bit_mask = 0x01 << ( y & 0x07 );

		for( x = 0; x < width; x++ )
		{
			if( x > curr_driver->width ) break;

			if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
			{
                graphics_set_pixel_index_backup( curr_driver, backup, index+x, fore_colour );
			}
		}

		index += curr_driver->width;
	}
}

graphics_backup_t * graphics_backup_create( uint32_t max_size )
{
    graphics_backup_t * ret = ( graphics_backup_t * )malloc( sizeof( graphics_backup_t ) );
    if( ret == NULL ) return NULL;
    
    ret->pixels = ( lcd_pixel_t * )malloc( sizeof( lcd_pixel_t ) * max_size );
    if( ret->pixels == NULL )
    {
        free( ret );
        return NULL;
    }

    ret->max_size = max_size;
    ret->curr_size = 0;
    ret->limit_size = 0;

    return ret;
}

void graphics_destroy_backup( graphics_backup_t * backup )
{
    free( backup->pixels );
    free( backup );
}

void graphics_set_pixel_backup( bitmap_t * curr_driver, graphics_backup_t * backup, uint16_t posx, uint16_t posy, pixel_t colour )
{
    uint32_t index = ((uint32_t)posy * curr_driver->width) + (uint32_t)posx;
    graphics_set_pixel_index_backup( curr_driver, backup, index, colour );
}

void graphics_set_pixel_index_backup( bitmap_t * curr_driver, graphics_backup_t * backup, uint32_t index, pixel_t colour )
{
    graphics_add_backup( backup, index, curr_driver->buffer[index] );
    curr_driver->buffer[index] = colour;
}

void graphics_restore_backup( bitmap_t * curr_driver, graphics_backup_t * backup )
{
    if( backup == NULL ) return;
    
    if( backup->curr_size > backup->limit_size )
    {
        backup->limit_size = backup->curr_size;
    }
    
    while( backup->curr_size )
    {
        backup->curr_size--;
        curr_driver->buffer[backup->pixels[backup->curr_size].index] = backup->pixels[backup->curr_size].pixel;
    }
}

void graphics_reset_backup( graphics_backup_t * backup )
{
    backup->curr_size = 0;
}

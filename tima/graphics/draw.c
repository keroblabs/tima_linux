#include "draw.h"
#include "tima_libc.h"
#include "graphics.h"
#include "t_threads.h"
#include "tima_libc.h"

/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////

static font_data_t * p_selected_font = NULL;
//static void * bitmap;

/////////////////////////////////////////////////////////////////////////////////////////

static void gr_draw_character(	bitmap_t * curr_driver,
								uint8_t character,
								uint16_t posx, uint16_t posy, 
								pixel_t fore_colour, pixel_t back_colour )
{
    uint32_t index;
    
	index = ( character - p_selected_font->offset ) * ( p_selected_font->size );
	graphics_bitmap_1bb(curr_driver, posx, posy,
						p_selected_font->width, p_selected_font->height,
						( uint8_t * )&p_selected_font->data[index], back_colour, fore_colour);
}

void draw_font_init( uint8_t index )
{
	switch( index )
	{
		case FONT_8x8:
			p_selected_font = ( font_data_t * )&font_8x8;
			break;

		case FONT_12x16:
			p_selected_font = ( font_data_t * )&font_12x16;
			break;

		default:
			p_selected_font = NULL;
	}
}

void draw_circle_arc( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour )
{
	int i, x, y;
	int ix = ( int )posx, iy = ( int )posy;

	for( i = start; i < end; i++ )
	{
		x = cos_table( (i*4096)/360 ) * ratio / 32768;
		y = sin_table( (i*4096)/360 ) * ratio / 32768;

		graphics_set_pixel( curr_driver, ix + x, iy - y, colour );
		//draw_line( curr_driver, posx, posy, ix + x, iy - y, colour );
	}
}

void draw_circle( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, int ratio, pixel_t colour, graphics_backup_t * backup )
{
    int i, x, y;
    int ix = ( int )posx, iy = ( int )posy;
    int prev_x, prev_y;
    
    for( i = 0; i < 360; i++ )
    {
        x = cos_table( (i*4096)/360 ) * ratio / 32768;
        y = sin_table( (i*4096)/360 ) * ratio / 32768;
        
        if( i > 0 )
        {
            draw_line( curr_driver, prev_x, prev_y, ix + x, iy - y, colour );
        }

        prev_x = ix + x;
        prev_y = iy - y;

        //graphics_set_pixel_backup( curr_driver, backup, ix + x, iy - y, colour );
        // draw_line( curr_driver, posx, posy, ix + x, iy - y, colour );
    }
}

void draw_rectangle( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
    draw_line( curr_driver, posx, posy, posx+width, posy, colour );
    draw_line( curr_driver, posx, posy+height, posx+width, posy+height, colour );
    
    draw_line( curr_driver, posx, posy, posx, posy+height, colour );
    draw_line( curr_driver, posx+width, posy, posx+width, posy+height, colour );
}

void draw_line( bitmap_t * curr_driver, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, pixel_t colour )
{
    draw_line_backup( curr_driver, x1, y1, x2, y2, colour, NULL );
}

void draw_line_backup( bitmap_t * curr_driver, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, pixel_t colour, graphics_backup_t * backup )
{
    // draw function
    int x,y,end,inc=0,p;
    int dx=( int )x2-( int )x1;
    int dy=( int )y2-( int )y1;
    int c=0,current=0;

    // last_x = x2;
    // last_y = y2;

    if( dx < 0 ) dx = -dx;
    if( dy < 0 ) dy = -dy;

     if(dx>dy)
     {
         p=2*dy-dx;
          if(x1<x2)
          {
               x=x1;y=y1;end=x2;
               if(y1<y2)inc=1;
               if(y1>y2)inc=-1;
          }
          else
          {
               x=x2;y=y2;end=x1;
               if(y2<y1)inc=1;
              if(y2>y1)inc=-1;
          }
          while(x<=end)
          {
              //lcd_set_pixel(x,y,colour);
			  //graphics_set_pixel( curr_driver, x, y, colour );
              graphics_set_pixel_backup( curr_driver, backup, x, y, colour );

              if(p<0) p=p+2*dy;
              else
              {
                  y=y+inc;p=p+2*(dy-dx);
               }
              x++;
              if(current==0&&c==10)
              {
                  current=1;c=-1;
              }
             if(current==1&&c==6)
              {
                  current=0;c=-1;
             }
             c++;
          }
     }
     else
    {
        p=2*dx-dy;
        if(y1<y2)
        {
            y=y1;x=x1;end=y2;
            if(x1<x2)inc=1;
            if(x1>x2)inc=-1;
        }
        else
        {
            y=y2;x=x2;end=y1;
            if(x2<x1)inc=1;
            if(x2>x1)inc=-1;
        }
        while(y<=end)
        {
            //lcd_set_pixel(x,y,colour);
            //graphics_set_pixel( curr_driver, x, y, colour );
            graphics_set_pixel_backup( curr_driver, backup, x, y, colour );

            if(p<0)p=p+2*dx;
            else
            {
                 x=x+inc;p=p+2*(dx-dy);
            }
            y++;
            if(current==0&&c==10)
            {
                current=1;c=-1;
            }
            if(current==1&&c==6)
            {
                current=0;c=-1;
            }
            c++;
        }
    }
}

#ifndef USE_4D_DISPLAY
void draw_text( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, pixel_t back_colour )
{
	uint32_t i;
	uint16_t x, y;
    //uint32_t index;

	if( p_selected_font == NULL ) return;

	x = posx;
	y = posy;

	for( i = 0; i < strlen( text ); i++ )
	{
		if( text[i] == 0x0a )
		{
			y += p_selected_font->height;
		}
		else if( text[i] == 0x0D )
		{
			x = 0;
		}
		else
		{
			gr_draw_character( curr_driver, ( uint8_t )text[i], x, y, fore_colour, back_colour );
			x += p_selected_font->width;
		}
	}
}

void draw_text_ex( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, graphics_backup_t * backup )
{
	uint32_t i;
	uint16_t x, y;
    uint32_t index;

	if( p_selected_font == NULL ) return;

	x = posx;
	y = posy;

	for( i = 0; i < strlen( text ); i++ )
	{
		if( text[i] == 0x0a )
		{
			y += p_selected_font->height;
		}
		else if( text[i] == 0x0D )
		{
			x = 0;
		}
		else
		{
			//gr_draw_character_ex( ( uint8_t )text[i], x, y, fore_colour );

			index = ( ( uint8_t )text[i] - p_selected_font->offset ) * ( p_selected_font->size );
			graphics_bitmap_1bb_ex( curr_driver, x, y, p_selected_font->width, p_selected_font->height,
					     			    	( uint8_t * )&p_selected_font->data[index], fore_colour, backup );

			x += p_selected_font->width;
		}
	}
}
#else
void draw_text( uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, pixel_t back_colour )
{
	void hw_lcd_set_pixel( uint16_t x, uint16_t y, pixel_t colour );
	void hw_lcd_4d_set_pos( uint16_t posx, pixel_t posy );
	void hw_lcd_4d_show_char( char char_out );
	void hw_lcd_4d_init_text( void );

	static bool_t is_init_4d = FALSE;

	uint32_t i;
	uint16_t x, y;

	if( is_init_4d == FALSE )
	{
		if( graphics_driver_ready() )
		{
			hw_lcd_4d_init_text();
			is_init_4d = TRUE;
		}
	}

	hw_lcd_4d_set_pos( posy >> 3, posx >> 3 );

	x = posx;
	y = posy;

	for( i = 0; i < strlen( text ); i++ )
	{
		if( text[i] == 0x0a )
		{
			y++;
			hw_lcd_4d_set_pos( x >> 3, y >> 3 );
		}
		else if( text[i] == 0x0D )
		{
			x = 0;
			hw_lcd_4d_set_pos( x >> 3, y >> 3 );
		}
		else
		{
			hw_lcd_4d_show_char( text[i] );
			x++;
		}
	}
}
#endif

int draw_text_printk( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char *fmt, ... )
{
#if 0
    va_list args;
    int printed_len;

    /* Emit the output into the temporary buffer */
    va_start(args, fmt);
    printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args);
    va_end(args);

    draw_text( posx, posy, vsf_printk_buf, APP_RGB(255,255,255), APP_RGB(0,0,0) );
    return printed_len;
#endif
    return 0;
}

void draw_text_vertical( bitmap_t * curr_driver, uint16_t posx, uint16_t posy, const char * text, pixel_t fore_colour, pixel_t back_colour )
{
	uint32_t i;
	uint16_t x, y;

	if( p_selected_font == NULL ) return;
    
	x = posx;
	y = posy;
    
	for( i = 0; i < strlen( text ); i++ )
	{
		if( text[i] == 0x0a )
		{
		}
		else if( text[i] == 0x0D )
		{
		}
		else
		{
			gr_draw_character( curr_driver, ( uint8_t )text[i], x, y, fore_colour, back_colour );
			y += p_selected_font->height;
		}
	}
}

uint32_t draw_get_text_height( char * text )
{
	uint32_t i;
	uint32_t len;

	if( p_selected_font == NULL ) return 0;
	
	len = 0;

	for( i = 0; i < strlen( text ); i++ )
	{
		if( len == 0 ) len = p_selected_font->width;

		if( text[i] == 0x0a )
		{
			len += p_selected_font->width;
		}
	}

	return len;
}

uint32_t draw_get_text_width( char * text )
{
	uint32_t i;
	uint32_t len;
	uint32_t max_len;

	if( p_selected_font == NULL ) return 0;

	len = 0;
	max_len = 0;

	for( i = 0; i < strlen( text ); i++ )
	{
		if( text[i] == 0x0D )
		{
			if( max_len < len ) max_len = len;
			len = 0;
		}
		else
		{
			len += p_selected_font->width;
		}
	}

	if( max_len < len ) max_len = len;
	return max_len;
}


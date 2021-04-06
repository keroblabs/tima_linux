#include "bitmap_draw_class_private.h"
#include "tima_libc.h"

////////////////////////////////////////////////////////////////////

typedef struct _flood_data_t
{
    pixel_t colour;
    bitmap_class_t * curr_driver;
    
} flood_data_t;

////////////////////////////////////////////////////////////////////

static void _fill_right( uint32_t index, flood_data_t * data )
{
    if(data->curr_driver->buffer[index] != data->colour)
    {
        data->curr_driver->set_pixel_index( index, data->colour );
        
        _fill_right( index+1, data );
        _fill_right( index-data->curr_driver->width, data );
        _fill_right( index+data->curr_driver->width, data );
    }
}

static void _fill_left( uint32_t index, flood_data_t * data )
{
    if(data->curr_driver->buffer[index] != data->colour)
    {
        data->curr_driver->set_pixel_index( index, data->colour );
        
        _fill_left( index-1, data );
        _fill_left( index-data->curr_driver->width, data );
        _fill_left( index+data->curr_driver->width, data );
    }
}

////////////////////////////////////////////////////////////////////

CREATOR static void creator_bitmap( bitmap_draw_class_t * p_data, bitmap_class_t * bitmap_class )
{
    p_data->bitmap_class = bitmap_class;
}

DELETE static void delete_bitmap( bitmap_draw_class_t * p_data )
{
}

METHOD static void fill_box( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
    bitmap_class_t * curr_driver = p_data->bitmap_class;
    uint16_t x,y,i;
    uint32_t index;
    
    if( posx >= curr_driver->width ) return;
    if( posy >= curr_driver->height ) return;
    
    index = ((uint32_t)(posy * curr_driver->width) + (uint32_t)posx);
    
    for( i = y = 0; y < height; y++ )
    {
        if( ( y + posy ) >= curr_driver->height ) break;
        
        for( x = 0; x < width; x++ )
        {
            if( ( x + posx ) < curr_driver->width )
            {
                curr_driver->set_pixel_index( index + x, colour );
            }
            
            i++;
        }
        
        index += curr_driver->width;
    }
}

METHOD static void draw_line( bitmap_draw_class_t * p_data, uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour )
{
    int x, y, end, inc = 0, p;
    int dx = ( int )posx2 - ( int )posx1;
    int dy = ( int )posy2 - ( int )posy1;
    int c = 0, current = 0;

    if( dx < 0 ) dx = -dx;
    if( dy < 0 ) dy = -dy;
    
    if( dx > dy )
    {
        p = 2*dy - dx;
        if( posx1 < posx2 )
        {
            x = posx1; y = posy1; end = posx2;
            if( posy1 < posy2 ) inc = 1;
            if( posy1 > posy2 ) inc = -1;
        }
        else
        {
            x = posx2; y = posy2; end = posx1;
            if( posy2 < posy1 ) inc = 1;
            if( posy2 > posy1 ) inc = -1;
        }
        while( x <= end )
        {
            p_data->bitmap_class->set_pixel( x, y, colour );
            
            if( p < 0 ) { p = p + 2*dy; }
            else { y = y + inc; p = p + 2 * ( dy - dx ); }
            x++;
            if( current == 0 && c == 10 ) { current = 1; c = -1; }
            if( current == 1 && c == 6 )  { current = 0; c = -1; }
            c++;
        }
    }
    else
    {
        p = 2*dx - dy;
        if( posy1 < posy2 )
        {
            y = posy1; x = posx1; end = posy2;
            if( posx1 < posx2 ) inc = 1;
            if( posx1 > posx2 ) inc = -1;
        }
        else
        {
            y = posy2; x = posx2; end = posy1;
            if( posx2 < posx1 ) inc = 1;
            if( posx2 > posx1 ) inc = -1;
        }
        while( y <= end )
        {
            p_data->bitmap_class->set_pixel( x, y, colour );
            
            if( p < 0 ) p = p + 2*dx;
            else { x = x + inc; p = p + 2*(dx-dy); }
            y++;
            if( current == 0 && c == 10 ) { current = 1; c = -1; }
            if( current == 1 && c == 6 )  { current = 0; c = -1; }
            c++;
        }
    }
}

METHOD static void draw_rectangle( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
    draw_line( p_data, posx, posy, posx+width, posy, colour );
    draw_line( p_data, posx, posy+height, posx+width, posy+height, colour );
    
    draw_line( p_data, posx, posy, posx, posy+height, colour );
    draw_line( p_data, posx+width, posy, posx+width, posy+height, colour );
}

METHOD static void draw_circle( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, int ratio, pixel_t colour )
{
    int i, x, y;
    int ix = ( int )posx, iy = ( int )posy;
    int prev_x = 0, prev_y = 0;
    
    for( i = 0; i < 360; i++ )
    {
        x = cos_table( (i*4096)/360 ) * ratio / 32768;
        y = sin_table( (i*4096)/360 ) * ratio / 32768;
        
        if( i > 0 )
        {
            draw_line( p_data, prev_x, prev_y, ix + x, iy - y, colour );
        }
        
        prev_x = ix + x;
        prev_y = iy - y;
    }
}

METHOD static void draw_circle_arc( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour )
{
    int i, x, y;
    int ix = ( int )posx, iy = ( int )posy;
    
    for( i = start; i < end; i++ )
    {
        x = cos_table( (i*4096)/360 ) * ratio / 32768;
        y = sin_table( (i*4096)/360 ) * ratio / 32768;
        
        p_data->bitmap_class->set_pixel( ix + x, iy - y, colour );
    }
}

METHOD static void flood_fill( bitmap_draw_class_t * p_data, uint16_t x, uint16_t y, pixel_t colour )
{
    uint32_t index = ( y * p_data->bitmap_class->width ) + x;
    flood_data_t data;
    
    data.colour = colour;
    data.curr_driver = p_data->bitmap_class;
    
    _fill_right( index, &data );
    _fill_left( index-1, &data );
}

METHOD static void set_bitmap_rgb( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent )
{
    uint16_t counter;
    uint32_t index;
    
    index = ( posy * p_data->bitmap_class->width ) + posx;
    
    while( height-- )
    {
        for( counter = 0; counter < width; counter++ )
        {
            if( ( data[ counter ] != transparent ) || ( use_transparent == FALSE ) )
            {
                p_data->bitmap_class->set_pixel_index( index + counter, data[counter] );
            }
        }
        
        index += p_data->bitmap_class->width;
        data += ( width );
    }
}

METHOD static void get_bitmap_rgb( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data )
{
    uint16_t x,y,i;
    pixel_t * p_pixel;
    pixel_t * d_pixel;
    uint32_t index;
    
    if( posx >= p_data->bitmap_class->width ) return;
    if( posy >= p_data->bitmap_class->height ) return;
    
    p_pixel = p_data->bitmap_class->buffer;
    
    for( i = y = 0; y < height; y++ )
    {
        if( ( y + posy ) >= p_data->bitmap_class->height ) break;
        
        index = ((uint32_t)(posy+y) * p_data->bitmap_class->width) + (uint32_t)posx;
        d_pixel = &p_pixel[index];
        
        for( x = 0; x < width; x++ )
        {
            if( ( x + posx ) < p_data->bitmap_class->width )
            {
                data[i] = d_pixel[x];
            }
            
            i++;
        }
    }
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_draw_class_t );

////////////////////////////////////////////////////////////////////

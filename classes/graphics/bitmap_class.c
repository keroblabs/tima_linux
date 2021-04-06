#include "bitmap_class_private.h"
#include "hardware_class.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator_bitmap( bitmap_class_t * p_data, uint16_t width, uint16_t height )
{
    if( ( width != 0 ) && ( height != 0 ) )
    {
        p_data->buffer = ( pixel_t * )MMALLOC( width * height * sizeof( pixel_t ) );
        p_data->width = width;
        p_data->height = height;
    }
    
    p_data->mutex = tthread_mutex_init();
    p_data->driver = NULL;
}

DELETE static void delete_bitmap( bitmap_class_t * p_data )
{
    if( p_data->driver == NULL ) MFREE( p_data->buffer );
}

STATIC static CLASS(bitmap_class_t) * from_driver( void )
{
    lcd_driver_class_t * driver = STATIC_METHOD( hardware_class_t, get_class )()->get_lcd_driver();

    CLASS(bitmap_class_t) * p_data = NEW_CLASS( bitmap_class_t )( 0, 0 );
    p_data->width = driver->get_width();
    p_data->height = driver->get_height();
    p_data->buffer = ( pixel_t * )driver->get_buffer();
    p_data->driver = driver;
    
    return p_data;
}

METHOD static void claim( bitmap_class_t * p_data )
{
    tthread_mutex_lock( p_data->mutex );
}

METHOD static void release( bitmap_class_t * p_data )
{
    tthread_mutex_unlock( p_data->mutex );
    p_data->driver->release();
}

METHOD static void clear( bitmap_class_t * p_data )
{
    memset( p_data->buffer, 0x00, p_data->width * p_data->height * sizeof( pixel_t ) );
}

METHOD static uint16_t get_width( bitmap_class_t * p_data )
{
    return p_data->width;
}

METHOD static uint16_t get_height( bitmap_class_t * p_data )
{
    return p_data->height;
}

METHOD static uint32_t get_pixel( bitmap_class_t * p_data, uint16_t posx, uint16_t posy )
{
    if( posx >= p_data->width ) return 0;
    if( posy >= p_data->height ) return 0;
    
    uint32_t index = ((uint32_t)posy * p_data->width) + (uint32_t)posx;
    return p_data->buffer[index];
}

METHOD static void set_pixel( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t pixel )
{
    if( posx >= p_data->width ) return;
    if( posy >= p_data->height ) return;
    
    uint32_t index = ((uint32_t)posy * p_data->width) + (uint32_t)posx;
    
    p_data->buffer[index] = pixel;
}

METHOD static void set_pixel_index( bitmap_class_t * p_data, uint32_t index, pixel_t pixel )
{
    p_data->buffer[index] = pixel;
}

METHOD static void * get_buffer( bitmap_class_t * p_data )
{
    return p_data->buffer;
}

METHOD static CLASS(bitmap_class_t) * get_frame( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height )
{
    CLASS(bitmap_class_t) * bitmap = NEW_CLASS( bitmap_class_t )( width, height );

    pixel_t * lcd_buffer_margin = p_data->buffer;
    pixel_t * data = bitmap->buffer;

    lcd_buffer_margin += ( uint32_t )( posy * p_data->width );
    lcd_buffer_margin += ( uint32_t )( posx );

    while( height-- )
    {
        memcpy( data, lcd_buffer_margin, sizeof( pixel_t ) * width );
        
        lcd_buffer_margin += p_data->width;
        data += width;
    }

    return bitmap;
}

METHOD static void copy_bitmap( bitmap_class_t * p_data, const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy )
{
    pixel_t * lcd_buffer_margin = p_data->buffer;
    uint16_t width = bitmap->width;
    uint16_t height = bitmap->height;
    pixel_t * data = bitmap->buffer;
    
    lcd_buffer_margin += ( uint32_t )( posy * p_data->width );
    lcd_buffer_margin += ( uint32_t )( posx );
    
    while( height-- )
    {
        memcpy( lcd_buffer_margin, data, sizeof( pixel_t ) * width );
        
        lcd_buffer_margin += p_data->width;
        data += width;
    }
}

METHOD static void draw_1bbp( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour )
{
    uint16_t x;
    uint16_t y;
    uint16_t bit_mask;
    uint32_t index;
    uint8_t * ptr_pixel;
    
    index = ( posy * p_data->width ) + posx;
    
    for( y = 0; y < heigth; y++ )
    {
        if( y > p_data->height ) break;
        
        ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
        bit_mask = 0x01 << ( y & 0x07 );
        
        for( x = 0; x < width; x++ )
        {
            if( x > p_data->width ) break;
            
            if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
            {
                p_data->set_pixel_index( index+x, fore_colour );
            }
            else
            {
                p_data->set_pixel_index( index+x, back_colour );
            }
        }
        
        index += p_data->width;
    }
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_class_t );

////////////////////////////////////////////////////////////////////


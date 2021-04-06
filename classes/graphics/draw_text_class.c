#include "draw_text_class_private.h"

////////////////////////////////////////////////////////////////////

static void gr_draw_character(  text_bitmap_class_t * p_data,
                                uint8_t character,
                                uint16_t posx, uint16_t posy,
                                pixel_t fore_colour, pixel_t back_colour )
{
    uint32_t index;
    
    index = ( character - p_data->p_font->offset ) * ( p_data->p_font->size );
    p_data->bitmap_class->draw_1bbp( posx, posy, p_data->p_font->width, p_data->p_font->height,
                                     ( uint8_t * )&p_data->p_font->data[index], back_colour, fore_colour);
}

////////////////////////////////////////////////////////////////////

CREATOR static void creator( text_bitmap_class_t * p_data, char * text, bitmap_class_t * dest )
{
    if( text != NULL ) p_data->text_data = ( char * )MMALLOC( strlen( text ) + 1 );
    else p_data->text_data = NULL;
    
    p_data->bitmap_class = dest;
}

DELETE static void delete( text_bitmap_class_t * p_data )
{
    if( p_data->text_data != NULL ) MFREE( p_data->text_data );
}

METHOD static void set_text( text_bitmap_class_t * p_data, char * text )
{
    if( p_data->text_data != NULL ) MFREE( p_data->text_data );
    p_data->text_data = ( char * )MMALLOC( strlen( text ) + 1 );
}

METHOD static void draw( text_bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour )
{
    uint32_t i;
    uint16_t x, y;
    
    if( p_data->p_font == NULL ) return;
    
    x = posx;
    y = posy;
    
    for( i = 0; i < strlen( p_data->text_data ); i++ )
    {
        if( p_data->text_data[i] == 0x0a )
        {
            y += p_data->p_font->height;
        }
        else if( p_data->text_data[i] == 0x0D )
        {
            x = 0;
        }
        else
        {
            gr_draw_character( p_data, ( uint8_t )p_data->text_data[i], x, y, fore_colour, back_colour );
            x += p_data->p_font->width;
        }
    }
}

METHOD static void draw_vertical( text_bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour )
{
    uint32_t i;
    uint16_t x, y;
    
    if( p_data->p_font == NULL ) return;
    
    x = posx;
    y = posy;
    
    for( i = 0; i < strlen( p_data->text_data ); i++ )
    {
        if( p_data->text_data[i] == 0x0a )
        {
        }
        else if( p_data->text_data[i] == 0x0D )
        {
        }
        else
        {
            gr_draw_character( p_data, ( uint8_t )p_data->text_data[i], x, y, fore_colour, back_colour );
            y += p_data->p_font->height;
        }
    }
}

METHOD static uint16_t get_width( text_bitmap_class_t * p_data )
{
    uint32_t i;
    uint32_t len;
    uint32_t max_len;
    
    if( p_data->p_font == NULL ) return 0;
    
    len = 0;
    max_len = 0;
    
    for( i = 0; i < strlen( p_data->text_data ); i++ )
    {
        if( p_data->text_data[i] == 0x0D )
        {
            if( max_len < len ) max_len = len;
            len = 0;
        }
        else
        {
            len += p_data->p_font->width;
        }
    }
    
    if( max_len < len ) max_len = len;
    return max_len;
}

METHOD static uint16_t get_height( text_bitmap_class_t * p_data )
{
    uint32_t i;
    uint32_t len;
    
    if( p_data->p_font == NULL ) return 0;
    
    len = 0;
    
    for( i = 0; i < strlen( p_data->text_data ); i++ )
    {
        if( len == 0 ) len = p_data->p_font->width;
        
        if( p_data->text_data[i] == 0x0a )
        {
            len += p_data->p_font->width;
        }
    }
    
    return len;
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( text_bitmap_class_t );

////////////////////////////////////////////////////////////////////

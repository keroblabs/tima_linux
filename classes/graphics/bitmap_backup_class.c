#include "bitmap_backup_class_private.h"

////////////////////////////////////////////////////////////////////

#define POST_FLIP_INITIAL_SIZE          10000
#define POST_FLIP_ADDITIONAL_SIZE       5000

////////////////////////////////////////////////////////////////////

static void graphics_add_backup( bitmap_backup_class_t * backup, uint32_t index, pixel_t colour )
{
    if( backup && backup->curr_size < backup->max_size )
    {
        backup->pixels[backup->curr_size].pixel = colour;
        backup->pixels[backup->curr_size].index = index;
        backup->curr_size++;
        
        if( backup->curr_size == backup->max_size )
        {
            pixel_rec_t * new_pixels = ( pixel_rec_t * )MMALLOC( sizeof( pixel_rec_t ) * ( backup->max_size + POST_FLIP_ADDITIONAL_SIZE ) );
            if( new_pixels != NULL )
            {
                memcpy( new_pixels, backup->pixels, sizeof( pixel_rec_t ) * backup->max_size );
                backup->max_size += POST_FLIP_ADDITIONAL_SIZE;
                MFREE( backup->pixels );
                backup->pixels = new_pixels;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////

CREATOR static void create_backup( bitmap_backup_class_t * p_data, bitmap_class_t * bitmap_class, uint32_t max_size )
{
    p_data->pixels = ( pixel_rec_t * )malloc( sizeof( pixel_rec_t ) * max_size );
    if( p_data->pixels != NULL )
    {
        p_data->max_size = max_size;
        p_data->curr_size = 0;
        p_data->limit_size = 0;

        if( bitmap_class != NULL )
        {
            p_data->bitmap_class = bitmap_class;
            
            p_data->saved_override[0] = p_data->bitmap_class->set_pixel_index;
            p_data->saved_override[1] = p_data->bitmap_class->set_pixel;
            
            p_data->bitmap_class->set_pixel_index = p_data->set_pixel_index;
            p_data->bitmap_class->set_pixel       = p_data->set_pixel;
        }
    }
}

DELETE static void delete_backup( bitmap_backup_class_t * p_data )
{
    if( p_data->pixels != NULL )
    {
        MFREE( p_data->pixels );
        
        if( p_data->bitmap_class != NULL )
        {
            p_data->bitmap_class->set_pixel_index = p_data->saved_override[0];
            p_data->bitmap_class->set_pixel       = p_data->saved_override[1];
        }
    }
}

METHOD static void reset( bitmap_backup_class_t * p_data )
{
    p_data->curr_size = 0;
}

METHOD static void apply_to( bitmap_backup_class_t * p_data, bitmap_class_t * bitmap_class )
{
    if( ( p_data->pixels != NULL ) && ( bitmap_class != NULL ) )
    {
        while( p_data->curr_size )
        {
            p_data->curr_size--;
            bitmap_class->buffer[p_data->pixels[p_data->curr_size].index] = p_data->pixels[p_data->curr_size].pixel;
        }
    }
}

METHOD static void apply( bitmap_backup_class_t * p_data )
{
    apply_to( p_data, p_data->bitmap_class );
}

METHOD static void draw_1bbp_collect_from( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input )
{
    uint16_t x;
    uint16_t y;
    uint16_t bit_mask;
    uint32_t index;
    uint8_t * ptr_pixel;
    
    index = ( posy * p_data->bitmap_class->width ) + posx;
    
    for( y = 0; y < heigth; y++ )
    {
        ptr_pixel = &input[ ( ( y >> 3 ) * width ) ];
        bit_mask = 0x01 << ( y & 0x07 );
        
        for( x = 0; x < width; x++ )
        {
            if( ( ptr_pixel[ x ] & bit_mask ) != 0 )
            {
                graphics_add_backup( from, index+x, p_data->bitmap_class->buffer[index+x] );
            }
        }
        
        index += p_data->bitmap_class->width;
    }
}

METHOD static void draw_1bbp_collect( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input )
{
    draw_1bbp_collect_from( p_data, posx, posy, width, heigth, p_data, input );
}

METHOD static void draw_1bbp_merge( bitmap_backup_class_t * p_data, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip )
{
    uint16_t x;
    uint16_t y;
    uint16_t bit_mask;
    uint8_t * ptr_pixel;
    
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
                    output->pixels[output->curr_size].pixel = ( is_skip == FALSE ) ? fore_colour : p_data->pixels[output->curr_size].pixel;
                    output->pixels[output->curr_size].index = p_data->pixels[output->curr_size].index;
                    output->curr_size++;
                }
            }
        }
    }
}

METHOD static void set_pixel( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t pixel )
{
    uint32_t index = ((uint32_t)posy * p_data->bitmap_class->width) + (uint32_t)posx;
    graphics_add_backup( p_data, index, p_data->bitmap_class->buffer[index] );
    p_data->bitmap_class->buffer[index] = pixel;
}

METHOD static void set_pixel_index( bitmap_backup_class_t * p_data, uint32_t index, pixel_t pixel )
{
    graphics_add_backup( p_data, index, p_data->bitmap_class->buffer[index] );
    p_data->bitmap_class->buffer[index] = pixel;
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_backup_class_t );

////////////////////////////////////////////////////////////////////


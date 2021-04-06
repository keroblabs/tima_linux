#ifndef __graphics_bitmap_class_h__
#define __graphics_bitmap_class_h__

///////////////////////////////////////////////////////////////

#include "lcd_driver_class.h"

///////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 64

///////////////////////////////////////////////////////////////

typedef uint32_t pixel_t;

///////////////////////////////////////////////////////////////

typedef CLASS(bitmap_class_t)
{
    CLASS_DATA_VOID;
    
    lcd_driver_class_t * driver;
	pixel_t * buffer;

    uint16_t width;
    uint16_t height;

    pixel_t background_colour;
    
    void * mutex;
    
    CREATOR void ( *creator_bitmap )( uint16_t width, uint16_t height );
    DELETE  void ( *delete_bitmap )( void );
    STATIC  CLASS(bitmap_class_t) * ( * from_driver )( void );
    
    METHOD void ( *claim )( void );
    METHOD void ( *release )( void );
    
    METHOD void ( *clear )( void );
    
    METHOD uint16_t ( *get_width )( void );
    METHOD uint16_t ( *get_height )( void );
    METHOD uint32_t ( *get_pixel )( uint16_t posx, uint16_t posy );
    METHOD void     ( *set_pixel )( uint16_t posx, uint16_t posy, pixel_t pixel );
    METHOD void     ( *set_pixel_index )( uint32_t index, pixel_t pixel );

    METHOD void *   ( *get_buffer )( void );
    
    METHOD CLASS(bitmap_class_t) * ( *get_frame )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth );

    METHOD void ( *copy_bitmap )( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy );
    METHOD void ( *draw_1bbp )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour );

} bitmap_class_t;

///////////////////////////////////////////////////////////////

#endif // __graphics_bitmap_class_h__

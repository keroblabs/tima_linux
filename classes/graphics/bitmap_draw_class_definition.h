#ifndef __bitmap_draw_class_h__
#define __bitmap_draw_class_h__

///////////////////////////////////////////////////////////////

#include "bitmap_class.h"

///////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 64

///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

typedef CLASS(bitmap_draw_class_t)
{
    CLASS_DATA_VOID;
    
    bitmap_class_t * bitmap_class;
    
    CREATOR void ( *creator_bitmap )( bitmap_class_t * bitmap_class );
    DELETE  void ( *delete_bitmap )( void );

    METHOD void ( *fill_box )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );
    METHOD void ( *draw_line )( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour );
    METHOD void ( *draw_rectangle )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );
    METHOD void ( *draw_circle )( uint16_t posx, uint16_t posy, int ratio, pixel_t colour );
    METHOD void ( *draw_circle_arc )( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour );

    METHOD void ( *flood_fill )( uint16_t x, uint16_t y, pixel_t colour );
    
    METHOD void ( *set_bitmap_rgb )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent );
    METHOD void ( *get_bitmap_rgb )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data );

} bitmap_draw_class_t;

///////////////////////////////////////////////////////////////

#endif // __bitmap_draw_class_h__

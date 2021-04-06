#ifndef draw_text_class_h
#define draw_text_class_h

///////////////////////////////////////////////////////////////

#include "bitmap_class.h"

///////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 64

///////////////////////////////////////////////////////////////

typedef struct _font_data_t
{
    uint16_t width;
    uint16_t height;
    uint16_t offset;
    uint16_t size;
    
    const uint8_t * data;
} font_data_t;

typedef CLASS(text_bitmap_class_t)
{
    CLASS_DATA_VOID;
    
    font_data_t          * p_font;
    bitmap_class_t       * bitmap_class;
    char                 * text_data;
    
    CREATOR void ( *creator )( char * text, bitmap_class_t * dest );
    DELETE void ( *delete )( void );
    
    METHOD void ( *set_text )( char * text );
    METHOD void ( *draw )( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );
    METHOD void ( *draw_vertical )( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );
    METHOD uint16_t ( *get_width )( void );
    METHOD uint16_t ( *get_height )( void );
    
} text_bitmap_class_t;

///////////////////////////////////////////////////////////////

#endif /* draw_text_class_h */

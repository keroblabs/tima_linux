#ifndef graphics_backup_h
#define graphics_backup_h

///////////////////////////////////////////////////////////////

#include "bitmap_class.h"

///////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES       64

///////////////////////////////////////////////////////////////

typedef struct _pixel_rec_t
{
    uint32_t index;
    pixel_t pixel;
    
} pixel_rec_t;

typedef CLASS(bitmap_backup_class_t)
{
    CLASS_DATA * p_data;
    
    pixel_rec_t * pixels;
    uint32_t max_size;
    uint32_t curr_size;
    uint32_t limit_size;
    bitmap_class_t * bitmap_class;
    void * saved_override[2];
    
    CREATOR void ( *create_backup )( bitmap_class_t * bitmap_class, uint32_t max_size );
    DELETE void ( *delete_backup )( void );
    METHOD void ( *reset )( void );
    METHOD void ( *apply_to )( bitmap_class_t * bitmap_class );
    METHOD void ( *apply )( void );

    METHOD void ( *draw_1bbp_collect_from )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input );
    METHOD void ( *draw_1bbp_collect )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input );
    METHOD void ( *draw_1bbp_merge )( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip );

    METHOD void ( *set_pixel )( uint16_t posx, uint16_t posy, pixel_t pixel );
    METHOD void ( *set_pixel_index )( uint32_t index, pixel_t pixel );

} bitmap_backup_class_t;

///////////////////////////////////////////////////////////////

#endif /* graphics_backup_h */

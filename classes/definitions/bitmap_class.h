#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_H

////////////////////////////////////////////////////////////////////

#include "bitmap_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_bitmap_class_t
{
    CREATOR void ( * creator_bitmap )( bitmap_class_t * _data_bitmap_class_t, uint16_t width, uint16_t height );
    DELETE void ( * delete_bitmap )( bitmap_class_t * _data_bitmap_class_t );
    STATIC CLASS(bitmap_class_t) * ( * from_driver )( void );
    METHOD void ( * claim )( bitmap_class_t * _data_bitmap_class_t );
    METHOD void ( * release )( bitmap_class_t * _data_bitmap_class_t );
    METHOD void ( * clear )( bitmap_class_t * _data_bitmap_class_t );
    METHOD uint16_t ( * get_width )( bitmap_class_t * _data_bitmap_class_t );
    METHOD uint16_t ( * get_height )( bitmap_class_t * _data_bitmap_class_t );
    METHOD uint32_t ( * get_pixel )( bitmap_class_t * _data_bitmap_class_t, uint16_t posx, uint16_t posy );
    METHOD void ( * set_pixel )( bitmap_class_t * _data_bitmap_class_t, uint16_t posx, uint16_t posy, pixel_t pixel );
    METHOD void ( * set_pixel_index )( bitmap_class_t * _data_bitmap_class_t, uint32_t index, pixel_t pixel );
    METHOD void * ( * get_buffer )( bitmap_class_t * _data_bitmap_class_t );
    METHOD CLASS(bitmap_class_t) * ( * get_frame )( bitmap_class_t * _data_bitmap_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth );
    METHOD void ( * copy_bitmap )( bitmap_class_t * _data_bitmap_class_t, const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy );
    METHOD void ( * draw_1bbp )( bitmap_class_t * _data_bitmap_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour );
} api_bitmap_class_t;

////////////////////////////////////////////////////////////////////

extern api_bitmap_class_t * api_bitmap_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_bitmap_class_t( uint16_t width, uint16_t height );
void * _instance_new_bitmap_class_t_ex( void * api_bitmap_class_t_class, uint16_t width, uint16_t height );
void * _instance_static_bitmap_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_CLASS_H

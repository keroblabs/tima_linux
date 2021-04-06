#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_H

////////////////////////////////////////////////////////////////////

#include "bitmap_draw_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_bitmap_draw_class_t
{
    CREATOR void ( * creator_bitmap )( bitmap_draw_class_t * _data_bitmap_draw_class_t, bitmap_class_t * bitmap_class );
    DELETE void ( * delete_bitmap )( bitmap_draw_class_t * _data_bitmap_draw_class_t );
    METHOD void ( * fill_box )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );
    METHOD void ( * draw_line )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour );
    METHOD void ( * draw_rectangle )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );
    METHOD void ( * draw_circle )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, int ratio, pixel_t colour );
    METHOD void ( * draw_circle_arc )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour );
    METHOD void ( * flood_fill )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t x, uint16_t y, pixel_t colour );
    METHOD void ( * set_bitmap_rgb )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent );
    METHOD void ( * get_bitmap_rgb )( bitmap_draw_class_t * _data_bitmap_draw_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data );
} api_bitmap_draw_class_t;

////////////////////////////////////////////////////////////////////

extern api_bitmap_draw_class_t * api_bitmap_draw_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_bitmap_draw_class_t( bitmap_class_t * bitmap_class );
void * _instance_new_bitmap_draw_class_t_ex( void * api_bitmap_draw_class_t_class, bitmap_class_t * bitmap_class );
void * _instance_static_bitmap_draw_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_DRAW_CLASS_H

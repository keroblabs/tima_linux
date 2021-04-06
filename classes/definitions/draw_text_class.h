#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_DRAW_TEXT_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_DRAW_TEXT_CLASS_H

////////////////////////////////////////////////////////////////////

#include "draw_text_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_text_bitmap_class_t
{
    CREATOR void ( * creator )( text_bitmap_class_t * _data_text_bitmap_class_t, char * text, bitmap_class_t * dest );
    DELETE void ( * delete )( text_bitmap_class_t * _data_text_bitmap_class_t );
    METHOD void ( * set_text )( text_bitmap_class_t * _data_text_bitmap_class_t, char * text );
    METHOD void ( * draw )( text_bitmap_class_t * _data_text_bitmap_class_t, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );
    METHOD void ( * draw_vertical )( text_bitmap_class_t * _data_text_bitmap_class_t, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );
    METHOD uint16_t ( * get_width )( text_bitmap_class_t * _data_text_bitmap_class_t );
    METHOD uint16_t ( * get_height )( text_bitmap_class_t * _data_text_bitmap_class_t );
} api_text_bitmap_class_t;

////////////////////////////////////////////////////////////////////

extern api_text_bitmap_class_t * api_text_bitmap_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_text_bitmap_class_t( char * text, bitmap_class_t * dest );
void * _instance_new_text_bitmap_class_t_ex( void * api_text_bitmap_class_t_class, char * text, bitmap_class_t * dest );
void * _instance_static_text_bitmap_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_DRAW_TEXT_CLASS_H

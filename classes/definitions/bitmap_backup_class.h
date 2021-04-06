#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_H

////////////////////////////////////////////////////////////////////

#include "bitmap_backup_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_bitmap_backup_class_t
{
    CREATOR void ( * create_backup )( bitmap_backup_class_t * _data_bitmap_backup_class_t, bitmap_class_t * bitmap_class, uint32_t max_size );
    DELETE void ( * delete_backup )( bitmap_backup_class_t * _data_bitmap_backup_class_t );
    METHOD void ( * reset )( bitmap_backup_class_t * _data_bitmap_backup_class_t );
    METHOD void ( * apply_to )( bitmap_backup_class_t * _data_bitmap_backup_class_t, bitmap_class_t * bitmap_class );
    METHOD void ( * apply )( bitmap_backup_class_t * _data_bitmap_backup_class_t );
    METHOD void ( * draw_1bbp_collect_from )( bitmap_backup_class_t * _data_bitmap_backup_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input );
    METHOD void ( * draw_1bbp_collect )( bitmap_backup_class_t * _data_bitmap_backup_class_t, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input );
    METHOD void ( * draw_1bbp_merge )( bitmap_backup_class_t * _data_bitmap_backup_class_t, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip );
    METHOD void ( * set_pixel )( bitmap_backup_class_t * _data_bitmap_backup_class_t, uint16_t posx, uint16_t posy, pixel_t pixel );
    METHOD void ( * set_pixel_index )( bitmap_backup_class_t * _data_bitmap_backup_class_t, uint32_t index, pixel_t pixel );
} api_bitmap_backup_class_t;

////////////////////////////////////////////////////////////////////

extern api_bitmap_backup_class_t * api_bitmap_backup_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_bitmap_backup_class_t( bitmap_class_t * bitmap_class, uint32_t max_size );
void * _instance_new_bitmap_backup_class_t_ex( void * api_bitmap_backup_class_t_class, bitmap_class_t * bitmap_class, uint32_t max_size );
void * _instance_static_bitmap_backup_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_GRAPHICS_BITMAP_BACKUP_CLASS_H

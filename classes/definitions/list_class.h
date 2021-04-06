#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_H

////////////////////////////////////////////////////////////////////

#include "list_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_list_class_t
{
    CREATOR void ( * creator_list )( list_class_t * _data_list_class_t, delete_cb_t delete_cb );
    DELETE void ( * delete_list )( list_class_t * _data_list_class_t );
    METHOD void ( * clear )( list_class_t * _data_list_class_t );
    METHOD void ( * insert_head )( list_class_t * _data_list_class_t, list_node_t * node );
    METHOD void ( * insert_tail )( list_class_t * _data_list_class_t, list_node_t * node );
    METHOD void ( * remove_tail )( list_class_t * _data_list_class_t );
    METHOD bool_t ( * unlink_node )( list_class_t * _data_list_class_t, list_node_t * node );
    METHOD bool_t ( * remove_node )( list_class_t * _data_list_class_t, list_node_t * node );
    METHOD bool_t ( * is_empty )( list_class_t * _data_list_class_t );
    METHOD void * ( * get_head )( list_class_t * _data_list_class_t );
    METHOD void * ( * get_tail )( list_class_t * _data_list_class_t );
    METHOD void * ( * get_next )( list_class_t * _data_list_class_t, list_node_t * node );
    METHOD void * ( * get_prev )( list_class_t * _data_list_class_t, list_node_t * curr );
    METHOD uint16_t ( * size )( list_class_t * _data_list_class_t );
} api_list_class_t;

////////////////////////////////////////////////////////////////////

extern api_list_class_t * api_list_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_list_class_t( delete_cb_t delete_cb );
void * _instance_new_list_class_t_ex( void * api_list_class_t_class, delete_cb_t delete_cb );
void * _instance_static_list_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_H

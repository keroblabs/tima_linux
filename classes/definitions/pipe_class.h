#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_H

////////////////////////////////////////////////////////////////////

#include "pipe_class_definition.h"

////////////////////////////////////////////////////////////////////

typedef struct _api_pipe_class_t
{
    CREATOR void ( * creator )( pipe_class_t * _data_pipe_class_t, uint32_t max_size );
    DELETE void ( * delete_pipe )( pipe_class_t * _data_pipe_class_t );
    METHOD void * ( * get )( pipe_class_t * _data_pipe_class_t, uint32_t * size );
    METHOD void * ( * read )( pipe_class_t * _data_pipe_class_t, uint32_t * size );
    METHOD void * ( * wait_for_data )( pipe_class_t * _data_pipe_class_t, uint32_t * size );
    METHOD void ( * write )( pipe_class_t * _data_pipe_class_t, void * buffer, uint32_t size );
    METHOD void ( * send )( pipe_class_t * _data_pipe_class_t, void * buffer, uint32_t size );
    METHOD bool_t ( * is_full )( pipe_class_t * _data_pipe_class_t );
    METHOD bool_t ( * is_empty )( pipe_class_t * _data_pipe_class_t );
} api_pipe_class_t;

////////////////////////////////////////////////////////////////////

extern api_pipe_class_t * api_pipe_class_t_class;

////////////////////////////////////////////////////////////////////

void * _instance_new_pipe_class_t( uint32_t max_size );
void * _instance_new_pipe_class_t_ex( void * api_pipe_class_t_class, uint32_t max_size );
void * _instance_static_pipe_class_t_method( void * __api );

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_H

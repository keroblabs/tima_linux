#ifndef _DISC_UTILS_H_
#define _DISC_UTILS_H_

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "lists.h"
#include "string_lib.h"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct _file_data_t
{
    list_node_t node;
    string_t * full_path;
} file_data_t;

//////////////////////////////////////////////////////////////////////////////////////

void disc_utils_read_dir( const char * dir_path, const char * ext, list_t * file_list, bool_t recursive );
void disc_utils_init_file_list( list_t * file_list );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _DISC_UTILS_H_


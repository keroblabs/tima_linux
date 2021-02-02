#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#include "tima_libc.h"
#include "disc_utils.h"

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

static file_data_t * create_file_data( const char * curr_path, const char * name )
{
    file_data_t * item = ( file_data_t * )ZMMALLOC( sizeof( file_data_t ) );
    if( item == NULL ) return NULL;
    
    item->full_path = string_create_ex( curr_path );
    string_append_text( item->full_path, "/" );
    string_append_text( item->full_path, name );

    return item;
}

static void delete_file_data( list_node_t * node )
{
    file_data_t * item = ( file_data_t * )node;
    string_destroy( item->full_path );
}

void disc_utils_init_file_list( list_t * file_list )
{
    list_init( file_list, delete_file_data );
}

void disc_utils_read_dir( const char * dir_path, const char * ext, list_t * file_list, bool_t recursive )
{
    DIR * dir = opendir( dir_path );
    struct dirent * dir_entry;

    if( dir == NULL ) return;

    while( ( dir_entry = readdir( dir ) ) != NULL )
    {
        if( ( recursive == TRUE ) && ( dir_entry->d_type == 4 ) && strcmp( dir_entry->d_name, "." ) && strcmp( dir_entry->d_name, ".." ) )
        {
            char new_path[128];
            strcpy( new_path, dir_path );
            strcat( new_path, "/" );
            strcat( new_path, dir_entry->d_name );
            disc_utils_read_dir( new_path, ext, file_list, recursive );
        }
        else if( dir_entry->d_type == 8 )
        {
            file_data_t * ret = create_file_data( dir_path, dir_entry->d_name );

            if( ( ext == NULL ) || ( string_locate_content( ret->full_path, ext ) >= 0 ) )
            {
                list_insert_tail( file_list, &ret->node );
            }
            else
            {
                delete_file_data( &ret->node );
            }
        }
    }

    closedir( dir );
}


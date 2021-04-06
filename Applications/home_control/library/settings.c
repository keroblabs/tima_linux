#include "settings.h"
#include "string_lib.h"
#include "tima_libc.h"

#include "schedule_ctrl.h"
#include "sensor_ctrl.h"
#include "driver_ctrl.h"
#include "background.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

string_t * settings_get_line_string( FILE * fp )
{
    string_t * file_line;
    
    while( 1 )
    {
        file_line = string_file_line( fp );
        if( file_line == NULL ) return NULL;

        if( string_char_at( file_line, 0 ) != '#' )
        {
            break;
        }
        
        string_destroy( file_line );
    }
    
    string_trim( file_line );
    string_trail( file_line );
    
    if( string_length( file_line ) == 0 )
    {
        string_destroy( file_line );
        return NULL;
    }

    return file_line;
}

string_t * settings_get_line_header( FILE * fp )
{
    string_t * file_line;
    
    while( 1 )
    {
        file_line = string_file_line( fp );
        if( file_line == NULL ) return NULL;
        
        if( string_char_at( file_line, 0 ) != '#' )
        {
            string_trim( file_line );
            string_trail( file_line );

            if( string_length( file_line ) > 0 )
            {
                break;
            }
        }
        
        string_destroy( file_line );
    }
    
    return file_line;
}

string_t * settings_get_param( string_t * line, const char * field )
{
    uint32_t pos = 0;
    string_t * ret;
    
    ret = string_parse( line, &pos, ":" );
    string_trim( ret );
    string_trail( ret );
    
    if( strcmp( string_get_char_buffer( ret ), field ) )
    {
        string_destroy( ret );
        return NULL;
    }
    
    string_destroy( ret );
    ret = string_get_substring( line, pos, NEG_U32 );

    string_trim( ret );
    string_trail( ret );

    return ret;
}

uint32_t settings_get_numbers( string_t * line, int * list, uint32_t max_size )
{
    uint32_t pos = 0;
    uint32_t index = 0;
    string_t * temp;
    
    // pos = string_locate_content( line, "," );
    // if( pos == -1 ) return index;
    
    while( index < max_size )
    {
        temp = string_parse( line, &pos, "," );
        if( temp == NULL )
        {
            string_destroy( temp );
            break;
        }

        list[index++] = (int)tima_atoi( string_get_char_buffer( temp ) );
        string_destroy( temp );
    }
    
    return index;
}

super_item_t * settings_locate_item( list_t * list, const char * name )
{
    super_item_t * search = ( super_item_t * )list_get_head( list );
    
    while( search != NULL )
    {
        if( !strcmp( search->name, name ) )
        {
            return search;
        }
        
        search = ( super_item_t * )list_get_next( list, &search->node );
    }
    
    return NULL;
}

super_item_t * settings_create_item( string_t * line, const char * header, size_t size )
{
    super_item_t * item = ( super_item_t * )ZMMALLOC( size );
    if( item == NULL ) return NULL;
    
    string_t * s_name = settings_get_param( line, header );
    if( s_name == NULL )
    {
        MFREE( item );
        return NULL;
    }
    
    strcpy( item->name, string_get_char_buffer( s_name ) );
    string_destroy( s_name );

    return item;
}

string_t * settings_locate_param( string_t * line, const char * param )
{
    string_t * ret = NULL;
    
    if( string_locate_content( line, param ) == 0 )
    {
        ret = settings_get_param( line, param );
    }
    
    return ret;
}

void settings_init( home_data_t * home_data )
{
    memset( home_data, 0x00, sizeof( home_data_t ) );
    
#ifdef MAKE_RPI
    home_data->root_dir = background_spawn( "pwd" );
#else
    home_data->root_dir = string_create_ex( "/Volumes/Home Directory/home_control" );
#endif
    //printf( "Root dir: %s\n", string_get_char_buffer( home_data->root_dir ) );

    string_trim( home_data->root_dir );
    string_trail( home_data->root_dir );

    schedule_init( home_data );
    list_init( &home_data->sensor_list, NULL );
    list_init( &home_data->driver_list, NULL );
}

void settings_reload( home_data_t * home_data )
{
    schedule_destroy( home_data );
    list_clear( &home_data->sensor_list );
    list_clear( &home_data->driver_list );
    
    settings_load( home_data, home_data->config_file );
}

void settings_load( home_data_t * home_data, const char * filename )
{
    FILE * fp;
    string_t * line;
    
    strcpy( home_data->config_file, filename );
    
#ifdef MAKE_RPI
    string_t * settings_filename = string_sprintf( "%s/%s", string_get_char_buffer( home_data->root_dir ), filename );
#else
    string_t * settings_filename = string_sprintf( "/Users/marciocherobim/Projects/linux_a20/tima_linux/Applications/home_control/make_rpi/%s", filename );
#endif

    printf( "%s\n", string_get_char_buffer( settings_filename ) );
    fp = string_fopen( settings_filename, "r", FOPEN_DESTROY_FILENAME );
    if( fp == NULL )
    {
        printf( "Failed to open\r\n" );
        return;
    }
    
    //printf( "Opened config file\r\n" );
    while( ( line = settings_get_line_header( fp ) ) != NULL )
    {
        schedule_load( home_data, line, fp );
        sensor_load( home_data, line, fp );
        driver_load( home_data, line, fp );
        
        string_destroy( line );
    }
    
    fclose( fp );
}

#include "settings.h"
#include "string_lib.h"
#include "tima_libc.h"
#include "background.h"

#include "room_control.h"
#include "thermometer_control.h"
#include "valve_control.h"
#include "driver_ctrl.h"

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

static repeater_t * settings_locate_repeater( home_data_t * home_data, const char * address )
{
    repeater_t * repeater = ( repeater_t * )list_get_head( &home_data->repeater_list );
    
    while( repeater != NULL )
    {
        if( !strcpy( repeater->device_address, address ) )
        {
            return repeater;
        }
        
        repeater = list_get_next( &home_data->repeater_list, &repeater->node );
    }

    return NULL;
}

static repeater_t * settings_add_repeater( home_data_t * home_data, const char * repeater_address, const char * device_address )
{
    repeater_t * repeater = settings_locate_repeater( home_data, device_address );
    if( repeater == NULL )
    {
        repeater = ZMMALLOC( sizeof( repeater_t ) );
        if( repeater == NULL ) return NULL;
        strcpy( repeater->device_address, device_address );
    }
    
    strcpy( repeater->repeater_address, repeater_address );
    return repeater;
}

void settings_init( home_data_t * home_data )
{
    memset( home_data, 0x00, sizeof( home_data_t ) );
    
    list_init( &home_data->room_list, room_destroy_room_data );
    list_init( &home_data->settings_list, NULL );
    list_init( &home_data->profile_list, room_destroy_profile );
    
#ifdef MAKE_RPI
    home_data->root_dir = background_spawn( "pwd" );
    //printf( "%s\n", string_get_char_buffer( home_data->root_dir ) );
#else
    home_data->root_dir = string_create_ex( "/Volumes/Home Directory/home_control" );
#endif
    
    string_trim( home_data->root_dir );
    string_trail( home_data->root_dir );

    list_init( &home_data->valve_list, NULL );
    list_init( &home_data->driver_list, NULL );
    list_init( &home_data->thermometer_list, NULL );
}

void settings_destroy( home_data_t * home_data )
{
    list_clear( &home_data->room_list );
    list_clear( &home_data->settings_list );
    list_clear( &home_data->profile_list );
    list_clear( &home_data->valve_list );
    list_clear( &home_data->driver_list );
    list_clear( &home_data->thermometer_list );
    
    MFREE( home_data->hot_water );
    
    string_destroy( home_data->root_dir );
}

void settings_load( home_data_t * home_data, const char * filename )
{
    FILE * fp;
    string_t * line;
    
#ifdef MAKE_RPI
    string_t * settings_filename = string_sprintf( "%s/%s", string_get_char_buffer( home_data->root_dir ), filename );
#else
    string_t * settings_filename = string_sprintf( "/Volumes/Home Directory/home_control/%s", filename );
#endif

    //printf( "%s\n", string_get_char_buffer( settings_filename ) );
    fp = string_fopen( settings_filename, "r", FOPEN_DESTROY_FILENAME );
    if( fp == NULL )
    {
        return;
    }
    
    while( ( line = settings_get_line_header( fp ) ) != NULL )
    {
        if( room_load( home_data, line, fp ) )
        {
        }
        else if( driver_load( home_data, line, fp ) )
        {
        }
        else if( valve_load( home_data, line, fp ) )
        {
        }
        else if( thermometer_load( home_data, line, fp ) )
        {
        }
        
        string_destroy( line );
    }
    
    fclose( fp );
}

void settings_save( home_data_t * home_data, const char * filename )
{
    FILE * fp;

    fp = fopen( filename, "w" );
    if( fp == NULL )
    {
        return;
    }
    
    room_save( home_data, fp );
    driver_save( home_data, fp );
    valve_save( home_data, fp );
    thermometer_save( home_data, fp );
    
    fclose( fp );
}

void settings_set_repeater( home_data_t * home_data, const char * repeater_address, const char * device_address )
{
    settings_add_repeater( home_data, repeater_address, device_address );
}

string_t * settings_get_repeater( home_data_t * home_data, const char * device_address )
{
    repeater_t * repeater = settings_locate_repeater( home_data, device_address );
    if( repeater == NULL ) return NULL;
    
    return string_create_ex( repeater->device_address );
}

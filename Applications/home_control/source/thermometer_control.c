#include "thermometer_control.h"
#include "string_lib.h"
#include "settings.h"
#include "room_control.h"
#include "tima_libc.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

bool_t thermometer_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    if( string_locate_content( line, THERMOMETER_HEADER ) != 0 ) return FALSE;

    thermometer_t * new_thermometer = ( thermometer_t * )settings_create_item( line, THERMOMETER_HEADER, sizeof( thermometer_t ) );
    if( new_thermometer == NULL ) return FALSE;
    
    int index = 0;
    
    while( 1 )
    {
        string_t * thermometer_line = settings_get_line_string( fp );
        if( thermometer_line == NULL ) break;
        
        string_t * s_param = NULL;
        
        if( string_locate_content( thermometer_line, XIAOMI_PARAM ) == 0 )
        {
            s_param = settings_get_param( thermometer_line, XIAOMI_PARAM );
            new_thermometer->type = Thermometer_Xiaomi;
            strcpy( new_thermometer->address, string_get_char_buffer( s_param ) );
        }
        else if( string_locate_content( thermometer_line, TIMA_PARAM ) == 0 )
        {
            s_param = settings_get_param( thermometer_line, TIMA_PARAM );
            new_thermometer->type = Thermometer_Tima;
            strcpy( new_thermometer->address, string_get_char_buffer( s_param ) );
        }
        else if( ( string_locate_content( thermometer_line, TARGET_PARAM ) == 0 ) && ( index < ( THERMOMETER_MAX_ROOMS - 1 ) ) )
        {
            s_param = settings_get_param( thermometer_line, TARGET_PARAM );
            room_data_t * room = room_locate( home_data, string_get_char_buffer( s_param ) );
            if( room != NULL ) new_thermometer->room_list[index] = room;
            index++;
        }
        
        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( thermometer_line );
    }
    
    list_insert_tail( &home_data->thermometer_list, &new_thermometer->node );
    
    return TRUE;
}

void thermometer_save( home_data_t * home_data, FILE * fp )
{
    thermometer_t * search = ( thermometer_t * )list_get_head( &home_data->thermometer_list );
    
    while( search != NULL )
    {
        fprintf( fp, "%s: %s\r\n", THERMOMETER_HEADER, search->name );
        
        if( search->type == Thermometer_Tima ) fprintf( fp, "%s: %s\r\n", TIMA_PARAM, search->address );
        else if( search->type == Thermometer_Xiaomi ) fprintf( fp, "%s: %s\r\n", XIAOMI_PARAM, search->address );
        
        int i;
        for( i = 0; i < THERMOMETER_MAX_ROOMS; i++ )
        {
            if( search->room_list[i] == NULL ) break;
            fprintf( fp, "%s: %s\r\n", TARGET_PARAM, search->room_list[i]->name );
        }
        
        fprintf( fp, "\r\n" );
        search = ( thermometer_t * )list_get_next( &home_data->thermometer_list, &search->node );
    }
}

bool_t thermometer_get( home_data_t * home_data, thermometer_t ** thermometer_data )
{
    GET_ITEM_FROM_LIST(thermometer_t, home_data->thermometer_list, thermometer_data);
}

thermometer_t * thermometer_locate_from_room( home_data_t * home_data, const char * room )
{
    thermometer_t * search = ( thermometer_t * )list_get_head( &home_data->thermometer_list );
    
    while( search != NULL )
    {
        int i;
        for( i = 0; i < THERMOMETER_MAX_ROOMS; i++ )
        {
            if( search->room_list[i] == NULL ) break;
            
            if( !strcmp( search->room_list[i]->name, room ) )
            {
                return search;
            }
        }
        
        search = ( thermometer_t * )list_get_next( &home_data->thermometer_list, &search->node );
    }
    
    return NULL;
}

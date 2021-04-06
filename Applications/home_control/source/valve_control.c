#include "valve_control.h"
#include "string_lib.h"
#include "settings.h"
#include "tima_libc.h"
#include "room_control.h"
#include "bluetooth.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static uint8_t count_proc;

////////////////////////////////////////////////////////////////////

bool_t valve_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    count_proc = 0;
    
    if( string_locate_content( line, VALVE_HEADER ) != 0 ) return FALSE;
    
    valve_t * new_valve = ( valve_t * )settings_create_item( line, VALVE_HEADER, sizeof( valve_t ) );
    if( new_valve == NULL ) return FALSE;
    
    new_valve->temperature = 0;
    new_valve->valve_pos = (uint8_t)NEG_U32;
    int target_cnt = 0;
    
    while( 1 )
    {
        string_t * valve_line = settings_get_line_string( fp );
        if( valve_line == NULL ) break;
        
        string_t * s_param = NULL;
        
        if( string_locate_content( valve_line, EQIVA_PARAM ) == 0 )
        {
            s_param = settings_get_param( valve_line, EQIVA_PARAM );
            new_valve->type = Valve_Eqiva;
            strcpy( new_valve->address, string_get_char_buffer( s_param ) );
        }
        else if( string_locate_content( valve_line, LEVEL_PARAM ) == 0 )
        {
            s_param = settings_get_param( valve_line, LEVEL_PARAM );
            int int_list[2];
            settings_get_numbers( s_param, int_list, 2 );
            new_valve->pos_threshold = int_list[0];
            new_valve->pos_offset = int_list[1];
        }
        else if( string_locate_content( valve_line, TARGET_PARAM ) == 0 )
        {
            s_param = settings_get_param( valve_line, TARGET_PARAM );
            room_data_t * room = room_locate(home_data, string_get_char_buffer( s_param ) );
            if( room != NULL )
            {
                new_valve->room_target = room;
                target_cnt++;
            }
        }
        
        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( valve_line );
    }
    
    if( ( new_valve->type != Valve_None ) && ( target_cnt > 0 ) )
    {
        list_insert_tail( &home_data->valve_list, &new_valve->node );
    }
    else
    {
        MFREE( new_valve );
    }
    
    return TRUE;
}

void valve_save( home_data_t * home_data, FILE * fp )
{
    valve_t * search = ( valve_t * )list_get_head( &home_data->valve_list );
    
    while( search != NULL )
    {
        fprintf( fp, "%s:%s\r\n", VALVE_HEADER, search->name );
        
        if( search->type == Valve_Eqiva ) fprintf( fp, "%s:%s\r\n", EQIVA_PARAM, search->address );
        else if( search->type == Valve_Tima ) fprintf( fp, "%s:%s\r\n", TIMA_PARAM, search->address );
        
        fprintf( fp, "%s: %d, %d\r\n", LEVEL_PARAM, search->pos_threshold, search->pos_offset );
        fprintf( fp, "%s: %s\r\n", TARGET_PARAM, search->room_target->name );
        fprintf( fp, "\r\n" );
        
        search = ( valve_t * )list_get_next( &home_data->valve_list, &search->node );
    }
}

bool_t valve_get( home_data_t * home_data, valve_t ** valve_data )
{
    GET_ITEM_FROM_LIST(valve_t, home_data->valve_list, valve_data);
}

valve_t * valve_locate_from_room( home_data_t * home_data, const char * room )
{
    valve_t * search = ( valve_t * )list_get_head( &home_data->valve_list );
    
    while( search != NULL )
    {
        if( !strcmp( search->room_target->name, room ) )
        {
            return search;
        }
        search = ( valve_t * )list_get_next( &home_data->valve_list, &search->node );
    }
    
    return NULL;
}

void valve_process( home_data_t * home_data )
{
    valve_t * valve = NULL;
    
    while( valve_get( home_data, &valve ) == TRUE )
    {
        if( valve->type == Valve_Eqiva )
        {
            eqiva_status_t eqiva_status;
            bool_t ret1 = FALSE;
            bool_t ret2 = FALSE;
            char is_update = ' ';

            eqiva_status.temperature = 0;
            int target_temperature = 0;

            room_data_t * room_data = valve->room_target;
            ret2 = room_get_target_temperature( room_data, &target_temperature );
            
            if( ( ret2 == TRUE ) && ( valve->temperature != 0 ) && ( valve->temperature != target_temperature ) )
            {
                is_update = '*';
                ret1 = bluetooth_eqiva_set_temperature( home_data, valve->address, target_temperature, &eqiva_status );
            }
            else
            {
                ret1 = bluetooth_eqiva_valve_read_status( home_data, valve->address, &eqiva_status );
            }

            if( ( ret1 == TRUE ) && ( ret2 == TRUE ) )
            {
                printf( "%s: now = %.1f, target = %d, valve = %d, open %d%% %c\r\n", room_data->name, room_data->temperature, target_temperature,
                                                                                   eqiva_status.temperature, eqiva_status.valve_pos, is_update );
            }
            
            if( ret1 == TRUE )
            {
                valve->valve_pos = eqiva_status.valve_pos;
                valve->low_battery = eqiva_status.low_battery;
                valve->temperature = eqiva_status.temperature;
                
                room_data->valve_pos = eqiva_status.valve_pos;
            }
        }
    }
    
    count_proc++;
}

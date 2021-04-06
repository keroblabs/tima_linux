#include "driver_ctrl.h"
#include "background.h"
#include "settings.h"
#include "valve_control.h"
#include "thermometer_control.h"
#include "room_control.h"
#include "bluetooth.h"

////////////////////////////////////////////////////////////////////

#if 0


driver: boiler_hw
espeasy: ESP-Easy-1/control?cmd=GPIO,12
source: hot_water
target: Hot Water Program

driver: heater_dogs1
espeasy: ESP-Easy-2/control?cmd=GPIO,12
source: room_temperature
target: Kennel1 Adults

driver: heater_dogs2
espeasy: ESP-Easy-3/control?cmd=GPIO,12
target: Kennel1 Room

driver: heater_dogs3
espeasy: ESP-Easy-4/control?cmd=GPIO,12
target: Kennel1 Puppies

driver: heater_dogs4
espeasy: ESP-Easy-5/control?cmd=GPIO,12
target: Kennel2 ESP

driver: heater_dogs5
espeasy: ESP-Easy-6/control?cmd=GPIO,12
target: Kennel2 Room

driver: heater_dogs6
espeasy: ESP-Easy-7/control?cmd=GPIO,12
target: Kennel2 Puppies

driver: heater_observatory
espeasy: ESP-Easy-8/control?cmd=GPIO,12
target: Observatory

#endif

////////////////////////////////////////////////////////////////////

#define DRIVER_ESPEASY_UPDATE_GPIO          "curl http://%s,%d"

////////////////////////////////////////////////////////////////////

static void driver_update_state( home_data_t * home_data, driver_t * driver )
{
    if( driver->type == Driver_EspEasy )
    {
        string_t * command = string_sprintf( DRIVER_ESPEASY_UPDATE_GPIO, driver->command, driver->current_state & 0x01 );
        string_t * ret = background_spawn( string_get_char_buffer( command ) );
        
        string_destroy( command );
        string_destroy( ret );
    }
}

bool_t driver_get( home_data_t * home_data, driver_t ** driver_data )
{
    GET_ITEM_FROM_LIST(driver_t, home_data->driver_list, driver_data);
}

void driver_process( home_data_t * home_data )
{
    int i;
    driver_t * driver = NULL;
    
    while( driver_get( home_data, &driver ) == TRUE )
    {
        uint32_t driver_bitmask = 0;
        
        for( i = 0; i < DRIVER_MAX_ROOMS; i++ )
        {
            room_data_t * room = driver->room_list[i];
            if( room == NULL ) break;
            
            valve_t * valve = valve_locate_from_room( home_data, room->name );
            if( valve != NULL )
            {
                if( valve->valve_pos != ( uint8_t )NEG_U32 )
                {
                    // this is a room with valve, read the status and take decision
                    if( ( ( driver->current_state == TRUE ) && ( valve->valve_pos > ( valve->pos_threshold - valve->pos_offset ) ) ) ||
                        ( ( driver->current_state == FALSE ) && ( valve->valve_pos < ( valve->pos_threshold + valve->pos_offset ) ) ) )
                    {
                        // this room cannot change the state
                        driver_bitmask |= ( 1 << i );
                    }
                }
                else
                {
                    // this room cannot change the state
                    driver_bitmask |= ( 1 << i );
                }
            }
            else
            {
                thermometer_t * thermometer = thermometer_locate_from_room( home_data, room->name );
                if( thermometer != NULL )
                {
                    // this is a room controlled by thermometer, check the temperature and target
                    int target_temperature = 0;
                    if( ( room_get_target_temperature( room, &target_temperature ) == TRUE ) && ( room->bitmask & ROOM_VALID_TEMPERATURE ) )
                    {
                        if( ( ( ( driver->current_state == TRUE ) && ( target_temperature > (int)room->temperature ) ) ||
                              ( ( driver->current_state == FALSE ) && ( target_temperature < (int)room->temperature ) ) ) &&
                            ( thermometer->is_updated == TRUE ) )
                        {
                            // this room cannot change the state
                            driver_bitmask |= ( 1 << i );
                        }
                    }
                    else
                    {
                        driver_bitmask |= ( 1 << i );
                    }
                }
            }
        }
        
        //printf( "Bitmask %s: %04x\r\n", driver->name, driver_bitmask );
        
        if( driver_bitmask == 0 )
        {
            // there is no room that cannot change the state, so change it
            driver->current_state = driver->current_state ? FALSE : TRUE;
            driver_update_state( home_data, driver );
        }
    }
}

bool_t driver_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    if( string_locate_content( line, DRIVER_HEADER ) != 0 ) return FALSE;
    
    driver_t * new_driver = ( driver_t * )settings_create_item( line, DRIVER_HEADER, sizeof( driver_t ) );
    if( new_driver == NULL ) return FALSE;
    
    int target_cnt = 0;
    
    while( 1 )
    {
        string_t * driver_line = settings_get_line_string( fp );
        if( driver_line == NULL ) break;
        
        string_t * s_param = NULL;
        if( ( s_param = settings_locate_param( driver_line, ESPEASY_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_EspEasy;
            strcpy( new_driver->command, string_get_char_buffer( s_param ) );
        }
        else if( ( s_param = settings_locate_param( driver_line, TIMA_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_Tima;
            strcpy( new_driver->command, string_get_char_buffer( s_param ) );
        }
        else if( ( s_param = settings_locate_param( driver_line, LOCAL_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_Local;
            strcpy( new_driver->command, string_get_char_buffer( s_param ) );
        }
        else if( ( ( s_param = settings_locate_param( driver_line, TARGET_PARAM ) ) != NULL ) && ( target_cnt < ( DRIVER_MAX_ROOMS - 1 ) ) )
        {
            room_data_t * room = room_locate(home_data, string_get_char_buffer( s_param ) );
            if( room != NULL )
            {
                new_driver->room_list[target_cnt] = room;
                target_cnt++;
            }
        }
        
        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( driver_line );
    }
    
    if( ( new_driver->type != Driver_None ) && ( target_cnt > 0 ) )
    {
        list_insert_tail( &home_data->driver_list, &new_driver->node );
    }
    else
    {
        MFREE( new_driver );
    }
    
    return TRUE;
}

void driver_save( home_data_t * home_data, FILE * fp )
{
    driver_t * search = ( driver_t * )list_get_head( &home_data->driver_list );
    
    while( search != NULL )
    {
        fprintf( fp, "%s: %s\r\n", DRIVER_HEADER, search->name );
        
        if( search->type == Driver_Local ) fprintf( fp, "%s: %s\r\n", LOCAL_PARAM, search->command );
        else if( search->type == Driver_EspEasy ) fprintf( fp, "%s: %s\r\n", ESPEASY_PARAM, search->command );
        else if( search->type == Driver_Tima ) fprintf( fp, "%s: %s\r\n", TIMA_PARAM, search->command );
        
        int i;
        for( i = 0; i < DRIVER_MAX_ROOMS; i++ )
        {
            if( search->room_list[i] == NULL ) break;
            fprintf( fp, "%s: %s\r\n", TARGET_PARAM, search->room_list[i]->name );
        }
        
        fprintf( fp, "\r\n" );
        search = ( driver_t * )list_get_next( &home_data->driver_list, &search->node );
    }
}


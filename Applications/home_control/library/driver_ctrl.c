#include "driver_ctrl.h"
#include "settings.h"
#include "background.h"

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

curl http://192.168.1.201/control?cmd=GPIO,12,1

#endif

////////////////////////////////////////////////////////////////////

#define DRIVER_ESPEASY_UPDATE_GPIO          "curl http://%s,%d"

////////////////////////////////////////////////////////////////////

static void driver_update_state( driver_t * driver )
{
    if( driver->type == Driver_EspEasy )
    {
        string_t * command_call = string_sprintf( DRIVER_ESPEASY_UPDATE_GPIO, driver->command, driver->current_state & 0x01 );
        string_t * ret = background_spawn( string_get_char_buffer( command_call ) );
        
        string_destroy( command_call );
        string_destroy( ret );
    }
}

bool_t driver_get( home_data_t * home_data, driver_t ** driver_data )
{
    GET_ITEM_FROM_LIST(driver_t, home_data->driver_list, driver_data);
}

driver_t * driver_locate( home_data_t * home_data, const char * name )
{
    driver_t * data = NULL;
    
    while( driver_get( home_data, &data ) == TRUE )
    {
        if( !strcmp( name, data->name ) )
        {
            break;
        }
    }
    
    return data;
}

void driver_set_state( driver_t * driver, bool_t state )
{
    if( driver->current_state != state )
    {
        driver->current_state = state;
        driver_update_state( driver );
    }
}

bool_t driver_get_state( home_data_t * home_data, const char * name )
{
    driver_t * driver = NULL;

    while( driver_get( home_data, &driver ) == TRUE )
    {
        if( !strcmp( name, driver->name ) )
        {
            return driver->current_state;
        }
    }

    return FALSE;
}

void driver_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    /*
     * driver: boiler_hw
     * espeasy: ESP-Easy-1/control?cmd=GPIO,12
     */
    if( string_locate_content( line, DRIVER_HEADER ) != 0 ) return;
    
    driver_t * new_driver = ( driver_t * )settings_create_item( line, DRIVER_HEADER, sizeof( driver_t ) );
    if( new_driver == NULL ) return;
    new_driver->type = Driver_None;
    new_driver->delay_ms = 10;
    
    while( 1 )
    {
        string_t * driver_line = settings_get_line_string( fp );
        if( driver_line == NULL ) break;
        
        string_t * s_param = NULL;
        int temp_param = 0;

        if( ( s_param = settings_locate_param( driver_line, ESPEASY_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_EspEasy;
        }
        else if( ( s_param = settings_locate_param( driver_line, TIMA_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_Tima;
        }
        else if( ( s_param = settings_locate_param( driver_line, LOCAL_PARAM ) ) != NULL )
        {
            new_driver->type = Driver_Local;
        }
        else if( string_locate_content( driver_line, PARAM_DELAY_OFF ) == 0 )
        {
            s_param = settings_get_param( driver_line, PARAM_DELAY_OFF );
            settings_get_numbers( s_param, &temp_param, 1 );
            new_driver->delay_ms = ( uint32_t )temp_param * 1000;
        }

        if( new_driver->type != Driver_None )
        {
            strcpy( new_driver->command, string_get_char_buffer( s_param ) );
        }

        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( driver_line );
    }
    
    if( new_driver->type != Driver_None )
    {
        timer_Expire( &new_driver->delay_off );
        list_insert_tail( &home_data->driver_list, &new_driver->node );
    }
    else
    {
        MFREE( new_driver );
    }
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
        
        fprintf( fp, "\r\n" );
        search = ( driver_t * )list_get_next( &home_data->driver_list, &search->node );
    }
}


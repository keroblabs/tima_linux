#include "bluetooth.h"
#include "settings.h"
#include "background.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

#define ERROR_RESOURCE_BUSY             "resource busy"
#define NOTIFICATION_HANDLE_TEXT        "Notification handle"
#define VALUE_STR                       "value:"

#define EQIVA_HANDLER                   "0x0411"
#define EQIVA_READ_STATUS               "03"

#define XIAOMI_HANDLER                  "0x0010"
#define XIAOMI_READ_TEMPERATURE         "0100"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static uint8_t bluetooth_byte_to_num( string_t * string, uint8_t pos )
{
    uint8_t ret;
    
    ret = string_char_at( string, pos+1 );
    if( ret >= 0x61 ) ret = ( ret - 0x61 ) + 0x0A;
    else ret = ( ret - 0x30 );
    ret += ( ( string_char_at( string, pos ) & 0x0F ) << 4 );
    
    return ret;
}

static string_t * bluetooth_request_notification( home_data_t * home_data, const char * address, const char * handle, const char * value )
{
    string_t * ble_resp = NULL;
    
#ifdef MAKE_RPI
    
    string_t * ret = NULL;
    string_t * gatttool_command;
    int index;
    int retry = 2;
    
    while( retry )
    {
        gatttool_command = string_sprintf( "%s/read_ble.sh %s %s %s", string_get_char_buffer( home_data->root_dir ), address, handle, value );
        //printf( "%s\n", string_get_char_buffer( gatttool_command ) );
        ret = background_spawn( string_get_char_buffer( gatttool_command ) );
        string_destroy( gatttool_command );
        
        if( ret == NULL ) return NULL;
        
        //printf( "%s\n", string_get_char_buffer( ret ) );
        
        index = string_locate_content( ret, ERROR_RESOURCE_BUSY );
        if( index != -1 )
        {
            string_t * restart_command = string_sprintf( "%s/reset_ble.sh %s", string_get_char_buffer( home_data->root_dir ), address );
            string_t * restart_ret = background_spawn( string_get_char_buffer( restart_command ) );

            //printf( "%s\n", string_get_char_buffer( restart_ret ) );

            string_destroy( restart_command );
            string_destroy( restart_ret );
            string_destroy( ret );
            retry--;
            continue;
        }
        
        index = string_locate_content( ret, NOTIFICATION_HANDLE_TEXT );
        if( index == -1 )
        {
            string_destroy( ret );
            return NULL;
        }
        
        index = string_locate_content_ex( ret, index, VALUE_STR );
        if( index == -1 )
        {
            string_destroy( ret );
            return NULL;
        }
        
        index += strlen( VALUE_STR );
        ble_resp = string_get_substring( ret, index, NEG_U32 );
        string_trim( ble_resp );
        string_trail( ble_resp );
        string_destroy( ret );
        retry = 0;
    }
#endif
    
    return ble_resp;
}

bool_t bluetooth_eqiva_valve_read_status( home_data_t * home_data, const char * address, eqiva_status_t * eqiva_status )
{
    string_t * notification = bluetooth_request_notification( home_data, address, EQIVA_HANDLER, EQIVA_READ_STATUS );
    if( notification == NULL ) return FALSE;
    
    //printf( "%s\n", string_get_char_buffer( notification ) );
    // status: 02 01 08 23 04 2a
    
    eqiva_status->valve_pos = bluetooth_byte_to_num( notification, 9 );
    eqiva_status->temperature = bluetooth_byte_to_num( notification, 15 ) >> 1;
    eqiva_status->low_battery = ( bluetooth_byte_to_num( notification, 6 ) & 0x80 ) ? TRUE : FALSE;

    string_destroy( notification );

    return TRUE;
}

bool_t bluetooth_eqiva_set_temperature( home_data_t * home_data, const char * address, uint8_t temperature, eqiva_status_t * eqiva_status )
{
    string_t * value = string_sprintf( "41%02x", temperature << 1 );

    string_t * notification = bluetooth_request_notification( home_data, address, EQIVA_HANDLER, string_get_char_buffer( value ) );
    if( notification == NULL ) return FALSE;

    eqiva_status->valve_pos = bluetooth_byte_to_num( notification, 9 );
    eqiva_status->temperature = bluetooth_byte_to_num( notification, 15 ) >> 1;
    eqiva_status->low_battery = ( bluetooth_byte_to_num( notification, 6 ) & 0x80 ) ? TRUE : FALSE;

    string_destroy( value );
    string_destroy( notification );
    
    return TRUE;
}

uint8_t bluetooth_xiaomi_read_temperature( home_data_t * home_data, const char * address )
{
    uint8_t ret = 0;
    
    string_t * notification = bluetooth_request_notification( home_data, address, XIAOMI_HANDLER, XIAOMI_READ_TEMPERATURE );
    if( notification == NULL ) return 0xFF;

    ret = ( ( string_char_at( notification, 7 ) & 0x0F ) * 10 ) + ( string_char_at( notification, 10 ) & 0x0F );
    
    return ret;
}

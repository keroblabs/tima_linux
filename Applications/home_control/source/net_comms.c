#include "net_comms.h"
#include "t_threads.h"
#include "timer.h"
#include "socket_library.h"
#include "string_lib.h"
#include "temp_room.h"
#include "background.h"

////////////////////////////////////////////////////////////////////

#define RX_BUFFER_MAX_SIZE          128

#define COMMAND_ROOM_TEMPERATURE    "room_temperature"
#define COMMAND_ROOM_DETAILS        "room_details"
#define COMMAND_BOILER_CONTROL      "boiler_control"
#define COMMAND_WEATHER             "weather"
#define COMMAND_SERVICE_RESTART     "service_restart"

#define RESPONSE_ERROR_INVALID      "err_invalid"
#define RESPONSE_NO_ERROR           "ok"

#define COMMAND_CHECK(a, b)         (!strncmp( (a), (b), strlen((b))))

#define HTML_CONTROLLER_TELNET      50021
#define HTML_DEAMON_PORT            50022

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static void net_comms_deamon_connection_thread( home_data_t * home_data, uint32_t socket )
{
    bool_t is_run = TRUE;
    
    //printf( "net_comms_deamon_connection_thread\n" );

    char rx_buffer[RX_BUFFER_MAX_SIZE+1];
    
    string_t * command = string_create();
    string_t * response = NULL;
    
    while( is_run )
    {
        int read_size = socket_read( socket, ( uint8_t * )rx_buffer, RX_BUFFER_MAX_SIZE );
        if( read_size <= 0 ) break;
        
        rx_buffer[read_size] = 0;
        string_append_text( command, ( const char * )rx_buffer );
        
        if( string_locate_content( command, "\r\n" ) != -1 )
        {
            string_trail( command );
            uint32_t pos = 0;
            string_t * argv_1 = string_parse( command, &pos, " " );
            string_t * argv_2 = string_parse( command, &pos, " " );
            
            //printf( "%s %s\r\n", string_get_char_buffer( argv_1 ), string_get_char_buffer( argv_2 ) );

            if( !strcmp( string_get_char_buffer( argv_1 ), "display" ) )
            {
                if( !strcmp( string_get_char_buffer( argv_2 ), "room_temperature" ) )
                {
                    response = build_temperature_page( home_data );
                    //printf( "Done\r\n" );
                }
                else if( !strcmp( string_get_char_buffer( argv_2 ), "boiler_status" ) )
                {
                }
                else if( !strcmp( string_get_char_buffer( argv_2 ), "home_screen" ) )
                {
                }
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "details" ) )
            {
                response = build_room_page( home_data, string_get_char_buffer( argv_2 ) );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "graph" ) )
            {
                response = build_graph_page( home_data, string_get_char_buffer( argv_2 ) );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "setup" ) )
            {
                response = build_room_page( home_data, string_get_char_buffer( argv_2 ) );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "sensor" ) )
            {
                // GET /update_sensor.php?cmd=details_computer_room&field=Humidity&value=65.70 HTTP/1.1
                // GET /update_sensor.php?cmd=details_computer_room&field=Temperature&value=22.40 HTTP/1.1
                // GET /update_sensor.php?cmd=Switch&field=Pushbutton&value=0 HTTP/1.1

                // "sensor" <cmd> <field> <value>
                string_t * argv_3 = string_parse( command, &pos, " " );
                string_t * argv_4 = string_parse( command, &pos, " " );

                if( !strcmp( string_get_char_buffer( argv_3 ), "Pushbutton" ) )
                {
                    background_update_pushbutton( home_data, string_get_char_buffer( argv_2 ), string_get_char_buffer( argv_4 ) );
                }
                else if( !strcmp( string_get_char_buffer( argv_3 ), "Temperature" ) )
                {
                    background_update_sensor( home_data, string_get_char_buffer( argv_2 ), string_get_char_buffer( argv_4 ) );
                }
                else if( !strcmp( string_get_char_buffer( argv_3 ), "Humidity" ) )
                {
                    background_update_humidity( home_data, string_get_char_buffer( argv_2 ), string_get_char_buffer( argv_4 ) );
                }

                string_destroy( argv_3 );
                string_destroy( argv_4 );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "set_repeater" ) )
            {
                // "set_repeater" <repeater_address> <device_address>
                string_t * argv_3 = string_parse( command, &pos, " " );
                settings_set_repeater( home_data, string_get_char_buffer( argv_2 ), string_get_char_buffer( argv_3 ) );
                string_destroy( argv_3 );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "get_status" ) )
            {
                // "get_status" <repeater_address> <device_address>
                if( !strcmp( string_get_char_buffer( argv_2 ), "valve" ) )
                {
                }
                else if( !strcmp( string_get_char_buffer( argv_2 ), "driver" ) )
                {
                }
            }
            if( response == NULL )
            {
                response = string_create_ex( RESPONSE_ERROR_INVALID );
            }
            
            string_destroy( argv_1 );
            string_destroy( argv_2 );

            socket_write_data( socket, ( uint8_t* )string_get_char_buffer( response ), string_length( response ) );
            tthread_sleep_ms( 100 );
            is_run = FALSE;
        }
    }
    
    string_destroy( command );
    
    if( response != NULL )
    {
        string_destroy( response );
    }
    
    socket_close_port( socket );
    //printf( "Disconnect\r\n" );
}

static void net_comms_deamon_thread( void * args )
{
    uint32_t listen_socket = SOCKET_FAIL_LISTEN;
    
    while( listen_socket == SOCKET_FAIL_LISTEN )
    {
        listen_socket = socket_listen_port( HTML_CONTROLLER_TELNET );
        tthread_sleep_ms( 2000 );
    }
    
    while( 1 )
    {
        uint32_t socket_accepted = socket_accept_port( listen_socket );
        if( ( socket_accepted != SOCKET_FAIL_LISTEN ) && ( socket_accepted != SOCKET_NOT_READY ) )
        {
            //printf( "Connect\r\n" );
            net_comms_deamon_connection_thread( ( home_data_t * )args, socket_accepted );
        }
    }
}

void net_comms_init( home_data_t * home_data )
{
    printf( "net_comms_init\n" );
    socket_library_init();
    tthread_create_ex( net_comms_deamon_thread, home_data );
}

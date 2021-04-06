#include "net_comms.h"
#include "t_threads.h"
#include "timer.h"
#include "socket_library.h"
#include "string_lib.h"
#include "sensor_ctrl.h"
#include "driver_ctrl.h"
#include "build_page.h"

////////////////////////////////////////////////////////////////////

#define RX_BUFFER_MAX_SIZE          128

#define COMMAND_ROOM_TEMPERATURE    "room_temperature"
#define COMMAND_ROOM_DETAILS        "room_details"
#define COMMAND_BOILER_CONTROL      "boiler_control"
#define COMMAND_WEATHER             "weather"
#define COMMAND_SERVICE_RESTART     "service_restart"

#define RESPONSE_ERROR_INVALID      "err_invalid"
#define RESPONSE_NO_ERROR           "ok"
#define REDIRECT_DISPLAY_PAGE       "<meta http-equiv=\"Refresh\" content=\"0; url=http://%s/display.php?name=switch_page\" />"
#define SYSTEM_WIFI_INET            "ifconfig %s | grep \'inet \'"

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
                if( home_data->page_handler != NULL )
                {
                    response = home_data->page_handler( home_data, argv_1, argv_2, command, &pos );
                    if( response == NULL )
                    {
                        response = string_create_ex( RESPONSE_NO_ERROR );
                    }
                    //printf( "%s\r\n", string_get_char_buffer(response) );
                }
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "setup" ) )
            {
                if( home_data->setup_handler != NULL )
                {
                    response = home_data->setup_handler( home_data, argv_1, argv_2, command, &pos );
                }
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "reload" ) )
            {
                printf( "Reload configuration\r\n" );
                settings_reload( home_data );
                response = string_create_ex( RESPONSE_NO_ERROR );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "driver" ) )
            {
                // "driver" <name> <value>
                printf( "%s\r\n", string_get_char_buffer(command) );
                driver_t * driver = driver_locate( home_data, string_get_char_buffer( argv_2 ) );
                if( driver )
                {
                    string_t * argv_3 = string_parse( command, &pos, " " );
                    bool_t new_value = ( bool_t )atof( string_get_char_buffer( argv_3 ) );
                    driver_set_state( driver, new_value );

                    string_t * ip_addr = net_comms_get_ip( "eth0" );
                    response = string_sprintf( REDIRECT_DISPLAY_PAGE, string_get_char_buffer( ip_addr ) );
                    string_destroy( ip_addr );
                    string_destroy( argv_3 );
                }
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "sensor" ) )
            {
                // GET /update_sensor.php?cmd=details_computer_room&field=Humidity&value=65.70 HTTP/1.1
                // GET /update_sensor.php?cmd=details_computer_room&field=Temperature&value=22.40 HTTP/1.1
                // GET /update_sensor.php?cmd=Switch&field=Pushbutton&value=0 HTTP/1.1
                // http://192.168.1.200/update_sensor.php?name=Switch_Light&field=Button&value=0
                // curl -X GET -G 'http://192.168.1.200/update_sensor.php' -d 'name=Switch_Light' -d 'field=Button' -d 'value=0'
                // curl http://192.168.1.201/control?cmd=GPIO,12,1
                // curl -X GET -G 'http://192.168.1.200/display.php' -d 'name=switch_table'

                // "sensor" <cmd> <field> <value>
                printf( "%s\r\n", string_get_char_buffer(command) );
                string_t * argv_3 = string_parse( command, &pos, " " );
                string_t * argv_4 = string_parse( command, &pos, " " );

                if( sensor_record_value( home_data, argv_2, argv_3, argv_4 ) == TRUE )
                {
                    response = string_create_ex( RESPONSE_NO_ERROR );
                }

                string_destroy( argv_3 );
                string_destroy( argv_4 );
            }
            else if( !strcmp( string_get_char_buffer( argv_1 ), "get_status" ) )
            {
                if( home_data->status_handler != NULL )
                    response = home_data->status_handler( home_data, argv_1, argv_2, command, &pos );
            }
            
            if( response == NULL )
            {
                response = string_create_ex( RESPONSE_ERROR_INVALID );
            }
            
            string_destroy( argv_1 );
            string_destroy( argv_2 );

            string_append_text( response, "\r\n" );

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

void net_comms_set_page_handler( home_data_t * home_data, comm_handler_t handler )
{
    home_data->page_handler = handler;
}

void net_comms_set_setup_handler( home_data_t * home_data, comm_handler_t handler )
{
    home_data->setup_handler = handler;
}

void net_comms_set_status_handler( home_data_t * home_data, comm_handler_t handler )
{
    home_data->status_handler = handler;
}

string_t * net_comms_get_ip( char * interface )
{
    char out_buffer[128];
    char inet_command[128];
    string_t * inet_result;
    FILE * fp;

    sprintf( inet_command, SYSTEM_WIFI_INET, interface );

    fp = popen( inet_command, "r" );
    if( fp == NULL ) return NULL;

    inet_result = string_create();
    memset( out_buffer, 0x00, sizeof( out_buffer ) );

    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        string_append_text( inet_result, out_buffer );
    }

    pclose( fp );

    string_trim( inet_result );

    if( string_locate_content( inet_result, "inet" ) != -1 )
    {
        uint32_t pos = 5;
        string_t * ip_addr = string_parse( inet_result, &pos, " " );

        string_destroy( inet_result );
        inet_result = ip_addr;
    }

    // printf( "%s\n", string_get_char_buffer( inet_result ) );

    return inet_result;
}

void net_comms_init( home_data_t * home_data )
{
    printf( "net_comms_init\n" );

    string_t * ip_addr = net_comms_get_ip( "eth0" );
    if( ip_addr )
    {
        printf( "IP Address: %s\n", string_get_char_buffer( ip_addr ) );
        string_destroy( ip_addr );
    }

    socket_library_init();
    tthread_create_ex( net_comms_deamon_thread, home_data );
}

#include "system.h"
#include "device.h"
//#include "debug.h"

#include "tima_libc.h"
#include "pipe.h"
#include "timer.h"

///////////////////////////////////////////////////////////////////////////

#define CONNECT_TIMEOUT					25000

#define SOCKET                  		int

#define ESP8266_TTY						"/dev/tty5"
#define ESP8266_BAUDRATE				115200

#define ESP8266_LISTEN_SOCKET			0x1A
#define ESP8266_NO_SOCKET				0x1B

#define ESP8266_MAX_SOCKETS				5
#define ESP8266_BUFFER_SIZE				1024
#define ESP8266_TEMP_SIZE				32

#define ESP8266_MODE_NORMAL             ( WIFI_MODE_IDLE | \
								          WIFI_MODE_READY | \
										  WIFI_MODE_CONNECTED | \
										  WIFI_MODE_SENDING_CMD | \
										  WIFI_MODE_GET_IP_RESULT )

#define ESP8266_SEND_AT(a)				device_write_buffer( uart_drv, a, strlen( a ) ); \
							    		device_write_buffer( uart_drv, esp8266_new_line, strlen( esp8266_new_line ) );

#define WIFI_DATA(a)					(&socket_list[((a)-1)&0x07])

///////////////////////////////////////////////////////////////////////////

enum
{
	WIFI_MODE_DISABLED      = 0x00,

	WIFI_MODE_IDLE          = 0x01,
	WIFI_MODE_READY         = 0x02,
	WIFI_MODE_CONNECTED     = 0x04,
	WIFI_MODE_SENDING_CMD   = 0x08,
	WIFI_MODE_GET_IP_RESULT = 0x10,

	WIFI_MODE_SCAN_RESULT   = 0x20,
	WIFI_MODE_INCOMING_DATA = 0x40,
};

enum
{
	WIFI_SOCKET_CLOSED,
	WIFI_SOCKET_CLIENT,
	WIFI_SOCKET_LISTEN,
	WIFI_SOCKET_OPEN,
};

///////////////////////////////////////////////////////////////////////////

typedef struct socket_wifi_t_
{
	pipe_data_t rcvr_pipe;

	uint8_t index;
	uint8_t state;
	uint16_t size;
	uint16_t count;

	uint8_t * buffer;

} socket_wifi_t;

///////////////////////////////////////////////////////////////////////////

static device_t * uart_drv;

static char cmd_buffer[50];
static uint8_t rx_buffer[ESP8266_BUFFER_SIZE+1];
static uint16_t rx_count;

static bool_t is_send_cmd;
static uint16_t eol_code;
static uint8_t wifi_mode;

static pipe_data_t esp8266_cmd_pipe;
static pipe_data_t esp8266_send_pipe;

static timer_data_t esp8266_connect_timer;
static timer_data_t esp8266_delay_timer;

static socket_wifi_t * rx_socket;
static socket_wifi_t socket_list[ESP8266_MAX_SOCKETS];

static uint8_t ip_connected[4];
static uint8_t wifi_mac_addr[6];

static const char esp8266_new_line[] = { 0x0d, 0x0a, 0x00 };

///////////////////////////////////////////////////////////////////////////

static int esp8266_cmd_printk( const char *fmt, ... )
{
    va_list args;
    int printed_len;
    
    /* Emit the output into the temporary buffer */
    va_start(args, fmt);
    printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args);
    va_end(args);
    
    pipe_send_buffer( &esp8266_cmd_pipe, (uint8_t *)vsf_printk_buf, strlen(vsf_printk_buf)+1 );
    
    return printed_len;
}

static void esp8266_parse_response( void )
{
	if( ( rx_buffer[0] >= '0' ) && ( rx_buffer[0] <= '9' ) && ( rx_buffer[1] == ',' ) )
	{
		if( !strncmp( (char *)&rx_buffer[2], "CONNECT", 7 ) )
		{
			// connect indication
			if( WIFI_DATA(rx_buffer[0]+1)->state == WIFI_SOCKET_CLIENT )
			{
				WIFI_DATA(rx_buffer[0]+1)->state = WIFI_SOCKET_OPEN;
			}
			else
			{
				WIFI_DATA(rx_buffer[0]+1)->state = WIFI_SOCKET_LISTEN;
			}
		}
		else if( !strncmp( (char *)&rx_buffer[2], "CLOSED", 6 ) )
		{
			// disconnect indication
			WIFI_DATA(rx_buffer[0]+1)->state = WIFI_SOCKET_CLOSED;
		}
	}
	else if( !strncmp( (char *)&rx_buffer[0], "ready", 5 ) )
	{
		// module is ready
		wifi_mode |= WIFI_MODE_READY;
		timer_Start( &esp8266_connect_timer, CONNECT_TIMEOUT );
	}
	else if( !strncmp( (char *)&rx_buffer[0], "WIFI CONNECTED", 14 ) )
	{
		// module connected to AP
	}
	else if( !strncmp( (char *)&rx_buffer[0], "WIFI GOT IP", 11 ) )
	{
		// module got IP assigned by AP
		wifi_mode |= WIFI_MODE_CONNECTED;
		timer_Expire( &esp8266_connect_timer );
	}
	else if( !strncmp( (char *)&rx_buffer[0], "OK", 2 ) )
	{
		// success response
	}
	else if( !strncmp( (char *)&rx_buffer[0], "ERROR", 5 ) )
	{
		// error response
	}
	else if( !strncmp( (char *)&rx_buffer[0], "SEND OK", 7 ) )
	{
		// send ok
	}
	else if( !strncmp( (char *)&rx_buffer[0], "SEND FAIL", 9 ) )
	{
		// send fail
	}
	else if( !strncmp( (char*)&rx_buffer[0], "STAIP", 5 ) )
	{
		uint8_t cnt;
		uint8_t index = 0;

		memset( ip_connected, 0x00, sizeof( ip_connected ) );

		for( cnt = 0; cnt < 20; cnt++ )
		{
			if( rx_buffer[7+cnt] == '.' ) index++;
			if( rx_buffer[7+cnt] == '\"' ) break;

			ip_connected[index] = (ip_connected[index]*10) + (rx_buffer[7+cnt]&0x0F);
		}
	}
	else if( !strncmp( (char*)&rx_buffer[0], "STAMAC", 6 ) )
	{
		uint8_t cnt;
		uint8_t index = 0;

		memset( wifi_mac_addr, 0x00, sizeof( wifi_mac_addr ) );

		for( cnt = 0; cnt < 20; cnt++ )
		{
			if( rx_buffer[7+cnt] == ':' ) index++;
			if( rx_buffer[7+cnt] == '\"' ) break;

			wifi_mac_addr[index] = (ip_connected[index]<<8) + (rx_buffer[7+cnt]&0x0F);
			if( (rx_buffer[7+cnt] >= 'a') && (rx_buffer[7+cnt] <= 'f') )
			{
				ip_connected[index] += 10;
			}
		}
	}
}

static void esp8266_process_scan_result( void )
{
	//uint8_t rx_byte;

	//if( wifi_mode != WIFI_MODE_SCAN_RESULT ) return;
}

static void esp8266_process_incoming_data( void )
{
	uint32_t rx_size;
    
	if( !( wifi_mode & WIFI_MODE_INCOMING_DATA )) return;

	while( device_is_rx_pending( uart_drv ) )
	{
		rx_size = device_read_buffer( uart_drv, &rx_socket->buffer[rx_socket->count], rx_socket->size );
		rx_socket->size -= rx_size;
		rx_socket->count += rx_size;

		if( rx_socket->size == 0 )
		{
			// send received data
			pipe_send_buffer( &rx_socket->rcvr_pipe, rx_socket->buffer, rx_socket->count );
			pipe_release_buffer( rx_socket->buffer );
			wifi_mode &= ~WIFI_MODE_INCOMING_DATA;
		}
	}
}

static void esp8266_process_idle( void )
{
	uint8_t rx_byte;
	uint8_t cnt;
	uint8_t index;
	uint8_t * send_buffer;
	uint16_t size;

	if( wifi_mode & ~ESP8266_MODE_NORMAL ) return;

	while( device_is_rx_pending( uart_drv ) )
	{
		rx_byte = device_read( uart_drv );
		eol_code = ( eol_code << 8 ) | rx_byte;

		if( ( rx_count >= 8 ) && ( rx_count <= 10 ) && ( rx_buffer[0] == '+' ) && ( rx_byte == ':' ) )
		{
			// incoming indication (receive more data)
			if( !strncmp( (char *)&rx_buffer[1], "CWLAP", 5 ) )
			{
				// AP scan result
			}
			else if( !strncmp( (char *)&rx_buffer[1], "CIFSR", 5 ) )
			{
				// get IP result
				wifi_mode |= WIFI_MODE_GET_IP_RESULT;
                rx_buffer[0] = 0;
                rx_count = 0;
			}
			else if( !strncmp( (char *)&rx_buffer[1], "IPD", 3 ) )
			{
				// incoming data
				wifi_mode |= WIFI_MODE_INCOMING_DATA;
                rx_buffer[rx_count++] = rx_byte;
                
				index = rx_buffer[5] & 0x0F;
				rx_socket = WIFI_DATA(index+1);

				rx_socket->index = index;
				rx_socket->size = 0;
				rx_socket->count = 0;

				for( cnt = 0; cnt < 4; cnt++ )
				{
					if( rx_buffer[7+cnt] == ':' ) break;
					rx_socket->size = ( rx_socket->size * 10 ) + (rx_buffer[7+cnt] & 0x0F);
				}

				rx_socket->buffer = pipe_alloc_buffer( rx_socket->size );
                break;
			}
		}
		else if( ( rx_byte == ' ' ) && ( eol_code == 0x3e20 ) )
		{
			// ready to send data
			if( pipe_is_empty( &esp8266_send_pipe ) == FALSE )
			{
				send_buffer = pipe_read( &esp8266_send_pipe, &size );
				device_write_buffer( uart_drv, send_buffer, size );
				pipe_release_buffer( send_buffer );
                
                rx_buffer[0] = 0;
                rx_count = 0;
                
                wifi_mode &= ~WIFI_MODE_SENDING_CMD;
			}
		}
		else if( ( rx_byte == 0x0A ) && ( eol_code == 0x0d0a ) )
		{
			// process response
			esp8266_parse_response();
			rx_buffer[0] = 0;
			rx_count = 0;
            
			wifi_mode &= ~WIFI_MODE_GET_IP_RESULT;
            wifi_mode &= ~WIFI_MODE_SENDING_CMD;
		}
		else if( ( rx_byte >= 0x20 ) && ( rx_byte <= 0x7F ) )
		{
			rx_buffer[rx_count++] = rx_byte;
		}
	}

	if( ( wifi_mode & WIFI_MODE_CONNECTED ) &&
	   !( wifi_mode & WIFI_MODE_SENDING_CMD ) &&
	    timer_Check( &esp8266_delay_timer ) &&
        ( pipe_is_empty( &esp8266_cmd_pipe ) == FALSE ) )
	{
        timer_Reload( &esp8266_delay_timer );

        wifi_mode |= WIFI_MODE_SENDING_CMD;
        
        send_buffer = pipe_read( &esp8266_cmd_pipe, &size );
        
        strcpy( cmd_buffer, (char *)send_buffer );
        strcat( cmd_buffer, (char *)esp8266_new_line );
        
        device_write_buffer( uart_drv, ( uint8_t * )cmd_buffer, (uint32_t)strlen( cmd_buffer ) );
        
        pipe_release_buffer( send_buffer );
	}

	if( timer_Check( &esp8266_connect_timer ) )
	{
		timer_Stop( &esp8266_connect_timer );

		if( wifi_mode & WIFI_MODE_CONNECTED )
		{
			// it's connected,
		}
		else if( wifi_mode & WIFI_MODE_READY )
		{
			// it's not connected,
		}
	}
}

static void esp8266_process( void )
{
	if( uart_drv == NULL ) return;

	esp8266_process_idle();
	esp8266_process_scan_result();
	esp8266_process_incoming_data();
}

static void esp8266_global_init( void )
{
	wifi_mode = WIFI_MODE_DISABLED;
	uart_drv = NULL;

	memset( socket_list, 0x00, sizeof( socket_list ) );
}

///////////////////////////////////////////////////////////////////////////

static void esp8266_library_init( void )
{
	uint32_t baud = ESP8266_BAUDRATE;

	wifi_mode = WIFI_MODE_DISABLED;
	is_send_cmd = FALSE;

	uart_drv = device_open( ESP8266_TTY );
	if( uart_drv != NULL )
	{
		device_ioctrl( uart_drv, DEVICE_SET_CONFIG_DATA, &baud );
		wifi_mode |= WIFI_MODE_IDLE;

		pipe_init( &esp8266_send_pipe, "ESP8266_SEND_PIPE", MAX_PIPE_SIZE );
		pipe_init( &esp8266_cmd_pipe, "ESP8266_CMD_PIPE", MAX_PIPE_SIZE );

		DEBUG_PRINTK( "ESP8266 UART init\r\n" );

        // init
        esp8266_cmd_printk( "atE0" );		    // echo off
        esp8266_cmd_printk( "at+CWMODE=1" );  // station mode only
        esp8266_cmd_printk( "at+CIPMUX=1" );  // multiple connections
	    esp8266_cmd_printk( "at+CIFSR" );

        timer_Stop( &esp8266_connect_timer );
        timer_Start( &esp8266_delay_timer, 10 );
        timer_Expire( &esp8266_delay_timer );
	}
}

static void esp8266_close_port( uint32_t socket )
{
    if( socket < 1 ) return;
	if( WIFI_DATA(socket)->state != WIFI_SOCKET_OPEN ) return;

    esp8266_cmd_printk( "at+CIPCLOSE=%d", (socket-1)&0x07 );
}

static uint32_t esp8266_accept_port( uint32_t socket )
{
    uint8_t cnt;

    if( socket != ESP8266_LISTEN_SOCKET ) return SOCKET_FAIL_LISTEN;

    for( cnt = 0; cnt < ESP8266_MAX_SOCKETS; cnt++ )
    {
    	if( WIFI_DATA(cnt+1)->state == WIFI_SOCKET_LISTEN )
    	{
    		WIFI_DATA(cnt+1)->state = WIFI_SOCKET_OPEN;
    		return cnt+1;
    	}
    }

    return SOCKET_NOT_READY;
}

static uint32_t esp8266_connect_addr( uint8_t * ip_addr, uint16_t port )
{
	uint8_t cnt;

	for( cnt = 1; cnt <= ESP8266_MAX_SOCKETS; cnt++ )
	{
		if( WIFI_DATA(cnt)->state == WIFI_SOCKET_CLOSED )
		{
			WIFI_DATA(cnt)->state = WIFI_SOCKET_CLIENT;
		    esp8266_cmd_printk( "at+CIPSTART=%d,\"TCP\",\"%d.%d.%d.%d\",%d", cnt-1, ip_addr[0],
		    																	    ip_addr[1],
																					ip_addr[2],
																					ip_addr[3], port );
		    return cnt;
		}
	}

	return 0;
}

static uint32_t esp8266_connect_url( char * url_addr, uint16_t port )
{
	uint8_t cnt;

	for( cnt = 1; cnt <= ESP8266_MAX_SOCKETS; cnt++ )
	{
		if( WIFI_DATA(cnt)->state == WIFI_SOCKET_CLOSED )
		{
			WIFI_DATA(cnt)->state = WIFI_SOCKET_CLIENT;
		    esp8266_cmd_printk( "at+CIPSTART=%d,\"TCP\",\"%s\",%d", cnt-1, url_addr, port );
		    return cnt;
		}
	}

	return 0;
}

static uint32_t esp8266_listen_port( uint16_t port )
{
    esp8266_cmd_printk( "at+CIPSERVER=1,%d", port );
    return ( uint32_t )ESP8266_LISTEN_SOCKET;
}

static int esp8266_read_data( uint32_t socket, uint8_t *buffer, uint32_t max_size )
{
	uint32_t rx_size = 0;
	pipe_data_t * p_pipe;

	if( socket < 1 ) return 0;
	if( WIFI_DATA(socket)->state != WIFI_SOCKET_OPEN ) return 0;
	p_pipe = &WIFI_DATA(socket)->rcvr_pipe;

	if( pipe_is_empty( p_pipe ) == FALSE )
	{
		// rcvr_buffer
		rx_size = pipe_get_total_size( p_pipe );
		if( max_size > rx_size ) max_size = rx_size;

		if( buffer != NULL )
		{
			pipe_read_buffer( p_pipe, buffer, max_size );
		}
	}

	return rx_size;
}

static int esp8266_write_data( uint32_t socket, uint8_t *buffer, uint32_t size )
{
    if( socket < 1 ) return 0;

    if( ( WIFI_DATA(socket)->state == WIFI_SOCKET_CLIENT ) ||
    	( WIFI_DATA(socket)->state == WIFI_SOCKET_OPEN ) )
    {
        //DEBUG_PRINTK( "Sending data\r\n" );

        pipe_send_buffer( &esp8266_send_pipe, buffer, size );

        esp8266_cmd_printk( "at+CIPSEND=%d,%d", (socket-1)&0x0F, size );

        return (int)size;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////

static const device_socket_t esp8266_device_socket =
{
	esp8266_library_init,
    
	esp8266_listen_port,
	esp8266_connect_addr,
	esp8266_connect_url,
	esp8266_accept_port,

	esp8266_read_data,
	esp8266_write_data,

	esp8266_close_port,
	NULL,

	NULL
};

#if defined TIMA_OS
SYSTEM_DRIVER_DEFINE( device_socket_t, esp8266_device_socket, socket, "socket", NULL );
#else
device_socket_t * socket_driver = ( device_socket_t * )&esp8266_device_socket;
#endif

DECLARE_PROCESS_SECTION(esp8266_process);
DECLARE_INIT_POWERUP_SECTION(esp8266_global_init);


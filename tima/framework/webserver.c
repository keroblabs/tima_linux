#include "system.h"
#include "device.h"
#include "timer.h"
#include "file.h"
#include "efs.h"

#ifdef USE_MULTITHREAD
#include "t_threads.h"
#endif

#include "debug.h"
#include "tima_libc.h"
#include "string_lib.h"
#include "webserver.h"

///////////////////////////////////////////////////////////////

#define RX_BUFFER_SIZE				64
#define HTTP_REQUEST_MAX_SIZE       1024
#define HTTP_VERSION_MAX_SIZE       15
#define HTTP_CONNECTION_MAX_SIZE    50
#define WEBSERVER_BUFFER_SIZE       64

#define HTTP_TIMEOUT_MS				5000

///////////////////////////////////////////////////////////////

typedef struct _webserver_instance_t_
{
	device_t * dev_accept;
	string_t * http_request;
	string_t * http_version;
	string_t * conn_status;
	string_t * url_request;

	timer_data_t http_timeout;

	struct _webserver_instance_t_ * p_next;

} webserver_instance_t;

///////////////////////////////////////////////////////////////

extern const mime_list_t mime_list[];

static const char * response_fail_list[] =
{
    "The URL cannot be displayed",
    "Server under construction",
    "File cannot be displayed",
    "Path does not exist"
};

const char * m_err_dir_notfound = "<!DOCTYPE html><html><body><H2>Server under construction 3</H2><Br></body></html>";
const char * m_err_server_not_ready = "<h1>Server under construction</h1>";
const char * m_err_file_not_found = "<h1>File cannot be displayed</h1>";

const char * m_html_header = "<!DOCTYPE html><html><body>";
const char * m_html_footer = "</body></html>";

const char * m_mime_default = "application/octet-stream";
const char * m_mime_html = "text/html";
const char * m_mime_bmp = "image/bmp";

const char * m_status_send = "355 SEND";
const char * m_status_ok = "200 OK";
const char * m_status_not_found = "404 Not Found";

const char * m_server_name = "Tima System";

///////////////////////////////////////////////////////////////

static ptr_event_t http_request_event;
static uint8_t web_file_buffer[ WEBSERVER_BUFFER_SIZE + 1 ];
//static char web_file_buffer_ascii[ ( WEBSERVER_BUFFER_SIZE * 2 ) + 1 ];
static uint8_t rx_buffer[ RX_BUFFER_SIZE+1 ];
static device_t * dev_listen;
static webserver_instance_t * first_webserver;

///////////////////////////////////////////////////////////////

void webserver_process_instance( webserver_instance_t * p_instance );

///////////////////////////////////////////////////////////////

webserver_instance_t * _webserver_create_instance( void )
{
	webserver_instance_t * ret;

	ret = ( webserver_instance_t * )MMALLOC( sizeof( webserver_instance_t ) );
	if( ret == NULL ) return NULL;

	ret->http_request = string_create();

	ret->p_next = first_webserver;
	first_webserver = ret;
	return ret;
}

void _webserver_close_instance( webserver_instance_t * p_instance )
{
	webserver_instance_t * p_prev;
	webserver_instance_t * p_search;

	p_prev = NULL;
	p_search = first_webserver;

	while( p_search )
	{
		if( p_search == p_instance )
		{
			if( p_prev == NULL )
			{
				p_prev->p_next = p_instance->p_next;
			}
			else
			{
				first_webserver = p_instance->p_next;
			}

			string_destroy( p_instance->http_request );
			device_close( p_instance->dev_accept );
			MFREE( p_instance );
			break;
		}

		p_prev = p_search;
		p_search = p_instance->p_next;
	}
}

const char * _webserver_get_mime( char * filename )
{
    char * ext = strchr( filename, '.' );
    uint16_t counter;

    if( ext != NULL )
    {
        for( counter = 0; counter < 1024; counter++ )
        {
            if( mime_list[ counter ].extension == NULL ) break;

            // to speed up, check first character (after dot)
            if( mime_list[ counter ].extension[1] == ext[1] )
            {
                if( !strcmp( mime_list[ counter ].extension, ext ) )
                {
                    return mime_list[ counter ].mime_type;
                }
            }
        }
    }

    return m_mime_default;
}

bool_t webserver_send_file( char * path, const char * status, void * p_ptr )
{
	webserver_instance_t * p_instance = ( webserver_instance_t * )p_ptr;
    File * xfer_file;
    uint32_t rx_size;
    char * mime;

    // send file
    if( ( xfer_file = efs_fopen( path, FS_MODE_READ ) ) != NULL )
    {
        DEBUG_PRINTK( "Sending %s\r\n", path );

        mime = ( char * )_webserver_get_mime( path );
        webserver_send_header( efs_ioctrl( xfer_file, IO_CONTROL_FILE_SIZE, NULL ), status, mime, p_ptr );

        while( !efs_feof( xfer_file ) )
        {
            //memset( web_file_buffer_ascii, 0x00, sizeof( web_file_buffer_ascii ) );

            rx_size = efs_fread( web_file_buffer, WEBSERVER_BUFFER_SIZE, 1, xfer_file );
			device_write_buffer( p_instance->dev_accept, web_file_buffer, rx_size );
        }

        efs_fclose( xfer_file );

        return TRUE;
    }

    return FALSE;
}

void webserver_send_header( uint32_t resp_size, const char * status, const char * mime, void * p_ptr )
{
	webserver_instance_t * p_instance = ( webserver_instance_t * )p_ptr;
    string_t * header_obj;
    char resp_len_str[10];

    tima_itoa( resp_size, resp_len_str, 10 );

    header_obj = string_create();
	if( header_obj == NULL )
	{
		return;
	}

    string_append( header_obj, p_instance->http_version );
    string_append_text( header_obj, " " );
    string_append_text( header_obj, status );
    string_append_text( header_obj, "\r\n" );

    string_append_text( header_obj, "Server: " );
    string_append_text( header_obj, m_server_name );
    string_append_text( header_obj, "\r\n" );

    if( mime != NULL )
    {
        string_append_text( header_obj, "Content-Type: " );
        string_append_text( header_obj, mime );
        string_append_text( header_obj, "\r\n" );
    }

    string_append_text( header_obj, "Accept-Ranges: bytes\r\n" );
    string_append_text( header_obj, "Content-Length: " );
    string_append_text( header_obj, resp_len_str );
    string_append_text( header_obj, "\r\n" );

    string_append_text( header_obj, "\r\n" );

	device_write_buffer( p_instance->dev_accept, ( uint8_t* )string_get_char_buffer( header_obj ), string_length( header_obj ) );
	string_destroy( header_obj );
}

void webserver_send_fail_response( uint32_t resp_index, void * p_ptr )
{
	webserver_instance_t * p_instance = ( webserver_instance_t * )p_ptr;
    time_t time_now;
    string_t * resp;

    if( resp_index >= FAIL_INDEX_MAX ) resp_index = 0;

    resp = string_create();
    string_append_text( resp, m_html_header );

    string_append_text( resp, "<h1>" );
    string_append_text( resp, response_fail_list[ resp_index ] );
    string_append_text( resp, "</h1>" );

    string_append_text( resp, "<h3>" );
    time_now = timer_Now();
    string_append_text( resp, ( char * )ctime( &time_now ) );
    string_append_text( resp, "</h3>" );

    string_append_text( resp, m_html_footer );

	timer_Reload( &p_instance->http_timeout );
    webserver_send_header( string_length( resp ), m_status_not_found, m_mime_html, p_instance );
	device_write_buffer( p_instance->dev_accept, ( uint8_t* )string_get_char_buffer( resp ), string_length( resp ) );

    string_destroy( resp );
}

///////////////////////////////////////////////////////////////

void webserver_init( uint16_t port )
{
	first_webserver = NULL;
	http_request_event = NULL;

	dev_listen = device_socket_listen( port );
}

ptr_event_t webserver_set_handler( ptr_event_t new_event )
{
	ptr_event_t old_event;
	old_event = http_request_event;
	http_request_event = new_event;
	return old_event;
}

void webserver_process_instance( webserver_instance_t * p_instance )
{
	uint32_t rx_size;
	bool_t request_done = FALSE;
	char * http_request_str;
	uint32_t index;

	if( timer_Check( &p_instance->http_timeout ) )
	{
		timer_Expire( &p_instance->http_timeout );
		_webserver_close_instance( p_instance );
		return;
	}

	// receive http request
	if( ( rx_size = device_read_buffer( p_instance->dev_accept, rx_buffer, RX_BUFFER_SIZE ) ) > 0 )
	{
		timer_Reload( &p_instance->http_timeout );

		// append to request received
		rx_buffer[rx_size] = 0;
		string_append_text( p_instance->http_request, ( const char * )rx_buffer );

		// request size exceed
		if( string_length( p_instance->http_request ) > HTTP_REQUEST_MAX_SIZE )
		{
			string_clear( p_instance->http_request );
		}

		// received request
		if( string_locate_content( p_instance->http_request, "\r\n\r\n" ) != -1 )
		{
			request_done = TRUE;
		}
	}

	while( request_done == TRUE )
	{
        // parse request
        http_request_str = string_get_char_buffer( p_instance->http_request );

        // get HTTP version
        index = string_locate_content( p_instance->http_request, "HTTP" );
        if( index == -1 ) break;
        string_destroy( p_instance->http_version );
        p_instance->http_version = string_get_substring( p_instance->http_request, index, HTTP_VERSION_MAX_SIZE );
        DEBUG_PRINTK( "Version = %s\r\n", string_get_char_buffer( p_instance->http_version ) );

		index = string_locate_content( p_instance->http_version, "\r\n" );
        if( index == -1 ) break;
        string_delete( p_instance->http_version, index, NEG_U32 );

        // get connection status
        index = string_locate_content( p_instance->http_request, "Connection:" );
        if( index != -1 )
        {
            // Connection:
            // 123456789012
            p_instance->conn_status = string_get_substring( p_instance->http_request, index + 12, HTTP_CONNECTION_MAX_SIZE );
            index = string_locate_content( p_instance->conn_status, "\r\n" );
            if( index == -1 ) break;
            string_delete( p_instance->conn_status, index, NEG_U32 );
            DEBUG_PRINTK( "CONN = %s\r\n", string_get_char_buffer( p_instance->conn_status ) );
        }

        if( ( index = string_locate_content( p_instance->http_request, "GET" ) ) != -1 )
        {
            // GET handler
            p_instance->url_request = string_get_substring( p_instance->http_request, index + 4, NEG_U32 );
            index = string_locate_content( p_instance->url_request, " " );
            if( index == -1 ) break;
            string_delete( p_instance->url_request, index, NEG_U32 );

			request_done = FALSE;
            DEBUG_PRINTK( "URL = %s\r\n", string_get_char_buffer( p_instance->url_request ) );

            // send default response
            if( http_request_event == NULL )
            {
                webserver_send_fail_response( FAIL_SERVER_NOT_READY, p_instance );
            }
            else
            {
                http_request_event( p_instance, p_instance->url_request );
            }

            string_destroy( p_instance->url_request );
            string_destroy( p_instance->conn_status );
            string_destroy( p_instance->http_version );

            string_clear( p_instance->http_request );
        }
	}
}

void webserver_process( void )
{
	device_t * dev_accept;
	webserver_instance_t * p_instance;
	webserver_instance_t * p_next;

	if( dev_listen == NULL ) return;

	if( ( dev_accept = device_socket_accept( dev_listen ) ) != NULL )
	{
		p_instance = _webserver_create_instance();
		p_instance->dev_accept = dev_accept;
		timer_Start( &p_instance->http_timeout, HTTP_TIMEOUT_MS );
	}

	p_instance = first_webserver;

	while( p_instance != NULL )
	{
		p_next = p_instance->p_next;
		webserver_process_instance( p_instance );
		p_instance = p_next;
	}
}


#include "system.h"
#include "device.h"
#include "types.h"

#ifdef DEBUG_LOG_FILE
#include "vm_debug.h"
#endif

///////////////////////////////////////////////////////////////////////////

#define CONSOLE_THREAD_STACK_SIZE       1024
#define CONSOLE_BUFFER_SIZE             256

///////////////////////////////////////////////////////////////////////////

#ifdef WANT_INPUT_CONSOLE
static uint8_t          console_thread_stack[ CONSOLE_THREAD_STACK_SIZE ];
static uint8_t          console_rx_buffer[ CONSOLE_BUFFER_SIZE ];
static buffer_data_t   	console_buffer_data;
static thread_data_t    console_thread;
#endif

#ifdef DEBUG_LOG_FILE
void platform_write_log( char * log_line )
{
	FILE * fp;
	fp = fopen( DEBUG_LOG_FILE, "a+" );
	if( fp == NULL ) return;

	fputs( log_line, fp );
	fclose( fp );
}
#endif

#ifdef DEBUG_LOG_FILE
void platform_create_log( void )
{
	FILE * fp;
	fp = fopen( DEBUG_LOG_FILE, "w" );
	if( fp == NULL ) return;

	fputs( "New log file", fp );
	fclose( fp );
}
#endif

///////////////////////////////////////////////////////////////////////////

static uint32_t console_output( uint32_t index, uint8_t * text, uint32_t size )
{
    DI();
	printf( "%s", (char*)text );
    EI();
    
    return size;
}

static uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    #ifdef WANT_INPUT_CONSOLE
    return ( int )buffer_read_buffer( &console_buffer_data, buffer, ( uint16_t )size );
    #else
    return 0;
    #endif
}

#ifdef WANT_INPUT_CONSOLE
static void console_input_process( void * args )
{
    int char_in;
    int eof;
	
    while( 1 )
    {
        SYSTEM_EVENTS();

        // receive data
        eof = feof(stdin);
        if( eof )
        {
            char_in = fgetc(stdin);
            buffer_write( &console_buffer_data, ( uint8_t )char_in );            
        }
    }
}
#endif

static void console_drv_init( uint32_t index )
{
    #ifdef WANT_INPUT_CONSOLE
    buffer_init( &console_buffer_data, console_rx_buffer, CONSOLE_BUFFER_SIZE );
	thread_create( &console_thread, console_input_process, NULL, console_thread_stack, CONSOLE_THREAD_STACK_SIZE );
    #endif
}

static void console_drv_close( uint32_t index )
{
}

//static void console_drv_trig_tx( uint32_t index )
//{
//}

static bool_t validate( uint32_t index )
{
    if( index == 39 ) return TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const device_data_t console_tty_device =
{
    "tty*",
    &_in_use,
    
    console_drv_init,
    console_drv_close,
    NULL,
    validate,
    NULL,
    NULL,
    NULL,
    
    DEV_MODE_CHANNEL,
    
    console_input,
    console_output,
    
};

DECLARE_DEVICE_SECTION( console_tty_device );

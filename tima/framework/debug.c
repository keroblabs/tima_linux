#include "system.h"
#include "serial_driver.h"
#include "tima_libc.h"

#if defined USE_SERIAL_PRINTF

///////////////////////////////////////////////////////////////

static device_t dev_debug;
static int dev_init_ret;

///////////////////////////////////////////////////////////////

void debug_init( void )
{
	dev_init_ret = serial_open_device( DEV_PRINTK, &dev_debug, 115200 );
}

int debug_printk( const char *fmt, ... )
{
    va_list args;
    int printed_len;
    if( dev_init_ret != 0 ) return 0;
    
    /* Emit the output into the temporary buffer */
    va_start(args, fmt);
    printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args);
    va_end(args);
    
    return device_write_buffer( &dev_debug, ( uint8_t * )vsf_printk_buf, printed_len );
}

bool_t debug_read_input( char * out )
{
	if( dev_init_ret != 0 ) return FALSE;
	if( device_is_rx_pending( &dev_debug ) )
	{
		device_read_buffer( &dev_debug, ( uint8_t * )out, 1 );
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////

DECLARE_INIT_DEBUG_SECTION( debug_init );

#endif


#include "system.h"
#include "device.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <paths.h>
#include <termios.h>
#include <sysexits.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <sys/filio.h>

#include "types.h"

///////////////////////////////////////////////////////////////////////////

#define CONSOLE_THREAD_STACK_SIZE       1024
#define CONSOLE_BUFFER_SIZE             256

#define MAC_OS_TOTAL_PORTS              2

#define MAC_SERIAL_PORT0                "/dev/tty.usbserial-FTEP3OEA"
#define MAC_SERIAL_PORT1                "/dev/tty.SLAB_USBtoUART"

#ifndef MAC_INDEX_PORT0
#define MAC_INDEX_PORT0                 31
#endif

#ifndef MAC_INDEX_PORT1
#define MAC_INDEX_PORT1                 30
#endif

///////////////////////////////////////////////////////////////////////////

static int serial_fd[MAC_OS_TOTAL_PORTS+1];

static const char * mac_serial_port[MAC_OS_TOTAL_PORTS+1] = { "", MAC_SERIAL_PORT0, MAC_SERIAL_PORT1 };

///////////////////////////////////////////////////////////////////////////

static uint8_t console_get_index( uint32_t index )
{
    if( index == MAC_INDEX_PORT0 ) return 1;
    if( index == MAC_INDEX_PORT1 ) return 2;
    
    return 0;
}

static uint32_t console_output( uint32_t index, uint8_t * text, uint32_t size )
{
	//printf( text );
    
    index = console_get_index( index );
    write( serial_fd[index], text, size );
    return size;
}

static uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    int num_bytes_present;
    
    index = console_get_index( index );
    ioctl(serial_fd[index], FIONREAD, &num_bytes_present);
    
    if( ( num_bytes_present > 0 ) && ( buffer != NULL ) )
    {
        if( num_bytes_present > size ) num_bytes_present = size;
        read( serial_fd[index], buffer, num_bytes_present );
    }
    return ( uint32_t )num_bytes_present;
}

static void console_drv_close( uint32_t index )
{
    index = console_get_index( index );
    close(serial_fd[index]);
    serial_fd[index] = 0;
}

static void console_drv_init( uint32_t index )
{
    index = console_get_index( index );
 
    if( serial_fd[index] != 0 ) close( serial_fd[index] );
    serial_fd[index] = 0;
    
    serial_fd[index] = open(mac_serial_port[index], O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (serial_fd[index] == -1)
    {
        serial_fd[index] = 0;
        return;
    }
}

static void console_drv_set_baud( uint32_t index, uint32_t baud )
{
    struct termios options;

    index = console_get_index( index );
    
    if( serial_fd[index] == 0 ) return;
    
    fcntl(serial_fd[index], F_SETFL, 0);    // clear all flags on descriptor, enable direct I/O
    
    tcgetattr(serial_fd[index], &options);   // read serial port options
    
    // enable receiver, set 8 bit data, ignore control lines
    options.c_cflag |= (CLOCAL | CREAD | CS8);
    
    // disable parity generation and 2 stop bits
    options.c_cflag &= ~(PARENB | CSTOPB);
    
    options.c_ispeed = baud;
    options.c_ospeed = baud;
    
    // set the new port options
    tcsetattr(serial_fd[index], TCSANOW, &options);
}

static bool_t validate( uint32_t index )
{
    if( console_get_index( index ) ) return TRUE;
    return FALSE;
}

static uint32_t console_drv_ioctrl( uint32_t index, uint32_t param, void * data )
{
    uint32_t *p_baud;
    
	if( param == DEVICE_SET_CONFIG_DATA )
	{
		p_baud = ( uint32_t * )data;
        if( validate( index ) )
		{
			console_drv_set_baud( index, *p_baud );
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t console_device =
{
    "tty*",
    &_in_use,
    
    console_drv_init,
    console_drv_close,
    NULL,
    validate,
    NULL,
    console_drv_ioctrl,
    NULL,
    
    DEV_MODE_CHANNEL,
    
    console_input,
    console_output,
    
};

DECLARE_DEVICE_SECTION( console_device );


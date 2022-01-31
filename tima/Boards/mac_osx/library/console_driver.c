#include "system.h"
#include "device.h"
#include "types.h"

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

///////////////////////////////////////////////////////////////////////////

#define CONSOLE_THREAD_STACK_SIZE       1024
#define CONSOLE_BUFFER_SIZE             256
#define MAC_SERIAL_PORT                 "/dev/ttys004"

//"/dev/tty.usbserial-00001214"

///////////////////////////////////////////////////////////////////////////

static int serial_fd;

///////////////////////////////////////////////////////////////////////////

uint32_t console_output( uint32_t index, char * text, uint32_t size )
{
	//printf( text );
    write( serial_fd, text, size );
    return size;
}

uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    int num_bytes_present;
    
    ioctl(serial_fd, FIONREAD, &num_bytes_present);
    
    if( ( num_bytes_present > 0 ) && ( buffer != NULL ) )
    {
        if( num_bytes_present > size ) num_bytes_present = size;
        read( serial_fd, buffer, num_bytes_present );
    }
    return ( uint32_t )num_bytes_present;
}

void console_drv_close( uint32_t index )
{
    close(serial_fd);
}

void console_drv_init( uint32_t index )
{
    struct termios options;

    serial_fd = 0;
    
    serial_fd = open(MAC_SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1)
    {
        serial_fd = 0;
        return;
    }
    
    fcntl(serial_fd, F_SETFL, 0);    // clear all flags on descriptor, enable direct I/O
    
    tcgetattr(serial_fd, &options);   // read serial port options
    
    // enable receiver, set 8 bit data, ignore control lines
    options.c_cflag |= (CLOCAL | CREAD | CS8);
    
    // disable parity generation and 2 stop bits
    options.c_cflag &= ~(PARENB | CSTOPB);
    
    options.c_ispeed = 115200;
    options.c_ospeed = 115200;
    
    // set the new port options
    tcsetattr(serial_fd, TCSANOW, &options);
}

static bool_t validate( uint32_t index )
{
    if( index == 3 ) return TRUE;
    return FALSE;
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
    NULL,
    NULL,
    
    DEV_MODE_CHANNEL,
    
    console_input,
    console_output,
    
};

DECLARE_DEVICE_SECTION( console_device );

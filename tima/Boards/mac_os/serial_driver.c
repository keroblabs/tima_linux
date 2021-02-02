#include "serial_driver.h"
#include "t_threads.h"
#include "buffer.h"


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

////////////////////////////////////////////////////////////////////////////////////////

#define SERIAL_TOTAL_PORTS              2

#define SERIAL_PORT0                    "/dev/ttyUSB0"
#define SERIAL_PORT1                    "/dev/ttyUSB1"

////////////////////////////////////////////////////////////////////////////////////////

typedef struct serial_data_t_
{
    void * mutex;
    void * thread_rx;
    void * thread_tx;
    
    int serial_fs;
    
    buffer_data_t rx_buffer;
    buffer_data_t tx_buffer;
    
} serial_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static const char * tty_serial_port[SERIAL_TOTAL_PORTS+1] = { "", SERIAL_PORT0, SERIAL_PORT1 };

////////////////////////////////////////////////////////////////////////////////////////

void serial_rx_thread( void * args )
{
    serial_data_t * p_serial = ( serial_data_t * )args;
    uint8_t buffer[64];
    int read_size;
    int total_size;
    
    while( 1 )
    {
        total_size = (int)read( p_serial->serial_fs, buffer, 1 );
        
        if( total_size )
        {
            buffer_write( &p_serial->rx_buffer, buffer[0] );
            ioctl(p_serial->serial_fs, FIONREAD, &total_size);
        }

        while( total_size )
        {
            read_size = 64;
            if( total_size <= read_size ) read_size = total_size;
            
            read_size = (int)read( p_serial->serial_fs, buffer, read_size );
            buffer_write_buffer( &p_serial->rx_buffer, buffer, read_size );
            
            total_size -= read_size;
        }
    }
}

void serial_tx_thread( void * args )
{
    serial_data_t * p_serial = ( serial_data_t * )args;
    uint8_t buffer[32];
    int write_size;
    int total_size;

    while( 1 )
    {
        total_size = buffer_wait_for_data( &p_serial->tx_buffer, buffer, 32 );
        write_size = (int)write( p_serial->serial_fs, buffer, total_size );
    }
}

void * serial_open( uint8_t index, uint32_t baud )
{
    serial_data_t * ret;
    struct termios options;

    ret = ( serial_data_t * )MMALLOC( sizeof( serial_data_t ) );
    if( ret == NULL ) return NULL;
    
    ret->mutex = tthread_mutex_init();
    
    ret->serial_fs = open( tty_serial_port[index], O_RDWR | O_NOCTTY | O_NDELAY );
    if( ret->serial_fs == -1 )
    {
        MFREE( ret );
        return NULL;
    }
    
    fcntl(ret->serial_fs, F_SETFL, 0);    // clear all flags on descriptor, enable direct I/O
    tcgetattr(ret->serial_fs, &options);   // read serial port options
    
    // enable receiver, set 8 bit data, ignore control lines
    options.c_cflag |= (CLOCAL | CREAD | CS8);
    
    // disable parity generation and 2 stop bits
    options.c_cflag &= ~(PARENB | CSTOPB);
    
    options.c_ispeed = baud;
    options.c_ospeed = baud;
    
    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 5;
    
    // set the new port options
    tcsetattr(ret->serial_fs, TCSANOW, &options);
    
    buffer_init( &ret->rx_buffer, 256 );
    buffer_init( &ret->tx_buffer, 64 );
    
    ret->thread_rx = tthread_create_ex( serial_rx_thread, ret );
    ret->thread_tx = tthread_create_ex( serial_tx_thread, ret );

    return ret;
}

uint32_t serial_pending_rx( void * p_serial )
{
    serial_data_t * serial_data = ( serial_data_t * )p_serial;
    return buffer_get_size( &serial_data->rx_buffer );
}

uint32_t serial_receive( void * p_serial, uint8_t * buffer, uint32_t size )
{
    serial_data_t * serial_data = ( serial_data_t * )p_serial;
    return buffer_read_buffer( &serial_data->rx_buffer, buffer, size );
}

uint32_t serial_transmit( void * p_serial, uint8_t * buffer, uint32_t size )
{
    serial_data_t * serial_data = ( serial_data_t * )p_serial;
    buffer_write_buffer( &serial_data->tx_buffer, buffer, size );
    return size;
}

void serial_close( void * p_serial )
{
    serial_data_t * serial_data = ( serial_data_t * )p_serial;
    buffer_destroy( &serial_data->rx_buffer );
    buffer_destroy( &serial_data->tx_buffer );
    
    close( serial_data->serial_fs );
}

void serial_system_init( void )
{
}

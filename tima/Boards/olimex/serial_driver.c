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
#include <termios.h>
//#include <sys/filio.h>

////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////

void serial_rx_thread( void * args )
{
    serial_data_t * p_serial = ( serial_data_t * )args;
    uint8_t buffer[64];
    int read_size;
    int total_size;
    
    printf( "RX thread start\n" );

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

int serial_convert_baud( int input )
{
	if( input == 1200 ) return B1200;
	if( input == 2400 ) return B2400;
	if( input == 4800 ) return B4800;
	if( input == 9600 ) return B9600;
	if( input == 19200 ) return B19200;
	if( input == 38400 ) return B38400;
	if( input == 57600 ) return B57600;

	return B115200;
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

void * serial_open( const char * tty_name, uint32_t baud )
{
    serial_data_t * ret;
    struct termios options;

    ret = ( serial_data_t * )malloc( sizeof( serial_data_t ) );
    if( ret == NULL ) return NULL;
    
    ret->mutex = tthread_mutex_init();
    
    ret->serial_fs = open( tty_name, O_RDWR | O_NOCTTY );
    if( ret->serial_fs == -1 )
    {
    	printf( "Failed to open %s\r\n", tty_name );
        free( ret );
        return NULL;
    }
    
    fcntl(ret->serial_fs, F_SETFL, 0);    // clear all flags on descriptor, enable direct I/O
    //tcgetattr(ret->serial_fs, &options);   // read serial port options
    memset( &options, 0x00, sizeof( options ) );
    
    // enable receiver, set 8 bit data, ignore control lines
    // options.c_cflag |= (CLOCAL | CREAD | CS8);
    // options.c_cflag =  CRTSCTS | CS8 | CLOCAL | CREAD;
    options.c_cflag =  CS8 | CLOCAL | CREAD;
    
    options.c_oflag = 0;
    options.c_lflag = ICANON;

    // disable parity generation and 2 stop bits
    options.c_cflag &= ~(PARENB | CSTOPB);
    
    cfsetospeed (&options, serial_convert_baud(baud));
    cfsetispeed (&options, serial_convert_baud(baud));

    //options.c_ispeed = baud;
    //options.c_ospeed = baud;
    
    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 5;
    
    options.c_cc[VINTR]    = 0;     /* Ctrl-c */
    options.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    options.c_cc[VERASE]   = 0;     /* del */
    options.c_cc[VKILL]    = 0;     /* @ */
    options.c_cc[VEOF]     = 4;     /* Ctrl-d */
    options.c_cc[VTIME]    = 0;     /* inter-character timer unused */
    options.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
    options.c_cc[VSWTC]    = 0;     /* '\0' */
	options.c_cc[VSTART]   = 0;     /* Ctrl-q */
	options.c_cc[VSTOP]    = 0;     /* Ctrl-s */
	options.c_cc[VSUSP]    = 0;     /* Ctrl-z */
	options.c_cc[VEOL]     = 0;     /* '\0' */
	options.c_cc[VREPRINT] = 0;     /* Ctrl-r */
	options.c_cc[VDISCARD] = 0;     /* Ctrl-u */
	options.c_cc[VWERASE]  = 0;     /* Ctrl-w */
	options.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
	options.c_cc[VEOL2]    = 0;     /* '\0' */

    // set the new port options
	tcflush(ret->serial_fs, TCIFLUSH);
    tcsetattr(ret->serial_fs, TCSANOW, &options);
    
    buffer_init( &ret->rx_buffer, 1024 );
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


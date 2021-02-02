#include "serial_driver.h"
#include "t_threads.h"
#include "buffer.h"
#include "spawn_lib.h"

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
#include <stropts.h>
//#include <sys/filio.h>

////////////////////////////////////////////////////////////////////////////////////////

typedef struct serial_data_t_
{
    void * mutex;
    void * thread_rx;
    void * thread_tx;
    
    int serial_fs;
    char name[20];
    
    bool_t is_blocking;

    buffer_data_t rx_buffer;
    buffer_data_t tx_buffer;
    
} serial_data_t;

////////////////////////////////////////////////////////////////////////////////////////

#define SERIAL_MAX      10

////////////////////////////////////////////////////////////////////////////////////////

static serial_data_t serial_data_list[SERIAL_MAX];
static char serial_usb_list[SERIAL_MAX][20];

////////////////////////////////////////////////////////////////////////////////////////

static int serial_convert_baud( int input )
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

static void set_blocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            printf("error %d from tggetattr", errno);
            return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
            printf("error %d setting term attributes", errno);
}

static void set_interface_attribs (int fd, int speed)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        printf ("error %d from tcgetattr\r\n", errno);
        return;
    }

    cfsetospeed (&tty, serial_convert_baud(speed));
    cfsetispeed (&tty, serial_convert_baud(speed));

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    // tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf ("error %d from tcsetattr", errno);
        return;
    }
}

static void serial_rx_thread( void * args )
{
    serial_data_t * p_serial = ( serial_data_t * )args;
    uint8_t buffer[64];
    int read_size;
    int total_size;

    printf( "RX thread start: %s\n", p_serial->name );

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

static void serial_tx_thread( void * args )
{
    serial_data_t * p_serial = ( serial_data_t * )args;
    uint8_t buffer[32];
    int write_size;
    int total_size;

    printf( "TX thread start: %s\n", p_serial->name );

    while( 1 )
    {
        total_size = buffer_wait_for_data( &p_serial->tx_buffer, buffer, 32 );
        write_size = (int)write( p_serial->serial_fs, buffer, total_size );
    }
}

static uint32_t serial_rx_channel( uint32_t index, uint8_t * data, uint32_t size )
{
    serial_data_t * serial_data = ( serial_data_t * )&serial_data_list[index];

    if( data == NULL )
    {
        return buffer_get_size( &serial_data->rx_buffer );
    }

    if( serial_data->is_blocking == TRUE )
    {
        return buffer_wait_for_data( &serial_data->rx_buffer, data, size );
    }
    else
    {
        return buffer_read_buffer( &serial_data->rx_buffer, data, size );
    }
}

static uint32_t serial_tx_channel( uint32_t index, uint8_t * data, uint32_t size )
{
    serial_data_t * serial_data = ( serial_data_t * )&serial_data_list[index];
    buffer_write_buffer( &serial_data->tx_buffer, data, size );
    return size;
}

uint32_t serial_io_ctrl( uint32_t index, uint32_t param, void * value )
{
    serial_data_t * serial_data = ( serial_data_t * )&serial_data_list[index];

    if( param == DEVICE_BLOCKING_STATE )
    {
        bool_t * state = ( bool_t * )value;
        serial_data->is_blocking = *state;
    }
    return 0;
}

static void spawn_handler( void * data, const char * line )
{
    int usb_index = line[4] & 0x0F;
    strcpy( serial_usb_list[usb_index], "/dev/" );
    strcat( serial_usb_list[usb_index], &line[6] );

    while(serial_usb_list[usb_index][strlen(serial_usb_list[usb_index])-1] <= 0x20 )
    {
        serial_usb_list[usb_index][strlen(serial_usb_list[usb_index])-1] = 0;
    }
}

int serial_get_usb_path( int index, char * tty_name )
{
    if( index >= SERIAL_MAX ) return 0;

    memset( serial_usb_list, 0x00, sizeof( serial_usb_list ) );
    spawn_command_ex( "dmesg | grep ttyUSB | awk '{print $4 $10}'", spawn_handler, NULL );

    if( strlen( serial_usb_list[ index ] ) > 0 )
    {
        strcpy( tty_name, serial_usb_list[ index ] );
        return strlen( tty_name );
    }
    return 0;
}

int serial_open_device( const char * tty_name, device_t * device, uint32_t baud )
{
    int device_index = -1;

    for( int i = 0; i < SERIAL_MAX; i++ )
    {
        if( serial_data_list[i].serial_fs == -1 )
        {
            device_index = i;
            break;
        }
    }

    if( device_index == -1 ) return -1;

    serial_data_t * serial_data = ( serial_data_t * )&serial_data_list[device_index];
    memset( serial_data, 0x00, sizeof( serial_data_t ) );

    serial_data->mutex = tthread_mutex_init();

    serial_data->serial_fs = open( tty_name, O_RDWR | O_NOCTTY );
    if( serial_data->serial_fs == -1 )
    {
        printf( "Failed to open %s\r\n", tty_name );
        return -1;
    }

    strcpy( serial_data->name, tty_name );
    device_data_t * device_data = ( device_data_t * )malloc( sizeof( device_data_t ) );
    if( device_data == NULL )
    {
        printf( "Failed allocate %s\r\n", tty_name );
        close( serial_data->serial_fs );
        return -3;
    }
    memset( device_data, 0x00, sizeof( device_data_t ) );

    set_interface_attribs( serial_data->serial_fs, baud );
    set_blocking (serial_data->serial_fs, 0); // no blocking

    buffer_init( &serial_data->rx_buffer, 1024 );
    buffer_init( &serial_data->tx_buffer, 64 );

    serial_data->thread_rx = tthread_create_ex( serial_rx_thread, serial_data );
    serial_data->thread_tx = tthread_create_ex( serial_tx_thread, serial_data );

    device_data->dev_mode = DEV_MODE_CHANNEL;
    device_data->rx_channel = serial_rx_channel;
    device_data->tx_channel = serial_tx_channel;
    device_data->io_ctrl    = serial_io_ctrl;

    device->device_ptr = device_data;
    device->device_index = device_index;

    return 0;
}

void serial_system_init( void )
{
    for( int i = 0; i < SERIAL_MAX; i++ )
    {
        serial_data_list[i].serial_fs = -1;
    }
}

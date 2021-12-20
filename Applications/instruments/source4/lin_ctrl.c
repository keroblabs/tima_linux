#include "lin_ctrl.h"
#include "system.h"
#include "driving_data.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////

#define LIN_USB_DEV_INDEX       5
#define LIN_HEADER_SIZE         2
#define LIN_RESPONSE_MAX_SIZE   20
#define LIN_BAUD_RATE           4800

////////////////////////////////////////////////////////////////////

typedef struct lin_command_t
{
    uint8_t id;
    uint8_t * tx_buffer;
    uint16_t tx_size;
    //uint8_t response_buffer[LIN_RESPONSE_MAX_SIZE];
    //uint8_t * resp_pointer;

    pipe_data_t * rx_pipe;
    uint16_t resp_size;
} lin_command_t;

////////////////////////////////////////////////////////////////////

static const uint8_t lin_header[] = { 0x00, 0x55 };

////////////////////////////////////////////////////////////////////

static pipe_data_t cmd_pipe;

////////////////////////////////////////////////////////////////////

static uint8_t lin_checksum( uint8_t * buffer, uint16_t rx_size )
{
    uint16_t suma = 0;
    for( int i = 1; i < rx_size; i++ ) // skip break
    {
        suma = suma + buffer[i];
        //suma = suma + 1;
        if( suma >= 256 ) suma -= 255;
    }
    suma = 0xFF & ( ~suma );
    return (uint8_t)suma;
}

static void lin_ctrl_thread( void )
{
    timer_data_t serial_timeout;
    device_t serial_device;
    char dev_name[20];
    void * gpio_cslin;

    serial_get_usb_path( LIN_USB_DEV_INDEX, dev_name );

    printf( "LIN device: %s\n", dev_name );

    if( serial_open_device( dev_name, &serial_device, LIN_BAUD_RATE ) < 0 )
    {
        printf( "No LIN\n" );
        return;
    }
    bool_t blocking = TRUE;
    device_ioctrl( &serial_device, DEVICE_BLOCKING_STATE, &blocking );
    uint32_t timeout_ms = 50;
    device_ioctrl( &serial_device, DEVICE_SET_TIMEOUT, &timeout_ms );

    gpio_cslin = gpio_open_output( GPIO_PE01 );
    gpio_output( gpio_cslin, TRUE );

    while( 1 )
    {
        lin_command_t * lin_command = ( lin_command_t * )pipe_wait_for_data( &cmd_pipe, NULL );
        if( lin_command == NULL ) continue;

        uint8_t lin_buffer[20];
        uint16_t rx_index = 0;

        memcpy( &lin_buffer[rx_index], lin_header, LIN_HEADER_SIZE );
        rx_index += LIN_HEADER_SIZE;

        lin_buffer[rx_index++] = lin_command->id;

        if( lin_command->tx_size > 0 )
        {
            memcpy( &lin_buffer[rx_index], lin_command->tx_buffer, lin_command->tx_size );
            rx_index += lin_command->tx_size;
            MFREE( lin_command->tx_buffer );
        }

        if( lin_command->resp_size == 0 )
        {
            /* Checksum is calculated by master when there is no response */
            lin_buffer[rx_index++] = lin_checksum( lin_buffer, rx_index );
        }

        device_write_buffer( &serial_device, ( uint8_t * )lin_buffer, rx_index );
        tthread_sleep_ms( ( 10000 / LIN_BAUD_RATE ) * ( rx_index * 3 ) ); // Sleep a bit to wait for response.
        //uint16_t echo = device_is_rx_pending( &serial_device );

        uint32_t echo_count = device_read_buffer( &serial_device, ( uint8_t * )lin_buffer, rx_index ); // read lin echo back

        if( echo_count != rx_index )
        {
            printf( "LIN link error: %d %d\n", echo_count, rx_index );
        }

        if( ( lin_command->resp_size > 0 ) && ( echo_count == rx_index ) )
        {
            uint16_t rx_point = rx_index;
            uint16_t rx_size = 0;

            //printf( "size = %d\n", lin_command->resp_size );
            echo_count = device_read_buffer( &serial_device, ( uint8_t * )&lin_buffer[rx_index], lin_command->resp_size + 1 );
            //printf( "echo = %d\n", echo_count );
            if( echo_count >= lin_command->resp_size )
            {
                pipe_send_buffer( lin_command->rx_pipe, &lin_buffer[rx_point], lin_command->resp_size+1 );
            }

            tthread_sleep_ms( ( 10000 / LIN_BAUD_RATE ) * ( 6 ) ); // Sleep a bit to wait for response.

            //if( lin_buffer[index] == lin_checksum( lin_buffer, index-1 ) )
            //{
            //
            //}

            while( device_is_rx_pending( &serial_device ) )
            {
                (void)device_read( &serial_device );
            }
        }

        //tthread_sleep_ms( 100 );

        MFREE( lin_command );
    }
}

void lin_ctrl_send_command( uint8_t id, uint8_t * buffer, uint16_t size, uint16_t resp_size, pipe_data_t * rx_pipe )
{
    lin_command_t lin_command;
    memset( &lin_command, 0x00, sizeof( lin_command_t ) );

    if( buffer != NULL )
    {
        lin_command.tx_buffer = ( uint8_t * )MMALLOC( size );
        if( lin_command.tx_buffer == NULL ) return;
        memcpy( lin_command.tx_buffer, buffer, size );
    }

    lin_command.id        = id;
    lin_command.tx_size   = size;
    lin_command.resp_size = resp_size;
    lin_command.rx_pipe   = rx_pipe;

    pipe_send_buffer( &cmd_pipe, ( uint8_t * )&lin_command, sizeof( lin_command_t ) );
}

void lin_ctrl_init( void )
{
    pipe_init( &cmd_pipe, "LIN_PIPE", MAX_PIPE_SIZE );
    tthread_create( lin_ctrl_thread );
}

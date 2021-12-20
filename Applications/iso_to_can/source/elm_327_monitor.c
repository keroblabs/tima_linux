#include "elm_327_monitor.h"
#include "system.h"

////////////////////////////////////////////////////////////////////

enum
{
    ELM_327_Idle,
    ELM_327_EnableHeader,
    ELM_327_Receiving
};

////////////////////////////////////////////////////////////////////

static const char elm_327_header_on[] = { 'a', 't', 'h', '1', 0x0d };
static const char elm_327_monitor_on[] = { 'a', 't', 'm', 'a', 0x0d };

////////////////////////////////////////////////////////////////////

static char elm_buffer[100];

static uint64_t rpm;
static uint16_t speed;
static uint8_t temp;
static uint8_t bitmask;
static uint8_t activity;
static uint8_t previous_activity;

static void * data_mutex;

////////////////////////////////////////////////////////////////////

static uint8_t val_to_num( char val )
{
    if( ( val >= '0' ) && ( val <= '9' ) ) return val & 0x0F;
    else if( ( val >= 'A' ) && ( val <= 'F' ) ) return ( val & 0x0F ) + 9;
    else if( ( val >= 'a' ) && ( val <= 'f' ) ) return ( val & 0x0F ) + 9;

    return 0;
}

static void ascii_to_buffer( char * buffer, uint8_t * data )
{
    int len = strlen( buffer );
    uint8_t index = 0;

    for( int i = 0; i < len; i += 3 )
    {
        data[index] = val_to_num( buffer[i] ) << 4;
        data[index] |= val_to_num( buffer[i+1] );
        index++;

        //if( buffer[i+2] == 0 ) break;
    }
}

static void decode_elm_327( uint8_t * data )
{
    tthread_mutex_lock( data_mutex );

    if( ( data[0] == 0xA1 ) && ( data[1] == 0x29 ) )
    {
        // speed
        speed = data[4];
        speed = ( speed << 8 ) | data[5];
    }
    else if( ( data[0] == 0x81 ) && ( data[1] == 0x1B ) )
    {
        // RPM
        rpm = data[4];
        rpm = ( rpm << 8 ) | data[5];
        rpm = ( rpm << 8 ) | data[6];
        rpm = ( rpm << 8 ) | data[7];
        rpm = ( rpm << 8 ) | data[8];
    }
    else if( ( ( data[0] == 0x81 ) && ( data[1] == 0x4B ) ) ||
             ( ( data[0] == 0x81 ) && ( data[1] == 0x49 ) ) )
    {
        // temp
        temp = data[4];
    }
    else if( ( data[0] == 0xA1 ) && ( data[1] == 0x7B ) )
    {
        // bitmask
        bitmask = data[4];
    }

    activity++;

    tthread_mutex_unlock( data_mutex );
}

static void monitor_thread( void )
{
    device_t serial_device;
    int elm327_index;
    char rx_char;
    uint8_t mode;

    if( serial_open_device( "/dev/ttyS0", &serial_device, 115200 ) < 0 )
    {
        printf( "Failed to open ELM\n" );
        return;
    }

    bool_t blocking = TRUE;
    device_ioctrl( &serial_device, DEVICE_BLOCKING_STATE, &blocking );

    mode = ELM_327_Idle;
    elm_buffer[0] = 0;
    elm327_index = 0;

    while( 1 )
    {
        rx_char = device_read( &serial_device );

        switch( mode )
        {
            case ELM_327_Receiving:
                if( ( rx_char == 0x0d ) || ( rx_char == 0x0a ) )
                {
                    uint8_t data[16];
                    ascii_to_buffer( elm_buffer, data );
                    decode_elm_327( data );

                    elm_buffer[0] = 0;
                    elm327_index = 0;
                }
                else if( rx_char != '>' )
                {
                    elm_buffer[ elm327_index++ ] = rx_char;
                    elm_buffer[ elm327_index ] = 0;
                }
                /* no break */

            case ELM_327_Idle:
                if( rx_char == '>' )
                {
                    printf( "Startup\n" );
                    tthread_sleep_ms( 200 );
                    device_write_buffer( &serial_device, ( uint8_t * )elm_327_header_on, strlen( elm_327_header_on ) );
                    mode = ELM_327_EnableHeader;
                }
                break;

            case ELM_327_EnableHeader:
                if( rx_char == '>' )
                {
                    printf( "Monitor on\n" );
                    tthread_sleep_ms( 200 );
                    device_write_buffer( &serial_device, ( uint8_t * )elm_327_monitor_on, strlen( elm_327_monitor_on ) );
                    mode = ELM_327_Receiving;
                }
                break;
        }
    }
}

void elm_327_get_data( elm_327_data_t * data )
{
    tthread_mutex_lock( data_mutex );

    data->speed = (int)speed / 100;
    data->rpm = (long)rpm;
    data->temp = (int)temp - 40;
    data->bitmask = bitmask;

    tthread_mutex_unlock( data_mutex );
}

bool_t elm_327_has_data( void )
{
    bool_t ret = FALSE;

    tthread_mutex_lock( data_mutex );
    ret = ( activity != previous_activity ) ? TRUE : FALSE;
    previous_activity = activity;
    tthread_mutex_unlock( data_mutex );

    return ret;
}

void elm_327_monitor_init( void )
{
    activity = 0;
    previous_activity = 0;

    speed = 0;
    rpm = 0;
    temp = 0;
    bitmask = 0;

    data_mutex = tthread_mutex_init();

    tthread_create( monitor_thread );
}

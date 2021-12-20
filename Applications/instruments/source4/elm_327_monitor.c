#include "elm_327_monitor.h"
#include "system.h"
#include "driving_data.h"
#include "input_reader.h"
#include "odometer_ctrl.h"
#include "ignition_control.h"

////////////////////////////////////////////////////////////////////

#define CAN_FAILURE_COUNTER     12

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

static const uint8_t crc_table[] =
{
      0x00 , 0x1D , 0x3A , 0x27 , 0x74 , 0x69 , 0x4E , 0x53 , 0xE8 , 0xF5 , 0xD2 , 0xCF , 0x9C , 0x81 , 0xA6 , 0xBB
    , 0xCD , 0xD0 , 0xF7 , 0xEA , 0xB9 , 0xA4 , 0x83 , 0x9E , 0x25 , 0x38 , 0x1F , 0x02 , 0x51 , 0x4C , 0x6B , 0x76
    , 0x87 , 0x9A , 0xBD , 0xA0 , 0xF3 , 0xEE , 0xC9 , 0xD4 , 0x6F , 0x72 , 0x55 , 0x48 , 0x1B , 0x06 , 0x21 , 0x3C
    , 0x4A , 0x57 , 0x70 , 0x6D , 0x3E , 0x23 , 0x04 , 0x19 , 0xA2 , 0xBF , 0x98 , 0x85 , 0xD6 , 0xCB , 0xEC , 0xF1
    , 0x13 , 0x0E , 0x29 , 0x34 , 0x67 , 0x7A , 0x5D , 0x40 , 0xFB , 0xE6 , 0xC1 , 0xDC , 0x8F , 0x92 , 0xB5 , 0xA8
    , 0xDE , 0xC3 , 0xE4 , 0xF9 , 0xAA , 0xB7 , 0x90 , 0x8D , 0x36 , 0x2B , 0x0C , 0x11 , 0x42 , 0x5F , 0x78 , 0x65
    , 0x94 , 0x89 , 0xAE , 0xB3 , 0xE0 , 0xFD , 0xDA , 0xC7 , 0x7C , 0x61 , 0x46 , 0x5B , 0x08 , 0x15 , 0x32 , 0x2F
    , 0x59 , 0x44 , 0x63 , 0x7E , 0x2D , 0x30 , 0x17 , 0x0A , 0xB1 , 0xAC , 0x8B , 0x96 , 0xC5 , 0xD8 , 0xFF , 0xE2
    , 0x26 , 0x3B , 0x1C , 0x01 , 0x52 , 0x4F , 0x68 , 0x75 , 0xCE , 0xD3 , 0xF4 , 0xE9 , 0xBA , 0xA7 , 0x80 , 0x9D
    , 0xEB , 0xF6 , 0xD1 , 0xCC , 0x9F , 0x82 , 0xA5 , 0xB8 , 0x03 , 0x1E , 0x39 , 0x24 , 0x77 , 0x6A , 0x4D , 0x50
    , 0xA1 , 0xBC , 0x9B , 0x86 , 0xD5 , 0xC8 , 0xEF , 0xF2 , 0x49 , 0x54 , 0x73 , 0x6E , 0x3D , 0x20 , 0x07 , 0x1A
    , 0x6C , 0x71 , 0x56 , 0x4B , 0x18 , 0x05 , 0x22 , 0x3F , 0x84 , 0x99 , 0xBE , 0xA3 , 0xF0 , 0xED , 0xCA , 0xD7
    , 0x35 , 0x28 , 0x0F , 0x12 , 0x41 , 0x5C , 0x7B , 0x66 , 0xDD , 0xC0 , 0xE7 , 0xFA , 0xA9 , 0xB4 , 0x93 , 0x8E
    , 0xF8 , 0xE5 , 0xC2 , 0xDF , 0x8C , 0x91 , 0xB6 , 0xAB , 0x10 , 0x0D , 0x2A , 0x37 , 0x64 , 0x79 , 0x5E , 0x43
    , 0xB2 , 0xAF , 0x88 , 0x95 , 0xC6 , 0xDB , 0xFC , 0xE1 , 0x5A , 0x47 , 0x60 , 0x7D , 0x2E , 0x33 , 0x14 , 0x09
    , 0x7F , 0x62 , 0x45 , 0x58 , 0x0B , 0x16 , 0x31 , 0x2C , 0x97 , 0x8A , 0xAD , 0xB0 , 0xE3 , 0xFE , 0xD9 , 0xC4
};

////////////////////////////////////////////////////////////////////

static char elm_buffer[100];

static uint16_t rpm;
static uint16_t speed;
static uint8_t temp;
static uint8_t oil_temp;
static int field1;

static uint8_t bitmask;
static uint16_t field2;
static uint16_t field3;

static uint8_t activity;
static uint8_t previous_activity;

static void * data_mutex;

////////////////////////////////////////////////////////////////////

static bool_t crc_check( uint8_t * buffer, uint8_t size )
{
    bool_t ret = TRUE;

#ifndef TESTBENCH
    uint8_t crc = 0xff;
    uint8_t temp;

    for( uint8_t index = 0; index < ( size - 1 ); index++ )
    {
        temp = buffer[index] ^ crc;
        crc = crc_table[temp];
    }

    ret = ( crc ^ 0xFF ) == buffer[size-1];
#endif

    return ret;
}

static bool_t validate_signal( char * buffer )
{
    int len = strlen( buffer );
    uint8_t index = 0;

    for( int i = 0; i < len; i += 3 )
    {
        if( buffer[i+2] > 0x20 ) return FALSE;
    }

    return TRUE;
}

static uint8_t val_to_num( char val )
{
    if( ( val >= '0' ) && ( val <= '9' ) ) return val & 0x0F;
    else if( ( val >= 'A' ) && ( val <= 'F' ) ) return ( val & 0x0F ) + 9;
    else if( ( val >= 'a' ) && ( val <= 'f' ) ) return ( val & 0x0F ) + 9;

    return 0;
}

static uint8_t ascii_to_buffer( char * buffer, uint8_t * data )
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

    return index;
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

        field1 = data[6];
        field1 = ( field1 << 8 ) | data[7];
        if( field1 & 0x8000 ) field1 |= 0xFFFF0000;

        field2 = data[8];
    }
    else if( ( data[0] == 0x81 ) && ( data[1] == 0x49 ) )
    {
        // temp
        temp = data[4];
    }
    else if( ( data[0] == 0x81 ) && ( data[1] == 0x4B ) )
    {
        // oil temp
        oil_temp = data[4];
    }
    else if( ( data[0] == 0x81 ) && ( data[1] == 0x88 ) )
    {
        // bitmask
        bitmask = data[4];
    }
    else if( ( data[0] == 0xA1 ) && ( data[1] == 0x7B ) )
    {
        // bitmask
        field3 = data[4];
    }

    activity++;

    tthread_mutex_unlock( data_mutex );
}

static bool_t elm_327_has_data( void )
{
    bool_t ret = FALSE;

    tthread_mutex_lock( data_mutex );
    ret = ( activity != previous_activity ) ? TRUE : FALSE;
    previous_activity = activity;
    tthread_mutex_unlock( data_mutex );

    return ret;
}

static void update_thread( void )
{
    int local_rpm = 0;
    int local_speed;
    int local_temp;
    int local_oil_temp;

    int local_bitmask;
    int local_field1;
    int local_field2;
    int local_field3;

    int fail_count = 0;
    bool_t can_failure = FALSE;
    bool_t ignition_state = FALSE;
    bool_t oil_state = input_reader_get_oil_pressure_state() ? FALSE : TRUE;

    tthread_sleep_ms( 2000 );

    while( 1 )
    {
        tthread_sleep_ms( 200 );

        if( ( input_reader_get_oil_pressure_state() == TRUE ) && ( oil_state == FALSE ) )
        {
            driving_data_set_reading_value( Reading_OilPressure, 0 );
            oil_state = TRUE;
        }
        else if( ( input_reader_get_oil_pressure_state() == FALSE ) && ( oil_state == TRUE ) )
        {
            oil_state = FALSE;
        }

        if( oil_state == FALSE )
        {
            // 0 - 0 - 60
            // ... 0 - 4000
            int oil_pressure = ( local_rpm / 180 ) + 35;
            driving_data_set_reading_value( Reading_OilPressure, oil_pressure );
        }

        if( ignition_control_get_state() == TRUE )
        {
            ignition_state = TRUE;

            if( elm_327_has_data() == TRUE )
            {
                fail_count = 0;

                if( can_failure == TRUE )
                {
                    can_failure = FALSE;
                    //driving_data_state_mask( StateMask_CANFailure, FALSE );
                }

                tthread_mutex_lock( data_mutex );
                local_speed = (int)speed / 128;
                local_rpm = (int)rpm >> 2;
                local_temp = (int)temp - 40;
                local_oil_temp = (int)oil_temp;

                local_field1 = (int) field1;
                local_field2 = (int) field2;
                local_field3 = (int) field3;

                local_bitmask = bitmask;
                tthread_mutex_unlock( data_mutex );

                driving_data_set_reading_value( Reading_ELM327_Field1, local_field1 );
                driving_data_set_reading_value( Reading_ELM327_Field2, local_field2 );
                driving_data_set_reading_value( Reading_ELM327_Field3, local_field3 );
                driving_data_set_reading_value( Reading_ELM327_Bitmap, local_bitmask );

                driving_data_set_reading_value( Reading_EngineTemp, local_temp );
                driving_data_set_reading_value( Reading_RPM, local_rpm );
                driving_data_set_reading_value( Reading_Speed, local_speed );
                driving_data_set_reading_value( Reading_OilTemp, local_oil_temp );

                odometer_control_add_speed_value( local_speed );
            }

            if( ( can_failure == FALSE ) && ( ++fail_count > CAN_FAILURE_COUNTER ) )
            {
                can_failure = TRUE;
                //driving_data_state_mask( StateMask_CANFailure, TRUE );
                driving_data_set_reading_value( Reading_ELM327_Field1, 0 );
                driving_data_set_reading_value( Reading_ELM327_Field2, 0 );
                driving_data_set_reading_value( Reading_ELM327_Field3, 0 );
                driving_data_set_reading_value( Reading_ELM327_Bitmap, 0 );

                driving_data_set_reading_value( Reading_EngineTemp, 0 );
                driving_data_set_reading_value( Reading_RPM, 0 );
                driving_data_set_reading_value( Reading_Speed, 0 );
                driving_data_set_reading_value( Reading_OilTemp, 0 );

                odometer_control_reset();

                printf( "Data failure\n" );
            }
        }
        else if( can_failure == TRUE )
        {
            fail_count = 0;
            can_failure = FALSE;
            //driving_data_state_mask( StateMask_CANFailure, FALSE );
        }
        else if( ignition_state == TRUE )
        {
            ignition_state = FALSE;

            tthread_mutex_lock( data_mutex );
            speed = 0;
            rpm = 0;
            temp = 0;
            bitmask = 0;
            field1 = 0;
            field2 = 0;
            tthread_mutex_unlock( data_mutex );
        }
    }
}

static void monitor_thread( void * args )
{
    device_t serial_device;
    int elm327_index;
    char rx_char;
    uint8_t mode;
    const char * dev_name = ( const char * )args;

    if( serial_open_device( dev_name, &serial_device, 115200 ) < 0 )
    {
        printf( "Failed to open ELM\n" );
        return;
    }

    bool_t blocking = TRUE;
    device_ioctrl( &serial_device, DEVICE_BLOCKING_STATE, &blocking );

    mode = ELM_327_Receiving;
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
                    if( validate_signal( elm_buffer ) == TRUE )
                    {
                        uint8_t data[16];
                        uint8_t size = ascii_to_buffer( elm_buffer, data );
                        if( crc_check( data, size ) == TRUE )
                        decode_elm_327( data );
                    }

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

void elm_327_monitor_init( char * dev_name )
{
    activity = 0;
    previous_activity = 0;

    speed = 0;
    rpm = 0;
    temp = 0;
    bitmask = 0;
    field1 = 0;
    field2 = 0;

    data_mutex = tthread_mutex_init();

    if( dev_name == NULL ) return;

    tthread_create_ex( monitor_thread, dev_name );
    tthread_create( update_thread );
}

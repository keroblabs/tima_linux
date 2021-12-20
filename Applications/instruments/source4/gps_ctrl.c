#include "gps_ctrl.h"
#include "system.h"
#include "driving_data.h"

////////////////////////////////////////////////////////////////////
enum
{
    NMEA_MODE_IDLE,
    NMEA_MODE_RECEIVING,
    NMEA_MODE_DECODE,
};

#define GPS_USB_DEV_INDEX       2

////////////////////////////////////////////////////////////////////

static char nmea_buffer[1024];
static void *gps_mutex;
static nmea_data_t nmea_data;
static bool_t data_ready;

////////////////////////////////////////////////////////////////////

static void gps_ctrl_thread( void * args )
{
    device_t serial_device;
    int size;
    int nmea_index;
    char rx_char;
    uint8_t mode;
    nmea_data_t nmea;
    //const char * dev_name = ( const char * )args;
    char dev_name[20];

    serial_get_usb_path( GPS_USB_DEV_INDEX, dev_name );
    nmea_init( &nmea );

    printf( "GPS device: %s\n", dev_name );

    if( serial_open_device( dev_name, &serial_device, 4800 ) < 0 )
    {
        printf( "No GPS\n" );
        return;
    }
    bool_t blocking = TRUE;
    device_ioctrl( &serial_device, DEVICE_BLOCKING_STATE, &blocking );

    mode = NMEA_MODE_IDLE;
    nmea_buffer[0] = 0;
    nmea_index = 0;

    while( 1 )
    {
        rx_char = device_read( &serial_device );
        switch( mode )
        {
            case NMEA_MODE_IDLE:
                if( rx_char == '$' )
                {
                    nmea_index = 0;
                    mode = NMEA_MODE_RECEIVING;
                    nmea_buffer[nmea_index++] = rx_char;
                }
                break;

            case NMEA_MODE_RECEIVING:
                nmea_buffer[nmea_index++] = rx_char;
                if( rx_char == '*' )
                {
                    nmea_buffer[nmea_index] = 0;
                    mode = NMEA_MODE_IDLE;

                    nmea_decoder( nmea_buffer, &nmea );
                }
                break;
        }

        if( nmea_update_sats_data( &nmea ) )
        {
            // valid data available
            //printf( "%s %s\n", tima_asctime( &nmea.utc_date ), nmea.utc_date.tm_isdst ? "DST" : "" );
            //printf( "%8.3f km/h\n", nmea.ground_speed );

            tthread_mutex_lock( gps_mutex );
            memcpy( &nmea_data, &nmea, sizeof( nmea_data_t ) );
            data_ready = TRUE;
            tthread_mutex_unlock( gps_mutex );

            //driving_data_set_time( &nmea.utc_date );
            //driving_data_set_reading_value( Reading_SpeedGPS, (int)nmea.ground_speed );
        }
    }
}

bool_t gps_ctrl_get_nmea( nmea_data_t * data )
{
    bool_t ret;

    tthread_mutex_lock( gps_mutex );
    memcpy( data, &nmea_data, sizeof( nmea_data_t ) );
    ret = data_ready;
    data_ready = FALSE;
    tthread_mutex_unlock( gps_mutex );

    return ret;
}

void gps_ctrl_init( char * dev_name )
{
    data_ready = FALSE;
    gps_mutex = tthread_mutex_init();
    //if( dev_name != NULL )
    tthread_create_ex( gps_ctrl_thread, dev_name );
}

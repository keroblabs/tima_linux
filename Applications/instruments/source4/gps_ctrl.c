#include "gps_ctrl.h"
#include "system.h"
#include "nmea.h"
#include "driving_data.h"

////////////////////////////////////////////////////////////////////
enum
{
    NMEA_MODE_IDLE,
    NMEA_MODE_RECEIVING,
    NMEA_MODE_DECODE,
};

////////////////////////////////////////////////////////////////////

static char nmea_buffer[1024];

////////////////////////////////////////////////////////////////////

static void gps_ctrl_thread( void )
{
    device_t serial_device;
    int size;
    int nmea_index;
    char rx_char;
    uint8_t mode;
    nmea_data_t nmea;

    nmea_init( &nmea );

    if( serial_open_device( "/dev/ttyUSB0", &serial_device, 4800 ) < 0 )
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

            driving_data_set_time( &nmea.utc_date );
            driving_data_set_reading_value( Reading_SpeedGPS, (int)nmea.ground_speed );
        }
    }
}

void gps_ctrl_init( void )
{
    tthread_create( gps_ctrl_thread );
}

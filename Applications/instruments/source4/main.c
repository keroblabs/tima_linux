#include "canbus_conns.h"
#include "system.h"
#include "graphics.h"
#include "timer.h"
#include "draw.h"
#include "pipe.h"

#include "canbus_conns.h"
#include "driving_data.h"
#include "input_reader.h"
#include "odometer_ctrl.h"
#include "gps_ctrl.h"
#include "elm_327_monitor.h"
#include "logging_data.h"
#include "lin_ctrl.h"
#include "fuel_control.h"
#include "ignition_control.h"
#include "rear_bcm_comms.h"

#include "skin_standard.h"
#include "skin_infocentre.h"
#include "touchscreen_lib.h"

#include "skin_rpm.h"
#include "skin_speed.h"

///////////////////////////////////////////////////////////////////////////////////////

#ifdef TESTBENCH
#define ELM327_SERIAL_DEV       "/dev/ttyUSB0"
#define GPS_SERIAL_DEV          NULL
#else
#define ELM327_SERIAL_DEV       "/dev/ttyS0"
#define GPS_SERIAL_DEV          "/dev/ttyUSB0"
#endif

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    timer_data_t update_clock;
    uint8_t minute_count;

    void * pp_data;
    //int test_rpm = 0;
    //int test_speed = 0;
    uint16_t mouse_posx, mouse_posy, mouse_posz;
    
    system_init();

    driving_data_init();
    logging_data_init();
    touchscreen_lib_init();

	timer_Init();

    pp_data = infocentre_init();
    skin_standard_init( pp_data );

    input_reader_init();
    odometer_control_init();
    gps_ctrl_init( GPS_SERIAL_DEV );
    canbus_conns_init();
    elm_327_monitor_init( ELM327_SERIAL_DEV );

    lin_ctrl_init();
    lin_gpio_init();
    fuel_control_init();
    ignition_control_init();

    logging_data_load();

    timer_Start( &update_clock, 1000 );
    minute_count = 0;

    printf( "Tima Instruments 2\r\n" );
    
    while( 1 )
	{
        if( timer_Check( &update_clock ) )
        {
            timer_Reload( &update_clock );

            nmea_data_t nmea_data;
            bool_t is_ready = gps_ctrl_get_nmea( &nmea_data );

            if( is_ready == TRUE )
            {
                driving_data_set_time( &nmea_data.utc_date );
                driving_data_set_reading_value( Reading_SpeedGPS, (int)nmea_data.ground_speed );
            }

            if( ++minute_count >= 60 )
            {
                if( is_ready == TRUE )
                {
                    minute_count = 0;
                    logging_data_save();
                }
            }
        }
        
        if( lcd_driver_read_mouse( &mouse_posx, &mouse_posy, &mouse_posz ) )
        {
            //printf( "mouse: x=%d, y=%d, z=%d\n", mouse_posx, mouse_posy, mouse_posz );
            touchscreen_lib_set_reading( mouse_posx, mouse_posy, mouse_posz );
        }

        tthread_sleep_ms( 10 );
        graphics_process();
	}

	return 0;
}

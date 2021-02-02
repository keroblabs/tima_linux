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

#include "skin_standard.h"
#include "skin_infocentre.h"
#include "touchscreen_lib.h"

#include "skin_rpm.h"
#include "skin_speed.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    timer_data_t update_clock;
    void * pp_data;
    //int test_rpm = 0;
    //int test_speed = 0;
    uint16_t mouse_posx, mouse_posy, mouse_posz;
    
    system_init();

    driving_data_init();
    touchscreen_lib_init();

	timer_Init();

    pp_data = infocentre_init();
    skin_standard_init( pp_data );

    input_reader_init();
    odometer_control_init();
    gps_ctrl_init();
    canbus_conns_init();

    timer_Start( &update_clock, 500 );

    printf( "Tima Instruments 2\r\n" );

#if 0
    driving_data_set_odometer( 225833 );
    driving_data_set_reading_value( Reading_ShiftLightRPM, 6000 );
    driving_data_send_message( MessageSkin_Reload );
    
    driving_data_state_mask( StateMask_Battery, TRUE );
    driving_data_state_mask( StateMask_OilPressure, TRUE );
    driving_data_state_mask( StateMask_Washers, TRUE );
    driving_data_state_mask( StateMask_LowFuel, TRUE );
    driving_data_state_mask( StateMask_FogLight, TRUE );
    driving_data_state_mask( StateMask_EngineTemperature, TRUE );
    driving_data_state_mask( StateMask_FullBeam, TRUE );
    driving_data_state_mask( StateMask_EngineFault, TRUE );
    //driving_data_state_mask( StateMask_in, TRUE );
#endif
    
    while( 1 )
	{
        if( timer_Check( &update_clock ) )
        {
        	//time_t local_time;
        	//time(&local_time);
            //driving_data_set_time( localtime ( &local_time ) );
        	//timer_Start( &update_clock, 5000 );

        	//printf( "heap = %d .. thread = %d\n", mm_used(), mm_threads() );
            
            #if 0
            driving_data_set_reading_value( Reading_RPM, test_rpm );
            test_rpm += 1000;
            if( test_rpm > 7500 ) test_rpm = 0;
            
            if( test_rpm == 6000 )
            {
                driving_data_set_odometer(225834);
            }
            
            driving_data_set_speed(test_speed, Unit_Km, test_speed*6/10, Unit_Miles );
            test_speed += 23;
            if( test_speed > 250 ) test_speed = 0;
            //printf( "benchmark: rpm = %lld, speed = %lld\r\n", skin_rpm_get_draw_time(), skin_speed_get_draw_time() );
            #endif
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

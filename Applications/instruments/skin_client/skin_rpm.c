#include "skin_rpm.h"
#include "t_threads.h"
#include "gauges_lib.h"
#include "warning_lights.h"

////////////////////////////////////////////////////////////////////////////////////////

#define RPM_NIDDLE_BACKUP_LEN       2048

////////////////////////////////////////////////////////////////////////////////////////

static instruments_gauge_t rpm_gauge_data;
static niddle_data_t rpm_niddle_data;
static bool_t is_enabled;
static int shift_light_angle;
static uint32_t last_time_stamp = 0;

////////////////////////////////////////////////////////////////////////////////////////

static void show_rpm( void * lcd, void * p_data, int angle )
{
    niddle_data_t * niddle_data = ( niddle_data_t * )p_data;
    
    if( is_enabled == TRUE )
    {
        gauge_draw_niddle( lcd, niddle_data, angle - 677 );
        //warning_shift_set_state( lcd, ( angle > shift_light_angle ) );
    }
}

static void init_gauge_rpm( void )
{
    warning_shift_light_init( 282, 284 );
    skin_rpm_set_shift_light_value( 6000 );
    
    rpm_niddle_data.niddle_backup = graphics_backup_create( RPM_NIDDLE_BACKUP_LEN );
    
    rpm_niddle_data.posx = 220;
    rpm_niddle_data.posy = 220;
    rpm_niddle_data.niddle_colour = APP_RGB( 50, 100, 100 );
    rpm_niddle_data.niddle_width = 7;
    rpm_niddle_data.niddle_width_edge = 2;
    rpm_niddle_data.niddle_len = 195;
    rpm_niddle_data.end_niddle = TRUE;
    rpm_niddle_data.draw_circle = FALSE;
    rpm_niddle_data.circle_ratio = 35;
    rpm_niddle_data.circle_colour = APP_RGB( 254, 0, 0 );
    
    rpm_gauge_data.mutex = tthread_mutex_init();
    rpm_gauge_data.cond = tthread_condition_create();
    rpm_gauge_data.target = 0;
    rpm_gauge_data.curr_value = 0;
    rpm_gauge_data.min_diff = 6;
    rpm_gauge_data.min_inc = 10;
    rpm_gauge_data.max_inc = 15;
    rpm_gauge_data.base_diff = 64;
    rpm_gauge_data.initial_rate = LCD_REFRESH_RATE_MS;
    rpm_gauge_data.run_rate = LCD_REFRESH_RATE_MS;
    rpm_gauge_data.show_handler = show_rpm;
    rpm_gauge_data.data = &rpm_niddle_data;
    
    gauge_thread_start( &rpm_gauge_data );
}

void skin_rpm_set_value( int value )
{
    int new_value = ( value * 5543 ) >> 14;
    //printf( "RPM %4d - %d\n", new_value, timer_get_MS() - last_time_stamp );
    //last_time_stamp = timer_get_MS();

    tthread_mutex_lock( rpm_gauge_data.mutex );
    rpm_gauge_data.target = new_value;
    tthread_mutex_unlock( rpm_gauge_data.mutex );

    tthread_condition_signal( rpm_gauge_data.cond );
}

void skin_rpm_set_shift_light_value( int value )
{
    shift_light_angle = ( ( value * 5543 ) >> 14 );
}

void skin_rpm_hide( void )
{
    is_enabled = FALSE;
}

void skin_rpm_reload( void )
{
    is_enabled = TRUE;
    tthread_condition_signal( rpm_gauge_data.cond );
}

void skin_rpm_init( void )
{
    is_enabled = FALSE;
    init_gauge_rpm();
}

uint64_t skin_rpm_get_draw_time( void )
{
    return rpm_gauge_data.max_drawtime;
}

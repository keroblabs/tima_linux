#include "skin_fuel.h"
#include "t_threads.h"
#include "gauges_lib.h"
#include "warning_lights.h"
#include "skin_fuel.h"
#include "skin_warning.h"

////////////////////////////////////////////////////////////////////////////////////////

#define FUEL_NIDDLE_BACKUP_LEN      256

////////////////////////////////////////////////////////////////////////////////////////

static instruments_gauge_t fuel_gauge_data;
static niddle_data_t fuel_niddle_data;
static bool_t is_enabled;

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

static void show_fuel( void * lcd, void * p_data, int angle )
{
    if( is_enabled == FALSE ) return;
    niddle_data_t * niddle_data = ( niddle_data_t * )p_data;
    
    angle = 1024 - angle;
    
    if( angle < 512 ) niddle_data->niddle_len = 97 - ABS( angle / 42 );
    else niddle_data->niddle_len = 85 + ABS( ( angle - 512 ) / 56 );
    
    gauge_draw_niddle( lcd, niddle_data, 1024+angle );
}

static void init_gauge_fuel( void )
{
    fuel_niddle_data.niddle_backup = graphics_backup_create( FUEL_NIDDLE_BACKUP_LEN );
    fuel_niddle_data.posx = 679;
    fuel_niddle_data.posy = 106;
    fuel_niddle_data.niddle_colour = APP_RGB( 128, 214, 250 );
    fuel_niddle_data.niddle_width = 1;
    fuel_niddle_data.niddle_width_edge = 1;
    fuel_niddle_data.niddle_len = 85;
    fuel_niddle_data.end_niddle = TRUE;
    fuel_niddle_data.draw_circle = FALSE;
    fuel_niddle_data.circle_ratio = 20;
    fuel_niddle_data.circle_colour = APP_RGB( 223, 6, 37 );
    
    fuel_gauge_data.mutex = tthread_mutex_init();
    fuel_gauge_data.cond = tthread_condition_create();
    fuel_gauge_data.target = 0;
    fuel_gauge_data.curr_value = 0;
    fuel_gauge_data.min_diff = 25;
    fuel_gauge_data.min_inc = 18;
    fuel_gauge_data.max_inc = 18;
    fuel_gauge_data.base_diff = 128;
    fuel_gauge_data.initial_rate = TEMP_REFRESH_RATE_MS;
    fuel_gauge_data.run_rate = FUEL_REFRESH_RATE_MS;
    fuel_gauge_data.show_handler = show_fuel;
    fuel_gauge_data.data = &fuel_niddle_data;
    
    gauge_thread_start( &fuel_gauge_data );
}

void skin_fuel_set_value( int value )
{
    int target;
    bool_t is_update = FALSE;
    
    // 0 - 1024
    if( value < 0 ) target = 0;
    else if( value > 100 ) target = 1024;
    else target = ( ( value * 10485 ) >> 10 );
    
    if( is_enabled == FALSE )
    {
        tthread_mutex_lock( fuel_gauge_data.mutex );
        fuel_gauge_data.saved_value = target;
        tthread_mutex_unlock( fuel_gauge_data.mutex );
    }
    else
    {
        tthread_mutex_lock( fuel_gauge_data.mutex );
        fuel_gauge_data.target = target;
        tthread_mutex_unlock( fuel_gauge_data.mutex );
        
        tthread_condition_signal( fuel_gauge_data.cond );
    }
}

void skin_fuel_hide( void )
{
    is_enabled = FALSE;
    gauge_thread_force_value( &fuel_gauge_data, 0 );
}

void skin_fuel_reload( void )
{
    is_enabled = TRUE;
    gauge_thread_restore_value( &fuel_gauge_data );
}

void skin_fuel_init( void )
{
    is_enabled = FALSE;
    init_gauge_fuel();
}

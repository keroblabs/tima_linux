#include "skin_oil_temp.h"
#include "t_threads.h"
#include "graphics.h"
#include "gauges_lib.h"
#include "warning_lights.h"
#include "skin_warning.h"
#include "driving_data.h"

////////////////////////////////////////////////////////////////////////////////////////

#define TEMPERATURE_NIDDLE_BACKUP_LEN       256

////////////////////////////////////////////////////////////////////////////////////////

static instruments_gauge_t temperature_gauge_data;
static niddle_data_t temperature_niddle_data;
static bool_t is_enabled;

////////////////////////////////////////////////////////////////////////////////////////

static void show_temperature( void * lcd, void * p_data, int angle )
{
    if( is_enabled == FALSE ) return;
    
    niddle_data_t * niddle_data = ( niddle_data_t * )p_data;

    if( angle < 512 ) niddle_data->niddle_len = 97 - ABS( angle / 42 );
    else niddle_data->niddle_len = 85 + ABS( ( angle - 512 ) / 56 );

    angle = 1024 - angle;
    gauge_draw_niddle( lcd, niddle_data, 1024+angle );
}

static void init_gauge_temperature( void )
{
    temperature_niddle_data.niddle_backup = graphics_backup_create( TEMPERATURE_NIDDLE_BACKUP_LEN );
    temperature_niddle_data.posx = 679;
    temperature_niddle_data.posy = 224;
    temperature_niddle_data.niddle_colour = APP_RGB( 128, 214, 250 );
    temperature_niddle_data.niddle_width = 1;
    temperature_niddle_data.niddle_width_edge = 1;
    temperature_niddle_data.niddle_len = 80;
    temperature_niddle_data.end_niddle = TRUE;
    temperature_niddle_data.draw_circle = FALSE;
    temperature_niddle_data.circle_ratio = 20;
    temperature_niddle_data.circle_colour = APP_RGB( 223, 6, 37 );
    
    temperature_gauge_data.mutex = tthread_mutex_init();
    temperature_gauge_data.cond = tthread_condition_create();
    temperature_gauge_data.target = 0;
    temperature_gauge_data.curr_value = 0;
    temperature_gauge_data.min_diff = 30;
    temperature_gauge_data.min_inc = 21;
    temperature_gauge_data.max_inc = 21;
    temperature_gauge_data.base_diff = 128;
    temperature_gauge_data.posx = 0;
    temperature_gauge_data.posy = 0;
    temperature_gauge_data.initial_rate = TEMP_REFRESH_RATE_MS;
    temperature_gauge_data.run_rate = TEMP_REFRESH_RATE_MS;
    temperature_gauge_data.show_handler = show_temperature;
    temperature_gauge_data.data = &temperature_niddle_data;
    
    gauge_thread_start( &temperature_gauge_data );
}

void skin_oil_pressure_set_value( int value )
{
    int target;
    
    // 0 - 1024
    if( value < 0 ) target = 0;
    else if( value > 100 ) target = 1024;
    else target = ( ( value * 10485 ) >> 10 );
    
    tthread_mutex_lock( temperature_gauge_data.mutex );
    temperature_gauge_data.target = target;
    tthread_mutex_unlock( temperature_gauge_data.mutex );
    
    tthread_condition_signal( temperature_gauge_data.cond );
}

void skin_oil_pressure_hide( void )
{
    is_enabled = FALSE;
}

void skin_oil_pressure_reload( void )
{
    is_enabled = TRUE;
    tthread_condition_signal( temperature_gauge_data.cond );
}

void skin_oil_pressure_init( void )
{
    is_enabled = FALSE;
    init_gauge_temperature();
}

#include "instruments.h"
#include "t_threads.h"
#include "skin_graphics.h"
#include "draw.h"
#include "pipe.h"
#include "warning_lights.h"
#include "infocentre.h"

////////////////////////////////////////////////////////////////////////////////////////

#define LCD_REFRESH_RATE_MS         16
#define FUEL_REFRESH_RATE_MS        100
#define TEMP_REFRESH_RATE_MS        25

////////////////////////////////////////////////////////////////////////////////////////

typedef struct _instruments_data_t
{
    uint8_t mode;
    int value;
    char * info;
    
    int rpm_target;
    int speed_target;
    int fuel_target;
    int temperature_target;

    int rpm_read;
    int speed_read;
    int fuel_read;
    int temperature_read;

    uint32_t odometer_value;

    bool_t overheat_flag;
    bool_t low_fuel_flag;

} instruments_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static void * rpm_cond;
static void * speed_cond;
static void * fuel_cond;
static void * temperature_cond;

static void * rpm_thread;
static void * speed_thread;
static void * fuel_thread;
static void * temperature_thread;

static void * instruments_mutex;

static instruments_data_t instruments_data;

////////////////////////////////////////////////////////////////////////////////////////

static void instruments_get_data( instruments_data_t * data )
{
    tthread_mutex_lock( instruments_mutex );
    memcpy( data, &instruments_data, sizeof( instruments_data_t ) );
    tthread_mutex_unlock( instruments_mutex );
}

static void instruments_rpm_thread( void )
{
    int inc = 42;
    int diff;
    int curr_value = 0;
    int target;
    instruments_data_t data;
    
    while( 1 )
    {
        tthread_sleep_ms( LCD_REFRESH_RATE_MS );
        instruments_get_data( &data );
        target = data.rpm_target;
        
        diff = target - curr_value;
        
        if( ( diff > -30 ) && ( diff < 30 ) )
        {
            curr_value = target;
            diff = 0;
        }
        else
        {
            if( ( diff > -128 ) && ( diff < 128 ) ) inc = 21;
            else inc = 42;

            if( diff > 0 ) curr_value += inc;
            else curr_value -= inc;
        }
        
        skin_standard_show_rpm( curr_value );

        if( diff == 0 )
        {
            tthread_condition_wait( rpm_cond );
        }
    }
}

static void instruments_speed_thread( void )
{
    int inc = 42;
    int diff;
    int curr_value = 0;
    int target;
    instruments_data_t data;

    while( 1 )
    {
        tthread_sleep_ms( LCD_REFRESH_RATE_MS );
        instruments_get_data( &data );
        target = data.speed_target;

        diff = target - curr_value;
        
        if( ( diff > -30 ) && ( diff < 30 ) )
        {
            curr_value = target;
            diff = 0;
        }
        else
        {
            if( ( diff > -128 ) && ( diff < 128 ) ) inc = 21;
            else inc = 42;

            if( diff > 0 ) curr_value += inc;
            else curr_value -= inc;
        }
        
        skin_standard_show_speed( curr_value );
        
        if( diff == 0 )
        {
            tthread_condition_wait( speed_cond );
        }
    }
}

static void instruments_fuel_thread( void )
{
    int diff;
    int curr_value = 0;
    int initial_refresh;
    int target;
    bool_t prev_low;
    bool_t new_low;
    instruments_data_t data;
    
    initial_refresh = LCD_REFRESH_RATE_MS;
    new_low = instruments_data.low_fuel_flag;
    prev_low = instruments_data.low_fuel_flag ? FALSE : TRUE;
    
    tthread_condition_wait( fuel_cond );
    
    while( 1 )
    {
        tthread_sleep_ms( initial_refresh );
        instruments_get_data( &data );
        target = data.fuel_target;
        new_low = data.low_fuel_flag;

        diff = target - curr_value;
        
        if( ( diff > -15 ) && ( diff < 15 ) )
        {
            curr_value = target;
            diff = 0;
        }
        else
        {
            if( diff > 0 ) curr_value += 10;
            else curr_value -= 10;
        }
        
        if( prev_low != new_low )
        {
        	prev_low = new_low;
        	if( new_low == TRUE )
        		skin_standard_show_warnings( 10, Warning_Fuel_Warning );
        	else
                skin_standard_hide_warnings( 10 );
        }

        skin_standard_show_fuel( curr_value );
        
        if( diff == 0 )
        {
            initial_refresh = FUEL_REFRESH_RATE_MS;
            tthread_condition_wait( fuel_cond );
        }
    }
}

static void instruments_temperature_thread( void )
{
    int diff;
    int curr_value = 0;
    int target;
    bool_t prev_low;
    bool_t new_low;
    bool_t is_init;
    instruments_data_t data;
    
    is_init = TRUE;
    new_low = FALSE;
    prev_low = FALSE;

    tthread_condition_wait( temperature_cond );
    
    while( 1 )
    {
        tthread_sleep_ms( TEMP_REFRESH_RATE_MS );
        instruments_get_data( &data );
        target = data.temperature_target;
        new_low = data.overheat_flag;

        diff = target - curr_value;
        
        if( ( diff > -30 ) && ( diff < 30 ) )
        {
            curr_value = target;
            diff = 0;
        }
        else
        {
            if( diff > 0 ) curr_value += 21;
            else curr_value -= 21;
        }
        
        if( ( prev_low != new_low ) || ( is_init == TRUE ) )
        {
            is_init = FALSE;
        	prev_low = new_low;
        	if( new_low == TRUE )
        		skin_standard_show_warnings( 11, Warning_Temperature_Warning );
        	else
                skin_standard_hide_warnings( 11 );
        }

        skin_standard_show_temperature( curr_value );
        
        if( diff == 0 )
        {
            tthread_condition_wait( temperature_cond );
        }
    }
}

void instruments_set_rpm( skin_rpm_cmd_t * cmd )
{
    if( cmd->value <= 250 ) cmd->value = 0;
    else cmd->value -= 250;
    
    tthread_mutex_lock( instruments_mutex );
    instruments_data.rpm_target = ( cmd->value * 7123 ) >> 14;
    instruments_data.rpm_read = cmd->value;
    tthread_mutex_unlock( instruments_mutex );

    tthread_condition_signal( rpm_cond );
}

void instruments_set_speed( skin_speed_cmd_t * cmd )
{
    if( cmd->value <= 5 ) cmd->value = 0;
     
    tthread_mutex_lock( instruments_mutex );
    instruments_data.speed_target = ( ( cmd->value * 355522 ) >> 14 ) - 75;
    if( instruments_data.speed_target < 0 ) instruments_data.speed_target = 0;
    instruments_data.speed_read = cmd->value;
    tthread_mutex_unlock( instruments_mutex );
    
    tthread_condition_signal( speed_cond );
}

void instruments_set_fuel( skin_fuel_cmd_t * cmd )
{
    int target;
    
    // 0 - 1024
    if( cmd->value < 0 ) target = 0;
    else if( cmd->value > 100 ) target = 1024;
    else target = ( ( cmd->value * 10485 ) >> 10 );
    
    tthread_mutex_lock( instruments_mutex );
    instruments_data.fuel_target = target;
    instruments_data.fuel_read = cmd->value;

    if( ( cmd->value < 10 ) && ( instruments_data.low_fuel_flag == FALSE ) )
    {
    	instruments_data.low_fuel_flag = TRUE;
    }
    else if( ( cmd->value > 13 ) && ( instruments_data.low_fuel_flag == TRUE ) )
    {
    	instruments_data.low_fuel_flag = FALSE;
    }

    tthread_mutex_unlock( instruments_mutex );

    tthread_condition_signal( fuel_cond );
}

void instruments_set_temperature( skin_temperature_cmd_t * cmd )
{
    int target;
    
    // 35 - 95 - 155 = 0 - 1024
    if( cmd->value < 35 ) target = 0;
    else if( cmd->value > 155 ) target = 1024;
    else target = ( ( cmd->value - 35 ) * 8738 ) >> 10;
    
    tthread_mutex_lock( instruments_mutex );

    if( ( cmd->value > 110 ) && ( instruments_data.overheat_flag == FALSE ) )
    {
    	instruments_data.overheat_flag = TRUE;
    }
    else if( ( cmd->value < 95 ) && ( instruments_data.overheat_flag == TRUE ) )
    {
    	instruments_data.overheat_flag = FALSE;
    }

    instruments_data.temperature_target = target;
    instruments_data.temperature_read = cmd->value;

    tthread_mutex_unlock( instruments_mutex );
    
    infocentre_set_value( InfoCentre_Set_EngineTemperature, cmd->value );

    tthread_condition_signal( temperature_cond );
}

int instruments_get_rpm( void )
{
	int ret;

    tthread_mutex_lock( instruments_mutex );
    ret = instruments_data.rpm_read;
    tthread_mutex_unlock( instruments_mutex );

    return ret;
}

int instruments_get_speed( void )
{
	int ret;

    tthread_mutex_lock( instruments_mutex );
    ret = instruments_data.speed_read;
    tthread_mutex_unlock( instruments_mutex );

	return ret;
}

int instruments_get_fuel( void )
{
	int ret;

    tthread_mutex_lock( instruments_mutex );
	ret = instruments_data.fuel_read;
    tthread_mutex_lock( instruments_mutex );

    return ret;
}

int instruments_get_temperature( void )
{
	int ret;

    tthread_mutex_lock( instruments_mutex );
    ret = instruments_data.temperature_read;
    tthread_mutex_unlock( instruments_mutex );

	return ret;
}

uint32_t instruments_get_odometer( void )
{
	uint32_t ret;

	tthread_mutex_lock( instruments_mutex );
	ret = instruments_data.odometer_value;
	tthread_mutex_unlock( instruments_mutex );

	return ret;
}

void instruments_set_odometer_count( skin_odometer_cmd_t * cmd )
{
	uint32_t meters;

	tthread_mutex_lock( instruments_mutex );

	// recalculate odometer calibration before assigning
	// stored value is in meters
	instruments_data.odometer_value = cmd->value;
	meters = instruments_data.odometer_value;

	tthread_mutex_unlock( instruments_mutex );

	skin_standard_show_odometer( meters );
}

void instruments_reload( void )
{
    tthread_condition_signal( rpm_cond );
    tthread_condition_signal( speed_cond );
    tthread_condition_signal( fuel_cond );
    tthread_condition_signal( temperature_cond );
    
    skin_standard_show_odometer( instruments_data.odometer_value );
}

void instruments_init( void )
{
	memset( &instruments_data, 0x00, sizeof( instruments_data ) );

	instruments_data.low_fuel_flag = TRUE;

    rpm_cond = tthread_condition_create();
    speed_cond = tthread_condition_create();
    fuel_cond = tthread_condition_create();
    temperature_cond = tthread_condition_create();
    
    instruments_mutex = tthread_mutex_init();
    
    rpm_thread = tthread_create( instruments_rpm_thread );
    speed_thread = tthread_create( instruments_speed_thread );
    fuel_thread = tthread_create( instruments_fuel_thread );
    temperature_thread = tthread_create( instruments_temperature_thread );
}

#include "system.h"
#include "ms_timer_hw_api.h"

///////////////////////////////////////////////////////////////////////////

static time_t start_time;

///////////////////////////////////////////////////////////////////////////

void rtc_driver_init( uint32_t index )
{
    time( ( time_t * )&start_time );
    start_time = start_time - ( time_t )( ms_timer_hw_get_ms() / 1000 );
}

void rtc_driver_close( uint32_t index )
{
}

uint32_t rtc_driver_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    time_t * p_value = ( time_t * )buffer;
    
    if( size >= sizeof( time_t ) )
    {
        *p_value = start_time + ( long )( ms_timer_hw_get_ms() / 1000 );
    }
    
    return sizeof( time_t );
}

uint32_t rtc_driver_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
    time_t * p_value = ( time_t * )buffer;
    
    if( size >= sizeof( time_t ) )
    {
        start_time = *p_value - ( long )( ms_timer_hw_get_ms() / 1000 );
    }
    
    return sizeof( time_t );
}

///////////////////////////////////////////////////////////////////////////

static bool_t rtc_validate( uint32_t index )
{
    if( index == 0 ) return TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t rtc_device =
{
    "rtc*",
    &_in_use,

    rtc_driver_init,
    rtc_driver_close,
    NULL,
    rtc_validate,
    NULL,
    NULL,
    NULL,

    DEV_MODE_CHANNEL,

    rtc_driver_input,
    rtc_driver_output,

};

DECLARE_DEVICE_SECTION( rtc_device );




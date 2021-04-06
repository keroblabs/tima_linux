#include "timer_class_private.h"
#include "hardware_class.h"

////////////////////////////////////////////////////////////////////////

#define TIMER_INIT      0x00
#define TIMER_OFF       0x00
#define TIMER_RUN       0x01
#define TIMER_STOPPED   0x02
#define TIMER_EXPIRED   0x04

#define TIME_IS_GREATER(a,b)        (((int32_t)((uint32_t)a - (uint32_t)b)) > 0)

////////////////////////////////////////////////////////////////////////

CREATOR static void creator( timer_class_t * p_data, uint32_t period )
{
    p_data->driver = STATIC_METHOD( hardware_class_t, get_class )()->get_timer_driver();
    
    if( period != 0 )
    {
        p_data->start( period );
    }
}

METHOD static void start( timer_class_t * p_data, uint32_t period )
{
    p_data->reload_ms = period;
    p_data->expire_ms = period + p_data->driver->get_ms();
    p_data->status = TIMER_INIT | TIMER_RUN;
}

METHOD static void reload( timer_class_t * p_data )
{
    p_data->expire_ms = p_data->driver->get_ms() + p_data->reload_ms;
    p_data->status = TIMER_INIT | TIMER_RUN;
}

METHOD static void stop( timer_class_t * p_data )
{
    p_data->status = TIMER_STOPPED;
}

METHOD static void expire( timer_class_t * p_data )
{
    p_data->status = TIMER_EXPIRED;
}

METHOD static bool_t check( timer_class_t * p_data )
{
    if( p_data->status & TIMER_STOPPED ) return FALSE;
    if( p_data->status & TIMER_EXPIRED ) return TRUE;
    return TIME_IS_GREATER( p_data->driver->get_ms(), p_data->expire_ms );
}

METHOD static uint32_t get_counter( timer_class_t * p_data )
{
    return 0;
}

////////////////////////////////////////////////////////////////////////

CREATE_CLASS( timer_class_t );

////////////////////////////////////////////////////////////////////////


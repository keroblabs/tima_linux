#include "timer.h"
#include "timer_driver.h"
#include "t_threads.h"

///////////////////////////////////////////////////////////////////////////////////////

#define _MS_TIMER ( ms_timer_hw_get_ms() )

///////////////////////////////////////////////////////////////////////////////////////

static void timer_trigger_thread( void * args )
{
    timer_trigger_t * p_timer = ( timer_trigger_t * )args;
    uint32_t period;
    uint16_t msg_expire;
    bool_t is_cancel;
    
    while( 1 )
    {
    	tthread_condition_wait( p_timer->timer_signal );

    	tthread_mutex_lock( p_timer->mutex );
    	period = p_timer->period;
    	tthread_mutex_unlock( p_timer->mutex );

        tthread_sleep_ms( period );

        tthread_mutex_lock( p_timer->mutex );
    	is_cancel = p_timer->is_cancel;
        p_timer->is_cancel = TRUE;
    	msg_expire = p_timer->msg_expire;
    	tthread_mutex_unlock( p_timer->mutex );

        if( is_cancel == FALSE )
    	{
            message_Post( p_timer->message, msg_expire );
    	}
    }
}

///////////////////////////////////////////////////////////////////////////////////////

time_t timer_Now( void )
{
    return 0; // ms_timer_now();
}

void timer_SetRTC( const time_t time )
{
}

uint32_t timer_get_MS( void )
{
    return _MS_TIMER;
}

uint64_t timer_get_microsecs( void )
{
	return ms_timer_hw_get_us();
}

uint32_t timer_32bit_now( void )
{
#if 0
    time_t tp;
    struct tm * time_2000;
    time_t tp_2000;
    time_t ret;
 
    time( &tp );
    
    // seconds from 2000
    time_2000->tm_mday = 1;
    time_2000->tm_mon  = 0;
    time_2000->tm_year = 2000;
    time_2000->tm_hour = 0;
    time_2000->tm_min = 0;
    time_2000->tm_sec = 0;
    
    tp_2000 = mktime( time_2000 );
    ret = tp - tp_2000;
    return ( uint32_t )ret;
#endif
    return 0;
}

void timer_Init( void )
{
    ms_timer_hw_global_init();
}

void timer_Trigger_Init( timer_trigger_t * ret, message_data_t * message )
{
    ret->msg_expire = Message_NoMessage;
    ret->message = message;
    ret->period = 0;
    ret->is_cancel = TRUE;

    ret->timer_signal = tthread_condition_create();
    ret->mutex = tthread_mutex_init();
    ret->thread = tthread_create_ex( timer_trigger_thread, ret );
}

void timer_Trigger( timer_trigger_t * ret, uint16_t msg, uint32_t period )
{
	tthread_mutex_lock( ret->mutex );
    ret->msg_expire = msg;
    ret->period = period;
    ret->is_cancel = FALSE;
	tthread_mutex_unlock( ret->mutex );

    tthread_condition_signal( ret->timer_signal );
}

void timer_CancelTrigger( timer_trigger_t * p_timer )
{
	tthread_mutex_lock( p_timer->mutex );
	p_timer->is_cancel = TRUE;
	tthread_mutex_unlock( p_timer->mutex );

    tthread_cancel( p_timer->thread );
}

void timer_Create( timer_data_t * timer_entry, uint32_t period )
{
    uint32_t curr_ms = _MS_TIMER;
    
    timer_entry->reload_ms = period;
    timer_entry->expire_ms = curr_ms + period;
    timer_entry->status = TIMER_STOPPED;
}

void timer_Start( timer_data_t * timer_entry, uint32_t period )
{
	uint32_t curr_ms = _MS_TIMER;

	timer_entry->reload_ms = period;
    timer_entry->expire_ms = curr_ms + period;
    timer_entry->status = TIMER_INIT | TIMER_RUN;
}

void timer_Reload( timer_data_t * timer_entry )
{
	timer_Start( timer_entry, timer_entry->reload_ms );
}

void timer_Stop( timer_data_t * timer_entry )
{
    timer_entry->status = TIMER_STOPPED;
}

void timer_Expire( timer_data_t * timer_entry )
{
    timer_entry->status = TIMER_EXPIRED;
}

bool_t timer_Check( timer_data_t * timer_entry )
{
	uint32_t curr_ms = _MS_TIMER;

	if( timer_entry->status & TIMER_STOPPED )       return( FALSE );
	else if( timer_entry->status & TIMER_EXPIRED )	return( TRUE );

    if( timer_entry->expire_ms < curr_ms )
    {
		if( ( curr_ms - timer_entry->expire_ms ) < 0x7FFFFFFF ) return( TRUE );
    }
	else if( timer_entry->expire_ms > curr_ms )
	{
		if( ( timer_entry->expire_ms - curr_ms ) > 0x7FFFFFFF ) return( TRUE );
	}

    //usleep(1);
    return( FALSE );
}

uint32_t timer_Get_Counter( timer_data_t * timer_entry )
{
	uint32_t curr_ms = _MS_TIMER;

	if( timer_entry->expire_ms <= curr_ms )
	{
		if( ( curr_ms - timer_entry->expire_ms ) > 0x7FFFFFFF )
		{
			return( ( 0xFFFFFFFF - curr_ms ) + timer_entry->expire_ms ) + 1;
		}
	}
	else
	{
		if( ( timer_entry->expire_ms - curr_ms ) < 0x7FFFFFFF )
		{
			return( timer_entry->expire_ms - curr_ms );
		}
	}

	return( 0L );

}


#include "pulse.h"

///////////////////////////////////////////////////////////////

static pulse_data_t * first_pulse = NULL;

///////////////////////////////////////////////////////////////
/*

Pulse format:
                 _________________
                |                 |
   period low   |   period high   |
0---------------1                 2

from 0 to 1...: returns PULSE_STATE_OFF
at 1..........: returns PULSE_RISING
from 1 to 2...: returns PULSE_STATE_ON
at 2..........: returns PULSE_FALLING

*/

void pulse_create( pulse_data_t * pulse_data, uint32_t period_low, uint32_t period_high, bool_t is_reload )
{
	pulse_data->p_event = NULL;
	pulse_data->mode = 0;
	if( is_reload == TRUE ) pulse_data->mode |= PULSE_RELOAD;

	timer_Start( &pulse_data->timer_low, period_low );
	timer_Start( &pulse_data->timer_high, period_high );

	timer_Stop( &pulse_data->timer_low );
	timer_Stop( &pulse_data->timer_high );

	if( first_pulse == NULL ) 
	{
		first_pulse = pulse_data;
		pulse_data->p_next = NULL;
	}
	else
	{
		pulse_data->p_next = first_pulse;
		first_pulse = pulse_data;
	}
}

void pulse_set_event( pulse_data_t * pulse_data, pulse_event_t p_event )
{
	pulse_data->p_event = p_event;
}

void pulse_start( pulse_data_t * pulse_entry )
{
	pulse_entry->mode |= PULSE_RUN;
	if( pulse_entry->p_event != NULL ) pulse_entry->p_event( pulse_entry, PULSE_RUN );
}

void pulse_stop( pulse_data_t * pulse_entry )
{
	pulse_entry->mode &= ~PULSE_RUN;
	if( pulse_entry->p_event != NULL ) pulse_entry->p_event( pulse_entry, PULSE_OFF );
}

uint8_t pulse_check( pulse_data_t * pulse_entry )
{
	uint8_t ret;
	uint32_t curr_ms = timer_get_MS();

	if( pulse_entry == NULL ) return( PULSE_OFF );
	if( !( pulse_entry->mode & PULSE_RUN ) ) return( PULSE_OFF );

	if( pulse_entry->mode & PULSE_STATE_OFF )
	{
		ret = PULSE_STATE_OFF;

		if( timer_Check( &pulse_entry->timer_low ) )
		{
			pulse_entry->mode |= PULSE_STATE_ON;
			pulse_entry->mode &= ~PULSE_STATE_OFF;
			ret = PULSE_RISING;

			if( pulse_entry->p_event != NULL ) pulse_entry->p_event( pulse_entry, ret );
		}
	}
	else if( pulse_entry->mode & PULSE_STATE_ON )
	{
		ret = PULSE_STATE_ON;

		if( timer_Check( &pulse_entry->timer_high ) )
		{
			pulse_entry->mode |= PULSE_STATE_OFF;
			pulse_entry->mode &= ~PULSE_STATE_ON;
			ret = PULSE_FALLING;

			if( pulse_entry->p_event != NULL ) pulse_entry->p_event( pulse_entry, ret );
		}
	}	

	return ret;
}

void pulse_process( void )
{
	pulse_data_t * pulse_data = first_pulse;

	while( pulse_data != NULL )
	{
		pulse_check( pulse_data );
		pulse_data = pulse_data->p_next;
	}
}


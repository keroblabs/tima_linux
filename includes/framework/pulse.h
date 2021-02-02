#ifndef __pulse_h__
#define __pulse_h__

///////////////////////////////////////////////////////////////

#include "types.h"
#include "pipe.h"
#include "timer.h"

///////////////////////////////////////////////////////////////

typedef void ( *pulse_event_t )( void * sender, uint32_t data );

typedef struct _pulse_data_t
{
	uint8_t mode;
	timer_data_t timer_low;
	timer_data_t timer_high;
	pulse_event_t p_event;

	struct _pulse_data_t * p_next;
	
} pulse_data_t;

typedef struct _pulse_msg_t
{
	uint32_t id;
	uint32_t mode;

} pulse_msg_t;

///////////////////////////////////////////////////////////////

#define PULSE_INIT		0x00
#define PULSE_OFF		0x00
#define PULSE_RELOAD	0x01
#define PULSE_RUN		0x02
#define PULSE_STATE_ON	0x04
#define PULSE_STATE_OFF 0x08
#define PULSE_RISING	0x10
#define PULSE_FALLING	0x20
#define PULSE_PIPED 	0x40

///////////////////////////////////////////////////////////////

void pulse_create( pulse_data_t * pulse_data, uint32_t period_low, uint32_t period_high, bool_t is_reload );
void pulse_process( void );
void pulse_set_event( pulse_data_t * pulse_data, pulse_event_t p_event );

void pulse_start( pulse_data_t * pulse_data );
void pulse_stop( pulse_data_t * pulse_data );

uint8_t pulse_check( pulse_data_t * pulse_data );

///////////////////////////////////////////////////////////////

#endif // __pulse_h__

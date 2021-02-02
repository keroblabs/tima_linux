#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "types.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////

__IO uint32_t _ms_timer = 0;

/*

SysTick free counter

84000 ticks = 1ms
counter runs at 84 MHz (11.9 ns)

 */
////////////////////////////////////////////////////////////////////////

void ms_timer_init( void )
{
	_ms_timer = 0;

	NVIC_SetPriority(SysTick_IRQn, 0x0);

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(84000))
	{ 
		/* Capture error */ 
		HardFault_Handler();
	}
}

void SysTick_Handler(void)
{
	_ms_timer++;
}

uint32_t ms_timer_get_ms( void )
{
	uint32_t ret;
	
	DI();
	ret = _ms_timer;
	EI();

	return ret;
}

void ms_timer_get_us( uint64_t * p_value )
{
	uint64_t ret = 0L;
	uint32_t cnt;

	DI();
	ret = _ms_timer;
	cnt = SysTick->VAL;
	EI();

	ret = ( ret * 1000 ) + ( cnt / 84 );

	*p_value = ret;
}

time_t ms_timer_now( void )
{
    return ( time_t )0;
}

////////////////////////////////////////////////////////////////////////

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

static void ms_timer_init( void )
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

////////////////////////////////////////////////////////////////////////

static void ms_timer_drv_init( uint32_t index )
{
	ms_timer_init();
}

static void ms_timer_drv_close( uint32_t index )
{
}

static uint32_t ms_timer_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
    return 0;
}

static uint32_t ms_timer_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    if( size == sizeof( uint32_t ) )
	{
		uint32_t * p_ms_value = ( uint32_t * )buffer;
		*p_ms_value = ms_timer_get_ms();
		return sizeof( uint32_t );
	}
    else if( size == sizeof( uint64_t ) )
    {
    	ms_timer_get_us( ( uint64_t * )buffer );
		return sizeof( uint64_t );
    }

    return size;
}

////////////////////////////////////////////////////////////////////////

static bool_t ms_timer_validate( uint32_t index )
{
    if( index == 0 ) return TRUE;
    return FALSE;
}

static bool_t _in_use;

const static device_data_t ms_timer_device =
{
    "timer*",
    &_in_use,

    ms_timer_drv_init,
    ms_timer_drv_close,
    NULL,
    ms_timer_validate,
    NULL,
    NULL,
    NULL,

    DEV_MODE_CHANNEL,

    ms_timer_drv_input,
    ms_timer_drv_output,

};

DECLARE_DEVICE_SECTION( ms_timer_device );




#include "system.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

////////////////////////////////////////////////////////////////////////

uint32_t ms_timer_get_ms( void );

void ms_timer_get_us( uint64_t * p_value );

////////////////////////////////////////////////////////////////////////

static __IO uint32_t counter_event;
static __IO uint64_t t1_ms_event;
static __IO uint64_t t2_ms_event;

////////////////////////////////////////////////////////////////////////

void EXTI9_5_IRQHandler( void )
{
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		counter_event++;

		t1_ms_event = t2_ms_event;
		ms_timer_get_us( ( uint64_t * )&t2_ms_event );

		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

static void hw_counter_init( void )
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	/* Enable GPIOC clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PC9 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Connect EXTI Line9 to PC9 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource9);

	/* Configure EXTI Line9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line9 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

////////////////////////////////////////////////////////////////////////

static void counter_drv_init( uint32_t index )
{
	t1_ms_event = ms_timer_get_ms();
	t2_ms_event = t1_ms_event;

	counter_event = 0;
	hw_counter_init();
}

static void counter_drv_close( uint32_t index )
{
}

static uint32_t counter_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	uint32_t * p_value;

	if( size != sizeof( uint32_t ) ) return size;

	DI();

	p_value = ( uint32_t * )buffer;
	counter_event = *p_value;

	EI();

	return size;
}

static uint32_t counter_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
	uint32_t * p_value;

	if( size != sizeof( uint32_t ) ) return size;

	DI();

	p_value = ( uint32_t * )buffer;
	*p_value = counter_event;

	EI();

	return size;
}

uint32_t counter_io_ctrl( uint32_t index, uint32_t param, void * value )
{
	uint32_t * p_value = ( uint32_t * )value;

	if( param == DEVICE_GET_RUNTIME_VALUE )
	{
		DI();
		*p_value = t2_ms_event - t1_ms_event;
		EI();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

static bool_t counter_validate( uint32_t index )
{
    if( index == 0 ) return TRUE;
    return FALSE;
}

static bool_t _in_use;

const static device_data_t counter_device =
{
    "counter*",
    &_in_use,

    counter_drv_init,
    counter_drv_close,
    NULL,
	counter_validate,
    NULL,
    counter_io_ctrl,
    NULL,

    DEV_MODE_CHANNEL,

    counter_drv_input,
    counter_drv_output,

};

DECLARE_DEVICE_SECTION( counter_device );



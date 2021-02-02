#include "system.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

static int intr_cnt = 0;

#define SYSTEM_HEAP_SIZE 		32768

uint8_t system_heap[SYSTEM_HEAP_SIZE];
uint32_t system_heap_size = SYSTEM_HEAP_SIZE;


//#define EEPROM_SECTION 		    	__attribute__ ((section(".eeprom_section")))

//EEPROM_SECTION const uint8_t eeprom_buffer_page0[256];
//EEPROM_SECTION const uint8_t eeprom_buffer_page1[256];

void _cpu_pio_init( void )
{
	/*
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits( GPIOA, GPIO_Pin_5 );
	*/
}

void _cpu_pio( bool_t state )
{
	//if( !state ) GPIO_ResetBits( GPIOA, GPIO_Pin_5 );
	//else GPIO_SetBits( GPIOA, GPIO_Pin_5 );
}

void _cpu_disable_irq( void )
{
	if( intr_cnt == 0 ) __disable_irq();
	intr_cnt++;
}

void _cpu_enable_irq( void )
{
	if( intr_cnt == 1 )
	{
		__enable_irq();
		intr_cnt = 0;
	}
	else
	{
		intr_cnt--;
	}
}

void _cpu_critical_init( void )
{
	_cpu_pio_init();
}

void _cpu_normal_init( void )
{
	_cpu_pio(1);
}

DECLARE_INIT_CRITICAL_SECTION( _cpu_critical_init );
DECLARE_INIT_MODULE_SECTION( _cpu_normal_init );


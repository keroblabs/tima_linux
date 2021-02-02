#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "types.h"

uint32_t SystemCoreClock;
 
/* Helpers for SystemInitError() */
#define SYSTEM_INIT_ERROR_FLASH 0x01
#define SYSTEM_INIT_ERROR_PLL 0x02
#define SYSTEM_INIT_ERROR_CLKSRC 0x04
#define SYSTEM_INIT_ERROR_HSI 0x08

 void SystemInitError(uint8_t error_source) {
	while(1);
}

void CPU_pio_debug_init( void )
{
#if 0
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits( GPIOA, GPIO_Pin_5 );
#endif
}

void CPU_pio_reset_init( void )
{
#if 0
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits( GPIOA, GPIO_Pin_13 );
#endif
}

void CPU_pio_reset( bool_t state )
{
	//if( !state ) GPIO_ResetBits( GPIOA, GPIO_Pin_13 );
	//else GPIO_SetBits( GPIOA, GPIO_Pin_13 );
}

void CPU_setup( void )
{
	/* Setup STM32 system (clock, PLL and Flash configuration) */
	/* it's already called by CRT */
	// SystemInit();

	/* Enable clocks */
	// RCC_AHB1PeriphClockCmd( RCC_AHB1en Periph_AFIO, ENABLE );
	/* Set the Vector Table base address at 0x08000000 */

	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Configure the SysTick handler priority */
	NVIC_SetPriority(SysTick_IRQn, 0x0);

	/* 1 bit for pre-emption priority, 3 bits for subpriority */
	NVIC_SetPriorityGrouping(6);
}

void CPU_system_init( void )
{
	/* Enable Power Control clock */
	RCC->APB1ENR |= RCC_APB1LPENR_PWRLPEN;
	/* Regulator voltage scaling output selection: Scale 2 */
	PWR->CR |= PWR_CR_VOS_1;
 
	/* Wait until HSI ready */
	while ((RCC->CR & RCC_CR_HSIRDY) == 0);
 
	/* Store calibration value */
	PWR->CR |= (uint32_t)(16 << 3);
 
	/* Disable main PLL */
	RCC->CR &= ~(RCC_CR_PLLON);
	/* Wait until PLL ready (disabled) */
	while ((RCC->CR & RCC_CR_PLLRDY) != 0);
 
	/*
	 * Configure Main PLL
	 * HSI as clock input
	 * fvco = 336MHz
	 * fpllout = 84MHz
	 * fusb = 48MHz
	 * PLLM = 16
	 * PLLN = 336
	 * PLLP = 4
	 * PLLQ = 7
	 */
	RCC->PLLCFGR = (uint32_t)((uint32_t)0x20000000 | (uint32_t)(16 << 0) | (uint32_t)(336 << 6) | 
					RCC_PLLCFGR_PLLP_0 | (uint32_t)(7 << 24));
 
	/* PLL On */
	RCC->CR |= RCC_CR_PLLON;
	/* Wait until PLL is locked */
	while ((RCC->CR & RCC_CR_PLLRDY) == 0);
 
	/* 
	 * FLASH configuration block
	 * enable instruction cache
	 * enable prefetch
	 * set latency to 2WS (3 CPU cycles)
	 */
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_2WS;
 
	/* Check flash latency */
	if ((FLASH->ACR & FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_2WS) {
		SystemInitError(SYSTEM_INIT_ERROR_FLASH);
	}
 
	/* Set clock source to PLL */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	/* Check clock source */
	while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
 
	/* Set HCLK (AHB1) prescaler (DIV1) */
	RCC->CFGR &= ~(RCC_CFGR_HPRE);
 
	/* Set APB1 Low speed prescaler (APB1) DIV2 */
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
 
	/* SET APB2 High speed srescaler (APB2) DIV1 */
	RCC->CFGR &= ~(RCC_CFGR_PPRE2);

	//RCC_GetHCLKFreq();
}

void SystemInit( void )
{
	CPU_system_init();
	CPU_setup();
	CPU_pio_debug_init();
	CPU_pio_reset_init();
}



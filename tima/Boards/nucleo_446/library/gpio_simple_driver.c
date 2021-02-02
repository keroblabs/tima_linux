#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "types.h"
#include "system.h"
#include "debug.h"

////////////////////////////////////////////////////////////////////////

typedef struct
{
	GPIO_TypeDef * gpio;
	uint16_t pin;
	uint16_t mode;

} gpio_map_t;

#define GPIO_INIT_MODE_NONE			0
#define GPIO_INIT_MODE_INPUT		1
#define GPIO_INIT_MODE_INPUT_PU		2
#define GPIO_INIT_MODE_OUTPUT   	3
#define GPIO_INIT_MODE_OUTPUT_ON	4
#define GPIO_INIT_MODE_OUTPUT_OFF	5
#define GPIO_INIT_MODE_EXPAND		6

////////////////////////////////////////////////////////////////////////

static const gpio_map_t gpio_map_list[] =
{
	// dummy
	{ GPIOC, GPIO_Pin_0, GPIO_INIT_MODE_NONE },

	{ GPIOC, GPIO_Pin_0, GPIO_INIT_MODE_OUTPUT_ON }, // 1
	{ GPIOC, GPIO_Pin_1, GPIO_INIT_MODE_OUTPUT_OFF }, // 2
	{ GPIOC, GPIO_Pin_2, GPIO_INIT_MODE_OUTPUT_OFF }, // 3
	{ GPIOC, GPIO_Pin_3, GPIO_INIT_MODE_OUTPUT_OFF }, // 4
	{ GPIOC, GPIO_Pin_4, GPIO_INIT_MODE_OUTPUT_OFF }, // 5
	{ GPIOC, GPIO_Pin_5, GPIO_INIT_MODE_OUTPUT_OFF }, // 6
	{ GPIOC, GPIO_Pin_6, GPIO_INIT_MODE_OUTPUT_OFF }, // 7
	{ GPIOC, GPIO_Pin_7, GPIO_INIT_MODE_OUTPUT_OFF }, // 8
};

#define GPIO_MAX_INDEX 36

static uint8_t gpio_mode_list[GPIO_MAX_INDEX+1];

static bool_t is_init;

////////////////////////////////////////////////////////////////////////

static void hw_gpio_list_init( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint32_t counter;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	for( counter = 1; counter <= GPIO_MAX_INDEX; counter++ )
	{
		if( ( gpio_map_list[counter].gpio != NULL ) && ( gpio_map_list[counter].mode != GPIO_INIT_MODE_NONE ) )
		{
			if( ( gpio_map_list[counter].mode == GPIO_INIT_MODE_INPUT ) ||
				( gpio_map_list[counter].mode == GPIO_INIT_MODE_INPUT_PU ) )
			{
				// this is for input
				GPIO_InitStructure.GPIO_Pin = gpio_map_list[counter].pin;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
				GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

				if( gpio_map_list[counter].mode == GPIO_INIT_MODE_INPUT_PU )
				{
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				}

				GPIO_Init(gpio_map_list[counter].gpio, &GPIO_InitStructure);
				gpio_mode_list[counter] = GPIO_INIT_MODE_INPUT;
			}
			else if( ( gpio_map_list[counter].mode == GPIO_INIT_MODE_OUTPUT_ON ) ||
					 ( gpio_map_list[counter].mode == GPIO_INIT_MODE_OUTPUT_OFF ) )
			{
				GPIO_InitStructure.GPIO_Pin = gpio_map_list[counter].pin;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
				GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
				GPIO_Init(gpio_map_list[counter].gpio, &GPIO_InitStructure);
				gpio_mode_list[counter] = GPIO_INIT_MODE_OUTPUT;

				if( gpio_map_list[counter].mode == GPIO_INIT_MODE_OUTPUT_OFF )
				{
					GPIO_ResetBits( gpio_map_list[counter].gpio, gpio_map_list[counter].pin );
				}
				else
				{
					GPIO_SetBits( gpio_map_list[counter].gpio, gpio_map_list[counter].pin );
				}
			}
		}
	}
}

static void gpio_drv_global_init( void )
{
	is_init = FALSE;
}

static void gpio_drv_init( uint32_t index )
{
	if( is_init == TRUE ) return;
	is_init = TRUE;

	memset( gpio_mode_list, 0x00, sizeof( gpio_mode_list ) );
	//hw_gpio_input_init();
	hw_gpio_list_init();
}

static void gpio_drv_close( uint32_t index )
{
}

static uint32_t gpio_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
	return 0;
}

static uint32_t gpio_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	if( size != sizeof( uint8_t ) ) return 0;

	if( index > GPIO_MAX_INDEX ) return 0;

	if( gpio_map_list[index].gpio != NULL )
	{
		if( gpio_mode_list[index] == GPIO_INIT_MODE_OUTPUT )
		{
			if( buffer[0] == 0 )
			{
				GPIO_ResetBits( gpio_map_list[index].gpio, gpio_map_list[index].pin );
			}
			else
			{
				GPIO_SetBits( gpio_map_list[index].gpio, gpio_map_list[index].pin );
			}
		}
	}

	return size;
}

static uint32_t gpio_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
	if( size != sizeof( uint8_t ) ) return 0;

	if( index > GPIO_MAX_INDEX ) return 0;

	if( gpio_map_list[index].gpio != NULL )
	{
		if( gpio_mode_list[index] == GPIO_INIT_MODE_INPUT )
		{
			*buffer =  GPIO_ReadInputDataBit( gpio_map_list[index].gpio, gpio_map_list[index].pin );
		}
	}

	return size;
}

////////////////////////////////////////////////////////////////////////

static bool_t gpio_validate( uint32_t index )
{
    if( index <= GPIO_MAX_INDEX ) return TRUE;
    return FALSE;
}

static bool_t _in_use;

const static device_data_t gpio_device =
{
    "gpio*",
    &_in_use,

    gpio_drv_init,
    gpio_drv_close,
    NULL,
    gpio_validate,
	NULL,
	gpio_drv_ioctl,
    NULL,

    DEV_MODE_CHANNEL,

    gpio_drv_input,
    gpio_drv_output,

};

DECLARE_DEVICE_SECTION( gpio_device );
DECLARE_INIT_POWERUP_SECTION( gpio_drv_global_init );



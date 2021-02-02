#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "types.h"
#include "system.h"

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
	{ GPIOC, GPIO_Pin_1, GPIO_INIT_MODE_OUTPUT_ON }, // 2
	{ GPIOC, GPIO_Pin_2, GPIO_INIT_MODE_INPUT_PU },  // 3
	{ GPIOC, GPIO_Pin_3, GPIO_INIT_MODE_INPUT_PU },  // 4
	{ GPIOB, GPIO_Pin_0, GPIO_INIT_MODE_OUTPUT_ON }, // 5
	{ GPIOC, GPIO_Pin_5, GPIO_INIT_MODE_OUTPUT_OFF }, // 6
	{ GPIOC, GPIO_Pin_6, GPIO_INIT_MODE_OUTPUT_OFF }, // 7
	{ GPIOC, GPIO_Pin_7, GPIO_INIT_MODE_OUTPUT_OFF }, // 8
#if 0
	{ GPIOC, GPIO_Pin_14, GPIO_INIT_MODE_INPUT }, // 9
	{ GPIOA, GPIO_Pin_8,  GPIO_INIT_MODE_INPUT }, // 10
	{ GPIOC, GPIO_Pin_9,  GPIO_INIT_MODE_INPUT }, // 11
	{ GPIOH, GPIO_Pin_1,  GPIO_INIT_MODE_INPUT }, // 12
	{ GPIOH, GPIO_Pin_2,  GPIO_INIT_MODE_INPUT }, // 13
	{ GPIOC, GPIO_Pin_13, GPIO_INIT_MODE_INPUT }, // 14
	{ GPIOC, GPIO_Pin_8,  GPIO_INIT_MODE_INPUT }, // 15

	{ GPIOB, GPIO_Pin_0,  GPIO_INIT_MODE_OUTPUT_OFF }, // 16
	{ GPIOA, GPIO_Pin_4,  GPIO_INIT_MODE_OUTPUT_OFF }, // 17
	{ GPIOB, GPIO_Pin_12, GPIO_INIT_MODE_OUTPUT_OFF }, // 18
	{ GPIOA, GPIO_Pin_12, GPIO_INIT_MODE_OUTPUT_OFF }, // 19
	{ GPIOB, GPIO_Pin_10, GPIO_INIT_MODE_OUTPUT_OFF }, // 20
	{ GPIOB, GPIO_Pin_4,  GPIO_INIT_MODE_OUTPUT_OFF }, // 21

	{ GPIOA, GPIO_Pin_14, GPIO_INIT_MODE_NONE }, // 22
	{ GPIOB, GPIO_Pin_7,  GPIO_INIT_MODE_NONE }, // 23
	{ GPIOA, GPIO_Pin_11, GPIO_INIT_MODE_INPUT_PU }, // 24

	{ GPIOB, GPIO_Pin_1,  GPIO_INIT_MODE_NONE }, // 25
	{ GPIOA, GPIO_Pin_7,  GPIO_INIT_MODE_INPUT_PU }, // 26
	{ GPIOA, GPIO_Pin_6,  GPIO_INIT_MODE_INPUT_PU }, // 27
	{ GPIOB, GPIO_Pin_6,  GPIO_INIT_MODE_NONE }, // 28
	{ GPIOB, GPIO_Pin_3,  GPIO_INIT_MODE_NONE }, // 29
	//{ GPIOA, GPIO_Pin_2,  GPIO_INIT_MODE_NONE }, // 30
	//{ GPIOA, GPIO_Pin_3,  GPIO_INIT_MODE_INPUT_PU }, // 31
	{ GPIOC, GPIO_Pin_15, GPIO_INIT_MODE_NONE }, // 32

	{ GPIOA, GPIO_Pin_5,  GPIO_INIT_MODE_INPUT_PU }, // 33
	{ GPIOB, GPIO_Pin_5,  GPIO_INIT_MODE_INPUT_PU }, // 34
	{ GPIOB, GPIO_Pin_8,  GPIO_INIT_MODE_INPUT_PU }, // 35
	{ GPIOB, GPIO_Pin_9,  GPIO_INIT_MODE_INPUT_PU }, // 36
#endif
	// not used

	{ NULL, GPIO_Pin_0, GPIO_INIT_MODE_EXPAND }, // 33
	{ NULL, GPIO_Pin_1, GPIO_INIT_MODE_EXPAND }, // 34
	{ NULL, GPIO_Pin_2, GPIO_INIT_MODE_EXPAND }, // 35
	{ NULL, GPIO_Pin_3, GPIO_INIT_MODE_EXPAND }, // 36
	{ NULL, GPIO_Pin_4, GPIO_INIT_MODE_EXPAND }, // 37
	{ NULL, GPIO_Pin_5, GPIO_INIT_MODE_EXPAND }, // 38
	{ NULL, GPIO_Pin_6, GPIO_INIT_MODE_EXPAND }, // 39
	{ NULL, GPIO_Pin_7, GPIO_INIT_MODE_EXPAND }, // 40


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
	memset( gpio_mode_list, 0x00, sizeof( gpio_mode_list ) );
}

static void gpio_drv_init( uint32_t index )
{
	if( is_init == TRUE ) return;
	is_init = TRUE;

	//hw_gpio_input_init();
	hw_gpio_list_init();
}

static void gpio_drv_close( uint32_t index )
{
}

static uint32_t gpio_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	char * p_param = ( char * )value;

	if( index > GPIO_MAX_INDEX ) return 0;

	if( ( gpio_map_list[index].gpio != NULL ) && ( gpio_map_list[index].mode == GPIO_INIT_MODE_NONE ) )
	{
		// only for configurable ports
		if( strncmp( p_param, "in", 2 ) == 0 )
		{
			// this is for input
			GPIO_InitStructure.GPIO_Pin = gpio_map_list[index].pin;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

			if( p_param[2] == ',' )
			{
				p_param += 3;
				if( strncmp( p_param, "pullup", 6 ) == 0 )
				{
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				}
			}

			GPIO_Init(gpio_map_list[index].gpio, &GPIO_InitStructure);
			gpio_mode_list[index] = GPIO_INIT_MODE_INPUT;
		}
		else if( strncmp( p_param, "out", 3 ) == 0 )
		{
			GPIO_InitStructure.GPIO_Pin = gpio_map_list[index].pin;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
			GPIO_Init(gpio_map_list[index].gpio, &GPIO_InitStructure);
			gpio_mode_list[index] = GPIO_INIT_MODE_OUTPUT;

			if( p_param[3] == ',' )
			{
				p_param += 4;
				if( strncmp( p_param, "off", 3 ) == 0 )
				{
					GPIO_ResetBits( gpio_map_list[index].gpio, gpio_map_list[index].pin );
				}
				else
				{
					GPIO_SetBits( gpio_map_list[index].gpio, gpio_map_list[index].pin );
				}
			}
		}
	}
	else if( ( gpio_map_list[index].gpio == NULL ) && ( gpio_map_list[index].mode == GPIO_INIT_MODE_EXPAND ) )
	{
		// setup expand gpio
		if( strncmp( p_param, "in", 2 ) == 0 )
		{
			// TODO: prepare GPIO as input

			if( p_param[2] == ',' )
			{
				p_param += 3;
				if( strncmp( p_param, "pullup", 6 ) == 0 )
				{
					// TODO: enable pull up
				}
			}

			// TODO: finish initialising the port
			gpio_mode_list[index] = GPIO_INIT_MODE_INPUT;
		}
		else if( strncmp( p_param, "out", 3 ) == 0 )
		{
			// TODO: configure port as output
			gpio_mode_list[index] = GPIO_INIT_MODE_OUTPUT;

			if( p_param[3] == ',' )
			{
				p_param += 4;
				if( strncmp( p_param, "off", 3 ) == 0 )
				{
					// TODO: set the port low
				}
				else
				{
					// TODO: set the port high
				}
			}
		}
	}

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
	else if( ( gpio_map_list[index].gpio == NULL ) && ( gpio_map_list[index].mode == GPIO_INIT_MODE_EXPAND ) )
	{
		if( gpio_mode_list[index] == GPIO_INIT_MODE_OUTPUT )
		{
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
	else if( ( gpio_map_list[index].gpio == NULL ) && ( gpio_map_list[index].mode == GPIO_INIT_MODE_EXPAND ) )
	{
		if( gpio_mode_list[index] == GPIO_INIT_MODE_INPUT )
		{
			*buffer = 0;
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



#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "system.h"
#include "gpio_driver.h"

////////////////////////////////////////////////////////////////////////

typedef struct
{
    gpio_t std_gpio;
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
	{ GPIO_PC03, GPIOC, GPIO_Pin_0, GPIO_INIT_MODE_OUTPUT_ON }, // 1
	{ GPIO_PC07, GPIOC, GPIO_Pin_1, GPIO_INIT_MODE_OUTPUT_ON }, // 2
    { GPIO_PC16, GPIOB, GPIO_Pin_0, GPIO_INIT_MODE_OUTPUT_ON }, // 5
	{ GPIO_PH00, GPIOC, GPIO_Pin_2, GPIO_INIT_MODE_INPUT_PU },  // 3
	{ GPIO_PH02, GPIOC, GPIO_Pin_3, GPIO_INIT_MODE_INPUT_PU },  // 4
#if 0

	{ GPIO_PH00, GPIOC, GPIO_Pin_5, GPIO_INIT_MODE_OUTPUT_OFF }, // 6
	{ GPIO_PH00, GPIOC, GPIO_Pin_6, GPIO_INIT_MODE_OUTPUT_OFF }, // 7
	{ GPIO_PH00, GPIOC, GPIO_Pin_7, GPIO_INIT_MODE_OUTPUT_OFF }, // 8
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
	// not used

	{ NULL, GPIO_Pin_0, GPIO_INIT_MODE_EXPAND }, // 33
	{ NULL, GPIO_Pin_1, GPIO_INIT_MODE_EXPAND }, // 34
	{ NULL, GPIO_Pin_2, GPIO_INIT_MODE_EXPAND }, // 35
	{ NULL, GPIO_Pin_3, GPIO_INIT_MODE_EXPAND }, // 36
	{ NULL, GPIO_Pin_4, GPIO_INIT_MODE_EXPAND }, // 37
	{ NULL, GPIO_Pin_5, GPIO_INIT_MODE_EXPAND }, // 38
	{ NULL, GPIO_Pin_6, GPIO_INIT_MODE_EXPAND }, // 39
	{ NULL, GPIO_Pin_7, GPIO_INIT_MODE_EXPAND }, // 40
#endif

    { GPIO_MAX, GPIOC, GPIO_Pin_3, GPIO_INIT_MODE_INPUT_PU },

};

////////////////////////////////////////////////////////////////////////

static uint8_t gpio_mode_list[GPIO_MAX];

////////////////////////////////////////////////////////////////////////

static const gpio_map_t * gpio_locate_map( gpio_t gpio )
{
    int counter;

    for( counter = 0; counter < GPIO_MAX; counter++ )
    {
        if( gpio_map_list[counter].std_gpio == GPIO_MAX ) break;
        if( gpio_map_list[counter].std_gpio == gpio ) return &gpio_map_list[counter];
    }

    return NULL;
}

static void gpio_local_init( const gpio_map_t *gpio_map, uint8_t mode )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if( gpio_map != NULL )
    {
        if( ( mode == GPIO_INIT_MODE_INPUT ) || ( mode == GPIO_INIT_MODE_INPUT_PU ) )
        {
            // this is for input
            GPIO_InitStructure.GPIO_Pin = gpio_map->pin;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
            GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

            if( mode == GPIO_INIT_MODE_INPUT_PU )
            {
                GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
            }

            GPIO_Init(gpio_map->gpio, &GPIO_InitStructure);
            gpio_mode_list[(int)gpio_map->std_gpio] = GPIO_INIT_MODE_INPUT;
        }
        else if( ( mode == GPIO_INIT_MODE_OUTPUT_ON ) ||
                 ( mode == GPIO_INIT_MODE_OUTPUT_OFF ) ||
                 ( mode == GPIO_INIT_MODE_OUTPUT ) )
        {
            GPIO_InitStructure.GPIO_Pin = gpio_map->pin;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
            GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
            GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;

            GPIO_Init(gpio_map->gpio, &GPIO_InitStructure);
            gpio_mode_list[(int)gpio_map->std_gpio] = GPIO_INIT_MODE_OUTPUT;

            if( mode == GPIO_INIT_MODE_OUTPUT_OFF )
            {
                GPIO_ResetBits( gpio_map->gpio, gpio_map->pin );
            }
            else if( mode == GPIO_INIT_MODE_OUTPUT_ON )
            {
                GPIO_SetBits( gpio_map->gpio, gpio_map->pin );
            }
        }
    }
}

void gpio_init( void )
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
}

void * gpio_open_output( gpio_t gpio )
{
    const gpio_map_t * gpio_map = gpio_locate_map( gpio );
    if( gpio_map != NULL )
    {
        gpio_local_init( gpio_map, GPIO_INIT_MODE_OUTPUT );
    }

    return ( void * )gpio_map;
}

void * gpio_open_input( gpio_t gpio )
{
    const gpio_map_t * gpio_map = gpio_locate_map( gpio );
    if( gpio_map != NULL )
    {
        gpio_local_init( gpio_map, GPIO_INIT_MODE_INPUT_PU );
    }

    return ( void * )gpio_map;
}

void * gpio_open_counter( gpio_t gpio )
{
    return NULL;
}

void gpio_output( void * p_gpio, int state )
{
    const gpio_map_t * gpio_map = ( const gpio_map_t * )p_gpio;
    int index                   = (int)gpio_map->std_gpio;

    if( gpio_mode_list[index] == GPIO_INIT_MODE_OUTPUT )
    {
        if( state == 0 )
        {
            GPIO_ResetBits( gpio_map->gpio, gpio_map->pin );
        }
        else
        {
            GPIO_SetBits( gpio_map->gpio, gpio_map->pin );
        }
    }
}

int  gpio_input( void * p_gpio )
{
    gpio_map_t * gpio_map = ( gpio_map_t * )p_gpio;
    int index             = (int)gpio_map->std_gpio;
    int ret               = 0;

    if( gpio_mode_list[index] == GPIO_INIT_MODE_INPUT )
    {
        ret = GPIO_ReadInputDataBit( gpio_map->gpio, gpio_map->pin );
    }

    return ret;
}

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval )
{
    return 0;
}




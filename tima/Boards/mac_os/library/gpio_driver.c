#include "types.h"
#include "gpio_driver.h"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

typedef struct gpio_data_t_
{
	gpio_t gpio;
	int mode;
} gpio_data_t;

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

int _gpio_setup_direction( gpio_t gpio, char * dir )
{
	return 0;
}

void gpio_init( void )
{
}

void * gpio_open_output( gpio_t gpio )
{
	return NULL;
}

void * gpio_open_input( gpio_t gpio )
{
	return NULL;
}

void * gpio_open_counter( gpio_t gpio )
{
    return NULL;
}

void gpio_output( void * p_gpio, int state )
{
}

int  gpio_input( void * p_gpio )
{
	return 0;
}

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval )
{
    return 0;
}

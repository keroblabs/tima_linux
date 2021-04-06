#include "types.h"
#include "gpio_driver.h"

///////////////////////////////////////////////////////////////////////////

extern "C"
{
    int ui_add_button( int index );
    
    int get_gpio_state( int index );
    void set_gpio_state( int index, int state );

}

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
	gpio_data_t * gpio_fs;

	if( _gpio_setup_direction( gpio, "out" ) != 0 )
	{
		return NULL;
	}

	gpio_fs = new gpio_data_t;
	if( gpio_fs == NULL ) return NULL;

	gpio_fs->mode = MODE_OUTPUT;
	gpio_fs->gpio = gpio;
    
    ui_add_button((int)gpio);
    
	return gpio_fs;
}

void * gpio_open_input( gpio_t gpio )
{
	gpio_data_t * gpio_fs;

	if( _gpio_setup_direction( gpio, "in" ) != 0 )
	{
		return NULL;
	}

	gpio_fs = new gpio_data_t;
	if( gpio_fs == NULL ) return NULL;

	gpio_fs->mode = MODE_INPUT;
	gpio_fs->gpio = gpio;

	return gpio_fs;
}

void * gpio_open_counter( gpio_t gpio )
{
    gpio_data_t * gpio_fs;
    
    gpio_fs = new gpio_data_t;
    if( gpio_fs == NULL ) return NULL;
    
    gpio_fs->mode = MODE_COUNTER;
    gpio_fs->gpio = gpio;
    
    return gpio_fs;
}

void gpio_output( void * p_gpio, int state )
{
	gpio_data_t * gpio_fs = ( gpio_data_t * )p_gpio;

	if( gpio_fs->mode != MODE_OUTPUT ) return;
    
    set_gpio_state( (int)gpio_fs->gpio, state );
}

int  gpio_input( void * p_gpio )
{
	gpio_data_t * gpio_fs = ( gpio_data_t * )p_gpio;

	if( gpio_fs->mode != MODE_INPUT ) return 0;
    return get_gpio_state( (int)gpio_fs->gpio );
}

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval )
{
    if( interval != NULL ) *interval = 0;
    return 0;
}

#include "types.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////

uint32_t api_get_input_gpio( void );
void api_set_output_gpio( uint32_t pio );

static uint32_t pio_input_mask;
static uint32_t pio_out_curr;
static uint32_t pio_out_send;

////////////////////////////////////////////////////////////////////////

static void hw_gpio_process( void )
{
    if( pio_out_curr != pio_out_send )
    {
        pio_out_curr = pio_out_send;
        api_set_output_gpio( pio_out_curr );
    }
    
    pio_input_mask = api_get_input_gpio();
}

////////////////////////////////////////////////////////////////////////

static void hw_gpio_input_init( void )
{
}

static void hw_gpio_output_init( void )
{
}

static void gpio_drv_global_init( void )
{
    pio_out_send = 0;
    pio_out_curr = 0;
}

static void gpio_drv_init( uint32_t index )
{
}

static void gpio_drv_close( uint32_t index )
{
}

static uint32_t gpio_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	if( size != sizeof( uint8_t ) ) return 0;
    if( ( index < 32 ) || ( index >= 64 ) ) return 0;
    
    index -= 32;
    
    if( *buffer ) pio_out_send |= ( 1 << index );
    else pio_out_send &= ~( 1 << index );

	return size;
}

static uint32_t gpio_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t pio_mask;

	if( size != sizeof( uint8_t ) ) return 0;
    if( index >= 32 ) return 0;
    
    pio_mask = api_get_input_gpio();
    
    if( pio_mask & ( 1 << index ) ) *buffer = TRUE;
    else *buffer = FALSE;

    return size;
}

////////////////////////////////////////////////////////////////////////

static bool_t gpio_validate( uint32_t index )
{
    if( index < 64 ) return TRUE;
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
    NULL,
    NULL,

    DEV_MODE_CHANNEL,

    gpio_drv_input,
    gpio_drv_output,

};

DECLARE_DEVICE_SECTION( gpio_device );
DECLARE_CRITICAL_SECTION( gpio_drv_global_init );
DECLARE_PROCESS_SECTION( hw_gpio_process );



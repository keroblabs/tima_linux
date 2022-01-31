#include "types.h"
#include "system.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

static uint64_t gpio_bitmask;
static timer_data_t powerdown_timer;
static timer_data_t powerup_timer;

////////////////////////////////////////////////////////////////////////

static void hw_gpio_input_init( void )
{
}

static void hw_gpio_output_init( void )
{
}

static void gpio_drv_global_init( void )
{
    gpio_bitmask = 0;
    
    //gpio_bitmask |= ( ( uint64_t )1 << 33 );
}

static void gpio_dev_hw_init( void )
{
    hw_gpio_input_init();
    hw_gpio_output_init();
    
    timer_Start( &powerdown_timer, 20000 );
}

static void gpio_drv_process( void )
{
    if( timer_Check( &powerdown_timer ) )
    {
        timer_Start( &powerup_timer, 2500 );
        timer_Stop( &powerdown_timer );
        gpio_bitmask |= ( ( uint64_t )1 << 33 );
    }
    
    if( timer_Check( &powerup_timer ) )
    {
        timer_Stop( &powerup_timer );
        gpio_bitmask &= ~( ( uint64_t )1 << 33 );
    }
}

////////////////////////////////////////////////////////////////////////

static void gpio_drv_init( uint32_t index )
{
}

static void gpio_drv_close( uint32_t index )
{
}

static uint32_t gpio_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	if( size != sizeof( uint8_t ) ) return 0;
    
    if( buffer[0] ) gpio_bitmask |= ( ( uint64_t )1 << index );
    else gpio_bitmask &= ~( ( uint64_t )1 << index );
    
	return size;
}

static uint32_t gpio_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
	if( size != sizeof( uint8_t ) ) return 0;

    buffer[0] = ( ( ( uint64_t )1 << index ) & gpio_bitmask ) ? TRUE : FALSE;
    
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

DECLARE_PROCESS_SECTION( gpio_drv_process );
DECLARE_DEVICE_SECTION( gpio_device );

DECLARE_INIT_DEVICE_SECTION( gpio_dev_hw_init );
DECLARE_INIT_POWERUP_SECTION( gpio_drv_global_init );



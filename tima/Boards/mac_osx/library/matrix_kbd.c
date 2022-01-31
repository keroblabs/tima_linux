#include "types.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////

uint32_t api_get_input_gpio( void );
void api_set_output_gpio( uint32_t pio );

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

static void matrix_drv_global_init( void )
{
}

static void matrix_drv_init( uint32_t index )
{
}

static void matrix_drv_close( uint32_t index )
{
}

static uint32_t matrix_drv_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t * p_pio;
	if( size != sizeof( uint32_t ) ) return 0;
    
    p_pio = ( uint32_t * )buffer;
    api_set_output_gpio( *p_pio );
    
	return size;
}

static uint32_t matrix_drv_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t * p_pio;
	if( size != sizeof( uint32_t ) ) return 0;

    p_pio = ( uint32_t * )buffer;
    *p_pio = api_get_input_gpio();

    return size;
}

////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t matrix_device =
{
    "matrix",
    &_in_use,

    matrix_drv_init,
    matrix_drv_close,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,

    DEV_MODE_CHANNEL,

    matrix_drv_input,
    matrix_drv_output,

};

DECLARE_DEVICE_SECTION( matrix_device );
DECLARE_INIT_POWERUP_SECTION( matrix_drv_global_init );



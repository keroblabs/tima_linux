#include "types.h"
#include "spi_driver.h"

///////////////////////////////////////////////////////////////////////////

static void * adc_spi = NULL;

///////////////////////////////////////////////////////////////////////////

void adc_driver_init( void )
{
	adc_spi = spi_open( GPIO_PG02 );
}

uint16_t adc_driver_read( uint8_t index )
{
	uint8_t cmd[3];
	uint8_t resp[3];
	uint16_t value;

	if( adc_spi == NULL ) return 0;

	resp[0] = resp[1] = resp[2] = 0;

	cmd[0] = 0x01;
	cmd[1] = 0xA0; // SGL, ODD, LSBF
	cmd[2] = 0;

	if( index ) cmd[1] |= 0x40;

	spi_exchange( adc_spi, cmd, resp, 3 );

	value = resp[1] & 0x0F;
	value = ( value << 8 ) | resp[2];

	return value;
}

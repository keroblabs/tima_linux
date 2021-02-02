#include "system.h"
#include "gpio_driver.h"

#include <unistd.h>
#include <getopt.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

///////////////////////////////////////////////////////////////////////////

#if defined _USE_OLIMEX
#define SPI_GPIO_CLOCK      GPIO_PC17
#define SPI_GPIO_MOSI       GPIO_PC23
#define SPI_GPIO_MISO       GPIO_PC18
#elif defined _USE_RPI
#define SPI_GPIO_CLOCK      GPIO_PC17
#define SPI_GPIO_MOSI       GPIO_PC23
#define SPI_GPIO_MISO       GPIO_PC18
#else
#define SPI_GPIO_CLOCK      GPIO_PC17
#define SPI_GPIO_MOSI       GPIO_PC23
#define SPI_GPIO_MISO       GPIO_PC18
#endif

#define SPI_CLOCK(a)		gpio_output( gpio_clock, a )
#define SPI_CS_EN(a)		gpio_output( a, 0 )
#define SPI_CS_DIS(a)		gpio_output( a, 1 )
#define SPI_MOSI(a)			gpio_output( gpio_mosi, a )

#define SPI_MISO()			gpio_input( gpio_miso )

///////////////////////////////////////////////////////////////////////////

static void * gpio_clock;
static void * gpio_mosi;
static void * gpio_miso;

static void * spi_mutex;

static bool_t is_init = FALSE;

///////////////////////////////////////////////////////////////////////////

void * spi_open( gpio_t gpio )
{
	void * ret;

	ret = gpio_open_output( gpio );

	if( is_init == FALSE )
	{
		gpio_clock = gpio_open_output( SPI_GPIO_CLOCK );
		gpio_mosi = gpio_open_output( SPI_GPIO_MOSI );
		gpio_miso = gpio_open_input( SPI_GPIO_MISO );

		spi_mutex = tthread_mutex_init();

		SPI_CLOCK(0);
		SPI_MOSI(0);
	}

	SPI_CS_DIS( ret );

	is_init = TRUE;

	return ret;
}

void spi_exchange( void * p_spi, uint8_t * data_in, uint8_t * data_out, int len )
{
	int mask = 0x80;
	int cnt;
	int cnt_bit;
	int input_read;

	tthread_mutex_lock( spi_mutex );

	SPI_CS_EN( p_spi );

	for( cnt = 0; cnt < len; cnt++ )
	{
		mask = 0x80;
		data_out[cnt] = 0;

		for( cnt_bit = 0; cnt_bit < 8; cnt_bit++ )
		{
			//printf( "0x%02x - ", mask );

			SPI_CLOCK(0);
			if( data_in[cnt] & mask ) SPI_MOSI(1);
			else SPI_MOSI(0);

			SPI_CLOCK(1);
			input_read = SPI_MISO();
			if( input_read ) data_out[cnt] |= mask;
			//printf( "%d\r\n", input_read );

			mask >>= 1;
		}
	}

	SPI_CS_DIS( p_spi );

    tthread_mutex_unlock( spi_mutex );
}

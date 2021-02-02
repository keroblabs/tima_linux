#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "system.h"
#include "debug.h"

//////////////////////////////////////////////////////////////////////////////

#define SPI_FLASH_INDEX 			1 // 15
#define SPI_GPIO_INDEX 				2 // 13

#define sFLASH_DUMMY_BYTE         	0xA5

#define CS_MODE_CHECK				1
#define CS_MODE_ENABLE				2
#define CS_MODE_DISABLE 			3

#define SPI_HW_INDEX				1

//////////////////////////////////////////////////////////////////////////////

typedef struct pio_config_t_
{
	uint32_t rcc_field;
	GPIO_TypeDef * GPIO;
	uint16_t pio;
	uint16_t pio_source;

} pio_config_t;


typedef struct
{
    // uart index
    SPI_TypeDef* SPIx;
	uint8_t SPI_AF;
	uint8_t dummy_byte;

    // RCC configuration
    uint32_t RCC_APB1Periph;
    uint32_t RCC_APB2Periph;
    uint32_t RCC_AHB1Periph;
    uint32_t RCC_AHB2Periph;

	// gpio used by spi
    GPIO_TypeDef* GPIO_SCLK;
    uint16_t GPIO_Pin_SCLK;
	uint32_t GPIO_PinSource_SCLK;

    GPIO_TypeDef* GPIO_MISO;
    uint16_t GPIO_Pin_MISO;
	uint32_t GPIO_PinSource_MISO;

    GPIO_TypeDef* GPIO_MOSI;
    uint16_t GPIO_Pin_MOSI;
	uint32_t GPIO_PinSource_MOSI;

} spi_data_t;

//////////////////////////////////////////////////////////////////////////////
// board dependent configuration

static const pio_config_t chip_select_list[] =
{
	{  RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_15, GPIO_PinSource15 },
	{  RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_13, GPIO_PinSource13 },
	{  RCC_AHB1Periph_GPIOA, GPIOA, GPIO_Pin_8,  GPIO_PinSource8 },
	{ 0, NULL, 0 }
};

static const spi_data_t spi_config_list[] =
{
	{
		// SPI 1 (to be used on Cerb40 boards)
		SPI1, GPIO_AF_SPI1, 0x00,

		// RCC clocks
		0,
		RCC_APB2Periph_SPI1,
		RCC_AHB1Periph_GPIOA,
		0,

		// gpio
		GPIOA, GPIO_Pin_5, GPIO_PinSource5,
		GPIOA, GPIO_Pin_6, GPIO_PinSource6,
		GPIOA, GPIO_Pin_7, GPIO_PinSource7,
	},
	{
		// SPI 3 (to be used on Mikro boards)
		SPI3, GPIO_AF_SPI3, 0x00,

		// RCC clocks
		RCC_APB1Periph_SPI3,
		0,
		RCC_AHB1Periph_GPIOB,
		0,

		// gpio
		GPIOB, GPIO_Pin_3, GPIO_PinSource3,
		GPIOB, GPIO_Pin_4, GPIO_PinSource4,
		GPIOB, GPIO_Pin_5, GPIO_PinSource5,
	},
	{
		// SPI 3 (to be used on Mikro boards)
		SPI3, GPIO_AF_SPI3, 0x00,

		// RCC clocks
		RCC_APB1Periph_SPI3,
		0,
		RCC_AHB1Periph_GPIOC,
		0,

		// gpio
		GPIOC, GPIO_Pin_10, GPIO_PinSource10,
		GPIOC, GPIO_Pin_11, GPIO_PinSource11,
		GPIOC, GPIO_Pin_12, GPIO_PinSource12,
	}
};

//////////////////////////////////////////////////////////////////////////////

void hw_spi_init_cs_pio( void )
{
	pio_config_t * entry = NULL;
	uint32_t cnt = 0;
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;

	while(1)
	{
		entry = ( pio_config_t * )&chip_select_list[cnt];
		if( entry->GPIO == NULL ) break;

		GPIO_InitStructure.GPIO_Pin = entry->pio;
		GPIO_Init(entry->GPIO, &GPIO_InitStructure);

		GPIO_SetBits( entry->GPIO, entry->pio );
		cnt++;
	}
}

void hw_spi_init_spi_pio( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
    I2S_InitTypeDef  I2S_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	spi_data_t * spi_config;

	spi_config = ( spi_data_t * )&spi_config_list[SPI_HW_INDEX];

	// enable clocks
	if( spi_config->RCC_APB1Periph != 0 )
	{
		RCC_APB1PeriphClockCmd( spi_config->RCC_APB1Periph , ENABLE);
	}

	if( spi_config->RCC_APB2Periph != 0 )
	{
		RCC_APB2PeriphClockCmd( spi_config->RCC_APB2Periph , ENABLE);
	}

	if( spi_config->RCC_AHB1Periph != 0 )
	{
		RCC_AHB1PeriphClockCmd( spi_config->RCC_AHB1Periph , ENABLE);
	}

	if( spi_config->RCC_AHB2Periph != 0 )
	{
		RCC_AHB2PeriphClockCmd( spi_config->RCC_AHB2Periph , ENABLE);
	}

	hw_spi_init_cs_pio();

	// connect pins to AF
	GPIO_PinAFConfig( spi_config->GPIO_SCLK, spi_config->GPIO_PinSource_SCLK, spi_config->SPI_AF );
	GPIO_PinAFConfig( spi_config->GPIO_MOSI, spi_config->GPIO_PinSource_MOSI, spi_config->SPI_AF );
	GPIO_PinAFConfig( spi_config->GPIO_MISO, spi_config->GPIO_PinSource_MISO, spi_config->SPI_AF );

	// setup gpio
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

	// SPI pin configuration
	GPIO_InitStructure.GPIO_Pin = spi_config->GPIO_Pin_SCLK | spi_config->GPIO_Pin_MOSI | spi_config->GPIO_Pin_MISO;
	GPIO_Init(spi_config->GPIO_SCLK, &GPIO_InitStructure);

	// SPI configuration
	SPI_StructInit( &SPI_InitStructure );
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	// Enable the sFLASH_SPI
	SPI_Init(spi_config->SPIx, &SPI_InitStructure);
	SPI_Cmd(spi_config->SPIx, ENABLE);
}

bool_t hw_spi_check_cs_pio( uint32_t index, uint8_t mode )
{
	pio_config_t * entry;
	uint32_t cnt = 0;
	GPIO_InitTypeDef GPIO_InitStructure;

	while(1)
	{
		entry = ( pio_config_t * )&chip_select_list[cnt];
		if( entry->GPIO == NULL ) break;

		if( (cnt+1) == index )
		{
			if( mode == CS_MODE_ENABLE )
			{
				GPIO_ResetBits( entry->GPIO, entry->pio );
			}
			else if( mode == CS_MODE_DISABLE )
			{
				GPIO_SetBits( entry->GPIO, entry->pio );
			}

			return TRUE;
		}

		cnt++;
	}

	return FALSE;
}

void hw_spi_init( void )
{
	SPI_InitTypeDef  SPI_InitStructure;

	//DEBUG_PRINTK( "hw_spi_init\r\n" );

	// configure GPIO
	hw_spi_init_spi_pio();
}

static uint8_t hw_spi_send_byte(uint8_t byte)
{
	uint32_t cnt = 8192;
	SPI_TypeDef* SPI_HW_PORT;

	SPI_HW_PORT = spi_config_list[SPI_HW_INDEX].SPIx;

	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI_HW_PORT, SPI_I2S_FLAG_TXE) == RESET)
	{
		if( --cnt == 0 )
		{
			DEBUG_PRINTK( "hw_spi_send_byte failed\r\n" );
			return 0;
		}
	}

	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI_HW_PORT, byte);

	/*!< Wait to receive a byte */
	cnt = 8192;
	while (SPI_I2S_GetFlagStatus(SPI_HW_PORT, SPI_I2S_FLAG_RXNE) == RESET)
	{
		if( --cnt == 0 )
		{
			DEBUG_PRINTK( "hw_spi_send_byte failed\r\n" );
			return 0;
		}
	}

	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI_HW_PORT);
}

static uint8_t hw_spi_read_byte(void)
{
  return (hw_spi_send_byte(0x00));
}

///////////////////////////////////////////////////////////////

static uint32_t spi_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	uint32_t cnt;

	for( cnt = 0; cnt < size; cnt++ )
	{
		hw_spi_send_byte( buffer[cnt] );
	}

	return size;
}

static uint32_t spi_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
	uint32_t cnt;

	for( cnt = 0; cnt < size; cnt++ )
	{
		buffer[cnt] = hw_spi_read_byte();
	}

	return size;
}

static void spi_drv_init( uint32_t index )
{
	hw_spi_init();
}

static void spi_drv_close( uint32_t index )
{
}

static uint32_t spi_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
	uint32_t * p_value = ( uint32_t * )value;
	uint8_t mode;

	switch( param )
	{
		case DEVICE_SET_RUNTIME_VALUE:
			mode = CS_MODE_DISABLE;
			if( *p_value ) mode = CS_MODE_ENABLE;
			else mode = CS_MODE_DISABLE;

			hw_spi_check_cs_pio( index, mode );
			break;
	}

	return 0;
}

static bool_t spi_validate( uint32_t index )
{
	return hw_spi_check_cs_pio( index, CS_MODE_CHECK );
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t spi_device =
{
    "spi*",
    &_in_use,

    spi_drv_init,
    spi_drv_close,
    NULL,
    spi_validate,
    NULL,
    spi_drv_ioctl,
    NULL,

    DEV_MODE_CHANNEL,

    spi_input,
    spi_output,

};

DECLARE_DEVICE_SECTION( spi_device );

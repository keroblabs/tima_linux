#include "system.h"
#include "buffer.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// #include "debug.h"

////////////////////////////////////////////////////////////////////

#define RX_SERIAL_BUFFER_SIZE          1024
#define TX_SERIAL_BUFFER_SIZE          1024

#define SERIAL_TOTAL					5

#define UART1_TTY_INDEX					10
#define UART2_TTY_INDEX					3
#define UART3_TTY_INDEX					8
#define UART4_TTY_INDEX				    9
#define UART5_TTY_INDEX					5

////////////////////////////////////////////////////////////////////

typedef struct _serial_buffer_data_t
{
	__IO uint8_t         rx_uart_buffer[ RX_SERIAL_BUFFER_SIZE ];
	__IO buffer_data_t   rx_uart_buffer_data;
	__IO uint8_t         tx_uart_buffer[ TX_SERIAL_BUFFER_SIZE ];
	__IO buffer_data_t   tx_uart_buffer_data;
	__IO bool_t          tx_busy;

} serial_buffer_data_t;

typedef void ( *clock_cmd_t )( uint32_t perith, FunctionalState state );

typedef struct _cmd_data_t
{
    clock_cmd_t          uart_cmd;
    uint32_t             uart_perith;
} cmd_data_t;

typedef struct _serial_pin_data_t
{
    GPIO_TypeDef    *gpio;
    uint8_t          pin_source;
    cmd_data_t       gpio_cmd;

} serial_pin_data_t;

typedef struct _serial_config_data_t
{
    USART_TypeDef       *uart;
    cmd_data_t           uart_cmd;
    uint8_t              irq;
    uint8_t              gpio_af;

    serial_pin_data_t    tx_pin;
    serial_pin_data_t    rx_pin;
    serial_buffer_data_t *buffer_data;

    uint8_t              tty_index;

} serial_config_data_t;

////////////////////////////////////////////////////////////////////

static serial_buffer_data_t serial_buffer_data[SERIAL_TOTAL];

static const serial_config_data_t serial_data[SERIAL_TOTAL] =
{
    {
        USART1, { RCC_APB2PeriphClockCmd, RCC_APB2Periph_USART1 },
        USART1_IRQn, GPIO_AF_USART1,
        { GPIOA, GPIO_PinSource9,  { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        { GPIOA, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        &serial_buffer_data[0], UART1_TTY_INDEX
    },
    {
        USART2, { RCC_APB1PeriphClockCmd, RCC_APB1Periph_USART2 },
        USART2_IRQn, GPIO_AF_USART2,
        { GPIOA, GPIO_PinSource2, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        { GPIOA, GPIO_PinSource3, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        &serial_buffer_data[1], UART2_TTY_INDEX
    },
    {
        USART3, { RCC_APB1PeriphClockCmd, RCC_APB1Periph_USART3 },
        USART3_IRQn, GPIO_AF_USART3,
        { GPIOC, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOC, GPIO_PinSource11, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        &serial_buffer_data[2], UART3_TTY_INDEX
    },
    {
        UART4,  { RCC_APB1PeriphClockCmd, RCC_APB1Periph_UART4 },
        UART4_IRQn, GPIO_AF_UART4,
        { GPIOC, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOC, GPIO_PinSource11, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        &serial_buffer_data[3], UART4_TTY_INDEX
    },
    {
        UART5,  { RCC_APB1PeriphClockCmd, RCC_APB1Periph_UART5 },
        UART5_IRQn, GPIO_AF_UART5,
        { GPIOC, GPIO_PinSource12, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOD, GPIO_PinSource2,  { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOD } },
        &serial_buffer_data[4], UART5_TTY_INDEX
    },
};

////////////////////////////////////////////////////////////////////

static const serial_config_data_t * uart_find_by_tty( uint8_t tty )
{
    uint8_t cnt = 0;

    for( cnt = 0; cnt < SERIAL_TOTAL; cnt++ )
    {
        if( serial_data[cnt].tty_index == tty ) return &serial_data[cnt];
    }

    return NULL;
}

static void uart_enable_clock( const cmd_data_t * data )
{
    data->uart_cmd( data->uart_perith, ENABLE );
}

static void init_uart_general( const serial_config_data_t * data, uint32_t baud )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable UART clock */
    uart_enable_clock( &data->uart_cmd );

    /* Enable GPIO clocks */
    uart_enable_clock( &data->rx_pin.gpio_cmd );
    uart_enable_clock( &data->tx_pin.gpio_cmd );

    /* Connect USART pins to AF */
    GPIO_PinAFConfig( data->rx_pin.gpio, data->rx_pin.pin_source, data->gpio_af );
    GPIO_PinAFConfig( data->tx_pin.gpio, data->tx_pin.pin_source, data->gpio_af );

    /*-------------------------- GPIO Configuration ----------------------------*/
    GPIO_InitStructure.GPIO_Pin =  ( uint16_t )( 0x01 << data->rx_pin.pin_source );
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(data->rx_pin.gpio, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  ( uint16_t )( 0x01 << data->tx_pin.pin_source );
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(data->tx_pin.gpio, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = data->irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(data->uart, USART_IT_ORE_RX, ENABLE);
    USART_ITConfig(data->uart, USART_IT_RXNE, ENABLE);
    USART_ITConfig(data->uart, USART_IT_TC, ENABLE);

    /* USARTx configuration ------------------------------------------------------*/
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(data->uart, &USART_InitStructure);

    USART_Cmd(data->uart, ENABLE);

    buffer_init( ( buffer_data_t * )&data->buffer_data->rx_uart_buffer_data, ( uint8_t * )&data->buffer_data->rx_uart_buffer, RX_SERIAL_BUFFER_SIZE );
    buffer_init( ( buffer_data_t * )&data->buffer_data->tx_uart_buffer_data, ( uint8_t * )&data->buffer_data->tx_uart_buffer, TX_SERIAL_BUFFER_SIZE );
    data->buffer_data->tx_busy = FALSE;
}

static void uart_irq_handler( uint8_t tty )
{
    uint16_t RxByte = 0x00;

    const serial_config_data_t * data = uart_find_by_tty( tty );
    if( data == NULL ) return;

    if (USART_GetITStatus((USART_TypeDef*)(data->uart), USART_IT_TC) == SET)
    {
        if (USART_GetFlagStatus((USART_TypeDef*)(data->uart), USART_FLAG_TC))
        {
            if( buffer_is_empty( ( buffer_data_t * )( &data->buffer_data->tx_uart_buffer_data ) ) == FALSE )
            {
                RxByte = buffer_read( ( buffer_data_t * )&data->buffer_data->tx_uart_buffer_data );
                USART_SendData((USART_TypeDef*)(data->uart), RxByte);
            }
            else
            {
                data->buffer_data->tx_busy = FALSE;
            }
        }

        USART_ClearITPendingBit((USART_TypeDef*)(data->uart), USART_IT_TC);
    }

    if ((USART_GetITStatus((USART_TypeDef*)(data->uart), USART_IT_RXNE) == SET) ||
        (USART_GetITStatus((USART_TypeDef*)(data->uart), USART_IT_ORE_RX) == SET))
    {
        if (USART_GetFlagStatus((USART_TypeDef*)(data->uart), USART_FLAG_RXNE))
        {
            RxByte = USART_ReceiveData((USART_TypeDef*)(data->uart));
            buffer_write( ( buffer_data_t * )( &data->buffer_data->rx_uart_buffer_data ), ( uint8_t )RxByte );
        }

        USART_ClearITPendingBit((USART_TypeDef*)(data->uart), USART_IT_RXNE);
    }
}

void USART1_IRQHandler(void)
{
    uart_irq_handler( UART1_TTY_INDEX );
}

void USART2_IRQHandler(void)
{
    uart_irq_handler( UART2_TTY_INDEX );
}

void USART3_IRQHandler(void)
{
    uart_irq_handler( UART3_TTY_INDEX );
}

void UART4_IRQHandler(void)
{
    uart_irq_handler( UART4_TTY_INDEX );
}

void UART5_IRQHandler(void)
{
    uart_irq_handler( UART5_TTY_INDEX );
}

///////////////////////////////////////////////////////////////////////////

static void uart_drv_init( uint32_t index )
{
}

static uint32_t uart_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
    const serial_config_data_t * data = uart_find_by_tty( index );
    if( data == NULL ) return 0;

    if( param == DEVICE_SET_CONFIG_DATA )
    {
        uint32_t * p_baud = ( uint32_t * )value;
        DEBUG_PRINTK( "[%d] %d init\r\n", index, *p_baud );
        init_uart_general( data, *p_baud );
    }

	return 0;
}

static uint32_t uart_read_buffer( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t num_bytes_present = 0;
	serial_buffer_data_t * p_buffer;
	uint32_t cnt;
    const serial_config_data_t * data = uart_find_by_tty( index );

    if( data == NULL ) return 0;
    p_buffer = data->buffer_data;

    num_bytes_present = buffer_get_size( ( buffer_data_t * )&p_buffer->rx_uart_buffer_data );

    if( ( num_bytes_present > 0 ) && ( buffer != NULL ) )
    {
    	for( cnt = 0; cnt < size; cnt++ )
    	{
    		if( cnt >= num_bytes_present ) break;
    		buffer[cnt] = buffer_read(( buffer_data_t * )&p_buffer->rx_uart_buffer_data);
    	}
    }

    return num_bytes_present;
}

static uint32_t uart_write_buffer( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t num_bytes_present = 0;
	serial_buffer_data_t * p_buffer;
	uint32_t cnt;
	uint16_t RxByte = 0x00;
    const serial_config_data_t * data = uart_find_by_tty( index );

    if( data == NULL ) return 0;
    p_buffer = data->buffer_data;

	buffer_write_buffer( ( buffer_data_t * )&p_buffer->tx_uart_buffer_data, buffer, size );
	if( p_buffer->tx_busy == FALSE )
	{
		 RxByte = buffer_read( ( buffer_data_t * )&p_buffer->tx_uart_buffer_data );
		 USART_SendData((USART_TypeDef*)data->uart, RxByte);
		 p_buffer->tx_busy = TRUE;
	}

	return size;
}

static void uart_drv_close( uint32_t index )
{
}

static bool_t uart_drv_validate( uint32_t index )
{
    if( uart_find_by_tty( index ) != NULL ) return TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const device_data_t console_tty_device =
{
    "tty*",
    &_in_use,

	uart_drv_init,
	uart_drv_close,
    NULL,
    uart_drv_validate,
    NULL,
	uart_drv_ioctl,
    NULL,

    DEV_MODE_CHANNEL,

	uart_read_buffer,
	uart_write_buffer,

};

DECLARE_DEVICE_SECTION( console_tty_device );



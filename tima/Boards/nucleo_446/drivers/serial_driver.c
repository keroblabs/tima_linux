#include "system.h"
#include "buffer.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
// #include "debug.h"

////////////////////////////////////////////////////////////////////

#define RX_SERIAL_BUFFER_SIZE          1024
#define TX_SERIAL_BUFFER_SIZE          1024

#define UART1_TTY_INDEX					0
#define UART2_TTY_INDEX					1
#define UART3_TTY_INDEX					2
#define UART4_TTY_INDEX				    3
#define UART5_TTY_INDEX					4
#define SERIAL_TOTAL                    5

#define UART1_TTY_NAME                  "/dev/tty1"
#define UART2_TTY_NAME                  "/dev/tty2"
#define UART3_TTY_NAME                  "/dev/tty3"
#define UART4_TTY_NAME                  "/dev/tty4"
#define UART5_TTY_NAME                  "/dev/tty5"

////////////////////////////////////////////////////////////////////

typedef struct _serial_buffer_data_t
{
	__IO uint8_t         rx_uart_buffer[ RX_SERIAL_BUFFER_SIZE ];
	__IO buffer_data_t   rx_uart_buffer_data;
	__IO uint8_t         tx_uart_buffer[ TX_SERIAL_BUFFER_SIZE ];
	__IO buffer_data_t   tx_uart_buffer_data;
	__IO bool_t          tx_busy;
	__IO device_data_t   device_data;
} serial_data_t;

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
    serial_data_t       *serial_data;

    const char          *name;

} serial_config_data_t;

////////////////////////////////////////////////////////////////////

static serial_data_t serial_data[SERIAL_TOTAL];

static const serial_config_data_t serial_setup[SERIAL_TOTAL] =
{
    {
        USART1, { RCC_APB2PeriphClockCmd, RCC_APB2Periph_USART1 },
        USART1_IRQn, GPIO_AF_USART1,
        { GPIOA, GPIO_PinSource9,  { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        { GPIOA, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        &serial_data[0], UART1_TTY_NAME
    },
    {
        USART2, { RCC_APB1PeriphClockCmd, RCC_APB1Periph_USART2 },
        USART2_IRQn, GPIO_AF_USART2,
        { GPIOA, GPIO_PinSource2, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        { GPIOA, GPIO_PinSource3, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOA } },
        &serial_data[1], UART2_TTY_NAME
    },
    {
        USART3, { RCC_APB1PeriphClockCmd, RCC_APB1Periph_USART3 },
        USART3_IRQn, GPIO_AF_USART3,
        { GPIOC, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOC, GPIO_PinSource11, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        &serial_data[2], UART3_TTY_NAME
    },
    {
        UART4,  { RCC_APB1PeriphClockCmd, RCC_APB1Periph_UART4 },
        UART4_IRQn, GPIO_AF_UART4,
        { GPIOC, GPIO_PinSource10, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOC, GPIO_PinSource11, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        &serial_data[3], UART4_TTY_NAME
    },
    {
        UART5,  { RCC_APB1PeriphClockCmd, RCC_APB1Periph_UART5 },
        UART5_IRQn, GPIO_AF_UART5,
        { GPIOC, GPIO_PinSource12, { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOC } },
        { GPIOD, GPIO_PinSource2,  { RCC_AHB1PeriphClockCmd, RCC_AHB1Periph_GPIOD } },
        &serial_data[4], UART5_TTY_NAME
    },
};

////////////////////////////////////////////////////////////////////

static int uart_find_index( const char * name )
{
    int cnt = 0;

    for( cnt = 0; cnt < SERIAL_TOTAL; cnt++ )
    {
        if( serial_setup[cnt].name == NULL  ) break;
        if( !strcmp( serial_setup[cnt].name, name ) ) return cnt;
    }

    return -1;
}

static void uart_enable_clock( const cmd_data_t * data )
{
    data->uart_cmd( data->uart_perith, ENABLE );
}

static void uart_init_hw( const serial_config_data_t * data, uint32_t baud )
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
}

static void uart_irq_handler( const serial_config_data_t * data )
{
    uint16_t RxByte = 0x00;

    if (USART_GetITStatus((USART_TypeDef*)(data->uart), USART_IT_TC) == SET)
    {
        if (USART_GetFlagStatus((USART_TypeDef*)(data->uart), USART_FLAG_TC))
        {
            if( buffer_is_empty( ( buffer_data_t * )( &data->serial_data->tx_uart_buffer_data ) ) == FALSE )
            {
                RxByte = buffer_read( ( buffer_data_t * )&data->serial_data->tx_uart_buffer_data );
                USART_SendData((USART_TypeDef*)(data->uart), RxByte);
            }
            else
            {
                data->serial_data->tx_busy = FALSE;
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
            buffer_write( ( buffer_data_t * )( &data->serial_data->rx_uart_buffer_data ), ( uint8_t )RxByte );
        }

        USART_ClearITPendingBit((USART_TypeDef*)(data->uart), USART_IT_RXNE);
    }
}

void USART1_IRQHandler(void)
{
    uart_irq_handler( &serial_setup[UART1_TTY_INDEX] );
}

void USART2_IRQHandler(void)
{
    uart_irq_handler( &serial_setup[UART2_TTY_INDEX] );
}

void USART3_IRQHandler(void)
{
    uart_irq_handler( &serial_setup[UART3_TTY_INDEX] );
}

void UART4_IRQHandler(void)
{
    uart_irq_handler( &serial_setup[UART4_TTY_INDEX] );
}

void UART5_IRQHandler(void)
{
    uart_irq_handler( &serial_setup[UART5_TTY_INDEX] );
}

static uint32_t uart_read_buffer( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t num_bytes_present = 0;
    uint32_t cnt;
    serial_data_t * p_data = &serial_data[index];

    num_bytes_present = buffer_get_size( ( buffer_data_t * )&p_data->rx_uart_buffer_data );

    if( ( num_bytes_present > 0 ) && ( buffer != NULL ) )
    {
        for( cnt = 0; cnt < size; cnt++ )
        {
            if( cnt >= num_bytes_present ) break;
            buffer[cnt] = buffer_read(( buffer_data_t * )&p_data->rx_uart_buffer_data);
        }
    }

    return num_bytes_present;
}

static uint32_t uart_write_buffer( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t num_bytes_present = 0;
    uint32_t cnt;
    uint16_t RxByte = 0x00;
    serial_data_t * p_data = &serial_data[index];

    buffer_write_buffer( ( buffer_data_t * )&p_data->tx_uart_buffer_data, buffer, size );
    if( p_data->tx_busy == FALSE )
    {
         RxByte = buffer_read( ( buffer_data_t * )&p_data->tx_uart_buffer_data );
         USART_SendData((USART_TypeDef*)serial_setup[index].uart, RxByte);
         p_data->tx_busy = TRUE;
    }

    return size;
}

///////////////////////////////////////////////////////////////////////////

int serial_open_device( const char * tty_name, device_t * device, uint32_t baud )
{
    int index = uart_find_index( tty_name );
    if( index == -1 ) return -1;

    serial_data_t * serial_data = serial_setup[index].serial_data;
    memset( serial_data, 0x00, sizeof( serial_data_t ) );

    device_data_t * device_data = ( device_data_t * )&serial_data->device_data;
    memset( device_data, 0x00, sizeof( device_data_t ) );

    uart_init_hw( &serial_setup[index], baud );

    buffer_init_static( ( buffer_data_t * )&serial_data->rx_uart_buffer_data, ( uint8_t * )serial_data->rx_uart_buffer, RX_SERIAL_BUFFER_SIZE );
    buffer_init_static( ( buffer_data_t * )&serial_data->tx_uart_buffer_data, ( uint8_t * )serial_data->tx_uart_buffer, TX_SERIAL_BUFFER_SIZE );

    serial_data->tx_busy = FALSE;

    device_data->dev_mode = DEV_MODE_CHANNEL;
    device_data->rx_channel = uart_read_buffer;
    device_data->tx_channel = uart_write_buffer;

    device->device_ptr = device_data;
    device->device_index = ( int32_t )index;

    return 0;
}

void serial_system_init( void )
{
}



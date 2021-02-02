#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////

enum
{
	I2C_TRANSMIT,
	I2C_RECEIVE
};

enum
{
	I2C_REQ_RD_ADDR_8BIT,
	I2C_REQ_RD_ADDR_16BIT,
	I2C_REQ_WR_ADDR_8BIT,
	I2C_REQ_WR_ADDR_16BIT

};

////////////////////////////////////////////////////////////////////////

#define I2C_SLAVE_ADDRESS7      		  0xA0
#define I2C_SPEED               		  100000

#define I2C_BUS_FLAG_TIMEOUT         	  ((uint32_t)0x1000)
#define I2C_BUS_LONG_TIMEOUT         	  ((uint32_t)(10 * I2C_BUS_FLAG_TIMEOUT))

#define TIMA_I2C                          I2C1
#define TIMA_I2C_CLK                      RCC_APB1Periph_I2C1

#define TIMA_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define TIMA_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define TIMA_I2C_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define TIMA_I2C_SCL_SOURCE               GPIO_PinSource6
#define TIMA_I2C_SCL_AF                   GPIO_AF_I2C1

#define TIMA_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define TIMA_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define TIMA_I2C_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define TIMA_I2C_SDA_SOURCE               GPIO_PinSource7
#define TIMA_I2C_SDA_AF                   GPIO_AF_I2C1

////////////////////////////////////////////////////////////////////

static void _i2c_gpio_init( void )
{
	GPIO_InitTypeDef  GPIO_InitStructure; 

	/*!< TIMA_I2C Periph clock enable */
	RCC_APB1PeriphClockCmd(TIMA_I2C_CLK, ENABLE);

	/*!< TIMA_I2C_SCL_GPIO_CLK and TIMA_I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_AHB1PeriphClockCmd(TIMA_I2C_SCL_GPIO_CLK | TIMA_I2C_SDA_GPIO_CLK, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Reset TIMA_I2C IP */
	RCC_APB1PeriphResetCmd(TIMA_I2C_CLK, ENABLE);

	/* Release reset signal of TIMA_I2C IP */
	RCC_APB1PeriphResetCmd(TIMA_I2C_CLK, DISABLE);

	/*!< GPIO configuration */
	/* Connect PXx to I2C_SCL*/
	GPIO_PinAFConfig(TIMA_I2C_SCL_GPIO_PORT, TIMA_I2C_SCL_SOURCE, TIMA_I2C_SCL_AF);
	/* Connect PXx to I2C_SDA*/
	GPIO_PinAFConfig(TIMA_I2C_SDA_GPIO_PORT, TIMA_I2C_SDA_SOURCE, TIMA_I2C_SDA_AF);  

	/*!< Configure TIMA_I2C pins: SCL */   
	GPIO_InitStructure.GPIO_Pin = TIMA_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(TIMA_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure TIMA_I2C pins: SDA */
	GPIO_InitStructure.GPIO_Pin = TIMA_I2C_SDA_PIN;
	GPIO_Init(TIMA_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);	
}

static void _i2c_bus_start_internal(uint8_t device_id, uint8_t direction)
{
	// wait until I2C1 is not busy anymore
	while(I2C_GetFlagStatus(TIMA_I2C, I2C_FLAG_BUSY));
	
	// Send I2C1 START condition 
	I2C_GenerateSTART(TIMA_I2C, ENABLE);

	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while(!I2C_CheckEvent(TIMA_I2C, I2C_EVENT_MASTER_MODE_SELECT));

	if(direction == I2C_TRANSMIT)
	{
		// Send slave Address for write 
		// I2C_Send7bitAddress(TIMA_I2C, device_address[address], I2C_Direction_Transmitter);
		I2C_SendData(TIMA_I2C, ( device_id << 1 ));

		/* wait for I2C1 EV6, check if 
		 * either Slave has acknowledged Master transmitter or
		 * Master receiver mode, depending on the transmission
		 * direction
		 */ 
		 
		while(!I2C_CheckEvent(TIMA_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_RECEIVE)
	{
		// Send slave Address for write 
		// I2C_Send7bitAddress(TIMA_I2C, device_address[address], I2C_Direction_Receiver);
		I2C_SendData(TIMA_I2C, ( device_id << 1 ) | 0x01);
		
		while(!I2C_CheckEvent(TIMA_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

////////////////////////////////////////////////////////////////////

void I2C_Bus_Init( void )
{
	I2C_InitTypeDef  I2C_InitStructure;

	_i2c_gpio_init();

	/*!< I2C configuration */
	/* TIMA_I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
	I2C_Init(TIMA_I2C, &I2C_InitStructure);

	/* TIMA_I2C Peripheral Enable */
	I2C_Cmd(TIMA_I2C, ENABLE);
}

void I2C_Bus_Start_Transmit(uint8_t device_id)
{
	_i2c_bus_start_internal( device_id, I2C_TRANSMIT );
}

void I2C_Bus_Start_Receive(uint8_t device_id)
{
	_i2c_bus_start_internal( device_id, I2C_RECEIVE );
}

void I2C_Write_Data(uint8_t data)
{
	I2C_SendData(TIMA_I2C, data);
	
	// wait for I2C1 EV8_2 --> byte has been transmitted
	while(!I2C_CheckEvent(TIMA_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t I2C_Read_Data(bool_t ack_flag)
{
	// disabe acknowledge of received data
	I2C_AcknowledgeConfig(TIMA_I2C, ack_flag);
	
	// wait until one byte has been received
	while( !I2C_CheckEvent(TIMA_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	
	// read data from I2C data register and return data byte
	return I2C_ReceiveData(TIMA_I2C);
}

void I2C_Bus_Stop(void)
{
	// Send I2C1 STOP Condition 
	I2C_GenerateSTOP(TIMA_I2C, ENABLE);
}


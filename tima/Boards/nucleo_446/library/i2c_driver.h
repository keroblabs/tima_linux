#ifndef _I2C_DRIVER_H_
#define _I2C_DRIVER_H_

/////////////////////////////////////////////////////////////////////

#include "types.h"

/////////////////////////////////////////////////////////////////////

void I2C_Bus_Init(void);

void I2C_Bus_Start_Transmit(uint8_t device_id);
void I2C_Bus_Start_Receive(uint8_t device_id);

void I2C_Write_Data(uint8_t data);
uint8_t I2C_Read_Data(bool_t ack_flag);

void I2C_Bus_Stop(void);

/////////////////////////////////////////////////////////////////////

#endif // _I2C_DRIVER_H_

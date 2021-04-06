#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//////////////////////////////////////////////////////////////////////////////

#include "types.h"

#include "device.h"
#include "t_heap.h"
#include "t_threads.h"
#include "gpio_driver.h"
#include "serial_driver.h"
#include "lcd.h"

////////////////////////////////////////////////////////////////////////////////

enum
{
    SYSTEM_INIT_MODULE,
    SYSTEM_DEVICE_DATA,
};

////////////////////////////////////////////////////////////////////////////////

void system_init( void );

//////////////////////////////////////////////////////////////////////////////

#endif // _SYSTEM_H_


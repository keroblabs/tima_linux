#ifndef BOARDS_INCLUDE_GPIO_DRIVER_H_
#define BOARDS_INCLUDE_GPIO_DRIVER_H_

///////////////////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////////////////

#define MODE_INPUT			0
#define MODE_OUTPUT 		1
#define MODE_COUNTER		2
#define MODE_INTERVAL		3

///////////////////////////////////////////////////////////////////////////

typedef enum
{
	GPIO_PE00,	GPIO_PE01,	GPIO_PE02,	GPIO_PE03,	GPIO_PE04,	GPIO_PE05,	GPIO_PE06,	GPIO_PE07,
	GPIO_PE08,	GPIO_PE09,	GPIO_PE10,	GPIO_PE11,	GPIO_PI14,	GPIO_PI15,	GPIO_PI00,	GPIO_PI01,
	GPIO_PI02,	GPIO_PI03,	GPIO_PI10,	GPIO_PI11,	GPIO_PC03,	GPIO_PC07,	GPIO_PC16,	GPIO_PC17,
	GPIO_PC18,	GPIO_PC23,	GPIO_PC24,	GPIO_PB03,	GPIO_PB04,	GPIO_PB05,	GPIO_PB06,	GPIO_PB07,
	GPIO_PB08,	GPIO_PB10,	GPIO_PB11,	GPIO_PB12,	GPIO_PB13,	GPIO_PB14,	GPIO_PB15,	GPIO_PB16,
	GPIO_PB17,	GPIO_PH24,	GPIO_PH25,	GPIO_PH26,	GPIO_PH27,	GPIO_PH00,	GPIO_PH02,	GPIO_PH07,
	GPIO_PH09,	GPIO_PH10,	GPIO_PH11,	GPIO_PH12,	GPIO_PH13,	GPIO_PH14,	GPIO_PH15,	GPIO_PH16,
	GPIO_PH17,	GPIO_PH18,	GPIO_PH19,	GPIO_PH20,	GPIO_PH21,	GPIO_PH22,	GPIO_PH23,	GPIO_PG00,
	GPIO_PG01,	GPIO_PG02,	GPIO_PG03,	GPIO_PG04,	GPIO_PG05,	GPIO_PG06,	GPIO_PG07,	GPIO_PG08,
	GPIO_PG09,	GPIO_PG10,	GPIO_PG11,	GPIO_PI16,	GPIO_PI17,	GPIO_PI18,	GPIO_PI19,

	GPIO_MAX

} gpio_t;

///////////////////////////////////////////////////////////////////////////

typedef struct time_log_t_
{
	uint32_t counter;
	uint64_t time_stamp;

} counter_log_t;

///////////////////////////////////////////////////////////////////////////

void gpio_init( void );

void * gpio_open_output( gpio_t gpio );
void * gpio_open_input( gpio_t gpio );
void * gpio_open_counter( gpio_t gpio );

void gpio_output( void * p_gpio, int state );
int  gpio_input( void * p_gpio );

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval );

int serial_get_usb_path( int index, char * tty_name );

///////////////////////////////////////////////////////////////////////////

#endif /* BOARDS_INCLUDE_GPIO_DRIVER_H_ */

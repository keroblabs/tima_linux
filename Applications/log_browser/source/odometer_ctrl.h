#ifndef APPLICATIONS_INSTRUMENTS_SOURCE4_ODOMETER_CTRL_H_
#define APPLICATIONS_INSTRUMENTS_SOURCE4_ODOMETER_CTRL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

typedef struct odometer_data_t_
{
    uint32_t incr_counter;
    uint32_t full_counter;

} odometer_data_t;

////////////////////////////////////////////////////////////////////

void odometer_control_add_speed_value( int value );
void odometer_control_reset( void );
void odometer_control_get( odometer_data_t * data );
void odometer_control_set( odometer_data_t * data );
void odometer_control_init( void );

////////////////////////////////////////////////////////////////////

#endif /* APPLICATIONS_INSTRUMENTS_SOURCE4_ODOMETER_CTRL_H_ */

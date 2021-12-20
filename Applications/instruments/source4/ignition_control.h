#ifndef SOURCE4_IGNITION_CONTROL_H_
#define SOURCE4_IGNITION_CONTROL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

bool_t ignition_control_get_key_state( void );
bool_t ignition_control_get_state( void );
void ignition_control_init( void );

////////////////////////////////////////////////////////////////////

#endif /* SOURCE4_IGNITION_CONTROL_H_ */
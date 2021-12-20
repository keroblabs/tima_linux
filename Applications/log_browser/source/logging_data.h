#ifndef APPLICATIONS_INSTRUMENTS_SOURCE4_LOGGING_DATA_H_
#define APPLICATIONS_INSTRUMENTS_SOURCE4_LOGGING_DATA_H_

////////////////////////////////////////////////////////////////////

#include "driving_data.h"
#include "odometer_ctrl.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void logging_data_save( void );
void logging_data_load( void );
void logging_data_init( void );

bool_t logging_data_load_record( uint32_t index, driving_data_t * driving_data, odometer_data_t * odometer_data );

////////////////////////////////////////////////////////////////////

#endif /* APPLICATIONS_INSTRUMENTS_SOURCE4_LOGGING_DATA_H_ */

#ifndef _THERMOMETER_CONTROL_H_
#define _THERMOMETER_CONTROL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

bool_t thermometer_load( home_data_t * home_data, string_t * line, FILE * fp );

void thermometer_save( home_data_t * home_data, FILE * fp );

bool_t thermometer_get( home_data_t * home_data, thermometer_t ** thermometer_data );

thermometer_t * thermometer_locate_from_room( home_data_t * home_data, const char * room );

////////////////////////////////////////////////////////////////////

#endif /* _THERMOMETER_CONTROL_H_ */

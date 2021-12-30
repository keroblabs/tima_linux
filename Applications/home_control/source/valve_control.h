#ifndef _VALVE_CONTROL_H_
#define _VALVE_CONTROL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

bool_t valve_load( home_data_t * home_data, string_t * line, FILE * fp );

void valve_save( home_data_t * home_data, FILE * fp );

bool_t valve_get( home_data_t * home_data, valve_t ** valve_data );

valve_t * valve_locate_from_room( home_data_t * home_data, const char * room );

void valve_process( home_data_t * home_data );

////////////////////////////////////////////////////////////////////

#endif /* _VALVE_CONTROL_H_ */
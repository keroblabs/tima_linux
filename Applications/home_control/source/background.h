#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "settings.h"
#include "string_lib.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void background_init( void );

void background_run( home_data_t * home_data );

void background_update_sensor( home_data_t * home_data, const char * ref, const char * value );
void background_update_pushbutton( home_data_t * home_data, const char * ref, const char * value );
void background_update_humidity( home_data_t * home_data, const char * ref, const char * value );

string_t * background_spawn( const char * command );

////////////////////////////////////////////////////////////////////

#endif /* _BACKGROUND_H_ */

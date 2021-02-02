#ifndef instruments_h
#define instruments_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "skin_data.h"

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

void instruments_init( void );

void instruments_set_rpm( skin_rpm_cmd_t * cmd );
void instruments_set_speed( skin_speed_cmd_t * cmd );
void instruments_set_fuel( skin_fuel_cmd_t * cmd );
void instruments_set_temperature( skin_temperature_cmd_t * cmd );

int instruments_get_rpm( void );
int instruments_get_speed( void );
int instruments_get_fuel( void );
int instruments_get_temperature( void );

uint32_t instruments_get_odometer( void );

void instruments_set_odometer_count( skin_odometer_cmd_t * cmd );

void instruments_reload( void );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* instruments_h */

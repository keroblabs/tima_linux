#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"

////////////////////////////////////////////////////////////////////

typedef struct eqiva_status_t_
{
    int temperature;
    uint8_t valve_pos;
    
    bool_t low_battery;
    
} eqiva_status_t;

////////////////////////////////////////////////////////////////////

bool_t bluetooth_eqiva_valve_read_status( home_data_t * home_data, const char * address, eqiva_status_t * eqiva_status );

bool_t bluetooth_eqiva_set_temperature( home_data_t * home_data, const char * address, uint8_t temperature, eqiva_status_t * eqiva_status );

uint8_t bluetooth_xiaomi_read_temperature( home_data_t * home_data, const char * address );

////////////////////////////////////////////////////////////////////

#endif /* _BLUETOOTH_H_ */

#ifndef SOURCE_ELM_327_MONITOR_H_
#define SOURCE_ELM_327_MONITOR_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

// #define TESTBENCH 1

////////////////////////////////////////////////////////////////////

typedef struct elm_327_data_t_
{
    int rpm;
    int speed;
    int temp;
    uint8_t bitmask;

} elm_327_data_t;

////////////////////////////////////////////////////////////////////

void elm_327_monitor_init( char * dev_name );

////////////////////////////////////////////////////////////////////

#endif /* SOURCE_ELM_327_MONITOR_H_ */

#ifndef _DRIVER_CTRL_H_
#define _DRIVER_CTRL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"
#include "string_lib.h"
#include "lists.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////

#define DRIVER_HEADER               "driver"

#define ESPEASY_PARAM               "espeasy"
#define XIAOMI_PARAM                "xiaomi"
#define EQIVA_PARAM                 "eqiva"
#define TIMA_PARAM                  "tima"
#define LOCAL_PARAM                 "local"
#define PARAM_DELAY_OFF             "delayed"

////////////////////////////////////////////////////////////////////

typedef enum
{
    Driver_None,
    Driver_EspEasy,
    Driver_Tima,
    Driver_Local,
    Driver_Internal,
} driver_type_t;

typedef struct _driver_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    driver_type_t type;
    char command[40];

    timer_data_t delay_off;
    uint32_t delay_ms;

    bool_t current_state;
} driver_t;

////////////////////////////////////////////////////////////////////

bool_t driver_get( home_data_t * home_data, driver_t ** driver_data );
void driver_load( home_data_t * home_data, string_t * line, FILE * fp );

driver_t * driver_locate( home_data_t * home_data, const char * name );

void driver_process( home_data_t * home_data );
void driver_save( home_data_t * home_data, FILE * fp );

void driver_set_state( driver_t * driver, bool_t state );
bool_t driver_get_state( home_data_t * home_data, const char * name );

////////////////////////////////////////////////////////////////////

#endif /* _DRIVER_CTRL_H_ */

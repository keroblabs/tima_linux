#ifndef APPLICATIONS_HOME_CONTROL_LIBRARY_SENSOR_CTRL_H_
#define APPLICATIONS_HOME_CONTROL_LIBRARY_SENSOR_CTRL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"
#include "string_lib.h"
#include "lists.h"

////////////////////////////////////////////////////////////////////

#define SENSOR_HEADER               "sensor"

#define PARAM_TYPE                  "type"

#define SENSOR_PARAM_TEMPERATURE    "temperature"
#define SENSOR_PARAM_HUMIDITY       "humidity"
#define SENSOR_PARAM_SWITCH         "switch"
#define SENSOR_PARAM_BUTTON         "button"
#define SENSOR_PARAM_VALVE_EQIVA    "eqiva"
#define SENSOR_PARAM_VALVE_TIME     "valve_tima"
#define SENSOR_PARAM_INTERNAL       "internal"
#define SENSOR_PARAM_INVERTED       "inverted"

#define PARAM_VALUE_ON              "value_on"
#define PARAM_VALUE_OFF             "value_off"

#ifndef PARAM_DRIVER
#define PARAM_DRIVER                "driver"
#endif

////////////////////////////////////////////////////////////////////

typedef enum
{
    History_File_Idle,
    History_File_Logging,
    History_File_Finished,
} history_state_t;

typedef enum
{
    Sensor_Temperature,
    Sensor_Humidity,
    Sensor_Switch,
    Sensor_Button,
    Sensor_Valve_Eqiva,
    Sensor_Valve_Tima,
    Sensor_Internal,
} sensor_type_t;

typedef struct _sensor_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    sensor_type_t type;

    bool_t is_inverted;
    float prev_value;
    float value;
    float value_on;
    float value_off;
    float history[24*60];
    
    string_t * file_history;
    history_state_t history_state;

    void * driver;
} sensor_t;

////////////////////////////////////////////////////////////////////

bool_t sensor_get( home_data_t * home_data, sensor_t ** data );

bool_t sensor_get_state( sensor_t * data );

float sensor_get_value( home_data_t * home_data, const char * name );

void sensor_load( home_data_t * home_data, string_t * line, FILE * fp );

sensor_t * sensor_locate( home_data_t * home_data, const char * name );

bool_t sensor_record_value( home_data_t * home_data, string_t * cmd, string_t * field, string_t * value );

void sensor_process( home_data_t * home_data );

////////////////////////////////////////////////////////////////////

#endif /* APPLICATIONS_HOME_CONTROL_LIBRARY_SENSOR_CTRL_H_ */

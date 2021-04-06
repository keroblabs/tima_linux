#ifndef _SETTINGS_H_
#define _SETTINGS_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "lists.h"
#include "string_lib.h"
#include "home_data.h"

////////////////////////////////////////////////////////////////////

#define ROOM_BITMASK_PRIORITY       0x01
#define ROOM_BITMASK_BOOST          0x02
#define ROOM_DATA_FILE              "room_data.txt"

////////////////////////////////////////////////////////////////////

#define PROFILE_HEADER              "profile"
#define SETTINGS_HEADER             "settings"
#define HOT_WATER_HEADER            "hot_water"
#define VALVE_HEADER                "valve"
#define THERMOMETER_HEADER          "thermometer"
#define DRIVER_HEADER               "driver"

#define ESPEASY_PARAM               "espeasy"
#define TARGET_PARAM                "target"
#define LEVEL_PARAM                 "level"
#define ROOM_HEADER                 "room"
#define COMMAND_PARAM               "command"
#define SETTINGS_PARAM              "settings"
#define EQIVA_PARAM                 "eqiva"
#define CONTROL_PARAM               "control"
#define XIAOMI_PARAM                "xiaomi"
#define HOT_WATER_PARAM             "hot_water"
#define TIMA_PARAM                  "tima"
#define LOCAL_PARAM                 "local"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

string_t * settings_get_line_string( FILE * fp );
string_t * settings_get_line_header( FILE * fp );
string_t * settings_get_param( string_t * line, const char * field );
string_t * settings_locate_param( string_t * line, const char * param );

uint32_t settings_get_numbers( string_t * line, int * list, uint32_t max_size );

super_item_t * settings_locate_item( list_t * list, const char * name );
super_item_t * settings_create_item( string_t * line, const char * header, size_t size );

void settings_init( home_data_t * home_data );
void settings_load( home_data_t * home_data, const char * filename );
void settings_save( home_data_t * home_data, const char * filename );
void settings_destroy( home_data_t * home_data );

void settings_set_repeater( home_data_t * home_data, const char * repeater_address, const char * device_address );

string_t * settings_get_repeater( home_data_t * home_data, const char * device_address );

////////////////////////////////////////////////////////////////////

#endif /* _SETTINGS_H_ */

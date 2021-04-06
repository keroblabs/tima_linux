#ifndef _HOME_DATA_H_
#define _HOME_DATA_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "lists.h"
#include "string_lib.h"

////////////////////////////////////////////////////////////////////

#define DRIVER_MAX_ROOMS            16
#define VALVE_MAX_ROOMS             4
#define THERMOMETER_MAX_ROOMS       4

#define ROOM_VALID_TEMPERATURE      0x01
#define ROOM_TEMPERATURE_BOOST      0x02
#define ROOM_RECEIVED_TEMPERATURE   0x04
#define ROOM_RECEIVED_HUMIDITY      0x08

////////////////////////////////////////////////////////////////////

#define GET_ITEM_FROM_LIST(type, list, arg)     type * item; \
                                                if( *arg == NULL ) item = (type*)list_get_head(&list); \
                                                else item = (type*)list_get_next(&list, &((*arg)->node)); \
                                                *arg = item; \
                                                if(item == NULL) return FALSE; \
                                                return TRUE;

////////////////////////////////////////////////////////////////////

typedef enum
{
    Valve_None,
    Valve_Eqiva,
    Valve_Tima,
} valve_type_t;

typedef enum
{
    Driver_None,
    Driver_EspEasy,
    Driver_Tima,
    Driver_Local,
} driver_type_t;

typedef enum
{
    Source_None,
    Source_Valve,
    Source_HotWater,
    Source_RoomTemperature,
} driver_source_t;

typedef enum
{
    Thermometer_Http,
    Thermometer_Xiaomi,
    Thermometer_Tima,
} thermometer_type_t;

typedef struct _repeater_t
{
    list_node_t node;
    
    char device_address[30];
    char repeater_address[30];
} repeater_t;

typedef enum
{
    Room_State_Boot,
    Room_State_Setup,
    Room_State_Collecting,
    
} room_day_state_t;

typedef struct _config_entry_t
{
    list_node_t node;
    
    int start_hour;
    int start_min;
    int end_hour;
    int end_min;
    int temperature;
} config_entry_t;

typedef struct _super_item_t
{
    list_node_t node;
    char name[30];
    void * p_home;

} super_item_t;

typedef struct _profile_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    list_t entry_list;
} profile_t;

typedef struct _settings_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    profile_t * profile_list[4];
} settings_t;

typedef struct _list_fp_t
{
    list_node_t node;
    int index;
    fpos_t file_pos;
    
} entry_fpos_t;

typedef struct _room_data_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    char command[30];
    float temperature;
    float humidity;
    int valve_pos;
    
    uint32_t boost_start_time;
    uint8_t bitmask;
    list_t graph_pos_list;
    int recorded_hour;
    room_day_state_t state;
    
    string_t * dir_history;
    string_t * file_history;
    string_t * graph_title;

    float temp_history[24*60];
    float humid_history[24*60];
    int valve_history[24*60];
    int target_history[24*60];

    int curr_profile;
    settings_t * settings;
} room_data_t;

typedef struct _valve_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    valve_type_t type;
    char address[30];
    
    int pos_threshold;
    int pos_offset;
    
    int temperature;
    uint8_t valve_pos;
    bool_t low_battery;
    
    room_data_t * room_target;
} valve_t;

typedef struct _driver_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    driver_type_t type;
    char command[40];
    
    bool_t current_state;
    
    room_data_t * room_list[DRIVER_MAX_ROOMS];
} driver_t;

typedef struct _thermometer_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    thermometer_type_t type;
    char address[30];
    bool_t is_updated;
    
    room_data_t * room_list[THERMOMETER_MAX_ROOMS];
} thermometer_t;

typedef struct _home_data_t
{
    list_t room_list;
    list_t settings_list;
    list_t profile_list;
    list_t repeater_list;
    list_t driver_list;
    list_t valve_list;
    list_t thermometer_list;
    
    room_data_t * hot_water;
    
    string_t * root_dir;
} home_data_t;

////////////////////////////////////////////////////////////////////

#endif /* _HOME_DATA_H_ */

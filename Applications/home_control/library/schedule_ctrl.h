#ifndef APPLICATIONS_HOME_CONTROL_LIBRARY_SCHEDULE_CTRL_H_
#define APPLICATIONS_HOME_CONTROL_LIBRARY_SCHEDULE_CTRL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"
#include "string_lib.h"
#include "lists.h"

////////////////////////////////////////////////////////////////////

#define SCHEDULE_HEADER             "schedule"

#define PARAM_PROFILE               "profile"

#ifndef PARAM_DRIVER
#define PARAM_DRIVER                "driver"
#endif

////////////////////////////////////////////////////////////////////

typedef struct _schedule_item_t
{
    list_node_t node;

    int start_hour;
    int start_min;
    int end_hour;
    int end_min;

} schedule_item_t;

typedef struct _schedule_t
{
    list_node_t node;
    char name[30];
    void * p_home;

    uint8_t profile;

    void * driver;
    list_t schedule_list;
    bool_t schedule_on;
} schedule_t;

////////////////////////////////////////////////////////////////////

void schedule_init( home_data_t * home_data );

void schedule_destroy( home_data_t * home_data );

void schedule_load( home_data_t * home_data, string_t * line, FILE * fp );

bool_t schedule_get( home_data_t * home_data, schedule_t ** data );

schedule_t * schedule_locate( home_data_t * home_data, const char * name );

bool_t schedule_check( schedule_t * schedule, uint8_t profile );

void schedule_process( home_data_t * home_data );

////////////////////////////////////////////////////////////////////

#endif

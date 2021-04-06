#ifndef _HOME_DATA_H_
#define _HOME_DATA_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "lists.h"
#include "string_lib.h"

////////////////////////////////////////////////////////////////////

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

typedef void * (*comm_handler_t)( void * param0, void * param1, void * param2, void * param3, void * param4 );

typedef struct _super_item_t
{
    list_node_t node;
    char name[30];
    void * p_home;

} super_item_t;

typedef struct _home_data_t
{
    list_t sensor_list;
    list_t driver_list;
    list_t schedule_list;

    string_t * root_dir;
    char config_file[200];

    uint8 active_profile;
    
    comm_handler_t page_handler;
    comm_handler_t setup_handler;
    comm_handler_t status_handler;
} home_data_t;

////////////////////////////////////////////////////////////////////

#endif /* _HOME_DATA_H_ */

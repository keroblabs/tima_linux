#ifndef _NET_COMMS_H_
#define _NET_COMMS_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "settings.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void net_comms_init( home_data_t * home_data );
string_t * net_comms_get_ip( char * interface );

void net_comms_set_page_handler( home_data_t * home_data, comm_handler_t handler );
void net_comms_set_setup_handler( home_data_t * home_data, comm_handler_t handler );
void net_comms_set_sensor_handler( home_data_t * home_data, comm_handler_t handler );
void net_comms_set_status_handler( home_data_t * home_data, comm_handler_t handler );

////////////////////////////////////////////////////////////////////

#endif /* _NET_COMMM_H_ */

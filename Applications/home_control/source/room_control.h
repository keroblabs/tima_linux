#ifndef _ROOM_CONTROL_H_
#define _ROOM_CONTROL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "home_data.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void room_destroy_profile( list_node_t * node );
void room_destroy_room_data( list_node_t * node );

void room_save( home_data_t * home_data, FILE * fp );

bool_t room_load( home_data_t * home_data, string_t * line, FILE * fp );
bool_t room_get( home_data_t * home_data, room_data_t ** room_data );
bool_t room_hot_water_get( home_data_t * home_data, room_data_t ** room_data );

profile_t * room_locate_profile( home_data_t * home_data, const char * name );
settings_t * room_locate_settings( home_data_t * home_data, const char * name );

room_data_t * room_locate( home_data_t * home_data, const char * name );
room_data_t * room_locate_room_by_ref( home_data_t * home_data, const char * ref );

bool_t room_get_target_temperature( room_data_t * room_data, int * temperature );

void room_store_recorded_data( room_data_t * room_data );

void room_save_temperature_history( room_data_t * room_data );

void room_data_generate_graphic( room_data_t * room_data, string_t ** response );

////////////////////////////////////////////////////////////////////

#endif /* _ROOM_CONTROL_H_ */

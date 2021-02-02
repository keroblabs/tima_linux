#ifndef BOARDS_RPI_LIBRARY_SPAWN_LIB_H_
#define BOARDS_RPI_LIBRARY_SPAWN_LIB_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

typedef void ( *spawn_line_handler_t )( void * data, const char *line );

////////////////////////////////////////////////////////////////////

int spawn_command( const char * command );

void spawn_command_ex( const char * command, spawn_line_handler_t handler, void * data );

void * spawn_command_start( const char * command );

bool_t spawn_command_read( void * hdl, char * out_buffer, int max_size );

void spawn_command_close( void * hdl );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_RPI_LIBRARY_SPAWN_LIB_H_ */

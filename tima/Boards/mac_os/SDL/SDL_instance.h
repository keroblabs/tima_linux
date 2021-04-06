#ifndef BOARDS_MAC_OS_SDL_SDL_INSTANCE_H_
#define BOARDS_MAC_OS_SDL_SDL_INSTANCE_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void sdl_instance_init( void );

void sdl_instance_switch_context( void );

int sdl_get_thread_index( void );

void * sdl_get_window_data( void );
void sdl_set_window_data( void * data );
void * sdl_get_window_data_from_index( int index );

const void * sdl_get_rom_data( void );
void sdl_set_rom_data( const char * data );

uint8_t * sdl_instance_add_ram_data( uint16_t size );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_MAC_OS_SDL_SDL_INSTANCE_H_ */

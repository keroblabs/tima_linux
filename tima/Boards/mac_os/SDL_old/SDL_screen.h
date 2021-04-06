#ifndef BOARDS_MAC_OS_SDL_SDL_SCREEN_H_
#define BOARDS_MAC_OS_SDL_SDL_SCREEN_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void sdl_screen_init( void );
void sdl_screen_stop( void );

void sdl_lcd_init( void );

void sdl_update_window( void );
void * sdl_GetTarget( void );
void sdl_clear_screen( void );
void sdl_set_contrast( uint8_t level );
void sdl_set_backlight( bool_t state );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_MAC_OS_SDL_SDL_SCREEN_H_ */

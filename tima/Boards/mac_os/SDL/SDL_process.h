#ifndef BOARDS_MAC_OS_SDL_SDL_PROCESS_H_
#define BOARDS_MAC_OS_SDL_SDL_PROCESS_H_

////////////////////////////////////////////////////////////////////

#include "SDL_internal.h"

////////////////////////////////////////////////////////////////////

typedef void ( *sdl_delegate_t )( void * data );
typedef void ( *loop_handler_t )( void );

typedef void ( *sdl_keypad_down_event_t )( SDL_Keycode sym );
typedef void ( *sdl_mouse_event_t )( uint32_t type, SDL_MouseButtonEvent event );
typedef void ( *sdl_text_input_event_t )( uint8_t keycode );

////////////////////////////////////////////////////////////////////

typedef struct sdl_loop_t_
{
    loop_handler_t handler;
    struct sdl_loop_t_ * next;
    
} sdl_loop_t;

typedef struct condition_signal_t_
{
    SDL_mutex *mutex;
    SDL_cond  *condition;
    bool_t flag;
    bool_t state;
    SDL_mutex *mutex_state;
    
} condition_signal_t;

////////////////////////////////////////////////////////////////////

void sdl_event_init( void );
void sdl_signal_create( condition_signal_t * signal );
void sdl_signal_wait( condition_signal_t * signal );
void sdl_signal_continue( condition_signal_t * signal );

bool_t sdl_signal_state( condition_signal_t * signal );

void sdl_instance_send_message( int message_code, void * data1, void * data2 );
void sdl_add_event_loop( sdl_loop_t * event );
void sdl_add_quit_handler( sdl_loop_t * event );

int sdl_event_loop( void );

void sdl_set_text_input_event( sdl_text_input_event_t input );
void sdl_set_keydown_event( sdl_keypad_down_event_t input );
void sdl_set_mouse_event( sdl_mouse_event_t input );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_MAC_OS_SDL_SDL_PROCESS_H_ */

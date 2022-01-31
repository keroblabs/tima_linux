#ifndef BOARDS_MACOS_SDL_SDL_INTERNAL_H_
#define BOARDS_MACOS_SDL_SDL_INTERNAL_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

#ifdef WIN32
#include <SDL.h>
#include <Windows.h>
#include <conio.h>
#elif defined __MACH__
#include <SDL2/SDL.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#endif

#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "pipe.h"
#include "device.h"
//#include "fsm.h"

////////////////////////////////////////////////////////////////////

#define MAX_INSTANCES           10

#define SDL_INTERNAL_DELEGATE   1

////////////////////////////////////////////////////////////////////

typedef void ( *sdl_delegate_t )( void * data );
typedef void ( *loop_handler_t )( void );

////////////////////////////////////////////////////////////////////

typedef struct sdl_loop_t_
{
    loop_handler_t handler;
    struct sdl_loop_t_ * next;
    
} sdl_loop_t;

////////////////////////////////////////////////////////////////////

typedef struct window_data_t_
{
    SDL_Window *   window;
    SDL_Surface *  surface;
    SDL_Renderer * renderer;
    SDL_Texture *  texture;
    
    uint32_t vsync_ms;
    
} window_data_t;

typedef struct condition_signal_t_
{
    SDL_mutex *mutex;
    SDL_cond  *condition;
    bool_t flag;
    bool_t state;
    SDL_mutex *mutex_state;

} condition_signal_t;

typedef struct thread_list_t_
{
    SDL_Thread * thread;
    SDL_threadID id;

    uint16_t printf_port;
    uint32_t socket_printf;
    device_t dev_printf;
    //fsm_instance_t fsm_instance;
    
    uint8_t current_channel;
    pipe_data_t send_pipe;
    pipe_data_t receive_pipe;
    bool_t last_tx_good;
    bool_t tx_completed;
    bool_t is_listening;
    void * failed_frame;
    
    condition_signal_t signal;
    
    window_data_t window_data;
    
    const void * rom_data;
    
} instance_data_t;

////////////////////////////////////////////////////////////////////

void sdl_instance_init( void );
int sdl_get_thread_index( void );
void sdl_instance_yield( void );
void sdl_add_event_loop( sdl_loop_t * event );

instance_data_t * sdl_get_current_instance( void );
instance_data_t * sdl_get_instance_from_index( int index );
instance_data_t * sdl_alloc_instance( void );

window_data_t * sdl_get_window_data( void );

void sdl_mouse_init( void );
void sdl_mouse_event( uint32_t type, SDL_MouseButtonEvent event );
int sdl_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz );

void sdl_text_input_event( uint8_t keycode );
void sdl_keypad_down_event( SDL_Keycode sym, Uint32 type );
int sdl_library_kbhit( void );
void sdl_input_event( void );
void keybdrv_mouse_set_state( bool_t state );

void sdl_lcd_stop( void );
void sdl_lcd_init( void );

void sdl_instance_send_message( int message_code, void * data1, void * data2 );
void sdl_startup_background( void );

void sdl_signal_create( condition_signal_t * signal );
void sdl_signal_wait( condition_signal_t * signal );
void sdl_signal_continue( condition_signal_t * signal );
bool_t sdl_signal_state( condition_signal_t * signal );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_MACOS_SDL_SDL_INTERNAL_H_ */

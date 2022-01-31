//Using SDL and standard IO

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

#include "types.h"

////////////////////////////////////////////////////////////////////

static uint32_t mouse_x;
static uint32_t mouse_y;
static unsigned int mouse_button;
static unsigned int mouse_trigg;

static uint16_t mouse_min_x = 0;
static uint16_t mouse_max_x = 560;
static uint16_t mouse_min_y = 0;
static uint16_t mouse_max_y = 192;

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void sdl_mouse_init( void )
{
    mouse_trigg = 0;
    mouse_button = 0;
}

void keybdrv_mouse_set_state( bool_t state )
{
    SDL_ShowCursor( ( state == TRUE ) ? SDL_DISABLE : SDL_ENABLE );
}

void keybdrv_mouse_set_limits( uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y )
{
    mouse_max_x = (int)max_x;
    mouse_min_x = (int)min_x;
    mouse_max_y = (int)max_y;
    mouse_min_y = (int)min_y;
}

void keybdrv_mouse_set_pos( uint16_t posx, uint16_t posy )
{
    mouse_x = ( posx * _USE_SCREEN_WIDTH ) / ( mouse_max_x - mouse_min_x );
    mouse_y = ( posx * _USE_SCREEN_HEIGHT ) / ( mouse_max_y - mouse_min_y );
}

bool_t keybdrv_mouse_get_pos( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
    if( mouse_trigg == 1 )
    {
        mouse_trigg = 0;
        
        *posx = ( uint16_t )( ( ( mouse_max_x - mouse_min_x ) * mouse_x ) / _USE_SCREEN_WIDTH );
        *posy = ( uint16_t )( ( ( mouse_max_y - mouse_min_y ) * mouse_y ) / _USE_SCREEN_HEIGHT );
        *posz = ( mouse_button ) ? 100 : 0;
        
        return TRUE;
    }
    
    return FALSE;
}

void sdl_mouse_event( uint32_t type, SDL_MouseButtonEvent event )
{
    switch( type )
    {
        case SDL_MOUSEBUTTONDOWN:
            mouse_x = event.x;
            mouse_y = event.y;
            if( event.button == SDL_BUTTON_LEFT )
            {
                mouse_button = 1;
            }
            else if( event.button == SDL_BUTTON_RIGHT )
            {
                mouse_button = 2;
            }
            else break;
            mouse_trigg = 1;
            break;
            
        case SDL_MOUSEBUTTONUP:
            if( mouse_button == 0 ) break;
            mouse_button = 0;
            mouse_x = event.x;
            mouse_y = event.y;
            mouse_trigg = 1;
            break;
            
        case SDL_MOUSEMOTION:
            // uncomment the line below to enable touchscreen mode
            // comment the line below to enable mouse mode
            //if( mouse_button == 0 ) break;
            
            mouse_x = event.x;
            mouse_y = event.y;
            mouse_trigg = 1;
            
            //printf( "%4d x %4d\n", mouse_x, mouse_y );
            break;
    }
}

#include "SDL_touch_driver.h"
#include "SDL_process.h"
#include "SDL_internal.h"

////////////////////////////////////////////////////////////////////

static unsigned int mouse_x;
static unsigned int mouse_y;
static unsigned int mouse_button;
static unsigned int mouse_trigg;

static bool_t is_init = FALSE;

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static void sdl_mouse_event( uint32_t type, SDL_MouseButtonEvent event )
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
            if( mouse_button == 0 ) break;
            
            mouse_x = event.x;
            mouse_y = event.y;
            mouse_trigg = 1;
            break;
    }
}

void sdl_mouse_init( void )
{
    if( is_init == FALSE )
    {
        mouse_trigg = 0;
        mouse_button = 0;

        sdl_set_mouse_event( sdl_mouse_event );
    }
}

int sdl_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
    if( mouse_trigg == 1 )
    {
        mouse_trigg = 0;
        
        *posx = ( unsigned short )mouse_x;
        *posy = ( unsigned short )mouse_y;
        *posz = 0;
        
        if( mouse_button ) *posz = 100;
        return 1;
    }
    
    return 0;
}

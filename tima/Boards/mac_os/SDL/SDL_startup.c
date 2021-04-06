#include "SDL_internal.h"
#include "SDL_process.h"
#include "SDL_instance.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

int SDL_main( int argc, char* argv[] )
{
    sdl_event_init();
    sdl_instance_init();

    while( 1 )
    {
        sdl_event_loop();
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

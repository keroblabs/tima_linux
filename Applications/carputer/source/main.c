#include "system.h"
#include "graphics.h"
#include "timer.h"
#include "draw.h"
#include "mp3_player.h"

///////////////////////////////////////////////////////////////////////////////////////

#define BASE_PATH       "/Users/marciocherobim/Projects/GIT_Dev/tima_linux/Applications/carputer/music/"
#define MUSIC_FILE      BASE_PATH"Reverse - Absolute Reality (Arty Remix).mp3"

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    timer_data_t update_clock;
    uint16_t mouse_posx, mouse_posy, mouse_posz;
    
    system_init();
    graphics_init();

	timer_Init();

    printf( "Tima carputer\r\n" );
    
    while( 1 )
	{
        if( timer_Check( &update_clock ) )
        {
        }
        
        if( lcd_driver_read_mouse( &mouse_posx, &mouse_posy, &mouse_posz ) )
        {
            //printf( "mouse: x=%d, y=%d, z=%d\n", mouse_posx, mouse_posy, mouse_posz );
            //touchscreen_lib_set_reading( mouse_posx, mouse_posy, mouse_posz );
        }

        tthread_sleep_ms( 10 );
        graphics_process();
	}

	return 0;
}

#include "system.h"
#include "timer_class.h"
#include "bitmap_class.h"
#include "bitmap_draw_class.h"
#include "hardware_class.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
	int i = 0;
    timer_class_t * timer_class;
    timer_class_t * timer2;

    system_init();
    STATIC_METHOD( hardware_class_t, init )();

    timer_class = NEW_CLASS(timer_class_t)(0);
    timer_class->start( 1000 );
    
    timer2 = NEW_CLASS(timer_class_t)( 500 );
    
    bitmap_class_t * screen = STATIC_METHOD( bitmap_class_t, from_driver )();
    bitmap_draw_class_t * screen_draw = NEW_CLASS( bitmap_draw_class_t )( screen );
    
    screen_draw->draw_circle( 100, 100, 30, APP_RGB( 255, 0, 0 ) );
    screen_draw->draw_line( 100, 100, 150, 300, APP_RGB( 0, 255, 0 ) );

    while( 1 )
    {
    	if( timer_class->check() )
    	{
            timer_class->reload();
            printf( "Counter %d\r\n", i );
            i++;
    	}
        
        if( timer2->check() )
        {
            timer2->reload();
            printf( "timer2\n" );
        }
    }

	return 0;
}

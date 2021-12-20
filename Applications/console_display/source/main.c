#include "system.h"
#include "graphics.h"
#include "bitmap.h"
#include "capture.h"
#include "timer.h"
#include "yuv_to_rgb.h"

static void hdmi_console_correction( void )
{
    void * lcd = graphics_claim();
    bitmap_t * lcd_driver = ( bitmap_t * )lcd;
    lcd_driver->width += 8;
    graphics_release();
}

static void hdmi_touchscreen_update( uint16_t * posx, uint16_t * posy )
{
    int temp_x = (((3700 - *posx) * 43) >> 8);
    int temp_y = (((4000 - *posy) * 68) >> 8);
    *posx = ( temp_x > 600 ) ? 600 : ( ( temp_x < 0 ) ? 0 : temp_x );
    *posy = ( temp_y > 1024 ) ? 1024 : ( ( temp_y < 0 ) ? 0 : temp_y );
}

static void show_capture( void * p_data, const void *p, uint16_t width, uint16_t height )
{
    bitmap_t * lcd = ( bitmap_t * )graphics_claim();
    yuv_to_rgb_display( p, NULL, lcd, width, height, 36, 150 );
    graphics_release();
}

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    uint16_t mouse_posx, mouse_posy, mouse_posz;

    system_init();
    graphics_init();
    hdmi_console_correction();
    timer_Init();
    yuv_to_rgb_init();

    bitmap_t * switch_bmp = bitmap_load_file( "switch_down.bmp" );

    void * lcd = graphics_claim();
    graphics_show_bitmap( ( bitmap_t * )lcd, 0, 75, switch_bmp, FALSE );
    //graphics_fill_box( lcd, 0, 0, 100, 100, APP_RGB(255,0,0) );
    graphics_release();

    void * capture = capture_start( "/dev/video0", show_capture, NULL );

    while( 1 )
    {
        if( lcd_driver_read_mouse( &mouse_posx, &mouse_posy, &mouse_posz ) )
        {
            hdmi_touchscreen_update( &mouse_posx, &mouse_posy );
            printf( "mouse: x=%d, y=%d, z=%d\n", mouse_posx, mouse_posy, mouse_posz );
        }

        //capture_loop( capture );
        graphics_process();
    }

    return 0;
}

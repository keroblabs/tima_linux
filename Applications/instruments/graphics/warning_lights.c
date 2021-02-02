#include "warning_lights.h"
#include "bitmap.h"

////////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
#define BITMAP_DIR "/Users/marciocherobim/Projects/linux_a20/tima_linux/Applications/instruments/bitmaps/"
#else
#define BITMAP_DIR "./bitmaps/"
#endif

////////////////////////////////////////////////////////////////////////////////////////

typedef struct _warning_bitmap_t
{
    warning_t warning;
    bitmap_t * bitmap;
    
} warning_bitmap_t;

typedef struct shift_light_data_t_
{
    uint16_t posx;
    uint16_t posy;

    bool_t state;

    bitmap_t * bitmap[2];
    
} shift_light_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static const char * shift_light_names[] =
{
    BITMAP_DIR"shift_light_off.bmp",
    BITMAP_DIR"shift_light.bmp",
};

static const char * bitmap_names[] =
{
    BITMAP_DIR"battery.bmp",
    BITMAP_DIR"brake_service.bmp",
    BITMAP_DIR"parking_brake.bmp",
    BITMAP_DIR"dim_lights.bmp",
    BITMAP_DIR"high_beam.bmp",
    BITMAP_DIR"fog_lights.bmp",
    BITMAP_DIR"left_indicator.bmp",
    BITMAP_DIR"right_indicator.bmp",
    BITMAP_DIR"temperature-blue.bmp",
    BITMAP_DIR"temperature-warning.bmp",
    BITMAP_DIR"fuel-warning-blue.bmp",
    BITMAP_DIR"fuel-warning-light.bmp",
    BITMAP_DIR"oil_pressure.bmp",
    BITMAP_DIR"engine.bmp",
    BITMAP_DIR"hazard_warning.bmp",
    BITMAP_DIR"washers.bmp",
    BITMAP_DIR"key_missing.bmp",
    BITMAP_DIR"headlamps.bmp",
};

////////////////////////////////////////////////////////////////////////////////////////

static bitmap_t * warning_bitmap[WARNING_MAX_TOTAL];

static shift_light_data_t shift_light_data;

////////////////////////////////////////////////////////////////////////////////////////

void warning_lights_init( void )
{
    int cnt;
    
    for( cnt = 0; cnt < WARNING_MAX_TOTAL; cnt++ )
    {
        warning_bitmap[cnt] = bitmap_load_file( bitmap_names[cnt] );
    }
}

void warning_lights_show( void * p_lcd, warning_t warning, uint16_t posx, uint16_t posy )
{
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    graphics_show_bitmap( lcd, posx, posy, warning_bitmap[(int)warning], TRUE );
}

void warning_shift_light_init( uint16_t posx, uint16_t posy )
{
    shift_light_data.bitmap[0] = bitmap_load_file( shift_light_names[0] );
    shift_light_data.bitmap[1] = bitmap_load_file( shift_light_names[1] );
    shift_light_data.state     = FALSE;
    shift_light_data.posx      = posx;
    shift_light_data.posy      = posy;
}

void warning_shift_set_state( void * p_lcd, bool_t state )
{
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    if( state != shift_light_data.state )
    {
        shift_light_data.state = state;
        graphics_show_bitmap( lcd, shift_light_data.posx, shift_light_data.posy, shift_light_data.bitmap[(int)state], FALSE );
    }
}

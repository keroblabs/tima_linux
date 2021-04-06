#include "skin_speed.h"
#include "touchscreen_lib.h"
#include "t_threads.h"
#include "gauges_lib.h"
#include "warning_lights.h"
#include "driving_data.h"
#include "draw.h"
#include "bitmap.h"
#include "show_7segs_lib.h"

////////////////////////////////////////////////////////////////////////////////////////

//#define SPEED_FOREGROUND_COLOUR         APP_RGB(255, 255, 220)
#define SPEED_FOREGROUND_COLOUR         APP_RGB(180, 255, 180)

//#define SECONDARY_FOREGROUND_COLOUR     APP_RGB(180, 255, 180)
#define SECONDARY_FOREGROUND_COLOUR     APP_RGB(200, 180, 32)

#define DISABLED_DIGITS_COLOUR          APP_RGB(25,45,85)

#define SPEED_POSX                      (366+38)
#define SPEED_POSY                      (160+28)

////////////////////////////////////////////////////////////////////////////////////////

typedef struct speedometer_data_t_
{
    unit_display_t  speed_unit;
    unit_display_t  secondary_speed_unit;
    
    digits_data_t   digits_data;
    pixel_t         secondary_colour;
    graphics_backup_t * mph_backup;
    
} speedometer_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static const char * unit_str[2] = { "km/h", "mph" };

static bool_t is_enabled;

static speedometer_data_t local_speed;

static instruments_gauge_t speed_gauge_data;

////////////////////////////////////////////////////////////////////////////////////////

static void show_speed( void * lcd, void * p_data, int speed )
{
    char secondary_speed_str[15];
    speedometer_data_t * data = ( speedometer_data_t * )p_data;
    
    if( is_enabled == TRUE )
    {
        int secondary_value = (speed * 10)/16;
        show_7segs_large_digits_show( lcd, &data->digits_data, speed );
    
        draw_font_init( FONT_12x16 );
        sprintf( secondary_speed_str, "%3d", secondary_value );
        graphics_restore_backup( lcd, data->mph_backup );
        draw_text_ex( lcd, SPEED_POSX, SPEED_POSY + 160, secondary_speed_str, data->secondary_colour, data->mph_backup );
    }
}

static void init_gauge_speed( void )
{
    show_7segs_digits_create_data( &local_speed.digits_data, SPEED_POSX, SPEED_POSY, 3, SPEED_FOREGROUND_COLOUR );

    local_speed.speed_unit = Unit_Km;
    local_speed.secondary_colour = SECONDARY_FOREGROUND_COLOUR;
    local_speed.secondary_speed_unit = Unit_Miles;
    
    local_speed.mph_backup = graphics_backup_create( 1000 );

    speed_gauge_data.mutex = tthread_mutex_init();
    speed_gauge_data.cond = tthread_condition_create();
    speed_gauge_data.target = 0;
    speed_gauge_data.curr_value = 0;
    speed_gauge_data.min_diff = 2;
    speed_gauge_data.min_inc = 1;
    speed_gauge_data.max_inc = 4;
    speed_gauge_data.base_diff = 10;
    speed_gauge_data.initial_rate = SPEED_REFRESH_RATE_MS;
    speed_gauge_data.run_rate = SPEED_REFRESH_RATE_MS;
    speed_gauge_data.show_handler = show_speed;
    speed_gauge_data.data = &local_speed;
    
    gauge_thread_start( &speed_gauge_data );
}

static bool_t touchscreen_event( touchscreen_event_t event, uint16_t posx, uint16_t posy, uint16_t posz )
{
    bool_t ret = FALSE;

    switch( event )
    {
        case Touchscreen_Event_Start:
            break;

        case Touchscreen_Event_Short:
            break;

        case Touchscreen_Event_End:
            break;
    }

    return ret;
}

void skin_speed_set_value( int value_main )
{
    tthread_mutex_lock( speed_gauge_data.mutex );
    
    speed_gauge_data.target = value_main;
    
    local_speed.speed_unit = Unit_Km;
    local_speed.secondary_speed_unit = Unit_Miles;
    
    tthread_mutex_unlock( speed_gauge_data.mutex );

    tthread_condition_signal( speed_gauge_data.cond );
}

void skin_speed_hide( void )
{
    is_enabled = FALSE;
}

void skin_speed_reload( void )
{
    void * lcd = graphics_claim();

    draw_font_init( FONT_12x16 );
    draw_text_ex( lcd, SPEED_POSX + 150, SPEED_POSY + 160, ( char * )unit_str[local_speed.speed_unit], local_speed.digits_data.colour, NULL );

    char secondary_speed_str[15];
    sprintf( secondary_speed_str, "    %s", unit_str[local_speed.secondary_speed_unit] );
    draw_text_ex( lcd, SPEED_POSX, SPEED_POSY + 160, secondary_speed_str, local_speed.secondary_colour, NULL );

    graphics_release();

    is_enabled = TRUE;
    tthread_condition_signal( speed_gauge_data.cond );
}

void skin_speed_init( void )
{
    is_enabled = FALSE;

    init_gauge_speed(); // initialises local_speed
    touchscreen_lib_set_handler( local_speed.digits_data.posx,
                                 local_speed.digits_data.posy,
                                 local_speed.digits_data.posx + 100,
                                 local_speed.digits_data.posy + 100, touchscreen_event );
}

uint64_t skin_speed_get_draw_time( void )
{
    return speed_gauge_data.max_drawtime;
}

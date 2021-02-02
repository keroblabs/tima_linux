#include "skin_odometer.h"
#include "touchscreen_lib.h"
#include "t_threads.h"
#include "bitmap.h"
#include "draw.h"
#include "show_7segs_lib.h"
#include "driving_data.h"
#include "timer.h"
#include "message.h"

////////////////////////////////////////////////////////////////////////////////////////

#define ODOMETER_X_MARK                 247
#define ODOMETER_LINE1                  355
#define ODOMETER_LINE2                  375

#define ODOMETER_DIGIT_COLOUR           APP_RGB(45,56,203)
#define ODOMETER_BACKGROUND_COLOUR      APP_RGB(223, 222, 221)

#define ODOMETER_BACKUP_MAX_SIZE        5000

#define ODOMETER_LONG_PRESS             1800

#define ODOMETER_LONG_PRESS_MESSAGE     (Message_User_Space + 1)
#define ODOMETER_DOWN_MESSAGE           (Message_User_Space + 2)
#define ODOMETER_RELEASE_MESSAGE        (Message_User_Space + 3)
#define ODOMETER_RESET_MESSAGE          (Message_User_Space + 4)

// static const char *message_str[] = { "ODOMETER_LONG_PRESS_MESSAGE", "ODOMETER_DOWN_MESSAGE", "ODOMETER_RELEASE_MESSAGE", "ODOMETER_RESET_MESSAGE" };

////////////////////////////////////////////////////////////////////////////////////////

typedef struct odometer_data_t_
{
    uint32_t main_odometer;
    uint32_t trip_odometer[ODOMETER_TRIP_MAX_INDEX];
    
    uint8_t trip_index;
    
    graphics_backup_t * backup;
    
} odometer_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static odometer_data_t local_odometer;
static bool_t is_enabled;

////////////////////////////////////////////////////////////////////////////////////////

static void show_odometer( odometer_data_t * p_data )
{
    char temp_str[15];
    uint16_t posx;
    void * lcd;
    uint32_t trip_odometer;
    
    if( is_enabled == FALSE ) return;
    
    lcd = graphics_claim();
    graphics_restore_backup( lcd, p_data->backup );
    
    // odometer
    draw_font_init(FONT_12x16);
    sprintf( temp_str, "%d", p_data->main_odometer/100 );
    posx = ODOMETER_X_MARK - draw_get_text_width( temp_str );
    draw_text_ex( lcd, posx, ODOMETER_LINE2, temp_str, ODOMETER_DIGIT_COLOUR, p_data->backup );
    
    draw_font_init(FONT_8x8);
    strcpy( temp_str, "all" );
    draw_text_ex( lcd, ODOMETER_X_MARK+8, ODOMETER_LINE2+8, temp_str, ODOMETER_DIGIT_COLOUR, p_data->backup );

    // trip
    trip_odometer = (p_data->main_odometer - p_data->trip_odometer[p_data->trip_index]) % 100000;
    draw_font_init(FONT_12x16);
    sprintf( temp_str, "%d.%01d", trip_odometer/100, (trip_odometer%100)/10 );
    posx = ODOMETER_X_MARK - draw_get_text_width( temp_str );
    draw_text_ex( lcd, posx, ODOMETER_LINE1, temp_str, ODOMETER_DIGIT_COLOUR, p_data->backup );
    
    draw_font_init(FONT_8x8);
    sprintf( temp_str, "t%d", p_data->trip_index+1 );
    draw_text_ex( lcd, ODOMETER_X_MARK+8, ODOMETER_LINE1+8, temp_str, ODOMETER_DIGIT_COLOUR, p_data->backup );

    graphics_release();
}

static bool_t touchscreen_event( touchscreen_event_t event, uint16_t posx, uint16_t posy, uint16_t posz )
{
    bool_t ret = FALSE;

    switch( event )
    {
        case Touchscreen_Event_Start:
            break;

        case Touchscreen_Event_Short:
            skin_odometer_select_trip();
            break;

        case Touchscreen_Event_Long:
            driving_data_reset_trip( local_odometer.trip_index );
            break;

        case Touchscreen_Event_End:
            break;
    }

    return ret;
}

void skin_odometer_set_value( uint32_t value )
{
    local_odometer.main_odometer = value;
    show_odometer( &local_odometer );
}

void skin_odometer_select_trip( void )
{
    local_odometer.trip_index++;
    if( local_odometer.trip_index >= ODOMETER_TRIP_MAX_INDEX ) local_odometer.trip_index = 0;
    skin_odometer_reload();
}

void skin_odometer_load_trip( uint32_t * trips )
{
    uint32_t cnt;
    
    for( cnt = 0; cnt < ODOMETER_TRIP_MAX_INDEX; cnt++ )
    {
        local_odometer.trip_odometer[cnt] = trips[cnt];
    }
}

void skin_odometer_reload( void )
{
    is_enabled = TRUE;
    show_odometer( &local_odometer );
}

void skin_odometer_hide( void )
{
    is_enabled = FALSE;
}

void skin_odometer_init( void )
{
    is_enabled = FALSE;
    
    memset( &local_odometer, 0x00, sizeof( odometer_data_t ) );
    local_odometer.backup = graphics_backup_create( ODOMETER_BACKUP_MAX_SIZE );

    touchscreen_lib_set_handler( 165, 340, 280, 400, touchscreen_event );

    //tthread_create( odometer_press_thread );
    //message_Init( &long_press_message );
}

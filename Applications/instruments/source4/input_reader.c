#include "input_reader.h"

#include "system.h"
#include "driving_data.h"
#include "adc_driver.h"
#include "input_reader.h"
#include "message.h"
#include "timer.h"
#include "logging_data.h"
#include "lp_filter.h"
#include "button_ctrl.h"

////////////////////////////////////////////////////////////////////

#define BATTERY_CHECK_TIMER_MS      300
#define IGNITION_READ_TIMER_MS      300
#define LP_BUFFER_SIZE              10
#define LP_FUEL_GAUGE_SIZE          500

#define R_SWITCH_COUNT              5

#define R_SWITCH_MASK               0xFF0
#define R_SWITCH_MESSAGE            0x00F
#define R_SWITCH_VOL_UP             0x800
#define R_SWITCH_VOL_DOWN           0x810
#define R_SWITCH_SEEK_UP            0x820
#define R_SWITCH_SEEK_DOWN          0x830
#define R_SWITCH_MODE               0x840

////////////////////////////////////////////////////////////////////

typedef struct r_switch_data_t_
{
    uint16_t min;
    uint16_t max;
    uint16_t id;

} r_switch_data_t;

////////////////////////////////////////////////////////////////////

static const r_switch_data_t r_switch_data[R_SWITCH_COUNT] =
{
    {  20,  60, R_SWITCH_VOL_DOWN  },
    {  80, 130, R_SWITCH_VOL_UP    },
    { 150, 250, R_SWITCH_SEEK_DOWN },
    { 300, 450, R_SWITCH_SEEK_UP   },
    { 500, 650, R_SWITCH_MODE      },
};

static const char * str_debug_r_switch[] =
{
    "R_SWITCH_VOL_UP",
    "R_SWITCH_VOL_DOWN",
    "R_SWITCH_SEEK_UP",
    "R_SWITCH_SEEK_DOWN",
    "R_SWITCH_MODE",
};

////////////////////////////////////////////////////////////////////

static void * state_mutex;
static void * ignition_gpio;
static void * backlight_gpio;

static timer_data_t battery_timer;
static timer_data_t ignition_timer;
static timer_data_t fuel_gauge_timer;

static message_data_t r_switch_message;

static lp_filter_t fuel_gauge_lp;
static lp_filter_t battery_voltage_lp;
static uint32_t battery_voltage_buffer[LP_BUFFER_SIZE];
static uint32_t fuel_gauge_buffer[LP_FUEL_GAUGE_SIZE];

static bool_t ignition_state;
static bool_t battery_state;

static int count;

////////////////////////////////////////////////////////////////////

static bool_t get_ignition( void )
{
    return gpio_input( ignition_gpio ) ? FALSE : TRUE;
}

static bool_t r_switch_read( void * p_data )
{
    r_switch_data_t * data = ( r_switch_data_t * )p_data;
    uint32_t r_switch_value = adc_driver_read(0);

    return ( ( r_switch_value > data->min ) && ( r_switch_value < data->max ) ) ? TRUE : FALSE;
}

static void r_switch_thread( void )
{
    uint16_t message;
    uint16_t button_id;

    if( ( message = message_Get( &r_switch_message ) ) != Message_NoMessage )
    {
        button_id = message & R_SWITCH_MASK;
        message = message & R_SWITCH_MESSAGE;

        if( message == Button_Message_Down )
        {
            switch( button_id )
            {
                case R_SWITCH_MODE:
                    // driving_data_next_trip();
                    break;

                case R_SWITCH_SEEK_UP:
                    driving_data_send_message( MessageSkin_Button2 );
                    break;

                case R_SWITCH_SEEK_DOWN:
                    driving_data_send_message( MessageSkin_Button3 );
                    break;

                case R_SWITCH_VOL_UP:
                    driving_data_send_message( MessageSkin_Button0 );
                    break;

                case R_SWITCH_VOL_DOWN:
                    driving_data_send_message( MessageSkin_Button1 );
                    break;
            }
        }

       // printf( "%s - %s\n", str_debug_r_switch[(button_id & 0x0F0) >> 4], str_debug_button_message[message] );
    }
}

static void fuel_gauge_thread( void )
{
    int fuel_level = lp_filter_add( &fuel_gauge_lp, adc_driver_read(0) );

    if( timer_Check( &fuel_gauge_timer ) )
    {
        timer_Reload( &fuel_gauge_timer );
        driving_data_set_reading_value( Reading_Fuel, fuel_level - 35 );
        // printf( "Fuel gauge = %d\n", fuel_level );
    }
}

static void battery_voltage_thread( void )
{
    if( !timer_Check( &battery_timer ) ) return;
    timer_Reload( &battery_timer );

    int volts = ((10 * lp_filter_add( &battery_voltage_lp, adc_driver_read(1))) / 184 );
    driving_data_set_reading_value( Reading_BatteryVoltage, volts );

    if( ( volts > 130 ) && ( battery_state == TRUE ) )
    {
        driving_data_state_mask( StateMask_Battery, FALSE );
        battery_state = FALSE;
    }
    else if( ( volts < 125 ) && ( battery_state == FALSE ) )
    {
        driving_data_state_mask( StateMask_Battery, TRUE );
        battery_state = TRUE;
    }
}

static void ignition_check_thread( void )
{
    bool_t input;

    if( !timer_Check( &ignition_timer ) ) return;
    timer_Reload( &ignition_timer );

    input = get_ignition();

    if( input != ignition_state )
    {
        gpio_output( backlight_gpio, input );
        driving_data_send_message( input ? MessageSkin_Reload : MessageSkin_Hide );

        //if( input ) logging_data_load();
        //else logging_data_save();

        tthread_mutex_lock( state_mutex );
        ignition_state = input;
        tthread_mutex_unlock( state_mutex );
    }
}

static void input_reader_thread( void )
{
    count = 0;
    battery_state = FALSE;

    while( 1 )
    {
        tthread_sleep_ms( 20 );

        battery_voltage_thread();
        ignition_check_thread();
        fuel_gauge_thread();
        //r_switch_thread();
    }
}

bool_t input_reader_get_ignition_state( void )
{
    bool_t ret;

    tthread_mutex_lock( state_mutex );
    ret = ignition_state;
    tthread_mutex_unlock( state_mutex );

    return ret;
}

void input_reader_init( void )
{
    backlight_gpio = gpio_open_output( GPIO_PG00 );
    ignition_gpio  = gpio_open_input( GPIO_PE03 );
    state_mutex    = tthread_mutex_init();

    button_ctrl_init();

    timer_Start( &battery_timer, BATTERY_CHECK_TIMER_MS );
    timer_Start( &ignition_timer, IGNITION_READ_TIMER_MS );
    timer_Start( &fuel_gauge_timer, 300 );

    lp_filter_init( &fuel_gauge_lp, fuel_gauge_buffer, LP_FUEL_GAUGE_SIZE );
    lp_filter_init( &battery_voltage_lp, battery_voltage_buffer, LP_BUFFER_SIZE );

    /*
    message_Init( &r_switch_message );

    for( int i = 0; i < R_SWITCH_COUNT; i++ )
    {
        button_ctrl_create( r_switch_read, &r_switch_message, r_switch_data[i].id, (void *)&r_switch_data[i] );
    }
    */

    adc_driver_init();

    ignition_state = get_ignition() ? FALSE : TRUE; // invert for force update
    tthread_create( input_reader_thread );
}

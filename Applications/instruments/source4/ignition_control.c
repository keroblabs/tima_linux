#include "system.h"
#include "driving_data.h"
#include "timer.h"
#include "input_reader.h"
#include "ignition_control.h"
#include "logging_data.h"
#include "rear_bcm_comms.h"

////////////////////////////////////////////////////////////////////

#define KEY_CHECK_BACKOFF_MS        200

////////////////////////////////////////////////////////////////////

static void * acc_gpio;
static void * starter_gpio;
static void * backlight_gpio;
static void * ignition_gpio;
static void * enable_start_gpio;

static void * ignition_mutex;

static timer_data_t key_check_timeout;

static bool_t ignition_state;
static bool_t starter_state;
static bool_t acc_state;
static bool_t enable_start_state;

static bool_t first_off;

////////////////////////////////////////////////////////////////////

static bool_t get_ignition( void )
{
    return gpio_input( ignition_gpio ) ? FALSE : TRUE;
}

static bool_t get_starter( void )
{
    return gpio_input( starter_gpio ) ? FALSE : TRUE;
}

static bool_t get_acc( void )
{
    return gpio_input( acc_gpio ) ? FALSE : TRUE;
}

static bool_t get_enable_start( void )
{
    return gpio_input( enable_start_gpio ) ? FALSE : TRUE;
}

static void ignition_control_thread( void )
{
    bool_t input;

    while( 1 )
    {
        input = get_ignition();
        if( input != ignition_state )
        {
            lin_gpio_set_ignition_relay( input );

            // first time here, first_off will be true
            if( ( input == FALSE ) && ( first_off == FALSE ) ) logging_data_save();
            first_off = FALSE;

            timer_Reload( &key_check_timeout );

            tthread_mutex_lock( ignition_mutex );
            ignition_state = input;
            tthread_mutex_unlock( ignition_mutex );
        }

        input = get_enable_start();
        if( input != enable_start_state )
        {
            timer_Reload( &key_check_timeout );

            tthread_mutex_lock( ignition_mutex );
            enable_start_state = input;
            tthread_mutex_unlock( ignition_mutex );
        }

        if( timer_Check( &key_check_timeout ) )
        {
            timer_Stop( &key_check_timeout );
            driving_data_state_mask( StateMask_KeyMissing, enable_start_state ? FALSE : ignition_state );
        }

        input = get_starter();
        if( input != starter_state )
        {
            if( ( input == FALSE ) || ( enable_start_state == TRUE ) )
            {
                lin_gpio_set_starter_relay( input );
            }

            tthread_mutex_lock( ignition_mutex );
            starter_state = input;
            tthread_mutex_unlock( ignition_mutex );
        }

        input = get_acc();
        if( input != acc_state )
        {
            gpio_output( backlight_gpio, input );
            driving_data_send_message( input ? MessageSkin_Reload : MessageSkin_Hide );

            tthread_mutex_lock( ignition_mutex );
            acc_state = input;
            tthread_mutex_unlock( ignition_mutex );
        }

        tthread_sleep_ms( 50 );
    }
}

bool_t ignition_control_get_state( void )
{
    bool_t ret;

    tthread_mutex_lock( ignition_mutex );
    ret = ignition_state;
    tthread_mutex_unlock( ignition_mutex );

    return ret;
}

bool_t ignition_control_get_key_state( void )
{
    bool_t ret;

    tthread_mutex_lock( ignition_mutex );
    ret = enable_start_state;
    tthread_mutex_unlock( ignition_mutex );

    return ret;
}

void ignition_control_init( void )
{
    first_off = TRUE;

    backlight_gpio    = gpio_open_output( GPIO_PG00 );
    acc_gpio          = gpio_open_input( GPIO_PE03 );
    starter_gpio      = gpio_open_input( GPIO_PE09 );
    ignition_gpio     = gpio_open_input( GPIO_PE10 );
    enable_start_gpio = gpio_open_input( GPIO_PE11 );

    ignition_mutex = tthread_mutex_init();

    timer_Start( &key_check_timeout, KEY_CHECK_BACKOFF_MS );

    ignition_state     = get_ignition() ? FALSE : TRUE; // invert for force update
    starter_state      = get_starter() ? FALSE : TRUE;
    acc_state          = get_acc() ? FALSE : TRUE;
    enable_start_state = get_enable_start() ? FALSE : TRUE;

    tthread_create( ignition_control_thread );
}

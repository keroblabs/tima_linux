#include "system.h"
#include "rear_bcm_comms.h"
#include "pipe.h"
#include "timer.h"
#include "lin_ctrl.h"

////////////////////////////////////////////////////////////////////

#define LIN_CHECK_TIMER_MS          200

#define LIN_IGNITION_MASK           0x20
#define LIN_STARTER_MASK            0x10

#define LIN_ID_ADC_INPUT            0x8A
#define LIN_ID_GPIO_INPUT           0x8B
#define LIN_ID_GPIO_OUTPUT          0x8C

////////////////////////////////////////////////////////////////////

static uint8_t curr_gpio;
static bool_t read_gpio_req;

static void * lin_cond;
static void * lin_mutex;

static pipe_data_t gpio_reading_pipe;
static timer_data_t lin_check_timeout;

////////////////////////////////////////////////////////////////////

static void lin_check_gpio_thread( void )
{
    uint8_t local_gpio;
    uint8_t lin_gpio;
    bool_t is_wait = TRUE;
    bool_t is_read_req;
    bool_t is_received = FALSE;

    while( 1 )
    {
        if( is_wait == TRUE )
        {
            tthread_condition_wait( lin_cond );
            is_wait = FALSE;
        }

        if( pipe_is_empty( &gpio_reading_pipe ) == FALSE )
        {
            uint8_t * read_gpio = pipe_read( &gpio_reading_pipe, NULL );
            lin_gpio = *read_gpio;

            pipe_release_buffer( read_gpio );
            timer_Expire( &lin_check_timeout );
            is_received = TRUE;
        }

        if( timer_Check( &lin_check_timeout ) == TRUE )
        {
            timer_Stop( &lin_check_timeout );
            is_wait = TRUE;

            tthread_mutex_lock( lin_mutex );
            local_gpio = curr_gpio;
            is_read_req = read_gpio_req;
            tthread_mutex_unlock( lin_mutex );

            if( is_received == FALSE )
            {
                printf( "LIN timeout\n" );
            }
            is_received = FALSE;

            //printf( "LIN 0x%02X - local 0x%02X\n", lin_gpio, local_gpio );

            if( is_read_req == TRUE )
            {
                tthread_mutex_lock( lin_mutex );
                curr_gpio = lin_gpio;
                read_gpio_req = FALSE;
                tthread_mutex_unlock( lin_mutex );
                //printf( "LIN curr gpio: 0x%02X\n", lin_gpio );
            }
            else
            {
                if( ( local_gpio ^ lin_gpio ) & LIN_IGNITION_MASK )
                {
                    printf( "LIN retry (ignition)\n" );
                    lin_gpio_set_ignition_relay( ( local_gpio & LIN_IGNITION_MASK ) ? TRUE : FALSE );
                }

                if( ( local_gpio ^ lin_gpio ) & LIN_STARTER_MASK )
                {
                    printf( "LIN retry (starter)\n" );
                    lin_gpio_set_starter_relay( ( local_gpio & LIN_STARTER_MASK ) ? TRUE : FALSE );
                }
            }
        }
        else
        {
        }
        tthread_sleep_ms( 50 );
    }
}

static void send_lin_command( bool_t state, uint8_t mask )
{
    tthread_mutex_lock( lin_mutex );
    if( state ) curr_gpio |= mask;
    else curr_gpio &= ~mask;
    tthread_mutex_unlock( lin_mutex );

    //printf( "LIN out 0x%02x (%d)\n", mask, state );

    uint8_t command = mask | ( state ? 0x80 : 0x00 );
    lin_ctrl_send_command( LIN_ID_GPIO_OUTPUT, &command, 0x01, 0, NULL );
    //lin_ctrl_send_command( LIN_ID_GPIO_OUTPUT, &command, 0x01, 0, NULL );
    //lin_ctrl_send_command( LIN_ID_GPIO_OUTPUT, &command, 0x01, 0, NULL );
    lin_ctrl_send_command( LIN_ID_GPIO_INPUT, NULL, 0x00, 1, &gpio_reading_pipe );
    timer_Reload( &lin_check_timeout );
    tthread_condition_signal( lin_cond );
}

void lin_gpio_read_request( void )
{
    tthread_mutex_lock( lin_mutex );
    read_gpio_req = TRUE;
    tthread_mutex_unlock( lin_mutex );

    lin_ctrl_send_command( LIN_ID_GPIO_INPUT, NULL, 0x00, 1, &gpio_reading_pipe );
}

bool_t lin_gpio_read_done( uint8_t * gpio )
{
    bool_t is_read_done;
    uint8_t ret_gpio;

    tthread_mutex_lock( lin_mutex );
    is_read_done = read_gpio_req ? FALSE : TRUE;
    ret_gpio = curr_gpio;
    tthread_mutex_unlock( lin_mutex );

    if( ( is_read_done == TRUE ) && ( gpio != NULL ) )
    {
        *gpio = ret_gpio;
    }

    return is_read_done;
}

void lin_gpio_set_starter_relay( bool_t state )
{
    send_lin_command( state, LIN_STARTER_MASK );
}

void lin_gpio_set_ignition_relay( bool_t state )
{
    send_lin_command( state, LIN_IGNITION_MASK );
}

void lin_gpio_init( void )
{
    pipe_init( &gpio_reading_pipe, "PIPE_RX_LIN", 16 );
    lin_cond = tthread_condition_create();
    lin_mutex = tthread_mutex_init();

    timer_Start( &lin_check_timeout, LIN_CHECK_TIMER_MS );
    timer_Stop( &lin_check_timeout );

    tthread_create( lin_check_gpio_thread );
}

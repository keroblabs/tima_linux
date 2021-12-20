#include "system.h"
#include "canbus_conns.h"
#include "canbus_driver.h"
#include "driving_data.h"
#include "odometer_ctrl.h"
#include "ignition_control.h"

////////////////////////////////////////////////////////////////////

#define CAN_DATA_RATE                           500000
#define CAN_VALUE_TO_16BITS(i)                  (((int)(msg->data[i]) * 256) + (int)msg->data[i+1])
#define CAN_VALUE_TO_8BIT(i)                    ((int)msg->data[i])

#define CAN_MESSAGE1_RPM_INDEX                  0
#define CAN_MESSAGE1_SPEED_INDEX                2
#define CAN_MESSAGE1_FUEL_INDEX                 5
#define CAN_MESSAGE1_COOLANT_INDEX              6

#define CAN_MESSAGE_GEM_BITMAP                  0

#define CAN_BUS_CHECK_MASK(b, s, c, sm )        if( b & s ) { c |= ( 1 << sm ); } else { c &= ~( 1 << sm ); }

#define CAN_MESSAGE3_STATUS_HEADLAMPS           0x0001
#define CAN_MESSAGE3_STATUS_MAINBEAM            0x0002
#define CAN_MESSAGE3_STATUS_FULLBEAM            0x0004
#define CAN_MESSAGE3_STATUS_FRONTFOG            0x0008

////////////////////////////////////////////////////////////////////

static void canbus_conns_receive1( const CAN_msg_t * msg );
static void canbus_conns_receive2( const CAN_msg_t * msg );
static void canbus_conns_receive3( const CAN_msg_t * msg );
static void canbus_conns_gem( const CAN_msg_t * msg );

////////////////////////////////////////////////////////////////////

static int can_counter;
static void * counter_mutex;

static const CAN_filter_t can_filter[] =
{
        { 0x7f1, canbus_conns_receive1 },
        { 0x7f2, canbus_conns_receive2 },
        { 0x7f3, canbus_conns_gem      },
        { 0x7e8, canbus_conns_receive3 },
};

////////////////////////////////////////////////////////////////////

static void set_counter( int value )
{
    tthread_mutex_lock( counter_mutex );
    can_counter = value;
    tthread_mutex_unlock( counter_mutex );
}

static int get_counter( void )
{
    int value;

    tthread_mutex_lock( counter_mutex );
    value = can_counter;
    tthread_mutex_unlock( counter_mutex );

    return value;
}

static void canbus_print_message( const CAN_msg_t * msg )
{
    uint8_t i;
    printf( "%05d - 0x%04x: [%d] ", can_counter++, msg->id, msg->len );

    for( i = 0; i < msg->len; i++ )
    {
        printf( " 0x%02x", msg->data[i] );
    }

    printf( "\n" );
}

static void canbus_conns_receive1( const CAN_msg_t * msg )
{
    //printf( "msg1 0x%03x\n", msg->id );
    set_counter( get_counter() + 1 );

    int rpm   = CAN_VALUE_TO_16BITS(CAN_MESSAGE1_RPM_INDEX);
    int speed = CAN_VALUE_TO_16BITS(CAN_MESSAGE1_SPEED_INDEX);
    //int fuel  = CAN_VALUE_TO_8BIT(CAN_MESSAGE1_FUEL_INDEX);
    //int temp  = CAN_VALUE_TO_8BIT(CAN_MESSAGE1_COOLANT_INDEX);

    driving_data_set_reading_value( Reading_RPM, rpm );
    driving_data_set_reading_value( Reading_Speed, speed );
    //driving_data_set_reading_value( Reading_Fuel, fuel );
    //driving_data_set_reading_value( Reading_EngineTemp, temp );

    odometer_control_add_speed_value( speed );

    // canbus_print_message( msg );
}

static void canbus_conns_gem( const CAN_msg_t * msg )
{
    uint16_t bitmap = CAN_VALUE_TO_16BITS(CAN_MESSAGE_GEM_BITMAP);
    uint32_t curr_mask = driving_data_get_mask();

    CAN_BUS_CHECK_MASK(bitmap, CAN_MESSAGE3_STATUS_FULLBEAM, curr_mask, StateMask_FullBeam )
    CAN_BUS_CHECK_MASK(bitmap, CAN_MESSAGE3_STATUS_FRONTFOG, curr_mask, StateMask_FogLight )
    CAN_BUS_CHECK_MASK(bitmap, CAN_MESSAGE3_STATUS_HEADLAMPS, curr_mask, StateMask_Headlights )
    CAN_BUS_CHECK_MASK(bitmap, CAN_MESSAGE3_STATUS_MAINBEAM, curr_mask, StateMask_MainBeam )

    driving_data_set_mask( curr_mask );
}

static void canbus_watchdog_thread( void )
{
    volatile int last_value;
    volatile int new_value;
    bool_t can_failure = FALSE;

    last_value = get_counter();

    while( 1 )
    {
        tthread_sleep_ms( 1500 );
        new_value = get_counter();

        if( ignition_control_get_state() == TRUE )
        {
            if( ( last_value == new_value ) && ( can_failure == FALSE ) )
            {
                // no can communication
                //printf( "no CAN data\n" );
                driving_data_state_mask( StateMask_CANFailure, TRUE );
                driving_data_set_reading_value( Reading_RPM, 0 );
                driving_data_set_reading_value( Reading_Speed, 0 );
                odometer_control_reset();
                can_failure = TRUE;
            }
            else if( ( last_value != new_value ) && ( can_failure == TRUE ) )
            {
                // can communication is back
                //printf( "CAN data OK\n" );
                driving_data_state_mask( StateMask_CANFailure, FALSE );
                can_failure = FALSE;
            }
        }
        else if( can_failure == TRUE )
        {
            can_failure = FALSE;
            driving_data_state_mask( StateMask_CANFailure, FALSE );
        }

        last_value = new_value;
    }
}

static void canbus_conns_receive2( const CAN_msg_t * msg )
{
    //printf( "msg2 0x%03x\n", msg->id );
}

static void canbus_conns_receive3( const CAN_msg_t * msg )
{
    //printf( "msg-OBD 0x%03x\n", msg->id );
}

void canbus_conns_init( void )
{
    counter_mutex = tthread_mutex_init();
    can_counter = 0;
    canbus_start( "can0", CAN_DATA_RATE, can_filter, SIZE_OF_ARRAY(can_filter) );
    //tthread_create( canbus_watchdog_thread );
}

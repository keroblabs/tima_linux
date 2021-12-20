#include "system.h"
#include "driving_data.h"
#include "timer.h"
#include "pipe.h"
#include "lin_ctrl.h"
#include "fuel_control.h"
#include "ignition_control.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static timer_data_t fuel_gauge_timer;
static pipe_data_t fuel_reading_pipe;

////////////////////////////////////////////////////////////////////

void fuel_control_thread( void )
{
    timer_Start( &fuel_gauge_timer, 1000 );

    while( 1 )
    {
        if( timer_Check( &fuel_gauge_timer ) )
        {
            timer_Reload( &fuel_gauge_timer );
            if( ignition_control_get_state() == TRUE )
            {
                lin_ctrl_send_command( 0x8A, NULL, 0, 2, &fuel_reading_pipe );
            }
        }

        if( pipe_is_empty( &fuel_reading_pipe ) == FALSE )
        {
            uint8_t * readings = pipe_read( &fuel_reading_pipe, NULL );
            if( readings[0] < 100 ) readings[0] = 100;

            driving_data_set_reading_value( Reading_Fuel, readings[0] - 100 );
            //printf( "Fuel gauge = %d %d\n", readings[0], readings[1] );

            pipe_release_buffer( readings );
        }
    }
}

void fuel_control_init( void )
{
    pipe_init( &fuel_reading_pipe, "FUEL_PIPE", MAX_PIPE_SIZE );
    tthread_create( fuel_control_thread );
}

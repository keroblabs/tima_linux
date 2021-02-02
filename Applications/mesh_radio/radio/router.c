#include "router.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////


typedef struct addressing_t_
{
    uint16_t        pan_id;
    uint64_t        address;

} addressing_t;

////////////////////////////////////////////////////////////////////

static timer_data_t beacon_timer;

////////////////////////////////////////////////////////////////////

static void beacon_process( void )
{
    if( timer_Check( &beacon_timer ) )
    {
        timer_Reload( &beacon_timer );

        // send beacon
    }
}

static void on_received_frame( const uint8_t * frame )
{

}

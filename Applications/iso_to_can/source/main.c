#include "system.h"
#include "timer.h"
#include "elm_327_monitor.h"
#include "canbus_driver.h"

///////////////////////////////////////////////////////////////////////////////////////

#define CAN_DATA_RATE                           500000

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    timer_data_t update_clock;

    system_init();
    timer_Init();
    elm_327_monitor_init();

    int can_socket = canbus_start( "can0", CAN_DATA_RATE, NULL, 0 );

    timer_Start( &update_clock, 250 );

    printf( "ISO reader\r\n" );
    
    while( 1 )
    {
        if( timer_Check( &update_clock ) )
        {
            timer_Reload( &update_clock );

            elm_327_data_t data;
            elm_327_get_data( &data );

            printf( "speed = %5d - temp = %3d - bits = 0x%02x - rpm = %ld\n", data.speed, data.temp, data.bitmask, data.rpm );

            CAN_msg_t msg;
            msg.id = 0x7F1;
            msg.len = 8;
            memset( msg.data, 0x00, 8 );
            //msg.data[0] = ( data.rpm >> 8   ) & 0x0FF;
            //msg.data[1] = ( data.rpm        ) & 0x0FF;

            msg.data[2] = ( data.speed >> 8 ) & 0x0FF;
            msg.data[3] = ( data.speed      ) & 0x0FF;
            canbus_send( can_socket, &msg );

        }
    }

    return 0;
}

#include "types.h"
#include "settings.h"
#include "net_comms.h"
#include "background.h"
#include "timer.h"

#include "string_lib.h"
#include "temp_room.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

static void main_lock( void )
{
#ifdef MAKE_RPI
    int pid_file = open("./pid.txt", O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);
    if(rc)
    {
        if(EWOULDBLOCK == errno)
        {
            // another instance is running
            printf( "Another instance is running\n" );
            exit(1);
        }
    }
    else
    {
        // this is the first instance
    }
#endif
}

int main( int argc, char *argv [])
{
    home_data_t home_data;
    //timer_data_t run_timer;
    
    //printf( "Start: %d\r\n", mm_used() );
        
    mm_init();
    main_lock();
    timer_Init();
    background_init();
    
    settings_init( &home_data );
    settings_load( &home_data, ROOM_DATA_FILE );

    net_comms_init( &home_data );
    
    //timer_Start( &run_timer, 10*60*1000 );
    
    //string_t * resp = build_temperature_page( &home_data );
    //printf( "%s\n", string_get_char_buffer( resp ) );
            
    //printf( "Running: %d\r\n", mm_used() );

    while( 1 ) // !timer_Check( &run_timer ) )
    {
        background_run( &home_data );
    }
    
    //printf( "Before the end: %d\r\n", mm_used() );

    //settings_destroy( &home_data );
    //printf( "End: %d\r\n", mm_used() );

    return 0;
}

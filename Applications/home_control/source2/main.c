#include "types.h"
#include "timer.h"
#include "string_lib.h"

#include "settings.h"
#include "net_comms.h"
#include "background.h"
#include "build_page.h"

///////////////////////////////////////////////////////////////////////////////////////

#define CONTROL_DATA_FILE       "control_data.txt"

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
    
    mm_init();
    main_lock();
    timer_Init();
    
    background_init();
    
    settings_init( &home_data );
    settings_load( &home_data, CONTROL_DATA_FILE );

    net_comms_init( &home_data );
    build_page_init( &home_data );
    
    while( 1 ) // !timer_Check( &run_timer ) )
    {
        background_run( &home_data );
    }
    
    return 0;
}

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "types.h"

#if 0
void ms_timer_init( void )
{
}

uint32_t ms_timer_get_ms( void )
{
    //return ( uint32_t )( clock() / ( CLOCKS_PER_SEC / 1000 ) );
    return ( uint32_t )( clock() );
}

uint64_t ms_timer_get_us( void )
{
    return ( uint32_t )( clock() / ( CLOCKS_PER_SEC ) );
}
#endif

#include <sys/time.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////

static bool_t is_init = FALSE;
static struct timeval ms_start;

///////////////////////////////////////////////////////////////////////////

void ms_timer_init( void )
{
    if( is_init == TRUE ) return;
    is_init = TRUE;
    
    gettimeofday( &ms_start, NULL );
}

uint32_t ms_timer_get_ms( void )
{
    struct timeval ms_value;
    long mtime, seconds, useconds;
    
    gettimeofday( &ms_value, NULL );
    
    seconds = ms_value.tv_sec - ms_start.tv_sec;
    useconds = ms_value.tv_usec - ms_start.tv_usec;
    mtime = ( seconds * 1000 ) + ( useconds / 1000 );
    
    return ( uint32_t )mtime;
}

uint64_t ms_timer_get_us( void )
{
    struct timeval ms_value;
    long mtime, seconds, useconds;
    
    gettimeofday( &ms_value, NULL );
    
    seconds = ms_value.tv_sec - ms_start.tv_sec;
    useconds = ms_value.tv_usec - ms_start.tv_usec;
    mtime = ( seconds * 1000000 ) + useconds;
    
    return ( uint64_t )mtime;
}

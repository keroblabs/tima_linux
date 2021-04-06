#include "timer_driver_class_private.h"

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

///////////////////////////////////////////////////////////////////////////

CREATOR static void creator( timer_driver_class_t * p_data )
{
    gettimeofday( &p_data->ms_start, NULL );
}

METHOD static uint32_t get_ms( timer_driver_class_t * p_data )
{
    struct timeval ms_value;
    long mtime, seconds, useconds;
    
    gettimeofday( &ms_value, NULL );
    
    seconds = ms_value.tv_sec - p_data->ms_start.tv_sec;
    useconds = ms_value.tv_usec - p_data->ms_start.tv_usec;
    mtime = ( seconds * 1000 ) + ( useconds / 1000 );
    
    return ( uint32_t )mtime;
}

METHOD static uint64_t get_us( timer_driver_class_t * p_data )
{
    struct timeval ms_value;
    long mtime, seconds, useconds;
    
    gettimeofday( &ms_value, NULL );
    
    seconds = ms_value.tv_sec - p_data->ms_start.tv_sec;
    useconds = ms_value.tv_usec - p_data->ms_start.tv_usec;
    mtime = ( seconds * 1000000 ) + useconds;
    
    return ( uint64_t )mtime;
}

CREATE_CLASS(timer_driver_class_t);

///////////////////////////////////////////////////////////////////////////


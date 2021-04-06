#include "background.h"
#include "t_threads.h"
#include "tima_libc.h"
#include "timer.h"
#include "sensor_ctrl.h"
#include "schedule_ctrl.h"

////////////////////////////////////////////////////////////////////

#if 0
xiaomi:
gatttool -b <MAC> --char-write-req --handle=0x0010 --value=0100 --listen
Notification handle = 0x000e value: 54 3d 32 33 2e 36 20 48 3d 33 37 2e 33 00
ASCII: "T=23.6 H=37.3"

eqiva valve:
https://github.com/Heckie75/eQ-3-radiator-thermostat/blob/master/eq-3-radiator-thermostat-api.md

Notification handle = 0x0421 value: 02 01 08 14 04 2c
0x00 ... 0x64 -> close ... open

-> every 60000 ms
if( temp < setpoint ) send: 0x0411 43 (high comfort temp)
else if( temp > setpoint) send: 0x0411 44 (low eco temp)
get notification - if ( valve_pos > 0x30 ) send: boiler_ch = 1
else send: boiler_ch = 0

#endif

////////////////////////////////////////////////////////////////////

#ifdef MAKE_RPI
#define VALVE_UPDATE_TIME_MS        (2*60*1000)
#else
#define VALVE_UPDATE_TIME_MS        (10*1000)
#endif

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void background_init( void )
{
}

void background_run( home_data_t * home_data )
{
    tthread_sleep_ms( 20 );
    sensor_process( home_data );
    schedule_process( home_data );
}

string_t * background_spawn( const char * command )
{
    string_t * output;
    FILE * fp;
    char out_buffer[128];
    
    fp = popen( command, "r" );
    if( fp == NULL ) return NULL;
    
    output = string_create();
    memset( out_buffer, 0x00, sizeof( out_buffer ) );
    
    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        string_append_text( output, out_buffer );
    }
    
    pclose( fp );
    
    return output;
}



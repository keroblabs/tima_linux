#include "system.h"
#include "spawn_lib.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static char out_buffer[128];

////////////////////////////////////////////////////////////////////

void * spawn_command_start( const char * command )
{
    return popen( command, "r" );
}

bool_t spawn_command_read( void * hdl, char * out_buffer, int max_size )
{
    FILE * fp = ( FILE * )hdl;
    memset( out_buffer, 0x00, max_size );
    return fgets( out_buffer, max_size, fp ) != NULL;
}

void spawn_command_close( void * hdl )
{
    FILE * fp = ( FILE * )hdl;
    pclose( fp );
}

int spawn_command( const char * command )
{
    FILE * fp;
    char out_buffer[128];
    int ret = 0;

    fp = popen( command, "r" );
    if( fp == NULL ) return 0;

    memset( out_buffer, 0x00, sizeof( out_buffer ) );

    while( fgets( out_buffer, 100, fp ) != NULL )
    {
    }

    if( strlen( out_buffer ) > 0 )
    {
        ret = out_buffer[0] & 0x0F;
    }
    pclose( fp );

    return ret;
}

void spawn_command_ex( const char * command, spawn_line_handler_t handler, void * data )
{
    FILE * fp;

    printf( "spawn_command_ex %s\n", command );

    fp = popen( command, "r" );
    if( fp == NULL ) return;

    memset( out_buffer, 0x00, sizeof( out_buffer ) );

    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        if( handler != NULL ) handler( data, out_buffer );
    }

    pclose( fp );
}


#include "logging_data.h"
#include "odometer_ctrl.h"

////////////////////////////////////////////////////////////////////

#define MAX_TOTAL_LOGGING       300

////////////////////////////////////////////////////////////////////

typedef struct logging_data_t_
{
    uint64_t time_stamp;

    odometer_data_t odometer_data;

} logging_data_t;

////////////////////////////////////////////////////////////////////

void logging_data_save( void )
{
    logging_data_t data;

    // write timestamp
    time( ( time_t * )&data.time_stamp );

    // collect logging data
    odometer_control_get( &data.odometer_data );

    FILE * fp = fopen( "logging_data.bin", "a+" );
    if( fp )
    {
        fwrite( &data, sizeof( logging_data_t ), 1, fp );
        fclose( fp );
    }
}

void logging_data_load( void )
{
    logging_data_t data;

    memset( &data, 0x00, sizeof( data ) );

    FILE * fp = fopen( "logging_data.bin", "a+" );
    if( fp && ( ftell( fp ) >= sizeof( logging_data_t ) ) )
    {
        fseek( fp, sizeof( logging_data_t ), SEEK_END );
        fread( &data, sizeof( logging_data_t ), 1, fp );
        fclose( fp );
    }

    // set logged data
    odometer_control_set( &data.odometer_data );
}

void logging_data_init( void )
{
    FILE * fp;
    logging_data_t data;

    fp = fopen( "logging_data.bin", "a+" );
    if( fp )
    {
        if( ftell( fp ) > ( MAX_TOTAL_LOGGING * sizeof( logging_data_t ) ) )
        {
            fseek( fp, 0L, SEEK_SET );
            FILE * fp_out = fopen( "logging_prev.bin", "w" );

            if( fp_out )
            {
                while( fread( &data, sizeof( logging_data_t ), 1, fp ) )
                {
                    fwrite( &data, sizeof( logging_data_t ), 1, fp_out );
                }

                fclose( fp_out );
                fclose( fp );

                remove( "logging_data.bin" );
            }
        }
    }
}

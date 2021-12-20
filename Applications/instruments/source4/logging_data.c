#include "logging_data.h"
#include "driving_data.h"
#include "odometer_ctrl.h"

////////////////////////////////////////////////////////////////////

#define MAX_TOTAL_LOGGING       1024

////////////////////////////////////////////////////////////////////

typedef struct logging_data_t_
{
    driving_data_t driving_data;
    odometer_data_t odometer_data;

} logging_data_t;

////////////////////////////////////////////////////////////////////

static void update_logging_files( void )
{
    FILE * fp;

    fp = fopen( "logging_data.bin", "a+" );
    if( fp )
    {
        if( ftell( fp ) > ( MAX_TOTAL_LOGGING * sizeof( logging_data_t ) ) )
        {
            fseek( fp, 0L, SEEK_SET );
            logging_data_t entry;
            fread( &entry, sizeof( logging_data_t ), 1, fp );

            char prev_filename[30];
            sprintf( prev_filename, "logging_prev_%04d%02d%02d_%02d%02d.bin", entry.driving_data.std_time.tm_year,
                                                                              entry.driving_data.std_time.tm_mon+1,
                                                                              entry.driving_data.std_time.tm_mday,
                                                                              entry.driving_data.std_time.tm_hour,
                                                                              entry.driving_data.std_time.tm_min );
            FILE * fp_out = fopen( prev_filename, "w" );
            fwrite( &entry, sizeof( logging_data_t ), 1, fp_out );

            if( fp_out )
            {
                while( fread( &entry, sizeof( logging_data_t ), 1, fp ) )
                {
                    fwrite( &entry, sizeof( logging_data_t ), 1, fp_out );
                }

                fclose( fp_out );
                fclose( fp );

                remove( "logging_data.bin" );
            }
        }
    }
}

void logging_data_save( void )
{
    update_logging_files();

    driving_data_t * curr_data;
    logging_data_t data;

    curr_data = driving_data_lock();
    memcpy( &data.driving_data, curr_data, sizeof( driving_data_t ) );
    driving_data_release();

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
    logging_data_t new_data;

    memset( &data, 0x00, sizeof( data ) );
    memset( &new_data, 0x00, sizeof( new_data ) );

    FILE * fp = fopen( "logging_data.bin", "r" );
    if( fp != NULL )
    {
        while( fread( &new_data, sizeof( logging_data_t ), 1, fp ) > 0 )
        {
            //printf( "%d\n", new_data.odometer_data.full_counter );
            if( data.odometer_data.full_counter > new_data.odometer_data.full_counter )
            {
                break;
            }

            memcpy( &data, &new_data, sizeof( logging_data_t ) );
        }

        odometer_control_set( &data.odometer_data );

        driving_data_set_trips( data.driving_data.trip_list );
        driving_data_set_reading_value( Reading_Odometer, data.driving_data.reading_values[Reading_Odometer] );

        fclose( fp );
    }
}

void logging_data_init( void )
{
}

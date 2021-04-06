#include "sensor_ctrl.h"
#include "settings.h"
#include "driver_ctrl.h"

////////////////////////////////////////////////////////////////////

#define LAST_HISTORY_LOG       ( ( 23 * 60 ) + 59 )

////////////////////////////////////////////////////////////////////

static const char * sensor_type_string[] =
{
    "Temperature",
    "Humidity",
    "Switch",
    "Button",
    "Valve_Eqiva",
    "Valve_Tima",
    "Internal",
};

////////////////////////////////////////////////////////////////////

static string_t * get_dir_history( sensor_t * sensor_data )
{
    home_data_t * home_data = ( home_data_t * )sensor_data->p_home;
    string_t * dir_history = string_sprintf( "%s/dir_history_%s", string_get_char_buffer( home_data->root_dir ), sensor_data->name );
    struct stat st = {0};
    if( stat( string_get_char_buffer( dir_history ), &st ) == -1 )
    {
        mkdir( string_get_char_buffer( dir_history ), 0700);
    }

    return dir_history;
}

static string_t * get_file_history( sensor_t * sensor_data, string_t * dir_history )
{
    home_data_t * home_data = ( home_data_t * )sensor_data->p_home;

    time_t read_time = time( NULL );
    struct tm * date_time = localtime( &read_time );
    string_t * filename = string_sprintf( "%s/file_history_%04d%02d%02d_%s_%s.txt", string_get_char_buffer( dir_history ),
                                            date_time->tm_year + 1900, date_time->tm_mon + 1, date_time->tm_mday, sensor_data->name,
                                            sensor_type_string[sensor_data->type]);

    return filename;
}

bool_t sensor_get( home_data_t * home_data, sensor_t ** data )
{
    GET_ITEM_FROM_LIST(sensor_t, home_data->sensor_list, data);
}

void sensor_process( home_data_t * home_data )
{
    sensor_t * sensor = NULL;
    
    while( sensor_get( home_data, &sensor ) == TRUE )
    {
        if( sensor->prev_value != sensor->value )
        {
            sensor->prev_value = sensor->value;
            
            if( sensor->driver != NULL )
            {
                driver_t * driver = ( driver_t * )sensor->driver;
                driver_set_state( driver, sensor_get_state( sensor ) );
            }
        }
    }
}

bool_t sensor_record_value( home_data_t * home_data, string_t * cmd, string_t * field, string_t * value )
{
    bool_t ret = FALSE;
    char * name = string_get_char_buffer( cmd );
    float f_value;

    sensor_t * sensor = NULL;

    while( sensor_get( home_data, &sensor ) == TRUE )
    {
        if( !strcmp( name, sensor->name ) && !strcmp( sensor_type_string[(int)sensor->type], string_get_char_buffer( field ) ) )
        {
            f_value = atof( string_get_char_buffer( value ) );
            
            if( sensor->type == Sensor_Button )
            {
                if( f_value >= sensor->value_on )
                {
                    if( sensor->value <= sensor->value_off )
                    {
                        sensor->value = sensor->value_on;
                    }
                    else if( sensor->value >= sensor->value_on )
                    {
                        sensor->value = sensor->value_off;
                    }
                }
            }
            else
            {
                sensor->value = f_value;
            }

            time_t read_time = time( NULL );
            struct tm * date_time = localtime( &read_time );
            uint32_t index = ( date_time->tm_hour * 60 ) + date_time->tm_min;

            if( ( index < LAST_HISTORY_LOG ) && ( sensor->file_history == NULL ) )
            {
                string_t * dir_history = get_dir_history( sensor );
                sensor->file_history = get_file_history( sensor, dir_history );
                string_destroy( dir_history );

                for( int i = 0; i < (24*60); i++ )
                {
                    sensor->history[i] = 0;
                }
            }

            if ( sensor->file_history != NULL ) sensor->history[index] = sensor->value;

            if( ( index == LAST_HISTORY_LOG ) && ( sensor->file_history != NULL ) )
            {
                sensor_save_history( sensor );
                string_destroy( sensor->file_history );
                sensor->file_history = NULL;
            }

            ret = TRUE;

            break;
        }
    }

    return ret;
}

sensor_t * sensor_locate( home_data_t * home_data, const char * name )
{
    sensor_t * data = NULL;

    while( sensor_get( home_data, &data ) == TRUE )
    {
        if( !strcmp( name, data->name ) )
        {
            break;
        }
    }

    return data;
}

bool_t sensor_get_state( sensor_t * data )
{
    if( data )
    {
        if( data->value <= data->value_off )
        {
            return ( data->is_inverted ? TRUE : FALSE );
        }
        else if( data->value >= data->value_on )
        {
            return ( data->is_inverted ? FALSE : TRUE );
        }
    }

    return ( data->is_inverted ? TRUE : FALSE );
}

float sensor_get_value( home_data_t * home_data, const char * name )
{
    sensor_t * data = sensor_locate( home_data, name );
    if( data )
    {
        return data->value;
    }

    return 0.0;
}

void sensor_generate_plot( sensor_t * sensor_data, const char * plot_file )
{
    home_data_t * home_data = ( home_data_t * )sensor_data->p_home;

    string_t * plot_scrip_file = string_sprintf( "%s/do_temp_plot.sh", string_get_char_buffer( home_data->root_dir ) );
    FILE * fp = string_fopen( plot_scrip_file, "r", FOPEN_KEEP_FILENAME );
    if( fp == NULL ) return;
    string_destroy( filename );

    fprintf( fp, "#!/usr/bin/gnuplot\n" );
    fprintf( fp, "set terminal png\n" );
    fprintf( fp, "set grid\n" );
    fprintf( fp, "set term pngcairo\n" );
    fprintf( fp, "set output \"%s\"\n", plot_file );
    fprintf( fp, "set yrange [-10:40]\n" );
    fprintf( fp, "set xdata time\n" );
    fprintf( fp, "set timefmt \"%%M:%%S\"\n" );
    fprintf( fp, "set format x \"%%M:%%S\"\n" );
    fprintf( fp, "set xtics \"00:00\", 240, \"24:00\"\n" );
    fprintf( fp, "plot \"%s\" using 1:2 with lines title '%s - %s'\n\n", string_get_char_buffer( sensor_data->file_history ),
                                                                       sensor_data->name, sensor_type_string[sensor_data->type] );
    fclose( fp );

    string_t * command = string_create_ex( "sudo ./do_temp_plot.sh" );
    string_t * output = background_spawn( string_get_char_buffer( filename ) );
    //printf( "%s\n", string_get_char_buffer( output ) );
    string_destroy( output );
    string_destroy( command );
}

void sensor_load_history( sensor_t * sensor_data )
{
    string_t * dir_history = get_dir_history( sensor_data );
    string_t * filename = get_file_history( sensor_data, dir_history );
    FILE * fp = string_fopen( filename, "r", FOPEN_KEEP_FILENAME );

    if( fp != NULL )
    {
        for( int i = 0; i < (24*60); i++ )
        {
            string_t * file_line = string_file_line( fp );

            float data;
            int hour, min;

            sscanf( file_line->buffer, "%d:%d %f %f %d %d", &hour, &min, &data );
            sensor_data->history[i] = data;

            string_destroy( file_line );
        }

        fclose( fp );
    }

    string_destroy( dir_history );
    string_destroy( filename );
}

void sensor_save_history( sensor_t * sensor_data )
{
    // dir : dir_history_<sensor_data->name>
    // file: file_history_<year>_<month>_<day>_<sensor_data->name>_<sensor_data->type>
    string_t * dir_history = get_dir_history( sensor_data );
    string_t * filename = get_file_history( sensor_data, dir_history );
    FILE * fp = string_fopen( filename, "w", FOPEN_KEEP_FILENAME );

    if( fp != NULL )
    {
        for( int i = 0; i < (24*60); i++ )
        {
            fprintf( fp, "%02d:%02d %.1f %.1f %d %d\n", i/60, i%60, sensor_data->history[i] );
        }

        fclose( fp );
    }

    string_destroy( dir_history );
    string_destroy( filename );
}

void sensor_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    if( string_locate_content( line, SENSOR_HEADER ) != 0 ) return;

    sensor_t * new_item = ( sensor_t * )settings_create_item( line, SENSOR_HEADER, sizeof( sensor_t ) );
    if( new_item == NULL ) return;
    
    while( 1 )
    {
        string_t * read_line = settings_get_line_string( fp );
        if( read_line == NULL ) break;

        string_t * s_param = NULL;
        int temp_param = 0;

        if( string_locate_content( read_line, PARAM_TYPE ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_TYPE );

            if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_TEMPERATURE ) )     new_item->type = Sensor_Temperature;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_HUMIDITY ) )   new_item->type = Sensor_Humidity;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_SWITCH ) )     new_item->type = Sensor_Switch;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_BUTTON ) )     new_item->type = Sensor_Button;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_VALVE_EQIVA ) ) new_item->type = Sensor_Valve_Eqiva;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_VALVE_TIME ) ) new_item->type = Sensor_Valve_Tima;
            else if( !strcmp(string_get_char_buffer( s_param ), SENSOR_PARAM_INTERNAL ) )   new_item->type = Sensor_Internal;
        }
        else if( string_locate_content( read_line, PARAM_DRIVER ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_DRIVER );
            new_item->driver = driver_locate( home_data, string_get_char_buffer( s_param ) );
        }
        else if( string_locate_content( read_line, SENSOR_PARAM_INVERTED ) == 0 )
        {
            new_item->is_inverted = TRUE;
        }
        else if( string_locate_content( read_line, PARAM_VALUE_ON ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_VALUE_ON );
            settings_get_numbers( s_param, &temp_param, 1 );
            new_item->value_on = ( float )temp_param;
        }
        else if( string_locate_content( read_line, PARAM_VALUE_OFF ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_VALUE_OFF );
            settings_get_numbers( s_param, &temp_param, 1 );
            new_item->value_off = ( float )temp_param;
        }

        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( read_line );
    }

    new_item->p_home = home_data;
    list_insert_tail( &home_data->sensor_list, &new_item->node );
}

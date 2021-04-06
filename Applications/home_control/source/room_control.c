#include "room_control.h"
#include "string_lib.h"
#include "settings.h"
#include "tima_libc.h"
#include "background.h"
#include "generate_html.h"

////////////////////////////////////////////////////////////////////

static const char mon[][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

////////////////////////////////////////////////////////////////////

#define LAST_MINUTE_OF_THE_DAY  ((23*60)+59)

////////////////////////////////////////////////////////////////////

static void room_data_setup_history_data( room_data_t * room_data )
{
    time_t read_time = time( NULL );
    struct tm * date_time = localtime( &read_time );
    
    if( room_data->file_history != NULL ) string_destroy( room_data->file_history );
    if( room_data->dir_history != NULL ) string_destroy( room_data->dir_history );
    if( room_data->graph_title != NULL ) string_destroy( room_data->graph_title );

    room_data->file_history = string_sprintf( "file_history_%04d_%02d_%02d_%s.dat", date_time->tm_year+1900, date_time->tm_mon+1, date_time->tm_mday, room_data->command );
    room_data->dir_history = string_sprintf( "dir_history_%s", room_data->command );
    
    //printf( "File history: %s/%s", string_get_char_buffer( room_data->dir_history ), string_get_char_buffer( room_data->file_history ) );
    
    room_data->graph_title = string_sprintf( "%2d %s, %4d - %s", date_time->tm_mday, mon[date_time->tm_mon], date_time->tm_year+1900, room_data->name );
    //printf( " title: %s\r\n", string_get_char_buffer( room_data->graph_title ) );
}

static void room_load_graph_file_list( room_data_t * room_data )
{
    FILE * fp;
    string_t * filename;
    string_t * file_line;
    int line_count;
    fpos_t curr_pos;
    entry_fpos_t * file_pos;
    home_data_t * home_data = ( home_data_t * )room_data->p_home;
    
    filename = string_sprintf( "%s/history_list_%s.txt", string_get_char_buffer( home_data->root_dir ), room_data->command );
    printf( "Load %s\r\n", string_get_char_buffer( filename ) );
    
    line_count = 0;
    fp = string_fopen( filename, "r", FOPEN_DESTROY_FILENAME );
    if( fp != NULL )
    {
        fgetpos( fp, &curr_pos );
        while( ( file_line = string_file_line( fp ) ) != NULL )
        {
            if( string_length( file_line ) > 10 )
            {
                file_pos = ( entry_fpos_t * )ZMMALLOC( sizeof( entry_fpos_t ) );
                if( file_pos == NULL ) break;
                file_pos->file_pos = curr_pos;
                file_pos->index = line_count;
                line_count++;

                list_insert_tail( &room_data->graph_pos_list, &file_pos->node );
            }
            
            fgetpos( fp, &curr_pos );
            string_destroy( file_line );
        }
        
        fclose( fp );
    }
}

static void room_add_graph_history_entry( room_data_t * room_data )
{
    FILE * fp;
    string_t * filename;
    string_t * file_line;
    bool_t is_found = FALSE;
    home_data_t * home_data = ( home_data_t * )room_data->p_home;

    filename = string_sprintf( "%s/history_list_%s.txt", string_get_char_buffer( home_data->root_dir ), room_data->command );
    //printf( "%s\r\n", string_get_char_buffer( filename ) );
    
    fp = string_fopen( filename, "r", FOPEN_KEEP_FILENAME );
    if( fp != NULL )
    {
        while( ( ( file_line = string_file_line( fp ) ) != NULL ) && ( is_found == FALSE ) )
        {
            if( string_locate_content( file_line, string_get_char_buffer( room_data->file_history ) ) == 0 )
            {
                is_found = TRUE;
            }
            string_destroy( file_line );
        }
        
        fclose( fp );
    }

    if( is_found == FALSE )
    {
        fp = string_fopen( filename, "a+", FOPEN_KEEP_FILENAME );
        if( fp != NULL )
        {
            fprintf( fp, "%s : %s\r\n", string_get_char_buffer( ( string_t * )room_data->file_history ), string_get_char_buffer( ( string_t * )room_data->graph_title ) );
            fclose( fp );
        }
    }
    
    string_destroy( filename );
}

static void room_load_profiles( home_data_t * home_data, string_t * line, FILE * fp )
{
    profile_t * new_profile = ( profile_t * )settings_create_item( line, PROFILE_HEADER, sizeof( profile_t ) );
    if( new_profile == NULL ) return;
    
    while( 1 )
    {
        int value_list[5];
        string_t * setting_line = settings_get_line_string( fp );
        if( setting_line == NULL ) break;
        
        settings_get_numbers( setting_line, value_list, 5 );
        string_destroy( setting_line );
        
        config_entry_t * new_entry = ( config_entry_t * )ZMMALLOC( sizeof( config_entry_t ) );
        if( new_entry == NULL ) break;
        
        new_entry->start_hour  = value_list[0];
        new_entry->start_min   = value_list[1];
        new_entry->end_hour    = value_list[2];
        new_entry->end_min     = value_list[3];
        new_entry->temperature = value_list[4];
        
        list_insert_tail( &new_profile->entry_list, &new_entry->node );
    }
    
    list_insert_tail( &home_data->profile_list, &new_profile->node );
}

static void room_load_settings( home_data_t * home_data, string_t * line, FILE * fp )
{
    settings_t * new_settings = ( settings_t * )settings_create_item( line, SETTINGS_HEADER, sizeof( settings_t ) );
    if( new_settings == NULL ) return;
    
    uint32_t index = 0;
    
    while( index < 4 )
    {
        string_t * setting_line = settings_get_line_string( fp );
        if( setting_line == NULL ) break;
        
        profile_t * search_profile = room_locate_profile( home_data, string_get_char_buffer( setting_line ) );
        if( search_profile != NULL )
        {
            new_settings->profile_list[index] = search_profile;
            index++;
        }
        
        string_destroy( setting_line );
    }
    
    list_insert_tail( &home_data->settings_list, &new_settings->node );
}

void room_data_generate_graphic( room_data_t * room_data, string_t ** response )
{
    home_data_t * home_data = ( home_data_t * )room_data->p_home;
    string_t * output;
    
    string_t * data_file = string_sprintf( "%s/%s/%s", string_get_char_buffer( home_data->root_dir ),
                                         string_get_char_buffer( room_data->dir_history ),
                                         string_get_char_buffer( room_data->file_history ) );

    string_t * graph_temp_name = string_sprintf( "graph_output_%s.png", room_data->command );
    
    string_t * filename = string_sprintf( "%s/do_temp_plot.sh", string_get_char_buffer( home_data->root_dir ) );
    FILE * fp = fopen( string_get_char_buffer( filename ), "w" );
    if( fp == NULL ) return;
    string_destroy( filename );
    
    fprintf( fp, "#!/usr/bin/gnuplot\n" );
    fprintf( fp, "set terminal png\n" );
    fprintf( fp, "set grid\n" );
    fprintf( fp, "set term pngcairo\n" );
    fprintf( fp, "set output \"%s\"\n", string_get_char_buffer( graph_temp_name ) );
    fprintf( fp, "set yrange [-10:40]\n" );
    fprintf( fp, "set xdata time\n" );
    fprintf( fp, "set timefmt \"%%M:%%S\"\n" );
    fprintf( fp, "set format x \"%%M:%%S\"\n" );
    fprintf( fp, "set xtics \"00:00\", 240, \"24:00\"\n" );
    fprintf( fp, "plot \"%s\" using 1:2 with lines title '%s'\n\n", string_get_char_buffer( data_file ), string_get_char_buffer( room_data->graph_title ) );
    fclose( fp );
    
    filename = string_create_ex( "sudo ./do_temp_plot.sh" );
    output = background_spawn( string_get_char_buffer( filename ) );
    //printf( "%s\n", string_get_char_buffer( output ) );
    string_destroy( output );
    string_destroy( filename );
    
    filename = string_sprintf( "sudo cp ./%s /var/www/html/assets/images", string_get_char_buffer( graph_temp_name ) );
    output = background_spawn( string_get_char_buffer( filename ) );
    //printf( "%s\n", string_get_char_buffer( output ) );
    string_destroy( output );
    string_destroy( filename );
    
    if( response != NULL )
    {
        //printf( "Generate %s\n", string_get_char_buffer( filename ) );
        html_generate_box_image( *response, string_get_char_buffer( graph_temp_name ) );
    }

    string_destroy( graph_temp_name );
}

void room_save_temperature_history( room_data_t * room_data )
{
    FILE * fp;
    home_data_t * home_data = ( home_data_t * )room_data->p_home;
    string_t * filename = string_sprintf( "%s/%s/%s", string_get_char_buffer( home_data->root_dir ),
                                                      string_get_char_buffer( room_data->dir_history ),
                                                      string_get_char_buffer( room_data->file_history ) );
    string_t * dir_name = string_sprintf( "%s/%s", string_get_char_buffer( home_data->root_dir ), string_get_char_buffer( room_data->dir_history ) );

    struct stat st = {0};
    
    if( stat( string_get_char_buffer( dir_name ), &st ) == -1 )
    {
        mkdir( string_get_char_buffer( dir_name ), 0700);
    }
    
    fp = string_fopen( filename, "w", FOPEN_KEEP_FILENAME );
    //printf( "Save graph %s (fp = %d)\n", string_get_char_buffer( filename ), (fp != NULL) );
    
    if( fp != NULL )
    {
        int i;
        
        for( i = 0; i < (24*60); i++ )
        {
            fprintf( fp, "%02d:%02d %.1f %.1f %d %d\n", i/60, i%60, room_data->temp_history[i], room_data->humid_history[i], room_data->target_history[i], room_data->valve_history[i] );
        }
        fclose( fp );
    }
    
    string_destroy( filename );
    string_destroy( dir_name );
}

static void room_load_temperature_history( room_data_t * room_data )
{
    FILE * fp;
    home_data_t * home_data = ( home_data_t * )room_data->p_home;
    
    string_t * filename = string_sprintf( "%s/%s/%s", string_get_char_buffer( home_data->root_dir ),
                                         string_get_char_buffer( room_data->dir_history ),
                                         string_get_char_buffer( room_data->file_history ) );

    fp = string_fopen( filename, "r", FOPEN_DESTROY_FILENAME );
    if( fp != NULL )
    {
        int i = 0;
        
        while( i < (24*60) )
        {
            string_t * file_line = string_file_line( fp );
            
            float temp, humidity;
            int target, valve;
            int hour, min;
            
            sscanf( file_line->buffer, "%d:%d %f %f %d %d", &hour, &min, &temp, &humidity, &target, &valve );
            room_data->temp_history[i] = temp;
            room_data->humid_history[i] = humidity;
            room_data->target_history[i] = target;
            room_data->valve_history[i] = valve;
            i++;
            
            string_destroy( file_line );
        }

        fclose( fp );
    }
    else
    {
        room_save_temperature_history( room_data );
    }
}

static void room_load_hot_water( home_data_t * home_data, string_t * line, FILE * fp )
{
    room_data_t * new_room = ( room_data_t * )settings_create_item( line, HOT_WATER_HEADER, sizeof( room_data_t ) );
    if( new_room == NULL ) return;
    
    uint32_t index = 0;
    while( index < 3 )
    {
        string_t * room_line = settings_get_line_string( fp );
        if( room_line == NULL ) break;
        
        string_t * s_param = NULL;
        if( string_locate_content( room_line, COMMAND_PARAM ) == 0 )
        {
            s_param = settings_get_param( room_line, COMMAND_PARAM );
            strcpy( new_room->command, string_get_char_buffer( s_param ) );
            index++;
        }
        else if( string_locate_content( room_line, SETTINGS_PARAM ) == 0 )
        {
            s_param = settings_get_param( room_line, SETTINGS_PARAM );
            settings_t * settings = room_locate_settings( home_data, string_get_char_buffer( s_param ) );
            if( settings != NULL )
            {
                index++;
                new_room->settings = settings;
            }
        }
        
        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( room_line );
    }
    
    home_data->hot_water = new_room;
}

static void room_data_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    room_data_t * new_room = ( room_data_t * )settings_create_item( line, ROOM_HEADER, sizeof( room_data_t ) );
    if( new_room == NULL ) return;
    new_room->p_home = home_data;
    
    uint32_t index = 0;
    while( index < 3 )
    {
        string_t * room_line = settings_get_line_string( fp );
        if( room_line == NULL ) break;
        
        string_t * s_param = NULL;
        if( string_locate_content( room_line, COMMAND_PARAM ) == 0 )
        {
            s_param = settings_get_param( room_line, COMMAND_PARAM );
            strcpy( new_room->command, string_get_char_buffer( s_param ) );
            index++;
        }
        else if( string_locate_content( room_line, SETTINGS_PARAM ) == 0 )
        {
            s_param = settings_get_param( room_line, SETTINGS_PARAM );
            settings_t * settings = room_locate_settings( home_data, string_get_char_buffer( s_param ) );
            if( settings != NULL )
            {
                index++;
                new_room->settings = settings;
            }
        }
        
        if( s_param != NULL ) string_destroy( s_param );
        string_destroy( room_line );
    }
    
    list_insert_tail( &home_data->room_list, &new_room->node );
    
    new_room->state = Room_State_Boot;
    
    room_data_setup_history_data( new_room );
    room_add_graph_history_entry( new_room );
    room_load_graph_file_list( new_room );
    room_load_temperature_history( new_room );
}

static void room_save_profiles( home_data_t * home_data, FILE * fp )
{
    profile_t * profile = ( profile_t * )list_get_head( &home_data->profile_list );
    
    while( profile != NULL )
    {
        fprintf( fp, "%s: %s\r\n", PROFILE_HEADER, profile->name );
        config_entry_t * configs = ( config_entry_t * )list_get_head( &profile->entry_list );
        
        while( configs != NULL )
        {
            fprintf( fp, "%2d, %2d, %2d, %2d, %2d\r\n", configs->start_hour, configs->start_min,
                    configs->end_hour, configs->end_min, configs->temperature );
            
            configs = list_get_next( &profile->entry_list, &configs->node );
        }
        
        fprintf( fp, "\r\n" );
        
        profile = ( profile_t * )list_get_next( &home_data->profile_list, &profile->node );
    }
}

static void room_save_settings( home_data_t * home_data, FILE * fp )
{
    settings_t * search = ( settings_t * )list_get_head( &home_data->settings_list );
    int counter;
    
    while( search != NULL )
    {
        fprintf( fp, "%s: %s\r\n", SETTINGS_HEADER, search->name );
        
        for( counter = 0; counter < 4; counter++ )
        {
            if( search->profile_list[counter] != NULL )
            {
                fprintf( fp, "%s\r\n", search->profile_list[counter]->name );
            }
        }
        
        fprintf( fp, "\r\n" );
        
        search = ( settings_t * )list_get_next( &home_data->settings_list, &search->node );
    }
}

void room_destroy_profile( list_node_t * node )
{
    profile_t * profile = ( profile_t * )node;
    list_clear( &profile->entry_list );
}

void room_destroy_room_data( list_node_t * node )
{
    room_data_t * room_data = ( room_data_t * )node;
    if( room_data->file_history != NULL ) string_destroy( room_data->file_history );
    if( room_data->graph_title != NULL ) string_destroy( room_data->graph_title );
    
    list_clear( &room_data->graph_pos_list );
}

void room_save( home_data_t * home_data, FILE * fp )
{
    room_save_profiles( home_data, fp );
    room_save_settings( home_data, fp );
    
    room_data_t * search = ( room_data_t * )list_get_head( &home_data->room_list );
    
    while( search != NULL )
    {
        fprintf( fp, "%s: %s\r\n", ROOM_HEADER, search->name );
        fprintf( fp, "%s: %s\r\n", COMMAND_PARAM, search->command );
        fprintf( fp, "%s: %s\r\n", SETTINGS_PARAM, search->settings->name );
        fprintf( fp, "\r\n" );
        
        search = ( room_data_t * )list_get_next( &home_data->room_list, &search->node );
    }
    
    fprintf( fp, "%s: %s\r\n", HOT_WATER_HEADER, home_data->hot_water->name );
    fprintf( fp, "%s: %s\r\n", COMMAND_PARAM,    home_data->hot_water->command );
    fprintf( fp, "%s: %s\r\n", SETTINGS_PARAM,   home_data->hot_water->settings->name );
    fprintf( fp, "\r\n" );
}

bool_t room_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    bool_t ret = FALSE;
    
    if( string_locate_content( line, PROFILE_HEADER ) == 0 )
    {
        room_load_profiles( home_data, line, fp );
        ret = TRUE;
    }
    else if( string_locate_content( line, SETTINGS_HEADER ) == 0 )
    {
        room_load_settings( home_data, line, fp );
        ret = TRUE;
    }
    else if( string_locate_content( line, ROOM_HEADER ) == 0 )
    {
        room_data_load( home_data, line, fp );
        ret = TRUE;
    }
    else if( string_locate_content( line, HOT_WATER_HEADER ) == 0 )
    {
        room_load_hot_water( home_data, line, fp );
        ret = TRUE;
    }
    
    return ret;
}

bool_t room_get( home_data_t * home_data, room_data_t ** room_data )
{
    GET_ITEM_FROM_LIST(room_data_t, home_data->room_list, room_data);
}

bool_t room_hot_water_get( home_data_t * home_data, room_data_t ** room_data )
{
    bool_t ret = FALSE;
    
    if( home_data->hot_water != NULL )
    {
        *room_data = home_data->hot_water;
        ret = TRUE;
    }
    
    return ret;
}

profile_t * room_locate_profile( home_data_t * home_data, const char * name )
{
    return ( profile_t * )settings_locate_item( &home_data->profile_list, name );
}

settings_t * room_locate_settings( home_data_t * home_data, const char * name )
{
    return ( settings_t * )settings_locate_item( &home_data->settings_list, name );
}

room_data_t * room_locate( home_data_t * home_data, const char * name )
{
    return ( room_data_t * )settings_locate_item( &home_data->room_list, name );
}

room_data_t * room_locate_room_by_ref( home_data_t * home_data, const char * ref )
{
    room_data_t * search = ( room_data_t * )list_get_head( &home_data->room_list );
    
    while( search != NULL )
    {
        if( !strcmp( search->command, ref ) )
        {
            return search;
        }
        
        search = ( room_data_t * )list_get_next( &home_data->room_list, &search->node );
    }
    
    if( !strcmp( home_data->hot_water->command, ref ) )
    {
        return home_data->hot_water;
    }
    
    return NULL;
}

void room_store_recorded_data( room_data_t * room_data )
{
    time_t read_time = time( NULL );
    struct tm * date_time = localtime( &read_time );
    uint32_t index = ( date_time->tm_hour * 60 ) + date_time->tm_min;
    
    room_data->bitmask |= ROOM_VALID_TEMPERATURE;

    room_data->bitmask &= ~ROOM_RECEIVED_TEMPERATURE;
    room_data->bitmask &= ~ROOM_RECEIVED_HUMIDITY;

    if( ( room_data->state == Room_State_Collecting ) && ( date_time->tm_hour == 0 ) )
    {
        // Previous day
        room_data->recorded_hour = 0;
        room_save_temperature_history( room_data );

        // New day
        room_data_setup_history_data( room_data );
        room_add_graph_history_entry( room_data );
        
        room_data->state = Room_State_Setup;
    }

    room_data->temp_history[index] = room_data->temperature;
    room_data->valve_history[index] = room_data->valve_pos;
    room_data->humid_history[index] = room_data->humidity;
    room_get_target_temperature( room_data, &room_data->target_history[index] );
    
    if( ( room_data->state == Room_State_Collecting ) && ( room_data->recorded_hour != date_time->tm_hour ) )
    {
        room_data->recorded_hour = date_time->tm_hour;
        room_save_temperature_history( room_data );
    }

    if( ( room_data->state != Room_State_Collecting ) && ( date_time->tm_hour > 0 ) )
    {
        room_data->state = Room_State_Collecting;
    }    
}

bool_t room_get_target_temperature( room_data_t * room_data, int * temperature )
{
    bool_t ret = FALSE;
    date_time_t * date_time = tima_localtime( time( NULL ) );
    profile_t * profile = room_data->settings->profile_list[room_data->curr_profile];
    
    if( profile != NULL )
    {
        config_entry_t * configs = list_get_head( &profile->entry_list );
        
        while( configs != NULL )
        {
            uint32_t config_total_min_start = ( configs->start_hour * 60 ) + configs->start_min;
            uint32_t config_total_min_end   = ( configs->end_hour * 60 ) + configs->end_min;
            uint32_t now_total_min          = ( date_time->tm_hour * 60 ) + date_time->tm_min;
            if( config_total_min_end == LAST_MINUTE_OF_THE_DAY ) config_total_min_end++;
            
            if( ( now_total_min >= config_total_min_start ) && ( now_total_min < config_total_min_end ) )
            {
                *temperature = configs->temperature;
                ret = TRUE;
                break;
            }
            
            configs = list_get_next( &profile->entry_list, &configs->node );
        }
    }
    
    return ret;
}

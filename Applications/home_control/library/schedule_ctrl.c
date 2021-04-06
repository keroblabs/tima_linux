#include "schedule_ctrl.h"
#include "settings.h"
#include "driver_ctrl.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static void schedule_delete_node( list_node_t * node )
{
    schedule_t * schedule = ( schedule_t * )node;
    list_clear( &schedule->schedule_list );
}

int schedule_diff_time( int ref_hour, int ref_min, int check_hour, int check_min )
{
    int ref_time = ( ref_hour * 60 ) + ref_min;
    int check_time = ( check_hour * 60 ) + check_min;
    
    return check_time - ref_time;
}

bool_t schedule_get( home_data_t * home_data, schedule_t ** data )
{
    GET_ITEM_FROM_LIST(schedule_t, home_data->schedule_list, data);
}

schedule_t * schedule_locate( home_data_t * home_data, const char * name )
{
    schedule_t * data = NULL;

    while( schedule_get( home_data, &data ) == TRUE )
    {
        if( !strcmp( name, data->name ) )
        {
            break;
        }
    }

    return data;
}

void schedule_process( home_data_t * home_data )
{
    schedule_t * schedule = NULL;
    bool_t is_update = FALSE;

    while( schedule_get( home_data, &schedule ) == TRUE )
    {
        if( ( schedule_check( schedule, home_data->active_profile ) == TRUE ) && ( schedule->schedule_on == FALSE ) )
        {
            schedule->schedule_on = TRUE;
        }
        else if( ( schedule_check( schedule, home_data->active_profile ) == FALSE ) && ( schedule->schedule_on == TRUE ) )
        {
            schedule->schedule_on = FALSE;
        }
        
        if( is_update && ( schedule->driver != NULL ) )
        {
            driver_t * driver = ( driver_t * )schedule->driver;
            driver_set_state( driver, schedule->schedule_on );
        }
    }
}

bool_t schedule_check( schedule_t * schedule, uint8_t profile )
{
    bool_t ret = FALSE;

    if( schedule->profile != profile ) return FALSE;

    time_t read_time = time( NULL );
    struct tm * date_time = localtime( &read_time );

    schedule_item_t * entry = (schedule_item_t *)list_get_head( &schedule->schedule_list );
    while( entry )
    {
        if( ( schedule_diff_time( entry->start_hour, entry->start_min, date_time->tm_hour, date_time->tm_min ) >= 0 ) &&
            ( schedule_diff_time( entry->end_hour, entry->end_min, date_time->tm_hour, date_time->tm_min ) < 0 ) )
        {
            ret = TRUE;
            break;
        }

        entry = ( schedule_item_t * )list_get_next( &schedule->schedule_list, &entry->node );
    }

    return ret;
}

void schedule_init( home_data_t * home_data )
{
    list_init( &home_data->schedule_list, schedule_delete_node );
}

void schedule_destroy( home_data_t * home_data )
{
    list_clear( &home_data->schedule_list );
}

void schedule_load( home_data_t * home_data, string_t * line, FILE * fp )
{
    if( string_locate_content( line, SCHEDULE_HEADER ) != 0 ) return;

    schedule_t * new_item = ( schedule_t * )settings_create_item( line, SCHEDULE_HEADER, sizeof( schedule_t ) );
    if( new_item == NULL ) return;

    while( 1 )
    {
        string_t * read_line = settings_get_line_string( fp );
        if( read_line == NULL ) break;

        string_t * s_param = NULL;
        int temp_param = 0;

        if( string_locate_content( read_line, PARAM_PROFILE ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_PROFILE );
            settings_get_numbers( s_param, &temp_param, 1 );
            new_item->profile = ( uint8 )temp_param;
        }
        else if( string_locate_content( read_line, PARAM_DRIVER ) == 0 )
        {
            s_param = settings_get_param( read_line, PARAM_DRIVER );
            new_item->driver = driver_locate( home_data, string_get_char_buffer( s_param ) );
        }
        else
        {
            int value_list[4];
            settings_get_numbers( read_line, value_list, 4 );
            schedule_item_t * schedule_item = ( schedule_item_t *)ZMMALLOC( sizeof( schedule_item_t ) );
            if( schedule_item )
            {
                schedule_item->start_hour = value_list[0];
                schedule_item->start_min  = value_list[1];
                schedule_item->end_hour   = value_list[2];
                schedule_item->end_min    = value_list[3];
            }
            list_insert_tail( &new_item->schedule_list, &schedule_item->node );
        }
    }

    list_insert_tail( &home_data->schedule_list, &new_item->node );
}

#include "temp_room.h"
#include "lists.h"
#include "timer.h"
#include "room_control.h"
#include "generate_html.h"
#include "valve_control.h"
#include "background.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    Button_Link_None,
    Button_Link_Back,
    Button_Link_Details,
    Button_Link_Setup,

} button_link_t;

///////////////////////////////////////////////////////////////////////////////////////

static void build_response( home_data_t * home_data, string_t * response, room_data_t * room_data )
{
    string_t * temp = NULL;
    
    if( room_data->curr_profile == -1 ) return;
    
    html_generate_box_header( response );
    html_generate_box_title( response, room_data->name );
    
    html_generate_box_temperature( response, room_data->temperature );

    valve_t * valve = valve_locate_from_room( home_data, room_data->name );
    if( ( valve != NULL ) && ( valve->valve_pos != ( uint8_t )NEG_U32 ) )
    {
        string_t * extra_info = string_sprintf( "Valve: %d%%", valve->valve_pos );
        html_generate_box_extra_info( response, string_get_char_buffer( extra_info ) );
        string_destroy( extra_info );
        
        if( valve->low_battery == TRUE )
        {
            html_generate_box_extra_info( response, "Low Battery" );
        }
    }
    
    html_generate_button_header( response );
    html_generate_button( response, "control.php?cmd=display&param=room_temperature", "Back" );
    
    temp = string_sprintf( "control.php?cmd=graph&param=%s", room_data->command );
    html_generate_button( response, string_get_char_buffer( temp ), "Graph" );
    string_destroy( temp );
    
    html_generate_box_end( response );
}

static void build_response_table( string_t * response, room_data_t * room_data )
{
    string_t * temp = NULL;
    
    if( room_data->curr_profile == -1 ) return;
    
    html_generate_table_start_end( response, TRUE );
    
    html_generate_table_entry( response, room_data->name, NULL );

    temp = string_sprintf( "%d", room_data->temperature );
    html_generate_table_entry( response, string_get_char_buffer( temp ), NULL );
    string_destroy( temp );
    
    //html_generate_table_entry( response, "Off", NULL );
    
    temp = string_sprintf( "control.php?cmd=details&param=%s", room_data->command );
    html_generate_table_entry( response, "Go", string_get_char_buffer( temp ) );
    string_destroy( temp );
    
    html_generate_table_start_end( response, FALSE );
}

string_t * build_temperature_page( home_data_t * home_data )
{
    string_t * response = NULL;
    room_data_t * room_data;
    
    response = string_create();
    
    html_generate_header( response, "Home Control" );
    html_generate_box_header_title( response, "Home Control" );
    html_generate_table_header( response );
    
    html_generate_table_entry( response, "Place", NULL );
    html_generate_table_entry( response, "Temp", NULL );
    //html_generate_table_entry( response, "Valve", NULL );
    html_generate_table_entry( response, "More", NULL );
    
    html_generate_table_content( response );
    
    room_data = NULL;
    while( room_get( home_data, &room_data ) == TRUE )
    {
        build_response_table( response, room_data );
    }
    if( room_hot_water_get( home_data, &room_data ) == TRUE )
    {
        build_response_table( response, room_data );
    }
    
    html_generate_table_end( response );
    html_generate_box_title_end( response );
    html_generate_footer( response );
    
    return response;
}

string_t * build_graph_page( home_data_t * home_data, const char * room_ref )
{
    string_t * response = NULL;
    string_t * temp;
    room_data_t * room_data;
    
    room_data = room_locate_room_by_ref( home_data, room_ref );
    if( room_data == NULL )
    {
        return NULL;
    }
    
    response = string_create();
    
    temp = string_create_ex( "Home Control - " );
    string_append_text( temp, room_data->name );
    html_generate_header( response, string_get_char_buffer( temp ) );
    string_destroy( temp );
    
    room_save_temperature_history( room_data );
    room_data_generate_graphic( room_data, &response );
    html_generate_footer( response );

    return response;
}

string_t * build_room_page( home_data_t * home_data, const char * room_ref )
{
    string_t * response = NULL;
    string_t * temp;
    room_data_t * room_data;
    
    room_data = room_locate_room_by_ref( home_data, room_ref );
    if( room_data == NULL )
    {
        return NULL;
    }
    
    response = string_create();
    
    temp = string_create_ex( "Home Control - " );
    string_append_text( temp, room_data->name );
    html_generate_header( response, string_get_char_buffer( temp ) );
    string_destroy( temp );
    
    //html_generate_title( response, "Room Temperature" );
    //room_save_temperature_history( room_data );
    
    // build_response( response, room_data, Button_Link_Setup );
    build_response( home_data, response, room_data );

    html_generate_footer( response );
    
    return response;
}

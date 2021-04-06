#include "build_page.h"
#include "net_comms.h"
#include "string_lib.h"
#include "driver_ctrl.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static const char * page_header =       "<!DOCTYPE html>\r\n"
                                        "<html lang=\"en\">\r\n"
                                        "<head>\r\n"
                                        "<title>%s</title>\r\n"
                                        "<meta charset=\"utf-8\">\r\n"
                                        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n"
                                        "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">\r\n"
                                        "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js\"></script>\r\n"
                                        "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\"></script>\r\n"
                                        "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\"></script>\r\n"
                                        "</head>\r\n"
                                        "<body>\r\n";

static const char * table_header =      "<div class=\"container\">\r\n"
                                        "<h2>%s</h2>\r\n"
                                        "<table class=\"table\">\r\n"
                                        "<thead><tr><th>%s</th><th>%s</th>\r\n"
                                        "</tr></thead><tbody>\r\n";

static const char * table_row_item =    "<tr><td>%s</td><td>\r\n"
                                        "<button type=\"button\" class=\"btn btn-%s btn-block\">%s</button></td></tr>\r\n";

static const char * table_row_link =    "<tr><td>%s</td><td>\r\n"
                                        "<a class=\"btn btn-%s btn-lg btn-block\" href=\"%s\" role=\"button\">%s</a>\r\n";

static const char * page_end =          "</tbody></table></div></body></html>\r\n";

////////////////////////////////////////////////////////////////////

static void build_page_add_page_header( string_t * response, const char * page_name )
{
    string_t * temp = string_sprintf( page_header, page_name );
    string_append( response, temp );
    string_destroy( temp );
}

static void build_page_add_table_header( string_t * response, const char * table_name, const char * row1, const char * row2 )
{
    string_t * temp = string_sprintf( table_header, table_name, row1, row2 );
    string_append( response, temp );
    string_destroy( temp );
}

static void build_page_app_table_item( string_t * response, const char * row1, const char * button_mode, const char * row2, const char * link )
{
    string_t * temp;
    
    if( link != NULL )
    {
        temp = string_sprintf( table_row_link, row1, button_mode, link, row2 );
    }
    else
    {
        temp = string_sprintf( table_row_item, row1, button_mode, row2 );
    }
    
    string_append( response, temp );
    string_destroy( temp );
}

static void build_page_add_page_end( string_t * response )
{
    string_t * temp = string_create_ex( page_end );
    string_append( response, temp );
    string_destroy( temp );
}

string_t * build_page_switch_table( home_data_t * home_data )
{
    // const char * url_driver = "http://192.168.1.201/control?cmd=GPIO,12,1";
    
    string_t     * ret  = string_create();
    driver_t     * data = NULL;
    
    build_page_add_page_header( ret, "Switch list" );
    build_page_add_table_header( ret, "Switch table", "Switch Name", "On/Off" );

    while( driver_get( home_data, &data ) == TRUE )
    {
        string_t * url_driver = string_create();
        url_driver = string_sprintf( "http://192.168.1.200/do_driver.php?name=%s&value=%d", data->name, data->current_state ? 0 : 1 );
        
        build_page_app_table_item( ret, data->name, data->current_state ? "danger" : "secondary",
                                  data->current_state ? "On" : "Off", string_get_char_buffer( url_driver ) );
    }
    
    build_page_add_page_end( ret );
    
    return ret;
}

static string_t * create_plot_script_file( sensor_t * sensor_data, string_t * script_file, string_t * command, int min_range, int max_range )
{
    home_data_t * home_data = ( home_data_t * )sensor_data->p_home;
    string_t * filename = string_sprintf( "%s/%s", string_get_char_buffer( home_data->root_dir ), string_get_char_buffer( script_file ) );

    string_t * graph_temp_name = string_sprintf( "graph_output_%s.png", sensor_data->name );

    FILE * fp = fopen( string_get_char_buffer( filename ), "w" );
    if( fp == NULL ) return string_create_ex( "" );
    string_destroy( filename );

    fprintf( fp, "#!/usr/bin/gnuplot\n" );
    fprintf( fp, "set terminal png\n" );
    fprintf( fp, "set grid\n" );
    fprintf( fp, "set term pngcairo\n" );
    fprintf( fp, "set output \"%s\"\n", string_get_char_buffer( graph_temp_name ) );
    fprintf( fp, "set yrange [%d:%d]\n", min_range, max_range );
    fprintf( fp, "set xdata time\n" );
    fprintf( fp, "set timefmt \"%%M:%%S\"\n" );
    fprintf( fp, "set format x \"%%M:%%S\"\n" );
    fprintf( fp, "set xtics \"00:00\", 240, \"24:00\"\n" );
    fprintf( fp, "%s\n\n", string_get_char_buffer( command ) );
    fclose( fp );

    string_destroy( filename );

    return graph_temp_name;
}

static void execute_plot_script_file( string_t * script_file, string_t * plot_file )
{
    string_t * filename = string_sprintf( "sudo ./%s", string_get_char_buffer( script_file ) );
    string_t * output = background_spawn( string_get_char_buffer( filename ) );
    //printf( "%s\n", string_get_char_buffer( output ) );
    string_destroy( output );
    string_destroy( filename );

    filename = string_sprintf( "sudo cp ./%s /var/www/html", string_get_char_buffer( plot_file ) );
    output = background_spawn( string_get_char_buffer( filename ) );
    //printf( "%s\n", string_get_char_buffer( output ) );
    string_destroy( output );
    string_destroy( filename );
}

// response = home_data->page_handler( home_data, argv_1, argv_2, command, &pos );
static void * build_page_hander( void * param0, void * param1, void * param2, void * param3, void * param4 )
{
    home_data_t * home_data = ( home_data_t * )param0;
    //string_t * argv_1 = ( string_t * )param1;
    string_t * argv_2 = ( string_t * )param2;
    //string_t * command = ( string_t * )param3;
    //uint32_t * pos = ( uint32_t * )param4;
    string_t * ret = NULL;
    
    if( string_locate_content( argv_2, "switch_page" ) == 0 )
    {
        ret = build_page_switch_table( home_data );
    }
    
    return ret;
}

void build_page_init( home_data_t * home_data )
{
    net_comms_set_page_handler( home_data, build_page_hander );
}

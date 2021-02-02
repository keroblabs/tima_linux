#include "webserver.h"
#include "t_threads.h"
#include "timer.h"

#include "wlan_lib.h"

////////////////////////////////////////////////////////////////////////

#define SYSTEM_WIFI_SCAN        "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport --scan"
#define SYSTEM_WIFI_INFO        "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I"
#define SYSTEM_WIFI_INET        "ifconfig %s | grep \'inet \'"
#define SYSTEM_WIFI_CONNECT     "networksetup -setairportnetwork %s %s %s"

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

static string_t * scan_extract_ssid( string_t * scan_line )
{
    int index = string_locate_content( scan_line, " " );
    if( index == -1 ) return NULL;
    return string_get_substring( scan_line, 0, index );
}

string_t * wlan_scan_start( char * pattern )
{
    FILE * fp;
    string_t * scan_results;
    string_t * ssid_device = NULL;
    string_t * scan_line = NULL;
    char out_buffer[128];
    bool_t is_found;
    
    fp = popen( SYSTEM_WIFI_SCAN, "r" );
    if( fp == NULL ) return NULL;
    
    scan_results = string_create();
    memset( out_buffer, 0x00, sizeof( out_buffer ) );

    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        string_append_text( scan_results, out_buffer );
    }
    
    pclose( fp );
    
    // printf( "%s", string_get_char_buffer( scan_results ) );
    uint32_t curr_pos = 0;
    is_found = FALSE;
    
    // Skip first line
    scan_line = string_parse( scan_results, &curr_pos, "\n" );
    if( scan_line == NULL )
    {
        string_destroy( scan_results );
        return NULL;
    }
    
    string_destroy( scan_line );

    while( is_found == FALSE )
    {
        scan_line = string_parse( scan_results, &curr_pos, "\n" );
        if( scan_line == NULL ) break;
        string_trim( scan_line );
        
        if( !strncmp( string_get_char_buffer( scan_line ), pattern, strlen( pattern ) ) )
        {
            ssid_device = scan_extract_ssid( scan_line );
            is_found = TRUE;
        }
        
        //printf( "%s\n", string_get_char_buffer( scan_line ) );
        string_destroy( scan_line );
    }
    
    string_destroy( scan_results );

    return ssid_device;
}

void wlan_connect( char * interface, char * ssid, char * password )
{
    char connect_command[128];
    sprintf( connect_command, SYSTEM_WIFI_CONNECT, interface, ssid, password );
    system( connect_command );
    tthread_sleep_ms( 2000 );
}

string_t * wlan_get_bssid( void )
{
    char out_buffer[128];
    string_t * bssid_result;
    FILE * fp;
    
    fp = popen( SYSTEM_WIFI_INFO, "r" );
    if( fp == NULL ) return NULL;
    
    bssid_result = string_create();
    memset( out_buffer, 0x00, sizeof( out_buffer ) );
    
    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        string_append_text( bssid_result, out_buffer );
    }
    
    pclose( fp );

    string_trim( bssid_result );
    
    if( string_locate_content( bssid_result, "SSID: " ) != -1 )
    {
        string_t * bssid_string = string_get_substring( bssid_result, 6, NEG_U32 );
        
        string_destroy( bssid_result );
        bssid_result = bssid_string;
    }
    
    //printf( "%s\n", string_get_char_buffer( inet_result ) );
    
    return bssid_result;
}

string_t * wlan_get_inet( char * interface )
{
    char out_buffer[128];
    char inet_command[128];
    string_t * inet_result;
    FILE * fp;
    
    sprintf( inet_command, SYSTEM_WIFI_INET, interface );
    
    fp = popen( inet_command, "r" );
    if( fp == NULL ) return NULL;
    
    inet_result = string_create();
    memset( out_buffer, 0x00, sizeof( out_buffer ) );
    
    while( fgets( out_buffer, 100, fp ) != NULL )
    {
        string_append_text( inet_result, out_buffer );
    }
    
    pclose( fp );
    
    string_trim( inet_result );
    
    if( string_locate_content( inet_result, "inet" ) != -1 )
    {
        uint32_t pos = 5;
        string_t * ip_addr = string_parse( inet_result, &pos, " " );
        
        string_destroy( inet_result );
        inet_result = ip_addr;
    }
    
    //printf( "%s\n", string_get_char_buffer( inet_result ) );

    return inet_result;
}

void wlan_get_gateway_ip( string_t * ip_addr, uint8_t gateway_index, uint8 * gateway_ip )
{
    string_t * ret = NULL;
    string_t * part = NULL;
    uint32_t pos = 0;
    uint32_t count;
    char index_str[5];
    
    ret = string_create();
    
    for( count = 0; count < 3; count++ )
    {
        part = string_parse( ip_addr, &pos, "." );
        if( part == NULL ) break;
        int part_ip = 0;
        sscanf( string_get_char_buffer( part ), "%d", &part_ip );
        *gateway_ip = ( uint8_t )part_ip;
        gateway_ip++;
    }
    
    *gateway_ip = gateway_index;
}

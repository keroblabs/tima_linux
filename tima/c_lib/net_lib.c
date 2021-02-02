#include "tima_libc.h"

bool_t tima_str_to_ip( char * input, uint8_t * output )
{
	static char ip_addr_str[20];
	char * s_ip[4];
	int i;
	uint32_t val;

	if( strlen( input ) > 15 ) return FALSE;
	strncpy( ip_addr_str, input, sizeof( ip_addr_str ) -1 );

	for( i = 0; i < 4; i++ )
	{
		if( i == 0 ) 
		{
			s_ip[i] = ip_addr_str;
		}
		if( i < 3 )
		{
			s_ip[i+1] = strchr( s_ip[i], '.' );
			if( s_ip[i+1] == NULL ) return FALSE;
			*s_ip[i+1] = 0; s_ip[i+1]++;
			if( !tima_is_numeric( s_ip[i] ) ) return FALSE;
			val = ( uint32_t )tima_atoi( s_ip[i] );
			if( val > 255 ) return FALSE;
			output[i] = ( uint8_t )val;
		}
		else
		{
			if( !tima_is_numeric( s_ip[i] ) ) return FALSE;

			val = ( uint32_t )tima_atoi( s_ip[i] );
			if( val > 255 ) return FALSE;
			output[i] = ( uint8_t )val;
		}
	}

	return TRUE;
}

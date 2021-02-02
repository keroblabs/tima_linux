#include "nmea.h"

///////////////////////////////////////////////////////////////////////////////////////

enum
{
	NMEA_MODE_IDLE,
	NMEA_MODE_RECEIVING,
	NMEA_MODE_DECODE,
};

enum
{
	NMEA_Summer_Time_Unknown,
	NMEA_No_Summer_Time,
	NMEA_Summer_Time_First_Day,
	NMEA_Summer_Time,
	NMEA_Summer_Time_Last_Day,
};

#define NMEA_GGA_TIME_FIELD						0
#define NMEA_GGA_LATITUDE_FIELD					1
#define NMEA_GGA_LONGITUDE_FIELD				3
#define NMEA_GGA_ELEVATION_FIELD				8

#define NMEA_VTG_TRACKING_FIELD					0
#define NMEA_VTG_MAGNETIC_FIELD					3
#define NMEA_VTG_SPEED_FIELD					6

#define NMEA_GSV_SENTENCE_COUNT_FIELD			0
#define NMEA_GSV_SENTENCE_INDEX_FIELD			1
#define NMEA_GSV_SAT_TOTAL_FIELD				2
#define NMEA_GSV_SAT_START_FIELD				3

#define NMEA_RMC_TIME_FIELD						0
#define NMEA_RMC_DATE_FIELD						8

#define NMEA_GSV_SAT_PRN_FIELD_OFFSET			0
#define NMEA_GSV_SAT_ELEVATION_FIELD_OFFSET		1
#define NMEA_GSV_SAT_AZIMUTE_FIELD_OFFSET		2
#define NMEA_GSV_SAT_SNR_FIELD_OFFSET			3

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
/*
$GPGSA,A,3,24,10,18,32,,,,,,,,,9.7,6.5,7.2*

$GPGSV,3,1,12,24,83,294,39,12,54,214,,15,44,177,,19,38,088,*
$GPGSV,3,2,12,17,32,059,15,10,25,288,43,18,21,261,42,13,16,147,*
$GPGSV,3,3,12,32,13,315,45,25,12,227,,01,04,010,33,28,01,049,17*

$GPRMC,090107.000,A,5218.6186,N,00000.9793,E,0.00,,290517,,,A*

$GPVTG,,T,,M,0.00,N,0.0,K,A*

$GPGGA,090108.000,5218.6186,N,00000.9793,E,1,05,4.6,36.0,M,47.0,M,,0000*

$GPGLL,5218.6186,N,00000.9793,E,090108.000,A,A*
*/

static int _nmea_get_weekday( int day, int month, int year )
{
	return ((day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7);
}

char * nmea_get_delimiter( char * buffer )
{
	char * ret;

	ret = strchr( buffer, ',' );
	if( ret != NULL ) return ret;

	ret = strchr( buffer, '*' );
	return ret;
}

char * nmea_get_field( char * buffer, int index, int * len )
{
	char * ret;
	char * next;
	int cnt;

	ret = buffer;
	if( len ) *len = 0;

	for( cnt = 0; cnt <= index; cnt++ )
	{
		ret = nmea_get_delimiter( ret );
		if( ret == NULL )
		{
			return NULL;
		}

		ret++;
	}

	next = nmea_get_delimiter( ret );
	if( next == NULL ) return NULL;
	if( len ) *len = (int)next - (int)ret;

	return ret;
}

int nmea_field_count( char * buffer )
{
	int cnt = 0;
	char * ret;

	ret = buffer;

	while( 1 )
	{
		ret = nmea_get_delimiter( ret );
		cnt++;
		if( ret == NULL )
		{
			break;
		}

		ret++;
	}

	return cnt;
}

void nmea_get_int_value( char * buffer, int index, int * value )
{
	char * ret;
	int len;
	int value_int, value_dec;

	if( value == NULL ) return;

	ret = nmea_get_field( buffer, index, &len );
	if( ret == NULL )
	{
		*value = 0;
		return;
	}

	if( len < 1 )
	{
		*value = 0;
		return;
	}

	sscanf( ret, "%d,", value );
}

void nmea_get_float_value( char * buffer, int index, float * value )
{
	char * ret;
	int len;
	int value_int, value_dec;

	if( value == NULL ) return;

	ret = nmea_get_field( buffer, index, &len );
	if( ret == NULL )
	{
		*value = 0.0;
		return;
	}

	if( len < 2 )
	{
		*value = 0.0;
		return;
	}

	sscanf( ret, "%d.%d,", &value_int, &value_dec );

	//*value = 0.0;
	*value = (float)value_dec;
	while( *value > 1.0 ) *value /= 10;
	*value += (float)value_int;
}

void nmea_coordinate_decode( char * buffer, int index, char * output )
{
	char * ret;
	int cnt;
	int coord_int, coord_dec;
	int hours, mins, secs;
	int secs_int, secs_dec;
	int len = 0;
	char side;

	ret = nmea_get_field( buffer, index, &len );
	if( ret == NULL )
	{
		strcpy( output, "(---)" );
		return;
	}

	if( len < 3 )
	{
		strcpy( output, "(empty)" );
		return;
	}

	sscanf( ret, "%d.%d,%c,", &coord_int, &coord_dec, &side );

	hours = coord_int / 100;
	mins = coord_int - ( hours * 100 );
	secs = coord_dec * 60;

	secs_int = secs / 10000;
	secs_dec = secs - ( secs_int * 10000 );

	sprintf( output, "%d'%02d''%02d.%d %c", hours, mins, secs_int, secs_dec, side );
}

void nmea_utc_date_decode( char * buffer, int index, struct tm *std_time )
{
	char * ret;
	int len;

	ret = nmea_get_field( buffer, index, &len );
	if( ret == NULL )
	{
		return;
	}

	if( len < 3 )
	{
		return;
	}

	std_time->tm_mday = ( ( ret[0] & 0x0F ) * 10 ) + ( ret[1] & 0x0F );
	std_time->tm_mon =  ( ( ret[2] & 0x0F ) * 10 ) + ( ret[3] & 0x0F );
	std_time->tm_year = ( ( ret[4] & 0x0F ) * 10 ) + ( ret[5] & 0x0F );
	std_time->tm_wday = _nmea_get_weekday( std_time->tm_mday, std_time->tm_mon, std_time->tm_year );

	std_time->tm_mon -= 1;
	std_time->tm_year += 100;
}

void nmea_utc_time_decode( char * buffer, int index, struct tm *std_time )
{
	char * ret;
	int len;

	ret = nmea_get_field( buffer, index, &len );
	if( ret == NULL )
	{
		return;
	}

	if( len < 3 )
	{
		return;
	}

	std_time->tm_hour = ( ( ret[0] & 0x0F ) * 10 ) + ( ret[1] & 0x0F );
	std_time->tm_min = ( ( ret[2] & 0x0F ) * 10 ) + ( ret[3] & 0x0F );
	std_time->tm_sec = ( ( ret[4] & 0x0F ) * 10 ) + ( ret[5] & 0x0F );
}

void nmea_decode_GGA( char * buffer, nmea_data_t * nmea )
{
	char output[40];
	float elevation;

	// $GPGGA,090108.000,5218.6186,N,00000.9793,E,1,05,4.6,36.0,M,47.0,M,,0000*
	//printf( "%s\n", buffer );

	// coord 1
	nmea_coordinate_decode( buffer, NMEA_GGA_LATITUDE_FIELD, output );
	strcpy( nmea->latitute, output );
	//printf( "%s x ", output );
	output[0] = 0;

	// coord 2
	nmea_coordinate_decode( buffer, NMEA_GGA_LONGITUDE_FIELD, output );
	strcpy( nmea->longitude, output );
	// printf( "%s - ", output );
	output[0] = 0;

	// elevation
	nmea_get_float_value( buffer, NMEA_GGA_ELEVATION_FIELD, &elevation );
	nmea->elevation = elevation;
	//printf( "%8.3f m\n", elevation );
}

void nmea_decode_VTG( char * buffer, nmea_data_t * nmea )
{
	float tracking;

	// $GPVTG,,T,,M,0.00,N,0.0,K,A*
	// printf( "buffer" );

	// tracking
	nmea_get_float_value( buffer, NMEA_VTG_TRACKING_FIELD, &tracking );
	nmea->heading = tracking;
	//printf( "Heading %8.3f - ", tracking );

	// magnetic tracking
	nmea_get_float_value( buffer, NMEA_VTG_MAGNETIC_FIELD, &tracking );
	nmea->magnetic = tracking;
	//printf( "%8.3f degs - ", tracking );

	// ground speed
	nmea_get_float_value( buffer, NMEA_VTG_SPEED_FIELD, &tracking );
	nmea->ground_speed = tracking;
	//printf( "%8.3f km/h\n", tracking );
}

void nmea_decode_RMC( char * buffer, nmea_data_t * nmea )
{
	char output[20];
	int day, month, year;
	int last_sunday_day;
	time_t time_secs;

	// $GPRMC,193142.000,A,5218.6029,N,00000.9731,E,0.00,,141017,,,A*71

	// UTC time
	nmea_utc_time_decode( buffer, NMEA_RMC_TIME_FIELD, &nmea->utc_date );

	// UTC date
	nmea_utc_date_decode( buffer, NMEA_RMC_DATE_FIELD, &nmea->utc_date );

	// check for summer time
	time_secs = mktime( &nmea->utc_date );
	nmea->utc_date.tm_isdst = 0;

	if( ( nmea->utc_date.tm_mon >= TM_April ) && ( nmea->utc_date.tm_mon <= TM_September ) )
	{
		// summer time for sure
		nmea->utc_date.tm_isdst = 1;
	}
	else if( nmea->utc_date.tm_mon == TM_March )
	{
		last_sunday_day = 31 - _nmea_get_weekday( 1, nmea->utc_date.tm_mon + 1, nmea->utc_date.tm_year );
		if( ( ( nmea->utc_date.tm_mday == last_sunday_day ) && ( nmea->utc_date.tm_hour >= 1 ) ) ||
			( nmea->utc_date.tm_mday > last_sunday_day ) )
		{
			nmea->utc_date.tm_isdst = 1;
		}
	}
	else if( nmea->utc_date.tm_mon == TM_October )
	{
		last_sunday_day = 31 - _nmea_get_weekday( 1, nmea->utc_date.tm_mon + 1, nmea->utc_date.tm_year );
		if( ( ( nmea->utc_date.tm_mday == last_sunday_day ) && ( nmea->utc_date.tm_hour < 1 ) ) ||
			( nmea->utc_date.tm_mday < last_sunday_day ) )
		{
			nmea->utc_date.tm_isdst = 1;
		}
	}

	if( nmea->utc_date.tm_isdst )
	{
		time_secs += 3600;
		memcpy( &nmea->utc_date, localtime( &time_secs ), sizeof( struct tm ) );
		nmea->utc_date.tm_isdst = 1;
	}
}

void nmea_decode_GSV( char * buffer, nmea_data_t * nmea )
{
	int max_sentence;
	int index;
	int field;
	int total_sats;
	int cnt;

	// calculate total of sat data
	total_sats = ( ( nmea_field_count( buffer ) - 3 ) >> 2 );

	//printf( "%s\n", buffer );

	// gsv index
	nmea_get_int_value( buffer, NMEA_GSV_SENTENCE_INDEX_FIELD, &index );
	nmea_get_int_value( buffer, NMEA_GSV_SENTENCE_COUNT_FIELD, &max_sentence );
	if( index == nmea->gsv_index )
	{
		//printf( "index = %d [%d]\n", index, nmea->sat_count );

		// first sentence, reset counts
		if( index == 1 )
		{
			nmea->sat_count = 0;
		}

		field = NMEA_GSV_SAT_START_FIELD;

		// retrieve sat data from sentence
		for( cnt = 0; cnt < total_sats; cnt++ )
		{
			nmea_get_int_value( buffer, field+NMEA_GSV_SAT_PRN_FIELD_OFFSET, &nmea->sat_data[nmea->sat_count].prn );
			nmea_get_int_value( buffer, field+NMEA_GSV_SAT_ELEVATION_FIELD_OFFSET, &nmea->sat_data[nmea->sat_count].elevation );
			nmea_get_int_value( buffer, field+NMEA_GSV_SAT_AZIMUTE_FIELD_OFFSET, &nmea->sat_data[nmea->sat_count].azimute );
			nmea_get_int_value( buffer, field+NMEA_GSV_SAT_SNR_FIELD_OFFSET, &nmea->sat_data[nmea->sat_count].snr );

			//printf( "%2d: %4d - %3d - %3d - %d\n", cnt+1, nmea->sat_data[nmea->sat_count].prn,
			//											  nmea->sat_data[nmea->sat_count].elevation,
			//											  nmea->sat_data[nmea->sat_count].azimute,
			//											  nmea->sat_data[nmea->sat_count].snr );

			field += NMEA_GSV_SAT_SNR_FIELD_OFFSET+1;

			nmea->sat_count++;
		}

		nmea->gsv_index++;
		if( nmea->gsv_index > max_sentence )
		{
			nmea->gsv_index = 1;
			nmea->sat_total = nmea->sat_count;
			nmea->update_cnt++;

			//printf( "Total: %d\n", nmea->sat_total );
		}
	}
}

void nmea_decoder( char * buffer, nmea_data_t * nmea )
{
	if( !strncmp( buffer, "$GPGGA", 6 ) )
	{
		nmea_decode_GGA( buffer, nmea );
	}
	else if( !strncmp( buffer, "$GPVTG", 6 ) )
	{
		nmea_decode_VTG( buffer, nmea );
	}
	else if( !strncmp( buffer, "$GPGSV", 6 ) )
	{
		nmea_decode_GSV( buffer, nmea );
	}
	else if( !strncmp( buffer, "$GPRMC", 6 ) )
	{
		nmea_decode_RMC( buffer, nmea );
	}
}

void nmea_show( nmea_data_t * nmea )
{
	printf( "at %s: %s, %s - %8.2f m\n", asctime( &nmea->utc_date ), nmea->latitute, nmea->longitude, nmea->elevation );
	printf( "Heading: %8.3f deg, magnetic: %8.3f degs - %8.3f km/h\n", nmea->heading, nmea->magnetic, nmea->ground_speed );
}

bool_t nmea_update_sats_data( nmea_data_t * nmea )
{
	if( nmea->update_cnt != nmea->update_read )
	{
		nmea->update_read = nmea->update_cnt;
		return TRUE;
	}

	return FALSE;
}

void nmea_show_sats( nmea_data_t * nmea )
{
	int cnt;

	printf( "Total sats: %d [%d]\n", nmea->sat_total, nmea->update_cnt );

	for( cnt = 0; cnt < nmea->sat_total; cnt++ )
	{
		printf( "%2d: %4d - %3d - %3d - %d\n", cnt+1, nmea->sat_data[cnt].prn,
													  nmea->sat_data[cnt].elevation,
													  nmea->sat_data[cnt].azimute,
													  nmea->sat_data[cnt].snr );
	}
}

void nmea_init( nmea_data_t * nmea )
{
	memset( nmea, 0x00, sizeof( nmea_data_t ) );

	nmea->ground_speed = 0.0;
	nmea->magnetic = 0.0;
	nmea->heading = 0.0;
	nmea->elevation = 0.0;

	nmea->gsv_index = 1;
	nmea->sat_total = 0;
}

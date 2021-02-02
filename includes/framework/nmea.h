#ifndef nmea_library_h
#define nmea_library_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    TM_January,
    TM_February,
    TM_March,
    TM_April,
    TM_May,
    TM_June,
    TM_July,
    TM_August,
    TM_September,
    TM_October,
    TM_November,
    TM_December,
} tm_month_t;

typedef struct satellite_data_t
{
	int prn;
	int snr;
	int azimute;
	int elevation;

} sat_data_t;

typedef struct nmea_data_t
{
	float ground_speed;
	float heading;
	float magnetic;

	struct tm utc_date;

	char latitute[40];
	char longitude[40];
	float elevation;

	int gsv_index;
	int sat_count;
	int sat_total;

	int update_cnt;
	int update_read;

	sat_data_t sat_data[25];

} nmea_data_t;

////////////////////////////////////////////////////////////////////////////////////////

void nmea_decoder( char * buffer, nmea_data_t * nmea );

void nmea_init( nmea_data_t * nmea );

void nmea_show( nmea_data_t * nmea );

void nmea_show_sats( nmea_data_t * nmea );

bool_t nmea_update_sats_data( nmea_data_t * nmea );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* direction_indicator_h */

#include "system.h"
#include "logging_data.h"

///////////////////////////////////////////////////////////////////////////////////////

#ifdef TESTBENCH
#define ELM327_SERIAL_DEV       "/dev/ttyUSB0"
#define GPS_SERIAL_DEV          NULL
#else
#define ELM327_SERIAL_DEV       "/dev/ttyS0"
#define GPS_SERIAL_DEV          "/dev/ttyUSB0"
#endif

///////////////////////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
int _fe_main( void )
#else
int main( void )
#endif
{
    uint32_t index = 0;
    //system_init();

    printf( "Log browser\r\n" );

    driving_data_t driving_data;
    odometer_data_t odometer_data;
    
    while( logging_data_load_record( index++, &driving_data, &odometer_data ) == TRUE )
	{
        printf( "%4d - %8d\n", index, odometer_data.full_counter );
	}

	return 0;
}

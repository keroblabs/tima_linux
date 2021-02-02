#include "system.h"

///////////////////////////////////////////////////////////////

static lcd_driver_t * lcd_api = NULL;

///////////////////////////////////////////////////////////////

lcd_driver_t * lcd_layer_get_driver( void )
{
	device_t * lcd_device_hdl;

	if( lcd_api == NULL )
	{
		lcd_device_hdl = device_open( "/dev/lcd" );
		if( lcd_device_hdl == NULL ) return NULL;
		device_ioctrl( lcd_device_hdl, DEVICE_GET_API, &lcd_api );
		device_close( lcd_device_hdl );
	}

	return lcd_api;
}

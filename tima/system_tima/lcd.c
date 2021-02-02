#include "lcd.h"
#include "system.h"

///////////////////////////////////////////////////////////////

static lcd_driver_t * lcd_driver = NULL;

///////////////////////////////////////////////////////////////

lcd_driver_t * lcd_layer_get_driver( void )
{
	device_t * lcd_device_hdl;
    //lcd_driver_t * api_addr;

	if( lcd_driver == NULL )
	{
		lcd_device_hdl = device_open( "/dev/lcd" );
		if( lcd_device_hdl == NULL ) return NULL;
		device_ioctrl( lcd_device_hdl, DEVICE_GET_API, &lcd_driver );
        //lcd_driver = ( lcd_driver_t * )api_addr;
        //device_read_buffer(lcd_device_hdl, (uint8_t *)&lcd_driver, sizeof(lcd_driver));
		device_close( lcd_device_hdl );
	}

	return lcd_driver;
}

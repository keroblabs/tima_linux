#include "system.h"
#include "device.h"
#include "types.h"
#include "timer.h"
#include "random.h"
#include "tima_libc.h"
//#include "warning_lights.h"

///////////////////////////////////////////////////////////////////////////

#define OBD_MESSAGE_ACK             0x9A

///////////////////////////////////////////////////////////////////////////

static char obd_resp[100];
static char * p_resp;
static uint32_t resp_index;
static bool_t send_obd;

static timer_data_t update_timer;
static timer_data_t send_timer;

static int obd_rpm;
static int obd_speed;
static int obd_temp_coolant;

static uint32_t obd_mask;

static int64_t obd_seed;

///////////////////////////////////////////////////////////////////////////

static uint32_t console_output( uint32_t index, uint8_t * text, uint32_t size )
{
    uint8_t rx_byte;
    
    rx_byte = *( ( uint8_t * )text );
    
    if( ( size == sizeof( rx_byte ) ) && ( rx_byte == OBD_MESSAGE_ACK ) )
    {
        send_obd = TRUE;
    }
    return size;
}

static uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t cnt;
    uint32_t val;
    
    uint16_t temp_val;
	uint32_t odometer_cnt = (2844 * 8510 );
    
    // if( timer_Check( &send_timer ) )
    if( send_obd == TRUE )
    {
        // timer_Reload( &send_timer );
        send_obd = FALSE;
        
        obd_resp[0] = 0xF8;
    	obd_resp[1] = ( uint8_t )obd_speed;
        
    	temp_val = ( uint16_t )obd_temp_coolant + 40;
    	if( temp_val > 255 ) temp_val = 255;
        
        memcpy( &obd_resp[2], &obd_rpm, sizeof( uint16_t ) );
        memcpy( &obd_resp[4], &odometer_cnt, sizeof( uint32_t ) );
        memcpy( &obd_resp[8], &obd_mask, sizeof( uint16_t ) );
        memcpy( &obd_resp[10], &temp_val, sizeof( uint8_t ) );
        
        obd_resp[11] = 0xA8;
        
        //sprintk( obd_resp, "obd_send %d,%d,%d,%d%c%c", obd_rpm, obd_speed, obd_temp_coolant, obd_mask, 0x0D, 0x0A );
        p_resp = obd_resp;
        resp_index = 0;
    }
    
    if( timer_Check( &update_timer ) )
    {
#if 1
        val = rand_get_next( &obd_seed ) & 0xFFF;
        obd_rpm = 800 + ( int )val;
        
        val = rand_get_next( &obd_seed ) & 0x07F;
        obd_speed = 1 + ( int )val;
        
        val = rand_get_next( &obd_seed ) & 0x03F;
        obd_temp_coolant = 30 + ( int )val;
        timer_Reload( &update_timer );

#else
        
        obd_rpm = 4000;
        obd_speed = 40;
        obd_temp_coolant = 96;
#endif
        //if( obd_temp_coolant < 100 ) obd_temp_coolant += 5;
    }
    
    cnt = 0;
    
    if( p_resp == NULL ) return 0;
    if( buffer == NULL ) return ( uint32_t )( 12 - resp_index );
    
    while( size-- )
    {
        *buffer = ( uint8_t )p_resp[resp_index++];
        buffer++;
        cnt++;
        
        if( resp_index >= 12 ) p_resp = NULL;
    }
    
    return cnt;
}

static void console_drv_init( uint32_t index )
{
    obd_rpm = 0;
    obd_speed = 0;
    obd_temp_coolant = 0;
    obd_mask = 2+4+8+16+(1<<WARNING_POWERDOWN);
    
    //obd_mask |= ( ( 1 << WARNING_MAX ) - 1 );
    send_obd = TRUE;
    
    rand_get_seed( &obd_seed );
    
    timer_Start( &send_timer, 300 );
    timer_Start( &update_timer, 2000 );
}

static void console_drv_close( uint32_t index )
{
}

static bool_t validate( uint32_t index )
{
    if( index == 18 ) return TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

static const device_data_t gem_tty_device =
{
    "tty*",
    &_in_use,
    
    console_drv_init,
    console_drv_close,
    NULL,
    validate,
    NULL,
    NULL,
    NULL,
    
    DEV_MODE_CHANNEL,
    
    console_input,
    console_output,
    
};

DECLARE_DEVICE_SECTION( gem_tty_device );

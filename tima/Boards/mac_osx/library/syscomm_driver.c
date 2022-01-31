#include "system.h"
#include "device.h"
#include "timer.h"
#include "random.h"
#include "tima_libc.h"
#include "types.h"

#ifdef DEBUG_LOG_FILE
#include "vm_debug.h"
#endif

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

static timer_data_t update_odometer_ms;
static timer_data_t ready_to_send_ms;
static timer_data_t poweroff_timer;

static bool_t send_resp;
static uint8_t resp_buffer[40];

static uint8_t * p_buffer;
static uint32_t p_size;

static uint32_t odometer;
static uint32_t gem_bitmask;

static uint8_t nvram[128];

///////////////////////////////////////////////////////////////////////////

static uint8_t syscomm_checksum( uint8_t * buffer, uint32_t size )
{
    uint8_t ret = 0;
    uint32_t cnt;
    
    for( cnt = 0; cnt < size; cnt++ )
    {
        ret += buffer[cnt];
    }
    
    return ret;
}

static uint32_t console_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
    //uint32_t odometer;
    //if( !timer_Check( &ready_to_send_ms ) ) return size;
    
    if( buffer[0] == 0x9F )
    {
        // powerup
        p_buffer = resp_buffer;
        p_size = 2;
        
        p_buffer[0] = 0x1F;
        p_buffer[1] = 0x9F;
    }
#if 1
    else if( buffer[0] == 0x31 )
    {
        // nvram read
        resp_buffer[0] = 0xb1;
        resp_buffer[1] = (uint8_t)buffer[2] + 1;
        memcpy( &resp_buffer[2], &nvram[buffer[1]], buffer[2] );
        resp_buffer[2+buffer[2]] = syscomm_checksum( &resp_buffer[2], buffer[2] );
        p_buffer = resp_buffer;
        p_size = 3+buffer[2];
    }
    else if( buffer[0] == 0x44 )
    {
        // nvram write
        memcpy( &nvram[buffer[1]], &resp_buffer[2], buffer[2] );
 
        resp_buffer[0] = 0xC4;
        resp_buffer[1] = 0x44;
        p_size = 2;
    }
    else if( buffer[0] == 0x08 )
    {
        // odometer read
        p_buffer = resp_buffer;
        p_size = 6;

        p_buffer[0] = 0x88;
        p_buffer[1] = 4;
        memcpy( &p_buffer[2], &odometer, 4 );
    }
    else if( buffer[0] == 0x1E )
    {
        // bitmask read
        p_buffer = resp_buffer;
        p_size = 6;
        
        p_buffer[0] = 0x9E;
        p_buffer[1] = 4;
        memcpy( &p_buffer[2], &gem_bitmask, 4 );
    }
    else if( buffer[0] == 0x12 )
    {
        // status send
        p_buffer = resp_buffer;
        p_size = 2;
        
        p_buffer[0] = 0x92;
        p_buffer[1] = 0x12;
    }
#endif
    
    return ( uint32_t )size;
}

static uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t cnt;
    
    if( p_buffer != NULL )
    {
        if( size == 0 ) return p_size;
        
        cnt = 0;
        
        while( size )
        {
            *buffer = *p_buffer;
            size--;
            buffer++;
            p_buffer++;
            p_size--;
            cnt++;
        }
        return cnt;
    }
    return 0;
}

static void console_drv_init( uint32_t index )
{
}

static void console_drv_close( uint32_t index )
{
}

static void console_drv_trig_tx( uint32_t index )
{
}

static bool_t validate( uint32_t index )
{
    if( index == 18 ) return TRUE;
    return FALSE;
}

static void syscomm_simulator_process( void )
{
    if( timer_Check( &update_odometer_ms ) )
    {
        timer_Reload( &update_odometer_ms );
        odometer += 100;
    }

    if( timer_Check( &poweroff_timer ) )
    {
        timer_Stop( &poweroff_timer );
        //gem_bitmask = 0;
    }
}

void syscomm_simulator_init( void )
{
    uint32_t value;
    
    p_buffer = NULL;
    p_size = 0;
    
    gem_bitmask = ( 1 << 11 );
    
    odometer = 5 * 2844;
    //odometer = 0;
    send_resp = FALSE;
    
    timer_Start( &update_odometer_ms, 500 );
    timer_Start( &ready_to_send_ms, 8000 );
    timer_Start( &poweroff_timer, 15000 );
    
    value = 2 * 2844; // 2844 * 8700;
    memcpy( &nvram[0x08], &value, sizeof( value ) );
    memset( &nvram[0x08+4], 0x00, sizeof( uint32_t ) );
    memset( &nvram[0x08+8], 0x00, sizeof( uint32_t ) );
    
    value = 0x00000000;
    memcpy( &nvram[0x18], &value, sizeof( value ) );
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

static const device_data_t console_tty_device =
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

DECLARE_INIT_SECTION( syscomm_simulator_init );
DECLARE_PROCESS_SECTION( syscomm_simulator_process );
DECLARE_DEVICE_SECTION( console_tty_device );

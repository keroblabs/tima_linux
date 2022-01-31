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

//static const char response_pid[] = { 'S','E','A','R','C','H','I','N','G','.','.','.',0x0d,
//                                     'U','N','A','B','L','E',' ','T','O',' ','C','O','N','N','E','C','T',0x0d,0x0d,'>',0x00 };

//static const char response_cmd[] = { 'O','K',0x0d,'>',0x00 };

static const char elm317_init[] =
{
    0x0d,0x0d,'E','L','M','3','2','7',' ','V','1','.','3','a',0x00
};

static const char response_echo_ok[] =
{
    'a','t','e','0',0x0d,'O','K',0x00
};

static const char response_ok[] =
{
    'O','K',0x00
};

static char response_all[30];

static char * p_resp;

static int resp_index;

static bool_t echo_state;

static int obd_rpm;
static int obd_speed;
static int obd_temp_coolant;

static bool_t is_start;

//static device_t * obd_dev;
static timer_data_t update_timer;

static int64_t obd_seed;

///////////////////////////////////////////////////////////////////////////

static void obd_simulator_send( const char * resp )
{
    char new_line[50];
    strcpy( new_line, resp );
    strcat( new_line, "\r\r>" );
    
    strcpy( response_all, new_line );
    
    p_resp = response_all;
    resp_index = 0;
}

static void obd_simulator_start( void )
{
    rand_get_seed( &obd_seed );
    
    obd_rpm = 0;
    obd_speed = 0;
    obd_temp_coolant = 0;
    
    echo_state = TRUE;
    
    timer_Start( &update_timer, 2000 );
    
    is_start = FALSE;
    
    strcpy( response_all, elm317_init );
    strcat( response_all, "\r>" );
    p_resp = response_all;
    resp_index = 0;
}

static uint32_t console_output( uint32_t index, uint8_t * text, uint32_t size )
{
    char command[10];
    char output[50];
    int val;
    
    strcpy( command, ( char * )text );
    command[4] = 0;
    
    if( !strcmp( command, "010c" ) )
    {
        obd_simulator_send("41 0C 00 00");
        val = obd_rpm << 2;
        sprintk( output, "41 0c %02x %02x", ( val >> 8 ), ( val & 0x0FF ) );
        obd_simulator_send( output );
        
    }
    else if( !strcmp( command, "0110" ) )
    {
        obd_simulator_send("41 10 00 00");
    }
    else if( !strcmp( command, "010d" ) )
    {
        val = obd_speed;
        sprintk( output, "41 0d %02x", ( val & 0x0FF ) );
        obd_simulator_send( output );
    }
    else if( !strcmp( command, "0105" ) )
    {
        val = obd_temp_coolant + 40;
        sprintk( output, "41 05 %02X", ( val & 0x0FF ) );
        obd_simulator_send( output );
    }
    else if( !strcmp( command, "0104" ) )
    {
        obd_simulator_send("41 04 00");
    }
    else if( !strcmp( command, "010f" ) )
    {
        obd_simulator_send("41 0F 33");
    }
    else if( !strcmp( command, "ate0" ) )
    {
        if( echo_state )
        {
            echo_state = FALSE;
            obd_simulator_send(response_echo_ok);
        }
        else
        {
            obd_simulator_send(response_ok);
        }
    }
    else
    {
        obd_simulator_send( "NO DATA" );
    }
    
    return ( uint32_t )strlen( p_resp );
}

static uint32_t console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    uint32_t cnt;
    
    cnt = 0;
    
    if( p_resp == NULL ) return 0;
    if( buffer == NULL ) return ( uint32_t )strlen( &p_resp[resp_index] );
    
    while( size-- )
    {
        *buffer = ( uint8_t )p_resp[resp_index++];
        cnt++;
        
        if( resp_index >= strlen( p_resp ) )
        {
            p_resp = NULL;
            break;
        }
    }
    
    return cnt;
}

static void console_drv_init( uint32_t index )
{
    echo_state = TRUE;
    obd_simulator_start();
}

static void console_drv_close( uint32_t index )
{
}

static void console_drv_trig_tx( uint32_t index )
{
}

static bool_t validate( uint32_t index )
{
    if( index == 3 ) return TRUE;
    return FALSE;
}

void elm327_simulator_process( void )
{
    uint32_t val;

    if( timer_Check( &update_timer ) )
    {
        val = rand_get_next( &obd_seed ) & 0xFFF;
        obd_rpm = 800 + ( int )val;
        DEBUG_PRINTK( "RPM = %d\r\n", obd_rpm );
        
        val = rand_get_next( &obd_seed ) & 0x07F;
        obd_speed = 5 + ( int )val;
        
        val = rand_get_next( &obd_seed ) & 0x03F;
        obd_temp_coolant = 30 + ( int )val;
        
        timer_Reload( &update_timer );
        //if( obd_temp_coolant < 100 ) obd_temp_coolant += 5;
    }
    
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

DECLARE_PROCESS_SECTION( elm327_simulator_process );
DECLARE_DEVICE_SECTION( console_tty_device );

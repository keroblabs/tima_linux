#include "system.h"
#include "device.h"
#include "types.h"
#include "socket_library.h"
#include "SDL_internal.h"

///////////////////////////////////////////////////////////////////////////

#define CONSOLE_THREAD_STACK_SIZE       1024
#define CONSOLE_BUFFER_SIZE             256

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

static uint32_t net_console_output( uint32_t index, uint8_t * text, uint32_t size )
{
    DI();
    instance_data_t * data = sdl_get_current_instance();
    if( data != NULL )
    {
        socket_write_data( data->socket_printf, text, size );
    }
    EI();
    
    return size;
}

static uint32_t net_console_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
    return 0;
}

static void net_console_drv_init( uint32_t index )
{
    uint8_t ip_addr[] = { 127, 0, 0, 1 };
    instance_data_t * data = sdl_get_current_instance();
    if( data != NULL )
    {
        printf( "net printf %d\r\n", data->printf_port );
        data->socket_printf = socket_connect_addr( ip_addr, data->printf_port );
    }
}

static void net_console_drv_close( uint32_t index )
{
}

static uint32_t net_console_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
    if( param == DEVICE_SET_CONFIG_DATA )
    {
    }
    
    return 0;
}

//static void console_drv_trig_tx( uint32_t index )
//{
//}

static bool_t net_validate( uint32_t index )
{
    if( index == 3 ) return TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

static const device_data_t socket_tty_device =
{
    "tty*",
    &_in_use,
    
    net_console_drv_init,
    net_console_drv_close,
    NULL,
    net_validate,
    NULL,
    net_console_drv_ioctl,
    NULL,
    
    DEV_MODE_CHANNEL,
    
    net_console_input,
    net_console_output,
    
};

DECLARE_DEVICE_SECTION( socket_tty_device );

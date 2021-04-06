#include "SDL_internal.h"
#include "device.h"
#include "system.h"
#include "mac.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static void cpu_send_frame_trigger( void * p_pipe )
{
    int cnt;

    instance_data_t * curr_instance = sdl_get_current_instance();
    if( curr_instance == NULL ) return;

    uint8_t * frame;
    uint16_t size;

    pipe_data_t * pipe = ( pipe_data_t * )p_pipe;
    frame = pipe_read( pipe, &size );
    curr_instance->last_tx_good = FALSE;

    if( curr_instance->current_channel == 0 )
    {
        curr_instance->failed_frame = frame;
        return;
    }

    for( cnt = 0; cnt < MAX_INSTANCES; cnt++ )
    {
        instance_data_t * instance = sdl_get_instance_from_index( cnt );
        if( instance != NULL )
        {
            if( ( instance->current_channel != 0 ) && ( instance->current_channel == curr_instance->current_channel ) && ( instance->id != curr_instance->id ) )
            {
                pipe_send_buffer( &instance->send_pipe, frame, size );

                curr_instance->last_tx_good = TRUE;
            }
        }
    }
}

static void mac_drv_init( uint32_t index )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return;
    
    pipe_init( &instance->send_pipe, "MAC_TX_PIPE", 16 );
    pipe_init( &instance->receive_pipe, "MAC_RX_PIPE", 16 );

    pipe_set_tx_trigger( &instance->send_pipe, cpu_send_frame_trigger );
    pipe_set_tx_trigger( &instance->receive_pipe, cpu_send_frame_trigger );
}

static void mac_drv_close( uint32_t index )
{
}

static pipe_data_t * mac_get_rx_pipe( uint32_t index )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return NULL;
    
    return &instance->send_pipe;
}

static pipe_data_t * mac_get_tx_pipe( uint32_t index )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return NULL;

    return &instance->receive_pipe;
}

///////////////////////////////////////////////////////////////////////////

static void set_channel( uint8_t channel )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL )
    {
        instance->is_listening = TRUE;
        instance->current_channel = channel;
    }
}

static void set_power( uint16_t power )
{
}

static uint8_t get_channel( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL )
    {
        return instance->current_channel;
    }
    
    return 0;
}

static bool_t is_tx_success( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL ) return instance->last_tx_good;
    return FALSE;
}

static bool_t is_tx_completed( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    bool_t ret = FALSE;
    
    if( instance != NULL )
    {
        ret = instance->tx_completed;
        instance->tx_completed = FALSE;
    }
    return ret;
}

static bool_t is_listening( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    bool_t ret = FALSE;
    
    if( instance != NULL )
    {
        ret = instance->is_listening;
        instance->is_listening = FALSE;
    }
    return ret;
}

static void * get_failed_frame( void )
{
    void * ret = NULL;
    
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL )
    {
        ret = instance->failed_frame;
        instance->failed_frame = NULL;
    }
    
    return ret;
}

static const mac_driver_t mac_driver =
{
    set_channel,
    set_power,
    is_tx_success,
    is_tx_completed,
    is_listening,
    get_channel,
    get_failed_frame,
};

static uint32_t mac_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
    mac_driver_t ** p_api = ( mac_driver_t ** )value;
    if( param == DEVICE_GET_API ) *p_api = ( mac_driver_t * )&mac_driver;
    return 0;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const device_data_t mac_device =
{
    "mac",
    &_in_use,
    
    mac_drv_init,
    mac_drv_close,
    NULL,
    NULL,
    NULL,
    mac_drv_ioctl,
    NULL,
    
    DEV_MODE_PIPE,
    
    mac_get_rx_pipe, // can_read_buffer,
    mac_get_tx_pipe, // can_write_buffer,
    
};

DECLARE_DEVICE_SECTION( mac_device );

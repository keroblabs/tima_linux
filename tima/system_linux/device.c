#include "device.h"
#include "system.h"
#include "tima_libc.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef uint32_t ( *dev_channel_mode_t )( uint32_t index, uint8_t * data, uint32_t size );
typedef uint8_t * ( *dev_pipe_mode_t )( uint32_t index, uint32_t * size );
typedef int ( *dev_byte_mode_t )( uint32_t index, uint8_t data );

////////////////////////////////////////////////////////////////////////////////////////

#define DEVICE_WITH_PARAM       NEG_U32
#define DEVICE_WITH_INDEX       255

////////////////////////////////////////////////////////////////////////////////////////

uint32_t device_ioctrl( device_t * dev, uint32_t param, void * data )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    
    if( dev_data == NULL ) return 0;
    if( dev_data->io_ctrl != NULL ) return dev_data->io_ctrl( dev_offset, param, data );
    
    return 0;
}

uint32_t device_is_rx_pending( device_t * dev )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    //buffer_data_t * rx_buffer;

    if( dev_data == NULL ) return 0;

	if( dev_data->dev_mode == DEV_MODE_CHANNEL )
    {
        // try receive with null buffer
        dev_channel_mode_t dev_channel = ( dev_channel_mode_t )dev_data->rx_channel;
        if( dev_channel != NULL )
            return dev_channel( dev_offset, NULL, 0 );
    }

    return 0;
}

uint32_t device_is_tx_pending( device_t * dev )
{
#if 0
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    //buffer_data_t * tx_buffer;
    //dev_buffer_mode_t dev_buffer;

    if( dev_data == NULL ) return 0;

	/*
    if( dev_data->dev_mode == DEV_MODE_BUFFER )
    {
        // use buffer information
        dev_buffer = ( dev_buffer_mode_t )dev_data->tx_channel;
        tx_buffer = dev_buffer( dev_offset );
        return buffer_get_available_size( tx_buffer );
    }
	*/
#endif
    return 0;
}

uint32_t device_write_buffer( device_t * dev, uint8_t * data, uint32_t size )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    uint16_t counter;

    if( dev_data == NULL ) return 0;

    if( dev_data->tx_channel == NULL ) return 0;

	if( dev_data->dev_mode == DEV_MODE_CHANNEL )
    {
        dev_channel_mode_t dev_channel = ( dev_channel_mode_t )dev_data->tx_channel;
        if( dev_channel == NULL ) return 0;
        return dev_channel( dev_offset, data, size );
    }
    else if( dev_data->dev_mode == DEV_MODE_BYTE )
    {
        dev_byte_mode_t dev_byte = ( dev_byte_mode_t )dev_data->tx_channel;

        for( counter = 0; counter < size; counter++ )
        {
            dev_byte( dev_offset, data[ counter ] );
        }
        
        return size;
    }
    
    return 0;
}

void device_write( device_t * dev, uint8_t data )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    dev_byte_mode_t dev_byte;
    
    if( dev_data->dev_mode == DEV_MODE_BYTE )
    {
        dev_byte = ( dev_byte_mode_t )dev_data->tx_channel;
        dev_byte( dev_offset, data );
    }
    else
    {
    	device_write_buffer( dev, &data, 1 );
    }
}

uint32_t device_read_buffer( device_t * dev, uint8_t * data, uint32_t size )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    uint16_t counter;

    if( dev_data == NULL ) return 0;

    if( dev_data->rx_channel == NULL ) return 0;

	if( dev_data->dev_mode == DEV_MODE_CHANNEL )
    {
        dev_channel_mode_t dev_channel = ( dev_channel_mode_t )dev_data->rx_channel;
        if( dev_channel == NULL ) return 0;
        
        return dev_channel( dev_offset, data, size );
    }
    else if( dev_data->dev_mode == DEV_MODE_BYTE )
    {
        dev_byte_mode_t dev_byte = ( dev_byte_mode_t )dev_data->rx_channel;
        int ret_byte;

        for( counter = 0; counter < size; counter++ )
        {
            ret_byte = dev_byte( dev_offset, 0 );
            if( ret_byte == -1 ) return counter;

            data[ counter ] = ( uint8_t )( ret_byte & 0x0FF );
        }
    }

    return 0;
}

uint8_t device_read( device_t * dev )
{
    uint8_t data = 0;
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    dev_byte_mode_t dev_byte;
    int ret_byte;
    
    if( dev_data->dev_mode == DEV_MODE_BYTE )
    {
        dev_byte = ( dev_byte_mode_t )dev_data->rx_channel;

        ret_byte = dev_byte( dev_offset, 0 );
        if( ret_byte == -1 ) data = 0;

        data = ( uint8_t )( ret_byte & 0x0FF );
    }
    else
    {
        device_read_buffer( dev, &data, 1 );
    }
    
    return data;
}

void device_close( device_t * dev )
{
    uint32_t dev_offset = dev->device_index;
    device_data_t * dev_data = dev->device_ptr;
    
    if( dev_data == NULL ) return;
    //if( dev_data->disable == NULL ) return;
    
    if( dev_data->in_use != NULL ) *dev_data->in_use = FALSE;

    if( dev_data->disable != NULL ) dev_data->disable( dev_offset );
	free( dev );
}

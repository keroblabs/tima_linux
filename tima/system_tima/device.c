#include "device.h"
#include "system.h"
#include "tima_libc.h"
#include "debug.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef uint32_t ( *dev_channel_mode_t )( uint32_t index, uint8_t * data, uint32_t size );
typedef uint8_t * ( *dev_pipe_mode_t )( uint32_t index, uint32_t * size );
typedef int ( *dev_byte_mode_t )( uint32_t index, uint8_t data );

device_data_t * _device_search( const char * name, uint32_t * index );

////////////////////////////////////////////////////////////////////////////////////////

#define DEVICE_WITH_PARAM       NEG_U32
#define DEVICE_WITH_INDEX       255

////////////////////////////////////////////////////////////////////////////////////////

static char dev_name_temp[ 128 ];

//////////////////////////////////////////////////////////////////

static const char device_disc_name[ 8 ] = "/dev";

///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

device_data_t * _device_search( const char * name, uint32_t * index )
{
    device_data_t * search_dev;
    uint32_t counter = 0;
    uint32_t len_cmp;
    uint32_t index_32 = 0;
    char * dev_pointer;
	int ret_cmp;
    int ret_index;
    
    if( strncmp( name, device_disc_name, strlen( device_disc_name ) ) ) return NULL;

    while( TRUE )
    {
        search_dev = ( device_data_t * )system_Get_Device_Driver(counter);
        if( search_dev == NULL ) break;
        
        strcpy( dev_name_temp, device_disc_name );
		strcat( dev_name_temp, "/" );
        strcat( dev_name_temp, search_dev->name );

		ret_cmp = 1;
        
        // drive with index
        dev_pointer = strchr( dev_name_temp, '*' );
        if( dev_pointer != NULL )
        {
			len_cmp = ( uint32_t )strlen( dev_name_temp );

			if( ( strlen( name ) >= len_cmp ) && !strncmp( name, dev_name_temp, len_cmp - 1 ) )
			{
	            index_32 = ( uint32_t )tima_atoi( &name[ len_cmp - 1 ] );
				ret_cmp = 0;			
			}
        }
        else
        {
            dev_pointer = strchr( dev_name_temp, '?' );
            if( dev_pointer != NULL )
            {            
                // device with param is like:
                // socket?192.168.0.1:80
                // parameter is everything after '?'
                len_cmp = ( uint32_t )strlen( dev_name_temp );

                if( ( strlen( name ) >= len_cmp ) && !strncmp( name, dev_name_temp, len_cmp - 1 ) )
                {
                    index_32 = DEVICE_WITH_PARAM;
                    dev_pointer = ( char * )&name[ len_cmp-1 ];
                    ret_cmp = 0;			
                }
            }
            else
            {
                ret_cmp = strcmp( name, dev_name_temp );
            }
        }

        if( !ret_cmp )
        {
            if( index != NULL ) *index = index_32;
            
            if( dev_pointer == NULL ) return search_dev;

            if( ( search_dev->validate != NULL ) && ( search_dev->validate( index_32 ) == TRUE ) )
            {
                return search_dev;
            }
            else if( index_32 == DEVICE_WITH_PARAM )
            {
                // extract the parameter from the device name
                // the index returned is the index of opened device
                if( index == NULL ) return NULL;
                ret_index = search_dev->get_index( dev_pointer );
                if( ret_index == -1 ) return NULL;
                *index = ( uint32_t )ret_index;
                return search_dev;
            }
        }
        
        counter++;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////

bool_t device_open_ex( const char * name, device_t * dev )
{
    device_data_t * dev_data;
    uint32_t index;

	if( dev == NULL ) return FALSE;

	// search for device
    dev_data = _device_search( name, &index );
	
    if( dev_data == NULL ) return FALSE;
	if( ( dev_data->is_open != NULL ) && ( dev_data->is_open( index ) == FALSE ) ) return FALSE;

    dev->device_ptr = NULL;
    
    // check if it's opened
    if( dev_data->in_use != NULL )
    {
        //if( *dev_data->in_use == TRUE ) return FALSE;
        *dev_data->in_use = TRUE;
    }

    if( dev_data->init != NULL ) dev_data->init( index );
    
    dev->device_ptr = dev_data;
    dev->device_index = index;

    DEBUG_PRINTK( "Open %s (0x%08x, %d)\r\n", name, (int)dev, sys_heap_used() );

    return TRUE;
}

device_t * device_open( const char * name )
{
	device_t * dev;

	dev = ( device_t * )MMALLOC( sizeof( device_t ) );
	if( dev == NULL ) return NULL;

	if( device_open_ex( name, dev ) == FALSE )
	{
		MFREE( dev );
		return NULL;
	}

    return dev;
}

device_t * device_socket_open( uint8_t * ip_addr, uint16_t port )
{
	device_t * dev;
	char dev_str[40];

	dev = ( device_t * )MMALLOC( sizeof( device_t ) );
	if( dev == NULL ) return NULL;

	sprintk( dev_str, "/dev/socket?%d.%d.%d.%d:%d", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port );
	if( device_open_ex( dev_str, dev ) == FALSE )
	{
		MFREE( dev );
		return NULL;
	}

	return dev;
}


device_t * device_socket_open_url( char * url_addr, uint16_t port )
{
    device_t * dev;
    static char dev_str[128];
    
    dev = ( device_t * )MMALLOC( sizeof( device_t ) );
    if( dev == NULL ) return NULL;
    
    sprintk( dev_str, "/dev/socket?%s:%d", url_addr, port );
    if( device_open_ex( dev_str, dev ) == FALSE )
    {
        MFREE( dev );
        return NULL;
    }
    
    return dev;
}

device_t * device_socket_listen( uint16_t port )
{
	device_t * dev;
	char dev_str[40];

	dev = ( device_t * )MMALLOC( sizeof( device_t ) );
	if( dev == NULL ) return NULL;

	sprintk( dev_str, "/dev/socket?listen:%d", port );
	if( device_open_ex( dev_str, dev ) == FALSE )
	{
		MFREE( dev );
		return NULL;
	}

	return dev;
}

device_t * device_socket_accept( device_t * dev )
{
	device_t * ret;
	uint32_t socket;

	socket = SOCKET_NOT_READY;
	device_ioctrl( dev, DEVICE_GET_RUNTIME_VALUE+1, &socket );

    if( socket == SOCKET_FAIL_LISTEN )
    {
        // listening failed, exit
        return NULL;
    }
    else if( socket != SOCKET_NOT_READY )
    {
        // listen accepted
		ret = ( device_t * )MMALLOC( sizeof( device_t ) );
		if( ret == NULL )
		{
			device_ioctrl( dev, DEVICE_SET_RUNTIME_VALUE, &socket );
			return NULL;
		}

		ret->device_index = socket;
		ret->device_ptr = dev->device_ptr;

        return ret;
    }    

	return NULL;
}

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
    
    DEBUG_PRINTK( "Close (0x%08x, %d)\r\n", (int)dev, sys_heap_used() );

    if( dev_data->in_use != NULL ) *dev_data->in_use = FALSE;

    if( dev_data->disable != NULL ) dev_data->disable( dev_offset );
	MFREE( dev );
}

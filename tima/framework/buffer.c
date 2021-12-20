#include "system.h"
#include "buffer.h"

////////////////////////////////////////////////////////////////////////////////////////

void _buffer_write_internal( buffer_data_t * buffer_data, uint8_t in_data )
{
    if( buffer_data == NULL ) return;
    if( buffer_data->buffer == NULL ) return;
    
    tthread_mutex_lock( buffer_data->mutex );
    
    // insert data into the buffer
    buffer_data->buffer[ buffer_data->pointer_in ] = in_data;
    buffer_data->pointer_in++;
    
    // update pointers and control overflow
    if( buffer_data->pointer_in == buffer_data->size ) buffer_data->pointer_in = 0;
    if( buffer_data->pointer_in == buffer_data->pointer_out ) buffer_data->pointer_out++;
    if( buffer_data->pointer_out == buffer_data->size ) buffer_data->pointer_out = 0;
    
    tthread_mutex_unlock( buffer_data->mutex );
}

////////////////////////////////////////////////////////////////////////////////////////

void buffer_init( buffer_data_t * buffer_data, uint32_t size )
{
    // init buffer
    buffer_data->buffer = ( uint8_t * )MMALLOC( size );
    if( buffer_data->buffer == NULL ) return;
    
    buffer_data->is_static = FALSE;
    buffer_data->size = size;
    buffer_data->pointer_in = 0;
    buffer_data->pointer_out = 0;
    buffer_data->mutex = tthread_mutex_init();
    buffer_data->cond = tthread_condition_create();
}

void buffer_init_static( buffer_data_t * buffer_data, uint8_t * buffer, uint32_t size )
{
    // init buffer
    buffer_data->buffer = buffer;
    buffer_data->is_static = TRUE;
    buffer_data->size = size;
    buffer_data->pointer_in = 0;
    buffer_data->pointer_out = 0;
    buffer_data->mutex = tthread_mutex_init();
    buffer_data->cond = tthread_condition_create();
}

void buffer_reset( buffer_data_t * buffer_data )
{
	if( buffer_data == NULL ) return;
    if( buffer_data->buffer == NULL ) return;
    
    tthread_mutex_lock( buffer_data->mutex );
    buffer_data->pointer_in = 0;
    buffer_data->pointer_out = 0;
    tthread_mutex_unlock( buffer_data->mutex );
}

void buffer_destroy( buffer_data_t * buffer_data )
{
    if( buffer_data == NULL ) return;
    if( buffer_data->buffer == NULL ) return;

    if( buffer_data->is_static == FALSE )
        MFREE( buffer_data->buffer );
}

////////////////////////////////////////////////////////////////////////////////

uint8_t buffer_read( buffer_data_t * buffer_data )
{
	uint8_t ret_value = 0;

	if( buffer_data == NULL ) return 0;
    if( buffer_data->buffer == NULL ) return 0;
    
    tthread_mutex_lock( buffer_data->mutex );
 
    // buffer is empty
	if( buffer_data->pointer_in == buffer_data->pointer_out )
    {
        tthread_mutex_unlock( buffer_data->mutex );
        return( 0 );
    }

    // get byte from buffer
	ret_value = buffer_data->buffer[ buffer_data->pointer_out ];

    // move out-pointer
	buffer_data->pointer_out++;
	if( buffer_data->pointer_out == buffer_data->size ) buffer_data->pointer_out = 0;
    
    tthread_mutex_unlock( buffer_data->mutex );
    
	return( ret_value );
}

void buffer_write( buffer_data_t * buffer_data, uint8_t in_data )
{	
	if( buffer_data == NULL ) return;
    if( buffer_data->buffer == NULL ) return;
    
    _buffer_write_internal( buffer_data, in_data );
    
    tthread_condition_signal( buffer_data->cond );
}

void buffer_write_buffer( buffer_data_t * buffer_data, uint8_t * in_data, uint32_t size )
{
	uint16_t counter;
	
	for( counter = 0; counter < size; counter++ )
	{
		_buffer_write_internal( buffer_data, in_data[ counter ] );
	}
 
    tthread_condition_signal( buffer_data->cond );
}

uint32_t buffer_read_buffer( buffer_data_t * buffer_data, uint8_t * out_data, uint32_t size )
{
	uint16_t counter;
	
	for( counter = 0; counter < size; counter++ )
	{
		// buffer is empty
		if( buffer_data->pointer_in == buffer_data->pointer_out ) break;
	
		out_data[ counter ] = buffer_read( buffer_data );
	}

	return counter;
}

uint32_t buffer_get_size( buffer_data_t * buffer_data )
{
    uint16_t size;

	if( buffer_data == NULL ) return 0;
    if( buffer_data->buffer == NULL ) return 0;
    
    tthread_mutex_lock( buffer_data->mutex );
    
    if( buffer_data->pointer_in >= buffer_data->pointer_out )
    {
        // in and out at same side
        size = buffer_data->pointer_in - buffer_data->pointer_out;
    }
    else
    {
        // in turned around
        size = ( buffer_data->size - buffer_data->pointer_out ) + buffer_data->pointer_in;
    }

    tthread_mutex_unlock( buffer_data->mutex );
    
    return( size );
}

uint32_t buffer_get_available_size( buffer_data_t * buffer_data )
{
    uint32_t ret;
    
    if( buffer_data == NULL ) return 0;
    if( buffer_data->buffer == NULL ) return 0;
    
    tthread_mutex_lock( buffer_data->mutex );
    ret = buffer_data->size - buffer_get_size( buffer_data );
    tthread_mutex_unlock( buffer_data->mutex );
    
    return ret;
}

bool_t buffer_is_full( buffer_data_t * buffer_data )
{        
    bool_t ret = FALSE;
    
    if( buffer_data == NULL ) return FALSE;
    if( buffer_data->buffer == NULL ) return FALSE;
    
    tthread_mutex_lock( buffer_data->mutex );
    
    // input is just before output
	if( buffer_data->pointer_in == ( buffer_data->pointer_out - 1 ) ) ret = TRUE;

    // input is in the tail, and output is in the head
	else if( ( buffer_data->pointer_in == ( buffer_data->size - 1 ) ) &&
             ( buffer_data->pointer_out == 0 ) ) ret = TRUE;

    tthread_mutex_unlock( buffer_data->mutex );

    return ret;
}

bool_t buffer_is_empty( buffer_data_t * buffer_data )
{
    bool_t ret = FALSE;
    
    if( buffer_data == NULL ) return TRUE;
    if( buffer_data->buffer == NULL ) return TRUE;

    tthread_mutex_lock( buffer_data->mutex );
	if( buffer_data->pointer_in == buffer_data->pointer_out ) ret = TRUE;
    tthread_mutex_unlock( buffer_data->mutex );
    
    return ret;
}

uint32_t buffer_wait_for_data( buffer_data_t * buffer_data, uint8_t * buffer, uint32_t size, uint32_t timeout )
{
    if( buffer_data == NULL ) return 0;
    if( buffer_data->buffer == NULL ) return 0;
    
    if( buffer_is_empty( buffer_data ) )
    {
        tthread_condition_wait_timeout( buffer_data->cond, timeout );
    }

    return buffer_read_buffer( buffer_data, buffer, size );
}

uint32_t buffer_dump( buffer_data_t * buffer_data, uint8_t * output, uint32_t max_size )
{
    uint8_t ret_value = 0;
    uint32_t pointer_out;
    uint32_t index_out = 0;

    if( buffer_data == NULL ) return 0;
    if( buffer_data->buffer == NULL ) return 0;

    tthread_mutex_lock( buffer_data->mutex );

    // buffer is empty
    if( buffer_data->pointer_in == buffer_data->pointer_out )
    {
        tthread_mutex_unlock( buffer_data->mutex );
        return( 0 );
    }

    pointer_out = buffer_data->pointer_out;

    while( max_size > index_out )
    {
        // get byte from buffer
        output[ index_out++ ] = buffer_data->buffer[ pointer_out ];

        // move out-pointer
        pointer_out++;
        if( pointer_out == buffer_data->size ) pointer_out = 0;
    }

    tthread_mutex_unlock( buffer_data->mutex );

    return( ret_value );
}

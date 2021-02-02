#include "pipe.h"
#include "tima_libc.h"

#include "t_threads.h"

////////////////////////////////////////////////////////////////////////////////////////

#define PIPE_HEAP_SIZE 8192

#define PIPE_MALLOC     MMALLOC
#define PIPE_FREE       MFREE

////////////////////////////////////////////////////////////////////////////////////////

static pipe_data_t * first_pipe;

////////////////////////////////////////////////////////////////////////////////////////

void pipe_global_init( void )
{
	first_pipe = NULL;
}

uint8_t * pipe_alloc_buffer( uint16_t size )
{
    uint8_t * ptr;

    ptr = ( uint8_t * )PIPE_MALLOC( size );
    return( ptr );
}

void pipe_release_buffer( uint8_t * buffer )
{
    PIPE_FREE( buffer );
}

void pipe_init( pipe_data_t * pipe_data, char * name, uint16_t size )
{
    // erase memory
    memset( pipe_data, 0x00, sizeof( pipe_data_t ) );

	if( size >= MAX_PIPE_SIZE ) size = MAX_PIPE_SIZE - 1;

    // setup pipe
	if( name != NULL )
	{
		strncpy( pipe_data->name, name, MAX_PIPE_NAME_SIZE );
		pipe_data->name[ MAX_PIPE_NAME_SIZE ] = 0;
	}

	pipe_data->mutex = tthread_mutex_init();
	pipe_data->cond = tthread_condition_create();

    pipe_data->max_size = ( uint8_t )size;

    // add to the list
    pipe_data->p_next = first_pipe;
    first_pipe = pipe_data;
}

pipe_data_t * pipe_locate( char * name )
{
    pipe_data_t * local_pipe;

    // get first pipe
    local_pipe = first_pipe;

    // search for the pipe
    while( local_pipe != NULL )
    {
        // found, exit
        if( !strcmp( local_pipe->name, name ) ) return( local_pipe );

        // get next pipe
        local_pipe = local_pipe->p_next;
    }

    return( NULL );
}

uint32_t pipe_get_buffer_size( pipe_data_t * pipe )
{
	uint32_t size = 0;
	
    if( pipe == NULL ) return( 0 );
    
    tthread_mutex_lock( pipe->mutex );

    // buffer is empty
	if( pipe->pointer_in == pipe->pointer_out ) size = 0;
	else size = pipe->pipe_size[ pipe->pointer_out ];

    tthread_mutex_unlock( pipe->mutex );
    
    return size;
}

uint32_t pipe_read_buffer( pipe_data_t * pipe, uint8_t * buffer, uint32_t max_size )
{
	uint16_t size;
    uint8_t * buf_tmp;
	
    if( pipe == NULL ) return( 0 );
    
    tthread_mutex_lock( pipe->mutex );
    
    // buffer is empty
	if( pipe->pointer_in == pipe->pointer_out )
    {
        tthread_mutex_unlock( pipe->mutex );
        return( 0 );
    }

    // get byte from buffer
    buf_tmp = pipe->pipe_list[ pipe->pointer_out ];
	size = pipe->pipe_size[ pipe->pointer_out ];
    if( size > max_size ) size = max_size;
    
	memcpy( buffer, buf_tmp, size );
    pipe_release_buffer( buf_tmp );

    // move out-pointer
	pipe->pointer_out++;
	if( pipe->pointer_out == pipe->max_size ) pipe->pointer_out = 0;

    tthread_mutex_unlock( pipe->mutex );
    
	return( size );
}

uint8_t * pipe_read( pipe_data_t * pipe, uint16_t * size )
{
	uint8_t * ret_value = NULL;

    if( pipe == NULL ) return( NULL );

    tthread_mutex_lock( pipe->mutex );
    
    // buffer is empty
	if( pipe->pointer_in == pipe->pointer_out )
    {
        tthread_mutex_unlock( pipe->mutex );
        return( NULL );
    }

    // get byte from buffer
	ret_value = pipe->pipe_list[ pipe->pointer_out ];
    
    if( size != NULL )
        *size =     pipe->pipe_size[ pipe->pointer_out ];

    // move out-pointer
	pipe->pointer_out++;
	if( pipe->pointer_out == pipe->max_size ) pipe->pointer_out = 0;
    
    tthread_mutex_unlock( pipe->mutex );
    
	return( ret_value );
}

uint8_t * pipe_get( pipe_data_t * pipe, uint16_t * size )
{
    uint8_t * ret_value = NULL;
    
    if( pipe == NULL ) return( NULL );
    
    tthread_mutex_lock( pipe->mutex );
    
    // buffer is empty
    if( pipe->pointer_in == pipe->pointer_out )
    {
        tthread_mutex_unlock( pipe->mutex );
        return( NULL );
    }
    
    // get byte from buffer
    ret_value = pipe->pipe_list[ pipe->pointer_out ];
    
    if( size != NULL )
        *size =     pipe->pipe_size[ pipe->pointer_out ];
    
    tthread_mutex_unlock( pipe->mutex );
    
    return( ret_value );
}

void pipe_send_buffer( pipe_data_t * pipe, uint8_t * buffer, uint16_t size )
{
    uint8_t * buf_tmp = pipe_alloc_buffer( size );
    if( buf_tmp == NULL ) return;
    
    memcpy( buf_tmp, buffer, size );
    pipe_write( pipe, buf_tmp, size );
}

void pipe_write( pipe_data_t * pipe, uint8_t * buffer, uint16_t size )
{
    if( pipe == NULL ) return;

    tthread_mutex_lock( pipe->mutex );
    
    // insert data into the buffer
	pipe->pipe_list[ pipe->pointer_in ] = buffer;
	pipe->pipe_size[ pipe->pointer_in ] = size;
	pipe->pointer_in++;
    
    // update pointers and control overflow
	if( pipe->pointer_in == pipe->max_size ) pipe->pointer_in = 0;

    // overflow, delete buffer
	if( pipe->pointer_in == pipe->pointer_out )
    {
        pipe_release_buffer( pipe->pipe_list[ pipe->pointer_out ] );
        pipe->pointer_out++;
	}
    
	if( pipe->pointer_out == pipe->max_size ) pipe->pointer_out = 0;
    
    tthread_mutex_unlock( pipe->mutex );
    tthread_condition_signal( pipe->cond );
}

uint8_t * pipe_wait_for_data( pipe_data_t * pipe, uint16_t * size )
{
	if( pipe == NULL ) return NULL;

	if( pipe_is_empty( pipe ) == TRUE )
	{
		tthread_condition_wait( pipe->cond );
	}

	return pipe_read( pipe, size );
}

uint8_t * pipe_wait_for_data_ex( pipe_data_t * pipe, uint16_t * size, void * p_data, pipe_data_check_t checker )
{
    if( pipe == NULL ) return NULL;

    while( 1 )
    {
        if( pipe_is_empty( pipe ) == TRUE )
        {
            tthread_condition_wait( pipe->cond );
        }

        uint16_t rx_size = 0;
        uint8_t * rx_buffer = pipe_get( pipe, &rx_size );

        if( ( checker != NULL ) && ( checker( p_data, rx_buffer, rx_size ) == TRUE ) ) break;
    }

    return pipe_read( pipe, size );
}

bool_t pipe_is_full( pipe_data_t * pipe )
{
    bool_t ret = FALSE;
    
    if( pipe == NULL ) return( TRUE );
    
    tthread_mutex_lock( pipe->mutex );
    
    // input is just before output
	if( pipe->pointer_in == ( pipe->pointer_out - 1 ) ) ret = TRUE ;

    // input is in the tail, and output is in the head
	else if( ( pipe->pointer_in == ( pipe->max_size - 1 ) ) &&
             ( pipe->pointer_out == 0 ) ) ret = TRUE;

    tthread_mutex_unlock( pipe->mutex );
    
    // not full
    return( ret );
}

bool_t pipe_is_empty( pipe_data_t * pipe )
{
    bool_t ret = FALSE;
    
    if( pipe == NULL ) return( TRUE );
    
    tthread_mutex_lock( pipe->mutex );
    
	if( pipe->pointer_in == pipe->pointer_out ) ret = TRUE;
    
    tthread_mutex_unlock( pipe->mutex );
    
    return( ret );
}

uint32_t pipe_get_used( pipe_data_t * pipe )
{
    uint32_t size;

    if( pipe == NULL ) return( 0 );
    
    tthread_mutex_lock( pipe->mutex );
    
    if( pipe->pointer_in >= pipe->pointer_out )
    {
        // in and out at same side
        size = pipe->pointer_in - pipe->pointer_out;
    }
    else
    {
        // in turned around
        size = ( ( pipe->max_size - 1 ) - pipe->pointer_out ) + pipe->pointer_in;
    }
    
    tthread_mutex_unlock( pipe->mutex );
    
    return( size );
}


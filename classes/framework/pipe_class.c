#include "pipe_class_private.h"

////////////////////////////////////////////////////////////////////

static void * pipe_read_data( pipe_class_t * p_data, uint32_t * size, bool_t take_it_out )
{
    void * ret_value = NULL;
    
    tthread_mutex_lock( p_data->mutex );
    
    // buffer is empty
    if( p_data->pointer_in == p_data->pointer_out )
    {
        tthread_mutex_unlock( p_data->mutex );
        return( NULL );
    }
    
    // get byte from buffer
    ret_value = p_data->pipe_list[ p_data->pointer_out ];
    
    if( size != NULL )
        *size =     p_data->pipe_size[ p_data->pointer_out ];
    
    if( take_it_out == TRUE )
    {
        // move out-pointer
        p_data->pointer_out++;
        if( p_data->pointer_out == p_data->max_size ) p_data->pointer_out = 0;
    }

    tthread_mutex_unlock( p_data->mutex );
    
    return( ret_value );
}

static void pipe_write_data( pipe_class_t * p_data, void * buffer, uint32_t size, bool_t is_dynamic )
{
    void * temp_buffer;
    if( is_dynamic == TRUE )
    {
        temp_buffer = MMALLOC( size );
        if( temp_buffer == NULL ) return;
        
        memcpy( temp_buffer, buffer, size );
    }
    else
    {
        temp_buffer = buffer;
    }

    tthread_mutex_lock( p_data->mutex );
    
    // insert data into the buffer
    p_data->pipe_list[ p_data->pointer_in ] = buffer;
    p_data->pipe_size[ p_data->pointer_in ] = size;
    p_data->is_dynamic[ p_data->pointer_in ] = is_dynamic;
    p_data->pointer_in++;
    
    // update pointers and control overflow
    if( p_data->pointer_in == p_data->max_size ) p_data->pointer_in = 0;
    
    // overflow, delete buffer
    if( p_data->pointer_in == p_data->pointer_out )
    {
        MFREE( p_data->pipe_list[ p_data->pointer_out ] );
        p_data->pointer_out++;
    }
    
    if( p_data->pointer_out == p_data->max_size ) p_data->pointer_out = 0;
    
    tthread_mutex_unlock( p_data->mutex );
    tthread_condition_signal( p_data->cond );
}

////////////////////////////////////////////////////////////////////

CREATOR static void creator( pipe_class_t * p_data, uint32_t max_size )
{
    p_data->pointer_in = 0;
    p_data->pointer_out = 0;
    p_data->max_size = max_size;
    
    p_data->mutex = tthread_mutex_init();
    p_data->cond = tthread_condition_create();
}

DELETE static void delete_pipe( pipe_class_t * p_data )
{
    while( p_data->pointer_in != p_data->pointer_out )
    {
        if( p_data->is_dynamic[p_data->pointer_out] == TRUE )
        {
            MFREE( p_data->pipe_list[p_data->pointer_out] );
        }
        
        // move out-pointer
        p_data->pointer_out++;
        if( p_data->pointer_out == p_data->max_size ) p_data->pointer_out = 0;
    }
}

METHOD static void * get( pipe_class_t * p_data, uint32_t * size )
{
    return pipe_read_data( p_data, size, FALSE );
}

METHOD static void * read( pipe_class_t * p_data, uint32_t * size )
{
    return pipe_read_data( p_data, size, TRUE );
}

METHOD static void * wait_for_data( pipe_class_t * p_data, uint32_t * size )
{
    while( 1 )
    {
        if( p_data->is_empty() == TRUE )
        {
            tthread_condition_wait( p_data->cond );
        }
    }
    
    return p_data->read( size );
}

METHOD static void write( pipe_class_t * p_data, void * buffer, uint32_t size )
{
    pipe_write_data( p_data, buffer, size, FALSE );
}

METHOD static void send( pipe_class_t * p_data, void * buffer, uint32_t size )
{
    pipe_write_data( p_data, buffer, size, TRUE );
}

METHOD static bool_t is_full( pipe_class_t * p_data )
{
    bool_t ret = FALSE;
    
    tthread_mutex_lock( p_data->mutex );
    
    // input is just before output
    if( p_data->pointer_in == ( p_data->pointer_out - 1 ) ) ret = TRUE ;
    
    // input is in the tail, and output is in the head
    else if( ( p_data->pointer_in == ( p_data->max_size - 1 ) ) &&
             ( p_data->pointer_out == 0 ) ) ret = TRUE;
    
    tthread_mutex_unlock( p_data->mutex );
    
    return( ret );
}

METHOD static bool_t is_empty( pipe_class_t * p_data )
{
    bool_t ret = FALSE;
    
    tthread_mutex_lock( p_data->mutex );
    if( p_data->pointer_in == p_data->pointer_out ) ret = TRUE;
    tthread_mutex_unlock( p_data->mutex );
    
    return( ret );
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( pipe_class_t );

////////////////////////////////////////////////////////////////////

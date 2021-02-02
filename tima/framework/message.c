#include "message.h"
#include "t_threads.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

void message_Init( message_data_t * msg )
{
	msg->pointer_in = 0;
	msg->pointer_out = 0;
    
    msg->mutex = tthread_mutex_init();
    msg->condition = tthread_condition_create();
    
	memset( msg->message_buffer, 0x00, sizeof( msg->message_buffer ) );
}

uint16_t message_GetData( message_data_t * msg, void ** p_data )
{
    uint16_t ret_value = Message_NoMessage;
    void * p_ret = NULL;
    
    tthread_mutex_lock( msg->mutex );
    
    if( msg->pointer_in != msg->pointer_out )
    {
        ret_value = msg->message_buffer[ msg->pointer_out ];
        p_ret = msg->data_buffer[ msg->pointer_out ];
        
        if( ret_value < Message_Exit_Priority )
        {
            msg->pointer_out++;
            if( msg->pointer_out == MESSAGE_MAX ) msg->pointer_out = 0;
        }
    }
    
    tthread_mutex_unlock( msg->mutex );
    
    if( p_data != NULL )
    {
        *p_data = p_ret;
    }
    
    return( ret_value );
}

uint16_t message_Wait( message_data_t * msg )
{
    if( msg->pointer_in == msg->pointer_out )
    {
        tthread_condition_wait( msg->condition );
    }
    
    return message_Get( msg );
}

uint16_t message_WaitData( message_data_t * msg, void ** p_data )
{
    if( msg->pointer_in == msg->pointer_out )
    {
        tthread_condition_wait( msg->condition );
    }
    
    return message_GetData( msg, p_data );
    
}

void message_PostData( message_data_t * msg, uint16_t in_data, void * p_data )
{
    tthread_mutex_lock( msg->mutex );
    
    if( in_data != Message_NoMessage )
    {
        msg->message_buffer[ msg->pointer_in ] = in_data;
        msg->data_buffer[ msg->pointer_in ] = p_data;
        
        msg->pointer_in++;
        if( msg->pointer_in == MESSAGE_MAX ) msg->pointer_in = 0;
        
        if( msg->pointer_in == msg->pointer_out ) msg->pointer_out++;
        if( msg->pointer_out == MESSAGE_MAX ) msg->pointer_out = 0;
    }
    
    tthread_mutex_unlock( msg->mutex );
    tthread_condition_signal( msg->condition );
}


uint16_t message_Get( message_data_t * msg )
{
	uint16_t ret_value = Message_NoMessage;

    tthread_mutex_lock( msg->mutex );
    
	if( msg->pointer_in != msg->pointer_out )
    {
        ret_value = msg->message_buffer[ msg->pointer_out ];
        
        if( ret_value < Message_Exit_Priority )
        {
            msg->pointer_out++;
            if( msg->pointer_out == MESSAGE_MAX ) msg->pointer_out = 0;
        }
    }

    tthread_mutex_unlock( msg->mutex );

	return( ret_value );
}

uint16_t message_Read( message_data_t * msg )
{
	uint16_t ret_value = Message_NoMessage;

    tthread_mutex_lock( msg->mutex );

	if( msg->pointer_in != msg->pointer_out )
    {
        ret_value = msg->message_buffer[ msg->pointer_out ];
    }
	
    tthread_mutex_unlock( msg->mutex );

    return( ret_value );
}

void message_Remove( message_data_t * msg )
{
    tthread_mutex_lock( msg->mutex );

    if( msg->pointer_in != msg->pointer_out )
    {
        msg->pointer_out++;
        if( msg->pointer_out == MESSAGE_MAX ) msg->pointer_out = 0;
    }

    tthread_mutex_unlock( msg->mutex );
}

void message_Post( message_data_t * msg, uint16_t in_data )
{
    tthread_mutex_lock( msg->mutex );

    if( in_data != Message_NoMessage )
    {
        msg->message_buffer[ msg->pointer_in ] = in_data;
        msg->data_buffer[ msg->pointer_in ] = NULL;
        
        msg->pointer_in++;
        if( msg->pointer_in == MESSAGE_MAX ) msg->pointer_in = 0;
        
        if( msg->pointer_in == msg->pointer_out ) msg->pointer_out++;
        if( msg->pointer_out == MESSAGE_MAX ) msg->pointer_out = 0;
    }

    tthread_mutex_unlock( msg->mutex );
    tthread_condition_signal( msg->condition );
}

void message_SendQuery( message_data_t * req, message_data_t * dest, uint16_t msg_query, uint16_t msg_resp )
{
    message_query_t * query = ( message_query_t * )MMALLOC( sizeof( message_query_t ) );
    if( query != NULL )
    {
        query->message_ret = msg_resp;
        query->p_message = ( message_data_t * )req;
        message_PostData( dest, msg_query, query );
    }
}

void message_ReplyQuery( void * p_query, uint32_t response )
{
    message_query_t * query = ( message_query_t * )p_query;
    if( query == NULL ) return;
    
    query->data = response;
    message_PostData( ( message_data_t * )query->p_message, query->message_ret, p_query );
}

uint32_t message_GetQuery( void * p_query )
{
    message_query_t * query = ( message_query_t * )p_query;
    uint32_t ret;
    
    if( query == NULL ) return 0;
    
    ret = query->data;
    MFREE( query );
    return ret;
}

void message_PostMatch( message_hook_t * msg, uint32_t value )
{
	message_hook_t * search = msg;

	while( search != NULL )
	{
		if( ( search->message_data != NULL ) && ( search->match_value == value ) )
		{
			message_Post( search->message_data, search->match_message );
		}

		search = search->p_next;
	}
}

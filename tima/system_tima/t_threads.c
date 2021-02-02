#include "t_threads.h"

////////////////////////////////////////////////////////////////////////////////////////////////

static void ** pp_data = NULL;

#ifdef USE_MULTITHREAD

static thread_data_t os_thread;
static bool_t syscall_usermode;

static thread_data_t * first_thread = NULL;
static thread_data_t * curr_thread = NULL;
static thread_data_t * last_thread = NULL;
static thread_data_t * syscall_thread = NULL;

void system_Events( void );

////////////////////////////////////////////////////////////////////////////////////////////////

void _thread_start_point( void )
{
    thread_addr_t thread_start_addr;
    thread_cb_t thread_callback;
    
    if( ( curr_thread != NULL ) && ( curr_thread->addr != NULL ) )
    {
        thread_start_addr = ( thread_addr_t )curr_thread->addr;
        thread_start_addr( curr_thread->args );
        
        if( curr_thread->callback != NULL )
        {
            thread_callback = ( thread_cb_t )curr_thread->callback;
            thread_callback();
        }
        
        thread_kill( NULL );
    }
    
    // should never get to here
    while( 1 ) { }
}

thread_data_t * _cpu_get_previous_thread( thread_data_t * context )
{
    thread_data_t * search_thread;
    thread_data_t * prev_thread;
    
    search_thread = first_thread;
    prev_thread = NULL;
    
    while( search_thread != NULL )
    {
        if( search_thread == context ) break;
        
        prev_thread = search_thread;
        search_thread = search_thread->t_next;
    }

    return prev_thread;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void thread_set_data_object( void ** p_obj )
{
    pp_data = p_obj;
    
    if( curr_thread != NULL ) curr_thread->p_data = *p_obj;
    else os_thread.p_data = *p_obj;
}

void thread_start( void )
{
    CPU_driver->get_os_context( &os_thread );
    
    if( first_thread != NULL )
    {
        curr_thread = first_thread;
        first_thread = first_thread->t_next;
        if( first_thread == NULL ) last_thread = NULL;
    }
    
    syscall_thread = NULL;

    while( TRUE )
    {
        if( curr_thread != NULL )
        {
            curr_thread->flags &= ~THREAD_SYSCALL;
            curr_thread->flags |= THREAD_CURRENT;
            syscall_usermode = TRUE;
            CPU_driver->start_contexts( curr_thread );
        }

        // getting here means usermode called syscall
        //if( syscall_entrypoint() == FALSE )
        //{
        //    break;
        //}
        
        // syscall terminated, go back to called
        curr_thread = syscall_thread;
        syscall_thread = NULL;
    }
}

void thread_syscall( uint32_t index )
{
    if( syscall_usermode == TRUE )
    {
        thread_wait( syscall_thread == NULL );
        syscall_thread = curr_thread;
        syscall_thread->flags |= THREAD_SYSCALL;
        syscall_thread->flags &= ~THREAD_CURRENT;
        syscall_usermode = FALSE;
        
        // switch to OS thread
        curr_thread = &os_thread;
        CPU_driver->syscall( curr_thread, index );
    }
}

void thread_yield( void )
{
    thread_data_t * next_thread;
    thread_data_t * this_thread;
    thread_data_t * old_thread;
    
    // rand_generate();
	SYSTEM_EVENTS();

    if( curr_thread == NULL ) return;
    
    if( curr_thread == &os_thread )
    {
        // thread switch from a syscall, take from the syscall caller thread
        this_thread = syscall_thread;
        syscall_usermode = TRUE;
    }
    else
    {
        this_thread = curr_thread;
    }
    
    while( TRUE )
    {
        if( ( this_thread->flags & THREAD_TERMINATE ) != 0 )
        {
            // thread is been terminated, kill it and dont link
            CPU_driver->kill_context( this_thread );

			if( ( this_thread->flags & THREAD_D_STACK ) != 0 )
			{
				MFREE( this_thread->stack );
			}

			if( ( this_thread->flags & THREAD_D_DATA ) != 0 )
			{
				MFREE( this_thread );
			}
		}
        else
        {
            // link the current thread at the end
            if( last_thread != NULL ) last_thread->t_next = this_thread;
            else first_thread = this_thread;
            
            last_thread = this_thread;
            last_thread->t_next = NULL;
        }

        // unlink first thread for use
        next_thread = first_thread;
        if( first_thread != NULL ) first_thread = first_thread->t_next;
        if( first_thread == NULL ) last_thread = NULL;
        
        if( next_thread == NULL )
        {
            // no threads to run
            thread_syscall( 0 /*SYSCALL_TERMINATED */ );
        }

        if( ( next_thread->flags & THREAD_SYSCALL ) != 0 )
        {
            // this thread is in a syscall, use OS thread
            next_thread = &os_thread;
            syscall_usermode = FALSE;
            break;
        }
        else if( ( next_thread->flags & THREAD_RUNNING ) != 0 )
        {
            break;
        }

        this_thread = next_thread;
        if( this_thread == curr_thread ) break;
    }
    
    if( next_thread == curr_thread ) return;

    // set custom application data
    if( pp_data != NULL )
    {
        *pp_data = next_thread->p_data;
    }    
    
    curr_thread->flags &= ~THREAD_CURRENT;
    old_thread = curr_thread;

    curr_thread = next_thread;
    curr_thread->flags |= THREAD_CURRENT;
    
    // set the new context
    CPU_driver->swap_context( old_thread, curr_thread );        
}

void exit_cb( void )
{
}

void thread_set_callback( thread_data_t * p_thread, void * cb )
{
    if( p_thread->flags == THREAD_RUNNING )
    {
        p_thread->callback = cb;
    }
}

bool_t thread_task_create( thread_data_t * p_thread, void * addr, void * param, void * stack, uint32_t stack_size )
{
    uint32_t * p_stack = ( uint32_t * )stack;
    
    if( stack_size < 128 ) return FALSE;
    
	// align stack size to 32bit
	stack_size = ( stack_size + 3 ) & ~3;

    p_thread->flags = THREAD_RUNNING;  

	// allow dynamic stack
	if( stack == NULL )
	{
		stack = ( void * )MMALLOC( stack_size >> 2 );
		if( stack == NULL ) return FALSE;

		p_thread->flags |= THREAD_D_STACK;
	}
    
	p_stack = ( uint32_t * )stack;
	stack_size -= 8;   
    p_stack = &p_stack[stack_size>>2];
    
    // finish initialization
    p_thread->stack = ( uint8_t * )stack;
    p_thread->stack_size = stack_size;
    p_thread->addr = addr;
    p_thread->callback = NULL;
    p_thread->args = param;
    
    // cpu dependent context creation
    CPU_driver->create_context( p_thread, _thread_start_point );
    if( p_thread->context == NULL ) 
	{
		if( ( p_thread->flags & THREAD_D_STACK ) != 0 )
		{
			MFREE( p_thread->stack );
		}

		return FALSE;
	}
    
    // set application defined data
    if( pp_data != NULL )
    {
        p_thread->p_data = *pp_data;
    }
    
    // link context
    if( first_thread == NULL )
    {
        first_thread = p_thread;
    }
    else
    {
        last_thread->t_next = p_thread;
    }

    last_thread = p_thread;
    p_thread->t_next = NULL;
    
    return TRUE;
}

void thread_kill( thread_data_t * p_thread )
{
    if( p_thread == NULL ) p_thread = curr_thread;
    p_thread->flags = THREAD_TERMINATE;
    thread_yield();
#if 0
    thread_data_t * prev_thread;
    
    if( p_thread == NULL ) return;
    
    // context signed to terminate, unlink
    prev_thread = _cpu_get_previous_thread( p_thread );
    if( prev_thread != NULL )
    {
        // curr_context isnt the first one
        prev_thread->t_next = p_thread->t_next;
    }
    else if( first_thread == p_thread->t_next )
    {
        // curr_context is the first and only one
        first_thread = NULL;
        last_thread = NULL;
    }
    else
    {
        // curr_context is the first one
        first_thread = p_thread->t_next;
    }

    CPU_driver->kill_context( p_thread );
#endif
}

#else

void * tthread_mutex_init( void )
{
    return NULL;
}

void tthread_mutex_lock( void * p_mutex )
{
}

void tthread_mutex_unlock( void * p_mutex )
{
}

void * tthread_condition_create( void )
{
    return NULL;
}

void tthread_condition_wait( void * p_cond )
{
}

void tthread_condition_signal( void * p_cond )
{
}

void * tthread_create_ex( tthread_handler_ex_t handler, void * args )
{
    return NULL;
}

void tthread_sleep_ms( int timeInMs )
{
}

void tthread_cancel( void * p_thread )
{
}

#endif

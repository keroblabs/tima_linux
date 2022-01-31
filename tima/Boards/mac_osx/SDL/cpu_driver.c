#include "system.h"
#include <SDL2/SDL.h>

////////////////////////////////////////////////////////////////////////

#define OS_STACK_SIZE   8192
#define DEFAULT_STACK   ( 128 * 1024 )

////////////////////////////////////////////////////////////////////////

typedef void ( *thread_call_t )( void * args );

typedef struct
{
    uint32_t thread_id;
    thread_call_t func;
    
    SDL_Thread * sdl_thread;
    SDL_cond * sdl_cond;
    SDL_mutex * sdl_mutex;
    
    bool_t thread_wait;
    void * args;
    
} thread_context_t;

////////////////////////////////////////////////////////////////////////

static thread_context_t os_context;
static uint32_t global_context_id = 0;

////////////////////////////////////////////////////////////////////////

void _cpu_sleep(void);

void _cpu_set_speed(uint8_t speed);

uint8_t _cpu_get_speed(void);

void _cpu_disable_irq(void);

void _cpu_enable_irq(void);

void _cpu_force_enable_irq(void);

bool_t _cpu_get_irq_state(void);

void _cpu_start_contexts( void * context );

void _cpu_get_os_context( void * thread );
void _cpu_create_context( void * thread, void * addr );

void _cpu_swap_context( void * old_thread, void * new_thread );
void _cpu_context_terminate( void * thread );
void _cpu_syscall( void * thread, void * args );

////////////////////////////////////////////////////////////////////////

static const cpu_api_t cpu_api = 
{
    _cpu_set_speed,
    _cpu_get_speed,

    _cpu_disable_irq,
    _cpu_enable_irq,
    _cpu_force_enable_irq,
    _cpu_get_irq_state,

    _cpu_sleep,
    
    _cpu_start_contexts,
    _cpu_get_os_context,
    _cpu_create_context,
    _cpu_swap_context,
    _cpu_context_terminate,
    _cpu_syscall
};

////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////

void _cpu_setup( uint32_t index )
{
}

void _cpu_init_mco( void )
{
}

void _cpu_sleep( void )
{
}

void _cpu_set_speed( uint8_t speed )
{
}

uint8_t _cpu_get_speed( void )
{
    return SPEED_DEFAULT;	
}

void _cpu_disable_irq( void )
{
}

void _cpu_enable_irq( void )
{
}

void _cpu_force_enable_irq( void )
{
}

bool_t _cpu_get_irq_state( void )
{
    return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////

void _cpu_internal_swap_context( thread_context_t * old_context, thread_context_t * new_context )
{
    // let new thread run
    SDL_mutexV( new_context->sdl_mutex );
    SDL_CondSignal(new_context->sdl_cond);
    
    // stop the running thread and wait for signal
    SDL_mutexP( old_context->sdl_mutex );
    SDL_CondWait(old_context->sdl_cond, old_context->sdl_mutex);
    SDL_mutexV( old_context->sdl_mutex );
}

int _cpu_thread_start_point( void * args )
{
    thread_context_t * context = ( thread_context_t * )args;
    
    SDL_mutexP( context->sdl_mutex );
    SDL_CondWait(context->sdl_cond, context->sdl_mutex);
    SDL_mutexV( context->sdl_mutex );
    SDL_CondSignal(context->sdl_cond);
    context->func( NULL );
    
    return 0;
}

void _cpu_start_contexts( void * thread )
{
    thread_data_t * thread_data = ( thread_data_t * )thread;
    thread_context_t * new_context = ( thread_context_t * )thread_data->context;
    
    // stop os thread and trig new context
    _cpu_internal_swap_context( &os_context, new_context );
}

void _cpu_get_os_context( void * thread )
{
    thread_data_t * thread_data = ( thread_data_t * )thread;
    thread_data->context = &os_context;
}

void _cpu_create_context( void * thread, void * addr )
{
    thread_context_t * context;
    thread_data_t * thread_data = ( thread_data_t * )thread;
    char thread_str[20];
    
    context = ( thread_context_t * )malloc(sizeof(thread_context_t));
    if( context == NULL ) return;

    context->thread_id = global_context_id;
    global_context_id++;
    
    sprintf( thread_str, "tima_thread_%d", context->thread_id );

    context->sdl_cond = SDL_CreateCond();
    context->sdl_mutex = SDL_CreateMutex();
    context->sdl_thread = SDL_CreateThread(_cpu_thread_start_point, thread_str, context);
    
    thread_data->context = context;
    
    context->thread_wait = TRUE;
    context->func = (thread_call_t )addr;
}

void _cpu_swap_context( void * old_thread, void * new_thread )
{
    thread_data_t * new_thread_data = ( thread_data_t * )new_thread;
    thread_data_t * old_thread_data = ( thread_data_t * )old_thread;
    
    thread_context_t * new_context = ( thread_context_t * )new_thread_data->context;
    thread_context_t * old_context = ( thread_context_t * )old_thread_data->context;

    _cpu_internal_swap_context(old_context, new_context);
}

void _cpu_context_terminate( void * thread )
{
    //thread_data_t * thread_data = ( thread_data_t * )thread;

}

void _cpu_syscall( void * thread, void * args )
{
    thread_data_t * thread_data = ( thread_data_t * )thread;
    thread_context_t * wait_context = ( thread_context_t * )thread_data->context;

    //syscall_index = args;

    // simple swap context
    _cpu_internal_swap_context(wait_context, &os_context);
}

////////////////////////////////////////////////////////////////////////

int event_loop( void * args )
{
    SDL_Event e;
    
    while( 1 )
    {
        //Event polling
        while (SDL_PollEvent(&e))
        {
            //If user closes he window
            if (e.type == SDL_QUIT)
            {
                return 0;
            }
            //If user presses any key
            if (e.type == SDL_KEYDOWN)
            {
                return 0;
            }
            //If user clicks the mouse
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
            }
        }
        
        SDL_Delay(1000);
    }
    
    return 0;
}

uint32_t cpu_read_ms( void )
{
    return SDL_GetTicks();
}

void cpu_sdl_do_events( void )
{
    SDL_Delay(10);
}

#if defined __MACH__
int SDL_main( int argc, char* argv[] )
#else
int main( int argc, char* argv[] )
#endif
{
    //int ret_code = 0;
    int _fe_main( void * args );
    
	//Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf( "Error = %s\n", SDL_GetError() );
        return 1;
    }
    
    os_context.sdl_thread = SDL_CreateThread(_fe_main, "os_thread", NULL);
    os_context.sdl_cond = SDL_CreateCond();
    os_context.sdl_mutex = SDL_CreateMutex();
    os_context.thread_id = NEG_U32;
    
    //SDL_WaitThread(os_context.sdl_thread, &ret_code);
    event_loop(NULL);
    
    //Quit SDL
    SDL_Quit();
    
	return 0;
}

////////////////////////////////////////////////////////////////////////

cpu_api_t * CPU_driver = ( cpu_api_t * )&cpu_api;




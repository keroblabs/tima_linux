#include "SDL_internal.h"
#include "system.h"

////////////////////////////////////////////////////////////////////

int _fe_main( void );

////////////////////////////////////////////////////////////////////

static Uint32 user_defined_type;

static SDL_mutex *user_signal_lock;
static SDL_cond  *user_signal_cond;
static bool_t user_signal_flag;

static sdl_loop_t * event_loop;

////////////////////////////////////////////////////////////////////

static void sdl_event_init( void )
{
    user_defined_type = SDL_RegisterEvents(1);
    
    user_signal_lock = SDL_CreateMutex();
    user_signal_cond = SDL_CreateCond();
}

static void run_delegate( void * data1, void * data2 )
{
    sdl_delegate_t delegate = ( sdl_delegate_t )data1;
    delegate( data2 );
}

static void sdl_event_loop_background( void )
{
    sdl_loop_t * loop = event_loop;
    
    while( loop != NULL )
    {
        loop->handler();
        loop = loop->next;
    }
}

static int sdl_event_loop( void )
{
    //Event handler
    SDL_Event e;
    
    // console keyboard
    sdl_input_event();
    
    sdl_event_loop_background();
    
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == user_defined_type )
        {
            SDL_LockMutex( user_signal_lock );
            
            switch( e.user.code )
            {
                case SDL_INTERNAL_DELEGATE:
                    run_delegate( e.user.data1, e.user.data2 );
                    break;
            }
            
            user_signal_flag = TRUE;
            SDL_CondSignal( user_signal_cond );
            SDL_UnlockMutex( user_signal_lock );
        }
        else
        {
            switch( e.type )
            {
                case SDL_TEXTINPUT:
                    sdl_text_input_event( ( uint8_t )e.text.text[0] );
                    break;
                    
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    sdl_keypad_down_event( e.key.keysym.sym, e.type );
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    sdl_mouse_event( e.type, e.button );
                    break;
                    
                case SDL_QUIT:
                    //system_PowerDown();
                    break;
            }
        }
    }
    
    return 1;
}

static int sdl_client_thread( void * param )
{
    instance_data_t * instance = ( instance_data_t * )param;
    sdl_signal_wait( &instance->signal );
    return _fe_main();
}

void sdl_add_event_loop( sdl_loop_t * event )
{
    if( event_loop != NULL ) event->next = event_loop;
    event_loop = event;
}

void sdl_signal_create( condition_signal_t * signal )
{
    signal->mutex = SDL_CreateMutex();
    signal->mutex_state = SDL_CreateMutex();
    signal->condition = SDL_CreateCond();
    signal->flag = FALSE;
    signal->state = FALSE;
}

void sdl_signal_wait( condition_signal_t * signal )
{
    SDL_LockMutex( signal->mutex_state );
    signal->state = TRUE;
    SDL_UnlockMutex( signal->mutex_state );

    SDL_LockMutex( signal->mutex );
    while( signal->flag == FALSE )
    {
        SDL_CondWait( signal->condition, signal->mutex );
    }
    signal->flag = FALSE;
    SDL_UnlockMutex( signal->mutex );

    SDL_LockMutex( signal->mutex_state );
    signal->state = FALSE;
    SDL_UnlockMutex( signal->mutex_state );
}

void sdl_signal_continue( condition_signal_t * signal )
{
    SDL_LockMutex( signal->mutex );
    signal->flag = TRUE;
    SDL_CondBroadcast( signal->condition );
    SDL_UnlockMutex( signal->mutex );
}

bool_t sdl_signal_state( condition_signal_t * signal )
{
    bool_t ret;
    
    SDL_LockMutex( signal->mutex_state );
    ret = signal->state;
    SDL_UnlockMutex( signal->mutex_state );

    return ret;
}

void sdl_instance_send_message( int message_code, void * data1, void * data2 )
{
    if (user_defined_type != ((Uint32)-1))
    {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
        event.type = user_defined_type;
        event.user.code = message_code;
        event.user.data1 = data1;
        event.user.data2 = data2;
        SDL_PushEvent(&event);
        
        user_signal_flag = FALSE;
        SDL_LockMutex( user_signal_lock );
        while( user_signal_flag == FALSE )
        {
            SDL_CondWait( user_signal_cond, user_signal_lock );
        }
        SDL_UnlockMutex( user_signal_lock );
    }
}

#if defined __MACH__
int SDL_main( int argc, char* argv[] )
#else
int main( int argc, char* argv[] )
#endif
{
    sdl_instance_init();
    sdl_mouse_init();
    sdl_event_init();
    sdl_lcd_init();
    
#ifdef WANT_MULTI_INSTANCES
    instance_data_t * instance;

    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        instance = sdl_alloc_instance();
        if( instance == NULL ) break;
        
        sdl_signal_create( &instance->signal );
        
        instance->thread = SDL_CreateThread(sdl_client_thread, "TestThread", instance);
        
        if (NULL == instance->thread)
        {
            printf("SDL_CreateThread failed: %s\n", SDL_GetError());
            continue;
        }
        
        sleep(1); // wait for the thread to start, otherwise there will be no ID
        instance->id = SDL_GetThreadID( instance->thread );
    }
    
    instance = sdl_get_instance_from_index( 0 );
    sdl_signal_continue( &instance->signal );
    
    while( 1 )
    {
        sdl_event_loop();
    }
    /*
     if( thread_list[0].thread != NULL )
     {
     SDL_WaitThread( thread_list[0].thread, &status );
     }
     */
#else
    _fe_main();
#endif
    return 0;
}

void sdl_startup_background( void )
{
    sdl_event_loop();
}

#ifndef WANT_MULTI_INSTANCES
//DECLARE_PROCESS_SECTION(sdl_event_loop);
#endif

////////////////////////////////////////////////////////////////////////////////

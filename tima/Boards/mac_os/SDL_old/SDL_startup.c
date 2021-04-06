#include "SDL_internal.h"
#include "system.h"

////////////////////////////////////////////////////////////////////

int _fe_main( void );

////////////////////////////////////////////////////////////////////

static Uint32 user_defined_type;

static SDL_mutex *user_signal_lock;
static SDL_cond  *user_signal_cond;
static bool_t user_signal_flag;

static sdl_loop_t * event_loop = NULL;
static sdl_loop_t * event_quit = NULL;

static sdl_keypad_down_event_t sdl_keypad_down_handler = NULL;
static sdl_text_input_event_t sdl_text_input_handler = NULL;
static sdl_mouse_event_t sdl_mouse_handler = NULL;

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

static void sdl_event_do_loop( sdl_loop_t * loop )
{
    while( loop != NULL )
    {
        loop->handler();
        loop = loop->next;
    }
}

static int sdl_client_thread( void * param )
{
    instance_data_t * instance = ( instance_data_t * )param;
    sdl_signal_wait( &instance->signal );
    return _fe_main();
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

void sdl_add_event_loop( sdl_loop_t * event )
{
    if( event_loop != NULL ) event->next = event_loop;
    event_loop = event;
}

void sdl_add_quit_handler( sdl_loop_t * event )
{
    if( event_quit != NULL ) event->next = event_quit;
    event_quit = event;
}

int sdl_event_loop( void )
{
    //Event handler
    SDL_Event e;
    
    sdl_event_do_loop( event_loop );
    
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
                    if( sdl_text_input_handler != NULL ) sdl_text_input_handler( ( uint8_t )e.text.text[0] );
                break;
                
                case SDL_KEYDOWN:
                    if( sdl_keypad_down_handler != NULL ) sdl_keypad_down_handler( e.key.keysym.sym );
                break;
                
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    if( sdl_mouse_handler != NULL ) sdl_mouse_handler( e.type, e.button );
                    // sdl_mouse_event( e.type, e.button );
                break;
                
                case SDL_QUIT:
                    sdl_event_do_loop( event_quit );
                    SDL_Quit();
                break;
            }
        }
    }
    
    return 1;
}

void sdl_set_text_input_event( sdl_text_input_event_t input )
{
    sdl_text_input_handler = input;
}

void sdl_set_keydown_event( sdl_keypad_down_event_t input )
{
    sdl_keypad_down_handler = input;
}

void sdl_set_mouse_event( sdl_mouse_event_t input )
{
    sdl_mouse_handler = input;
}

#if defined __MACH__
int SDL_main( int argc, char* argv[] )
#else
int main( int argc, char* argv[] )
#endif
{
    instance_data_t * instance;
    
    sdl_instance_init();
    sdl_mouse_init();
    sdl_event_init();
    sdl_screen_init();
    
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
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

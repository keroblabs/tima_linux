#include "SDL_internal.h"
#include "SDL_process.h"

////////////////////////////////////////////////////////////////////

static uint16_t port_list[] =
{
    12222,
    //12223,
    //12224,
    //12225,
    //12226,
    0
};

////////////////////////////////////////////////////////////////////

typedef struct thread_list_t_
{
    SDL_Thread * thread;
    SDL_threadID id;
    
    void * window_data;
    void * application_data;
    void * signal_data;
    const void * rom_data;
    
    uint8_t ram_data[MAX_RAM_DATA];
    uint16_t ram_pointer;
    
    uint16_t printf_port;
    
    //uint8_t current_channel;
    //pipe_data_t send_pipe;
    //pipe_data_t receive_pipe;
    //bool_t last_tx_good;
    //bool_t tx_completed;
    //bool_t is_listening;
    //void * failed_frame;
    
} instance_data_t;

////////////////////////////////////////////////////////////////////

static instance_data_t instance_list[MAX_INSTANCES];
static int current_instance;
static sdl_loop_t instance_loop;

int _fe_main( void );

////////////////////////////////////////////////////////////////////

static instance_data_t * sdl_get_instance_from_index( int index )
{
    if( instance_list[index].thread == NULL ) return NULL;
    return &instance_list[index];
}

static instance_data_t * sdl_get_current_instance( void )
{
    SDL_threadID thread_id = SDL_ThreadID();
    
    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        if( instance_list[i].thread == NULL ) break;
        if( instance_list[i].id == thread_id )
        {
            return &instance_list[i];
        }
    }
    
    return NULL;
}

static instance_data_t * sdl_alloc_instance( void )
{
    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        if( port_list[i] == 0 ) break;
        
        if( instance_list[i].thread == NULL )
        {
            instance_list[i].printf_port = port_list[i];
            return &instance_list[i];
        }
    }
    
    return NULL;
}

static void sdl_instance_scheduler( void )
{
    instance_data_t * next;
    instance_data_t * instance = sdl_get_instance_from_index( current_instance );
    if( sdl_signal_state( ( condition_signal_t * )instance->signal_data ) == TRUE )
    {
        current_instance++;
        next = sdl_get_instance_from_index( current_instance );
        if( next == NULL )
        {
            current_instance = 0;
            next = sdl_get_instance_from_index( current_instance );
        }
        
        sdl_signal_continue( ( condition_signal_t * )instance->signal_data );
    }
}

uint8_t * sdl_instance_add_ram_data( uint16_t size )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return NULL;
    if( ( instance->ram_pointer + size ) > MAX_RAM_DATA ) return NULL;
    
    uint8_t * ret = &instance->ram_data[instance->ram_pointer];
    instance->ram_pointer += size;
    
    return ret;
}

static int sdl_client_thread( void * param )
{
    instance_data_t * instance = ( instance_data_t * )param;
    sdl_signal_wait( ( condition_signal_t * )instance->signal_data );
    return _fe_main();
}

void sdl_instance_init( void )
{
    instance_data_t * instance;
    
    current_instance = 0;
    memset( instance_list, 0x00, sizeof( instance_list ) );
    
    instance_loop.handler = sdl_instance_scheduler;
    sdl_add_event_loop( &instance_loop );
    
    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        instance = sdl_alloc_instance();
        if( instance == NULL ) break;
        
        instance->signal_data = MMALLOC( sizeof( condition_signal_t ) );
        
        sdl_signal_create( ( condition_signal_t * )instance->signal_data );
        
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
    sdl_signal_continue( ( condition_signal_t * )instance->signal_data );
}

void sdl_instance_switch_context( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return;

    sdl_signal_wait( ( condition_signal_t * )instance->signal_data );
}

int sdl_get_thread_index( void )
{
    SDL_threadID thread_id = SDL_ThreadID();
    
    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        if( instance_list[i].thread == NULL ) break;
        if( instance_list[i].id == thread_id ) return i;
    }
    
    return -1;
}

const void * sdl_get_rom_data( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return NULL;
    return instance->rom_data;
}

void sdl_set_rom_data( const char * data )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL ) instance->rom_data = data;
}

void * sdl_get_window_data_from_index( int index )
{
    if( instance_list[index].thread == NULL ) return NULL;
    return instance_list[index].window_data;
}

void * sdl_get_window_data( void )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance == NULL ) return NULL;
    return instance->window_data;
}

void sdl_set_window_data( void * data )
{
    instance_data_t * instance = sdl_get_current_instance();
    if( instance != NULL ) instance->window_data = data;
}

#include "SDL_internal.h"
#include "device.h"
#include "system.h"

////////////////////////////////////////////////////////////////////

typedef struct rom_data_t_
{
    uint16_t node_id;
    uint16_t signal_level;
    const char node_name[32];
    
} rom_data_t;

static const rom_data_t rom_data[] =
{
    { 1, 200, "node 01" },
    { 2, 100, "node 02" },
    { 3,  50, "node 03" },
    { 4, 200, "node 04" },
    { 0,   0, ""        }
};

static uint16_t port_list[] =
{
    12222,
    12223,
    //12224,
    //12225,
    //12226,
    0
};

////////////////////////////////////////////////////////////////////

static instance_data_t instance_list[MAX_INSTANCES];
static int current_instance;
static sdl_loop_t instance_loop;

////////////////////////////////////////////////////////////////////

static void sdl_instance_scheduler( void )
{
    instance_data_t * next;
    instance_data_t * instance = sdl_get_instance_from_index( current_instance );
    if( sdl_signal_state( &instance->signal ) == TRUE )
    {
        current_instance++;
        next = sdl_get_instance_from_index( current_instance );
        if( next == NULL )
        {
            current_instance = 0;
            next = sdl_get_instance_from_index( current_instance );
        }
        
        sdl_signal_continue( &next->signal );
    }
}

void sdl_instance_init( void )
{
    current_instance = 0;
    
    memset( instance_list, 0x00, sizeof( instance_list ) );
    
    instance_loop.handler = sdl_instance_scheduler;
    sdl_add_event_loop( &instance_loop );
}

void sdl_instance_switch_context( void )
{
    instance_data_t * data = sdl_get_current_instance();
    if( data == NULL ) return;

    sdl_signal_wait( &data->signal );
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

window_data_t * sdl_get_window_data( void )
{
    instance_data_t * data = sdl_get_current_instance();
    if( data == NULL ) return NULL;
    
    return &data->window_data;
}

instance_data_t * sdl_get_current_instance( void )
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

instance_data_t * sdl_get_instance_from_index( int index )
{
    if( instance_list[index].thread == NULL ) return NULL;
    return &instance_list[index];
}

instance_data_t * sdl_alloc_instance( void )
{
    for( int i = 0; i < MAX_INSTANCES; i++ )
    {
        if( port_list[i] == 0 ) break;
        
        if( instance_list[i].thread == NULL )
        {
            instance_list[i].printf_port = port_list[i];
            instance_list[i].rom_data    = &rom_data[i];
            return &instance_list[i];
        }
    }
    
    return NULL;
}

const void * sdl_get_rom_data( uint16_t * size )
{
    instance_data_t * data = sdl_get_current_instance();
    if( data == NULL ) return NULL;
    
    if( size ) *size = ( uint16_t )sizeof( rom_data_t );
    return data->rom_data;
}


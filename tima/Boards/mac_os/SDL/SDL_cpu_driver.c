#include "SDL_internal.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_HEAP_SIZE        (256*1024)
#define MAX_INSTANCES           10

uint8_t system_heap[SYSTEM_HEAP_SIZE];
uint32_t system_heap_size = SYSTEM_HEAP_SIZE;

////////////////////////////////////////////////////////////////////////////////

static pthread_mutex_t cpu_mutex;

////////////////////////////////////////////////////////////////////////////////

static void cpu_init( void )
{
    pthread_mutex_init( &cpu_mutex, NULL );
}

static void _cpu_scheduler( void )
{
    sdl_instance_yield();
}

void _cpu_disable_irq( void )
{
    pthread_mutex_lock( &cpu_mutex );
}

void _cpu_enable_irq( void )
{
    pthread_mutex_unlock( &cpu_mutex );
}

DECLARE_INIT_CRITICAL_SECTION( cpu_init );
DECLARE_PROCESS_SECTION( _cpu_scheduler );

////////////////////////////////////////////////////////////////////////////////


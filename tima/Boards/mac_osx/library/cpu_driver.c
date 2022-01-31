#include "system.h"

#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_HEAP_SIZE 		(256*1024)

uint8_t system_heap[SYSTEM_HEAP_SIZE];
uint32_t system_heap_size = SYSTEM_HEAP_SIZE;

static pthread_mutex_t cpu_mutex;

////////////////////////////////////////////////////////////////////////////////

static void cpu_init( void )
{
    pthread_mutex_init( &cpu_mutex, NULL );
}

void _cpu_disable_irq( void )
{
    pthread_mutex_lock( &cpu_mutex );
}

void _cpu_enable_irq( void )
{
    pthread_mutex_unlock( &cpu_mutex );
}

void _cpu_pio( bool_t state )
{
}

void CPU_pio_reset( bool_t state )
{
}

DECLARE_INIT_CRITICAL_SECTION( cpu_init );

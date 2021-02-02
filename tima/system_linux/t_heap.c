#include "t_heap.h"

////////////////////////////////////////////////////////////////////////

#define DONT_MEMORY_DEBUG_ENABLED

////////////////////////////////////////////////////////////////////////

static uint32_t memory_heap = 0;

////////////////////////////////////////////////////////////////////////

void mm_init( void )
{
#ifdef MEMORY_DEBUG_ENABLED
    FILE * fp;
    fp = fopen( "memory_debug.txt", "w" );
    fprintf( fp, "# start\n" );
    fclose( fp );
#endif
}

uint32_t mm_used( void )
{
    return memory_heap;
}

void * mmalloc( size_t size, const char * file, int line )
{
    memory_heap++;
    void * ret = malloc(size);

#ifdef MEMORY_DEBUG_ENABLED
    FILE * fp;
    fp = fopen( "memory_debug.txt", "a" );
    fprintf( fp, "malloc %3d %08x %5d %s\n", memory_heap, (uint32_t)ret, line, file );
    fclose( fp );
#endif
    
    return ret;
}

void * zmmalloc( size_t size, const char * file, int line )
{
    void * ret = mmalloc( size, file, line );
    memset( ret, 0x00, size );
    return ret;
}

void mfree( void * p, const char * file, int line )
{
    memory_heap--;

#ifdef MEMORY_DEBUG_ENABLED
    FILE * fp;
    fp = fopen( "memory_debug.txt", "a" );
    fprintf( fp, "free   %3d %08x %5d %s\n", memory_heap, (uint32_t)p, line, file );
    fclose( fp );
#endif
    
    free( p );
}


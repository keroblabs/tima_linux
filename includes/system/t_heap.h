#ifndef t_heap_h
#define t_heap_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

#define DONT_MEMORY_DEBUG_ENABLED

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

void mm_init( void );

uint32_t mm_used( void );

void * mmalloc( size_t size, const char * file, int line );

void * zmmalloc( size_t size, const char * file, int line );

void mfree( void * p, const char * file, int line );

////////////////////////////////////////////////////////////////////////

#endif

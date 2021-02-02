#ifndef _HEAP_MMU_H_
#define _HEAP_MMU_H_

///////////////////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////////////////

typedef void ( *heap_handler_t )( uint8_t cause );

typedef struct _heap_t
{
    uint8_t * memory;
    uint32_t size;
    uint32_t used;

	heap_handler_t error_hdl;

} heap_t;

///////////////////////////////////////////////////////////////////////////

enum
{
	HEAP_ERROR_NO_MEMORY,
	HEAP_ERROR_CORRUPTED,
	HEAP_ERROR_INVALID
};

///////////////////////////////////////////////////////////////////////////

void heap_init( heap_t * heap_data, uint8_t * buffer, uint32_t size );
void heap_set_error_handler( heap_t * heap_data, heap_handler_t handler );

uint32_t heap_in_use( heap_t * heap_data );
uint32_t heap_size( heap_t * heap_data );

void * heap_malloc( heap_t * heap_data, uint32_t size );

void heap_free( heap_t * heap_data, void * p_mem );

bool_t heap_list_debug( ptr_print_t p_dev, heap_t * heap_data );
bool_t heap_check( heap_t * heap_data );

//////////////////////////////////////////////////////////////////////////

#endif // _HEAP_MMU_H_

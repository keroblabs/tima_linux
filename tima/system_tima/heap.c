#include "heap.h"
//#include "debug.h"

///////////////////////////////////////////////////////////////////////////

#define MIN_HEAP_SIZE         ( sizeof( heap_header_t ) + 4 )
#define HEAP_HEAD_SIZE        sizeof( heap_header_t )

#define HEAP_FREE_BLOCK       0xF460
#define HEAP_USED_BLOCK       0x8AC0
#define HEAP_USED_DATA        0x03E0
#define HEAP_USED_HEAP        0x2820
#define HEAP_CONST_DATA       0xF0F0

#define HEAP_FIELD_MASK          0x001F

///////////////////////////////////////////////////////////////////////////

#define HEAP_HEADER_STRUCT          uint32_t signature;                \
                                    uint32_t size;

///////////////////////////////////////////////////////////////////////////

heap_t * p_heap_data;

//////////////////////////////////////////////////////////////////////////

static bool_t heap_check_internal( ptr_print_t dev, heap_t * heap_data );

//////////////////////////////////////////////////////////////////////////

typedef struct _heap_header_t
{
    HEAP_HEADER_STRUCT

} heap_header_t;

typedef struct _heap_header_t2
{
    HEAP_HEADER_STRUCT

    uint8_t mem;

} heap_header_t2;

typedef struct _heap_header_t3
{
    HEAP_HEADER_STRUCT

    uint8_t * data;

} heap_header_t3;

///////////////////////////////////////////////////////////////////////////

static heap_header_t * _locate_next( heap_header_t * p )
{
   uint32_t heap_index;

   if( p == NULL )
   {
       return NULL;
   }

   heap_index = ( uint32_t )p - ( uint32_t )&p_heap_data->memory[0];
   heap_index += p->size + HEAP_HEAD_SIZE;

   if( heap_index >= p_heap_data->size ) return( NULL );
   p = ( heap_header_t * )&p_heap_data->memory[ heap_index ];

   return( p );
}

static heap_header_t * _locate_previous( heap_header_t * p )
{
   heap_header_t * p_search;
   heap_header_t * p_prev;

   p_prev = NULL;
   p_search = ( heap_header_t * )&p_heap_data->memory[ 0 ];

   while( p_search < p )
   {
      p_prev = p_search;
      p_search = _locate_next( p_prev );
   }

   return( p_prev );
}

static INLINE uint8_t * _get_memory( heap_header_t * p )
{
   heap_header_t2 * p_mem;
   p_mem = ( heap_header_t2 * )p;
   return( &p_mem->mem );
}

static INLINE uint8_t * _get_memory_data( heap_header_t * p )
{
   heap_header_t2 * p_mem;
   uint8_t ** p_data;

   p_mem = ( heap_header_t2 * )p;
   p_data = ( uint8_t ** )( &p_mem->mem );

   return( *p_data );
}


static INLINE heap_header_t * _get_header( void * p_mem )
{
   heap_header_t * p;
   p = ( heap_header_t * )( ( uint8_t * )p_mem - HEAP_HEAD_SIZE );
   return( p );
}

static heap_header_t * _internal_malloc( uint16_t size )
{
    heap_header_t * p;
    heap_header_t * p_new;
    uint8_t * p_mem;
    uint16_t signature;

    p_mem = NULL;

    // 32bit allignment
    size = ( size + 3 )& ~3;

    // get first block
    p = ( heap_header_t * )&p_heap_data->memory[ 0 ];

    while( p != NULL )
    {
        signature = p->signature & ~HEAP_FIELD_MASK;

        if( ( signature != HEAP_FREE_BLOCK ) &&
            ( signature != HEAP_USED_HEAP ) &&
            ( signature != HEAP_USED_DATA ) &&
            ( signature != HEAP_USED_BLOCK ) )
        {
			if( p_heap_data->error_hdl != NULL )
			{
				p_heap_data->error_hdl( HEAP_ERROR_CORRUPTED );
			}
            return NULL;
        }

        if( ( p->signature == HEAP_FREE_BLOCK ) && ( p->size >= size ) )
        {
            // block is free and suitable size
            p->signature = HEAP_USED_DATA;
            p_mem = _get_memory( p );
            memset( p_mem, 0x00, p->size );

            // is there space for another block?
            if( ( p->size - size ) >= MIN_HEAP_SIZE )
            {
                // squeeze block
                uint32_t new_size = p->size - size - HEAP_HEAD_SIZE;
                p->size = size;

                // create another block
                p_new = _locate_next( p );
                p_new->signature = HEAP_FREE_BLOCK;
                p_new->size = new_size;

                p_heap_data->used += HEAP_HEAD_SIZE;

            }

            p_heap_data->used += p->size;

            break;
        }

        // get next block
        p = _locate_next( p );
    }

    if( p_mem == NULL )
    {
        // need more memory
		if( p_heap_data->error_hdl != NULL )
		{
			p_heap_data->error_hdl( HEAP_ERROR_NO_MEMORY );
		}
    }

    return( p );
}

void _internal_free( void * p_mem )
{
    heap_header_t * p;
    heap_header_t * p_prev;
    heap_header_t * p_next;
    uint16_t signature;

    // get header block
    p = _get_header( p_mem );
    if( p == NULL ) 
	{
		if( p_heap_data->error_hdl != NULL )
		{
			p_heap_data->error_hdl( HEAP_ERROR_INVALID );
		}

		return;
	}

    signature = p->signature & ~HEAP_FIELD_MASK;

    if( ( signature != HEAP_FREE_BLOCK ) &&
        ( signature != HEAP_USED_HEAP ) &&
        ( signature != HEAP_USED_DATA ) &&
        ( signature != HEAP_USED_BLOCK ) )
    {
		if( p_heap_data->error_hdl != NULL )
		{
			p_heap_data->error_hdl( HEAP_ERROR_CORRUPTED );
		}
        return;
    }

    // release memory
    p->signature = HEAP_FREE_BLOCK;
    p_heap_data->used -= p->size;

    // locate next
    p_next = _locate_next( p );
    if( p_next != NULL )
    {
        if( p_next->signature == HEAP_FREE_BLOCK )
        {
            p->size = p->size + p_next->size + HEAP_HEAD_SIZE;
            p_heap_data->used -= HEAP_HEAD_SIZE;
        }
    }

    // locate previous
    p_prev = _locate_previous( p );
    if( p_prev != NULL )
    {
        if( p_prev->signature == HEAP_FREE_BLOCK )
        {
            p_prev->size = p_prev->size + p->size + HEAP_HEAD_SIZE;
            p_heap_data->used -= HEAP_HEAD_SIZE;
        }
    }
}

///////////////////////////////////////////////////////////////////////////

void heap_init( heap_t * heap_data, uint8_t * buffer, uint32_t size )
{
    heap_header_t * p;

	p_heap_data = heap_data;

    p_heap_data->memory = buffer;
    p_heap_data->size = size;
    p_heap_data->used = 0;
	p_heap_data->error_hdl = NULL;

    p = ( heap_header_t * )p_heap_data->memory;

    p->signature = HEAP_FREE_BLOCK;
    p->size = size - ( uint32_t )HEAP_HEAD_SIZE;

    p_heap_data->used += ( uint32_t )HEAP_HEAD_SIZE;
}

void heap_set_error_handler( heap_t * heap_data, heap_handler_t handler )
{
	heap_data->error_hdl = handler;
}

uint32_t heap_in_use( heap_t * heap_data )
{
	p_heap_data = heap_data;
    return p_heap_data->used;
}

uint32_t heap_size( heap_t * heap_data )
{
	p_heap_data = heap_data;
    return p_heap_data->size;
}

void * heap_malloc( heap_t * heap_data, uint32_t size )
{
    heap_header_t * p_data;
    uint8_t * p_mem;

	p_heap_data = heap_data;

    // create header
    p_data = ( heap_header_t * )_internal_malloc( size );
    if( p_data == NULL )
    {
        // need more memory
        return NULL;
    }

    //p_data->signature = HEAP_USED_HEAP;
    p_mem = _get_memory( p_data );
    return p_mem;
}

bool_t heap_list_debug( ptr_print_t dev, heap_t * heap_data )
{
	return heap_check_internal( dev, heap_data );
}

bool_t heap_check( heap_t * heap_data )
{
	return heap_check_internal( NULL, heap_data );
}

bool_t heap_check_internal( ptr_print_t p_print, heap_t * heap_data )
{
    heap_header_t * p;
    heap_header_t * p_prev;
    uint16_t signature;

	p_heap_data = heap_data;

    // get first block
    p = ( heap_header_t * )&p_heap_data->memory[ 0 ];

    while( p != NULL )
    {
        signature = p->signature & ~HEAP_FIELD_MASK;

        // check signature
        if( ( signature != HEAP_FREE_BLOCK ) &&
            ( signature != HEAP_USED_HEAP ) &&
            ( signature != HEAP_USED_BLOCK ) &&
            ( signature != HEAP_USED_DATA ) )
        {
			if( p_heap_data->error_hdl != NULL )
			{
				p_heap_data->error_hdl( HEAP_ERROR_CORRUPTED );
			}

			return FALSE;
        }

		if( p_print != NULL )
		{
			p_print( "Type " );

			switch( signature )
			{
				case HEAP_FREE_BLOCK:
					p_print( "free   " );
					break;
				case HEAP_USED_HEAP:
					p_print( "heap   " );
					break;
				case HEAP_USED_BLOCK:
					p_print( "block  " );
					break;
				case HEAP_USED_DATA:
					p_print( "data   " );
					break;
				default:
					p_print( "?????  " );
					break;
			}

			p_print( "%d bytes\r\n", p->size );
		}

        // get next block
        p_prev = p;
        p = _locate_next( p );
    }

    // if came to here means heap is fine
	return TRUE;
}

void heap_free( heap_t * heap_data, void * p_mem )
{
    heap_header_t * p;
    uint8_t * p_data;

	p_heap_data = heap_data;

    // get header block
    p = _get_header( p_mem );

	if( p == NULL ) 
	{
		if( p_heap_data->error_hdl != NULL )
		{
			p_heap_data->error_hdl( HEAP_ERROR_INVALID );
		}

		return;
	}

    if( ( p->signature & ~HEAP_FIELD_MASK ) == HEAP_USED_BLOCK )
    {
        p_data = _get_memory_data( p );
        _internal_free( p_data );
    }

    _internal_free( p_mem );
}

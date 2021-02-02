#ifndef __lp_filter_h__
#define __lp_filter_h__

///////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////

typedef struct
{
	uint32_t * filter_array;
	uint32_t filter_size;
	uint32_t filter_total;
	uint32_t filter_index;

} lp_filter_t;

///////////////////////////////////////////////////////////////

void lp_filter_init( lp_filter_t * filter, uint32_t * buffer, uint32_t size );
void lp_filter_force( lp_filter_t * filter, uint32_t value );

uint32_t lp_filter_add( lp_filter_t * filter, uint32_t value );
uint32_t lp_filter_get_value( lp_filter_t * filter );

///////////////////////////////////////////////////////////////

#endif // __lp_filter_h__

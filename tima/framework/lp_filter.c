#include "lp_filter.h"

///////////////////////////////////////////////////////////////

void lp_filter_init( lp_filter_t * filter, uint32_t * buffer, uint32_t size )
{
	filter->filter_array = buffer;
	filter->filter_size = size;
	filter->filter_index = 0;
	filter->filter_total = 0;
}

uint32_t lp_filter_add( lp_filter_t * filter, uint32_t value )
{
	filter->filter_total -= filter->filter_array[filter->filter_index];
	filter->filter_array[filter->filter_index] = value;
	filter->filter_total += value;

	if( ++filter->filter_index >= filter->filter_size ) filter->filter_index = 0;

	return lp_filter_get_value( filter );
}

uint32_t lp_filter_get_value( lp_filter_t * filter )
{
	return ( filter->filter_total / filter->filter_size );
}

void lp_filter_force( lp_filter_t * filter, uint32_t value )
{
	uint32_t cnt;

	filter->filter_total = 0;

	for( cnt = 0; cnt < filter->filter_size; cnt++ )
	{
		filter->filter_array[cnt] = value;
		filter->filter_total += value;
	}
}


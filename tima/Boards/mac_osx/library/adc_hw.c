#include "system.h"
//#include "debug.h"

//////////////////////////////////////////////////////////////////////////////

uint16_t hw_adc_index;

//////////////////////////////////////////////////////////////////////////////

void adc_hw_start( uint32_t index )
{
	hw_adc_index = index;
}

bool_t adc_hw_check( uint16_t * value )
{
	if( hw_adc_index == 2 ) *value = 506;
    else if( hw_adc_index == 3 ) *value = 399;
    else if( hw_adc_index == 1 ) *value = 2450;
    else return FALSE;
    
    return TRUE;
}

void adc_hw_init( void )
{
}


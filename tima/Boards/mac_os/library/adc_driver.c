#include "adc_driver_class_private.h"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

CREATOR static void init( adc_driver_class_t * p_data, uint8_t index )
{
}

METHOD static void start( adc_driver_class_t * p_data )
{
}

METHOD static bool_t is_ready( adc_driver_class_t * p_data )
{
    return TRUE;
}

METHOD static uint16_t read( adc_driver_class_t * p_data )
{
    return 0;
}

///////////////////////////////////////////////////////////////////////////

CREATE_CLASS(adc_driver_class_t);

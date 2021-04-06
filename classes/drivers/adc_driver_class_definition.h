#ifndef BOARDS_INCLUDE_ADC_DRIVER_H_
#define BOARDS_INCLUDE_ADC_DRIVER_H_

///////////////////////////////////////////////////////////////////////////

#include "class_framework.h"

///////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 16

///////////////////////////////////////////////////////////////////////////

typedef CLASS(adc_driver_class_t)
{
    CLASS_DATA_VOID;
    uint8_t adc_index;
    
    CREATOR void ( *init )( uint8_t index );
    METHOD void ( *start )( void );
    METHOD bool_t ( *is_ready )( void );
    METHOD uint16_t ( *read )( void );

} adc_driver_class_t;

///////////////////////////////////////////////////////////////////////////

#endif /* BOARDS_INCLUDE_ADC_DRIVER_H_ */

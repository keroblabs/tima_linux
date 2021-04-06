#ifndef _TIMER_CLASS_DEFINITION_H_
#define _TIMER_CLASS_DEFINITION_H_

////////////////////////////////////////////////////////////////////////

#include "timer_driver_class.h"

////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 32

////////////////////////////////////////////////////////////////////////

typedef CLASS(timer_class_t)
{
    CLASS_DATA_VOID;
    
    timer_driver_class_t * driver;
    
    uint32_t reload_ms;
    uint32_t expire_ms;
    uint32_t status;
    
    void * mutex;
    
    CREATOR void ( *creator )( uint32_t period );
    METHOD void ( *start )( uint32_t period );
    METHOD void ( *reload )( void );
    METHOD void ( *stop )( void );
    METHOD void ( *expire )( void );
    METHOD bool_t ( *check )( void );
    METHOD uint32_t ( *get_counter )( void );

} timer_class_t;

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

#endif // _TIMER_CLASS_DEFINITION_H_


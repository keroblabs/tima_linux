#ifndef BOARD_MS_TIMER_H_
#define BOARD_MS_TIMER_H_

///////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "class_framework.h"

///////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 1

///////////////////////////////////////////////////////////////////////////

typedef CLASS(timer_driver_class_t)
{
    CLASS_DATA_VOID;
    struct timeval ms_start;
    
    CREATOR void ( *creator )( void );
    METHOD uint32_t ( *get_ms )( void );
    METHOD uint64_t ( *get_us )( void );
    
} timer_driver_class_t;

///////////////////////////////////////////////////////////////////////////

#endif /* BOARD_MS_TIMER_H_ */

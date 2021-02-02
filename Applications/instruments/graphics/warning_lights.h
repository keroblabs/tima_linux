#ifndef warning_lights_h
#define warning_lights_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

#define WARNING_SLOT_KEY            0
#define WARNING_SLOT_FAULT          0
#define WARNING_SLOT_FOG_LIGHT      1
#define WARNING_SLOT_HEADLIGHT      1
#define WARNING_SLOT_INDICATOR      2
#define WARNING_SLOT_OIL            3
#define WARNING_SLOT_WASHERS        3

#define WARNING_SLOT_BATTERY        5
#define WARNING_SLOT_LOW_FUEL       6
#define WARNING_SLOT_OVERHEAT       8
#define WARNING_SLOT_BRAKE          6
#define WARNING_SLOT_HANDBRAKE      6

#define SLOT_MAX_COUNT              12

////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    Warning_Battery,
    Warning_Brake_Service,
    Warning_Brake_Parking,
    Warning_Lights_Dimmed,
    Warning_Lights_FullBeam,
    Warning_Lights_Fog,
    Warning_Indicator_Left,
    Warning_Indicator_Right,
    Warning_Temperature_Blue,
    Warning_Temperature_Warning,
    Warning_Fuel_Blue,
    Warning_Fuel_Warning,
    Warning_OilPressure,
    Warning_EngineFault,
    Warning_Hazard,
    Warning_Washers,
    Warning_Key,
    Warning_Headlamps,
    
    WARNING_MAX_TOTAL,

    Warning_Unused,
    
} warning_t;

////////////////////////////////////////////////////////////////////////////////////////

void warning_lights_init( void );
void warning_lights_show( void * p_lcd, warning_t warning, uint16_t posx, uint16_t posy );

void warning_shift_light_init( uint16_t posx, uint16_t posy );
void warning_shift_set_state( void * p_lcd, bool_t state );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* warning_lights_h */

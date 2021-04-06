#ifndef touchscreen_lib_h
#define touchscreen_lib_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    Touchscreen_Event_None,
    Touchscreen_Event_Start,
    Touchscreen_Event_Short,
    Touchscreen_Event_Long,
    Touchscreen_Event_MoveLeft,
    Touchscreen_Event_MoveRight,
    Touchscreen_Event_MoveUp,
    Touchscreen_Event_MoveDown,
    Touchscreen_Event_End,
} touchscreen_event_t;

////////////////////////////////////////////////////////////////////////////////////////

typedef bool_t ( *touchscreen_event_handler_t )( touchscreen_event_t event, uint16_t posx, uint16_t posy, uint16_t posz );

////////////////////////////////////////////////////////////////////////////////////////

void touchscreen_lib_set_reading( uint16_t posx, uint16_t posy, uint16_t posz );
void touchscreen_lib_get_reading( uint16_t *posx, uint16_t *posy, uint16_t *posz );
void touchscreen_lib_set_handler( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, touchscreen_event_handler_t handler );
void touchscreen_lib_init( void );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* touchscreen_lib_h */

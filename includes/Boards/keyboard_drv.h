#ifndef BOARDS_INCLUDE_KEYBOARD_H_
#define BOARDS_INCLUDE_KEYBOARD_H_

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

//////////////////////////////////////////////////////////////////////////////////////

#define ALT_FLAG		0x01
#define ALTGR_FLAG		0x02
#define SHIFT_FLAG		0x04
#define CTRL_FLAG		0x08
#define CTRL2_FLAG		0x10
#define WIN_FLAG		0x20
#define CAPS_FLAG		0x40

#define RESET_FLAG		0x01
#define FUNCTION_FLAG	0x02
#define OPENAPL_FLAG	0x04
#define CLOSEAPL_FLAG   0x08

#define KEYB_DOWN		1
#define KEYB_UP			2
#define KEYB_NONE		0

#define CTRL_RESET		129

///////////////////////////////////////////////////////////////////////////

typedef struct keyb_event
{
	uint16_t flags;
	char key;
	bool_t mode;

} keyb_event_t;

typedef struct mouse_limits_t_
{
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    int curr_x;
    int curr_y;

    int delta_x;
    int delta_y;

    uint32_t time_x;
    uint32_t time_y;
    int target_x;
    int target_y;
    int start_x;
    int start_y;

    bool_t mouse_button;
    bool_t mouse_button2;
    bool_t open_apple;
    bool_t close_apple;

    uint8_t flags;

    bool_t is_update;

    void * mutex;

} mouse_info_t;

//////////////////////////////////////////////////////////////////////////////////////

bool_t keybdrv_check( void );
bool_t keybdrv_read( keyb_event_t * event );

bool_t keybdrv_mouse_check( void );
bool_t keybdrv_mouse_read( mouse_info_t * event );

void keybdrv_init( void );

void keybdrv_mouse_set_limits( uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y );
void keybdrv_mouse_set_pos( uint16_t posx, uint16_t posy );
void keybdrv_mouse_get_joystick( uint16_t * posx, uint16_t * posy );
void keybdrv_mouse_read_joystick( uint16_t * posx, uint16_t * posy );

bool_t keybdrv_mouse_get_pos( uint16_t * posx, uint16_t * posy, uint16_t * posz );

bool_t keybdrv_read_button0( void );
bool_t keybdrv_read_button1( void );

void keybdrv_mouse_set_state( bool_t state );

//////////////////////////////////////////////////////////////////////////////////////

#endif /* BOARDS_INCLUDE_KEYBOARD_H_ */

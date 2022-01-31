#include "keyboard.h"
#include "board.h"
#include "paddles.h"
#include "cpu.h"
#include "io_addr.h"
#include "led_frame.h"
#include "printer.h"
#include "ram_ctrl.h"
#include "debug.h"
#include "video.h"
#include "sw_switch.h"

#include "pipe.h"
#include "keyboard_drv.h"

//////////////////////////////////////////////////////////////////////////////////////

#define LOCAL_DISASM_OFF            0
#define LOCAL_DISASM_WAITING        1
#define LOCAL_DISASM_ON             2

//////////////////////////////////////////////////////////////////////////////////////

typedef struct key_data_t_
{
	uint8_t keycode;
	bool_t keywaiting;

} keydata_t;

//////////////////////////////////////////////////////////////////////////////////////

static uint8_t 	  key_pressed;
static bool_t     keywaiting;

static bool_t     keyboard_locked;
static bool_t     previous_zoom;
static uint8_t    local_disasm;
static uint8_t    keycode;
static uint8_t    key_control;
//static uint8_t    key_param;

static loop_hdl_t local_loop;

static board_data_t * board;

static bool_t caps_lock;

static pipe_data_t key_pipe;

//////////////////////////////////////////////////////////////////////////////////////

static uint8_t KeybReadData (uint8_t null1, uint8_t null2)
{
	keydata_t * keydata;

	if( ( keywaiting == FALSE ) && ( pipe_is_empty( &key_pipe ) == FALSE ) )
	{
		keydata = ( keydata_t * )pipe_read( &key_pipe, NULL );
		keywaiting = TRUE;
		key_pressed = keydata->keycode;
	}

	return( key_pressed | ( keywaiting ? 0x80 : 0 ) );
}

static uint8_t KeybClearFlag( uint8_t null1, uint8_t null2 )
{
	keywaiting = FALSE;
	return key_pressed;
}

static uint8_t keyboard_loop( uint32_t cycles )
{
	keyb_event_t event;
	keydata_t keydata;

	if( keybdrv_read( &event ) && ( event.mode == KEYB_DOWN ) )
	{
		if( event.flags & ALTGR_FLAG )
		{
		}
		else if( event.flags & WIN_FLAG )
		{
			if( ( event.key >= '0' ) && ( event.key <= '9' ) )
			{
				//disc_drive_select_image( 6, event.key & 0x0F );
			}
			else if( ( event.key == 't' ) || ( event.key == 'T' ) )
			{
				if( cpu_get_turbo_mode() == TRUE ) cpu_turbo_mode( FALSE );
				else cpu_turbo_mode( TRUE );
			}
            #ifdef ENABLE_VIDEO
            else if( ( event.key == 'z' ) || ( event.key == 'Z' ) )
            {
                board->sw_switch[SW_VIDEOZOOM] = board->sw_switch[SW_VIDEOZOOM] ? FALSE : TRUE;
            }
            #endif
			else if( ( event.key == 'r' ) || ( event.key == 'R' ) )
			{
                //ram_reset();
				board_reset();
			}
            else if( ( event.key == 'b' ) || ( event.key == 'B' ) )
            {
                board_print_benchmark( NULL );
            }
            else if( ( event.key == 'q' ) || ( event.key == 'Q' ) )
            {
                board->is_running = FALSE;
            }
		}
		else if( keyboard_locked == FALSE )
		{
            keydata.keycode = event.key;
            keydata.keywaiting = TRUE;

	        if( ( event.flags & CTRL_FLAG ) && ( ( ( keydata.keycode >= 'A' ) && ( keydata.keycode <= 'Z' ) ) ||
	                                             ( ( keydata.keycode >= 'a' ) && ( keydata.keycode <= 'z' ) ) ) )
	        {
	            keydata.keycode &= ~0x20;
	            keydata.keycode -= 'A' - 1;
	        }
	        else if( ( caps_lock == FALSE ) && ( keydata.keycode >= 'A' ) && ( keydata.keycode <= 'Z' ) )
	        {
	            keydata.keycode |= 0x20;
	        }

			pipe_send_buffer( &key_pipe, ( uint8_t * )&keydata, ( uint16_t )sizeof( keydata ) );
		}

		if( ( key_control >= Key_CONTROL ) && ( key_control < Key_FUNC_DEFS ) )
		{
			switch( keycode )
			{
				case Key_FUNCTION:
					key_control = keycode;
					break;

				case Key_RESET:
                    ram_reset();
					board_reset();
					key_control = 0;
					break;

				case Key_CAPSLOCK:
					if( caps_lock == TRUE ) caps_lock = FALSE;
					else caps_lock = TRUE;
					led_show( LED_ID_CAPSLOCK, caps_lock );
					key_control = 0;
					break;

				default:
					key_control = 0;
					break;
			}

			keycode = 0;
		}
	}

	return local_loop( cycles );
}

uint8_t keyboard_read_raw( void )
{
    return keycode;
}

void keyboard_init( void * p_board )
{
	uint32_t counter;

	board = ( board_data_t * )p_board;

	pipe_init( &key_pipe, "KEYAPL", 8 );

	// hook loop handle
	local_loop = board_hook_loop( keyboard_loop );

	keycode         = 0;
	keywaiting      = FALSE;
	key_control     = 0;
	key_pressed     = 0;
	local_disasm    = LOCAL_DISASM_OFF;
	previous_zoom   = FALSE;
	keyboard_locked = FALSE;

	for( counter = 0x00; counter <= 0x0F; counter++ )
	{
		memory_io_set_handler( counter, KeybReadData, NULL );
	}

	memory_io_set_handler( 0x10, KeybClearFlag, KeybClearFlag );

	caps_lock = TRUE;
	led_show( LED_ID_CAPSLOCK, caps_lock );

	for( counter = 0x11; counter <= 0x1F; counter++ )
	{
		memory_io_set_handler( counter, NULL, KeybClearFlag );
	}
}

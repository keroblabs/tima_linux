#include "keyboard_drv.h"
#include "t_threads.h"
#include "pipe.h"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

///////////////////////////////////////////////////////////////////////////

static const char keyb_map[58] =
{
	0x00, 0x1b, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0',  '-',  '=',  127,
	0x09,  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[',  ']',  13,   0x00,
	  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',  0x00, '#',
	  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0x00, 0x00, 0x00, 0x20
};

static const char keyb_map2[58] =
{
	0x00, 0x1b, '!', '\"', '#', '$', '%', '^', '&', '*', '(',  ')',  '_',  '+',  127,
	0x09,  'Q', 'W', 'E',  'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '{',  '}',  0x0d, 0x00,
	  'A', 'S', 'D', 'F',  'G', 'H', 'J', 'K', 'L', ':', '@',  '~',  0x00, '~',
	  'Z', 'X', 'C', 'V',  'B', 'N', 'M', '<', '>', '?', 0x00, 0x00, 0x00, 0x20
};

///////////////////////////////////////////////////////////////////////////

struct termios orig_termios;

typedef struct input_event_t_
{
	struct timeval time;
	unsigned short type;
	unsigned short code;
	unsigned int value;

} input_event_t;

///////////////////////////////////////////////////////////////////////////

static pipe_data_t kbd_pipe;
static mouse_info_t mouse_data;
static bool_t mouse_mode;

///////////////////////////////////////////////////////////////////////////

static int keyboard_fd_open( char * path )
{
	char in_state[3];
	int len;
	int fd;

	fd = open(path, O_RDONLY);
	if( fd == -1 )
	{
		printf( "Failed to open %s\r\n", path );
		return -1;
	}

	return fd;
}

static void keyboard_fd_close( int fd )
{
	close( fd );
}

static int keyboard_fd_read( int fd, input_event_t * event )
{
	int len;

	len = read( fd, event, sizeof( input_event_t ) );
	if( len == -1 )
	{
	    return -1;
	}
	else if( len < sizeof( input_event_t ) )
	{
		printf( "Failed to read event (%d)\r\n", len );
		return -1;
	}

	return 0;
}

static void keyboard_fd_mouse_thread( void * args )
{
	int fd;
	char * path = ( char * )args;
	input_event_t event;

	fd = keyboard_fd_open( path );
	if( fd < 0 ) return;

	while( 1 )
	{
		if( keyboard_fd_read( fd, &event ) == 0 )
		{
		    //printf( "mouse event: %d\n", event.type );

			if( event.type == 2 )
			{
				tthread_mutex_lock( mouse_data.mutex );

				if( event.code == 0 )
				{
					mouse_data.curr_x += (int)event.value;
					if( mouse_data.curr_x < mouse_data.min_x ) mouse_data.curr_x = mouse_data.min_x;
					else if( mouse_data.curr_x > mouse_data.max_x ) mouse_data.curr_x = mouse_data.max_x;
				}
				else if( event.code == 1 )
				{
					mouse_data.curr_y += (int)event.value;
					if( mouse_data.curr_y < mouse_data.min_y ) mouse_data.curr_y = mouse_data.min_y;
					else if( mouse_data.curr_y > mouse_data.max_y ) mouse_data.curr_y = mouse_data.max_y;
				}

				mouse_data.is_update = TRUE;

				tthread_mutex_unlock( mouse_data.mutex );

				//printf( "mouse = %4d %4d %d %d\r\n", event.type, event.code, mouse_data.curr_x, mouse_data.curr_y );
			}
			else if( event.type == 1 )
			{
				uint8_t mask = 0;

				switch( event.code )
				{
					case 113: mask = RESET_FLAG; break;
					case 114: mask = FUNCTION_FLAG; break;
					case 272: mask = OPENAPL_FLAG; break;
					case 273: mask = CLOSEAPL_FLAG; break;
				}

				if( mask )
				{
					tthread_mutex_lock( mouse_data.mutex );

					if( event.value ) mouse_data.flags |= mask;
					else mouse_data.flags &= ~mask;

					tthread_mutex_unlock( mouse_data.mutex );
				}
				else
				{
					tthread_mutex_lock( mouse_data.mutex );

					switch( event.code )
					{
						case 165: mouse_data.delta_x = 128 - (120 * event.value ); break;
						case 163: mouse_data.delta_x = 128 + (120 * event.value ); break;
						case 164: mouse_data.delta_y = 128 - (120 * event.value ); break;
						case 166: mouse_data.delta_y = 128 + (120 * event.value ); break;
					}

					tthread_mutex_unlock( mouse_data.mutex );
				}

				//printf( "mouse = %4d %4d %d\r\n", event.type, event.code, (int)event.value );
			}

			//if( ( event.type == 1 ) && ( ( event.value == 0 ) || ( event.value == 1 ) ) )
				//printf( "mouse = %4d %4d %d\r\n", event.type, event.code, (int)event.value );
		}
	}
}

static void keyboard_fd_thread( void * args )
{
	int fd;
	char * path = ( char * )args;
	input_event_t event;
	keyb_event_t kbd_event;
	uint8_t mask;

	fd = keyboard_fd_open( path );
	if( fd < 0 ) return;

	kbd_event.mode = 0;
	kbd_event.flags = 0;

	while( 1 )
	{
		if( keyboard_fd_read( fd, &event ) == 0 )
		{
            //printf( "keyboard event: %d\n", event.type );

			if( ( event.type == 1 ) && ( ( event.value == 0 ) || ( event.value == 1 ) ) )
			{
				mask = 0;

				switch( event.code )
				{
					case 42:  mask = SHIFT_FLAG; break;
					case 29:  mask = CTRL_FLAG;  break;
					case 97:  mask = CTRL2_FLAG; break;
					case 125: mask = WIN_FLAG;   break;
					case 56:  mask = ALT_FLAG;   break;
					case 100: mask = ALTGR_FLAG; break;

					case 58:
						if( event.value == 1 )
						{
							if( kbd_event.flags & CAPS_FLAG ) kbd_event.flags &= ~CAPS_FLAG;
							else kbd_event.flags |= CAPS_FLAG;
						}
						break;
				}

				if( mask )
				{
					if( event.value ) kbd_event.flags |= mask;
					else kbd_event.flags &= ~mask;

					kbd_event.mode = KEYB_NONE;
					pipe_send_data( &kbd_pipe, ( uint8_t * )&kbd_event, sizeof( keyb_event_t ) );
				}
				else if( event.code <= 57 )
				{
					if( kbd_event.flags & SHIFT_FLAG ) kbd_event.key = keyb_map2[ event.code ];
					else kbd_event.key = keyb_map[ event.code ];

					if( ( kbd_event.key >= 'A' ) && ( kbd_event.key <= 'Z' ) )
					{
						if( ( kbd_event.flags & CAPS_FLAG ) || ( kbd_event.flags & SHIFT_FLAG ) ) kbd_event.key &= ~0x20;
						else kbd_event.key |= 0x20;
					}

					kbd_event.mode = event.value ? KEYB_DOWN : KEYB_UP;
					pipe_send_data( &kbd_pipe, ( uint8_t * )&kbd_event, sizeof( keyb_event_t ) );
				}
				else
				{
					bool_t is_pressed = TRUE;

					switch( event.code )
					{
						case 103: /* up */    kbd_event.key = 11; break;
						case 108: /* down */  kbd_event.key = 10; break;
						case 106: /* right */ kbd_event.key = 21; break;
						case 105: /* left */  kbd_event.key = 8; break;
						default: is_pressed = FALSE; break;
					}

					if( is_pressed )
					{
						kbd_event.mode = event.value ? KEYB_DOWN : KEYB_UP;
						pipe_send_data( &kbd_pipe, ( uint8_t * )&kbd_event, sizeof( keyb_event_t ) );
					}
				}
			}

			//if( ( event.type == 1 ) && ( ( event.value == 0 ) || ( event.value == 1 ) ) )
			//	printf( "event = %4d %4d %4x\r\n", event.type, event.code, event.value );
		}
	}
}

void keybdrv_mouse_set_limits( uint16_t min_x, uint16_t max_x, uint16_t min_y, uint16_t max_y )
{
	tthread_mutex_lock( mouse_data.mutex );

	mouse_data.max_x = (int)max_x;
	mouse_data.min_x = (int)min_x;
	mouse_data.max_y = (int)max_y;
	mouse_data.min_y = (int)min_y;

	tthread_mutex_unlock( mouse_data.mutex );
}

void keybdrv_mouse_set_pos( uint16_t posx, uint16_t posy )
{
	tthread_mutex_lock( mouse_data.mutex );

	mouse_data.curr_x = (int)posx;
	mouse_data.curr_y = (int)posy;

	tthread_mutex_unlock( mouse_data.mutex );
}

void keybdrv_mouse_get_joystick( uint16_t * posx, uint16_t * posy )
{
	tthread_mutex_lock( mouse_data.mutex );

	if( mouse_mode == TRUE )
	{
	    *posx = (uint16_t)( mouse_data.curr_x );
	    *posy = (uint16_t)( mouse_data.curr_y );
	}
	else
	{
	    *posx = (uint16_t)( mouse_data.delta_x );
	    *posy = (uint16_t)( mouse_data.delta_y );
	}

	tthread_mutex_unlock( mouse_data.mutex );
}

void keybdrv_joystick_set_mouse_mode( bool_t state )
{
    mouse_mode = state;
}

bool_t keybdrv_mouse_get_pos( uint16_t * posx, uint16_t * posy )
{
	bool_t ret;

	tthread_mutex_lock( mouse_data.mutex );

	*posx = (uint16_t)mouse_data.curr_x;
	*posy = (uint16_t)mouse_data.curr_y;

	ret = mouse_data.is_update;
	mouse_data.is_update = FALSE;

	tthread_mutex_unlock( mouse_data.mutex );

	return ret;
}

bool_t keybdrv_check( void )
{
	if( pipe_is_empty( &kbd_pipe ) == FALSE )
	{
		return TRUE;
	}

	return FALSE;
}

bool_t keybdrv_read( keyb_event_t * event )
{
	if( pipe_is_empty( &kbd_pipe ) == FALSE )
	{
		pipe_read_buffer( &kbd_pipe, ( uint8_t * )event, sizeof( keyb_event_t ) );
		return TRUE;
	}

	return FALSE;
}

bool_t keybdrv_read_button0( void )
{
	bool_t ret;

	tthread_mutex_lock( mouse_data.mutex );
	ret = mouse_data.flags & OPENAPL_FLAG ? TRUE : FALSE;
	tthread_mutex_unlock( mouse_data.mutex );

	return ret;
}

bool_t keybdrv_read_button1( void )
{
	bool_t ret;

	tthread_mutex_lock( mouse_data.mutex );
	ret = mouse_data.flags & CLOSEAPL_FLAG ? TRUE : FALSE;
	tthread_mutex_unlock( mouse_data.mutex );

	return ret;
}

void keybdrv_init( void )
{
	pipe_init( &kbd_pipe, "KBD_PIPE", 16 );

	mouse_data.mutex = tthread_mutex_init();
	mouse_data.min_x = mouse_data.min_y = 0;
	mouse_data.max_x = mouse_data.max_y = 255;
	mouse_data.delta_x = mouse_data.delta_x = 128;
	mouse_data.curr_x  = mouse_data.curr_y  = 128;
	mouse_data.is_update = FALSE;

	mouse_mode = FALSE;

	tthread_create_ex( keyboard_fd_mouse_thread, "/dev/input/event2" );
	tthread_create_ex( keyboard_fd_thread, "/dev/input/event1" );
}

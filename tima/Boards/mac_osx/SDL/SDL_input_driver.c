#include "SDL_internal.h"
#include "device.h"
#include "system.h"
#include "keyboard_drv.h"

////////////////////////////////////////////////////////////////////

#ifdef WIN32
#define GETCH   _getch
#else
#define GETCH   getchar
#endif

#ifdef WIN32
#define KBHIT    _kbhit
#else
#define KBHIT    sdl_library_kbhit
#endif

////////////////////////////////////////////////////////////////////

static bool_t button0 = FALSE;
static bool_t button1 = FALSE;
static bool_t temp_key_code;
static uint8_t key_code;
static uint8_t key_flag;
static uint8_t key_mask = 0;
static bool_t is_init = FALSE;
static sdl_loop_t kbd_loop;

////////////////////////////////////////////////////////////////////

#if defined __MACH__
int sdl_library_kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}
#endif

////////////////////////////////////////////////////////////////////

void sdl_input_init( void )
{
    key_flag = 0;
    key_code = 0;
}

void sdl_input_event( void )
{
    if( KBHIT() != 0 )
    {
    }
}

uint8_t sdl_keyRead( void )
{
    key_flag = 0;
    return key_code;
}

uint8_t sdl_keyCheck( void )
{
    return key_flag;
}

int sdl_getch( void )
{
    static int prev_ch = 0;
    
    int new_ch = GETCH();
    
    if( prev_ch == 0xE0 )
    {
        prev_ch = 0;
        if( new_ch == 0x4b )
        {
            return 0x08;
        }
        else if( new_ch == 0x4d )
        {
            return 0x0D;
        }
    }
    else if( prev_ch == 0 )
    {
        if( new_ch == 0xE0 ) prev_ch = new_ch;
        else return new_ch;
    }
    
    return 0;
}

/* SDL event handler */
void sdl_text_input_event( uint8_t keycode )
{
    // remap delete key
    if( keycode == 0x08 ) keycode = 0x7F;
    if( keycode == 0xC2 ) keycode = '#';
    
    //if( ( key_code >= 'A' ) && ( key_code <= 'Z' ) )
    //{
    //    key_code |= 0x20;
    //}
    
    key_code = keycode;
    key_flag = 1;
    //printf( "key code = %04x\n", _event.type );
}

typedef struct translate_key_t_
{
    SDL_Keycode sdl;
    uint8_t key_code;
    
} translate_key_t;

const static translate_key_t sdl_translate[] =
{
    { SDLK_ESCAPE, 0x1B },
    { SDLK_DOWN,   10   },
    { SDLK_UP,     11   },
    { SDLK_LEFT,   8    },
    { SDLK_RIGHT,  21   },
    
    { 13         , 13   },
    { 9          , 9    },
    { 8          , 8 },
    { SDLK_DELETE, 2    },
    { SDLK_ESCAPE, 0x1B },
    { 0xC2       , '#'  },
    { 127        , 0x7F },
    { 0          , 0    },
};

static uint8_t translate_key( SDL_Keycode sym )
{
    int index = 0;
    while( sdl_translate[index].sdl != 0 )
    {
        if( sdl_translate[index].sdl == sym ) return sdl_translate[index].key_code;
        index++;
    }
    
    return 0;
}

/* SDL event handler */
void sdl_keypad_down_event( SDL_Keycode sym, Uint32 type )
{
    uint8_t read_key;
    
    switch( sym )
    {
        case SDLK_LALT:
            button0 = ( type == SDL_KEYDOWN ) ? TRUE : FALSE;
            break;

        case SDLK_RALT:
            button1 = ( type == SDL_KEYDOWN ) ? TRUE : FALSE;
            break;
            
        case SDLK_LGUI:
            if( type == SDL_KEYDOWN ) key_mask |= WIN_FLAG;
            else key_mask &= ~WIN_FLAG;
            break;
            
        case SDLK_LCTRL:
        case SDLK_RCTRL:
            if( type == SDL_KEYDOWN ) key_mask |= CTRL_FLAG;
            else key_mask &= ~CTRL_FLAG;
            break;
            
        case SDLK_CAPSLOCK:
            if( type == SDL_KEYDOWN )
            {
                if( key_mask & CAPS_FLAG ) key_mask &= ~CAPS_FLAG;
                else key_mask |= CAPS_FLAG;
            }
            break;
            
        default:
            if( type == SDL_KEYDOWN )
            {
                read_key = translate_key( sym );
                if( read_key != 0 )
                {
                    key_code = read_key;
                    key_flag = 1;
                }
                else if( ( sym >= 0x20 ) && ( sym <= 125 ) )
                {
                    key_code = sym;
                    key_flag = 1;
                }
            }
            break;
    }
}

///////////////////////////////////////////////////////////////

static bool_t keypad_validate( uint32_t index )
{
    if( index == 0 ) return TRUE;
    return FALSE;
}

static void keypad_init( uint32_t index )
{
    if( is_init == FALSE )
    {
        kbd_loop.handler = sdl_input_event;
        sdl_add_event_loop( &kbd_loop );
        is_init = TRUE;
    }
}

static int keypad_read_byte( uint32_t socket, uint8_t *buffer, uint32_t max_size )
{
    int ret;
    
    ret = (int)key_flag;
    if( ( buffer != NULL ) && key_flag )
    {
        key_flag = 0;
        *buffer = key_code;
    }
    
    return ret;
}

void keybdrv_init( void )
{
}

bool_t keybdrv_read( keyb_event_t * event )
{
    bool_t ret = key_flag;
    
    if( key_flag == TRUE )
    {
        key_flag = FALSE;
        event->key = key_code;
        event->mode = KEYB_DOWN;
        event->flags = key_mask;
    }
    
    return ret;
}

void keybdrv_mouse_read_joystick( uint16_t * posx, uint16_t * posy )
{
    *posx = 128;
    *posy = 128;
}

bool_t keybdrv_read_button0( void )
{
    return button0;
}

bool_t keybdrv_read_button1( void )
{
    return button1;
}

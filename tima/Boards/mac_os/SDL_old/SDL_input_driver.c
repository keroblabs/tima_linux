#include "SDL_internal.h"
#include "device.h"
#include "system.h"

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

static uint8_t key_code;
static uint8_t key_flag;
static bool_t is_init = FALSE;
static sdl_loop_t key_loop;

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

static void sdl_input_event( void )
{
    if( KBHIT() != 0 )
    {
    }
}

/* SDL event handler */
static void sdl_text_input_event( uint8_t keycode )
{
    // remap delete key
    if( key_code == 0x08 ) key_code = 0x7F;
    if( key_code == 0xC2 ) key_code = '#';
    
    //if( ( key_code >= 'A' ) && ( key_code <= 'Z' ) )
    //{
    //    key_code |= 0x20;
    //}
    
    key_flag = 1;
    //printf( "key code = %04x\n", _event.type );
}

/* SDL event handler */
static void sdl_keypad_down_event( SDL_Keycode sym )
{
    if( sym == SDLK_ESCAPE )
    {
        // esq
        key_code = 0x1B;
        key_flag = 1;
    }
    else if( sym == SDLK_DOWN )
    {
        key_code = 10;
        key_flag = 1;
    }
    else if( sym == SDLK_UP )
    {
        key_code = 11;
        key_flag = 1;
    }
    else if( sym == SDLK_LEFT )
    {
        key_code = 8;
        key_flag = 1;
    }
    else if( sym == SDLK_RIGHT )
    {
        key_code = 21;
        key_flag = 1;
    }
    else if( sym == 13 )
    {
        // enter
        key_code = 13;
        key_flag = 1;
    }
    else if( sym == 9 )
    {
        // tab
        key_code = 9;
        key_flag = 1;
    }
    else if( sym == 8 )
    {
        // backspace
        key_code = 0x7E;
        key_flag = 1;
    }
    else if( sym == SDLK_DELETE )
    {
        // del
        key_code = 0x02;
        key_flag = 1;
    }
}

int sdl_get_char( void )
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

uint8_t sdl_input_read_key( void )
{
    key_flag = 0;
    return key_code;
}

uint8_t sdl_input_key_check( void )
{
    return key_flag;
}

void sdl_input_read_init( void )
{
    if( is_init == FALSE )
    {
        key_flag = 0;
        key_code = 0;
        
        key_loop.handler = sdl_input_event;
        sdl_add_event_loop( &key_loop );
        
        sdl_set_keydown_event( sdl_keypad_down_event );
        sdl_set_text_input_event( sdl_text_input_event );
        
        is_init = TRUE;
    }
}

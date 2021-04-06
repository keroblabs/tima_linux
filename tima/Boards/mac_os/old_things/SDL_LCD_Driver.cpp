//Using SDL and standard IO

#ifdef WIN32
#include <SDL.h>
#include <Windows.h>
#include <conio.h>
#elif defined __MACH__
#include <SDL2/SDL.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include "types.h"
#include "keyboard_drv.h"
//#include "device.h"
//#include "system.h"
//#include "lcd.h"

extern "C" { int ui_is_window_ready( void ); }

///////////////////////////////////////////////////////////////

#define VSYNC_RATE_HZ		50
#define VSYNC_PERIOD_MS		( 1000 / VSYNC_RATE_HZ )
#define VSYNC_PERIOD(r)		( 1000 / r )

#ifdef WIN32
#define KBHIT	_kbhit
#define GETCH   _getch
#else
#define KBHIT	kbhit
#define GETCH   getchar
#endif

#define SDL_SCREEN_WIDTH		800
#define SDL_SCREEN_HEIGHT		480

///////////////////////////////////////////////////////////////

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer * screenRenderer = NULL;
SDL_Texture * screenTexture = NULL;

unsigned int mouse_x;
unsigned int mouse_y;
unsigned int mouse_button;
unsigned int mouse_trigg;

Uint32 vsync_ms;
SDL_bool is_updated;

static bool_t v_sync;
static uint8_t key_code;
static uint8_t key_flag;

static bool_t is_loaded;

///////////////////////////////////////////////////////////////

#if defined __MACH__
int kbhit(void)
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

uint8_t sdl_keyRead( void )
{
	key_flag = 0;
	return key_code;
}

uint8_t sdl_keyCheck( void )
{
	return key_flag;
}

bool_t keybdrv_check( void )
{
    return key_flag;
}

bool_t keybdrv_read( keyb_event_t * event )
{
    bool_t ret = key_flag;
    key_flag = FALSE;
    
    event->key = key_code;
    event->flags = 0;
    event->mode = KEYB_DOWN;
    
    return ret;
}

void keybdrv_init( void )
{
    
}

void keybdrv_mouse_get_joystick( uint16_t * posx, uint16_t * posy )
{
    *posx = 0x80;
    *posy = 0x80;
}

bool_t keybdrv_read_button0( void )
{
    return FALSE;
}

bool_t keybdrv_read_button1( void )
{
    return FALSE;
}

void sdl_update_window( void )
{
	if( screenSurface == NULL ) return;

	v_sync = TRUE;

	SDL_UpdateTexture( screenTexture, NULL, screenSurface->pixels, screenSurface->pitch );
	SDL_RenderClear( screenRenderer );
	SDL_RenderCopy( screenRenderer, screenTexture, NULL, NULL );
	SDL_RenderPresent( screenRenderer );
}

int create_window( void )
{
	Uint32 r_mask, g_mask, b_mask, a_mask;
	int bpp;

	SDL_PixelFormatEnumToMasks( SDL_PIXELFORMAT_RGBX8888, &bpp, &r_mask, &g_mask, &b_mask, &a_mask );

    //Create window
    window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, 0 );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
    }

	// create renderer
	screenRenderer = SDL_CreateRenderer( window, -1, 0 );
	if( screenRenderer == NULL )
	{
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

    //Get window surface
	screenSurface = SDL_CreateRGBSurface(0,SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, bpp, r_mask, g_mask, b_mask, a_mask);
	if( screenSurface == NULL )
	{
        printf( "Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	screenTexture = SDL_CreateTexture( screenRenderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT);
	if( screenSurface == NULL )
	{
        printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	vsync_ms = SDL_GetTicks() + VSYNC_PERIOD_MS;

	return 0;
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

int sdl_event_loop( void )
{
	//Event handler
    SDL_Event e;

	// console keyboard
	if( KBHIT() != 0 )
	{
	}
    
    // vsync
    if( SDL_GetTicks() > vsync_ms )
    {
        vsync_ms = SDL_GetTicks() + VSYNC_PERIOD_MS;
        sdl_update_window();
    }

	//Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
		switch( e.type )
		{
            case SDL_TEXTINPUT:
                key_code = ( uint8_t )e.text.text[0];

                // remap delete key
                if( key_code == 0x08 ) key_code = 0x7F;
				if( key_code == 0xC2 ) key_code = '#';

				//if( ( key_code >= 'A' ) && ( key_code <= 'Z' ) )
				//{
				//	key_code |= 0x20;
				//}
                
                key_flag = 1;
                //printf( "key code = %04x\n", _event.type );
                break;

			case SDL_KEYDOWN:
				if( e.key.keysym.sym == SDLK_ESCAPE )
				{
					// esq
					key_code = 0x1B;
					key_flag = 1;
				}
				else if( e.key.keysym.sym == SDLK_DOWN )
				{
					key_code = 10;
					key_flag = 1;
				}
				else if( e.key.keysym.sym == SDLK_UP )
				{
					key_code = 11;
					key_flag = 1;
				}
				else if( e.key.keysym.sym == SDLK_LEFT )
				{
					key_code = 8;
					key_flag = 1;
				}
				else if( e.key.keysym.sym == SDLK_RIGHT )
				{
					key_code = 21;
					key_flag = 1;
				}
				else if( e.key.keysym.sym == 13 )
                {
                    // enter
					key_code = 13;
					key_flag = 1;
                }
				else if( e.key.keysym.sym == 9 )
                {
                    // tab
					key_code = 9;
					key_flag = 1;
                }
                else if( e.key.keysym.sym == 8 )
                {
                    // backspace
					key_code = 0x7E;
					key_flag = 1;
                }
				else if( e.key.keysym.sym == SDLK_DELETE )
				{
					// del
					key_code = 0x02;
					key_flag = 1;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_x = e.button.x;
				mouse_y = e.button.y;
				if( e.button.button == SDL_BUTTON_LEFT )
				{
					mouse_button = 1;
				}
				else if( e.button.button == SDL_BUTTON_RIGHT ) 
				{
					mouse_button = 2;
				}
				else break;
				mouse_trigg = 1;
				break;

			case SDL_MOUSEBUTTONUP:
				if( mouse_button == 0 ) break;
				mouse_button = 0;
				mouse_x = e.button.x;
				mouse_y = e.button.y;
				mouse_trigg = 1;
				break;

			case SDL_MOUSEMOTION:
				// uncomment the line below to enable touchscreen mode
				// comment the line below to enable mouse mode
				if( mouse_button == 0 ) break;

				mouse_x = e.button.x;
				mouse_y = e.button.y;
				mouse_trigg = 1;
				break;

			case SDL_QUIT:
				//System_PowerDown();
				break;
		}
	}

	return 1;
}

int sdl_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
	if( mouse_trigg == 1 )
	{
		mouse_trigg = 0;

		*posx = ( unsigned short )mouse_x;
		*posy = ( unsigned short )mouse_y;
		*posz = 0;

		if( mouse_button ) *posz = 100;
		return 1;
	}

	return 0;
}

void ms_timer_init( void )
{    
}

uint32_t * lcd_driver_get_buffer( void )
{
    return ( uint32_t * )screenSurface->pixels;
}

uint32_t ms_timer_get_ms( void )
{
	return SDL_GetTicks();
}

uint32_t ms_timer_get_us( void )
{
    return SDL_GetTicks() * 1000;
}

uint16_t lcd_driver_width( void )
{
    return SDL_SCREEN_WIDTH;
}

uint16_t lcd_driver_height( void )
{
    return SDL_SCREEN_HEIGHT;
}

int lcd_driver_init( void )
{
    while( !ui_is_window_ready() )
    {
        usleep(10000);
    }
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
    }

    is_loaded = FALSE;
	key_flag = 0;
	key_code = 0;
	v_sync = FALSE;

	// create window
	if( create_window() == -1 )
	{
        printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -2;
	}

	// uncomment the line below to enable touchscreen mode
	// comment the line below to enable mouse mode
	//SDL_ShowCursor(SDL_DISABLE);

    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) );
	is_updated = SDL_TRUE;

    //Update the surface
    SDL_UpdateWindowSurface( window );

	mouse_trigg = 0;
	mouse_button = 0;
    
    return 0;
}

void lcd_driver_process( void )
{
	sdl_event_loop();
}

void sdl_exit( void )
{
	SDL_ShowCursor(SDL_ENABLE);

	//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

#if defined __MACH__
int SDL_main( int argc, char* argv[] )
#else
int main( int argc, char* argv[] )
#endif
{
    int _fe_main( void );
    return _fe_main();
}

///////////////////////////////////////////////////////////////


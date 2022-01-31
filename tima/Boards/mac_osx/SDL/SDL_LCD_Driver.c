#include "SDL_internal.h"
#include "types.h"
#include "device.h"
#include "system.h"
#include "lcd.h"
#include "pipe.h"

#include <sys/time.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////

#define VSYNC_RATE_HZ		50
#define VSYNC_PERIOD_MS		( 1000 / VSYNC_RATE_HZ )
#define VSYNC_PERIOD(r)		( 1000 / r )

#define SDL_SCREEN_WIDTH		_USE_SCREEN_WIDTH
#define SDL_SCREEN_HEIGHT		(_USE_SCREEN_HEIGHT + 80)

#ifdef TIMA_LINUX
#define SDL_PIXEL_FORMAT SDL_PIXELFORMAT_XRGB8888
#define PIXEL_TYPE_T     uint32_t
#else
#define SDL_PIXEL_FORMAT SDL_PIXELFORMAT_RGB565
#define PIXEL_TYPE_T     uint16_t
#endif

///////////////////////////////////////////////////////////////

static bool_t is_init = FALSE;
static sdl_loop_t lcd_loop;
static uint32_t background_counter = 0;
static struct timeval us_start;
static bool_t us_init_done = FALSE;

///////////////////////////////////////////////////////////////

static void init_microsecond_timer( void )
{
    if( us_init_done == FALSE )
    {
        gettimeofday( &us_start, NULL );
        us_init_done = TRUE;
    }
}

static void sdl_update_window( void * p_data )
{
    window_data_t * window_data = ( window_data_t * )p_data;
    
    SDL_UpdateTexture( window_data->texture, NULL, window_data->surface->pixels, window_data->surface->pitch );
    SDL_RenderClear( window_data->renderer );
    SDL_RenderCopy( window_data->renderer, window_data->texture, NULL, NULL );
    SDL_RenderPresent( window_data->renderer );
}

void ms_timer_hw_global_init( void )
{
}

uint32_t ms_timer_hw_get_ms( void )
{
    return SDL_GetTicks();
}

uint64_t ms_timer_hw_get_us( void )
{
    struct timeval ms_value;
    long mtime, seconds, useconds;

    gettimeofday( &ms_value, NULL );

    seconds = ms_value.tv_sec - us_start.tv_sec;
    useconds = ms_value.tv_usec - us_start.tv_usec;
    mtime = ( seconds * 1000000 ) + useconds;

    return ( uint64_t )mtime;
}

PIXEL_TYPE_T * sdl_GetTarget( void )
{
    window_data_t * window_data = sdl_get_window_data();
    if( window_data == NULL ) return NULL;
    
    return ( PIXEL_TYPE_T * )window_data->surface->pixels;
}

void sdl_lcd_init( void )
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
}

void sdl_lcd_stop( void )
{
    window_data_t * window_data = sdl_get_window_data();
    if( window_data == NULL ) return;
    
    SDL_ShowCursor(SDL_ENABLE);
    
    //Destroy window
    SDL_DestroyWindow( window_data->window );
    
    //Quit SDL subsystems
    SDL_Quit();
}

static void sdl_vsync_event( void )
{
    #ifdef WANT_MULTI_INSTANCES
    int cnt;
    for( cnt = 0; cnt < MAX_INSTANCES; cnt++ )
    {
        instance_data_t * instance = sdl_get_instance_from_index( cnt );
        if( instance != NULL )
        {
            window_data_t * window_data = &instance->window_data;
            if( window_data == NULL ) return;
            
            if( ( window_data->window != NULL ) && ( SDL_GetTicks() > window_data->vsync_ms ) )
            {
                window_data->vsync_ms = SDL_GetTicks() + VSYNC_PERIOD_MS;
                sdl_update_window( window_data );
            }
        }
    }
    #else
    window_data_t * window_data = sdl_get_window_data();

    if( ( window_data->window != NULL ) && ( SDL_GetTicks() > window_data->vsync_ms ) )
    {
        window_data->vsync_ms = SDL_GetTicks() + VSYNC_PERIOD_MS;
        sdl_update_window( window_data );
    }
    #endif
}

static int create_window( window_data_t * window_data )
{
	Uint32 r_mask, g_mask, b_mask, a_mask;
	int bpp;

    if( window_data == NULL )
    {
        printf( "Window could not be created! \n" );
        return -1;
    }

	SDL_PixelFormatEnumToMasks( SDL_PIXEL_FORMAT, &bpp, &r_mask, &g_mask, &b_mask, &a_mask );

    //Create window
    window_data->window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, 0 );
    if( window_data->window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
    }

	// create renderer
	window_data->renderer = SDL_CreateRenderer( window_data->window, -1, 0 );
	if( window_data->renderer == NULL )
	{
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

    //Get window surface
	window_data->surface = SDL_CreateRGBSurface(0,SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, bpp, r_mask, g_mask, b_mask, a_mask);
	if( window_data->surface == NULL )
	{
        printf( "Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	window_data->texture = SDL_CreateTexture( window_data->renderer, SDL_PIXEL_FORMAT, SDL_TEXTUREACCESS_STREAMING, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT);
	if( window_data->texture == NULL )
	{
        printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	window_data->vsync_ms = SDL_GetTicks() + VSYNC_PERIOD_MS;

	return 0;
}

static void sdl_init_internal( void * param )
{
    if( is_init == FALSE )
    {
        lcd_loop.handler = sdl_vsync_event;
        sdl_add_event_loop( &lcd_loop );
        is_init = TRUE;
    }
    
    window_data_t * window_data = ( window_data_t * )param;

	// create window
	if( create_window( window_data ) == -1 )
	{
        printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return;
	}

	// uncomment the line below to enable touchscreen mode
	// comment the line below to enable mouse mode
	//SDL_ShowCursor(SDL_DISABLE);

    //Fill the surface white
    SDL_FillRect( window_data->surface, NULL, SDL_MapRGB( window_data->surface->format, 0, 0, 0 ) );

    //Update the surface
    SDL_UpdateWindowSurface( window_data->window );
}

#ifndef WANT_MULTI_INSTANCES
static void sdl_init( void )
{
    sdl_init_internal( sdl_get_window_data() );
}
#endif

static void sdl_driver_update_window( void )
{
    window_data_t * window_data = sdl_get_window_data();
    sdl_instance_send_message( SDL_INTERNAL_DELEGATE, sdl_update_window, window_data );
}

static void sdl_init_safe( void )
{
    window_data_t * window_data = sdl_get_window_data();
    sdl_instance_send_message( SDL_INTERNAL_DELEGATE, sdl_init_internal, window_data );
}

static bool_t sdl_lcd_init_process( void )
{
    return FALSE;
}

///////////////////////////////////////////////////////////////

int lcd_driver_init( void )
{
    sdl_init();
    return 0;
}

int lcd_driver_mouse_init( const char * dev )
{
    return 0;
}

void sdl_clear_screen( void )
{
}

void sdl_set_contrast( uint8_t level )
{
}

void sdl_set_backlight( bool_t state )
{
}

void lcd_driver_release_frame( void )
{
}

void lcd_driver_process( void )
{
    if( ++background_counter > 1024 )
    {
        sdl_startup_background();
        background_counter = 0;
    }
}

PIXEL_TYPE_T * lcd_driver_get_buffer( void )
{
    return sdl_GetTarget();
}

uint16_t lcd_driver_width( void )
{
    return SDL_SCREEN_WIDTH;
}

uint16_t lcd_driver_height( void )
{
    return SDL_SCREEN_HEIGHT;
}

///////////////////////////////////////////////////////////////

#if defined TIMA_OS
static const lcd_driver_t sdl_lcd_driver = 
{
	SDL_SCREEN_WIDTH,
	SDL_SCREEN_HEIGHT,

#ifdef WANT_MULTI_INSTANCES
    sdl_init_safe,
#else
	sdl_init,
#endif
    
	sdl_clear_screen,
	sdl_lcd_stop,
	sdl_driver_update_window,
	sdl_lcd_init_process,

	sdl_set_contrast,
	sdl_set_backlight,

	sdl_GetTarget,

	NULL,

	NULL,
	NULL,
	NULL,
	NULL,

	sdl_read_mouse
};

///////////////////////////////////////////////////////////////

SYSTEM_DRIVER_DEFINE( lcd_driver_t, sdl_lcd_driver, lcd, "lcd", NULL );
#endif

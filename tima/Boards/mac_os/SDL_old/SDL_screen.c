#include "SDL_internal.h"
#include "types.h"
#include "device.h"
#include "system.h"
#include "lcd.h"
#include "pipe.h"

///////////////////////////////////////////////////////////////

#define VSYNC_RATE_HZ		50
#define VSYNC_PERIOD_MS		( 1000 / VSYNC_RATE_HZ )
#define VSYNC_PERIOD(r)		( 1000 / r )

#define SDL_SCREEN_WIDTH		_USE_SCREEN_WIDTH
#define SDL_SCREEN_HEIGHT		_USE_SCREEN_HEIGHT

#if LCD_PIXEL_SIZE==32
#define SDL_PIXEL_CONFIG SDL_PIXELFORMAT_RGBA8888
#elif LCD_PIXEL_SIZE==16
#define SDL_PIXEL_CONFIG SDL_PIXELFORMAT_RGB565
#else
#error "Unknown pixel configuration"
#endif

///////////////////////////////////////////////////////////////

static bool_t is_init = FALSE;
static sdl_loop_t lcd_loop;

///////////////////////////////////////////////////////////////

static void sdl_update_window_internal( void * p_data )
{
    window_data_t * window_data = ( window_data_t * )p_data;
    
    SDL_UpdateTexture( window_data->texture, NULL, window_data->surface->pixels, window_data->surface->pitch );
    SDL_RenderClear( window_data->renderer );
    SDL_RenderCopy( window_data->renderer, window_data->texture, NULL, NULL );
    SDL_RenderPresent( window_data->renderer );
}

static void sdl_vsync_event( void )
{
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
                sdl_update_window_internal( window_data );
            }
        }
    }
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

	SDL_PixelFormatEnumToMasks( SDL_PIXELFORMAT_RGB565, &bpp, &r_mask, &g_mask, &b_mask, &a_mask );

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
    
	window_data->texture = SDL_CreateTexture( window_data->renderer, SDL_PIXEL_CONFIG, SDL_TEXTUREACCESS_STREAMING, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT);
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
    window_data_t * window_data = ( window_data_t * )param;
    
    if( is_init == FALSE )
    {
        lcd_loop.handler = sdl_vsync_event;
        sdl_add_event_loop( &lcd_loop );
        is_init = TRUE;
    }

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

void sdl_screen_init( void )
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
}

void sdl_screen_stop( void )
{
    window_data_t * window_data = sdl_get_window_data();
    if( window_data == NULL ) return;
    
    SDL_ShowCursor(SDL_ENABLE);
    
    //Destroy window
    SDL_DestroyWindow( window_data->window );
    
    //Quit SDL subsystems
    SDL_Quit();
}

void sdl_lcd_init( void )
{
    window_data_t * window_data = sdl_get_window_data();
    sdl_instance_send_message( SDL_INTERNAL_DELEGATE, sdl_init_internal, window_data );
}

void sdl_update_window( void )
{
    window_data_t * window_data = sdl_get_window_data();
    sdl_instance_send_message( SDL_INTERNAL_DELEGATE, sdl_update_window_internal, window_data );
}

void * sdl_GetTarget( void )
{
    window_data_t * window_data = sdl_get_window_data();
    if( window_data == NULL ) return NULL;
    
    return window_data->surface->pixels;
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

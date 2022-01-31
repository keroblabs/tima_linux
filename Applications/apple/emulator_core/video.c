#include "sw_switch.h"
#include "char_map.h"
#include "timer.h"
#include "io_addr.h"
#include "ram_ctrl.h"
#include "video.h"
#include "draw.h"
#include "led_frame.h"

//////////////////////////////////////////////////////////////////////////////////////

typedef uint32_t ( *video_dma_hdl_t )( void );

#define VIDEO_HZ                    40

#if (LCD_WIDTH == 1140) || (LCD_WIDTH == 1280)
#define VIDEO_RESCALE_SIZE          56
#define ENABLE_80COL_VIDEO
#define VIDEO_CENTRED
#elif LCD_WIDTH == 1024
#define VIDEO_RESCALE_SIZE			50
#define ENABLE_80COL_VIDEO
#elif LCD_WIDTH == 800
#define VIDEO_RESCALE_SIZE			39
#define ENABLE_80COL_VIDEO
#elif LCD_WIDTH == 640
#define VIDEO_RESCALE_SIZE			31
#define ENABLE_80COL_VIDEO
#elif LCD_WIDTH == 480
#define DONT_ENABLE_80COL_VIDEO
#define VIDEO_STREAM_SIZE			28
#elif LCD_WIDTH == 320
#define DONT_ENABLE_80COL_VIDEO
#define VIDEO_RESCALE_SIZE			28
#else
#error "Unsupported LCD"
#endif

#define VIDEO_RATE_MAX_ITEM			100

#if LCD_HEIGHT == 800
#define VIDEO_ZOOM_HEIGHT           2
#define VIDEO_ZOOM_INCREMENT        1
#elif LCD_HEIGHT == 600
#define VIDEO_ZOOM_HEIGHT			3
#define VIDEO_ZOOM_INCREMENT		0
#elif LCD_HEIGHT == 720
#define VIDEO_ZOOM_HEIGHT           3
#define VIDEO_ZOOM_INCREMENT        0
#elif LCD_HEIGHT == 480
#define VIDEO_ZOOM_HEIGHT			2
#define VIDEO_ZOOM_INCREMENT		1
#elif (LCD_HEIGHT == 240) || (LCD_HEIGHT == 200) || (LCD_HEIGHT == 272)
#define VIDEO_ZOOM_HEIGHT			1
#define VIDEO_ZOOM_INCREMENT		0
#else
#error "Unsupported LCD"
#endif

#define _USE_BITMAP_DISPLAY

//////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_VIDEO

#ifdef VIDEO_RESCALE_SIZE
static const uint8_t zoom_mask_index[VIDEO_RESCALE_SIZE] = 
{
    #if VIDEO_RESCALE_SIZE == 56
    2,2,2,2,2,2,2, 2,2,2,2,2,2,2, 2,2,2,2,2,2,2, 2,2,2,2,2,2,2,
    //0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    #elif VIDEO_RESCALE_SIZE == 50
    1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,
    #elif VIDEO_RESCALE_SIZE == 39
    1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,
	#elif VIDEO_RESCALE_SIZE == 31
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
	#endif
};
#endif

static const uint32_t base_address[] =   { 0x000,  0x080,  0x100,  0x180,  0x200,  0x280,  0x300,  0x380 };
static const uint32_t offset_address[] = { 0x000,  0x028,  0x050 };
static const uint32_t offset_hires[] =   { 0x0000, 0x0400, 0x0800, 0x0C00, 0x1000, 0x1400, 0x1800, 0x1C00 };

static const uint8_t expand_byte[] =     { 0x00,   0x03,   0x0C,   0x0F,   0x30,   0x33,   0x3C,   0x3F, 
	                                       0xC0,   0xC3,   0xCC,   0xCF,   0xF0,   0xF3,   0xFC,   0xFF };

static pixel_t pixel_color[2];

//static pixel_t pixel_lores[16] =
//{
//    APP_RGB(0, 0, 0 ),
//    APP_RGB(142, 3, 84 ),
//    APP_RGB(57, 11, 221 ),
//    APP_RGB(195, 21, 254 ),
//
//    APP_RGB(1, 104, 18 ),
//    APP_RGB(116, 116, 116 ),
//    APP_RGB(31, 141, 255 ),
//    APP_RGB(160, 152, 255 ),
//
//    APP_RGB(70, 71, 1 ),
//    APP_RGB(238, 81, 1 ),
//    APP_RGB(182, 182, 182 ),
//    APP_RGB(255, 122, 221 ),
//
//    APP_RGB(20, 195, 10 ),
//    APP_RGB(200, 206, 20 ),
//    APP_RGB(72, 243, 138 ),
//    APP_RGB(255, 255, 255 ),
//};

static uint8_t local_hires;
static uint8_t local_page2;
static uint8_t local_text;
static uint8_t local_dhires;
static uint8_t local_80col;
static uint8_t local_altchar;

static uint32_t scan_address;

static uint16_t vid_posy;
static uint16_t addr_posx;
static uint16_t addr_posy;

static uint32_t pixel_data;

static uint32_t frame_counter;

static video_dma_hdl_t video_dma_hdl;
static board_data_t * board;
static bool_t end_v_scan;

static timer_data_t scan_ms;
static uint32_t video_frame_ms;

static bool_t video_zoom;

static uint32_t update_count;

static uint8_t terminal_x;
static uint8_t terminal_y;
static bool_t en_cursor;
static vbl_hdl_t p_vbl;

#ifdef ENABLE_VIDEO_SHADOW
static uint32_t video_shadow[ 20 ][ 192 ];
#endif

//////////////////////////////////////////////////////////////////////////////////////

static void video_v_scan( void )
{
	uint16_t posx, posy;

	frame_counter++;
	vid_posy = 0;
	addr_posy = 0;

	if( video_zoom != board->sw_switch[SW_VIDEOZOOM] )
	{
		if( video_zoom == TRUE )
		{
			// reducing - need to clean screen
            void * lcd = graphics_claim();
			for( posy = 0; posy < LCD_HEIGHT; posy++ )
			{
				for( posx = 0; posx < LCD_WIDTH-BUTTON_WIDTH; posx++ )
				{
                    graphics_set_pixel( lcd, posx, posy, APP_RGB(0,0,0) );
				}
			}
            graphics_release();
		}

		video_zoom = board->sw_switch[SW_VIDEOZOOM];
		#ifdef ENABLE_VIDEO_SHADOW
		memset( video_shadow, 0xFF, sizeof( video_shadow ) );
		#endif
	}
}

uint32_t video_dma_lores( void )
{
	#ifndef ENABLE_80COL_VIDEO
	int i;
	uint32_t b_shift;
	uint32_t o_shift;
	uint32_t reduced_pixel;
	#endif

	uint16_t char_byte1;
	uint16_t char_byte2;
	uint32_t local_pixel;
	uint8_t * ptr_char_map;

	if( local_text )
	{
        ptr_char_map = ( uint8_t * )&char_map[local_altchar ? 2048 : 0]; // char maps are 2048 bytes size

        if( local_80col )
        {
            char_byte1 = global_memory_read( scan_address | MEMORY_AUX_BANK ) << 3;   // aux
            char_byte2 = global_memory_read( scan_address ) << 3; // main
            
            local_pixel = ptr_char_map[ char_byte1 + ( addr_posy & 0x07 ) ] +
            ( ptr_char_map[ char_byte2 + ( addr_posy & 0x07 ) ] << 7 );
            
#ifndef ENABLE_80COL_VIDEO
            b_shift = 0x01;
            o_shift = 0x01;
            reduced_pixel = 0;
            
            for( i = 0; i < 7; i++ )
            {
                if( local_pixel & b_shift ) reduced_pixel |= o_shift;
                b_shift <<= 2;
                o_shift <<= 1;
            }
            local_pixel = reduced_pixel;
#endif
        }
        else
        {
            char_byte1 = global_memory_read( scan_address ) << 3; // main
            char_byte2 = ptr_char_map[ char_byte1 + ( addr_posy & 0x07 ) ];
            
#ifdef ENABLE_80COL_VIDEO
            local_pixel = expand_byte[ char_byte2 & 0x0F ] | ( expand_byte[ char_byte2 >> 4 ] << 8 );
#else
            local_pixel = char_byte2;
#endif
        }
	}
	else
	{
		ptr_char_map = ( uint8_t * )char_map; // lores_char_map;
        
        if( local_80col )
        {
            char_byte1 = global_memory_read( scan_address | MEMORY_AUX_BANK );  // aux
            char_byte2 = global_memory_read( scan_address );                    // main
            local_pixel = char_byte2;
            local_pixel = ( local_pixel << 8 ) | char_byte1;
        }
        else
        {
            local_pixel = global_memory_read( scan_address );                    // main
        }
	}

	return local_pixel;
}

uint32_t video_dma_hires( void )
{
	uint16_t char_byte1;
	uint16_t char_byte2;
	uint32_t local_pixel;

    if( local_dhires )
	{
		char_byte1 = global_memory_read( scan_address | MEMORY_AUX_BANK );   // aux
		char_byte2 = global_memory_read( scan_address ); // main

		local_pixel = ( char_byte1 & 0x07F ) | ( ( char_byte2 & 0x07F ) << 7 );
	}
	else
	{
		char_byte1 = global_memory_read( scan_address ); // main

#ifdef ENABLE_80COL_VIDEO
		local_pixel = expand_byte[ char_byte1 & 0x0F ] | ( expand_byte[ char_byte1 >> 4 ] << 8 );
#else
		local_pixel = char_byte1;
#endif
	}

	return local_pixel;
}

void video_h_scan( void )
{
	uint16_t temp_posy;
	uint8_t sw_80store;
	uint8_t sw_an3;

	addr_posx = 0;

	vid_posy += VIDEO_ZOOM_HEIGHT;

    if( video_zoom == TRUE )
	{
		vid_posy += VIDEO_ZOOM_INCREMENT;
	}

	if( ++addr_posy > 191 )
	{
		end_v_scan = TRUE;
		p_vbl();
	}

	local_page2 = board->sw_switch[ SW_PAGE2 ];
	local_hires = board->sw_switch[ SW_HIRES ];
	local_text = board->sw_switch[ SW_TEXT ];
	local_80col = board->sw_switch[ SW_80COL ];
	local_altchar = board->sw_switch[ SW_CHARSET ];
	sw_80store = board->sw_switch[ SW_80STORE ];
	sw_an3 = board->sw_switch[ SW_AN3 ];

	if( board->sw_switch[ SW_MIXED ] && ( addr_posy >= 160 ) )
	{
		local_hires = 0;
		local_text = 1;
	}

	if( sw_80store == TRUE ) local_page2 = 0;

	if( local_hires && local_80col && !sw_an3 ) local_dhires = 1;
	else if( !local_hires && local_80col )		local_dhires = 1;
	else										local_dhires = 0;

	if( local_dhires == 1 )						local_page2 = 0;

	if( local_text || ( !local_text && !local_hires ) )
	{
		temp_posy = addr_posy >> 3;
		scan_address =   base_address[ temp_posy & 0x07 ]
                       + offset_address[ ( temp_posy >> 3 ) & 0x03 ]
                       + ( local_page2 ? 0x0800 : 0x0400 );
		video_dma_hdl = video_dma_lores;
	}
	else
	{
		temp_posy = addr_posy >> 3;
        scan_address =   base_address[ temp_posy & 0x07 ]
                       + offset_address[ ( temp_posy >> 3 ) & 0x07 ]
                       + offset_hires[ addr_posy & 0x07 ]
                       + ( local_page2 ? 0x4000 : 0x2000 );

		video_dma_hdl = video_dma_hires;
	}
}

void video_dma( void )
{
	uint16_t index;
	uint16_t left_margin;
	uint16_t top_margin;
	uint16_t zoom_height;
    uint8_t phase_low;
    uint8_t phase_high;
    uint8_t phase;
    uint8_t colour_info;
    uint8_t colour_cnt;

	if( end_v_scan == TRUE )
	{
		if( timer_Check( &scan_ms ) == TRUE )
		{
			timer_Start( &scan_ms, video_frame_ms );
			end_v_scan = FALSE;
		}
		else
		{
			return;
		}
	}

	if( ( addr_posx & 0x01 ) == 0 )
	{
		pixel_data = video_dma_hdl();
	}
	else
	{
		#ifdef ENABLE_80COL_VIDEO
		//pixel_data = ( video_dma_hdl() << 14 ) | ( pixel_data & 0x3fff );
		//max_index = 28;
        phase_low = (pixel_data & 0xC000) ? 0x04 : FALSE;
		pixel_data = ( video_dma_hdl() << 14 ) | pixel_data;
        phase_high = (pixel_data & (((uint32_t)0xC000)<<14)) ? 0x04 : FALSE;
        #else
		pixel_data = ( video_dma_hdl() << 7 ) | ( pixel_data & 0x07F );
		#endif

		zoom_height = VIDEO_ZOOM_HEIGHT;
        left_margin = LCD_LEFT_MARGIN;
        top_margin = LCD_TOP_MARGIN;

		#ifdef VIDEO_RESCALE_SIZE
		if( video_zoom == TRUE )
		{
            #ifndef VIDEO_CENTRED
			left_margin = 0;
			top_margin = 0;
            #endif
			zoom_height += VIDEO_ZOOM_INCREMENT;
		}
		#endif

		#ifdef ENABLE_VIDEO_SHADOW
		if( video_shadow[ addr_posx >> 1 ][ addr_posy ] != pixel_data )
		#endif
		{
			#ifdef ENABLE_VIDEO_SHADOW
			video_shadow[ addr_posx >> 1 ][ addr_posy ] = pixel_data;
			#endif

			update_count++;
            colour_info = pixel_data & 0x0F;
            colour_cnt = 0;
            phase = phase_low;
            uint32_t vid_posx = ( ( ( addr_posx - 1 ) * ( video_zoom ? 56 : 28 ) ) ) / 2;
            
            void * lcd = graphics_claim();
            pixel_t * pixel_out = graphics_get_target_at( lcd, vid_posx + left_margin, vid_posy + top_margin );
            pixel_t pixel_temp = 0;
            
            for( index = 0; index < 28; index++ )
            {
                if( ( local_text ) || ( local_dhires ) ) //  || ( !local_text && !local_hires ) )
                {
                    pixel_temp = pixel_color[pixel_data & 0x01];
                }
                else if( !local_text && !local_hires )
                {
                }
                else
                {
                    if(!( index % 4 )) colour_info = pixel_data & 0x0F;
                    if( index >= 14 ) phase = phase_high;

                    switch( colour_info )
                    {
                        case 0x00: pixel_temp = pixel_color[0]; break;
                        case 0x03: pixel_temp = phase ? APP_RGB( 64, 128, 255 ) : APP_RGB( 255, 0, 255 ); break;
                        case 0x0C: pixel_temp = phase ? APP_RGB( 255, 128, 64 ) : APP_RGB( 0, 255, 0 ); break;
                        case 0x0f: pixel_temp = pixel_color[1]; break;
                    }
                }
                
                int zoom_w_cnt = ( video_zoom == TRUE ) ? zoom_mask_index[index] : 1;
                while( zoom_w_cnt )
                {
                    for( uint16_t zoom_h_cnt = 0; zoom_h_cnt < zoom_height; zoom_h_cnt++ )
                    {
                        pixel_out[ zoom_h_cnt * LCD_WIDTH ] = pixel_temp;
                    }
                    
                    pixel_out++;
                    vid_posx++;
                    zoom_w_cnt--;
                }

                pixel_data >>= 1;
            }
            
            graphics_release();
		}
	}

	scan_address++;

	if( ++addr_posx >= 0x28 )
	{
		video_h_scan();
	}
}

uint8_t video_get_vlb( uint8_t address, uint8_t null1 ) 
{
	if( end_v_scan == TRUE ) return 0xA0;
	return 0x00;
}

void video_benchmark_reset( void )
{
	frame_counter = 0;
}

uint32_t video_benchmark_read( void )
{
	return frame_counter;
}

uint32_t video_rate_read( void )
{
	uint32_t cnt;

	cnt = update_count;
	update_count = 0;

	return cnt;
}

bool_t video_vblank( void )
{
	return end_v_scan;
}

bool_t video_is_zoom( void )
{
    return video_zoom;
}

vbl_hdl_t video_hook_vlb( vbl_hdl_t new_hook )
{
    vbl_hdl_t ret = p_vbl;
    p_vbl = new_hook;
    return ret;
}

void video_init( void * p_board )
{
	board = ( board_data_t * )p_board;

	video_frame_ms = 1000 / VIDEO_HZ;
	frame_counter = 0;
	timer_Start( &scan_ms, video_frame_ms );
	end_v_scan = FALSE;

	video_v_scan();
	video_h_scan();

	pixel_color[0] = APP_RGB(32, 32, 32);
	pixel_color[1] = APP_RGB(255, 255, 255 );

	video_zoom = board->sw_switch[SW_VIDEOZOOM];
	p_vbl = video_v_scan;

	terminal_x = 0;
	terminal_y = 0;
	en_cursor = FALSE;

	update_count = 0;

    memory_io_set_handler( 0x19, video_get_vlb, NULL );

	#ifdef ENABLE_VIDEO_SHADOW
	memset( video_shadow, 0x00, sizeof( video_shadow ) );
	#endif
}

#endif

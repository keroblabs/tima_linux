#ifndef _VIDEO_H__
#define _VIDEO_H__

//////////////////////////////////////////////////////////////////////////////////////

//#include "datatypes.h"
#include "board.h"

//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////

#if LCD_WIDTH == 1280
#define LCD_LEFT_MARGIN       70
#define LCD_TOP_MARGIN        70
#elif LCD_WIDTH == 480
#define LCD_LEFT_MARGIN		30
#define LCD_TOP_MARGIN		40
#else
#define LCD_LEFT_MARGIN		0
#define LCD_TOP_MARGIN		0
#endif

//////////////////////////////////////////////////////////////////////////////////////

void video_init( void * p_board );
void video_benchmark_reset( void );
uint32_t video_benchmark_read( void );

void video_dma( void );

bool_t video_vblank( void );
uint32_t video_rate_read( void );

bool_t video_is_zoom( void );

vbl_hdl_t video_hook_vlb( vbl_hdl_t new_hook );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _VIDEO_H__

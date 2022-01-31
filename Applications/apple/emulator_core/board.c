#include "datatypes.h"
#include "board.h"
#include "io_addr.h"
#include "cpu.h"
#include "timer.h"
#include "debug.h"

#include "paddles.h"
#include "keyboard.h"
#include "video.h"
#include "sw_switch.h"
#include "ram_ctrl.h"
#include "disc_drive.h"
#include "hard_drive.h"
#include "clock_card.h"
#include "mouse.h"
#include "graphics.h"
#include "led_frame.h"
#include "printer.h"
#include "serial.h"
#include "apple2rom.h"
#include "lists.h"

//////////////////////////////////////////////////////////////////////////////////////

#define ROM_APPLE_FILE      "rom/APPLE2E.ROM"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct board_slot_list_t_
{
    list_node_t     node;
    uint8_t         slot;
    slot_handler_t  handler;
} board_slot_list_t;

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static timer_data_t benchmark_ms;
static uint32_t cpu_benchmark;
static uint32_t video_benchmark;
static uint32_t video_update;
static bool_t show_benchmarks;
static list_t slot_list;

//////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_CONTEXT
void board_system_new( uint8_t page )
{
	#ifdef ENABLE_OWN_MAIN_MEMORY
	if( page >= TOTAL_SWAP_PAGES ) return;

	board->curr_cpu_page = page;
	ram_reset();
	board_reset();

	led_show( LED_ID_DESKTOP_1 + page, TRUE );

	// invalidate display
	#ifdef _USE_VIDEO_SHADOW
	memset( board->video_shadow, 0xFF, sizeof( board->video_shadow ) );
	#endif
	#endif
}

bool_t board_system_load( uint8_t page )
{
	#if defined ENABLE_OWN_MAIN_MEMORY && defined ENABLE_OWN_AUX_MEMORY
	char swap_name[30];

	if( page >= TOTAL_SWAP_PAGES ) return FALSE;

	// load new image
	sprintf( swap_name, "swap/image%d.bin", page );
	if( board->p_disc_access( swap_name, Disc_Mode_Size, 0, NULL, 0 ) == 0 )
	{
		return FALSE;
	}

	board->p_disc_access( swap_name, Disc_Mode_Read, 0, board->ram_memory, sizeof( board->ram_memory ) );

	sprintf( swap_name, "swap/regs%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Read, 0, ( uint8_t * )&board->cpu_regs, sizeof( regsrec_t ) );

	sprintf( swap_name, "swap/mouse%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Read, 0, ( uint8_t * )&board->mouse_data, sizeof( mouse_data_t ) );

	sprintf( swap_name, "swap/sw_switch%d.bin", page );
	sw_switch_load( swap_name );

	// invalidate display
	#ifdef _USE_VIDEO_SHADOW
	memset( board->video_shadow, 0xFF, sizeof( board->video_shadow ) );
	#endif

	#endif
	return TRUE;
}

void board_system_delete( uint8_t page )
{
	#if defined ENABLE_OWN_MAIN_MEMORY && defined ENABLE_OWN_AUX_MEMORY
	char swap_name[30];

	if( page >= TOTAL_SWAP_PAGES ) return;

	// save current image
	sprintf( swap_name, "swap/image%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Remove, 0, NULL, 0 );

	sprintf( swap_name, "swap/regs%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Remove, 0, NULL, 0 );

	sprintf( swap_name, "swap/mouse%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Remove, 0, NULL, 0 );

	sprintf( swap_name, "swap/sw_switch%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Remove, 0, NULL, 0 );
	#endif
}

void board_system_save( uint8_t page )
{
	#if defined ENABLE_OWN_MAIN_MEMORY && defined ENABLE_OWN_AUX_MEMORY
	char swap_name[30];

	if( page >= TOTAL_SWAP_PAGES ) return;

	// save current image
	sprintf( swap_name, "swap/image%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Write, 0, board->ram_memory, sizeof( board->ram_memory ) );

	sprintf( swap_name, "swap/regs%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Write, 0, ( uint8_t * )&board->cpu_regs, sizeof( regsrec_t ) );

	sprintf( swap_name, "swap/mouse%d.bin", page );
	board->p_disc_access( swap_name, Disc_Mode_Write, 0, ( uint8_t * )&board->mouse_data, sizeof( mouse_data_t ) );

	sprintf( swap_name, "swap/sw_switch%d.bin", page );
	sw_switch_save( swap_name );
	#endif
}

void board_system_swap( uint8_t page )
{
	#if defined ENABLE_OWN_MAIN_MEMORY && defined ENABLE_OWN_AUX_MEMORY
	if( page >= TOTAL_SWAP_PAGES ) return;

	// save current image
	board_system_save( board->curr_cpu_page );

	// change the image
	if( board->curr_cpu_page == page ) return;
	board->curr_cpu_page = page;

	led_show( LED_ID_DESKTOP_1 + page, TRUE );

	// load new image
	if( board_system_load( board->curr_cpu_page ) == FALSE )
	{
		ram_reset();
		board_reset();
	}

	// invalidate display
	#ifdef _USE_VIDEO_SHADOW
	memset( board->video_shadow, 0xFF, sizeof( board->video_shadow ) );
	#endif

	#endif
}
#endif

uint32_t board_disc_image_access( const char * handler, uint8_t mode, uint32_t pos, uint8_t * buffer, uint32_t size )
{
    return board->p_disc_access( handler, mode, pos, buffer, size );
}

uint8_t board_loop( uint32_t cycle )
{
	if( timer_Check( &benchmark_ms ) == TRUE )
	{
		timer_Start( &benchmark_ms, 1000 );

		#ifdef ENABLE_VIDEO
		video_benchmark = video_benchmark_read();
		video_update = video_rate_read();
		#else
		video_benchmark = 0;
		video_update = 0;
		#endif

		uint32_t cpu_usage = cpu_usage_read();
		cpu_benchmark = cpu_benchmark_read();

		if( show_benchmarks == TRUE )
		{
			//printf( "CPU = %d Hz (%d) - Video = %d hz (%d)\n", cpu_benchmark_read(), cpu_usage_read(), video_benchmark_read(), video_update );
			sprintf( debug_temp_string, "CPU = %d Hz (Host on %d%%) - Video = %d hz (%d)\r\n", cpu_benchmark, cpu_usage, video_benchmark, video_update );
			board->p_print( debug_temp_string );
		}

		cpu_benchmark_reset();

		#ifdef ENABLE_VIDEO
		video_benchmark_reset();
		#endif
	}

	return STATUS_NONE;
}

void board_print_benchmark( dump_hdl_t dump_hdl )
{
	//sprintf( debug_temp_string, "CPU = %d Hz (%d) - Video = %d hz (%d)\n", cpu_benchmark, cpu_usage, video_benchmark, video_update );
	//dump_hdl( debug_temp_string );

	if( show_benchmarks == FALSE )
	{
	    show_benchmarks = TRUE;
        timer_Start( &benchmark_ms, 1000 );
	}
	else
	{
	    show_benchmarks = FALSE;
        timer_Stop( &benchmark_ms );
	}
}

void board_add_slot( uint8_t slot, slot_handler_t handler )
{
    board_slot_list_t * slot_item = ( board_slot_list_t * )MMALLOC( sizeof( board_slot_list_t ) );
    if( slot_item == NULL ) return;

    slot_item->slot = slot;
    slot_item->handler = handler;

    list_insert_head( &slot_list, &slot_item->node );
}

void board_startup( void * p_board )
{
	#ifdef ENABLE_CONTEXT
	uint8_t cnt;
	#endif

	board = ( board_data_t * )p_board;
    
    board->is_running = TRUE;

	// default loop handler
	board->p_loop = board_loop;

	// default values
	show_benchmarks = FALSE;

	// init framework
	timer_Init();

    // initialize memory system
    memory_init( board );
    
    // initialize CPU
    cpu_init( board );

	// initialize devices installed in the board
	ram_ctrl_init( board );
	sw_switch_init( board );
	#ifdef ENABLE_VIDEO
	video_init( board );
    board->sw_switch[SW_VIDEOZOOM] = TRUE;
	#endif
	paddle_init( board );
	keyboard_init( board );
	disc_drive_init( board );
	hdd_drive_init( board );
	clock_card_init( board );
	mouse_card_init( board );
	printer_init( board );
	serial_init( board );

	list_init( &slot_list, NULL );

	// install peripherals
	disc_insert_drive( 6, Sector_Order_DSK );
	hdd_insert_drive( 7 );
	printer_insert( 1 );
	serial_insert( 2 );
	clock_card_insert( 4 );
	mouse_card_insert( 5 );

	// start with turbo mode off
	cpu_turbo_mode( FALSE );

	// delete all pages
	#ifdef ENABLE_CONTEXT
	for( cnt = 0; cnt < TOTAL_SWAP_PAGES; cnt++ )
	{
		board_system_delete( cnt );
	}
	#endif

	// on boot, select desktop 1
	#ifdef ENABLE_CONTEXT
	led_show( LED_ID_DESKTOP_1, TRUE );
	board->curr_cpu_page = 0;
	#endif

	board_reset();
}

loop_hdl_t board_hook_loop( loop_hdl_t new_hook )
{
    loop_hdl_t ret = board->p_loop;
    board->p_loop = new_hook;
    return ret;
}

void board_reset( void )
{
	cpu_reset();
	sw_switch_reset();
}

void board_execute( void )
{
	cpu_execute();
}

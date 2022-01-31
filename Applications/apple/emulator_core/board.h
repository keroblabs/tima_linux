#ifndef _BOARD_H__
#define _BOARD_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "datatypes.h"
#include "disc_drive.h"
#include "sw_switch.h"
#include "graphics.h"
#include "timer.h"
#include "string_lib.h"

//////////////////////////////////////////////////////////////////////////////////////

#define _DONT_USE_OWN_MEMORY

//////////////////////////////////////////////////////////////////////////////////////
/*

1 = printer (save BMP)
2 = serial
3 = N/A
4 = clock
5 = mouse/HDD
6 = diskII
7 = HDD/mouse

*/
//////////////////////////////////////////////////////////////////////////////////////

#define TOTAL_SWAP_PAGES			9
#define TOTAL_RAM_MEMORY			2
#define VIDEO_BITS_PER_PIXEL		7
#define MAX_SLOT_NUM				7

#define DISC_DATA_BUFFER_SIZE		8192
#define ROM_SIZE					32768
#define MEMORY_AUX_BANK				0x10000

#define LCD_WIDTH					_USE_SCREEN_WIDTH
#define LCD_HEIGHT					_USE_SCREEN_HEIGHT

#define SCREEN_WIDTH				560
#define SCREEN_HEIGHT				192
#define SCREEN_SWITCH_Y				160

#define EMULATOR_FRAME_POSX			( SCREEN_WIDTH + ( LCD_LEFT_MARGIN + 5 ) )
#define EMULATOR_FRAME_POSY			LCD_TOP_MARGIN
#define EMULATOR_FRAME_WIDTH		( LCD_WIDTH - SCREEN_WIDTH - 29 ) // ( LCD_LEFT_MARGIN * 3 ) )
#define EMULATOR_FRAME_HEIGHT		220 // ( SCREEN_HEIGHT * 2 )

//////////////////////////////////////////////////////////////////////////////////////

enum
{
	Disc_Mode_Read,
	Disc_Mode_Write,
	Disc_Mode_Append,
	Disc_Mode_Size,
	Disc_Mode_Remove
};

//////////////////////////////////////////////////////////////////////////////////////

enum
{
	Key_CONTROL = 128,

	Key_RESET,
	Key_FUNCTION,
	Key_CAPSLOCK,

	Key_FUNC_DEFS = 200,
	Key_FUNC_LoadImage,
	Key_FUNC_SaveImage,
	Key_FUNC_NewImage,
	Key_FUNC_SwapImage,
    Key_FUNC_Touchpad
	
};

//////////////////////////////////////////////////////////////////////////////////////

typedef void ( *cpu_halt_step_t )( uint16_t pc, void * p_data );
typedef void ( *co_proc_hdl_t )( uint16_t pc );
typedef bool_t ( *interrupt_hdl_t )( void );
typedef uint8_t ( *loop_hdl_t )( uint32_t cycle );
typedef void ( *vbl_hdl_t )( void );
typedef void ( *setpixel_hdl_t )( uint16_t posx, uint16_t posy, uint32_t colour );
typedef void ( *showbitmap_htl_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, void * data );
typedef uint8_t ( *keyboard_hdl_t )( void );
typedef void ( *flip_hdl_t )( void );

typedef uint8_t ( *io_addr_t )( uint8_t addr, uint8_t write );
typedef uint8_t ( *address_read_t )( uint16_t address );
typedef void ( *address_write_t )( uint16_t address, uint8_t data );
typedef uint8_t * ( *address_map_t )( uint16_t address, uint8_t sw_ram );

typedef uint32_t ( *disc_access_t )( const char * handler, uint8_t mode, uint32_t pos, uint8_t * buffer, uint32_t size );

typedef uint32_t ( *disc_image_t )( const char * handler, uint32_t pos, uint8_t * buffer, uint32_t size );
typedef uint32_t ( *disc_image_size_t )( const char * handler );

typedef uint8_t ( *mouse_hdl_t )( uint16_t * posx, uint16_t * posy, uint16_t * posz );

typedef void ( *dump_hdl_t )( char * line );

typedef string_t * ( *image_list_hdl_t )( void ** item );

typedef bool_t ( *slot_handler_t )( uint8_t slot, uint8_t disc, void * item );

//////////////////////////////////////////////////////////////////////////////////////

//typedef struct _regsrec
//{
//	uint8_t a;   // accumulator
//	uint8_t x;   // index X
//	uint8_t y;   // index Y
//	uint8_t ps;  // processor status
//	uint16_t pc;  // program counter
//	uint16_t sp;  // stack pointer
//
//	uint8_t      irq;
//	bool_t       nmi;
//	bool_t       wai;
//	bool_t       stp;
//
//} regsrec_t;

typedef struct _cpu_data_t_
{
	disc_access_t p_disc_access;
	image_list_hdl_t p_image_list;
	dump_hdl_t p_print;
    loop_hdl_t p_loop;
	
    #ifdef ENABLE_CONTEXT
	uint32_t curr_cpu_page;
    #endif

	uint8_t sw_switch[ SW_MAXINDEX ];
	uint8_t sw_switch_backup[ SW_MAXINDEX ];

    //bitmap_t * lcd;
    
    bool_t is_running;
    
} board_data_t;

//////////////////////////////////////////////////////////////////////////////////////

extern board_data_t * p_board;

//////////////////////////////////////////////////////////////////////////////////////

void board_startup( void * p_board );
void board_execute( void );
void board_print_benchmark( dump_hdl_t dump_hdl );
void board_reset( void );

void board_system_swap( uint8_t page );
void board_system_save( uint8_t page );
void board_system_new( uint8_t page );
bool_t board_system_load( uint8_t page );
void board_system_delete( uint8_t page );

void board_add_slot( uint8_t slot, slot_handler_t handler );

loop_hdl_t board_hook_loop( loop_hdl_t new_hook );

uint32_t board_disc_image_access( const char * handler, uint8_t mode, uint32_t pos, uint8_t * buffer, uint32_t size );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _DEVICE_0_H__

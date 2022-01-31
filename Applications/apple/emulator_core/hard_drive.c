#include "hard_drive.h"
#include "board.h"
#include "io_addr.h"
#include "cpu.h"
#include "timer.h"
#include "ram_ctrl.h"
#include "led_frame.h"
#include "debug.h"

#ifdef ENABLE_EMBEDDED_ASM
#include "embedded.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////

#define COMMAND_NONE                0
#define COMMAND_GET_SIZE            1
#define COMMAND_SET_BLOCK_NUM       2
#define COMMAND_READ_BLOCK          3
#define COMMAND_WRITE_BLOCK         4
#define COMMAND_CLEAR_BLOCK         5
#define COMMAND_READ_BLOCK_00       6
#define COMMAND_RESET_FIFO          7
#define COMMAND_GET_RESPONSE        8

/////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_HDD_IMAGE_D1        "hdd/hdd_01.bin"
//#define DEFAULT_HDD_IMAGE_D2        "hdd/apple_desktop.bin"
//#define DEFAULT_HDD_IMAGE_D1        "hdd/hdd_02.bin"
//#define DEFAULT_HDD_IMAGE_D2        "hdd/hdd_prodos_src.bin"
#define DEFAULT_HDD_IMAGE_D2        "hdd/hdd_geos.bin"

#define BLOCK_BUFFER_SIZE           512

/////////////////////////////////////////////////////////////////////////////////////

#define HDD_USE_FILE
#define HDD_FW_BINARY		        "rom/hdd_fw.bin"
//#define HDD_FW_SOURCE		        "fw/hdd_driver/hdd_src_mcu.asm"
#define HDD_FW_SOURCE               "fw/hdd_driver/hdd_src_dma.asm"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct mli_data_t_
{
    uint8_t command;
    uint8_t unit;
    uint16_t addr;
    uint16_t block;
    
} mli_data_t;

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static loop_hdl_t local_loop;
static timer_data_t hdd_led_timer;

static void * hdd_handler_0;
static void * hdd_handler_1;
static void * hdd_handler;

static uint16_t fifo_index = 0;
static uint8_t fifo_buffer[BLOCK_BUFFER_SIZE];
static uint16_t fifo_block_num;

static bool_t command_flag;
static bool_t latch_read_flag;
static bool_t latch_write_flag;
static uint8_t latch_read;
static uint8_t latch_write;
static uint8_t latch_command;

/////////////////////////////////////////////////////////////////////////////////////

#ifdef HDD_USE_FILE
static uint8_t hard_drive_fw[4096];

static const char * hdd_source_list[2] =
{
	HDD_FW_SOURCE,
	NULL
};

#else
const static uint8_t hard_drive_fw[4096] =
{
	0xA2, 0x20, 0xA0, 0x00, 0xA2, 0x03, 0x86, 0x3C, 0x20, 0x58, 0xFF, 0xBA, 0xBD, 0x00, 0x01, 0x0A, 
	0x0A, 0x0A, 0x0A, 0x85, 0x2B, 0xAA, 0x9D, 0x8C, 0xC0, 0x4C, 0x01, 0x08, 0xA5, 0x43, 0x29, 0x70, 
	0xAA, 0xA5, 0x43, 0x9D, 0x89, 0xC0, 0xA5, 0x42, 0xC9, 0x00, 0xF0, 0x14, 0xC9, 0x01, 0xF0, 0x20, 
	0xC9, 0x02, 0xF0, 0x25, 0xC9, 0x03, 0xF0, 0x2A, 0xA9, 0x27, 0x38, 0x60, 0xA9, 0x00, 0x18, 0x60, 
	0xA5, 0x43, 0x29, 0x70, 0xAA, 0xBD, 0x87, 0xC0, 0xA8, 0xBD, 0x86, 0xC0, 0xAA, 0x18, 0x90, 0xEC, 
	0xA9, 0x43, 0x9D, 0x8A, 0xC0, 0xA9, 0x00, 0x18, 0x60, 0xA9, 0x43, 0x9D, 0x8B, 0xC0, 0xA9, 0x00, 
	0x18, 0x60, 0xA9, 0x00, 0x9D, 0x88, 0xC0, 0xA9, 0x00, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x1C, 

};
#endif

//////////////////////////////////////////////////////////////////////////////////////

static uint16_t get_unit_size( uint8_t unit )
{
    hdd_handler = ( unit & 0x80 ) ? hdd_handler_1 : hdd_handler_0;

    uint32_t max_block = board_disc_image_access( hdd_handler, Disc_Mode_Size, 0, NULL, 0 ) >> 9;
    return ( uint16_t )max_block & 0x0FFFF;
}

static void instant_block_read( uint8_t unit, uint16_t block_num, uint8_t * buffer )
{
    hdd_handler = ( unit & 0x80 ) ? hdd_handler_1 : hdd_handler_0;
    board_disc_image_access( hdd_handler, Disc_Mode_Read, block_num << 9, buffer, BLOCK_BUFFER_SIZE );
}

static void instant_block_write( uint8_t unit, uint16_t block_num, uint8_t * buffer )
{
    hdd_handler = ( unit & 0x80 ) ? hdd_handler_1 : hdd_handler_0;
    board_disc_image_access( hdd_handler, Disc_Mode_Write, block_num << 9, buffer, BLOCK_BUFFER_SIZE );
}

static void trigger_led( uint8_t param )
{
    led_show( LED_ID_HDD_D1, ( param & 0x80 ) ? FALSE : TRUE );
    led_show( LED_ID_HDD_D2, ( param & 0x80 ) ? TRUE : FALSE );
    timer_Start( &hdd_led_timer, 500 );
}


static void exec_mli( void )
{
    mli_data_t * mli_data = ( mli_data_t * )ram_get_dma_pointer( 0x42 );
    uint16_t unit_size;
    uint16_t cnt;
    uint8_t * p_dma;
    
    switch( mli_data->command )
    {
        case 0:
            // get status
            unit_size = get_unit_size( mli_data->unit & 0x80 );
            cpu_set_regx( unit_size & 0x0FF );
            cpu_set_regy( ( unit_size >> 8 ) & 0x0FF );
            break;
            
        case 1:
            // read block
            trigger_led( mli_data->unit );
            instant_block_read( mli_data->unit & 0x80, mli_data->block, fifo_buffer );
            p_dma = ram_ctrl_get_pointer( mli_data->addr, FALSE );
            memcpy( p_dma, fifo_buffer, BLOCK_BUFFER_SIZE );
            break;

        case 2:
            // write block
            trigger_led( mli_data->unit );
            p_dma = ram_ctrl_get_pointer( mli_data->addr, FALSE );
            memcpy( fifo_buffer, p_dma, BLOCK_BUFFER_SIZE );
            instant_block_write( mli_data->unit & 0x80, mli_data->block, fifo_buffer );
            break;
            
        case 3:
            // format block
            unit_size = get_unit_size( mli_data->unit & 0x80 );
            memset( fifo_buffer, 0x00, BLOCK_BUFFER_SIZE );
            for( cnt = 0; cnt < unit_size; cnt++ )
            {
                instant_block_write( mli_data->unit & 0x80, cnt, fifo_buffer );
            }
            break;
    }
}

static void hdd_io_latch_process( void )
{
    uint16_t max_block;
    uint8_t param = latch_command & 0xF0;
    
    switch( latch_command & 0x0F)
    {
        case COMMAND_NONE:
            if( latch_write_flag == TRUE )
            {
                fifo_buffer[fifo_index] = latch_write;
                latch_write_flag = FALSE;
                if( ++fifo_index >= BLOCK_BUFFER_SIZE ) fifo_index = 0;
            }
            break;
            
        case COMMAND_GET_SIZE:
            max_block = get_unit_size( param & 0x80 );
            memcpy( fifo_buffer, &max_block, sizeof( max_block ) );
            latch_command = COMMAND_GET_RESPONSE;
            command_flag = FALSE;
            break;
            
        case COMMAND_SET_BLOCK_NUM:
            memcpy( &fifo_block_num, fifo_buffer, sizeof( fifo_block_num ) );
            fifo_buffer[0] = 0; // use this as error code
            latch_command = COMMAND_GET_RESPONSE;
            command_flag = FALSE;
            break;
            
        case COMMAND_READ_BLOCK_00:
            fifo_block_num = 0;
            /* FALLTHROUGH */

        case COMMAND_READ_BLOCK:
            instant_block_read( param & 0x80, fifo_block_num, fifo_buffer );
            latch_command = COMMAND_GET_RESPONSE;
            command_flag = FALSE;
            trigger_led( param );
            break;

        case COMMAND_WRITE_BLOCK:
            instant_block_write( param & 0x80, fifo_block_num, fifo_buffer );
            latch_command = COMMAND_NONE;
            command_flag = FALSE;
            trigger_led( param );
            break;

        case COMMAND_CLEAR_BLOCK:
            memset( fifo_buffer, 0x00, BLOCK_BUFFER_SIZE );
            instant_block_write( param ? 0x80 : 0x00, fifo_block_num, fifo_buffer );
            latch_command = COMMAND_GET_RESPONSE;
            command_flag = FALSE;
            trigger_led( param );
            break;
            
        case COMMAND_GET_RESPONSE:
            if( latch_read_flag == FALSE )
            {
                latch_read = fifo_buffer[ fifo_index ];
                latch_read_flag = TRUE;
                if( ++fifo_index >= BLOCK_BUFFER_SIZE ) fifo_index = 0;
            }
            break;

        case COMMAND_RESET_FIFO:
            if( command_flag == TRUE )
            {
                latch_command = COMMAND_NONE;
                command_flag = FALSE;
            }
            break;
    }
}

static uint8_t hdd_io_controller( uint8_t address, uint8_t data )
{
    uint8_t ret8 = 0;
    uint8_t * dma_pointer;
    
    switch( address & 0x0F )
    {
        // microcontroller support
            
        case 0x00: latch_write = data;      break;
        case 0x01: latch_write_flag = TRUE; break;
        case 0x02: ret8 = latch_read;       break;
        case 0x03: latch_read_flag = FALSE; break;

        case 0x04:
            // wait for the controller to take the command
            ret8 = ( command_flag == TRUE ) ? 0x80 : 0x00;
            hdd_io_latch_process();
            break;

        case 0x05:
            // wait for the controller to take the written data
            ret8 = ( latch_write_flag == TRUE ) ? 0x80 : 0x00;
            hdd_io_latch_process();
            break;

        case 0x06:
            // wait for the controller to load something to read
            ret8 = ( latch_read_flag == TRUE ) ? 0x80 : 0x00;
            hdd_io_latch_process();
            break;
            
        case 0x07:
            // command the controller
            latch_command = data;
            fifo_index = 0;
            command_flag = TRUE;
            latch_write_flag = FALSE;
            latch_read_flag = FALSE;
            break;
            
        // DMA support
            
        case 0x0C:
            // instant boot
            instant_block_read( 0x00, 0x0000, fifo_buffer );
            dma_pointer = ram_get_dma_pointer( 0x800 );
            memcpy( dma_pointer, fifo_buffer, BLOCK_BUFFER_SIZE );
            break;
            
        case 0x0D:
            // exec mli
            exec_mli();
            break;
    }
    
    return ret8;
}

static uint8_t hdd_local_loop( uint32_t cycles )
{
    if( timer_Check( &hdd_led_timer ) == TRUE )
    {
        timer_Stop( &hdd_led_timer );
        led_show( LED_ID_HDD_D1, FALSE );
        led_show( LED_ID_HDD_D2, FALSE );
    }

    return local_loop( cycles );
}

#ifdef HDD_USE_FILE
void hdd_fw_rebuild( bool_t force_build )
{
	if( ( board_disc_image_access( HDD_FW_BINARY, Disc_Mode_Size, 0, ( uint8_t * )&hard_drive_fw[0], 4096 ) == 0 ) ||
		( force_build == TRUE ) )
	{
		#ifdef ENABLE_EMBEDDED_ASM
		assembler( hdd_source_list, 1, HDD_FW_BINARY, board );
		#endif
	}
}
#endif

void hdd_block_read( uint8_t unit, uint16_t block_num, uint8_t * buffer )
{
    instant_block_read( unit, block_num, buffer );
}

void hdd_block_write( uint8_t unit, uint16_t block_num, uint8_t * buffer )
{
    instant_block_write( unit, block_num, buffer );
}

void hdd_insert_drive( uint8_t slot )
{
	int counter;
	uint8_t page = ( 0x08 + slot ) << 4;

	#ifdef HDD_USE_FILE
	hdd_fw_rebuild( TRUE );
    board_disc_image_access( HDD_FW_BINARY, Disc_Mode_Read, 0, ( uint8_t * )&hard_drive_fw[0], 4096 );
	#endif

	ram_ctrl_insert_slot( slot, ( uint8_t * )hard_drive_fw );

	for( counter = 0; counter < 16; counter++ )
	{
        memory_io_set_handler( page + counter, hdd_io_controller, hdd_io_controller );
	}

	hdd_handler_0 = DEFAULT_HDD_IMAGE_D1;
	hdd_handler_1 = DEFAULT_HDD_IMAGE_D2;
	hdd_handler = hdd_handler_0;
}

void hdd_drive_init( void * p_board )
{
	board = ( board_data_t * )p_board;
	timer_Stop( &hdd_led_timer );
	local_loop = board_hook_loop( hdd_local_loop );
}

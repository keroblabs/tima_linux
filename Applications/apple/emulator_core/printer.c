#include "printer.h"
#include "board.h"
#include "io_addr.h"
#include "cpu.h"
#include "ram_ctrl.h"
#include "tima_libc.h"
#include "led_frame.h"
#include "timer.h"

#ifdef ENABLE_EMBEDDED_ASM
#include "embedded.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////

#define PRINTER_BUFFER_SIZE		256

/////////////////////////////////////////////////////////////////////////////////////

#define PRINTER_USE_FILE
#define PRINTER_FW_BINARY		"rom/printer_fw.bin"
#define PRINTER_FW_SOURCE		"fw/printer_driver/printer_src.asm"

//////////////////////////////////////////////////////////////////////////////////////

#ifdef PRINTER_USE_FILE
static uint8_t printer_fw[4096];
static const char * printer_source_list[2] =
{
	PRINTER_FW_SOURCE,
	NULL
};
#else
const static uint8_t printer_fw[4096] =
{
	0x18, 0xB0, 0x38, 0x48, 0x8A, 0x48, 0x98, 0x48, 0x08, 0x78, 0x20, 0x58, 0xFF, 0xBA, 0x68, 0x68, 
	0x68, 0x68, 0xA8, 0xCA, 0x9A, 0x68, 0x28, 0xAA, 0x90, 0x38, 0xBD, 0xB8, 0x05, 0x10, 0x19, 0x98, 
	0x29, 0x7F, 0x49, 0x30, 0xC9, 0x0A, 0x90, 0x3B, 0xC9, 0x78, 0xB0, 0x29, 0x49, 0x3D, 0xF0, 0x21, 
	0x98, 0x29, 0x9F, 0x9D, 0x38, 0x06, 0x90, 0x7E, 0xBD, 0xB8, 0x06, 0x30, 0x14, 0xA5, 0x24, 0xDD, 
	0x38, 0x07, 0xB0, 0x0D, 0xC9, 0x11, 0xB0, 0x09, 0x09, 0xF0, 0x3D, 0x38, 0x07, 0x65, 0x24, 0x85, 
	0x24, 0x4A, 0x38, 0xB0, 0x6D, 0x18, 0x6A, 0x3D, 0xB8, 0x06, 0x90, 0x02, 0x49, 0x81, 0x9D, 0xB8, 
	0x06, 0xD0, 0x53, 0xA0, 0x0A, 0x7D, 0x38, 0x05, 0x88, 0xD0, 0xFA, 0x9D, 0xB8, 0x04, 0x9D, 0x38, 
	0x05, 0x38, 0xB0, 0x43, 0xC5, 0x24, 0x90, 0x3A, 0x68, 0xA8, 0x68, 0xAA, 0x68, 0x4C, 0xF0, 0xFD, 
	0x90, 0xFE, 0xB0, 0xFE, 0x99, 0x80, 0xC0, 0x90, 0x37, 0x49, 0x07, 0xA8, 0x49, 0x0A, 0x0A, 0xD0, 
	0x06, 0xB8, 0x85, 0x24, 0x9D, 0x38, 0x07, 0xBD, 0xB8, 0x06, 0x4A, 0x70, 0x02, 0xB0, 0x23, 0x0A, 
	0x0A, 0xA9, 0x27, 0xB0, 0xCF, 0xBD, 0x38, 0x07, 0xFD, 0xB8, 0x04, 0xC9, 0xF8, 0x90, 0x03, 0x69, 
	0x27, 0xAC, 0xA9, 0x00, 0x85, 0x24, 0x18, 0x7E, 0xB8, 0x05, 0x68, 0xA8, 0x68, 0xAA, 0x68, 0x60, 
	0x90, 0x27, 0xB0, 0x00, 0x10, 0x11, 0xA9, 0x89, 0x9D, 0x38, 0x06, 0x9D, 0xB8, 0x06, 0xA9, 0x28, 
	0x9D, 0xB8, 0x04, 0xA9, 0x02, 0x85, 0x36, 0x98, 0x5D, 0x38, 0x06, 0x0A, 0xF0, 0x90, 0x5E, 0xB8, 
	0x05, 0x98, 0x48, 0x8A, 0x0A, 0x0A, 0x0A, 0x0A, 0xA8, 0xBD, 0x38, 0x07, 0xC5, 0x24, 0x68, 0xB0, 
	0x05, 0x48, 0x29, 0x80, 0x09, 0x20, 0x2C, 0x58, 0xFF, 0xF0, 0x03, 0xFE, 0x38, 0x07, 0x70, 0x84, 
};
#endif

/////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static uint8_t print_buffer[PRINTER_BUFFER_SIZE];
static uint32_t printer_index;
static uint32_t printer_pos;
static char printer_filename[64];

static const char printer_off_string_upper[] = { 'P', 'R', '#', '0', 0x0d, 0x0a, 0x00 };
static const char printer_off_string_lower[] = { 'p', 'r', '#', '0', 0x0d, 0x0a, 0x00 };

static const char printer_asm_compiler[] = { ';', ' ', 'a', 's', 'm', '-', '6', '5', 0x0a, 0x0d, 0x00 };

static uint8_t printer_off_counter;
static uint8_t printer_asm_counter;

/////////////////////////////////////////////////////////////////////////////////////

static uint8_t printer_io_controller( uint8_t address, uint8_t data )
{
	if( strlen( printer_filename ) == 0 )
	{
		printer_new_paper();
	}

	if( ( address & 0x0f ) == 0 )
	{
        data &= 0x7F;
		print_buffer[printer_index++] = data;
        
        if( ( data == printer_off_string_upper[printer_off_counter] ) ||
            ( data == printer_off_string_lower[printer_off_counter] ) )
        {
            printer_off_counter++;
            
            if( printer_off_string_upper[printer_off_counter] == 0x00 )
            {
                printer_remove_paper();
            }
        }
        else if( data == printer_asm_compiler[printer_asm_counter] )
        {
            printer_asm_counter++;

            if( printer_asm_compiler[printer_asm_counter] == 0x00 )
            {
                printer_remove_paper();
            }
        }
        else
        {
            printer_off_counter = 0;
        }
           
		if( printer_index >= PRINTER_BUFFER_SIZE )
		{
            board_disc_image_access( printer_filename, Disc_Mode_Write, printer_pos, print_buffer, printer_index );
			printer_pos += PRINTER_BUFFER_SIZE;
			printer_index = 0;
		}
	}
	return 0;
}

void printer_new_paper( void )
{
	uint32_t printer_file_id;

	if( printer_index != 0 )
	{
		// flush current printing
        board_disc_image_access( printer_filename, Disc_Mode_Write, printer_pos, print_buffer, printer_index );
	}

	printer_file_id = timer_32bit_now();
	sprintf( printer_filename, "printer/printing_%d.prn", printer_file_id );
	printer_index = 0;
	printer_pos = 0;
    
    printer_off_counter = 0;
    printer_asm_counter = 0;

	led_show( LED_ID_PRINTER, TRUE );
}

void printer_remove_paper( void )
{
	if( printer_index != 0 )
	{
		// flush current printing
        board_disc_image_access( printer_filename, Disc_Mode_Write, printer_pos, print_buffer, printer_index );
	}

	printer_index = 0;
	printer_pos = 0;
	printer_filename[0] = 0;

	led_show( LED_ID_PRINTER, FALSE );
}

#ifdef PRINTER_USE_FILE
void printer_fw_rebuild( bool_t force_build )
{
	if( ( board_disc_image_access( PRINTER_FW_BINARY, Disc_Mode_Size, 0, ( uint8_t * )&printer_fw[0], 256 ) == 0 ) ||
		( force_build == TRUE ) )
	{
		#ifdef ENABLE_EMBEDDED_ASM
		assembler( printer_source_list, 1, PRINTER_FW_BINARY, board );
		#endif
	}
}
#endif

void printer_insert( uint8_t slot )
{
	int counter;
	uint8_t page = ( 0x08 + slot ) << 4;

	#ifdef PRINTER_USE_FILE
	printer_fw_rebuild( FALSE );
    board_disc_image_access( PRINTER_FW_BINARY, Disc_Mode_Read, 0, ( uint8_t * )&printer_fw[0], 256 );
	#endif

	ram_ctrl_insert_slot( slot, ( uint8_t * )printer_fw );

	for( counter = 0; counter < 16; counter++ )
	{
		memory_io_set_handler( page + counter, printer_io_controller, printer_io_controller );
	}
}

void printer_init( void * p_board )
{
	board = ( board_data_t * )p_board;

	printer_index = 0;
	printer_pos = 0;
	printer_filename[0] = 0;

	led_show( LED_ID_PRINTER, FALSE );
}


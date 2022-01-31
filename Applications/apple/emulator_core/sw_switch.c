#include "io_addr.h"
#include "board.h"
#include "sw_switch.h"
#include "debug.h"
#include "keyboard.h"
#include "ram_ctrl.h"

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;

static const char sw_switch_dump_str[SW_MAXINDEX][20] = 
{
	"SW_80STORE",
	"SW_RAMRD",
	"SW_RAMWR",
	"SW_ALTZP",
	"SW_80COL",
	"SW_SLOTXROM",
	"SW_SLOT3ROM",
	"SW_CHARSET",
	"SW_TEXT",
	"SW_MIXED",
	"SW_PAGE2",
	"SW_HIRES",
	"SW_AN0",
	"SW_AN1",
	"SW_AN2",
	"SW_AN3",
	"SW_EXP16RAM",
	"SW_EXP16WRITE",
	"SW_EXP16BANK",
	"SW_MEMPAGE",
};

static const char sw_switch_name_01[SW_MAXINDEX][20] = 
{
	"SW_80STORE",
	"SW_RAMRD",
	"SW_RAMWR",
	"SW_SLOTXROM",
	"SW_ALTZP",
	"SW_SLOT3ROM",
	"SW_80COL",
	"SW_CHARSET",
};

static const char sw_switch_name_02[SW_MAXINDEX][20] = 
{
	"SW_EXP16WRITE",
	"SW_EXP16BANK",
	"SW_EXP16RAM",
	"SW_RAMRD",
	"SW_RAMWR",
	"SW_SLOTXROM",
	"SW_ALTZP",
	"SW_SLOT3ROM",
	"SW_80STORE",
	"?????",
	"SW_TEXT",
	"SW_MIXED",
	"SW_PAGE2",
	"SW_HIRES",
	"?????",
	"SW_80COL",
};

static const char sw_switch_name_03[SW_MAXINDEX][20] = 
{
	"SW_TEXT",
	"SW_MIXED",
	"SW_PAGE2",
	"SW_HIRES",
	"SW_AN0",
	"SW_AN1",
	"SW_AN2",
	"SW_AN3",
	//"SW_MEMPAGE",
};

//////////////////////////////////////////////////////////////////////////////////////

static uint8_t SW_MemoryPageControl( uint8_t address, uint8_t null1 )
{
	switch( ( address & 0x0F ) >> 1 )
	{
		case 0x00: board->sw_switch[SW_80STORE]   = address & 0x01; break; // 0xC000 / 0xC001
		case 0x01: board->sw_switch[SW_RAMRD] 	  = address & 0x01; break; // 0xC002 / 0xC003
		case 0x02: board->sw_switch[SW_RAMWR] 	  = address & 0x01; break; // 0xC004 / 0xC005
		case 0x03: board->sw_switch[SW_SLOTXROM]  = address & 0x01; break; // 0xC006 / 0xC007
		case 0x04: board->sw_switch[SW_ALTZP]     = address & 0x01; break; // 0xC008 / 0xC009
		case 0x05: board->sw_switch[SW_SLOT3ROM]  = address & 0x01; break; // 0xC00A / 0xC00B
		case 0x06: board->sw_switch[SW_80COL] 	  = address & 0x01; break; // 0xC00C / 0xC00D
		case 0x07: board->sw_switch[SW_CHARSET]	  = address & 0x01; break; // 0xC00E / 0xC00F
	}

	//printf( "%s = %d\n", sw_switch_name_01[( address & 0x0F ) >> 1], address & 0x01 );

	if( ( address & 0x0F ) == 0x01 ) 
	{
		board->sw_switch[SW_PAGE2] = 0;
	}

	return( 0x00 );
}

static uint8_t get_exp16_addr_setup( void )
{
    uint8_t data = 2;
    
    if( board->sw_switch[SW_EXP16WRITE] && board->sw_switch[SW_EXP16RAM] ) data = 3;
    else if( board->sw_switch[SW_EXP16WRITE] ) data = 1;
    else if( board->sw_switch[SW_EXP16RAM] )   data = 0;
    
    data += ( board->sw_switch[SW_EXP16BANK] ) ? 0x00 : 0x08;

    return data;
}

static uint8_t SW_MemoryPageStatus( uint8_t address, uint8_t null1 )
{
	uint8_t result = 0;
	uint8_t get_keycode( void );

	switch( address & 0x0F )
	{
		//case 0x00: return( board->sw_switch[SW_EXP16WRITE]    ? 0x80 : 0x00 ); break;
		case 0x01: result =   ( board->sw_switch[SW_EXP16BANK]    ? 0x80 : 0x00 )
                            |   get_exp16_addr_setup();  break;
		case 0x02: result = ( board->sw_switch[SW_EXP16RAM]     ? 0x80 : 0x00 ); break;
		case 0x03: result = ( board->sw_switch[SW_RAMRD]        ? 0x80 : 0x00 ); break;
		case 0x04: result = ( board->sw_switch[SW_RAMWR]        ? 0x80 : 0x00 ); break;
		case 0x05: result = ( board->sw_switch[SW_SLOTXROM]     ? 0x80 : 0x00 ); break;
		case 0x06: result = ( board->sw_switch[SW_ALTZP]		? 0x80 : 0x00 ); break;
		case 0x07: result = ( board->sw_switch[SW_SLOT3ROM]     ? 0x80 : 0x00 ); break;
		case 0x08: result = ( board->sw_switch[SW_80STORE]      ? 0x80 : 0x00 ); break;
		// case 0x09: return 0;
		case 0x0A: result = ( board->sw_switch[SW_TEXT]			? 0x80 : 0x00 ); break;
		case 0x0B: result = ( board->sw_switch[SW_MIXED]		? 0x80 : 0x00 ); break;
		case 0x0C: result = ( board->sw_switch[SW_PAGE2]		? 0x80 : 0x00 ); break;
		case 0x0D: result = ( board->sw_switch[SW_HIRES]		? 0x80 : 0x00 ); break;
		case 0x0E: result = ( board->sw_switch[SW_CHARSET]		? 0x80 : 0x00 ); break;
		case 0x0F: result = ( board->sw_switch[SW_80COL]		? 0x80 : 0x00 ); break;
	}

	return( result | keyboard_read_raw() );
}

static uint8_t SW_VideoControl( uint8_t address, uint8_t null1 )
{
	uint8_t check_addr = ( address & 0x0F ) >> 1;
	
	switch( check_addr )
	{
		case 0x00: board->sw_switch[SW_TEXT]	= address & 0x01; break; // 0xC050 / 0xC051
		case 0x01: board->sw_switch[SW_MIXED]	= address & 0x01; break; // 0xC052 / 0xC053
		case 0x02: board->sw_switch[SW_PAGE2]	= address & 0x01; break; // 0xC054 / 0xC055
		case 0x03: board->sw_switch[SW_HIRES]	= address & 0x01; break; // 0xC056 / 0xC057
		case 0x04: board->sw_switch[SW_AN0]	= address & 0x01; break; // 0xC058 / 0xC059
		case 0x05: board->sw_switch[SW_AN1]	= address & 0x01; break; // 0xC05A / 0xC05B
		case 0x06: board->sw_switch[SW_AN2]	= address & 0x01; break; // 0xC05C / 0xC05D
		case 0x07: board->sw_switch[SW_AN3]	= address & 0x01; break; // 0xC05E / 0xC05F
	}

	//printf( "%s = %d\n", sw_switch_name_03[check_addr], address & 0x01 );

	return( 0x00 );
}

static uint8_t SW_Memory_Page( uint8_t address, uint8_t data )
{
	//char output[20];
	data = data % ( TOTAL_RAM_MEMORY );

	//sprintf( output, "0xC0%02x = %02x\n", address, data );
	//board->p_print( output );
	board->sw_switch[SW_MEMPAGE] = data;
    ram_set_mem_page( data );

	return 0;
}

static uint8_t SW_backup_switch( uint8_t address, uint8_t data )
{
	if( data == 0x5A )
	{
		memcpy( board->sw_switch, board->sw_switch_backup, sizeof( board->sw_switch ) );
        ram_set_mem_page( board->sw_switch[SW_MEMPAGE] );
	}
	else if( data == 0xF1 )
	{
		memcpy( board->sw_switch_backup, board->sw_switch, sizeof( board->sw_switch_backup ) );
        ram_set_mem_page( board->sw_switch_backup[SW_MEMPAGE] );
	}

	return 0;
}

static uint8_t SW_DHIRES_State( uint8_t address, uint8_t data )
{
	if( board->sw_switch[SW_AN3] ) return 0x00;
	return 0xA0;
}

static uint8_t Exp16_Control( uint8_t address, uint8_t null2 )
{
	board->sw_switch[SW_EXP16RAM] = FALSE;
	board->sw_switch[SW_EXP16BANK] = FALSE;
	board->sw_switch[SW_EXP16WRITE] = FALSE;

	if( address & 0x01 )
	{
		board->sw_switch[SW_EXP16WRITE] = TRUE;
	}

	if( !( address & 0x08 ) )
	{
		board->sw_switch[SW_EXP16BANK] = TRUE;
	}

	if( ( ( address & 2 ) >> 1 ) == ( address & 1 ) )
	{
		board->sw_switch[SW_EXP16RAM] = TRUE;
	}

	return 0;
}

void sw_switch_init( void * p_board )
{
	uint32_t counter;
	board = ( board_data_t * )p_board;
	
	for( counter = 0x00; counter <= 0x0F; counter++ )
	{
		memory_io_set_handler( counter, NULL, SW_MemoryPageControl );
	}

	for( counter = 0x50; counter <= 0x5F; counter++ )
	{
		memory_io_set_handler( counter, SW_VideoControl, SW_VideoControl );
	}

	for( counter = 0x11; counter <= 0x1F; counter++ )
	{
		if( counter != 0x19 )
			memory_io_set_handler( counter, SW_MemoryPageStatus, NULL );
	}

	memory_io_set_handler( 0x7F, SW_DHIRES_State, NULL );

	memory_io_set_handler( 0x73, NULL, SW_Memory_Page );

	memory_io_set_handler( 0x79, NULL, SW_backup_switch );

	for( counter = 0x80; counter <= 0x8F; counter++ )
	{
		memory_io_set_handler( counter, Exp16_Control, Exp16_Control );
	}

	sw_switch_reset();
}

void sw_switch_reset( void )
{
	memset( board->sw_switch, 0x00, sizeof( board->sw_switch ) );
    ram_set_mem_page( board->sw_switch[SW_MEMPAGE] );
    board->sw_switch[SW_VIDEOZOOM] = TRUE;
}

void sw_switch_dump( dump_hdl_t dump_hdl )
{
	int counter;

	for( counter = 0; counter < SW_MAXINDEX; counter++ )
	{
		sprintf( debug_temp_string, "%s = %d\r\n", sw_switch_dump_str[counter], board->sw_switch[counter] );
		dump_hdl( debug_temp_string );
	}
}

void sw_switch_save( void * handler )
{
    board_disc_image_access( handler, Disc_Mode_Write, 0, board->sw_switch, sizeof( board->sw_switch ) );
}

void sw_switch_load( void * handler )
{
    board_disc_image_access( handler, Disc_Mode_Read, 0, board->sw_switch, sizeof( board->sw_switch ) );
}

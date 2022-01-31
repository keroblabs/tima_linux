#include "io_addr.h"
#include "board.h"

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

#define DEVICE_PAGE					0xC0

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static io_addr_t p_io_read[256];
static io_addr_t p_io_write[256];

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

uint8_t dummy_io( uint8_t address, uint8_t null1 ) 
{
	return 0;
}

uint8_t memory_read_io( uint16_t address )
{
	return( p_io_read[ address & 0x0FF ]( ( uint8_t )( address & 0x0FF ), 0 ) );
}

void memory_write_io( uint16_t address, uint8_t data )
{
	p_io_write[ address & 0x0FF ]( ( uint8_t )( address & 0x0FF ), data );
}

void memory_init( void * p_board )
{
	uint32_t counter;
	
    board = ( board_data_t * )p_board;

	// reset all memory
	for( counter = 0; counter < 256; counter++ )
	{
		p_io_read[counter] = dummy_io;
		p_io_write[counter] = dummy_io;
	}
}

void memory_set_handler( uint8_t page, void * mem_read, void * mem_write )
{
}

void memory_io_set_handler( uint8_t page, void * io_read, void * io_write )
{
	if( ( io_read == NULL ) && ( io_write == NULL ) )
	{
		io_write = dummy_io;
		io_read = dummy_io;
	}

	if( io_read != NULL ) p_io_read[ page ] = ( io_addr_t )io_read;
	if( io_write != NULL ) p_io_write[ page ] = ( io_addr_t )io_write;
}


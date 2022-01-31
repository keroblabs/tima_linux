#include "paddles.h"
#include "board.h"
#include "io_addr.h"
#include "ram_ctrl.h"

#include "keyboard_drv.h"

//////////////////////////////////////////////////////////////////////////////////////

static uint32_t cycles_pdl_0;
static uint32_t cycles_pdl_1;
static uint32_t cycles_pdl_2;
static uint32_t cycles_pdl_3;

static uint16_t pdl0_val;
static uint16_t pdl1_val;
static uint16_t pdl2_val;
static uint16_t pdl3_val;

static bool_t paddle_button0;
static bool_t paddle_button1;

static uint32_t paddle_cycles;

//////////////////////////////////////////////////////////////////////////////////////

static void paddle_trigger( uint16_t pdl0, uint16_t pdl1, uint16_t pdl2, uint16_t pdl3 )
{
    cycles_pdl_0 = paddle_cycles + ( 0x0B * ( uint32_t )( pdl0 & 0x0FF ) );
    cycles_pdl_1 = paddle_cycles + ( 0x0B * ( uint32_t )( pdl1 & 0x0FF ) );
    cycles_pdl_2 = paddle_cycles + ( 0x0B * ( uint32_t )( pdl2 & 0x0FF ) );
    cycles_pdl_3 = paddle_cycles + ( 0x0B * ( uint32_t )( pdl3 & 0x0FF ) );
}

static bool_t paddle_get( uint8_t paddle )
{
    switch( paddle )
    {
        case 0: return( cycles_pdl_0 != 0 );
        case 1: return( cycles_pdl_1 != 0 );
        case 2: return( cycles_pdl_2 != 0 );
        case 3: return( cycles_pdl_3 != 0 );
    }

    return( 0 );
}

static uint8_t SW_StartPaddle( uint8_t address, uint8_t data )
{
	uint16_t pdl0  = 128, pdl1 = 128;

	//keybdrv_mouse_get_joystick( &pdl0, &pdl1 );
	keybdrv_mouse_read_joystick( &pdl0, &pdl1 );

	paddle_trigger( pdl0, pdl1, pdl2_val, pdl3_val );
	return( 0x00 );
}

static uint8_t SW_ReadButtons( uint8_t address, uint8_t data )
{
	switch( address & 0x0F )
	{
		case 1: return ( keybdrv_read_button0() ? 0xA0 : 0x00 );
		case 2: return ( keybdrv_read_button1() ? 0xA0 : 0x00 );
        case 3: return ram_get_slot_index();
	}

	return 0xA0;
}

static uint8_t SW_ReadPaddle( uint8_t address, uint8_t data )
{
	switch( address & 0x03 )
	{
		case 0: return( paddle_get( 0 ) ? 0x80 : 0x00 );
		case 1: return( paddle_get( 1 ) ? 0x80 : 0x00 );
		case 2: return( paddle_get( 2 ) ? 0x80 : 0x00 );
		case 3: return( paddle_get( 3 ) ? 0x80 : 0x00 );
	}
	
	return( 0xFF );
}

//////////////////////////////////////////////////////////////////////////////////////

bool_t paddle_get_button( uint8_t button )
{
	switch( button )
	{
		case PADDLE_BUTTON0: return paddle_button0;
		case PADDLE_BUTTON1: return paddle_button1;
	}

	return FALSE;
}

void paddle_set_button( uint8_t button, bool_t state )
{
	switch( button )
	{
		case PADDLE_BUTTON0:
			paddle_button0 = state;
			break;

		case PADDLE_BUTTON1:
			paddle_button1 = state;
			break;
	}
}

void paddle_loop( uint32_t cycles )
{
	paddle_cycles = cycles;

	if( ( cycles_pdl_0 != 0 ) && ( paddle_cycles > cycles_pdl_0 ) ) cycles_pdl_0 = 0;
	if( ( cycles_pdl_1 != 0 ) && ( paddle_cycles > cycles_pdl_1 ) ) cycles_pdl_1 = 0;
	if( ( cycles_pdl_2 != 0 ) && ( paddle_cycles > cycles_pdl_2 ) ) cycles_pdl_2 = 0;
	if( ( cycles_pdl_3 != 0 ) && ( paddle_cycles > cycles_pdl_3 ) ) cycles_pdl_3 = 0;
}

void paddle_init( void * p_board )
{
	uint32_t counter;

	memory_io_set_handler( 0x70, SW_StartPaddle, SW_StartPaddle );

	for( counter = 0x61; counter <= 0x63; counter++ )
	{
		memory_io_set_handler( counter, SW_ReadButtons, NULL );
	}

	for( counter = 0x64; counter <= 0x67; counter++ )
	{
		memory_io_set_handler( counter, SW_ReadPaddle, NULL );
	}

	paddle_button0 = 0;
	paddle_button1 = 0;

	cycles_pdl_0 = 0;
	cycles_pdl_1 = 0;
	cycles_pdl_2 = 0;
	cycles_pdl_3 = 0;

    pdl0_val = 80;
    pdl1_val = 80;
    pdl2_val = 80;
    pdl3_val = 80;

	//keybdrv_joystick_set_mouse_mode(TRUE);
}

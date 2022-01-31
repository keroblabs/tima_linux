#include "ram_ctrl.h"
#include "io_addr.h"
#include "board.h"
#include "sw_switch.h"

//////////////////////////////////////////////////////////////////////////////////////

#define MEMORY_RAM_ADDRESS			0x00000
#define RAM_MEMORY_AUX_BANK			( curr_mem_page + MEMORY_AUX_BANK )
#define GET_MEMORY_PTR(addr)        ( ( addr >= 65536 ) ? &aux_memory[ addr-0x10000 ] : &ram_memory[ addr ] )
#define MAX_SLOT_NUM				7
#define ROM_APPLE_FILE              "rom/APPLE2E.ROM"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    address_read_t mem_read;
    address_write_t mem_write;
    
} ram_ctrl_setup_t;

//////////////////////////////////////////////////////////////////////////////////////

static uint8_t * memory_map_pg0( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_lores( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_hires( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_lores2( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_hires2( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_normal( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_iosel( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_iostb( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_rom_0( uint16_t address, uint8_t ram_sw );
static uint8_t * memory_map_rom_1( uint16_t address, uint8_t ram_sw );

#include "ram_setup.h"

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static uint8_t ram_memory[ 64 * 1024 ];
static uint8_t aux_memory[ TOTAL_RAM_MEMORY * 64 * 1024 ];
static uint8_t rom_memory[64*1024];
static uint8_t * fw_slots[ MAX_SLOT_NUM+1 ];
static uint8_t slot_index;
static uint8_t iostb_index;
static uint32_t curr_mem_page;
static uint8_t dummy_addr_read = 0xA0;
static uint8_t dummy_addr_write;

//////////////////////////////////////////////////////////////////////////////////////

uint8_t global_memory_read( uint32_t mem_address )
{
    return ( mem_address >= 65536 ) ? aux_memory[ mem_address-0x10000 ] : ram_memory[ mem_address ];
}

void global_memory_write( uint32_t mem_address, uint8_t data )
{
    if( mem_address >= 65536 ) aux_memory[ mem_address-0x10000 ] = data;
    else ram_memory[ mem_address ] = data;
}

static void dummy_memory_write( uint16_t address, uint8_t data )
{
}

static uint8_t * memory_map_pg0( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( board->sw_switch[SW_ALTZP] == TRUE )
    {
        mem_address |= RAM_MEMORY_AUX_BANK;
    }

    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_lores( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( board->sw_switch[SW_80STORE] == TRUE )
    {
        if( board->sw_switch[SW_PAGE2] == TRUE )
        {
            mem_address |= RAM_MEMORY_AUX_BANK;
        }
    }
    else if( board->sw_switch[ram_switch] == TRUE )
    {
        mem_address |= RAM_MEMORY_AUX_BANK;
    }
    
    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_lores2( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( board->sw_switch[ram_switch] == TRUE )
    {
        mem_address |= RAM_MEMORY_AUX_BANK;
    }

    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_hires( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( ( board->sw_switch[SW_80STORE] == TRUE ) && ( board->sw_switch[SW_HIRES] == TRUE ) )
    {
        if( board->sw_switch[SW_PAGE2] == TRUE )
        {
            mem_address |= RAM_MEMORY_AUX_BANK;
        }
    }
    else
    {
        if( board->sw_switch[ram_switch] == TRUE )
        {
            mem_address |= RAM_MEMORY_AUX_BANK;
        }
    }

    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_hires2( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( board->sw_switch[ram_switch] == TRUE )
    {
        mem_address |= RAM_MEMORY_AUX_BANK;
    }

    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_normal( uint16_t address, uint8_t ram_switch )
{
    uint32_t mem_address = address;

    if( board->sw_switch[ram_switch] == TRUE )
    {
        mem_address |= RAM_MEMORY_AUX_BANK;
    }

    return GET_MEMORY_PTR(mem_address);
}

static uint8_t * memory_map_iosel( uint16_t address, uint8_t ram_switch )
{
    uint8_t index = ( address & 0x0F00 ) >> 8;

    if( ( slot_index == 0 ) || ( index == 3 ) ) iostb_index = index;
    slot_index = index;

    if( ( board->sw_switch[SW_SLOTXROM] == TRUE ) ||
        ( ( board->sw_switch[SW_SLOT3ROM] == FALSE ) && ( slot_index == 3 ) ) )
    {
        return &rom_memory[ address - 0xC000 + 0x4000 ];
    }
    else if( fw_slots[ slot_index ] != NULL )
    {
        return &fw_slots[ slot_index ][ address & 0x0FF ];
    }
    
    return( &dummy_addr_read );
}

static uint8_t * memory_map_iostb( uint16_t address, uint8_t ram_switch )
{
    uint8_t * ret = &dummy_addr_read;
    
    if( ( board->sw_switch[SW_SLOTXROM] == TRUE ) ||
       ( ( board->sw_switch[SW_SLOT3ROM] == FALSE ) && ( iostb_index == 3 ) ) )
    {
        ret = &rom_memory[ address - 0xC000 + 0x4000 ];
    }
    else if( ( iostb_index != 0 ) && ( fw_slots[ iostb_index ] != NULL ) )
    {
        ret = &fw_slots[ iostb_index ][ address & 0xFFF ];
    }
    else
    {
        ret = &dummy_addr_read;
    }

    if( address == 0xCFFF )
    {
        slot_index = 0;
        iostb_index = 0;
    }
    
    return ret;
}

static uint8_t * memory_map_rom_0( uint16_t address, uint8_t ram_switch )
{
    uint8_t exp_switch = ( ram_switch == SW_RAMRD ) ? SW_EXP16RAM : SW_EXP16WRITE;
    
    if( board->sw_switch[exp_switch] == TRUE )
    {
        uint32_t mem_address = ( ( board->sw_switch[SW_ALTZP] == TRUE ) ? RAM_MEMORY_AUX_BANK : 0 ) | address;
        mem_address -= ( board->sw_switch[SW_EXP16BANK] == FALSE ) ? 0x1000 : 0;

        return GET_MEMORY_PTR(mem_address);
    }
    else if( ram_switch == SW_RAMRD )
    {
        uint16_t rom_address = address - 0x8000;
        return &rom_memory[ rom_address ];
    }
    else
    {
        return &dummy_addr_write;
    }
}

static uint8_t * memory_map_rom_1( uint16_t address, uint8_t ram_switch )
{
    uint8_t exp_switch = ( ram_switch == SW_RAMRD ) ? SW_EXP16RAM : SW_EXP16WRITE;
    
    if( board->sw_switch[exp_switch] == TRUE )
    {
        uint32_t mem_address = ( ( board->sw_switch[SW_ALTZP] == TRUE ) ? RAM_MEMORY_AUX_BANK : 0 ) | address;

        return GET_MEMORY_PTR(mem_address);
    }
    else if( ram_switch == SW_RAMRD )
    {
        uint16_t rom_address = address - 0x8000;
        return &rom_memory[ rom_address ];
    }
    else
    {
        return &dummy_addr_write;
    }
}

uint8_t * ram_ctrl_get_pointer( uint16_t address, bool_t is_read )
{
    const address_map_t map = ram_map[address >> 8];
    return ( map != NULL ) ? map( address, is_read ? SW_RAMRD : SW_RAMWR ) : NULL;
}

void ram_ctrl_insert_slot( uint8_t slot, uint8_t * fw )
{
	if( slot <= MAX_SLOT_NUM ) 
	{
		fw_slots[slot] = fw;
	}
}

uint8_t ram_ctrl_read_8( uint16_t addr )
{
    uint8_t * p_data = ram_ctrl_get_pointer( addr, TRUE );
    return p_data ? *p_data : memory_read_io( addr );
}

uint16_t ram_ctrl_read_16(uint16_t addr)
{
    uint16_t ret = 0;
    
    uint8_t * p_data = ram_ctrl_get_pointer( addr, TRUE );
    if( p_data != NULL ) memcpy( &ret, p_data, sizeof( uint16_t ) );
    
    return ret;
}

void ram_ctrl_write_8(uint16_t addr, uint8_t data)
{
    uint8_t * p_data = ram_ctrl_get_pointer( addr, FALSE );
    if( p_data != NULL )
    {
        *p_data = data;
    }
    else
    {
        memory_write_io( addr, data );
    }
}

uint8_t ram_ctrl_read_fw( uint16_t slot, uint16_t address )
{
	uint8_t slot_index;

	if( address >= 0xc800 ) return 0xA0;

	slot_index = ( address & 0x0F00 ) >> 8;

	if( fw_slots[ slot_index ] != NULL )
	{
		return( fw_slots[ slot_index ][ address & 0x0FF ] );
	}

	return 0xA0;
}

uint8_t * ram_get_dma_pointer( uint16_t addr )
{
    return &ram_memory[addr];
}

void ram_set_mem_page( uint8_t page )
{
    uint32_t new_page = page;
    curr_mem_page = new_page << 16;
}

uint8_t ram_get_slot_index( void )
{
    return slot_index;
}

void ram_reset( void )
{
    slot_index = 0;
    iostb_index = 0;
    curr_mem_page = 0;

    memset( ram_memory, 0xA0, sizeof( ram_memory ) );
    memset( aux_memory, 0xA0, sizeof( aux_memory ) );
}

void ram_ctrl_init( void * p_board )
{
	board = ( board_data_t * )p_board;
	memset( fw_slots, 0x00, sizeof( fw_slots ) );
    board_disc_image_access( ROM_APPLE_FILE, Disc_Mode_Read, 0, ( uint8_t * )&rom_memory[0], 65536 );
}

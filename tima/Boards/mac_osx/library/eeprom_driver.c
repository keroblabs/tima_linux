#include "types.h"
#include "system.h"
#include "SDL_library.h"

//////////////////////////////////////////////////////////////////

#define IMAGE_OFFSET			(0x00000)
#define IMAGE_SIZE				(512)

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

static uint8_t sram_buffer[IMAGE_SIZE];

//////////////////////////////////////////////////////////////////

static int eeprom_init( void )
{
    memset( sram_buffer, 0x00, IMAGE_SIZE );
	return MAL_OK;
}

static int rom_init( void )
{
    return MAL_OK;
}

static int eeprom_write_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
    if( addr >= IMAGE_SIZE ) return MAL_FAIL;
    if( ( addr + size ) >= IMAGE_SIZE ) size = (uint32_t)(IMAGE_SIZE - addr);
    memcpy( &sram_buffer[addr], buffer, size );
	return MAL_OK;
}

static int eeprom_read_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
    if( addr >= IMAGE_SIZE ) return MAL_FAIL;
    if( ( addr + size ) >= IMAGE_SIZE ) size = (uint32_t)(IMAGE_SIZE - addr);
    memcpy( buffer, &sram_buffer[addr], size );
	return MAL_OK;
}

static int rom_read_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
    uint8_t rom_buffer[512];
    uint16_t rom_size;
    
    uint8_t * input = ( uint8_t * )sdl_get_rom_data( &rom_size );
    if( input == NULL ) return MAL_FAIL;
    
    memset( rom_buffer, 0x00, sizeof( rom_buffer ) );
    memcpy( rom_buffer, input, rom_size );
    memcpy( buffer, &rom_buffer[addr], size );

    return MAL_OK;
}

static int rom_write_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
    return MAL_FAIL;
}

static uint32_t eeprom_get_image_size( void )
{
	return IMAGE_SIZE/512;
}

static uint32_t rom_get_image_size( void )
{
    uint16_t rom_size;
    sdl_get_rom_data( &rom_size );
    return ( rom_size < 512 ) ? 1 : ( rom_size / 512 );
}

//////////////////////////////////////////////////////////////////

static const char eeprom_mass_name[] = "/eeprom1";
static const char rom_mass_name[]    = "/rom";

///////////////////////////////////////////////////////////////////////////

static const msd_driver_t eeprom_disc_mount =
{
	eeprom_mass_name,

    eeprom_init,
    eeprom_write_block,
    eeprom_read_block,
    eeprom_get_image_size,
    NULL,
	NULL,
	0,
	0,
	FALSE
};

DECLARE_STORAGE_DEVICE_SECTION( eeprom_disc_mount );

///////////////////////////////////////////////////////////////////////////

static const msd_driver_t rom_disc_mount =
{
    rom_mass_name,
    
    rom_init,
    rom_write_block,
    rom_read_block,
    rom_get_image_size,
    NULL,
    NULL,
    0,
    0,
    FALSE
};

DECLARE_STORAGE_DEVICE_SECTION( rom_disc_mount );

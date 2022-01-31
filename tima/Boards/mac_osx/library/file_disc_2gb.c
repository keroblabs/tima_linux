#include "types.h"
#include "system.h"

//////////////////////////////////////////////////////////////////


#define FILENAME_IMAGE      "/Users/marciocherobim/Projects/GIT/timaos_v41/Applications/instruments/image_dsk/image.bin"

#define IMAGE_SIZE				(32768)

//#define FILENAME_IMAGE		"C:\\Projects\\timaos_v40\\drive_003.vhd"
//#define IMAGE_SIZE			(16384)

#define IMAGE_OFFSET			(0x00000)

//////////////////////////////////////////////////////////////////

uint8_t * create_vhd_footer( uint64_t size, uint8_t * unique_id );

//////////////////////////////////////////////////////////////////

static const uint8_t disc_unique_id[16] = { 0x03, 0x75, 0xdc, 0x81, 0x3e, 0xec, 0x01, 0xff, 0x02, 0x75, 0xb3, 0x33, 0xc0, 0xcd, 0x16, 0xb8 };
//static const uint8_t disc_unique_id[16] = { 0xb8, 0x00, 0x04, 0xf7, 0x26, 0xec, 0x01, 0x8b, 0xf8, 0x03, 0x3e, 0xee, 0x01, 0x59, 0x3b, 0xd1 };
//static const uint8_t disc_unique_id[16] = { 0xec, 0x01, 0xd9, 0x06, 0xe4, 0x01, 0xd8, 0x06, 0xf8, 0x01, 0xd9, 0x1e, 0xe4, 0x01, 0xd9, 0x06 };

//////////////////////////////////////////////////////////////////

static int _unit_init( void )
{
    FILE * fp = NULL;
    int counter;
    uint32_t dummy;
    
	fp = fopen( FILENAME_IMAGE, "r+b" );
    if( fp == NULL )
    {
        dummy = 0;
        fp = fopen( FILENAME_IMAGE, "wb" );
		if( fp == NULL ) return MAL_FAIL;
        
        for( counter = 0; counter < (((IMAGE_SIZE*512)+IMAGE_OFFSET)>>2); counter++ )
        {
            fwrite( &dummy, 1, 4, fp );
        }
        fwrite( create_vhd_footer( ( IMAGE_SIZE * 512 ), ( uint8_t * )disc_unique_id ), 512, 1, fp );
    }
    
    fclose( fp );

	return MAL_OK;
}

static int _unit_write_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
	FILE * fp = NULL;

	addr += IMAGE_OFFSET;
	fp = fopen( FILENAME_IMAGE, "r+b" );
    if( fp == NULL ) return MAL_FAIL;
    
	fseek( fp, addr, SEEK_SET );
	fwrite( buffer, size, 1, fp );
	fclose( fp );

	return MAL_OK;
}

static int _unit_read_block( uint64_t addr, uint8_t * buffer, uint32_t size )
{
	FILE * fp = NULL;

	addr += IMAGE_OFFSET;
	fp = fopen( FILENAME_IMAGE, "r+b" );
    if( fp == NULL ) return MAL_FAIL;
    
	fseek( fp, addr, SEEK_SET );
	fread( buffer, size, 1, fp );
	fclose( fp );

	return MAL_OK;
}

static uint32_t _unit_get_image_size( void )
{
	return IMAGE_SIZE;
}

//////////////////////////////////////////////////////////////////

static const char sdcard_mass_name[ 8 ] = "/sdcard";

///////////////////////////////////////////////////////////////////////////

static const msd_driver_t sdcard_disc_mount =
{
	sdcard_mass_name,

    _unit_init,
    _unit_write_block,
    _unit_read_block,
    _unit_get_image_size,
    NULL,
	NULL,
	NULL,
	0,
	0,
    TRUE
};

DECLARE_DISC_SECTION( sdcard_disc_mount );

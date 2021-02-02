#include "system.h"
#include "mass_mal.h"
#include "debug.h"

///////////////////////////////////////////////////////////////////////////////

#define MAX_SECTOR_CACHE		6
#define MAL_BLOCK_SIZE			(512)

///////////////////////////////////////////////////////////////////////////////

typedef struct _cache_sector_t
{
    uint8_t buffer[ 512 ];
    uint32_t address;
    uint32_t lun;
    
    struct _cache_sector_t * next;
    
} cache_sector_t;

///////////////////////////////////////////////////////////////////////////////

static uint32_t cached_lun;
static uint32_t cached_index_lun;

static cache_sector_t cache_sector[MAX_SECTOR_CACHE];

static cache_sector_t * first_sector;
static cache_sector_t * last_sector;

///////////////////////////////////////////////////////////////////////////////

void _mal_cache_init( void )
{
    int i;
    // int size = (int)sizeof( cache_sector );
    
    memset( &cache_sector, 0x00, sizeof( cache_sector ) );
    
    first_sector = &cache_sector[0];
    last_sector = &cache_sector[MAX_SECTOR_CACHE-1];
    cache_sector[0].lun = LUN_NOT_FOUND;
    
    for( i = 1; i < MAX_SECTOR_CACHE; i++ )
    {
        cache_sector[i].lun = LUN_NOT_FOUND;
        cache_sector[i-1].next = &cache_sector[i];
        cache_sector[i].next = NULL;
    }
}


uint8_t * _mal_cache_add( uint8_t * buffer, uint32_t address, uint32_t lun )
{
    cache_sector_t * sector = first_sector;
    cache_sector_t * previous = NULL;
    
    while( sector != NULL )
    {
        if( ( sector->address == address ) &&
           ( sector->lun == lun ) )
        {
            break;
        }
        
        if( sector->next == NULL ) break;
        previous = sector;
        sector = sector->next;
    }
    
    if( previous != NULL )
    {
        previous->next = sector->next;
        if( sector->next == NULL ) last_sector = previous;
        sector->next = first_sector;
        first_sector = sector;
    }
    
    sector->address = address;
    sector->lun = lun;
    
    if( buffer != NULL )
        memcpy( sector->buffer, buffer, 512 );
    
    return sector->buffer;
}

uint8_t * _mal_cache_get( uint8_t * buffer, uint32_t address, uint32_t lun )
{
    cache_sector_t * sector = first_sector;
    cache_sector_t * previous = NULL;
    
    while( sector != NULL )
    {
        if( ( sector->address == address ) &&
           ( sector->lun == lun ) )
        {
            if( previous != NULL )
            {
                previous->next = sector->next;
                if( sector->next == NULL ) last_sector = previous;
                sector->next = first_sector;
                first_sector = sector;
            }
            
            if( buffer != NULL )
                memcpy( buffer, sector->buffer, 512 );
            
            return sector->buffer;
        }
        
        previous = sector;
        sector = sector->next;
    }
    
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void MAL_Init_All( void )
{
    //uint32_t counter;
    //msd_driver_t * driver;

    cached_index_lun = ( NEG_U32 );
    cached_lun = ( NEG_U32 );
    
    _mal_cache_init();
    
    /*
    counter = 0;
    while( ( driver = system_Get_Storage_Driver( counter ) ) != NULL )
    {
    	if( driver->init != NULL ) driver->init();
        counter++;
    }
     */
}

uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    
    if( driver == NULL ) return MAL_FAIL;
    if( driver->init == NULL ) return MAL_FAIL;
    
    status = driver->init();
    if ( status )
    {
        return MAL_FAIL;
    }
    
    return status;
}

uint16_t MAL_IsMount( uint8_t lun )
{
    uint16_t status = MAL_OK;
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    
    if( driver == NULL ) return MAL_FAIL;
    if( driver->is_mount == FALSE ) return MAL_NO_MOUNT;
    
    return status;
}

uint16_t MAL_Write(uint8_t lun, uint64_t Memory_Offset, uint8_t *Writebuff, uint16_t Transfer_Length)
{
    uint16_t status = MAL_OK;
    uint64_t mem_address;
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return MAL_FAIL;
    
    mem_address = Memory_Offset + driver->addr_offset;
    status = driver->write_block(mem_address, Writebuff, Transfer_Length);
    if ( status ) return MAL_FAIL;
    
    _mal_cache_add( Writebuff, (uint32_t)(mem_address/512), lun );
    
    return status;
}

uint16_t MAL_Read(uint8_t lun, uint64_t Memory_Offset, uint8_t *Readbuff, uint16_t Transfer_Length)
{
    uint16_t status = MAL_OK;
    uint64_t mem_address;
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return MAL_FAIL;
    
    mem_address = Memory_Offset + driver->addr_offset;
    
    if( _mal_cache_get( Readbuff, (uint32_t)(mem_address/512), lun ) != NULL ) return status;
    status = driver->read_block(mem_address, Readbuff, Transfer_Length);
    if ( status ) return MAL_FAIL;
    
    _mal_cache_add( Readbuff, (uint32_t)(mem_address/512), lun );
    
    return status;
}

uint8_t MAL_GetLun( const char * name )
{
    uint8_t counter = 0;
    msd_driver_t * driver;
    
    while( 1 )
    {
        driver = system_Get_Storage_Driver( counter );
        
        if( driver == NULL ) return LUN_NOT_FOUND;
        if( ( driver->init != NULL ) && !strcmp( driver->name, name ) ) break;
        
        counter++;
    }
    
    return counter;
}

uint32_t MAL_GetBlockCount( uint8_t lun )
{
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return 0;
    
    if( driver->get_block_count != NULL )
    {
        return driver->get_block_count();
    }
    
    return driver->page_count;
}

uint32_t MAL_GetBlockSize( uint8_t lun )
{
    return MAL_BLOCK_SIZE;
}

uint16_t MAL_GetStatus (uint8_t lun)
{
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return MAL_FAIL;
    
    return MAL_OK;
}

uint8_t * MAL_RetrieveInquiryData( uint8_t lun )
{
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return NULL;
    
    return( ( uint8_t * )driver->inquiry_data );
}

const char * MAL_RetrieveVolumeName( uint8_t lun )
{
    msd_driver_t * driver;
    
    driver = system_Get_Storage_Driver( lun );
    if( driver == NULL ) return NULL;
    
    return( driver->name );
}

uint32_t MAL_GetTotalLun( void )
{
    uint32_t counter = 0;
    
    while( system_Get_Storage_Driver( counter ) != NULL )
    {
        counter++;
    }
    
    return( counter );
}



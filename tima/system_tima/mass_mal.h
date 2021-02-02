#ifndef __MASS_MAL_H
#define __MASS_MAL_H

///////////////////////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////////////////////

#define MAL_OK                  0
#define MAL_FAIL                1
#define MAL_NO_MOUNT			2

#define LUN_NOT_FOUND           ((uint8_t)0xFF)

///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    const char * name;
    
    int (*init)( void );
    int (*write_block)( uint64_t addr, uint8_t *buff, uint32_t BlockSize );
    int (*read_block)( uint64_t addr, uint8_t *buff, uint32_t BlockSize );
    //int (*format_unit)( void );
    
    uint32_t (*get_block_count)( void );
    
    // data used by USB system
    bool_t (*usb_present)( void );
    
    const uint8_t * inquiry_data;
    
    uint32_t addr_offset;
    uint32_t page_count;
    bool_t is_mount;
    
} msd_driver_t;

///////////////////////////////////////////////////////////////////////////////

void 	 MAL_Init_All( void );
uint16_t MAL_Init(uint8_t lun);
uint16_t MAL_Write(uint8_t lun, uint64_t Memory_Offset, uint8_t *Writebuff, uint16_t Transfer_Length);

uint16_t MAL_Read(uint8_t lun, uint64_t Memory_Offset, uint8_t *Readbuff, uint16_t Transfer_Length);
uint16_t MAL_GetStatus (uint8_t lun);

uint8_t * MAL_RetrieveInquiryData( uint8_t lun );
uint32_t  MAL_GetTotalLun( void );

uint8_t   MAL_GetLun( const char * name );

uint32_t MAL_GetBlockCount( uint8_t lun );
uint32_t MAL_GetBlockSize( uint8_t lun );

uint16_t MAL_IsMount( uint8_t lun );

const char * MAL_RetrieveVolumeName( uint8_t lun );

///////////////////////////////////////////////////////////////////////////////

#endif /* __MASS_MAL_H */


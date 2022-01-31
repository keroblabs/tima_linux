#ifndef _RAM_CTRL_H__
#define _RAM_CTRL_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "datatypes.h"

//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////

void ram_ctrl_insert_slot( uint8_t slot, uint8_t * fw );
void ram_ctrl_init( void * p_board );
void ram_reset( void );

uint8_t ram_ctrl_read_8( uint16_t addr );
uint16_t ram_ctrl_read_16(uint16_t addr);

void ram_ctrl_write_8(uint16_t addr, uint8_t data);

uint8_t * ram_ctrl_get_pointer( uint16_t address, bool_t is_read );

uint8_t global_memory_read( uint32_t mem_address );
void global_memory_write( uint32_t mem_address, uint8_t data );

void ram_ctrl_update_map( void );

uint8_t * ram_get_dma_pointer( uint16_t addr );

void ram_set_mem_page( uint8_t page );

uint8_t ram_get_slot_index( void );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _RAM_CTRL_H__

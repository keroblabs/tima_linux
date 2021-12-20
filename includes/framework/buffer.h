#ifndef __BUFFER_H__
#define __BUFFER_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

//////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    uint32_t pointer_in;
    uint32_t pointer_out;

    void * mutex;
    void * cond;
    
    uint32_t size;
    uint32_t fill_size;
    bool_t is_static;

    uint8_t *buffer;

} buffer_data_t;

//////////////////////////////////////////////////////////////////////////////////////

void buffer_init( buffer_data_t * buffer_data, uint32_t size );
void buffer_destroy( buffer_data_t * buffer_data );
void buffer_init_static( buffer_data_t * buffer_data, uint8_t * buffer, uint32_t size );

uint8_t buffer_read( buffer_data_t * buffer_data );
uint32_t buffer_read_buffer( buffer_data_t * buffer_data, uint8_t * out_data, uint32_t size );
uint32_t buffer_wait_for_data( buffer_data_t * buffer_data, uint8_t * buffer, uint32_t size, uint32_t timeout );

void buffer_write( buffer_data_t * buffer_data, uint8_t in_data );
void buffer_write_buffer( buffer_data_t * buffer_data, uint8_t * in_data, uint32_t size );

uint32_t buffer_get_available_size( buffer_data_t * buffer_data );
uint32_t buffer_get_size( buffer_data_t * buffer_data );
void buffer_reset( buffer_data_t * buffer_data );

bool_t buffer_is_full( buffer_data_t * buffer_data );
bool_t buffer_is_empty( buffer_data_t * buffer_data );


//////////////////////////////////////////////////////////////////////////////////////

#endif // __BUFFER_H__


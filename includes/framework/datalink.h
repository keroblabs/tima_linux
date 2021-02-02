#ifndef __datalink_h__
#define __datalink_h__

///////////////////////////////////////////////////////////////

#include "types.h"
#include "device.h"
#include "timer.h"
#include "pipe.h"
#include "crc.h"
#include "random.h"

///////////////////////////////////////////////////////////////

#define MAX_HANDLERS        10
#define DATALINK_BROADCAST  0

///////////////////////////////////////////////////////////////

typedef void ( *datalink_handler_t )( uint8_t source, uint8_t * buffer, uint16_t size );

typedef struct _datalink_handler_t
{
    uint8_t id;
    pipe_data_t pipe_rx;
    void * p_data;

} datalink_node_t;

typedef struct _datalink_t
{
    device_t * comm_dev;
    pipe_data_t pipe_tx;

    uint8_t state;
    timer_data_t rx_timeout;
    timer_data_t tx_access;

    uint8_t * buffer;
    uint16_t size;
    uint16_t pointer;
    crc_data_t crc_data;
    random_t access_random;
    bool_t rts;

    uint8_t header;
    uint8_t footer;

    datalink_node_t * node_list[ MAX_HANDLERS ];

    struct _datalink_t * p_next;

} datalink_t;

///////////////////////////////////////////////////////////////

void datalink_global_init( void );

void datalink_init( datalink_t * p_data, device_t * p_dev, uint8_t header, uint8_t footer, uint32_t polynom );

void datalink_setup_node( datalink_node_t * p_node, device_t * p_dev, uint8_t id );

void datalink_send_data( datalink_node_t * p_node, uint8_t destination, uint8_t * buffer, uint16_t size );

uint8_t * datalink_waitfor_node( datalink_node_t * p_node, uint16_t * size );

///////////////////////////////////////////////////////////////

#endif // __datalink_h__

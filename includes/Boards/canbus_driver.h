#ifndef APPLICATIONS_INSTRUMENTS_SOURCE4_CANBUS_H_
#define APPLICATIONS_INSTRUMENTS_SOURCE4_CANBUS_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

typedef struct
{
    uint16_t id;
    uint8_t  data[8];
    uint8_t  len;
} CAN_msg_t;

typedef void ( *canbus_handler_t )( const CAN_msg_t *msg );

typedef struct
{
    uint16_t id;
    canbus_handler_t cb;

} CAN_filter_t;

////////////////////////////////////////////////////////////////////

int canbus_start( const char * can_port, uint32_t rate, const CAN_filter_t * filter, uint16_t filter_size );
int canbus_send( int socket, CAN_msg_t * msg );

////////////////////////////////////////////////////////////////////

#endif /* APPLICATIONS_INSTRUMENTS_SOURCE4_CANBUS_H_ */

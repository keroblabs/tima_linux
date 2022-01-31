#ifndef __SOCKET_LIBRARY_DRV_H__
#define __SOCKET_LIBRARY_DRV_H__

///////////////////////////////////////////////////////////////

#include "types.h"
#include <sys/socket.h>

///////////////////////////////////////////////////////////////

#define MIN_SOCKET_RESP_SIZE    25
#define SOCKET_ERROR_TOKEN        "ERR"

#define SOCKET_FAIL_OPEN        ( ( uint32_t )-3 )
#define SOCKET_NOT_READY        ( ( uint32_t )-2 )
#define SOCKET_FAIL_LISTEN      ( ( uint32_t )-1 )

//////////////////////////////////////////////////////////////////////////////////////

typedef struct _socket_dev_data_t
{
    uint8_t mode;
    void * curr_dev;
    
    void * data;
    
} socket_dev_data_t;

typedef struct _addr_net_t
{
    uint8_t ip_num[4];
    uint16_t port;
    uint8_t index;
    
} addr_net_t;

///////////////////////////////////////////////////////////////

void socket_library_init( void );

uint32_t socket_accept_port( uint32_t socket );
uint32_t socket_connect_addr( uint8_t * ip_addr, uint16_t port );
uint32_t socket_listen_port( uint16_t port );

int socket_read_data( uint32_t socket, uint8_t *buffer, uint32_t max_size );
int socket_write_data( uint32_t socket, uint8_t *buffer, uint32_t size );
int socket_read( uint32_t socket, uint8_t *buffer, uint32_t max_size );

void socket_close_port( uint32_t socket );

int setNonblocking(int fd);

///////////////////////////////////////////////////////////////


#endif // __SOCKET_LIBRARY_DRV_H__


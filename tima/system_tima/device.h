#ifndef __DEVICE_H__
#define __DEVICE_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

//////////////////////////////////////////////////////////////////////////////////////

// not sure what should be the highest index for a device
// for now limit it on 16384
#define MAX_DEVICE_INDEX        16384

#define MIN_SOCKET_RESP_SIZE    25
#define SOCKET_ERROR_TOKEN		"ERR"

#define SOCKET_ACCEPTED         ( ( uint32_t )-4 )
#define SOCKET_FAIL_OPEN        ( ( uint32_t )-3 )
#define SOCKET_NOT_READY        ( ( uint32_t )-2 )
#define SOCKET_FAIL_LISTEN      ( ( uint32_t )-1 )

enum
{
    SOCKET_DEV_CONNECTED,
    SOCKET_DEV_LISTENING,
    SOCKET_DEV_ACCEPTED
};

//////////////////////////////////////////////////////////////////////////////////////

enum
{
    DEV_MODE_CHANNEL,
    DEV_MODE_BYTE,
            
    DEVICE_IOCTRL_PARAM = 0x00000100,
    DEVICE_GET_API,

	DEVICE_GET_CONFIG_DATA   = 0x00010000,
    DEVICE_SET_CONFIG_DATA   = 0x00020000,
    DEVICE_GET_RUNTIME_VALUE = 0x00030000,
    DEVICE_SET_RUNTIME_VALUE = 0x00040000,
    DEVICE_IS_DATA_AVAILABLE = 0x00050000,
    DEVICE_IS_TX_BUSY        = 0x00060000,
    DEVICE_BLOCKING_STATE    = 0x00070000,
    
    DEVICE_USER_DEFINED,
    
};

typedef struct _device_data_t
{
    const char * name;
    
    bool_t * in_use;
    
    void ( *init )( uint32_t index );
    void ( *disable )( uint32_t index );
    void ( *trig_tx )( uint32_t index );
    bool_t ( *validate )( uint32_t index );
    int ( *get_index )( char * param );
    uint32_t ( *io_ctrl )( uint32_t index, uint32_t param, void * value );
    bool_t ( *is_open )( uint32_t index );
    
    uint8_t dev_mode;

    // for buffer use
    void * rx_channel;
    void * tx_channel;
    
} device_data_t;

typedef struct _device_socket_t_
{
	void ( *init )( void );
    uint32_t ( *listen )( uint16_t port );
    uint32_t ( *connect )( uint8_t * ip_addr, uint16_t port );
    uint32_t ( *connect_url )( char * url_str, uint16_t port );
    uint32_t ( *accept )( uint32_t socket );

    int ( *read )( uint32_t socket, uint8_t *buffer, uint32_t max_size );
    int ( *write )( uint32_t socket, uint8_t *buffer, uint32_t size );

    void ( *close )( uint32_t socket );
    bool_t ( *is_open )( uint32_t socket );

    char * ( *ctrl_ip )( void );

} device_socket_t;

typedef struct _device_location_t
{
    device_data_t * device_ptr;
    uint32_t device_index;
    
} device_t;

//////////////////////////////////////////////////////////////////////////////////////

bool_t device_open_ex( const char * name, device_t * dev );
device_t * device_open( const char * name );
device_t * device_socket_open( uint8_t * ip_addr, uint16_t port );
device_t * device_socket_open_url( char * url_addr, uint16_t port );

uint32_t device_is_rx_pending( device_t * dev );
uint32_t device_is_tx_pending( device_t * dev );

uint32_t device_ioctrl( device_t * file, uint32_t param, void * data );

uint32_t device_write_buffer( device_t * dev, uint8_t * data, uint32_t size );
uint32_t device_read_buffer( device_t * dev, uint8_t * data, uint32_t size );

uint8_t device_read( device_t * dev  );
void device_write( device_t * dev, uint8_t data );

void device_close( device_t * dev );

device_t * device_socket_open( uint8_t * ip_addr, uint16_t port );
device_t * device_socket_listen( uint16_t port );
device_t * device_socket_accept( device_t * dev );

//////////////////////////////////////////////////////////////////////////////////////

#endif // __DEVICE_H__



#include "system.h"
#include "datalink.h"
#include "debug.h"

///////////////////////////////////////////////////////////////

enum
{
    DATALINK_IDLE,
    DATALINK_WAIT_HEADER,
    DATALINK_WAIT_SIZE,
    DATALINK_RX_PAYLOAD,
    DATALINK_WAIT_FOOTER,
};

///////////////////////////////////////////////////////////////

#define DATALINK_MAX_PAYLOAD        2048
#define DATALINK_RX_TIMEOUT         300
#define DATALINK_EXTRA_SIZE         7
#define DATALINK_PAYLOAD_SIZE       4       // [header] [size][size] [destination] [source] {data} [footer] [crc8]

#define DATALINK_RANDOM_SEED        52154785456

///////////////////////////////////////////////////////////////

static datalink_t * first_datalink = NULL;
static datalink_t * last_datalink = NULL;
static void * datalink_mutex;

///////////////////////////////////////////////////////////////

static datalink_t * datalink_find( device_t * device )
{
    datalink_t * search;

    tthread_mutex_lock( datalink_mutex );

    search = first_datalink;

    while( search )
    {
        if( device == search->comm_dev ) break;
        search = search->p_next;
    }

    tthread_mutex_unlock( datalink_mutex );

    return search;
}

static uint8_t datalink_get_checksum( datalink_t * p_data, uint8_t * buffer, uint16_t size )
{
    //return ( uint8_t )( crc_calculate( &p_data->crc_data, buffer, size - 1 ) & 0x0FF );
    return 0xdd;
}

static void datalink_process_tx( datalink_t * p_data )
{
    if( ( p_data->state == DATALINK_IDLE ) && ( pipe_is_empty( &p_data->pipe_tx ) != TRUE ) )
    {
        uint16_t size;
        uint8_t * buffer = pipe_read( &p_data->pipe_tx, &size );
        device_write_buffer( p_data->comm_dev, buffer, size );
        MFREE( buffer );
    }
}

static void datalink_reset( datalink_t * p_data )
{
    timer_Stop( &p_data->rx_timeout );
    p_data->state = DATALINK_IDLE;
    datalink_process_tx( p_data );

    if( p_data->buffer != NULL )
    {
        MFREE( p_data->buffer );
        p_data->buffer = NULL;
    }
}

static void datalink_process_device( datalink_t * p_data )
{
    uint8_t rx_char;
    uint16_t rx_size;
    uint8_t counter;

    if( p_data->comm_dev == NULL ) return;

    if( timer_Check( &p_data->rx_timeout ) )
    {
        datalink_reset( p_data );
    }

    switch( p_data->state )
    {
        case DATALINK_IDLE:
            if( device_is_rx_pending( p_data->comm_dev ) == 0 )
            {
                datalink_process_tx( p_data );
                break;
            }
            device_read_buffer( p_data->comm_dev, &rx_char, 1 );

            if( rx_char != p_data->header ) break;

            // got header
            p_data->state = DATALINK_WAIT_SIZE;
            p_data->size = 0;
            timer_Start( &p_data->rx_timeout, DATALINK_RX_TIMEOUT );
            /* no break */

        case DATALINK_WAIT_SIZE:
            if( device_is_rx_pending( p_data->comm_dev ) < 2 ) break;
            device_read_buffer( p_data->comm_dev, ( uint8_t * )&rx_size, 2 );

            if( rx_size > DATALINK_MAX_PAYLOAD )
            {
                // header size exceeds
                datalink_reset( p_data );
                break;
            }

            p_data->state   = DATALINK_RX_PAYLOAD;
            p_data->size    = rx_size + ( DATALINK_EXTRA_SIZE - DATALINK_PAYLOAD_SIZE );
            p_data->pointer = DATALINK_EXTRA_SIZE - DATALINK_PAYLOAD_SIZE;

            p_data->buffer = ( uint8_t * )MMALLOC( p_data->size );
            if( p_data->buffer == NULL )
            {
                datalink_reset( p_data );
                break;
            }

            p_data->buffer[0] = p_data->header;
            memcpy( &p_data->buffer[1], &rx_size, sizeof( rx_size ) );

            timer_Start( &p_data->rx_timeout, DATALINK_RX_TIMEOUT );
            /* no break */

        case DATALINK_RX_PAYLOAD:
            while( device_is_rx_pending( p_data->comm_dev ) )
            {
                rx_size = ( uint16_t )device_is_rx_pending( p_data->comm_dev );
                if( rx_size > p_data->size ) rx_size = p_data->size;
                if( p_data->pointer < p_data->size )
                {
                    device_read_buffer( p_data->comm_dev, &p_data->buffer[p_data->pointer], rx_size );
                    p_data->pointer += rx_size;
                    timer_Start( &p_data->rx_timeout, DATALINK_RX_TIMEOUT );
                }

                if( p_data->pointer >= p_data->size )
                {
                    // finished payload, validate
                    if( ( p_data->buffer[p_data->size-1] == datalink_get_checksum( p_data, p_data->buffer, p_data->size ) ) &&
                        ( p_data->buffer[p_data->size-2] == p_data->footer ) )
                    {
                        DEBUG_PRINTK( "Received: 0x%02x -> 0x%02x\r\n", p_data->buffer[4], p_data->buffer[3] );
                        for( counter = 0; counter < MAX_HANDLERS; counter++ )
                        {
                            if( ( p_data->node_list[counter] != NULL ) &&
                                ( ( p_data->node_list[counter]->id == p_data->buffer[3] ) || ( p_data->buffer[3] == DATALINK_BROADCAST ) ) )
                            {
                                pipe_send_buffer( &p_data->node_list[counter]->pipe_rx, &p_data->buffer[4], p_data->size - DATALINK_EXTRA_SIZE + 1 );
                            }
                        }
                    }

                    datalink_reset( p_data );
                    break;
                }
            }
            break;
    }
}

void datalink_init( datalink_t * p_data, device_t * p_dev, uint8_t header, uint8_t footer, uint32_t polynom )
{
    memset( p_data, 0x00, sizeof( datalink_t ) );

    p_data->comm_dev = p_dev;
    p_data->header   = header;
    p_data->footer   = footer;
    p_data->pointer  = 0;
    p_data->size     = 0;
    p_data->state    = DATALINK_IDLE;
    p_data->rts      = FALSE;

    pipe_init( &p_data->pipe_tx, "DATALINK_PIPE_TX", 16 );
    timer_Stop( &p_data->rx_timeout );
    timer_Stop( &p_data->tx_access );
    crc_init( &p_data->crc_data, polynom, 0x00 );
    rand_init( &p_data->access_random, DATALINK_RANDOM_SEED, 25 );

    tthread_mutex_lock( datalink_mutex );
    if( first_datalink == NULL ) first_datalink = p_data;
    else last_datalink->p_next = p_data;
    last_datalink = p_data;
    tthread_mutex_unlock( datalink_mutex );
}

uint8_t * datalink_waitfor_node( datalink_node_t * p_node, uint16_t * size )
{
#ifdef _USE_LINUX
    uint8_t * ret;
    ret = pipe_wait_for_data( &p_node->pipe_rx, size );
    return ret;
#else
    return pipe_read( &p_node->pipe_rx, size );
#endif
}

void datalink_setup_node( datalink_node_t * p_node, device_t * p_dev, uint8_t id )
{
    uint8_t counter;

    datalink_t * p_data = datalink_find( p_dev );
    if( p_data == NULL ) return;

    p_node->id      = id;
    p_node->p_data  = p_data;
    pipe_init( &p_node->pipe_rx, "DATALINK_PIPE_RX", 16 );

    for( counter = 0; counter < MAX_HANDLERS; counter++ )
    {
        if( p_data->node_list[counter] == NULL )
        {
            DEBUG_PRINTK( "Node added: %d\r\n", counter );
            p_data->node_list[counter] = p_node;
            break;
        }
    }
}

void datalink_setup_tx_only_node( datalink_node_t * p_node, device_t * p_dev, uint8_t id )
{
    datalink_t * p_data = datalink_find( p_dev );
    if( p_data == NULL ) return;

    p_node->id      = id;
    p_node->p_data  = p_data;
}

void datalink_send_data( datalink_node_t * p_node, uint8_t destination, uint8_t * buffer, uint16_t size )
{
    uint8_t * tx_buffer;
    uint16_t total_size  = size + DATALINK_EXTRA_SIZE;
    uint16_t packet_size = size + DATALINK_PAYLOAD_SIZE;

    datalink_t * p_data = ( datalink_t * )p_node->p_data;
    if( p_data == NULL ) return;

    tx_buffer = MMALLOC(total_size);
    if( tx_buffer == NULL ) return;

    tx_buffer[0] = p_data->header;
    memcpy( &tx_buffer[1], &packet_size, sizeof( packet_size ) );
    tx_buffer[3] = destination;
    tx_buffer[4] = p_node->id;
    memcpy( &tx_buffer[5], buffer, size );
    tx_buffer[5+size] = p_data->footer;
    tx_buffer[6+size] = datalink_get_checksum( p_data, tx_buffer, total_size );

    pipe_write( &p_data->pipe_tx, tx_buffer, total_size );
}

static void datalink_process( void )
{
    datalink_t * search = first_datalink;

    while( search )
    {
        datalink_process_device( search );
        search = search->p_next;
    }
}

#if defined _USE_MULTITHREAD
static void datalink_process_thread( void )
{
    datalink_t * search;

    while( 1 )
    {
        tthread_mutex_lock( datalink_mutex );
        datalink_process();
        tthread_mutex_unlock( datalink_mutex );

        tthread_sleep_ms( 10 );
    }
}
#else
DECLARE_PROCESS_SECTION(datalink_process);
#endif

void datalink_global_init( void )
{
#if defined _USE_MULTITHREAD
    datalink_mutex = tthread_mutex_init();
    tthread_create( datalink_process_thread );
#endif
}

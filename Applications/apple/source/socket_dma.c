#include "socket_dma.h"
#include "socket_library.h"
#include "hard_drive.h"
#include "timer.h"
#include "board.h"
#include "ram_ctrl.h"

////////////////////////////////////////////////////////////////////

typedef struct command_t_
{
    uint32_t upcode;
    uint32_t start;
    uint32_t len;
    uint8_t  data[];

} command_t;

////////////////////////////////////////////////////////////////////

#define SOCKET_STATE_DISCONNECTED       0
#define SOCKET_STATE_WAIT_COMMAND       1
#define SOCKET_STATE_WAIT_DATA          2
#define SOCKET_STATE_COMMAND_DONE       3
#define SOCKET_STATE_TERMINATE          4

#define SOCKET_LISTEN_TIME_INTERVAL     500

////////////////////////////////////////////////////////////////////

static timer_data_t timer_listen;

static board_data_t * board;

static uint8_t socket_state;
static uint32_t socket_accepted;
static uint32_t listen_socket;

static uint32_t rx_pointer;
static uint8_t buffer[2048];
static command_t command;


////////////////////////////////////////////////////////////////////

void socket_dma_process( void )
{
    uint8_t * ram_addr_dma;
    
    if( socket_state == SOCKET_STATE_DISCONNECTED )
    {
        if( timer_Check( &timer_listen) )
        {
            timer_Reload( &timer_listen );

            if( listen_socket == SOCKET_FAIL_LISTEN )
            {
                listen_socket = socket_listen_port( 15500 );
            }
            else if( listen_socket != SOCKET_NOT_READY )
            {
                socket_accepted = socket_accept_port( listen_socket );
                if( ( socket_accepted != SOCKET_FAIL_LISTEN ) && ( socket_accepted != SOCKET_NOT_READY ) )
                {
                    socket_state = SOCKET_STATE_WAIT_COMMAND;
                    printf( "Connected\n" );
                }
            }
        }
    }
    else if( ( socket_state == SOCKET_STATE_WAIT_COMMAND ) && ( socket_read_data( socket_accepted, NULL, 0 ) >= sizeof( command ) ) )
    {
        socket_read( socket_accepted, ( uint8_t * )&command, sizeof( command ) );
        rx_pointer = 0;

        switch( command.upcode )
        {
            case 'Q': // disconnect
                socket_state = SOCKET_STATE_TERMINATE;
                break;

            case 0x10: // write
                if( ( command.start < 0x10000 ) && ( ( command.start + command.len ) < 0xFFFF ) )
                {
                    printf( "DMA Write %d data to $%04x\n", command.len, command.start );
                    socket_state = SOCKET_STATE_WAIT_DATA;
                }
                break;

            case 0x20: // read
                if( ( command.start < 0x10000 ) && ( ( command.start + command.len ) < 0xFFFF ) )
                {
                    printf( "DMA Read %d data to $%04x\n", command.len, command.start );
                    ram_addr_dma = ram_get_dma_pointer( command.start );
                    socket_write_data( socket_accepted, ( uint8_t * )ram_addr_dma, command.len ) ;
                    socket_state = SOCKET_STATE_COMMAND_DONE;
                }
                break;

            case 0x30:
            case 0x31:
                if( command.len == 512 )
                {
                    printf( "HDD write %d block\n", command.start );
                    socket_state = SOCKET_STATE_WAIT_DATA;
                }
                break;

            case 0x40:
            case 0x41:
                if( command.len == 512 )
                {
                    printf( "HDD read %d block\n", command.start );
                    hdd_block_read( command.upcode << 7, command.start, &buffer[sizeof(command_t)] );
                    socket_write_data( socket_accepted, ( uint8_t * )&buffer[sizeof(command_t)], command.len ) ;
                    socket_state = SOCKET_STATE_COMMAND_DONE;
                }
                break;
        }

        if( socket_state == SOCKET_STATE_WAIT_COMMAND ) socket_state = SOCKET_STATE_TERMINATE;
        else if( socket_state == SOCKET_STATE_COMMAND_DONE ) SOCKET_STATE_WAIT_COMMAND;
    }
    else if(    ( socket_state == SOCKET_STATE_WAIT_DATA )
             && ( rx_pointer < command.len )
             && ( socket_read_data( socket_accepted, NULL, 0 ) > 0 ) )
    {
        if( command.upcode == 0x10 )
        {
            int read_size = socket_read_data( socket_accepted, ( uint8_t * )buffer, MIN( 1024, command.len - rx_pointer ) );
            printf( "Received %d [0x%02X]\n", read_size, buffer[0] );

            ram_addr_dma = ram_get_dma_pointer( command.start );
            memcpy( ram_addr_dma, buffer, read_size );
            rx_pointer += read_size;

            if( rx_pointer >= command.len )
            {
                printf( "DMA Write done\n" );
                rx_pointer = 0;
                socket_state = SOCKET_STATE_WAIT_COMMAND;

                command.upcode = 0xF0;
                socket_write_data( socket_accepted, ( uint8_t * )&buffer[0], sizeof(command_t) );
            }
        }
        else if( ( command.upcode == 0x30 ) || ( command.upcode == 0x31 ) )
        {
            int read_size = socket_read_data( socket_accepted, ( uint8_t * )&buffer[rx_pointer], command.len - rx_pointer );
            rx_pointer += read_size;

            if( rx_pointer >= command.len )
            {
                hdd_block_write( command.upcode & 0x01, command.start, command.data );
                printf( "HDD write done\n" );
                rx_pointer = 0;
                socket_state = SOCKET_STATE_WAIT_COMMAND;
            }
        }
    }
    else if( socket_state == SOCKET_STATE_TERMINATE )
    {
        socket_close_port( socket_accepted );
        socket_state = SOCKET_STATE_DISCONNECTED;
        printf( "Disconnected\n" );
        timer_Reload( &timer_listen );
    }
}

void socket_dma_init( void * p_board )
{
    timer_Start( &timer_listen, SOCKET_LISTEN_TIME_INTERVAL );

    board = ( board_data_t * )p_board;
    socket_state = SOCKET_STATE_DISCONNECTED;
    listen_socket = socket_listen_port( 15500 );
    command.upcode = 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/tcp.h>

#include "socket_library.h"

///////////////////////////////////////////////////////////////////////////

#define MAX_SOCKET              20
#define QUEUE_SIZE              32
#define BUF_DATA_SIZE           1024

#define SOCKET                  int

#define __SOCKET_FF_PROBLEM

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

int setNonblocking(int fd)
{
    int flags;
    
    /* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    /* Otherwise, use the old way of doing it */
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}

void socket_library_init( void )
{
}

void socket_close_port( uint32_t socket )
{
    close( socket );
}

uint32_t socket_accept_port( uint32_t socket )
{
    SOCKET sa;
    struct sockaddr_in sin;
    uint32_t len = sizeof(sin);
    
    sa = accept(socket, (struct sockaddr*)&sin, &len);                  // block for connection request
    if ((int)sa < 0)
    {
        // 10035 = no connection accepted yet
        
        if((errno != 10035)&&(errno != 35)&&(errno != 11))
        {
            printf("accept error %d ", errno );
            return SOCKET_FAIL_LISTEN;
        }
        
        // not connected yet
        return SOCKET_NOT_READY;
    }
    
    int flag = 1;
    setsockopt(sa, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    
    return ( uint32_t )sa;
}

uint32_t socket_connect_addr( uint8_t * ip_addr, uint16_t port )
{
    SOCKET      sa;
    struct	    sockaddr_in channel;
    int		    b;
    
    uint32_t ip_addr_int;
    
    ip_addr_int = ip_addr[0];
    ip_addr_int = ( ip_addr_int << 8 ) | ip_addr[1];
    ip_addr_int = ( ip_addr_int << 8 ) | ip_addr[2];
    ip_addr_int = ( ip_addr_int << 8 ) | ip_addr[3];

	//---- Build address structure to bind to socket.--------
	memset(&channel, 0, sizeof(channel));// zerochannel
	channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(ip_addr_int);
	channel.sin_port = htons( port );
    
    sa = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( sa < 0 )
    {
		printf("socket error %d", errno );
		return 0;
    }
    
    //setNonblocking(sa);
    
    b = connect( sa, (struct sockaddr *) &channel, sizeof(channel));
	if (b < 0)
	{
		printf("connect error %d", errno );
        close( sa );
		return 0;
	}
    
    return ( uint32_t )sa;
}

uint32_t socket_listen_port( uint16_t port )
{
    struct	    sockaddr_in channel;
    int		    b, l, on = 1;
    SOCKET      _l_socket;
    
	//---- Build address structure to bind to socket.--------
	memset(&channel, 0, sizeof(channel));// zerochannel
	channel.sin_family = AF_INET;
	channel.sin_addr.s_addr = htonl(INADDR_ANY);
	channel.sin_port = htons( port );
    
	// ---- create SOCKET--------------------------------------
    _l_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_l_socket < 0)
	{
		printf("socket error %d", errno );
		return ( uint32_t )SOCKET_FAIL_LISTEN;
	}
    
	setsockopt(_l_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    setNonblocking(_l_socket);
    
	//---------------------------------------------------------
    
	//---- BIND socket ----------------------------------------
	b = bind(_l_socket, (struct sockaddr *) &channel, sizeof(channel));
	if (b < 0)
	{
		printf("bind error %d", errno );
		return ( uint32_t )SOCKET_FAIL_LISTEN;
	}
	//----------------------------------------------------------
    
	//---- LISTEN socket ----------------------------------------
	l = listen(_l_socket, QUEUE_SIZE);                 // specify queue size
	if (l < 0)
	{
		printf("listen error %d", errno );
        return ( uint32_t )SOCKET_FAIL_LISTEN;
	}
    
    return ( uint32_t )_l_socket;
}

int socket_read( uint32_t socket, uint8_t *buffer, uint32_t max_size )
{
    return (int)read( socket, (char*)buffer, max_size);
}

int socket_read_data( uint32_t socket, uint8_t *buffer, uint32_t max_size )
{
    uint32_t num_bytes_present = 0;

    ioctl( socket, FIONREAD ,&num_bytes_present);

    #ifdef SOCKET_FF_PROBLEM
    uint32_t i = ( uint32_t )num_bytes_present;
    #endif
    
    if( ( num_bytes_present > 0 ) && ( buffer != NULL ) )
    {
		#ifndef SOCKET_FF_PROBLEM
        if( num_bytes_present > max_size ) num_bytes_present = max_size;
		recv( socket, (char*)buffer, num_bytes_present, 0 );
		#else
		i = 0;

		while( num_bytes_present )
		{
			recv( socket, (char*)&buffer[i], 1, 0 );
	
			if( buffer[i] == 0x0FF ) 
			{
				recv( socket, (char*)&buffer[i], 1, 0 );
				num_bytes_present--;
			}
			
			i++;
			num_bytes_present--;

			if( i >= max_size ) break;
		}
		#endif
    }
    
	#ifndef SOCKET_FF_PROBLEM
    return ( int )num_bytes_present;
	#else
	return i;
	#endif
}

int socket_write_data( uint32_t socket, uint8_t *buffer, uint32_t size )
{
    size = (uint32_t)send( socket, (char*)buffer, size, 0 );
	//Sleep(100);
    //printf( "OUT %d\r\n", size );
    return (int)size;    
}

void socket_flush( uint32_t socket )
{
}

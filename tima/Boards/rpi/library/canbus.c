#include "canbus_driver.h"
#include "system.h"
#include "spawn_lib.h"
#include "tima_libc.h"
#include "string_lib.h"
#include <unistd.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

typedef struct spawn_canbus_data_t_
{
    int can_socket;

    const CAN_filter_t * filter;
    uint16_t filter_size;

} spawn_canbus_data_t;

////////////////////////////////////////////////////////////////////

static spawn_canbus_data_t data;

////////////////////////////////////////////////////////////////////

static void can_read_thread( void * p_data )
{
    int nbytes;
    struct can_frame frame;
    int count;
    spawn_canbus_data_t * data = ( spawn_canbus_data_t * )p_data;

    while( 1 )
    {
        nbytes = read(data->can_socket, &frame, sizeof(struct can_frame));

        if (nbytes < 0)
        {
           perror("Read");
           return;
        }

        for( count = 0; count < data->filter_size; count++ )
        {
            if( ( data->filter[count].id == frame.can_id ) && ( data->filter[count].cb != NULL ) )
            {
                CAN_msg_t msg;
                msg.id = frame.can_id;
                msg.len = frame.can_dlc;
                memcpy( msg.data, frame.data, frame.can_dlc );
                data->filter[count].cb( &msg );
            }
        }
    }
}

static int open_can_socket(const char * can_port)
{
    int s;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
       perror("Socket");
       return -1;
    }

    struct ifreq ifr;

    strcpy(ifr.ifr_name, can_port );
    ioctl(s, SIOCGIFINDEX, &ifr);

    struct sockaddr_can addr;

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
       perror("Bind");
       return -1;
    }

    return s;
}

void canbus_start( const char * can_port, uint32_t rate, const CAN_filter_t * filter, uint16_t filter_size )
{
    data.filter      = filter;
    data.filter_size = filter_size;
    data.can_socket  = open_can_socket( can_port );

    if( data.can_socket > 0 ) tthread_create_ex( can_read_thread, &data );
}

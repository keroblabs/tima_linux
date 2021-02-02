#include "system.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "pipe.h"

///////////////////////////////////////////////////////////////////////////

#define WIFI_HEADER0						0x55
#define WIFI_HEADER1						0xAA
#define WIFI_TAIL							0x45

///////////////////////////////////////////////////////////////////////////

enum
{
	WIFI_RECEIVE_IDLE,
	WIFI_RECEIVE_WAITING,
	WIFI_RECEIVE_RECEIVING,
	WIFI_RECEIVE_TAIL
};

///////////////////////////////////////////////////////////////////////////

// host -> module
#define WICOMM_SET_PWR_SAVE_MODE_MSG		102
#define WICOMM_PING_SEND_MSG				121
#define WICOMM_RESET_MSG					170
#define WICOMM_SET_ARP_TIME_MSG				173

#define WICOMM_SOCKET_CREATE_MSG			110
#define WICOMM_SOCKET_CLOSE_MSG				111
#define WICOMM_SOCKET_BIND_MSG				112
#define WICOMM_SOCKET_CONNECT_MSG			113
#define WICOMM_SOCKET_LISTEN_MSG			114
#define WICOMM_SOCKET_ACCEPT_MSG			115
#define WICOMM_SOCKET_SEND_MSG				116
#define WICOMM_SOCKET_RECV_MSG				117
#define WICOMM_SOCKET_SEND_TO_MSG			118
#define WICOMM_SOCKET_RECV_FROM_MSG			119

#define WICOMM_SOCKET_ALLOCATE_MSG			122

#define WICOMM_GET_VERSION_MSG				23

#define WICOMM_SET_IP_ADDRESS_MSG			41
#define WICOMM_SET_NETWORK_MASK_MSG			42
#define WICOMM_SET_GATEWAY_IP_ADDR_MSG		44

#define WICOMM_GET_NETWORK_STATUS			48
#define WICOMM_SET_MAC_ADDR_MSG				49
#define WICOMM_SET_CP_NETWORK_MODE_MSG		55
#define WICOMM_SET_REGIONAL_DOMAIN_MSG		56
#define WICOMM_SET_CP_SSID_MSG				57

#define WICOMM_SET_CHANNEL_LIST_MSG			58
#define WICOMM_SET_LIST_RETRY_CNT_MSG		59
#define WICOMM_SET_CP_SECURITY_OPEN_MSG		65
#define WICOMM_SET_CP_SECURITY_WEP40_MSG	66
#define WICOMM_SET_CP_SECURITY_WEP104_MSG	67
#define WICOMM_SET_CP_SECURITY_WPA_MSG		68
#define WICOMM_GET_CP_WPAKEY_MSG			71

#define WICOMM_SCAN_START_MSG				80
#define WICOMM_SCAN_GET_RESULTS_MSG			81

// module -> host
#define WICOMM_ACK_MSG						0
#define WICOMM_EVENT_MSG					1

#define WICOMM_SCAN_RESULT_MSG				22

#define WICOMM_NETWORK_STATUS_RESP_MSG		48
#define WICOMM_WAPKEY_RESPONSE_MSG			49

#define WICOMM_WIFI_CONNECT_MSG				90
#define WICOMM_WIFI_DISCONNECT_MSG			91

#define WICOMM_SOCKET_CREATE_RESP_MSG		23
#define WICOMM_SOCKET_BIND_RES_MSG			24
#define WICOMM_SOCKET_CONNECT_RESP_MSG		25
#define WICOMM_SOCKET_LISTEN_RESP_MSG		26
#define WICOMM_SOCKET_ACCEPT_RESP_MSG		27
#define WICOMM_SOCKET_SEND_RESP_MSG			28
#define WICOMM_SOCKET_RECV_RESP_MSG			29
#define WICOMM_SOCKET_SENT_TO_RESP_MSG		30
#define WICOMM_SOCKET_RECV_FROM_RESP_MSG	31

#define WICOMM_SOCKET_ALLOCATE_RESP_MSG		32

///////////////////////////////////////////////////////////////////////////

typedef struct _wifi_data_t_
{
	uint8_t header0;
	uint8_t header1;
	uint16_t msg_type;
	uint16_t msg_len;
	uint8_t data;

} wifi_data_t;

typedef struct _wifi_ssid_data_t_
{
	uint8_t BSSID[11-6+1];
	uint8_t SSID_len;
	uint8_t SSID[44-13+1];
	uint8_t AP_config;
	uint16_t beacon_period;
	uint16_t ATIM_window;
	uint8_t rates[57-50+1];
	uint8_t RSSI;
	uint8_t rate_len;
	uint8_t DTIM_period;
	uint8_t BSS_type;
	uint8_t channel_num;

} wifi_ssid_data_t;

///////////////////////////////////////////////////////////////////////////

static device_t * wifi_dev;
static uint16_t last_command;
static uint8_t wifi_recv_mode;
static uint8_t wifi_header[6];
static bool_t wifi_ack_flag;

static uint8_t * p_wifi_buffer;
static uint8_t * p_wifi_rx;
static uint32_t wifi_rx_cnt;

static pipe_data_t pipe_rx_wifi;
static pipe_data_t pipe_tx_wifi;

///////////////////////////////////////////////////////////////////////////

void wifi_click_init( void )
{
	uint32_t baud = 9600;

	wifi_dev = device_open( DEV_WIFI_CLICK );
	device_ioctrl( wifi_dev, DEVICE_SET_CONFIG_DATA, &baud );

	pipe_init( &pipe_rx_wifi, "PIPE_WIFI_RX", 8 );
	pipe_init( &pipe_tx_wifi, "PIPE_WIFI_TX", 8 );

	wifi_recv_mode = WIFI_RECEIVE_IDLE;
}

static void wifi_click_send_process( void )
{
	uint8_t * tx_buffer;
	uint32_t pack_len;
	wifi_data_t * wifi_data;
	uint16_t msg;
	uint8_t * buffer;
	uint16_t len;

	// wait for incoming data
	if( pipe_is_empty( &pipe_tx_wifi ) ) return;
	buffer = pipe_read( &pipe_tx_wifi, &len );

	// save last command to parse events
	last_command = msg;

	// clear ack flag to indicate transaction in progress
	wifi_ack_flag = FALSE;

	// set state machine to waiting mode
	wifi_recv_mode = WIFI_RECEIVE_WAITING;

	// prepare package
	pack_len = 7 + len;
	tx_buffer = ( uint8_t * )MMALLOC( pack_len );
	if( tx_buffer == NULL ) return;

	wifi_data = ( wifi_data_t * )tx_buffer;
	wifi_data->header0 = WIFI_HEADER0;
	wifi_data->header1 = WIFI_HEADER1;
	wifi_data->msg_type = msg;
	wifi_data->msg_len = ( uint16_t )len;

	memcpy( &wifi_data->data, buffer, len );
	tx_buffer[pack_len-1] = WIFI_TAIL;

	// send to the module
	device_write_buffer( wifi_dev, tx_buffer, pack_len );
	MFREE( tx_buffer );

	pipe_release_buffer( buffer );
}

static void wifi_click_receive_process( void )
{
	wifi_data_t * wifi_data;
	uint32_t rx_len;
	uint8_t wifi_tail;
	timer_data_t flush_ms;

	if( wifi_recv_mode == WIFI_RECEIVE_WAITING )
	{
		// receive the header first
		if( device_read_buffer( wifi_dev, wifi_header, sizeof( wifi_header ) ) >= sizeof( wifi_header ) )
		{
			// buffer header has been received
			wifi_data = ( wifi_data_t * )wifi_header;

			// check header
			if( ( wifi_data->header0 != WIFI_HEADER0 ) ||
				( wifi_data->header1 != WIFI_HEADER1 ) )
			{
				timer_Start( &flush_ms, 100 );

				// flush data
				while( ( device_read_buffer( wifi_dev, &rx_len, sizeof( rx_len ) ) ) ||
					   ( timer_Check( &flush_ms ) == 0 ) )
				{
					SYSTEM_EVENTS();
				}

				wifi_recv_mode = WIFI_RECEIVE_IDLE;
				return;
			}

			// allocate space for payload plus message type
			p_wifi_buffer = ( uint8_t * )MMALLOC( wifi_data->msg_len + sizeof( uint16_t ) );
			if( p_wifi_buffer == NULL ) return;

			// copy message type to the beginning of the buffer
			memcpy( p_wifi_buffer, wifi_data->msg_type, sizeof( uint16_t ) );

			// and point the payload space
			p_wifi_rx = &p_wifi_buffer[2];
			wifi_rx_cnt = wifi_data->msg_len;

			// start receiving data
			wifi_recv_mode = WIFI_RECEIVE_WAITING;
		}
	}

	if( wifi_recv_mode == WIFI_RECEIVE_RECEIVING )
	{
		wifi_data = ( wifi_data_t * )wifi_header;

		if( wifi_data->msg_type == 0 )
		{
			// empty message, send to pipe and finish
			pipe_send_buffer( &pipe_rx_wifi, &wifi_data->msg_type, sizeof( uint16_t ) );
			wifi_recv_mode = WIFI_RECEIVE_IDLE;
			wifi_ack_flag = TRUE;
		}
		else
		{
			// start receiving the payload
			rx_len = device_read_buffer( wifi_dev, p_wifi_rx, wifi_rx_cnt );
			p_wifi_rx += rx_len;
			wifi_rx_cnt -= rx_len;
			if( wifi_rx_cnt == 0 )
			{
				wifi_recv_mode = WIFI_RECEIVE_TAIL;
			}
		}
	}

	if( wifi_recv_mode == WIFI_RECEIVE_TAIL )
	{
		// after payload, receive tail
		if( device_read_buffer( wifi_dev, &wifi_tail, 1 ) )
		{
			// send payload with message type over the pipe
			pipe_write( &pipe_rx_wifi, p_wifi_buffer, wifi_data->msg_len + sizeof( uint16_t ) );
			wifi_recv_mode = WIFI_RECEIVE_IDLE;
		}
	}
}




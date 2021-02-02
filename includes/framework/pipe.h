#ifndef __PIPE_DATA_H__
#define __PIPE_DATA_H__

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

#define MAX_PIPE_SIZE           32
#define MAX_PIPE_NAME_SIZE      20

////////////////////////////////////////////////////////////////////////////////////////

#define PIPE_AUDIO_OUT1         "AUDIO_OUT1"
#define PIPE_AUDIO_OUT2         "AUDIO_OUT2"
#define PIPE_AUDIO_IN           "AUDIO_IN"

#define PIPE_CODEC_OUT          "CODEC_OUT"
#define PIPE_CODEC_IN           "CODEC_IN"
#define PIPE_CODED_ENC_OUT      "CODEC_ENC_OUT"

#define PIPE_DATALINK_IN        "DATALINK_IN"
#define PIPE_DATALINK_OUT       "DATALINK_OUT"

#define PIPE_PROTOCOL_IN        "PROTOCOL_IN"
#define PIPE_PROTOCOL_OUT       "PROTOCOL_OUT"

#define PIPE_KEYBOARD			"KEYBOARD_IN"

////////////////////////////////////////////////////////////////////////////////////////

typedef void ( *trig_pipe_t )( void );

typedef bool_t ( *pipe_data_check_t )( void * p_data, uint8_t * data, uint16_t size );

typedef struct _pipe_data_t
{
    char name[ MAX_PIPE_NAME_SIZE + 1 ];
    
    uint8_t pointer_in;
    uint8_t pointer_out;

    uint8_t max_size;
    
    uint8_t * pipe_list[ MAX_PIPE_SIZE ];
    uint16_t  pipe_size[ MAX_PIPE_SIZE ];

    void * mutex;
    void * cond;

    struct _pipe_data_t * p_next;
    
} pipe_data_t;

////////////////////////////////////////////////////////////////////////////////////////

void        pipe_global_init( void );

void        pipe_init( pipe_data_t * pipe_data, char * name, uint16_t size );

uint8_t   * pipe_alloc_buffer( uint16_t size );
void        pipe_release_buffer( uint8_t * buffer );
    
pipe_data_t* pipe_locate( char * name );

uint32_t    pipe_get_buffer_size( pipe_data_t * pipe );
uint32_t    pipe_read_buffer( pipe_data_t * pipe, uint8_t * buffer, uint32_t max_size );
uint8_t   * pipe_read( pipe_data_t * pipe, uint16_t * size );
uint8_t   * pipe_get( pipe_data_t * pipe, uint16_t * size );
void        pipe_write( pipe_data_t * pipe, uint8_t * buffer, uint16_t size );
void        pipe_send_buffer( pipe_data_t * pipe, uint8_t * buffer, uint16_t size );

bool_t      pipe_is_full( pipe_data_t * pipe );
bool_t      pipe_is_empty( pipe_data_t * pipe );
uint32_t    pipe_get_used( pipe_data_t * pipe );
uint8_t   * pipe_wait_for_data( pipe_data_t * pipe, uint16_t * size );
uint8_t   * pipe_wait_for_data_ex( pipe_data_t * pipe, uint16_t * size, void * p_data, pipe_data_check_t checker );

////////////////////////////////////////////////////////////////////////////////////////

#endif // __PIPE_DATA_H__


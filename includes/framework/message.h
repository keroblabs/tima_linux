#ifndef _MESSAGE_H_
#define _MESSAGE_H_

///////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////////////////////////////

enum
{
	Message_NoMessage = 0x0000,

	/* add here kernel messages */
    Message_Query = 0x1000,

	Message_User_Space = 0x2000,
	Message_Redraw_Screen,
	Message_Update_Screen,
	Message_KeyPressed,
	Message_KeyLongPres,
	Message_KeyReleased,    
    Message_Encoder,

	Message_GPIO_Update = 0x2100,
    
    Message_User_Defined = 0x3000,
    
	Message_Exit_Priority = 0xB000,
	Message_Exit,

	Message_User_Priority = 0xB100,

	Message_MAX = 0xFFFF
};

///////////////////////////////////////////////////////////////////////////////////////

#define MESSAGE_MAX 64

typedef struct
{
    uint8_t pointer_in;
    uint8_t pointer_out;
    void * mutex;
    void * condition;
    uint16_t message_buffer[ MESSAGE_MAX ];
    void * data_buffer[ MESSAGE_MAX ];
    
} message_data_t;

typedef struct message_query_t_
{
    void * p_message;
    uint16_t message_ret;
    uint32_t data;
    
} message_query_t;

typedef struct message_hook_t_
{
	message_data_t * message_data;
	uint32_t match_value;
	uint16_t match_message;

	struct message_hook_t_ * p_next;

} message_hook_t;

///////////////////////////////////////////////////////////////////////////////////////

void message_Init( message_data_t * msg );
uint16_t message_Get( message_data_t * msg );
uint16_t message_Read( message_data_t * msg );
uint16_t message_Wait( message_data_t * msg );
void message_Remove( message_data_t * msg );
void message_Post( message_data_t * msg, uint16_t in_data );

uint16_t message_WaitData( message_data_t * msg, void ** p_data );

void message_PostData( message_data_t * msg, uint16_t in_data, void * p_data );

void message_SendQuery( message_data_t * req, message_data_t * dest, uint16_t msg_query, uint16_t msg_resp );

void message_ReplyQuery( void * p_query, uint32_t response );

uint32_t message_GetQuery( void * p_query );

void message_PostMatch( message_hook_t * msg, uint32_t value );

///////////////////////////////////////////////////////////////////////////////////////

#endif // _MESSAGE_H_


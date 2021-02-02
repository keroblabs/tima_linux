#ifndef button_ctrl_h_
#define button_ctrl_h_

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "gpio_driver.h"
#include "message.h"

////////////////////////////////////////////////////////////////////////////////////////

enum
{
    Button_Message_Down,
    Button_Message_LongDown,
    Button_Message_VeryLongDown,
    Button_Message_Up,
    Button_Message_LongUp,
    Button_Message_VeryLongUp,
    
    Button_Message_Released
};

////////////////////////////////////////////////////////////////////////////////////////

extern const char * str_debug_button_message[];

////////////////////////////////////////////////////////////////////////////////////////

#define BUTTON_MESSAGE_DONW(a)              (a+Button_Message_Down)
#define BUTTON_MESSAGE_LONG_DONW(a)         (a+Button_Message_LongDown)
#define BUTTON_MESSAGE_VERY_LONG_DONW(a)    (a+Button_Message_VeryLongDown)
#define BUTTON_MESSAGE_UP(a)                (a+Button_Message_Up)
#define BUTTON_MESSAGE_LONG_UP(a)           (a+Button_Message_LongUp)
#define BUTTON_MESSAGE_VERY_LONG_UP(a)      (a+Button_Message_VeryLongUp)

#define DECLARE_BUTTON_MESSAGE(a)           a, a##_Skip = a+Button_Message_Released

////////////////////////////////////////////////////////////////////////////////////////

void button_ctrl_init( void );

bool_t button_ctrl_get_state( void * p_btn );

uint16_t button_ctrl_get_message( void * p_btn );

void * button_ctrl_create( void * read, message_data_t * msg, uint16_t msg_base, void * p_data );
void * button_ctrl_event_create( void * read, void * event, uint16_t msg_base, void * p_data );

void button_ctrl_set_press_state( void * p_btn, bool_t press_state );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* button_ctrl_h_ */

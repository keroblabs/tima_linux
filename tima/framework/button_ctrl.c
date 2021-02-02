#include "system.h"
#include "message.h"
#include "timer.h"
#include "button_ctrl.h"

////////////////////////////////////////////////////////////////////////////////////////

const char * str_debug_button_message[] =
{
    "Button_Message_Down",
    "Button_Message_LongDown",
    "Button_Message_VeryLongDown",
    "Button_Message_Up",
    "Button_Message_LongUp",
    "Button_Message_VeryLongUp",

    "Button_Message_Released"
};

////////////////////////////////////////////////////////////////////////////////////////

#define BUTTON_DEBOUCE_MS           50
#define BUTTON_LONG_TIME_MS         1200
#define BUTTON_VERY_LONG_TIME_MS    2500
#define BUTTON_MS_ROLL_OVER         ((NEG_U32)-5000)

////////////////////////////////////////////////////////////////////////////////////////

typedef void ( *button_handler_t )( void * p_ctrl );
typedef bool_t ( *button_read_t )( void * p_ctrl );

typedef struct _button_ctrl_t_
{
    void * mutex;
    void * thread;
    void * p_data;
    // void * p_gpio;
    
    bool_t curr_value;
    uint16_t message_base;
    uint16_t button_message;
    
    bool_t prev_state;
    bool_t new_state;
    bool_t state0;
    bool_t state1;
    bool_t state2;
    uint16_t curr_message;
    uint32_t press_ms;
    
    bool_t state_pressed;
    bool_t state_released;

    message_data_t * message;
    button_handler_t event;
    button_read_t read;
    
    struct _button_ctrl_t_ * p_next;
    
} button_ctrl_t;

////////////////////////////////////////////////////////////////////////////////////////

static button_ctrl_t * button_list;
static void * button_gpio_mutex;

#if !defined _USE_MULTITHREAD
static timer_data_t debouce_timer;
#endif

////////////////////////////////////////////////////////////////////////////////////////

static void button_control_send_event( button_ctrl_t * p_button, uint16_t msg )
{
    tthread_mutex_lock( p_button->mutex );
    p_button->button_message = p_button->message_base + msg;
    tthread_mutex_unlock( p_button->mutex );

    if( p_button->message != NULL )
    {
        message_Post( p_button->message, p_button->message_base + msg );
    }
    
    if( p_button->event != NULL )
    {
        p_button->event( p_button );
    }
}

static bool_t button_control_read_from( button_ctrl_t * p_button )
{
    return p_button->read ? p_button->read( p_button->p_data ) : FALSE;
}

static void button_control_process_data( button_ctrl_t * p_button )
{
    uint32_t curr_time;

    p_button->state0 = p_button->state1;
    p_button->state1 = p_button->state2;
    p_button->state2 = button_control_read_from( p_button );
    p_button->new_state = ( p_button->state0 == p_button->state2 ) ? p_button->state0 : p_button->prev_state;
    
    if( p_button->new_state != p_button->prev_state )
    {
        tthread_mutex_lock( p_button->mutex );
        p_button->curr_value = p_button->new_state;
        tthread_mutex_unlock( p_button->mutex );
        
        if( ( p_button->prev_state == p_button->state_pressed ) && ( p_button->new_state == p_button->state_released ) )
        {
            // release
            if( p_button->curr_message == Button_Message_Down )
            {
                // short release
                button_control_send_event( p_button, Button_Message_Up );
            }
            else if( p_button->curr_message == Button_Message_LongDown )
            {
                // long release
                button_control_send_event( p_button, Button_Message_LongUp );
            }
            else if( p_button->curr_message == Button_Message_VeryLongDown )
            {
                // very long release
                button_control_send_event( p_button, Button_Message_VeryLongUp );
            }
            
            p_button->curr_message = Button_Message_Released;
        }
        else if( ( p_button->prev_state == p_button->state_released ) && ( p_button->new_state == p_button->state_pressed ) )
        {
            // button pressed
            p_button->press_ms = timer_get_MS();
            p_button->curr_message = Button_Message_Down;
            button_control_send_event( p_button, p_button->curr_message );
        }
        
        p_button->prev_state = p_button->new_state;
    }
    
    if( p_button->curr_value == p_button->state_pressed )
    {
        curr_time = timer_get_MS() - p_button->press_ms;
        
        if( ( p_button->curr_message == Button_Message_Down ) && ( curr_time >= BUTTON_LONG_TIME_MS ) )
        {
            // long press
            p_button->curr_message = Button_Message_LongDown;
            button_control_send_event( p_button, p_button->curr_message );
            
            tthread_mutex_lock( p_button->mutex );
            p_button->button_message = p_button->curr_message;
            tthread_mutex_unlock( p_button->mutex );
        }
        else if( ( p_button->curr_message == Button_Message_LongDown ) && ( curr_time >= BUTTON_VERY_LONG_TIME_MS ) )
        {
            // very long press
            p_button->curr_message = Button_Message_VeryLongDown;
            button_control_send_event( p_button, p_button->curr_message );
            
            tthread_mutex_lock( p_button->mutex );
            p_button->button_message = p_button->curr_message;
            tthread_mutex_unlock( p_button->mutex );
        }
    }
}

static button_ctrl_t * button_create_data( void * read, void * event, message_data_t * msg, uint16_t msg_base, void * p_data )
{
    button_ctrl_t * p_button;

    p_button = ( button_ctrl_t * )MMALLOC( sizeof( button_ctrl_t ) );
    if( p_button == NULL ) return NULL;
    memset( p_button, 0x00, sizeof( button_ctrl_t ) );

    p_button->event = ( button_handler_t )event;
    p_button->message = msg;
    p_button->p_data = p_data;

    p_button->message_base = msg_base;
    p_button->read = ( button_read_t )read;
    p_button->mutex = tthread_mutex_init();

    p_button->prev_state = p_button->new_state = button_control_read_from( p_button );
    p_button->state0 = p_button->state1 = p_button->state2 = p_button->new_state;
    p_button->curr_message = Button_Message_Released;
    p_button->press_ms = 0;
    p_button->state_pressed = TRUE;
    p_button->state_released = FALSE;

    tthread_mutex_lock( button_gpio_mutex );
    p_button->p_next = button_list;
    button_list = p_button;
    tthread_mutex_unlock( button_gpio_mutex );

    return p_button;
}

#if defined _USE_MULTITHREAD
static void button_control_thread( void )
{
    button_ctrl_t * button_search;
    
    while( 1 )
    {
        tthread_sleep_ms( BUTTON_DEBOUCE_MS );
        
        tthread_mutex_lock( button_gpio_mutex );
        
        button_search = button_list;
        
        while( button_search != NULL )
        {
            button_control_process_data( button_search );
            button_search = button_search->p_next;
        }

        tthread_mutex_unlock( button_gpio_mutex );
    }
}
#else
static void button_control_thread( void )
{
    button_ctrl_t * button_search = button_list;

    while( button_search != NULL )
    {
        button_control_process_data( button_search );
        button_search = button_search->p_next;
    }
}
DECLARE_PROCESS_SECTION(button_control_thread);
#endif

bool_t button_ctrl_get_state( void * p_btn )
{
    button_ctrl_t * p_button = ( button_ctrl_t * )p_btn;
    return p_button->curr_value;
}

uint16_t button_ctrl_get_message( void * p_btn )
{
    button_ctrl_t * p_button = ( button_ctrl_t * )p_btn;
    return p_button->button_message;
}

void * button_ctrl_event_create( void * read, void * event, uint16_t msg_base, void * p_data )
{
	return button_create_data( read, event, NULL, msg_base, p_data );
}

void * button_ctrl_create( void * read, message_data_t * msg, uint16_t msg_base, void * p_data )
{
	return button_create_data( read, NULL, msg, msg_base, p_data );
}

void button_ctrl_set_press_state( void * p_btn, bool_t press_state )
{
	button_ctrl_t * p_button = ( button_ctrl_t * )p_btn;

	if( press_state == TRUE )
	{
		p_button->state_pressed = TRUE;
		p_button->state_released = FALSE;
	}
	else
	{
		p_button->state_pressed = FALSE;
		p_button->state_released = TRUE;
	}
}

void button_ctrl_init( void )
{
    button_list = NULL;
    button_gpio_mutex = tthread_mutex_init();

#if defined _USE_MULTITHREAD
    tthread_create( button_control_thread );
#else
    timer_Start( &debouce_timer, BUTTON_DEBOUCE_MS );
#endif
}

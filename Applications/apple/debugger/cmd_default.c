#include "cmd_default.h"

///////////////////////////////////////////////////////////////

static void cmd_exit_handler( console_instance_t * p_instance, char * input );
static void cmd_list_handler( console_instance_t * p_instance, char * input );
static void cmd_echo_handler( console_instance_t * p_instance, char * input );

///////////////////////////////////////////////////////////////

static command_data_t command_exit =
{
    "exit",
    NULL,
    cmd_exit_handler
};

static command_data_t command_help =
{
    "help",
    NULL,
    cmd_list_handler
};

static command_data_t command_echo =
{
    "echo",
    NULL,
    cmd_echo_handler
};

///////////////////////////////////////////////////////////////

static void cmd_exit_handler( console_instance_t * p_instance, char * input )
{
    if( p_instance->socket_accepted != 0 ) p_instance->to_terminate = TRUE;
    else p_instance->command_mode = FALSE;
}

static void cmd_list_handler( console_instance_t * p_instance, char * input )
{
    console_list_command( p_instance );
}

static void cmd_echo_handler( console_instance_t * p_instance, char * input )
{
    int socket = p_instance->socket_accepted;

    if( input != NULL )
    {
        if( !strcmp( input, "on" ) )
        {
            p_instance->echo_mode = TRUE;
        }
        else if( !strcmp( input, "off" ) )
        {
            p_instance->echo_mode = FALSE;
        }
    }

    console_command_printk( socket, "Echo %s\r\n", p_instance->echo_mode ? "ON" : "OFF" );
}

void commands_add_default( void )
{
    console_add_command( &command_echo );
    console_add_command( &command_help );
    console_add_command( &command_exit );
}

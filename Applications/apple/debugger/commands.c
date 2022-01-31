#include "system.h"
//#include "device.h"
#include "socket_library.h"

#ifdef USE_MULTITHREAD
#include "t_threads.h"
#endif

#include "tima_libc.h"
#include "commands.h"
//#include "ymodem.h"

////////////////////////////////////////////////////////////////////

#define CONSOLE_STACK_SIZE              1024
#define SOCKET_LISTEN_TIME_INTERVAL     500

////////////////////////////////////////////////////////////////////

#ifdef USE_MULTITHREAD
static uint8_t console_stack[ CONSOLE_STACK_SIZE ];
static thread_data_t co_console;
#endif

static console_instance_t * instance_list;
static command_data_t * command_list;

////////////////////////////////////////////////////////////////////

int console_tokenizer( char * input, char ** output, char * delim, int max )
{
	char * p_input;
	char * out;
	char * last;
	char str_val[10];
	int size;
	int i;

	p_input = input;
	i = 0;

	while( tima_tokenizer( p_input, ( const char ** )&out, &size, delim, &last ) )
	{
		strncpy( str_val, out, size );
		str_val[size] = 0;
		strcpy( *output, str_val );
		i++;
		p_input = NULL;
		output++;

		if( i >= max ) break;
	}

	return i;
}

void console_set_command_mode ( console_instance_t * p_instance )
{
	p_instance->command_mode = TRUE;
	console_command_printk( p_instance->socket_accepted, "\r\n%s> ", p_instance->cmd_curr_dir );
}

void console_execute_command( console_instance_t * p_instance )
{
	static char cmd_caption[128];
	char * cmd_param;
	command_data_t * p_command;

	if( p_instance->command_buffer[0] != 0 )
	{
		cmd_param = NULL;

		strcpy( cmd_caption, p_instance->command_buffer );
		cmd_param = strchr( cmd_caption, ' ' );
		if( cmd_param != NULL ) 
		{
			*cmd_param = 0;
			cmd_param++;
		}

		//CONSOLE_PRINTK( "\r\n" );
        // #define GET_FONT_SECTION(i)                         ( font_data_t * )system_List_Get_Item(FONT_SECTION_ID,i)
        
        p_command = command_list;
        while( p_command != NULL )
		{
			if( !strcmp( p_command->name, cmd_caption ) )
			{
				p_command->handler( p_instance, cmd_param );
			}
            
            p_command = p_command->p_next;
		}

		p_instance->command_pointer = 0;
		p_instance->command_buffer[0] = 0;
	}

	if( p_instance->command_mode == TRUE )
	{
		console_command_printk( p_instance->socket_accepted, "\r\n%s> ", p_instance->cmd_curr_dir );
	}
}

int console_echo_handler( console_instance_t * p_instance, char * input )
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

	return 0;
}

void console_list_command( console_instance_t * p_instance )
{
	//char * cmd_param;
	command_data_t * p_command;

    p_command = command_list;
    while( p_command != NULL )
	{
		console_command_printk( p_instance->socket_accepted, "%s\r\n", p_command->name );
        p_command = p_command->p_next;
	}
}

void console_local_process( console_instance_t * p_instance )
{
	uint8_t rx_byte;

#ifdef USE_MULTITHREAD
    while( 1 )
    {
        thread_wait( device_is_rx_pending(dev_tty) > 0 );
#else
    if( socket_read_data(p_instance->socket_accepted, NULL, 0 ) > 0 )
    {
#endif
        // receive data
        
		while( socket_read_data( p_instance->socket_accepted, (uint8_t *)&rx_byte, 1 ) > 0 )
		{
			if( p_instance->command_mode == FALSE )
			{
				if( rx_byte == 0x1B )
				{
					//p_instance->command_mode = TRUE;
					//console_command_printk( p_instance->dev_console_tty, "\r\n\r\n%s> ", p_instance->cmd_curr_dir );
					console_set_command_mode( p_instance );
				}
                
				p_instance->carriage_returned = FALSE;
            }
            else
            {
                if( ( rx_byte == 13 ) || ( rx_byte == 10 ) )
                {
					if( p_instance->carriage_returned == FALSE )
					{
						console_command_printk( p_instance->socket_accepted, "\r\n" );
						p_instance->command_buffer[p_instance->command_pointer] = 0;
						console_execute_command( p_instance );
						p_instance->carriage_returned = TRUE;
					}
					else
					{
						p_instance->carriage_returned = FALSE;
					}
                }
                else
                {
					p_instance->carriage_returned = FALSE;

                    if( ( rx_byte == 127 ) || ( rx_byte == 8 ) )
                    {
                        if( p_instance->command_pointer )
                        {
                            p_instance->command_buffer[p_instance->command_pointer] = 0;
                            p_instance->command_pointer--;
                            rx_byte = 8;
                        }
                    }
                    else
                    {
                        p_instance->command_buffer[p_instance->command_pointer++] = rx_byte;
                    }
                    
					if( ( p_instance->command_mode == TRUE ) && ( p_instance->echo_mode == TRUE ) )
					{
						console_command_printk( p_instance->socket_accepted, "%c", rx_byte );
					}
                }
            }
        }
    }
}

int console_command_printk( int socket, const char *fmt, ... )
{
	va_list args;	
	int printed_len;
    
	/* Emit the output into the temporary buffer */ 
	va_start(args, fmt);	
	printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args); 
	va_end(args);	

    return socket_write_data( socket, ( uint8_t * )vsf_printk_buf, printed_len );
}

int console_printk( const char *fmt, ... )
{
	va_list args;	
	int printed_len;
	console_instance_t * p_instance;
    
	/* Emit the output into the temporary buffer */ 
	va_start(args, fmt);	
	printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args); 
	va_end(args);	

	p_instance = instance_list;

	while( p_instance != NULL )
	{
		socket_write_data( p_instance->socket_accepted, ( uint8_t * )vsf_printk_buf, printed_len );
		p_instance = p_instance->p_next;
	}

	return printed_len;
}

int console_flaged_printk( const char *fmt, ... )
{
	va_list args;	
	int printed_len;
	console_instance_t * p_instance;

	/* Emit the output into the temporary buffer */ 
	va_start(args, fmt);	
	printed_len = vsnprintk(vsf_printk_buf, VSF_PRINTK_BUF_SIZE, fmt, args); 
	va_end(args);	

	p_instance = instance_list;

	while( p_instance != NULL )
	{
		if( p_instance->command_mode == FALSE )
		{
			socket_write_data( p_instance->socket_accepted, ( uint8_t * )vsf_printk_buf, printed_len );
		}
		p_instance = p_instance->p_next;
	}

	return printed_len;
}

void console_process( void )
{
	console_instance_t * p_instance = instance_list;

	while( p_instance != NULL )
	{
		if( p_instance->telnet_port != 0 )
		{
			console_accept_telnet( p_instance );
		}
		else
		{
			console_local_process( p_instance );
		}

		p_instance = p_instance->p_next;
	}
    
    // clear up
    p_instance = instance_list;
    while( p_instance != NULL )
    {
        if( p_instance->to_terminate == TRUE )
        {
            console_terminate_instance( p_instance );
            break;
        }

        p_instance = p_instance->p_next;
    }
}

console_instance_t * console_create_instance( void )
{
	console_instance_t * p_instance;

	p_instance = ( console_instance_t * ) MMALLOC( sizeof( console_instance_t ) );
	if( p_instance == NULL ) return NULL;
	memset( p_instance, 0x00, sizeof( console_instance_t ) );

	p_instance->command_mode = FALSE;
	p_instance->carriage_returned = FALSE;

	strcpy( p_instance->cmd_curr_dir, "/" );

	p_instance->command_pointer = 0;
    p_instance->command_buffer[0] = 0;

	return p_instance;
}

console_instance_t * console_accept_telnet( console_instance_t * p_instance )
{
	int socket_accept;
	console_instance_t * new_instance;
    
    if( timer_Check( &p_instance->listen_timeout ) == FALSE ) return NULL;
    timer_Reload( &p_instance->listen_timeout );

	if( ( socket_accept = socket_accept_port( p_instance->socket_listen ) ) > 0 )
	{
		new_instance = console_create_instance();
		if( new_instance == NULL )
		{
			MFREE( new_instance );
			return NULL;
		}

		new_instance->socket_accepted = socket_accept;

		// by default telnet is echo OFF
		new_instance->echo_mode = FALSE;

		// by default telnet starts in command mode
		console_set_command_mode( new_instance );

		console_add_instance( new_instance );
		return new_instance;
	}

	return NULL;
}
    
void console_terminate_instance( console_instance_t * p_instance )
{
    console_instance_t * search_instance = instance_list;
    console_instance_t * prev_instance = NULL;
    
    while( search_instance != NULL )
    {
        if( search_instance == p_instance )
        {
            if( prev_instance != NULL ) prev_instance->p_next = p_instance->p_next;
            else instance_list = p_instance->p_next;
            
            socket_close_port( p_instance->socket_accepted );
            MFREE( p_instance );
            break;
        }
        
        prev_instance = search_instance;
        search_instance = search_instance->p_next;
    }
}

console_instance_t * console_listen_telnet( uint16_t telnet_port )
{
	int socket_listen;
	console_instance_t * p_instance;

	if( ( socket_listen = socket_listen_port( telnet_port ) ) > 0 )
	{
		p_instance = console_create_instance();
		if( p_instance == NULL )
		{
			MFREE( p_instance );
			return NULL;
		}

		p_instance->socket_listen = socket_listen;
		p_instance->telnet_port = telnet_port;
        
        timer_Start( &p_instance->listen_timeout, CONSOLE_STACK_SIZE );

		console_add_instance( p_instance );
		return p_instance;
	}

	return NULL;
}

void console_add_instance( console_instance_t * p_instance )
{
    p_instance->p_next = instance_list;
    instance_list = p_instance;
}

void console_add_command( command_data_t * p_command )
{
    p_command->p_next = command_list;
    command_list = p_command;
}

void console_init( void )
{
    instance_list = NULL;
    command_list = NULL;
}

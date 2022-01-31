#ifndef __commands_h__
#define __commands_h__

///////////////////////////////////////////////////////////////

#include "types.h"
#include "system.h"
#include "timer.h"

///////////////////////////////////////////////////////////////

#define MAX_LONG_FILENAME_LENGHT 256

typedef struct _console_instance_t_
{
	char command_buffer[128];
	uint16_t command_pointer;

	bool_t echo_mode;
	bool_t command_mode;
	bool_t carriage_returned;
    bool_t to_terminate;
    
	uint16_t telnet_port;

    int socket_listen;
    int socket_accepted;
    timer_data_t listen_timeout;
    
	char cmd_curr_dir[MAX_LONG_FILENAME_LENGHT]; 

	struct _console_instance_t_ * p_next;

} console_instance_t;

typedef struct _command_data_t_
{
	char * name;
	void (* init )( void );
	void (* handler )( console_instance_t * p_instance, char * input );
    
    struct _command_data_t_ * p_next;

} command_data_t;

///////////////////////////////////////////////////////////////

//#define CONSOLE_PRINTK(...) file_fprintk( FILE_CONSOLE_HDL, __VA_ARGS__ )
//#define CONSOLE_FLUSH()     file_flush( FILE_CONSOLE_HDL )
#if defined DEBUG_PRINTK
#undef DEBUG_PRINTK
#endif

#define DEBUG_PRINTK(...)       console_flaged_printk( __VA_ARGS__ )
#define CONSOLE_PRINTK(...)		console_printk( __VA_ARGS__ )
#define CONSOLE_FLUSH()			

///////////////////////////////////////////////////////////////

#define COMMAND_SECTION_ID                          SYSTEM_LIST_SECTION+2
#define GET_COMMAND_SECTION(i)                      ( command_data_t * )system_List_Get_Item(COMMAND_SECTION_ID,i)
#define DECLARE_COMMAND_SECTION(a)                  SYSTEM_SECTION_LIST(a, COMMAND_SECTION_ID)

///////////////////////////////////////////////////////////////

void console_init( void );
void console_process( void );

int console_printk( const char *fmt, ... );
int console_flaged_printk( const char *fmt, ... );
int console_command_printk( int socket, const char *fmt, ... );

int console_tokenizer( char * input, char ** output, char * delim, int max );

void console_list_command( console_instance_t * p_instance );

console_instance_t * console_create_instance( void );
console_instance_t * console_accept_telnet( console_instance_t * p_instance );
console_instance_t * console_listen_telnet( uint16_t telnet_port );
console_instance_t * console_connect_uart( const char * dev_name );

void console_add_instance( console_instance_t * p_instance );
void console_add_command( command_data_t * p_command );

void console_terminate_instance( console_instance_t * p_instance );

void console_set_command_mode ( console_instance_t * p_instance );

///////////////////////////////////////////////////////////////

#endif // __commands_h__

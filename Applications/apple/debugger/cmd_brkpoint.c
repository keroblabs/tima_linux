#include "cmd_default.h"
#include "cpu.h"
#include "types.h"
#include "ram_ctrl.h"

///////////////////////////////////////////////////////////////

static void cmd_brk_handler( console_instance_t * p_instance, char * input );
static void cmd_step_handler( console_instance_t * p_instance, char * input );
static void cmd_next_handler( console_instance_t * p_instance, char * input );
static void cmd_cont_handler( console_instance_t * p_instance, char * input );
static void cmd_pause_handler( console_instance_t * p_instance, char * input );
static void cmd_dump_handler( console_instance_t * p_instance, char * input );
static void cmd_zpg16_handler( console_instance_t * p_instance, char * input );

uint8_t disasm_instruction( dump_hdl_t dump_hdl, uint16_t pc );

///////////////////////////////////////////////////////////////

static command_data_t command_brk =    { "brk",    NULL, cmd_brk_handler  };
static command_data_t command_step =   { "step",   NULL, cmd_step_handler };
static command_data_t command_next =   { "next",   NULL, cmd_next_handler };
static command_data_t command_cont =   { "cont",   NULL, cmd_cont_handler };
static command_data_t command_pause =  { "pause",  NULL, cmd_pause_handler };
static command_data_t command_dump =   { "dump",   NULL, cmd_dump_handler };
static command_data_t command_zpg16 =  { "zpg16",  NULL, cmd_zpg16_handler };

///////////////////////////////////////////////////////////////

static step_hook_t local_step;
static console_instance_t * curr_instance;

///////////////////////////////////////////////////////////////

static void cmd_print_line( char * line )
{
    console_printk( "%s\r\n", line );
}

static void cmd_brk_cpu_step( uint16_t pc_addr, void * p_data )
{
    if( curr_instance == NULL ) return;
    
    disasm_instruction( cmd_print_line, pc_addr );
    cpu_dump_regs( cmd_print_line );
    console_set_command_mode( curr_instance );
}

static void cmd_step_handler( console_instance_t * p_instance, char * input )
{
    p_instance->command_mode = FALSE;
    cpu_break_step( TRUE );
}

static void cmd_next_handler( console_instance_t * p_instance, char * input )
{
    p_instance->command_mode = FALSE;
    cpu_break_step( TRUE );
}

static void cmd_cont_handler( console_instance_t * p_instance, char * input )
{
    cpu_break_step( FALSE );
}

static void cmd_pause_handler( console_instance_t * p_instance, char * input )
{
    curr_instance = p_instance;

    p_instance->command_mode = FALSE;
    cpu_break_step( TRUE );
    cpu_break_step( TRUE );
}

static void cmd_zpg16_handler( console_instance_t * p_instance, char * input )
{
    if( input == NULL ) return;
    uint32_t zpg_addr;
    uint32_t out_addr;
    
    if( !strcmp( input, "help" ) )
    {
        console_command_printk( p_instance->socket_accepted, "zpg16 ind addr\n" );
        console_command_printk( p_instance->socket_accepted, "zpg16 addr\n" );
    }
    else if( ( strlen( input ) > 1 ) && !strncmp( input, "$", 1 ) )
    {
        sscanf( &input[1], "%x", &zpg_addr );
        out_addr = global_memory_read( ( zpg_addr & 0xFF ) + 1 );
        out_addr = ( out_addr << 8 ) | global_memory_read( ( zpg_addr & 0xFF ) );
        console_command_printk( p_instance->socket_accepted, "zpg16 = $%04x\n", out_addr );
    }
    else if( ( strlen( input ) > 5 ) && !strncmp( input, "ind $", 5 ) )
    {
        sscanf( &input[5], "%x", &zpg_addr );
        out_addr = global_memory_read( ( zpg_addr & 0xFF ) + 1 );
        out_addr = ( out_addr << 8 ) | global_memory_read( ( zpg_addr & 0xFF ) );
        console_command_printk( p_instance->socket_accepted, "zpg16 (ind) = $%02x\n", global_memory_read( out_addr ) );
    }
}

static void cmd_dump_handler( console_instance_t * p_instance, char * input )
{
    if( input == NULL ) return;
    
    if( !strcmp( input, "help" ) )
    {
        console_command_printk( p_instance->socket_accepted, "dump add len\n" );
    }
    else if( ( strlen( input ) > 6 ) && ( input[0] == '$' ) )
    {
        uint32_t dump_addr = 0;
        uint32_t dump_cnt = 0;
        sscanf( &input[1], "%x %d", &dump_addr, &dump_cnt );
        while( ( dump_addr < 0xFFFF ) && ( dump_cnt > 0 ) )
        {
            dump_addr += disasm_instruction( cmd_print_line, dump_addr );
            dump_cnt--;
        }
    }
}

static void cmd_brk_handler( console_instance_t * p_instance, char * input )
{
    if( input == NULL ) return;
    
    if( !strcmp( input, "help" ) )
    {
        console_command_printk( p_instance->socket_accepted, "brk add <addr>\n" );
        console_command_printk( p_instance->socket_accepted, "brk del <index>\n" );
        console_command_printk( p_instance->socket_accepted, "brk list\n" );
    }
    else if( !strcmp( input, "list" ) )
    {
        for( int i = 0; i < CPU_MAX_BRKPOINT; i++ )
        {
            uint16_t brk_addr = cpu_get_breakpoint( i );
            if( brk_addr != 0 ) console_command_printk( p_instance->socket_accepted, "%d: $%04X\n", i, brk_addr );
        }
    }
    else if( ( strlen( input ) > 4 ) && !strncmp( input, "del ", 4 ) )
    {
        uint8_t index = input[4];
        if( index < CPU_MAX_BRKPOINT ) cpu_set_breakpoint( index, 0x0000 );
        curr_instance = p_instance;
    }
    else if( ( strlen( input ) > 5 ) && !strncmp( input, "add $", 5 ) )
    {
        uint32_t brk_addr = 0;
        sscanf( &input[5], "%x", &brk_addr );
        
        for( int i = 0; i < CPU_MAX_BRKPOINT; i++ )
        {
            if( cpu_get_breakpoint( i ) == 0x0000 )
            {
                cpu_set_breakpoint( i, ( uint16_t )( brk_addr & 0xFFFF ) );
                console_command_printk( p_instance->socket_accepted, "New breakpoint %d: $%04X\n", i, brk_addr );
                curr_instance = p_instance;
                break;
            }
        }
    }
}

void commands_add_breakpoint( void )
{
    cpu_hook_step( &local_step, cmd_brk_cpu_step, NULL );
    console_add_command( &command_brk );
    console_add_command( &command_step );
    console_add_command( &command_cont );
    console_add_command( &command_next );
    console_add_command( &command_pause );
    console_add_command( &command_dump );
    console_add_command( &command_zpg16 );
}

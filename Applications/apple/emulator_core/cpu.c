#include "cpu.h"
#include "timer.h"
#include "debug.h"
#include "ram_ctrl.h"
#include "cpu.h"
#include "led_frame.h"
#include "video.h"
#include "paddles.h"

//////////////////////////////////////////////////////////////////////////////////////

#define  AF_SIGN                        0x80
#define  AF_OVERFLOW                    0x40
#define  AF_RESERVED                    0x20
#define  AF_BREAK                       0x10
#define  AF_DECIMAL                     0x08
#define  AF_INTERRUPT                   0x04
#define  AF_ZERO                        0x02
#define  AF_CARRY                       0x01

#define DEFAULT_CPU_CYCLE_PERIOD		100
#define CPU_LOOP_COUNT					40
#define CPU_VIDEO_COUNT					8
#define CPU_VIDEO_COUNT_TURBO           9

#define IRQ_STATE_NONE                  0
#define IRQ_STATE_PENDING               1
#define IRQ_STATE_SERVING               2

#ifdef TIMA_LINUX
#define CPY_CYCLE_MS                    10
#elif defined __MACH__
#define CPY_CYCLE_MS                    10
#else
#define CPY_CYCLE_MS                    0
#endif

//////////////////////////////////////////////////////////////////////////////////////

static board_data_t * board;
static timer_data_t cpu_ms;
static uint32_t cpu_cycle_counter;
static bool_t cpu_halt;
static bool_t cpu_break;
static bool_t turbo_mode;
static uint32_t loop_cnt;
static uint16_t prev_pc;
static uint32_t total_of_cycles = 0;
static uint32_t benchmark_cycles = 0;
static uint32_t cpu_max_cycles;
static uint64_t start_halt_us;
static uint32_t cpu_usage;
static bool_t enable_trace = FALSE;
static uint32_t cpu_cycle_ms;
static uint32_t cpu_clock;

static step_hook_t * step_hook_list;
static co_proc_hdl_t p_co_proc;
static interrupt_hdl_t p_irq;

#ifdef ENABLE_VIDEO
static uint32_t video_dma_cnt;
#endif

static uint16_t addr;
static bool_t flagc;
static bool_t flagn;
static bool_t flagv;
static bool_t flagz;
static uint16_t temp;
static uint16_t val;
static uint32_t cycles;
static uint16_t brkpoint_list[CPU_MAX_BRKPOINT];
static regsrec_t regs;

//////////////////////////////////////////////////////////////////////////////////////

static INLINE uint8_t cpu_fetch_8(uint16_t addr)
{
    return ram_ctrl_read_8( addr );
}

static INLINE uint8_t cpu_read_8(uint16_t addr)
{
    return ram_ctrl_read_8( addr );
}

static INLINE uint16_t cpu_read_16(uint16_t addr)
{
    return ram_ctrl_read_16( addr );
}

static INLINE void cpu_write_8(uint16_t addr, uint8_t data)
{
    ram_ctrl_write_8( addr, data );
}

//////////////////////////////////////////////////////////////////////////////////////

#include "instr_defs.h"
#include "instr_code.h"
#include "timer.h"

//////////////////////////////////////////////////////////////////////////////////////

void cpu_set_breakpoint( uint8_t index, uint16_t brk_addr )
{
    if( index < CPU_MAX_BRKPOINT ) brkpoint_list[index] = brk_addr;
}
uint16_t cpu_get_breakpoint( uint8_t index )
{
    if( index < CPU_MAX_BRKPOINT ) return brkpoint_list[index];
    return 0;
}

static bool_t is_brk_point( uint16_t pc_addr )
{
    for( int i = 0; i < CPU_MAX_BRKPOINT; i++ )
    {
        if( brkpoint_list[i] == pc_addr ) return TRUE;
    }
    
    return FALSE;
}

static INLINE void cpu_loop( void )
{
	uint8_t status = board->p_loop( total_of_cycles );

	switch( status )
	{
		case STATUS_IRQ:
			regs.irq = 0;
			break;

		case STATUS_NMI:
			regs.nmi = 0;
			break;
	}
}

static void cpu_default_co_proc( uint16_t co_proc_addr )
{
    switch( ram_ctrl_read_8( co_proc_addr ) )
    {
        case CO_PROC_SET_BRKPOINT:
            cpu_set_breakpoint( cpu_read_8( co_proc_addr + 2 ), cpu_read_16( co_proc_addr + 3 ) );
            break;

        case CO_PROC_ENABLE_TRACE:
            enable_trace = TRUE;
            break;
    }
}

static void cpu_exec_step( uint16_t pc_addr )
{
    step_hook_t * p_hook = step_hook_list;
    while( p_hook != NULL )
    {
        p_hook->hdl( pc_addr, p_hook->p_data );
        p_hook = p_hook->p_next;
    }
}

static bool_t cpu_default_irq( void )
{
    return FALSE;
}

uint32_t cpu_execute( void ) 
{
	uint8_t opcode;
    uint16_t disasm_pc;

	if( ( cpu_cycle_counter >= cpu_max_cycles ) && ( cpu_break == FALSE ) )
	{
		if( timer_Check( &cpu_ms ) == TRUE )
		{
            timer_Start( &cpu_ms, cpu_cycle_ms );
			cpu_cycle_counter = 0;
			cpu_halt = FALSE;

            start_halt_us = timer_get_microsecs();
		}
		else if( cpu_halt == FALSE ) // && ( turbo_mode == FALSE ) )
		{
			cpu_halt = TRUE;
            cpu_usage = ( ( uint32_t )( timer_get_microsecs() - start_halt_us ) * 100 ) / ( cpu_cycle_ms * 1000 );
		}
	}

    if( ( cpu_break == FALSE ) && ( is_brk_point(regs.pc) == TRUE ) )
    {
        cpu_break = TRUE;
        cpu_halt = TRUE;
        
        cpu_exec_step( regs.pc );
    }

    if( cpu_halt == FALSE )
	{
		cycles = 0;
		AF_TO_EF;					//get flags from regs.pc

        opcode = cpu_fetch_8( regs.pc );
        
        addr = 0;
        disasm_pc = prev_pc = regs.pc;
		regs.pc++;

		INSTR_DECODE( opcode )
        
        if( enable_trace == TRUE )
        {
            disasm_instruction( board->p_print, disasm_pc );
            board->p_print( "\n" );
        }
        
		total_of_cycles += cycles;
		benchmark_cycles += cycles;
        
		if( turbo_mode == FALSE )
		{
		    cpu_cycle_counter += cycles;
		}
	}

	if( ( cpu_break == TRUE ) && ( cpu_halt == FALSE ) )
	{
        cpu_exec_step( regs.pc );
		cpu_halt = TRUE;
	}

    #ifdef ENABLE_VIDEO
	if( ( --video_dma_cnt == 0 ) || ( cpu_halt == TRUE ) )
	{
		video_dma_cnt = turbo_mode ? CPU_VIDEO_COUNT_TURBO : CPU_VIDEO_COUNT;
		video_dma();
	}
    #endif

	if( cpu_halt == FALSE )
	{
        if( --loop_cnt == 0 )
        {
            loop_cnt = CPU_LOOP_COUNT;
            cpu_loop();
        }
	}

	paddle_loop( total_of_cycles );

    if( cpu_halt == FALSE )
	{
		if( !regs.stp ) 
		{        
            // If STP, then no IRQ or NMI allowed
			if( !regs.nmi )
            {
                if (regs.wai)
                {
                    regs.pc++;
                    regs.wai = 0;
                }
                                 
			    NMI;
                regs.nmi = 1;
            }

	        if( ( ( regs.irq == IRQ_STATE_NONE ) && p_irq() ) ||
	            ( ( regs.irq == IRQ_STATE_PENDING ) && !( regs.ps & AF_INTERRUPT ) ) )
            {
                if (regs.wai)
                {
                    regs.pc++;
                    regs.wai = 0;
                }

                regs.irq = IRQ_STATE_PENDING;
                //printf( "IRQ 0x%04x (%d)\n", regs.pc, !(regs.ps & AF_INTERRUPT) );
                
                if( !(regs.ps & AF_INTERRUPT) )
                {
                    IRQ;
                    regs.irq = IRQ_STATE_SERVING;
                    //printf( "Go to 0x%04x (%d)\n", regs.pc, regs.irq );
                }
            }
		}
	
		EF_TO_AF;								// put flags back in regs.ps
	}

	return cycles;
}

void cpu_dump_regs( dump_hdl_t dump_hdl )
{
	// A=00 X=00 Y=00 SP=0000 PS=00 PC=0000
	sprintf( debug_temp_string, "  A=%02X X=%02X Y=%02X SP=%04X PS=%02X PC=%04X", regs.a, regs.x, regs.y, regs.sp, regs.ps, regs.pc );
	dump_hdl( debug_temp_string );
}

void cpu_benchmark_reset( void )
{
	benchmark_cycles = 0;
}

void cpu_turbo_mode( bool_t state )
{
	turbo_mode = state;
	led_show( LED_ID_TURBO, state );
}

bool_t cpu_get_turbo_mode( void )
{
	return turbo_mode;
}

bool_t cpu_get_break( void )
{
	return cpu_break;
}

bool_t cpu_get_halt( void )
{
	return cpu_halt;
}

uint16_t cpu_get_pc( void )
{
    return prev_pc;
}

void cpu_break_step( bool_t state )
{
	if( ( cpu_break == TRUE ) && ( state == TRUE ) )
	{
		cpu_halt = FALSE;
	}
	else if( state == FALSE )
	{
		cpu_halt = FALSE;
	}

	cpu_break = state;
}

uint32_t cpu_benchmark_read( void )
{
	return benchmark_cycles;
}

uint32_t cpu_usage_read( void )
{
	return cpu_usage;
}

void cpu_boost( void )
{
    cpu_cycle_counter = 0;
}

void cpu_hook_step( step_hook_t * hook_data, cpu_halt_step_t new_hook, void * p_data )
{
    hook_data->hdl = new_hook;
    hook_data->p_data = p_data;
    
    hook_data->p_next = step_hook_list;
    step_hook_list = hook_data;
}

interrupt_hdl_t cpu_hook_irq( interrupt_hdl_t new_hook )
{
    interrupt_hdl_t ret = p_irq;
    p_irq = new_hook;
    return ret;
}

co_proc_hdl_t cpu_hook_co_proc( co_proc_hdl_t new_hook )
{
    co_proc_hdl_t ret = p_co_proc;
    p_co_proc = new_hook;
    return ret;
}

void cpu_get_regs( regsrec_t * p_regs )
{
    memcpy( p_regs, &regs, sizeof( regs ) );
}

void cpu_set_acu( uint8_t acu )
{
    regs.a = acu;
}

void cpu_set_regx( uint8_t regx )
{
    regs.x = regx;
}

void cpu_set_regy( uint8_t regy )
{
    regs.y = regy;
}

uint32_t cpu_get_run_period( void )
{
    return cpu_cycle_ms;
}

void cpu_reset( void )
{
	regs.a  = 0;
	regs.x  = 0;
	regs.y  = 0;
	regs.ps = 0x30;                       // set unused bit 5 to 1 and BRK=1
	regs.pc = cpu_read_16(0xFFFC);
	regs.sp = 0x01FF;

	regs.irq   = IRQ_STATE_NONE;
	regs.nmi   = 1;
	regs.wai   = 0;
	regs.stp   = 0;
    
    memset( brkpoint_list, 0x00, sizeof( brkpoint_list ) );

	prev_pc = regs.pc;

	total_of_cycles = 0;
	loop_cnt = CPU_LOOP_COUNT;

#ifdef ENABLE_VIDEO
	video_dma_cnt = CPU_VIDEO_COUNT;
#endif

	if( cpu_cycle_ms == 0 )
	{
		cpu_cycle_ms = DEFAULT_CPU_CYCLE_PERIOD;
	}

	timer_Start( &cpu_ms, cpu_cycle_ms );
	cpu_halt = FALSE;
	cpu_break = FALSE;
	turbo_mode = FALSE;
	cpu_max_cycles = ( ( cpu_clock + 1000 ) / ( 900 / cpu_cycle_ms ) );
	cpu_cycle_counter = 0;

	regs.ps = (regs.ps | AF_INTERRUPT) & ~AF_DECIMAL;
	regs.sp = 0x0100 | ((regs.sp - 3) & 0xFF);
}

void cpu_init( void * board_data )
{
    board = (board_data_t * )board_data;
    p_irq = cpu_default_irq;
    p_co_proc = cpu_default_co_proc;
    
    step_hook_list = NULL;
    cpu_cycle_ms   = CPY_CYCLE_MS;
    cpu_clock = 1000000;
}

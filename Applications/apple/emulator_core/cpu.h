#ifndef _CPU_H__
#define _CPU_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "datatypes.h"
#include "board.h"

//////////////////////////////////////////////////////////////////////////////////////

#define STATUS_NONE		0
#define STATUS_IRQ		1
#define STATUS_NMI		2
#define STATUS_BRK		3

//////////////////////////////////////////////////////////////////////////////////////

#define CO_PROC_READ_DISC_SECTOR        0x01
#define CO_PROC_ENABLE_TRACE            0x02
#define CO_PROC_SET_BRKPOINT            0x03
#define CPU_MAX_BRKPOINT                8

//////////////////////////////////////////////////////////////////////////////////////

typedef struct step_hook_t_
{
    cpu_halt_step_t hdl;
    void * p_data;
    struct step_hook_t_ * p_next;
    
} step_hook_t;

typedef struct _regsrec
{
    uint8_t a;   // accumulator
    uint8_t x;   // index X
    uint8_t y;   // index Y
    uint8_t ps;  // processor status
    uint16_t pc;  // program counter
    uint16_t sp;  // stack pointer

    uint8_t      irq;
    bool_t       nmi;
    bool_t       wai;
    bool_t       stp;

} regsrec_t;

//////////////////////////////////////////////////////////////////////////////////////

uint32_t cpu_execute( void );
bool_t cpu_get_paddle( uint8_t paddle );
void cpu_paddle_trigger( uint16_t pdl0, uint16_t pdl1, uint16_t pdl2, uint16_t pdl3 );
void cpu_init( void * board );
void cpu_reset( void );
void cpu_boost( void );

void cpu_break_step( bool_t state );
void cpu_turbo_mode( bool_t state );

bool_t cpu_get_turbo_mode( void );
bool_t cpu_get_break( void );
bool_t cpu_get_halt( void );

void cpu_benchmark_reset( void );
uint32_t cpu_benchmark_read( void );
uint32_t cpu_get_performance( void );
uint32_t cpu_get_run_period( void );

uint16_t cpu_get_pc( void );

void cpu_dump_regs( dump_hdl_t dump_hdl );

uint32_t cpu_usage_read( void );

interrupt_hdl_t cpu_hook_irq( interrupt_hdl_t new_hook );
co_proc_hdl_t cpu_hook_co_proc( co_proc_hdl_t new_hook );

void cpu_hook_step( step_hook_t * hook_data, cpu_halt_step_t new_hook, void * p_data );

void cpu_set_breakpoint( uint8_t index, uint16_t brk_addr );
uint16_t cpu_get_breakpoint( uint8_t index );
void cpu_get_regs( regsrec_t * regs );

void cpu_set_acu( uint8_t acu );
void cpu_set_regx( uint8_t regx );
void cpu_set_regy( uint8_t regy );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _CPU_H__

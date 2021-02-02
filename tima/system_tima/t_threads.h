#ifndef _THREADS_H_
#define _THREADS_H_

////////////////////////////////////////////////////////

#include "types.h"
// #include "system.h"

////////////////////////////////////////////////////////

#ifdef THREAD_TERMINATE
#undef THREAD_TERMINATE
#endif

#ifdef USE_MULTITHREAD

#define THREAD_RUNNING				0x0001
#define THREAD_TERMINATE			0x0002
#define THREAD_SYSCALL				0x0004
#define THREAD_CURRENT				0x0008
#define THREAD_D_STACK				0x0010
#define THREAD_D_DATA				0x0020

#define thread_wait(c)              while(!(c)) { thread_yield(); }

#define thread_init_session(s)      s = FALSE
#define thread_start_session(s)     if( s == TRUE ) { thread_wait( s == FALSE ); } else s = TRUE
#define thread_end_session(s)       s = FALSE

////////////////////////////////////////////////////////

typedef void ( *thread_addr_t )( void * args );
typedef void ( *thread_cb_t )( void );

enum
{
	SPEED_DEFAULT,
	
	SPEED_VERY_LOW,
	SPEED_LOW,
	SPEED_MEDIUM,
	SPEED_HIGH,
	SPEED_VERY_HIGH

};

enum
{
    CPU_NONE,
    
    CPU_DISABLE_IRQ,
    CPU_ENABLE_IRQ,
    CPU_FORCE_ENABLE_IRQ,
    CPU_GET_IRQ_STATE,
    
    CPU_SET_SPEED,
    CPU_GET_SPEED,
    CPU_SLEEP
};

////////////////////////////////////////////////////////

typedef struct _thread_data_t
{
    void * context;
    
    void * addr;
    void * callback;
    void * args;
    
    uint8_t * stack;
    uint32_t stack_size;  
    
    void * p_data;
    
    uint32_t flags;
    
    struct _thread_data_t * t_next;

} thread_data_t;

typedef struct _cpu_api_t
{
    void ( *set_speed )( uint8_t speed );
    uint8_t ( *get_speed )( void );

    void ( *disable_irq )( void );
    void ( *enable_irq )( void );
    void ( *force_enable_irq )( void );
    bool_t ( *irq_status )( void );

    void ( *sleep )( void );

    void ( *start_contexts )( void * thread );
    void ( *get_os_context )( void * thread );
    void ( *create_context )( void * thread, void * addr );

    void ( *swap_context )( void * old_thread, void * new_thread );
    void ( *kill_context )( void * thread );
    void ( *syscall )( void * thread, uint32_t args );
    
} cpu_api_t;

//////////////////////////////////////////////////////////////////////////////

extern cpu_api_t * CPU_driver;

//////////////////////////////////////////////////////////////////////////////

bool_t thread_task_create( thread_data_t * thread, void * addr, void * param, void * stack, uint32_t stack_size );

void   thread_kill( thread_data_t * thread );
void   thread_set_data_object( void ** p_obj );
void   thread_yield( void );
void   thread_start( void );

void   thread_syscall( uint32_t index );
void   thread_set_callback( thread_data_t * p_thread, void * cb );

////////////////////////////////////////////////////////

#else

////////////////////////////////////////////////////////

typedef void ( *tthread_handler_t )( void );
typedef void ( *tthread_handler_ex_t )( void * args );

////////////////////////////////////////////////////////

void * tthread_mutex_init( void );

void tthread_mutex_lock( void * p_mutex );
void tthread_mutex_unlock( void * p_mutex );

void * tthread_condition_create( void );
void tthread_condition_wait( void * p_cond );
void tthread_condition_signal( void * p_cond );

void * tthread_create_ex( tthread_handler_ex_t handler, void * args );

void tthread_sleep_ms( int timeInMs );

void tthread_cancel( void * p_thread );

#endif

#endif // _THREADS_H_

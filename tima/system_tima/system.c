#include "system.h"

////////////////////////////////////////////////////////////////////////////////

#define SYS_HEAP_SIZE		32768

////////////////////////////////////////////////////////////////////////////////

extern uint8_t system_heap[];
extern const uint32_t system_heap_size;

////////////////////////////////////////////////////////////////////////////////

//static char tima_version[30];
static uint16_t build_date;
static uint16_t build_time;

//static uint8_t system_heap[SYS_HEAP_SIZE];
static heap_t sys_heap;

static bool_t sys_is_run;

////////////////////////////////////////////////////////////////////////////////

void app_main_init( void );

////////////////////////////////////////////////////////////////////////////////

#if !defined USE_SECTIONS
#define SOFT_SECTION_MAX_SIZE		512

volatile void *     _list_list_[SOFT_SECTION_MAX_SIZE];
volatile uint32_t   _list_ptr_ = 0;

#endif

////////////////////////////////////////////////////////////////////////////////

static void * _system_get_internal_section( void * start, void * end, uint8_t type, uint32_t index )
{
    void ** pp_data;
    void ** pp_end;
    data_section_t * p_data;
    uint32_t counter;
    
    if( start == end ) return NULL;
    
    counter = 0;
    pp_data = ( void ** )start;
    pp_end = ( void ** )end;
    
    while( pp_data != pp_end )
    {
        p_data = ( data_section_t * )*pp_data;
        
        if( p_data->type == type )
        {
            if( counter == index )
            {
                return p_data->handler;
            }
            
            counter++;
        }
        
        pp_data++;
    }
    
    return NULL;
}

static void _system_run_internal_section( void * start, void * end, uint8_t type )
{
    void ** pp_data;
    void ** pp_end;
	data_section_t * p_data;
    
    ptr_module_t p_call;
    
	if( start == end ) return;
    pp_data = ( void ** )start;
    pp_end = ( void ** )end;
    
	while( pp_data != pp_end )
	{
        p_data = ( data_section_t * )*pp_data;
 
        if( p_data->type == type )
        {
            p_call = ( ptr_module_t )p_data->handler;
            ( *p_call )();
        }
        
		pp_data++;
	}
}

void _system_call_section( uint8_t type )
{
    _system_run_internal_section( _list_section, type );
}

void * _system_get_item_section( uint8_t type, uint32_t index )
{
    return _system_get_internal_section( _list_section, type, index );
}

void _system_powerup_call( void )
{
}

void _system_prepare_version( void )
{
}

////////////////////////////////////////////////////////////////////////////////

void * sys_malloc( uint32_t size )
{
	return heap_malloc( &sys_heap, size );
}

void sys_free( void * ptr )
{
	heap_free( &sys_heap, ptr );
}

uint32_t sys_heap_total( void )
{
	return heap_size( &sys_heap );
}

uint32_t sys_heap_used( void )
{
	return heap_in_use( &sys_heap );
}

void sys_heap_list( ptr_print_t dev )
{
	heap_list_debug( dev, &sys_heap );
}

void sys_heap_check( void )
{
	heap_check( &sys_heap );
}


void * zmmalloc( size_t size, const char * file, int line )
{
    void * ret = sys_malloc( size );
    memset( ret, 0x00, size );
    return ret;
}

void * mmalloc( size_t size, const char * file, int line )
{
    return sys_malloc( size );
}

void mfree( void * p, const char * file, int line  )
{
    sys_free( p );
}

////////////////////////////////////////////////////////////////////////////////

char * system_Get_Version( void )
{
    return NULL;
}

uint16_t system_Get_Build_Time( void )
{
    return build_time;
}

uint16_t system_Get_Build_Date( void )
{
    return build_date;
}

void * system_List_Get_Item( uint8_t type, uint32_t index )
{
    return _system_get_internal_section( _list_section, type+SYSTEM_LIST_SECTION, index );
}

msd_driver_t * system_Get_Storage_Driver( uint32_t index )
{
    return ( msd_driver_t * )_system_get_internal_section( _list_section, SYSTEM_STORAGE_DEVICE, index );
}

device_data_t * system_Get_Device_Driver( uint32_t index )
{
    return ( device_data_t * )_system_get_internal_section( _list_section, SYSTEM_DEVICE_DATA, index );
}

void * system_Get_Custom_Driver( uint32_t index )
{
    return _system_get_internal_section( _list_section, SYSTEM_CUSTOM_DEVICE, index );
}

void * system_Get_Item( uint32_t * start, uint32_t * end, uint32_t index )
{
	ptr_module_t *p_start;
	ptr_module_t *p_end;
    
	if( start == end ) return NULL;
    
	p_start = ( ptr_module_t * )start;
	p_end =   ( ptr_module_t * )end;
    
	p_start += index;
    
	if( p_start >= p_end ) return NULL;
    
	return *p_start;
}

void system_Events( void )
{
    _system_call_section( SYSTEM_RUN_PROCESS );
}

void System_PowerDown( void )
{
    _system_call_section( SYSTEM_RUN_POWERDOWN_CRITICAL );
    _system_call_section( SYSTEM_RUN_POWERDOWN_DEVICE );
    _system_call_section( SYSTEM_RUN_POWERDOWN_MODULE );
    _system_call_section( SYSTEM_RUN_POWERDOWN_APPLICATION );
    
    sys_is_run = FALSE;
}

void main( void )
{
	sys_is_run = TRUE;

    /* only init variables and values */
    _system_call_section( SYSTEM_INIT_POWERUP );

    /* Prepare build version */
    _system_prepare_version();

    /* Init heap */
    heap_init( &sys_heap, system_heap, system_heap_size );

	/* Critical initialization */
    _system_call_section( SYSTEM_INIT_CRITICAL );
    _system_call_section( SYSTEM_INIT_DEBUG );

	/* init libraries */
	MAL_Init_All();

    /* init devices and modules */
    _system_call_section( SYSTEM_INIT_DEVICE );
    _system_call_section( SYSTEM_INIT_MODULE );

    /* execute initialization related to application */
    _system_call_section( SYSTEM_INIT_APPLICATION );
    
    /* execute applications in the pool */
    _system_call_section( SYSTEM_START_MAIN_APPLICATION );
    
    /* start al threads */
	#ifdef USE_MULTITHREAD
    thread_start();
	#endif

    // if application exits, execute default application
    while( sys_is_run )
    {
		SYSTEM_EVENTS();
    }
}

////////////////////////////////////////////////////////////////////////



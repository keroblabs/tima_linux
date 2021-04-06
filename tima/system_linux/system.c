#include "system.h"
#include "sections.h"
#include "serial_driver.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#if !defined USE_SECTIONS
#define SOFT_SECTION_MAX_SIZE        512

volatile void *     _list_list_[SOFT_SECTION_MAX_SIZE];
volatile uint32_t   _list_ptr_ = 0;

#endif

////////////////////////////////////////////////////////////////////////////////

static void * _system_get_internal_section( void * start, void * end, uint32_t type, uint32_t index )
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

static void _system_run_internal_section( void * start, void * end, uint32_t type )
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

void _system_call_section( uint32_t type )
{
    _system_run_internal_section( _list_section, type );
}

void * _system_get_item_section( uint8_t type, uint32_t index )
{
    return _system_get_internal_section( _list_section, type, index );
}

void system_init( void )
{
    #if !defined _USE_MACOS_SDL
    int pid_file = open("./pid.txt", O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);
    if(rc)
    {
        if(EWOULDBLOCK == errno)
        {
            // another instance is running
            printf( "Another instance is running\n" );
            exit(1);
        }
    }
    else
    {
        // this is the first instance
    }
    #endif

    _system_call_section( SYSTEM_INIT_MODULE );
}

////////////////////////////////////////////////////////////////////////

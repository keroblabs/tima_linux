#ifndef pipe_class_definition_h
#define pipe_class_definition_h

////////////////////////////////////////////////////////////////////////

#include "class_framework.h"

////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 32

////////////////////////////////////////////////////////////////////////

#define MAX_PIPE_SIZE           32

////////////////////////////////////////////////////////////////////////

typedef CLASS(pipe_class_t)
{
    CLASS_DATA_VOID;
    
    uint8_t pointer_in;
    uint8_t pointer_out;
    
    uint8_t max_size;
    
    void * pipe_list[ MAX_PIPE_SIZE ];
    uint32_t  pipe_size[ MAX_PIPE_SIZE ];
    bool_t is_dynamic[ MAX_PIPE_SIZE ];
    
    void * mutex;
    void * cond;
    
    CREATOR void ( *creator )( uint32_t max_size );
    DELETE  void ( *delete_pipe )( void );
    
    METHOD void * ( *get )( uint32_t * size );
    METHOD void * ( *read )( uint32_t * size );
    METHOD void * ( *wait_for_data )( uint32_t * size );

    METHOD void   ( *write )( void * buffer, uint32_t size );
    METHOD void   ( *send )( void * buffer, uint32_t size );

    METHOD bool_t ( *is_full )( void );
    METHOD bool_t ( *is_empty )( void );
    
} pipe_class_t;

////////////////////////////////////////////////////////////////////////

#endif /* pipe_class_definition_h */

#ifndef list_class_definition_h
#define list_class_definition_h

////////////////////////////////////////////////////////////////////////

#include "class_framework.h"

////////////////////////////////////////////////////////////////////////

#ifdef MAX_INSTANCES
#undef MAX_INSTANCES
#endif
#define MAX_INSTANCES 16

////////////////////////////////////////////////////////////////////////

// MUST be the first element of a data structure
typedef struct _list_node_t
{
    struct _list_node_t *next;
    
} list_node_t;

typedef void (*delete_cb_t)(list_node_t *node);

////////////////////////////////////////////////////////////////////////

typedef CLASS(list_class_t)
{
    CLASS_DATA_VOID;
    
    uint16_t count;
    void * head;
    void * tail;
    delete_cb_t    delete_cb;
    
    CREATOR void ( *creator_list )( delete_cb_t delete_cb );
    DELETE  void ( *delete_list )( void );
    
    METHOD void ( *clear )( void );
    METHOD void ( *insert_head )( list_node_t * node );
    METHOD void ( *insert_tail )( list_node_t * node );
    METHOD void ( *remove_tail )( void );
    
    METHOD bool_t ( *unlink_node )( list_node_t * node );
    METHOD bool_t ( *remove_node )( list_node_t * node );
    METHOD bool_t ( *is_empty )( void );
    
    METHOD void * ( *get_head )( void );
    METHOD void * ( *get_tail )( void );
    METHOD void * ( *get_next )( list_node_t * node );
    METHOD void * ( *get_prev )( list_node_t * curr );
    
    METHOD uint16_t ( *size )( void );
    
} list_class_t;

////////////////////////////////////////////////////////////////////////

#endif /* list_class_definition_h */

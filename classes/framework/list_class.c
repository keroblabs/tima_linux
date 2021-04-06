#include "list_class_private.h"

////////////////////////////////////////////////////////////////////

#define LIST_INIT_NODE(node, nextnode)            node->next = nextnode;
#define LIST_DELETE_NODE(node, delete_cb)         if ((*delete_cb) != NULL) { (*delete_cb)(node); } { {MFREE(node); } }

////////////////////////////////////////////////////////////////////

static list_node_t *find_prev_node( list_class_t *list, list_node_t *node )
{
    list_node_t *curr = list->head;
    
    while (curr != NULL)
    {
        if (curr->next == node)
        {
            return curr;
        }
        curr = curr->next;
    }
    return curr;
}

////////////////////////////////////////////////////////////////////

CREATOR static void creator_list( list_class_t * p_data, delete_cb_t delete_cb )
{
    p_data->count     = 0;
    p_data->head      = NULL;
    p_data->tail      = NULL;
    p_data->delete_cb = delete_cb;
}

DELETE static void delete_list( list_class_t * p_data )
{
    while (p_data->head != NULL)
    {
        list_node_t *node = ( list_node_t * )p_data->head;
        p_data->head = ( ( list_node_t * )p_data->head )->next;
        LIST_DELETE_NODE(node, p_data->delete_cb);
    }
}

METHOD static void clear( list_class_t * p_data )
{
    while (p_data->head != NULL)
    {
        list_node_t *node = ( list_node_t * )p_data->head;
        p_data->head = ( ( list_node_t * )p_data->head )->next;
        LIST_DELETE_NODE(node, p_data->delete_cb);
    }
    
    p_data->count     = 0;
    p_data->head      = NULL;
    p_data->tail      = NULL;
}

METHOD static void insert_head( list_class_t * p_data, list_node_t * node )
{
    LIST_INIT_NODE(node, p_data->head);
    
    if (p_data->head == NULL)
    {
        p_data->tail = node;
    }
    p_data->head = node;
    p_data->count++;
}

METHOD static void insert_tail( list_class_t * p_data, list_node_t * node )
{
    LIST_INIT_NODE(node, NULL);
    
    if (p_data->head == NULL)
    {
        p_data->head = node;
    }
    else
    {
        ( ( list_node_t * )p_data->tail )->next = node;
    }
    
    p_data->tail = node;
    p_data->count++;
}

METHOD static void remove_tail( list_class_t * p_data )
{
    list_node_t *curr = ( list_node_t * )p_data->head;
    list_node_t *prev = NULL;
    
    if (p_data->head != NULL)
    {
        while (curr->next != NULL)
        {
            prev = curr;
            curr = curr->next;
        }
        
        /* delete the node */
        LIST_DELETE_NODE(curr, p_data->delete_cb);
        
        /* and update the previous node to be tail */
        if (prev)
        {
            prev->next = NULL;
        }
        
        /* update the list tail */
        p_data->tail = prev;
        p_data->count--;
    }
}

METHOD static bool_t unlink_node( list_class_t * p_data, list_node_t * node )
{
    if (p_data->head == node)
    {
        p_data->head = node->next;
        if (p_data->head == NULL)
        {
            p_data->tail = NULL;
        }
    }
    else
    {
        list_node_t *prevnode = find_prev_node(p_data, node);
        if (prevnode == NULL)
        {
            return FALSE;
        }
        prevnode->next = node->next;
        if (prevnode->next == NULL)
        {
            p_data->tail = prevnode;
        }
    }
    p_data->count--;
    return TRUE;
}

METHOD static bool_t remove_node( list_class_t * p_data, list_node_t * node )
{
    bool_t result = p_data->unlink_node(node);
    LIST_DELETE_NODE(node, p_data->delete_cb);
    return result;
}

METHOD static bool_t is_empty( list_class_t * p_data )
{
    return (p_data->head == NULL);
}

METHOD static void * get_head( list_class_t * p_data )
{
    return p_data->head;
}

METHOD static void * get_tail( list_class_t * p_data )
{
    return p_data->tail;
}

METHOD static void * get_next( list_class_t * p_data, list_node_t * node )
{
    if( node == NULL ) return p_data->head;
    else return node->next;
}

METHOD static void * get_prev( list_class_t * p_data, list_node_t * curr )
{
    list_node_t *node = p_data->get_head();
    while (node != NULL)
    {
        if( curr == node->next ) return node;
        node = p_data->get_next(node);
    }
    
    return NULL;
}

METHOD static uint16_t size( list_class_t * p_data )
{
    return p_data->count;
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( list_class_t );

////////////////////////////////////////////////////////////////////

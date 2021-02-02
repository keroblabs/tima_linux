#include "lists.h"

//////////////////////////////////////////////////////////////////////////////////////////

#define LIST_INIT_NODE(node, nextnode)            node->next = nextnode;
#define LIST_DELETE_NODE(node, delete_cb)         if ((*delete_cb) != NULL) { (*delete_cb)(node); } { {MFREE(node); } }

//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

static list_node_t *find_prev_node(list_t *list, list_node_t *node)
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

void list_init(list_t *list, delete_cb_t delete_cb)
{
    list->count     = 0;
    list->head      = NULL;
    list->tail      = NULL;
    list->delete_cb = delete_cb;
}

void list_clear(list_t *list)
{
    while (list->head != NULL)
    {
        list_node_t *node = list->head;
        list->head = list->head->next;
        LIST_DELETE_NODE(node, list->delete_cb);
    }
    
    /* clear only removes nodes, maintain the callback function */
    list_init(list, list->delete_cb);
}

void list_insert_head(list_t *list, list_node_t *node)
{
    LIST_INIT_NODE(node, list->head);
    
    if (list->head == NULL)
    {
        list->tail = node;
    }
    list->head = node;
    list->count++;
}

void list_insert_tail(list_t *list, list_node_t *node)
{
    LIST_INIT_NODE(node, NULL);
    
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        list->tail->next = node;
    }
    
    list->tail = node;
    list->count++;
}

void list_insert_after(list_t *list, list_node_t *existingnode, list_node_t *node)
{
    LIST_INIT_NODE(node, existingnode->next);
    
    existingnode->next = node;
    
    if (list->tail == existingnode)
    {
        list->tail = node;
    }
    list->count++;
}

bool_t list_unlink(list_t *list, list_node_t *node)
{
    if (list->head == node)
    {
        list->head = node->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
    }
    else
    {
        list_node_t *prevnode = find_prev_node(list, node);
        if (prevnode == NULL)
        {
            return FALSE;
        }
        prevnode->next = node->next;
        if (prevnode->next == NULL)
        {
            list->tail = prevnode;
        }
    }
    list->count--;
    return TRUE;
}

bool_t list_remove(list_t *list, list_node_t *node)
{
    bool_t result = list_unlink(list, node);
    LIST_DELETE_NODE(node, list->delete_cb);
    return result;
}

void list_remove_tail(list_t *list)
{
    list_node_t *curr = list->head;
    list_node_t *prev = NULL;
    
    if (list->head != NULL)
    {
        while (curr->next != NULL)
        {
            prev = curr;
            curr = curr->next;
        }
        
        /* delete the node */
        LIST_DELETE_NODE(curr, list->delete_cb);
        
        /* and update the previous node to be tail */
        if (prev)
        {
            prev->next = NULL;
        }
        
        /* update the list tail */
        list->tail = prev;
        list->count--;
    }
}

list_node_t *list_find(list_t *list, size_t offset, uint16_t size, const void *value)
{
    list_node_t *node = list_get_head(list);
    while (node != NULL)
    {
        if (memcmp(value, ((uint8_t *) node) + offset, size) == 0)
        {
            return node;
        }
        node = list_get_next(list, node);
    }
    
    return NULL;
}

bool_t list_is_empty(const list_t * const list)
{
    return (list->head == NULL);
}

void * list_get_prev(const list_t * const list, list_node_t * curr)
{
    list_node_t *node = list_get_head(list);
    while (node != NULL)
    {
        if( curr == node->next ) return node;
        node = list_get_next(list, node);
    }
    
    return NULL;
}

void * list_get_head(const list_t * const list)
{
    return list->head;
}

void * list_get_tail(const list_t * const list)
{
    return list->tail;
}

void * list_get_next(const list_t * const list, list_node_t * node)
{
    if( node == NULL ) return list->head;
    else return node->next;
}

uint16_t list_size(const list_t * const list)
{
    return list->count;
}

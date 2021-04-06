#include "list_class_private.h"
#include "list_class.h"

////////////////////////////////////////////////////////////////////

api_list_class_t * api_list_class_t_class = NULL;

static list_class_t * _instance_list_list_class_t[16] = {0};

typedef void ( *list_class_t_delete_list_t )( void );

static void list_class_t_delete_list_instance_00( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->delete_list( _instance_list_list_class_t[ 0] ); }
static void list_class_t_delete_list_instance_01( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->delete_list( _instance_list_list_class_t[ 1] ); }
static void list_class_t_delete_list_instance_02( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->delete_list( _instance_list_list_class_t[ 2] ); }
static void list_class_t_delete_list_instance_03( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->delete_list( _instance_list_list_class_t[ 3] ); }
static void list_class_t_delete_list_instance_04( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->delete_list( _instance_list_list_class_t[ 4] ); }
static void list_class_t_delete_list_instance_05( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->delete_list( _instance_list_list_class_t[ 5] ); }
static void list_class_t_delete_list_instance_06( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->delete_list( _instance_list_list_class_t[ 6] ); }
static void list_class_t_delete_list_instance_07( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->delete_list( _instance_list_list_class_t[ 7] ); }
static void list_class_t_delete_list_instance_08( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->delete_list( _instance_list_list_class_t[ 8] ); }
static void list_class_t_delete_list_instance_09( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->delete_list( _instance_list_list_class_t[ 9] ); }
static void list_class_t_delete_list_instance_10( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->delete_list( _instance_list_list_class_t[10] ); }
static void list_class_t_delete_list_instance_11( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->delete_list( _instance_list_list_class_t[11] ); }
static void list_class_t_delete_list_instance_12( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->delete_list( _instance_list_list_class_t[12] ); }
static void list_class_t_delete_list_instance_13( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->delete_list( _instance_list_list_class_t[13] ); }
static void list_class_t_delete_list_instance_14( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->delete_list( _instance_list_list_class_t[14] ); }
static void list_class_t_delete_list_instance_15( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->delete_list( _instance_list_list_class_t[15] ); }

static const list_class_t_delete_list_t _list_class_t_delete_list_list[16] =
{
    list_class_t_delete_list_instance_00,
    list_class_t_delete_list_instance_01,
    list_class_t_delete_list_instance_02,
    list_class_t_delete_list_instance_03,
    list_class_t_delete_list_instance_04,
    list_class_t_delete_list_instance_05,
    list_class_t_delete_list_instance_06,
    list_class_t_delete_list_instance_07,
    list_class_t_delete_list_instance_08,
    list_class_t_delete_list_instance_09,
    list_class_t_delete_list_instance_10,
    list_class_t_delete_list_instance_11,
    list_class_t_delete_list_instance_12,
    list_class_t_delete_list_instance_13,
    list_class_t_delete_list_instance_14,
    list_class_t_delete_list_instance_15,
};

typedef void ( *list_class_t_clear_t )( void );

static void list_class_t_clear_instance_00( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->clear( _instance_list_list_class_t[ 0] ); }
static void list_class_t_clear_instance_01( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->clear( _instance_list_list_class_t[ 1] ); }
static void list_class_t_clear_instance_02( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->clear( _instance_list_list_class_t[ 2] ); }
static void list_class_t_clear_instance_03( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->clear( _instance_list_list_class_t[ 3] ); }
static void list_class_t_clear_instance_04( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->clear( _instance_list_list_class_t[ 4] ); }
static void list_class_t_clear_instance_05( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->clear( _instance_list_list_class_t[ 5] ); }
static void list_class_t_clear_instance_06( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->clear( _instance_list_list_class_t[ 6] ); }
static void list_class_t_clear_instance_07( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->clear( _instance_list_list_class_t[ 7] ); }
static void list_class_t_clear_instance_08( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->clear( _instance_list_list_class_t[ 8] ); }
static void list_class_t_clear_instance_09( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->clear( _instance_list_list_class_t[ 9] ); }
static void list_class_t_clear_instance_10( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->clear( _instance_list_list_class_t[10] ); }
static void list_class_t_clear_instance_11( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->clear( _instance_list_list_class_t[11] ); }
static void list_class_t_clear_instance_12( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->clear( _instance_list_list_class_t[12] ); }
static void list_class_t_clear_instance_13( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->clear( _instance_list_list_class_t[13] ); }
static void list_class_t_clear_instance_14( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->clear( _instance_list_list_class_t[14] ); }
static void list_class_t_clear_instance_15( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->clear( _instance_list_list_class_t[15] ); }

static const list_class_t_clear_t _list_class_t_clear_list[16] =
{
    list_class_t_clear_instance_00,
    list_class_t_clear_instance_01,
    list_class_t_clear_instance_02,
    list_class_t_clear_instance_03,
    list_class_t_clear_instance_04,
    list_class_t_clear_instance_05,
    list_class_t_clear_instance_06,
    list_class_t_clear_instance_07,
    list_class_t_clear_instance_08,
    list_class_t_clear_instance_09,
    list_class_t_clear_instance_10,
    list_class_t_clear_instance_11,
    list_class_t_clear_instance_12,
    list_class_t_clear_instance_13,
    list_class_t_clear_instance_14,
    list_class_t_clear_instance_15,
};

typedef void ( *list_class_t_insert_head_t )( list_node_t * node );

static void list_class_t_insert_head_instance_00( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->insert_head( _instance_list_list_class_t[ 0], node ); }
static void list_class_t_insert_head_instance_01( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->insert_head( _instance_list_list_class_t[ 1], node ); }
static void list_class_t_insert_head_instance_02( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->insert_head( _instance_list_list_class_t[ 2], node ); }
static void list_class_t_insert_head_instance_03( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->insert_head( _instance_list_list_class_t[ 3], node ); }
static void list_class_t_insert_head_instance_04( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->insert_head( _instance_list_list_class_t[ 4], node ); }
static void list_class_t_insert_head_instance_05( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->insert_head( _instance_list_list_class_t[ 5], node ); }
static void list_class_t_insert_head_instance_06( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->insert_head( _instance_list_list_class_t[ 6], node ); }
static void list_class_t_insert_head_instance_07( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->insert_head( _instance_list_list_class_t[ 7], node ); }
static void list_class_t_insert_head_instance_08( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->insert_head( _instance_list_list_class_t[ 8], node ); }
static void list_class_t_insert_head_instance_09( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->insert_head( _instance_list_list_class_t[ 9], node ); }
static void list_class_t_insert_head_instance_10( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->insert_head( _instance_list_list_class_t[10], node ); }
static void list_class_t_insert_head_instance_11( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->insert_head( _instance_list_list_class_t[11], node ); }
static void list_class_t_insert_head_instance_12( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->insert_head( _instance_list_list_class_t[12], node ); }
static void list_class_t_insert_head_instance_13( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->insert_head( _instance_list_list_class_t[13], node ); }
static void list_class_t_insert_head_instance_14( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->insert_head( _instance_list_list_class_t[14], node ); }
static void list_class_t_insert_head_instance_15( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->insert_head( _instance_list_list_class_t[15], node ); }

static const list_class_t_insert_head_t _list_class_t_insert_head_list[16] =
{
    list_class_t_insert_head_instance_00,
    list_class_t_insert_head_instance_01,
    list_class_t_insert_head_instance_02,
    list_class_t_insert_head_instance_03,
    list_class_t_insert_head_instance_04,
    list_class_t_insert_head_instance_05,
    list_class_t_insert_head_instance_06,
    list_class_t_insert_head_instance_07,
    list_class_t_insert_head_instance_08,
    list_class_t_insert_head_instance_09,
    list_class_t_insert_head_instance_10,
    list_class_t_insert_head_instance_11,
    list_class_t_insert_head_instance_12,
    list_class_t_insert_head_instance_13,
    list_class_t_insert_head_instance_14,
    list_class_t_insert_head_instance_15,
};

typedef void ( *list_class_t_insert_tail_t )( list_node_t * node );

static void list_class_t_insert_tail_instance_00( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->insert_tail( _instance_list_list_class_t[ 0], node ); }
static void list_class_t_insert_tail_instance_01( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->insert_tail( _instance_list_list_class_t[ 1], node ); }
static void list_class_t_insert_tail_instance_02( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->insert_tail( _instance_list_list_class_t[ 2], node ); }
static void list_class_t_insert_tail_instance_03( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->insert_tail( _instance_list_list_class_t[ 3], node ); }
static void list_class_t_insert_tail_instance_04( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->insert_tail( _instance_list_list_class_t[ 4], node ); }
static void list_class_t_insert_tail_instance_05( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->insert_tail( _instance_list_list_class_t[ 5], node ); }
static void list_class_t_insert_tail_instance_06( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->insert_tail( _instance_list_list_class_t[ 6], node ); }
static void list_class_t_insert_tail_instance_07( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->insert_tail( _instance_list_list_class_t[ 7], node ); }
static void list_class_t_insert_tail_instance_08( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->insert_tail( _instance_list_list_class_t[ 8], node ); }
static void list_class_t_insert_tail_instance_09( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->insert_tail( _instance_list_list_class_t[ 9], node ); }
static void list_class_t_insert_tail_instance_10( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->insert_tail( _instance_list_list_class_t[10], node ); }
static void list_class_t_insert_tail_instance_11( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->insert_tail( _instance_list_list_class_t[11], node ); }
static void list_class_t_insert_tail_instance_12( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->insert_tail( _instance_list_list_class_t[12], node ); }
static void list_class_t_insert_tail_instance_13( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->insert_tail( _instance_list_list_class_t[13], node ); }
static void list_class_t_insert_tail_instance_14( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->insert_tail( _instance_list_list_class_t[14], node ); }
static void list_class_t_insert_tail_instance_15( list_node_t * node ){ ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->insert_tail( _instance_list_list_class_t[15], node ); }

static const list_class_t_insert_tail_t _list_class_t_insert_tail_list[16] =
{
    list_class_t_insert_tail_instance_00,
    list_class_t_insert_tail_instance_01,
    list_class_t_insert_tail_instance_02,
    list_class_t_insert_tail_instance_03,
    list_class_t_insert_tail_instance_04,
    list_class_t_insert_tail_instance_05,
    list_class_t_insert_tail_instance_06,
    list_class_t_insert_tail_instance_07,
    list_class_t_insert_tail_instance_08,
    list_class_t_insert_tail_instance_09,
    list_class_t_insert_tail_instance_10,
    list_class_t_insert_tail_instance_11,
    list_class_t_insert_tail_instance_12,
    list_class_t_insert_tail_instance_13,
    list_class_t_insert_tail_instance_14,
    list_class_t_insert_tail_instance_15,
};

typedef void ( *list_class_t_remove_tail_t )( void );

static void list_class_t_remove_tail_instance_00( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->remove_tail( _instance_list_list_class_t[ 0] ); }
static void list_class_t_remove_tail_instance_01( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->remove_tail( _instance_list_list_class_t[ 1] ); }
static void list_class_t_remove_tail_instance_02( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->remove_tail( _instance_list_list_class_t[ 2] ); }
static void list_class_t_remove_tail_instance_03( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->remove_tail( _instance_list_list_class_t[ 3] ); }
static void list_class_t_remove_tail_instance_04( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->remove_tail( _instance_list_list_class_t[ 4] ); }
static void list_class_t_remove_tail_instance_05( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->remove_tail( _instance_list_list_class_t[ 5] ); }
static void list_class_t_remove_tail_instance_06( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->remove_tail( _instance_list_list_class_t[ 6] ); }
static void list_class_t_remove_tail_instance_07( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->remove_tail( _instance_list_list_class_t[ 7] ); }
static void list_class_t_remove_tail_instance_08( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->remove_tail( _instance_list_list_class_t[ 8] ); }
static void list_class_t_remove_tail_instance_09( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->remove_tail( _instance_list_list_class_t[ 9] ); }
static void list_class_t_remove_tail_instance_10( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->remove_tail( _instance_list_list_class_t[10] ); }
static void list_class_t_remove_tail_instance_11( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->remove_tail( _instance_list_list_class_t[11] ); }
static void list_class_t_remove_tail_instance_12( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->remove_tail( _instance_list_list_class_t[12] ); }
static void list_class_t_remove_tail_instance_13( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->remove_tail( _instance_list_list_class_t[13] ); }
static void list_class_t_remove_tail_instance_14( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->remove_tail( _instance_list_list_class_t[14] ); }
static void list_class_t_remove_tail_instance_15( void ){ ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->remove_tail( _instance_list_list_class_t[15] ); }

static const list_class_t_remove_tail_t _list_class_t_remove_tail_list[16] =
{
    list_class_t_remove_tail_instance_00,
    list_class_t_remove_tail_instance_01,
    list_class_t_remove_tail_instance_02,
    list_class_t_remove_tail_instance_03,
    list_class_t_remove_tail_instance_04,
    list_class_t_remove_tail_instance_05,
    list_class_t_remove_tail_instance_06,
    list_class_t_remove_tail_instance_07,
    list_class_t_remove_tail_instance_08,
    list_class_t_remove_tail_instance_09,
    list_class_t_remove_tail_instance_10,
    list_class_t_remove_tail_instance_11,
    list_class_t_remove_tail_instance_12,
    list_class_t_remove_tail_instance_13,
    list_class_t_remove_tail_instance_14,
    list_class_t_remove_tail_instance_15,
};

typedef bool_t ( *list_class_t_unlink_node_t )( list_node_t * node );

static bool_t list_class_t_unlink_node_instance_00( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->unlink_node( _instance_list_list_class_t[ 0], node ); }
static bool_t list_class_t_unlink_node_instance_01( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->unlink_node( _instance_list_list_class_t[ 1], node ); }
static bool_t list_class_t_unlink_node_instance_02( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->unlink_node( _instance_list_list_class_t[ 2], node ); }
static bool_t list_class_t_unlink_node_instance_03( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->unlink_node( _instance_list_list_class_t[ 3], node ); }
static bool_t list_class_t_unlink_node_instance_04( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->unlink_node( _instance_list_list_class_t[ 4], node ); }
static bool_t list_class_t_unlink_node_instance_05( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->unlink_node( _instance_list_list_class_t[ 5], node ); }
static bool_t list_class_t_unlink_node_instance_06( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->unlink_node( _instance_list_list_class_t[ 6], node ); }
static bool_t list_class_t_unlink_node_instance_07( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->unlink_node( _instance_list_list_class_t[ 7], node ); }
static bool_t list_class_t_unlink_node_instance_08( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->unlink_node( _instance_list_list_class_t[ 8], node ); }
static bool_t list_class_t_unlink_node_instance_09( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->unlink_node( _instance_list_list_class_t[ 9], node ); }
static bool_t list_class_t_unlink_node_instance_10( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->unlink_node( _instance_list_list_class_t[10], node ); }
static bool_t list_class_t_unlink_node_instance_11( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->unlink_node( _instance_list_list_class_t[11], node ); }
static bool_t list_class_t_unlink_node_instance_12( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->unlink_node( _instance_list_list_class_t[12], node ); }
static bool_t list_class_t_unlink_node_instance_13( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->unlink_node( _instance_list_list_class_t[13], node ); }
static bool_t list_class_t_unlink_node_instance_14( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->unlink_node( _instance_list_list_class_t[14], node ); }
static bool_t list_class_t_unlink_node_instance_15( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->unlink_node( _instance_list_list_class_t[15], node ); }

static const list_class_t_unlink_node_t _list_class_t_unlink_node_list[16] =
{
    list_class_t_unlink_node_instance_00,
    list_class_t_unlink_node_instance_01,
    list_class_t_unlink_node_instance_02,
    list_class_t_unlink_node_instance_03,
    list_class_t_unlink_node_instance_04,
    list_class_t_unlink_node_instance_05,
    list_class_t_unlink_node_instance_06,
    list_class_t_unlink_node_instance_07,
    list_class_t_unlink_node_instance_08,
    list_class_t_unlink_node_instance_09,
    list_class_t_unlink_node_instance_10,
    list_class_t_unlink_node_instance_11,
    list_class_t_unlink_node_instance_12,
    list_class_t_unlink_node_instance_13,
    list_class_t_unlink_node_instance_14,
    list_class_t_unlink_node_instance_15,
};

typedef bool_t ( *list_class_t_remove_node_t )( list_node_t * node );

static bool_t list_class_t_remove_node_instance_00( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->remove_node( _instance_list_list_class_t[ 0], node ); }
static bool_t list_class_t_remove_node_instance_01( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->remove_node( _instance_list_list_class_t[ 1], node ); }
static bool_t list_class_t_remove_node_instance_02( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->remove_node( _instance_list_list_class_t[ 2], node ); }
static bool_t list_class_t_remove_node_instance_03( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->remove_node( _instance_list_list_class_t[ 3], node ); }
static bool_t list_class_t_remove_node_instance_04( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->remove_node( _instance_list_list_class_t[ 4], node ); }
static bool_t list_class_t_remove_node_instance_05( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->remove_node( _instance_list_list_class_t[ 5], node ); }
static bool_t list_class_t_remove_node_instance_06( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->remove_node( _instance_list_list_class_t[ 6], node ); }
static bool_t list_class_t_remove_node_instance_07( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->remove_node( _instance_list_list_class_t[ 7], node ); }
static bool_t list_class_t_remove_node_instance_08( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->remove_node( _instance_list_list_class_t[ 8], node ); }
static bool_t list_class_t_remove_node_instance_09( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->remove_node( _instance_list_list_class_t[ 9], node ); }
static bool_t list_class_t_remove_node_instance_10( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->remove_node( _instance_list_list_class_t[10], node ); }
static bool_t list_class_t_remove_node_instance_11( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->remove_node( _instance_list_list_class_t[11], node ); }
static bool_t list_class_t_remove_node_instance_12( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->remove_node( _instance_list_list_class_t[12], node ); }
static bool_t list_class_t_remove_node_instance_13( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->remove_node( _instance_list_list_class_t[13], node ); }
static bool_t list_class_t_remove_node_instance_14( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->remove_node( _instance_list_list_class_t[14], node ); }
static bool_t list_class_t_remove_node_instance_15( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->remove_node( _instance_list_list_class_t[15], node ); }

static const list_class_t_remove_node_t _list_class_t_remove_node_list[16] =
{
    list_class_t_remove_node_instance_00,
    list_class_t_remove_node_instance_01,
    list_class_t_remove_node_instance_02,
    list_class_t_remove_node_instance_03,
    list_class_t_remove_node_instance_04,
    list_class_t_remove_node_instance_05,
    list_class_t_remove_node_instance_06,
    list_class_t_remove_node_instance_07,
    list_class_t_remove_node_instance_08,
    list_class_t_remove_node_instance_09,
    list_class_t_remove_node_instance_10,
    list_class_t_remove_node_instance_11,
    list_class_t_remove_node_instance_12,
    list_class_t_remove_node_instance_13,
    list_class_t_remove_node_instance_14,
    list_class_t_remove_node_instance_15,
};

typedef bool_t ( *list_class_t_is_empty_t )( void );

static bool_t list_class_t_is_empty_instance_00( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->is_empty( _instance_list_list_class_t[ 0] ); }
static bool_t list_class_t_is_empty_instance_01( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->is_empty( _instance_list_list_class_t[ 1] ); }
static bool_t list_class_t_is_empty_instance_02( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->is_empty( _instance_list_list_class_t[ 2] ); }
static bool_t list_class_t_is_empty_instance_03( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->is_empty( _instance_list_list_class_t[ 3] ); }
static bool_t list_class_t_is_empty_instance_04( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->is_empty( _instance_list_list_class_t[ 4] ); }
static bool_t list_class_t_is_empty_instance_05( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->is_empty( _instance_list_list_class_t[ 5] ); }
static bool_t list_class_t_is_empty_instance_06( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->is_empty( _instance_list_list_class_t[ 6] ); }
static bool_t list_class_t_is_empty_instance_07( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->is_empty( _instance_list_list_class_t[ 7] ); }
static bool_t list_class_t_is_empty_instance_08( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->is_empty( _instance_list_list_class_t[ 8] ); }
static bool_t list_class_t_is_empty_instance_09( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->is_empty( _instance_list_list_class_t[ 9] ); }
static bool_t list_class_t_is_empty_instance_10( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->is_empty( _instance_list_list_class_t[10] ); }
static bool_t list_class_t_is_empty_instance_11( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->is_empty( _instance_list_list_class_t[11] ); }
static bool_t list_class_t_is_empty_instance_12( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->is_empty( _instance_list_list_class_t[12] ); }
static bool_t list_class_t_is_empty_instance_13( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->is_empty( _instance_list_list_class_t[13] ); }
static bool_t list_class_t_is_empty_instance_14( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->is_empty( _instance_list_list_class_t[14] ); }
static bool_t list_class_t_is_empty_instance_15( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->is_empty( _instance_list_list_class_t[15] ); }

static const list_class_t_is_empty_t _list_class_t_is_empty_list[16] =
{
    list_class_t_is_empty_instance_00,
    list_class_t_is_empty_instance_01,
    list_class_t_is_empty_instance_02,
    list_class_t_is_empty_instance_03,
    list_class_t_is_empty_instance_04,
    list_class_t_is_empty_instance_05,
    list_class_t_is_empty_instance_06,
    list_class_t_is_empty_instance_07,
    list_class_t_is_empty_instance_08,
    list_class_t_is_empty_instance_09,
    list_class_t_is_empty_instance_10,
    list_class_t_is_empty_instance_11,
    list_class_t_is_empty_instance_12,
    list_class_t_is_empty_instance_13,
    list_class_t_is_empty_instance_14,
    list_class_t_is_empty_instance_15,
};

typedef void * ( *list_class_t_get_head_t )( void );

static void * list_class_t_get_head_instance_00( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->get_head( _instance_list_list_class_t[ 0] ); }
static void * list_class_t_get_head_instance_01( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->get_head( _instance_list_list_class_t[ 1] ); }
static void * list_class_t_get_head_instance_02( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->get_head( _instance_list_list_class_t[ 2] ); }
static void * list_class_t_get_head_instance_03( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->get_head( _instance_list_list_class_t[ 3] ); }
static void * list_class_t_get_head_instance_04( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->get_head( _instance_list_list_class_t[ 4] ); }
static void * list_class_t_get_head_instance_05( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->get_head( _instance_list_list_class_t[ 5] ); }
static void * list_class_t_get_head_instance_06( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->get_head( _instance_list_list_class_t[ 6] ); }
static void * list_class_t_get_head_instance_07( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->get_head( _instance_list_list_class_t[ 7] ); }
static void * list_class_t_get_head_instance_08( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->get_head( _instance_list_list_class_t[ 8] ); }
static void * list_class_t_get_head_instance_09( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->get_head( _instance_list_list_class_t[ 9] ); }
static void * list_class_t_get_head_instance_10( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->get_head( _instance_list_list_class_t[10] ); }
static void * list_class_t_get_head_instance_11( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->get_head( _instance_list_list_class_t[11] ); }
static void * list_class_t_get_head_instance_12( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->get_head( _instance_list_list_class_t[12] ); }
static void * list_class_t_get_head_instance_13( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->get_head( _instance_list_list_class_t[13] ); }
static void * list_class_t_get_head_instance_14( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->get_head( _instance_list_list_class_t[14] ); }
static void * list_class_t_get_head_instance_15( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->get_head( _instance_list_list_class_t[15] ); }

static const list_class_t_get_head_t _list_class_t_get_head_list[16] =
{
    list_class_t_get_head_instance_00,
    list_class_t_get_head_instance_01,
    list_class_t_get_head_instance_02,
    list_class_t_get_head_instance_03,
    list_class_t_get_head_instance_04,
    list_class_t_get_head_instance_05,
    list_class_t_get_head_instance_06,
    list_class_t_get_head_instance_07,
    list_class_t_get_head_instance_08,
    list_class_t_get_head_instance_09,
    list_class_t_get_head_instance_10,
    list_class_t_get_head_instance_11,
    list_class_t_get_head_instance_12,
    list_class_t_get_head_instance_13,
    list_class_t_get_head_instance_14,
    list_class_t_get_head_instance_15,
};

typedef void * ( *list_class_t_get_tail_t )( void );

static void * list_class_t_get_tail_instance_00( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->get_tail( _instance_list_list_class_t[ 0] ); }
static void * list_class_t_get_tail_instance_01( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->get_tail( _instance_list_list_class_t[ 1] ); }
static void * list_class_t_get_tail_instance_02( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->get_tail( _instance_list_list_class_t[ 2] ); }
static void * list_class_t_get_tail_instance_03( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->get_tail( _instance_list_list_class_t[ 3] ); }
static void * list_class_t_get_tail_instance_04( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->get_tail( _instance_list_list_class_t[ 4] ); }
static void * list_class_t_get_tail_instance_05( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->get_tail( _instance_list_list_class_t[ 5] ); }
static void * list_class_t_get_tail_instance_06( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->get_tail( _instance_list_list_class_t[ 6] ); }
static void * list_class_t_get_tail_instance_07( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->get_tail( _instance_list_list_class_t[ 7] ); }
static void * list_class_t_get_tail_instance_08( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->get_tail( _instance_list_list_class_t[ 8] ); }
static void * list_class_t_get_tail_instance_09( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->get_tail( _instance_list_list_class_t[ 9] ); }
static void * list_class_t_get_tail_instance_10( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->get_tail( _instance_list_list_class_t[10] ); }
static void * list_class_t_get_tail_instance_11( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->get_tail( _instance_list_list_class_t[11] ); }
static void * list_class_t_get_tail_instance_12( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->get_tail( _instance_list_list_class_t[12] ); }
static void * list_class_t_get_tail_instance_13( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->get_tail( _instance_list_list_class_t[13] ); }
static void * list_class_t_get_tail_instance_14( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->get_tail( _instance_list_list_class_t[14] ); }
static void * list_class_t_get_tail_instance_15( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->get_tail( _instance_list_list_class_t[15] ); }

static const list_class_t_get_tail_t _list_class_t_get_tail_list[16] =
{
    list_class_t_get_tail_instance_00,
    list_class_t_get_tail_instance_01,
    list_class_t_get_tail_instance_02,
    list_class_t_get_tail_instance_03,
    list_class_t_get_tail_instance_04,
    list_class_t_get_tail_instance_05,
    list_class_t_get_tail_instance_06,
    list_class_t_get_tail_instance_07,
    list_class_t_get_tail_instance_08,
    list_class_t_get_tail_instance_09,
    list_class_t_get_tail_instance_10,
    list_class_t_get_tail_instance_11,
    list_class_t_get_tail_instance_12,
    list_class_t_get_tail_instance_13,
    list_class_t_get_tail_instance_14,
    list_class_t_get_tail_instance_15,
};

typedef void * ( *list_class_t_get_next_t )( list_node_t * node );

static void * list_class_t_get_next_instance_00( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->get_next( _instance_list_list_class_t[ 0], node ); }
static void * list_class_t_get_next_instance_01( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->get_next( _instance_list_list_class_t[ 1], node ); }
static void * list_class_t_get_next_instance_02( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->get_next( _instance_list_list_class_t[ 2], node ); }
static void * list_class_t_get_next_instance_03( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->get_next( _instance_list_list_class_t[ 3], node ); }
static void * list_class_t_get_next_instance_04( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->get_next( _instance_list_list_class_t[ 4], node ); }
static void * list_class_t_get_next_instance_05( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->get_next( _instance_list_list_class_t[ 5], node ); }
static void * list_class_t_get_next_instance_06( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->get_next( _instance_list_list_class_t[ 6], node ); }
static void * list_class_t_get_next_instance_07( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->get_next( _instance_list_list_class_t[ 7], node ); }
static void * list_class_t_get_next_instance_08( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->get_next( _instance_list_list_class_t[ 8], node ); }
static void * list_class_t_get_next_instance_09( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->get_next( _instance_list_list_class_t[ 9], node ); }
static void * list_class_t_get_next_instance_10( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->get_next( _instance_list_list_class_t[10], node ); }
static void * list_class_t_get_next_instance_11( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->get_next( _instance_list_list_class_t[11], node ); }
static void * list_class_t_get_next_instance_12( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->get_next( _instance_list_list_class_t[12], node ); }
static void * list_class_t_get_next_instance_13( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->get_next( _instance_list_list_class_t[13], node ); }
static void * list_class_t_get_next_instance_14( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->get_next( _instance_list_list_class_t[14], node ); }
static void * list_class_t_get_next_instance_15( list_node_t * node ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->get_next( _instance_list_list_class_t[15], node ); }

static const list_class_t_get_next_t _list_class_t_get_next_list[16] =
{
    list_class_t_get_next_instance_00,
    list_class_t_get_next_instance_01,
    list_class_t_get_next_instance_02,
    list_class_t_get_next_instance_03,
    list_class_t_get_next_instance_04,
    list_class_t_get_next_instance_05,
    list_class_t_get_next_instance_06,
    list_class_t_get_next_instance_07,
    list_class_t_get_next_instance_08,
    list_class_t_get_next_instance_09,
    list_class_t_get_next_instance_10,
    list_class_t_get_next_instance_11,
    list_class_t_get_next_instance_12,
    list_class_t_get_next_instance_13,
    list_class_t_get_next_instance_14,
    list_class_t_get_next_instance_15,
};

typedef void * ( *list_class_t_get_prev_t )( list_node_t * curr );

static void * list_class_t_get_prev_instance_00( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->get_prev( _instance_list_list_class_t[ 0], curr ); }
static void * list_class_t_get_prev_instance_01( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->get_prev( _instance_list_list_class_t[ 1], curr ); }
static void * list_class_t_get_prev_instance_02( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->get_prev( _instance_list_list_class_t[ 2], curr ); }
static void * list_class_t_get_prev_instance_03( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->get_prev( _instance_list_list_class_t[ 3], curr ); }
static void * list_class_t_get_prev_instance_04( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->get_prev( _instance_list_list_class_t[ 4], curr ); }
static void * list_class_t_get_prev_instance_05( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->get_prev( _instance_list_list_class_t[ 5], curr ); }
static void * list_class_t_get_prev_instance_06( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->get_prev( _instance_list_list_class_t[ 6], curr ); }
static void * list_class_t_get_prev_instance_07( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->get_prev( _instance_list_list_class_t[ 7], curr ); }
static void * list_class_t_get_prev_instance_08( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->get_prev( _instance_list_list_class_t[ 8], curr ); }
static void * list_class_t_get_prev_instance_09( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->get_prev( _instance_list_list_class_t[ 9], curr ); }
static void * list_class_t_get_prev_instance_10( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->get_prev( _instance_list_list_class_t[10], curr ); }
static void * list_class_t_get_prev_instance_11( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->get_prev( _instance_list_list_class_t[11], curr ); }
static void * list_class_t_get_prev_instance_12( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->get_prev( _instance_list_list_class_t[12], curr ); }
static void * list_class_t_get_prev_instance_13( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->get_prev( _instance_list_list_class_t[13], curr ); }
static void * list_class_t_get_prev_instance_14( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->get_prev( _instance_list_list_class_t[14], curr ); }
static void * list_class_t_get_prev_instance_15( list_node_t * curr ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->get_prev( _instance_list_list_class_t[15], curr ); }

static const list_class_t_get_prev_t _list_class_t_get_prev_list[16] =
{
    list_class_t_get_prev_instance_00,
    list_class_t_get_prev_instance_01,
    list_class_t_get_prev_instance_02,
    list_class_t_get_prev_instance_03,
    list_class_t_get_prev_instance_04,
    list_class_t_get_prev_instance_05,
    list_class_t_get_prev_instance_06,
    list_class_t_get_prev_instance_07,
    list_class_t_get_prev_instance_08,
    list_class_t_get_prev_instance_09,
    list_class_t_get_prev_instance_10,
    list_class_t_get_prev_instance_11,
    list_class_t_get_prev_instance_12,
    list_class_t_get_prev_instance_13,
    list_class_t_get_prev_instance_14,
    list_class_t_get_prev_instance_15,
};

typedef uint16_t ( *list_class_t_size_t )( void );

static uint16_t list_class_t_size_instance_00( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 0]->__api )->size( _instance_list_list_class_t[ 0] ); }
static uint16_t list_class_t_size_instance_01( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 1]->__api )->size( _instance_list_list_class_t[ 1] ); }
static uint16_t list_class_t_size_instance_02( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 2]->__api )->size( _instance_list_list_class_t[ 2] ); }
static uint16_t list_class_t_size_instance_03( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 3]->__api )->size( _instance_list_list_class_t[ 3] ); }
static uint16_t list_class_t_size_instance_04( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 4]->__api )->size( _instance_list_list_class_t[ 4] ); }
static uint16_t list_class_t_size_instance_05( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 5]->__api )->size( _instance_list_list_class_t[ 5] ); }
static uint16_t list_class_t_size_instance_06( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 6]->__api )->size( _instance_list_list_class_t[ 6] ); }
static uint16_t list_class_t_size_instance_07( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 7]->__api )->size( _instance_list_list_class_t[ 7] ); }
static uint16_t list_class_t_size_instance_08( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 8]->__api )->size( _instance_list_list_class_t[ 8] ); }
static uint16_t list_class_t_size_instance_09( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[ 9]->__api )->size( _instance_list_list_class_t[ 9] ); }
static uint16_t list_class_t_size_instance_10( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[10]->__api )->size( _instance_list_list_class_t[10] ); }
static uint16_t list_class_t_size_instance_11( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[11]->__api )->size( _instance_list_list_class_t[11] ); }
static uint16_t list_class_t_size_instance_12( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[12]->__api )->size( _instance_list_list_class_t[12] ); }
static uint16_t list_class_t_size_instance_13( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[13]->__api )->size( _instance_list_list_class_t[13] ); }
static uint16_t list_class_t_size_instance_14( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[14]->__api )->size( _instance_list_list_class_t[14] ); }
static uint16_t list_class_t_size_instance_15( void ){ return ( ( api_list_class_t * )_instance_list_list_class_t[15]->__api )->size( _instance_list_list_class_t[15] ); }

static const list_class_t_size_t _list_class_t_size_list[16] =
{
    list_class_t_size_instance_00,
    list_class_t_size_instance_01,
    list_class_t_size_instance_02,
    list_class_t_size_instance_03,
    list_class_t_size_instance_04,
    list_class_t_size_instance_05,
    list_class_t_size_instance_06,
    list_class_t_size_instance_07,
    list_class_t_size_instance_08,
    list_class_t_size_instance_09,
    list_class_t_size_instance_10,
    list_class_t_size_instance_11,
    list_class_t_size_instance_12,
    list_class_t_size_instance_13,
    list_class_t_size_instance_14,
    list_class_t_size_instance_15,
};

void * _instance_new_list_class_t_ex( void * __api, delete_cb_t delete_cb )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_list_class_t, sizeof(list_class_t), 16 );
    if( _instance_index == -1 ) return NULL;
    list_class_t * ret = _instance_list_list_class_t[_instance_index];
    ret->__api = __api;
    ret->clear = _list_class_t_clear_list[_instance_index];
    ret->insert_head = _list_class_t_insert_head_list[_instance_index];
    ret->insert_tail = _list_class_t_insert_tail_list[_instance_index];
    ret->remove_tail = _list_class_t_remove_tail_list[_instance_index];
    ret->unlink_node = _list_class_t_unlink_node_list[_instance_index];
    ret->remove_node = _list_class_t_remove_node_list[_instance_index];
    ret->is_empty = _list_class_t_is_empty_list[_instance_index];
    ret->get_head = _list_class_t_get_head_list[_instance_index];
    ret->get_tail = _list_class_t_get_tail_list[_instance_index];
    ret->get_next = _list_class_t_get_next_list[_instance_index];
    ret->get_prev = _list_class_t_get_prev_list[_instance_index];
    ret->size = _list_class_t_size_list[_instance_index];
    api_list_class_t_class->creator_list( ret, delete_cb );
    ret->__default_del = _list_class_t_delete_list_list[_instance_index];
    return ret;
}

void * _instance_new_list_class_t( delete_cb_t delete_cb )
{
    return _instance_new_list_class_t_ex( api_list_class_t_class, delete_cb );
}

void * _instance_static_list_class_t_method( void * __api )
{
    return api_list_class_t_class;
}

#if 0 // method definition for list_class_t

#include "list_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator_list( list_class_t * p_data, delete_cb_t delete_cb )
{
}

DELETE static void delete_list( list_class_t * p_data )
{
}

METHOD static void clear( list_class_t * p_data )
{
}

METHOD static void insert_head( list_class_t * p_data, list_node_t * node )
{
}

METHOD static void insert_tail( list_class_t * p_data, list_node_t * node )
{
}

METHOD static void remove_tail( list_class_t * p_data )
{
}

METHOD static bool_t unlink_node( list_class_t * p_data, list_node_t * node )
{
}

METHOD static bool_t remove_node( list_class_t * p_data, list_node_t * node )
{
}

METHOD static bool_t is_empty( list_class_t * p_data )
{
}

METHOD static void * get_head( list_class_t * p_data )
{
}

METHOD static void * get_tail( list_class_t * p_data )
{
}

METHOD static void * get_next( list_class_t * p_data, list_node_t * node )
{
}

METHOD static void * get_prev( list_class_t * p_data, list_node_t * curr )
{
}

METHOD static uint16_t size( list_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( list_class_t );

////////////////////////////////////////////////////////////////////

#endif // list_class_t

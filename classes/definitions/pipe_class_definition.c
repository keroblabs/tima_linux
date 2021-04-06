#include "pipe_class_private.h"
#include "pipe_class.h"

////////////////////////////////////////////////////////////////////

api_pipe_class_t * api_pipe_class_t_class = NULL;

static pipe_class_t * _instance_list_pipe_class_t[32] = {0};

typedef void ( *pipe_class_t_delete_pipe_t )( void );

static void pipe_class_t_delete_pipe_instance_00( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->delete_pipe( _instance_list_pipe_class_t[ 0] ); }
static void pipe_class_t_delete_pipe_instance_01( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->delete_pipe( _instance_list_pipe_class_t[ 1] ); }
static void pipe_class_t_delete_pipe_instance_02( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->delete_pipe( _instance_list_pipe_class_t[ 2] ); }
static void pipe_class_t_delete_pipe_instance_03( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->delete_pipe( _instance_list_pipe_class_t[ 3] ); }
static void pipe_class_t_delete_pipe_instance_04( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->delete_pipe( _instance_list_pipe_class_t[ 4] ); }
static void pipe_class_t_delete_pipe_instance_05( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->delete_pipe( _instance_list_pipe_class_t[ 5] ); }
static void pipe_class_t_delete_pipe_instance_06( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->delete_pipe( _instance_list_pipe_class_t[ 6] ); }
static void pipe_class_t_delete_pipe_instance_07( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->delete_pipe( _instance_list_pipe_class_t[ 7] ); }
static void pipe_class_t_delete_pipe_instance_08( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->delete_pipe( _instance_list_pipe_class_t[ 8] ); }
static void pipe_class_t_delete_pipe_instance_09( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->delete_pipe( _instance_list_pipe_class_t[ 9] ); }
static void pipe_class_t_delete_pipe_instance_10( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->delete_pipe( _instance_list_pipe_class_t[10] ); }
static void pipe_class_t_delete_pipe_instance_11( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->delete_pipe( _instance_list_pipe_class_t[11] ); }
static void pipe_class_t_delete_pipe_instance_12( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->delete_pipe( _instance_list_pipe_class_t[12] ); }
static void pipe_class_t_delete_pipe_instance_13( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->delete_pipe( _instance_list_pipe_class_t[13] ); }
static void pipe_class_t_delete_pipe_instance_14( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->delete_pipe( _instance_list_pipe_class_t[14] ); }
static void pipe_class_t_delete_pipe_instance_15( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->delete_pipe( _instance_list_pipe_class_t[15] ); }
static void pipe_class_t_delete_pipe_instance_16( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->delete_pipe( _instance_list_pipe_class_t[16] ); }
static void pipe_class_t_delete_pipe_instance_17( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->delete_pipe( _instance_list_pipe_class_t[17] ); }
static void pipe_class_t_delete_pipe_instance_18( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->delete_pipe( _instance_list_pipe_class_t[18] ); }
static void pipe_class_t_delete_pipe_instance_19( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->delete_pipe( _instance_list_pipe_class_t[19] ); }
static void pipe_class_t_delete_pipe_instance_20( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->delete_pipe( _instance_list_pipe_class_t[20] ); }
static void pipe_class_t_delete_pipe_instance_21( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->delete_pipe( _instance_list_pipe_class_t[21] ); }
static void pipe_class_t_delete_pipe_instance_22( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->delete_pipe( _instance_list_pipe_class_t[22] ); }
static void pipe_class_t_delete_pipe_instance_23( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->delete_pipe( _instance_list_pipe_class_t[23] ); }
static void pipe_class_t_delete_pipe_instance_24( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->delete_pipe( _instance_list_pipe_class_t[24] ); }
static void pipe_class_t_delete_pipe_instance_25( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->delete_pipe( _instance_list_pipe_class_t[25] ); }
static void pipe_class_t_delete_pipe_instance_26( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->delete_pipe( _instance_list_pipe_class_t[26] ); }
static void pipe_class_t_delete_pipe_instance_27( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->delete_pipe( _instance_list_pipe_class_t[27] ); }
static void pipe_class_t_delete_pipe_instance_28( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->delete_pipe( _instance_list_pipe_class_t[28] ); }
static void pipe_class_t_delete_pipe_instance_29( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->delete_pipe( _instance_list_pipe_class_t[29] ); }
static void pipe_class_t_delete_pipe_instance_30( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->delete_pipe( _instance_list_pipe_class_t[30] ); }
static void pipe_class_t_delete_pipe_instance_31( void ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->delete_pipe( _instance_list_pipe_class_t[31] ); }

static const pipe_class_t_delete_pipe_t _pipe_class_t_delete_pipe_list[32] =
{
    pipe_class_t_delete_pipe_instance_00,
    pipe_class_t_delete_pipe_instance_01,
    pipe_class_t_delete_pipe_instance_02,
    pipe_class_t_delete_pipe_instance_03,
    pipe_class_t_delete_pipe_instance_04,
    pipe_class_t_delete_pipe_instance_05,
    pipe_class_t_delete_pipe_instance_06,
    pipe_class_t_delete_pipe_instance_07,
    pipe_class_t_delete_pipe_instance_08,
    pipe_class_t_delete_pipe_instance_09,
    pipe_class_t_delete_pipe_instance_10,
    pipe_class_t_delete_pipe_instance_11,
    pipe_class_t_delete_pipe_instance_12,
    pipe_class_t_delete_pipe_instance_13,
    pipe_class_t_delete_pipe_instance_14,
    pipe_class_t_delete_pipe_instance_15,
    pipe_class_t_delete_pipe_instance_16,
    pipe_class_t_delete_pipe_instance_17,
    pipe_class_t_delete_pipe_instance_18,
    pipe_class_t_delete_pipe_instance_19,
    pipe_class_t_delete_pipe_instance_20,
    pipe_class_t_delete_pipe_instance_21,
    pipe_class_t_delete_pipe_instance_22,
    pipe_class_t_delete_pipe_instance_23,
    pipe_class_t_delete_pipe_instance_24,
    pipe_class_t_delete_pipe_instance_25,
    pipe_class_t_delete_pipe_instance_26,
    pipe_class_t_delete_pipe_instance_27,
    pipe_class_t_delete_pipe_instance_28,
    pipe_class_t_delete_pipe_instance_29,
    pipe_class_t_delete_pipe_instance_30,
    pipe_class_t_delete_pipe_instance_31,
};

typedef void * ( *pipe_class_t_get_t )( uint32_t * size );

static void * pipe_class_t_get_instance_00( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->get( _instance_list_pipe_class_t[ 0], size ); }
static void * pipe_class_t_get_instance_01( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->get( _instance_list_pipe_class_t[ 1], size ); }
static void * pipe_class_t_get_instance_02( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->get( _instance_list_pipe_class_t[ 2], size ); }
static void * pipe_class_t_get_instance_03( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->get( _instance_list_pipe_class_t[ 3], size ); }
static void * pipe_class_t_get_instance_04( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->get( _instance_list_pipe_class_t[ 4], size ); }
static void * pipe_class_t_get_instance_05( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->get( _instance_list_pipe_class_t[ 5], size ); }
static void * pipe_class_t_get_instance_06( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->get( _instance_list_pipe_class_t[ 6], size ); }
static void * pipe_class_t_get_instance_07( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->get( _instance_list_pipe_class_t[ 7], size ); }
static void * pipe_class_t_get_instance_08( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->get( _instance_list_pipe_class_t[ 8], size ); }
static void * pipe_class_t_get_instance_09( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->get( _instance_list_pipe_class_t[ 9], size ); }
static void * pipe_class_t_get_instance_10( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->get( _instance_list_pipe_class_t[10], size ); }
static void * pipe_class_t_get_instance_11( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->get( _instance_list_pipe_class_t[11], size ); }
static void * pipe_class_t_get_instance_12( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->get( _instance_list_pipe_class_t[12], size ); }
static void * pipe_class_t_get_instance_13( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->get( _instance_list_pipe_class_t[13], size ); }
static void * pipe_class_t_get_instance_14( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->get( _instance_list_pipe_class_t[14], size ); }
static void * pipe_class_t_get_instance_15( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->get( _instance_list_pipe_class_t[15], size ); }
static void * pipe_class_t_get_instance_16( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->get( _instance_list_pipe_class_t[16], size ); }
static void * pipe_class_t_get_instance_17( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->get( _instance_list_pipe_class_t[17], size ); }
static void * pipe_class_t_get_instance_18( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->get( _instance_list_pipe_class_t[18], size ); }
static void * pipe_class_t_get_instance_19( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->get( _instance_list_pipe_class_t[19], size ); }
static void * pipe_class_t_get_instance_20( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->get( _instance_list_pipe_class_t[20], size ); }
static void * pipe_class_t_get_instance_21( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->get( _instance_list_pipe_class_t[21], size ); }
static void * pipe_class_t_get_instance_22( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->get( _instance_list_pipe_class_t[22], size ); }
static void * pipe_class_t_get_instance_23( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->get( _instance_list_pipe_class_t[23], size ); }
static void * pipe_class_t_get_instance_24( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->get( _instance_list_pipe_class_t[24], size ); }
static void * pipe_class_t_get_instance_25( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->get( _instance_list_pipe_class_t[25], size ); }
static void * pipe_class_t_get_instance_26( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->get( _instance_list_pipe_class_t[26], size ); }
static void * pipe_class_t_get_instance_27( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->get( _instance_list_pipe_class_t[27], size ); }
static void * pipe_class_t_get_instance_28( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->get( _instance_list_pipe_class_t[28], size ); }
static void * pipe_class_t_get_instance_29( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->get( _instance_list_pipe_class_t[29], size ); }
static void * pipe_class_t_get_instance_30( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->get( _instance_list_pipe_class_t[30], size ); }
static void * pipe_class_t_get_instance_31( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->get( _instance_list_pipe_class_t[31], size ); }

static const pipe_class_t_get_t _pipe_class_t_get_list[32] =
{
    pipe_class_t_get_instance_00,
    pipe_class_t_get_instance_01,
    pipe_class_t_get_instance_02,
    pipe_class_t_get_instance_03,
    pipe_class_t_get_instance_04,
    pipe_class_t_get_instance_05,
    pipe_class_t_get_instance_06,
    pipe_class_t_get_instance_07,
    pipe_class_t_get_instance_08,
    pipe_class_t_get_instance_09,
    pipe_class_t_get_instance_10,
    pipe_class_t_get_instance_11,
    pipe_class_t_get_instance_12,
    pipe_class_t_get_instance_13,
    pipe_class_t_get_instance_14,
    pipe_class_t_get_instance_15,
    pipe_class_t_get_instance_16,
    pipe_class_t_get_instance_17,
    pipe_class_t_get_instance_18,
    pipe_class_t_get_instance_19,
    pipe_class_t_get_instance_20,
    pipe_class_t_get_instance_21,
    pipe_class_t_get_instance_22,
    pipe_class_t_get_instance_23,
    pipe_class_t_get_instance_24,
    pipe_class_t_get_instance_25,
    pipe_class_t_get_instance_26,
    pipe_class_t_get_instance_27,
    pipe_class_t_get_instance_28,
    pipe_class_t_get_instance_29,
    pipe_class_t_get_instance_30,
    pipe_class_t_get_instance_31,
};

typedef void * ( *pipe_class_t_read_t )( uint32_t * size );

static void * pipe_class_t_read_instance_00( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->read( _instance_list_pipe_class_t[ 0], size ); }
static void * pipe_class_t_read_instance_01( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->read( _instance_list_pipe_class_t[ 1], size ); }
static void * pipe_class_t_read_instance_02( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->read( _instance_list_pipe_class_t[ 2], size ); }
static void * pipe_class_t_read_instance_03( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->read( _instance_list_pipe_class_t[ 3], size ); }
static void * pipe_class_t_read_instance_04( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->read( _instance_list_pipe_class_t[ 4], size ); }
static void * pipe_class_t_read_instance_05( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->read( _instance_list_pipe_class_t[ 5], size ); }
static void * pipe_class_t_read_instance_06( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->read( _instance_list_pipe_class_t[ 6], size ); }
static void * pipe_class_t_read_instance_07( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->read( _instance_list_pipe_class_t[ 7], size ); }
static void * pipe_class_t_read_instance_08( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->read( _instance_list_pipe_class_t[ 8], size ); }
static void * pipe_class_t_read_instance_09( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->read( _instance_list_pipe_class_t[ 9], size ); }
static void * pipe_class_t_read_instance_10( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->read( _instance_list_pipe_class_t[10], size ); }
static void * pipe_class_t_read_instance_11( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->read( _instance_list_pipe_class_t[11], size ); }
static void * pipe_class_t_read_instance_12( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->read( _instance_list_pipe_class_t[12], size ); }
static void * pipe_class_t_read_instance_13( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->read( _instance_list_pipe_class_t[13], size ); }
static void * pipe_class_t_read_instance_14( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->read( _instance_list_pipe_class_t[14], size ); }
static void * pipe_class_t_read_instance_15( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->read( _instance_list_pipe_class_t[15], size ); }
static void * pipe_class_t_read_instance_16( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->read( _instance_list_pipe_class_t[16], size ); }
static void * pipe_class_t_read_instance_17( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->read( _instance_list_pipe_class_t[17], size ); }
static void * pipe_class_t_read_instance_18( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->read( _instance_list_pipe_class_t[18], size ); }
static void * pipe_class_t_read_instance_19( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->read( _instance_list_pipe_class_t[19], size ); }
static void * pipe_class_t_read_instance_20( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->read( _instance_list_pipe_class_t[20], size ); }
static void * pipe_class_t_read_instance_21( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->read( _instance_list_pipe_class_t[21], size ); }
static void * pipe_class_t_read_instance_22( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->read( _instance_list_pipe_class_t[22], size ); }
static void * pipe_class_t_read_instance_23( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->read( _instance_list_pipe_class_t[23], size ); }
static void * pipe_class_t_read_instance_24( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->read( _instance_list_pipe_class_t[24], size ); }
static void * pipe_class_t_read_instance_25( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->read( _instance_list_pipe_class_t[25], size ); }
static void * pipe_class_t_read_instance_26( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->read( _instance_list_pipe_class_t[26], size ); }
static void * pipe_class_t_read_instance_27( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->read( _instance_list_pipe_class_t[27], size ); }
static void * pipe_class_t_read_instance_28( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->read( _instance_list_pipe_class_t[28], size ); }
static void * pipe_class_t_read_instance_29( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->read( _instance_list_pipe_class_t[29], size ); }
static void * pipe_class_t_read_instance_30( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->read( _instance_list_pipe_class_t[30], size ); }
static void * pipe_class_t_read_instance_31( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->read( _instance_list_pipe_class_t[31], size ); }

static const pipe_class_t_read_t _pipe_class_t_read_list[32] =
{
    pipe_class_t_read_instance_00,
    pipe_class_t_read_instance_01,
    pipe_class_t_read_instance_02,
    pipe_class_t_read_instance_03,
    pipe_class_t_read_instance_04,
    pipe_class_t_read_instance_05,
    pipe_class_t_read_instance_06,
    pipe_class_t_read_instance_07,
    pipe_class_t_read_instance_08,
    pipe_class_t_read_instance_09,
    pipe_class_t_read_instance_10,
    pipe_class_t_read_instance_11,
    pipe_class_t_read_instance_12,
    pipe_class_t_read_instance_13,
    pipe_class_t_read_instance_14,
    pipe_class_t_read_instance_15,
    pipe_class_t_read_instance_16,
    pipe_class_t_read_instance_17,
    pipe_class_t_read_instance_18,
    pipe_class_t_read_instance_19,
    pipe_class_t_read_instance_20,
    pipe_class_t_read_instance_21,
    pipe_class_t_read_instance_22,
    pipe_class_t_read_instance_23,
    pipe_class_t_read_instance_24,
    pipe_class_t_read_instance_25,
    pipe_class_t_read_instance_26,
    pipe_class_t_read_instance_27,
    pipe_class_t_read_instance_28,
    pipe_class_t_read_instance_29,
    pipe_class_t_read_instance_30,
    pipe_class_t_read_instance_31,
};

typedef void * ( *pipe_class_t_wait_for_data_t )( uint32_t * size );

static void * pipe_class_t_wait_for_data_instance_00( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->wait_for_data( _instance_list_pipe_class_t[ 0], size ); }
static void * pipe_class_t_wait_for_data_instance_01( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->wait_for_data( _instance_list_pipe_class_t[ 1], size ); }
static void * pipe_class_t_wait_for_data_instance_02( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->wait_for_data( _instance_list_pipe_class_t[ 2], size ); }
static void * pipe_class_t_wait_for_data_instance_03( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->wait_for_data( _instance_list_pipe_class_t[ 3], size ); }
static void * pipe_class_t_wait_for_data_instance_04( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->wait_for_data( _instance_list_pipe_class_t[ 4], size ); }
static void * pipe_class_t_wait_for_data_instance_05( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->wait_for_data( _instance_list_pipe_class_t[ 5], size ); }
static void * pipe_class_t_wait_for_data_instance_06( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->wait_for_data( _instance_list_pipe_class_t[ 6], size ); }
static void * pipe_class_t_wait_for_data_instance_07( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->wait_for_data( _instance_list_pipe_class_t[ 7], size ); }
static void * pipe_class_t_wait_for_data_instance_08( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->wait_for_data( _instance_list_pipe_class_t[ 8], size ); }
static void * pipe_class_t_wait_for_data_instance_09( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->wait_for_data( _instance_list_pipe_class_t[ 9], size ); }
static void * pipe_class_t_wait_for_data_instance_10( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->wait_for_data( _instance_list_pipe_class_t[10], size ); }
static void * pipe_class_t_wait_for_data_instance_11( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->wait_for_data( _instance_list_pipe_class_t[11], size ); }
static void * pipe_class_t_wait_for_data_instance_12( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->wait_for_data( _instance_list_pipe_class_t[12], size ); }
static void * pipe_class_t_wait_for_data_instance_13( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->wait_for_data( _instance_list_pipe_class_t[13], size ); }
static void * pipe_class_t_wait_for_data_instance_14( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->wait_for_data( _instance_list_pipe_class_t[14], size ); }
static void * pipe_class_t_wait_for_data_instance_15( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->wait_for_data( _instance_list_pipe_class_t[15], size ); }
static void * pipe_class_t_wait_for_data_instance_16( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->wait_for_data( _instance_list_pipe_class_t[16], size ); }
static void * pipe_class_t_wait_for_data_instance_17( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->wait_for_data( _instance_list_pipe_class_t[17], size ); }
static void * pipe_class_t_wait_for_data_instance_18( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->wait_for_data( _instance_list_pipe_class_t[18], size ); }
static void * pipe_class_t_wait_for_data_instance_19( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->wait_for_data( _instance_list_pipe_class_t[19], size ); }
static void * pipe_class_t_wait_for_data_instance_20( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->wait_for_data( _instance_list_pipe_class_t[20], size ); }
static void * pipe_class_t_wait_for_data_instance_21( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->wait_for_data( _instance_list_pipe_class_t[21], size ); }
static void * pipe_class_t_wait_for_data_instance_22( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->wait_for_data( _instance_list_pipe_class_t[22], size ); }
static void * pipe_class_t_wait_for_data_instance_23( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->wait_for_data( _instance_list_pipe_class_t[23], size ); }
static void * pipe_class_t_wait_for_data_instance_24( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->wait_for_data( _instance_list_pipe_class_t[24], size ); }
static void * pipe_class_t_wait_for_data_instance_25( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->wait_for_data( _instance_list_pipe_class_t[25], size ); }
static void * pipe_class_t_wait_for_data_instance_26( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->wait_for_data( _instance_list_pipe_class_t[26], size ); }
static void * pipe_class_t_wait_for_data_instance_27( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->wait_for_data( _instance_list_pipe_class_t[27], size ); }
static void * pipe_class_t_wait_for_data_instance_28( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->wait_for_data( _instance_list_pipe_class_t[28], size ); }
static void * pipe_class_t_wait_for_data_instance_29( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->wait_for_data( _instance_list_pipe_class_t[29], size ); }
static void * pipe_class_t_wait_for_data_instance_30( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->wait_for_data( _instance_list_pipe_class_t[30], size ); }
static void * pipe_class_t_wait_for_data_instance_31( uint32_t * size ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->wait_for_data( _instance_list_pipe_class_t[31], size ); }

static const pipe_class_t_wait_for_data_t _pipe_class_t_wait_for_data_list[32] =
{
    pipe_class_t_wait_for_data_instance_00,
    pipe_class_t_wait_for_data_instance_01,
    pipe_class_t_wait_for_data_instance_02,
    pipe_class_t_wait_for_data_instance_03,
    pipe_class_t_wait_for_data_instance_04,
    pipe_class_t_wait_for_data_instance_05,
    pipe_class_t_wait_for_data_instance_06,
    pipe_class_t_wait_for_data_instance_07,
    pipe_class_t_wait_for_data_instance_08,
    pipe_class_t_wait_for_data_instance_09,
    pipe_class_t_wait_for_data_instance_10,
    pipe_class_t_wait_for_data_instance_11,
    pipe_class_t_wait_for_data_instance_12,
    pipe_class_t_wait_for_data_instance_13,
    pipe_class_t_wait_for_data_instance_14,
    pipe_class_t_wait_for_data_instance_15,
    pipe_class_t_wait_for_data_instance_16,
    pipe_class_t_wait_for_data_instance_17,
    pipe_class_t_wait_for_data_instance_18,
    pipe_class_t_wait_for_data_instance_19,
    pipe_class_t_wait_for_data_instance_20,
    pipe_class_t_wait_for_data_instance_21,
    pipe_class_t_wait_for_data_instance_22,
    pipe_class_t_wait_for_data_instance_23,
    pipe_class_t_wait_for_data_instance_24,
    pipe_class_t_wait_for_data_instance_25,
    pipe_class_t_wait_for_data_instance_26,
    pipe_class_t_wait_for_data_instance_27,
    pipe_class_t_wait_for_data_instance_28,
    pipe_class_t_wait_for_data_instance_29,
    pipe_class_t_wait_for_data_instance_30,
    pipe_class_t_wait_for_data_instance_31,
};

typedef void ( *pipe_class_t_write_t )( void * buffer, uint32_t size );

static void pipe_class_t_write_instance_00( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->write( _instance_list_pipe_class_t[ 0], buffer, size ); }
static void pipe_class_t_write_instance_01( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->write( _instance_list_pipe_class_t[ 1], buffer, size ); }
static void pipe_class_t_write_instance_02( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->write( _instance_list_pipe_class_t[ 2], buffer, size ); }
static void pipe_class_t_write_instance_03( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->write( _instance_list_pipe_class_t[ 3], buffer, size ); }
static void pipe_class_t_write_instance_04( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->write( _instance_list_pipe_class_t[ 4], buffer, size ); }
static void pipe_class_t_write_instance_05( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->write( _instance_list_pipe_class_t[ 5], buffer, size ); }
static void pipe_class_t_write_instance_06( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->write( _instance_list_pipe_class_t[ 6], buffer, size ); }
static void pipe_class_t_write_instance_07( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->write( _instance_list_pipe_class_t[ 7], buffer, size ); }
static void pipe_class_t_write_instance_08( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->write( _instance_list_pipe_class_t[ 8], buffer, size ); }
static void pipe_class_t_write_instance_09( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->write( _instance_list_pipe_class_t[ 9], buffer, size ); }
static void pipe_class_t_write_instance_10( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->write( _instance_list_pipe_class_t[10], buffer, size ); }
static void pipe_class_t_write_instance_11( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->write( _instance_list_pipe_class_t[11], buffer, size ); }
static void pipe_class_t_write_instance_12( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->write( _instance_list_pipe_class_t[12], buffer, size ); }
static void pipe_class_t_write_instance_13( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->write( _instance_list_pipe_class_t[13], buffer, size ); }
static void pipe_class_t_write_instance_14( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->write( _instance_list_pipe_class_t[14], buffer, size ); }
static void pipe_class_t_write_instance_15( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->write( _instance_list_pipe_class_t[15], buffer, size ); }
static void pipe_class_t_write_instance_16( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->write( _instance_list_pipe_class_t[16], buffer, size ); }
static void pipe_class_t_write_instance_17( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->write( _instance_list_pipe_class_t[17], buffer, size ); }
static void pipe_class_t_write_instance_18( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->write( _instance_list_pipe_class_t[18], buffer, size ); }
static void pipe_class_t_write_instance_19( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->write( _instance_list_pipe_class_t[19], buffer, size ); }
static void pipe_class_t_write_instance_20( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->write( _instance_list_pipe_class_t[20], buffer, size ); }
static void pipe_class_t_write_instance_21( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->write( _instance_list_pipe_class_t[21], buffer, size ); }
static void pipe_class_t_write_instance_22( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->write( _instance_list_pipe_class_t[22], buffer, size ); }
static void pipe_class_t_write_instance_23( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->write( _instance_list_pipe_class_t[23], buffer, size ); }
static void pipe_class_t_write_instance_24( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->write( _instance_list_pipe_class_t[24], buffer, size ); }
static void pipe_class_t_write_instance_25( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->write( _instance_list_pipe_class_t[25], buffer, size ); }
static void pipe_class_t_write_instance_26( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->write( _instance_list_pipe_class_t[26], buffer, size ); }
static void pipe_class_t_write_instance_27( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->write( _instance_list_pipe_class_t[27], buffer, size ); }
static void pipe_class_t_write_instance_28( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->write( _instance_list_pipe_class_t[28], buffer, size ); }
static void pipe_class_t_write_instance_29( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->write( _instance_list_pipe_class_t[29], buffer, size ); }
static void pipe_class_t_write_instance_30( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->write( _instance_list_pipe_class_t[30], buffer, size ); }
static void pipe_class_t_write_instance_31( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->write( _instance_list_pipe_class_t[31], buffer, size ); }

static const pipe_class_t_write_t _pipe_class_t_write_list[32] =
{
    pipe_class_t_write_instance_00,
    pipe_class_t_write_instance_01,
    pipe_class_t_write_instance_02,
    pipe_class_t_write_instance_03,
    pipe_class_t_write_instance_04,
    pipe_class_t_write_instance_05,
    pipe_class_t_write_instance_06,
    pipe_class_t_write_instance_07,
    pipe_class_t_write_instance_08,
    pipe_class_t_write_instance_09,
    pipe_class_t_write_instance_10,
    pipe_class_t_write_instance_11,
    pipe_class_t_write_instance_12,
    pipe_class_t_write_instance_13,
    pipe_class_t_write_instance_14,
    pipe_class_t_write_instance_15,
    pipe_class_t_write_instance_16,
    pipe_class_t_write_instance_17,
    pipe_class_t_write_instance_18,
    pipe_class_t_write_instance_19,
    pipe_class_t_write_instance_20,
    pipe_class_t_write_instance_21,
    pipe_class_t_write_instance_22,
    pipe_class_t_write_instance_23,
    pipe_class_t_write_instance_24,
    pipe_class_t_write_instance_25,
    pipe_class_t_write_instance_26,
    pipe_class_t_write_instance_27,
    pipe_class_t_write_instance_28,
    pipe_class_t_write_instance_29,
    pipe_class_t_write_instance_30,
    pipe_class_t_write_instance_31,
};

typedef void ( *pipe_class_t_send_t )( void * buffer, uint32_t size );

static void pipe_class_t_send_instance_00( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->send( _instance_list_pipe_class_t[ 0], buffer, size ); }
static void pipe_class_t_send_instance_01( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->send( _instance_list_pipe_class_t[ 1], buffer, size ); }
static void pipe_class_t_send_instance_02( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->send( _instance_list_pipe_class_t[ 2], buffer, size ); }
static void pipe_class_t_send_instance_03( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->send( _instance_list_pipe_class_t[ 3], buffer, size ); }
static void pipe_class_t_send_instance_04( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->send( _instance_list_pipe_class_t[ 4], buffer, size ); }
static void pipe_class_t_send_instance_05( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->send( _instance_list_pipe_class_t[ 5], buffer, size ); }
static void pipe_class_t_send_instance_06( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->send( _instance_list_pipe_class_t[ 6], buffer, size ); }
static void pipe_class_t_send_instance_07( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->send( _instance_list_pipe_class_t[ 7], buffer, size ); }
static void pipe_class_t_send_instance_08( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->send( _instance_list_pipe_class_t[ 8], buffer, size ); }
static void pipe_class_t_send_instance_09( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->send( _instance_list_pipe_class_t[ 9], buffer, size ); }
static void pipe_class_t_send_instance_10( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->send( _instance_list_pipe_class_t[10], buffer, size ); }
static void pipe_class_t_send_instance_11( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->send( _instance_list_pipe_class_t[11], buffer, size ); }
static void pipe_class_t_send_instance_12( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->send( _instance_list_pipe_class_t[12], buffer, size ); }
static void pipe_class_t_send_instance_13( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->send( _instance_list_pipe_class_t[13], buffer, size ); }
static void pipe_class_t_send_instance_14( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->send( _instance_list_pipe_class_t[14], buffer, size ); }
static void pipe_class_t_send_instance_15( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->send( _instance_list_pipe_class_t[15], buffer, size ); }
static void pipe_class_t_send_instance_16( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->send( _instance_list_pipe_class_t[16], buffer, size ); }
static void pipe_class_t_send_instance_17( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->send( _instance_list_pipe_class_t[17], buffer, size ); }
static void pipe_class_t_send_instance_18( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->send( _instance_list_pipe_class_t[18], buffer, size ); }
static void pipe_class_t_send_instance_19( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->send( _instance_list_pipe_class_t[19], buffer, size ); }
static void pipe_class_t_send_instance_20( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->send( _instance_list_pipe_class_t[20], buffer, size ); }
static void pipe_class_t_send_instance_21( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->send( _instance_list_pipe_class_t[21], buffer, size ); }
static void pipe_class_t_send_instance_22( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->send( _instance_list_pipe_class_t[22], buffer, size ); }
static void pipe_class_t_send_instance_23( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->send( _instance_list_pipe_class_t[23], buffer, size ); }
static void pipe_class_t_send_instance_24( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->send( _instance_list_pipe_class_t[24], buffer, size ); }
static void pipe_class_t_send_instance_25( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->send( _instance_list_pipe_class_t[25], buffer, size ); }
static void pipe_class_t_send_instance_26( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->send( _instance_list_pipe_class_t[26], buffer, size ); }
static void pipe_class_t_send_instance_27( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->send( _instance_list_pipe_class_t[27], buffer, size ); }
static void pipe_class_t_send_instance_28( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->send( _instance_list_pipe_class_t[28], buffer, size ); }
static void pipe_class_t_send_instance_29( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->send( _instance_list_pipe_class_t[29], buffer, size ); }
static void pipe_class_t_send_instance_30( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->send( _instance_list_pipe_class_t[30], buffer, size ); }
static void pipe_class_t_send_instance_31( void * buffer, uint32_t size ){ ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->send( _instance_list_pipe_class_t[31], buffer, size ); }

static const pipe_class_t_send_t _pipe_class_t_send_list[32] =
{
    pipe_class_t_send_instance_00,
    pipe_class_t_send_instance_01,
    pipe_class_t_send_instance_02,
    pipe_class_t_send_instance_03,
    pipe_class_t_send_instance_04,
    pipe_class_t_send_instance_05,
    pipe_class_t_send_instance_06,
    pipe_class_t_send_instance_07,
    pipe_class_t_send_instance_08,
    pipe_class_t_send_instance_09,
    pipe_class_t_send_instance_10,
    pipe_class_t_send_instance_11,
    pipe_class_t_send_instance_12,
    pipe_class_t_send_instance_13,
    pipe_class_t_send_instance_14,
    pipe_class_t_send_instance_15,
    pipe_class_t_send_instance_16,
    pipe_class_t_send_instance_17,
    pipe_class_t_send_instance_18,
    pipe_class_t_send_instance_19,
    pipe_class_t_send_instance_20,
    pipe_class_t_send_instance_21,
    pipe_class_t_send_instance_22,
    pipe_class_t_send_instance_23,
    pipe_class_t_send_instance_24,
    pipe_class_t_send_instance_25,
    pipe_class_t_send_instance_26,
    pipe_class_t_send_instance_27,
    pipe_class_t_send_instance_28,
    pipe_class_t_send_instance_29,
    pipe_class_t_send_instance_30,
    pipe_class_t_send_instance_31,
};

typedef bool_t ( *pipe_class_t_is_full_t )( void );

static bool_t pipe_class_t_is_full_instance_00( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->is_full( _instance_list_pipe_class_t[ 0] ); }
static bool_t pipe_class_t_is_full_instance_01( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->is_full( _instance_list_pipe_class_t[ 1] ); }
static bool_t pipe_class_t_is_full_instance_02( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->is_full( _instance_list_pipe_class_t[ 2] ); }
static bool_t pipe_class_t_is_full_instance_03( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->is_full( _instance_list_pipe_class_t[ 3] ); }
static bool_t pipe_class_t_is_full_instance_04( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->is_full( _instance_list_pipe_class_t[ 4] ); }
static bool_t pipe_class_t_is_full_instance_05( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->is_full( _instance_list_pipe_class_t[ 5] ); }
static bool_t pipe_class_t_is_full_instance_06( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->is_full( _instance_list_pipe_class_t[ 6] ); }
static bool_t pipe_class_t_is_full_instance_07( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->is_full( _instance_list_pipe_class_t[ 7] ); }
static bool_t pipe_class_t_is_full_instance_08( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->is_full( _instance_list_pipe_class_t[ 8] ); }
static bool_t pipe_class_t_is_full_instance_09( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->is_full( _instance_list_pipe_class_t[ 9] ); }
static bool_t pipe_class_t_is_full_instance_10( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->is_full( _instance_list_pipe_class_t[10] ); }
static bool_t pipe_class_t_is_full_instance_11( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->is_full( _instance_list_pipe_class_t[11] ); }
static bool_t pipe_class_t_is_full_instance_12( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->is_full( _instance_list_pipe_class_t[12] ); }
static bool_t pipe_class_t_is_full_instance_13( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->is_full( _instance_list_pipe_class_t[13] ); }
static bool_t pipe_class_t_is_full_instance_14( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->is_full( _instance_list_pipe_class_t[14] ); }
static bool_t pipe_class_t_is_full_instance_15( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->is_full( _instance_list_pipe_class_t[15] ); }
static bool_t pipe_class_t_is_full_instance_16( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->is_full( _instance_list_pipe_class_t[16] ); }
static bool_t pipe_class_t_is_full_instance_17( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->is_full( _instance_list_pipe_class_t[17] ); }
static bool_t pipe_class_t_is_full_instance_18( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->is_full( _instance_list_pipe_class_t[18] ); }
static bool_t pipe_class_t_is_full_instance_19( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->is_full( _instance_list_pipe_class_t[19] ); }
static bool_t pipe_class_t_is_full_instance_20( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->is_full( _instance_list_pipe_class_t[20] ); }
static bool_t pipe_class_t_is_full_instance_21( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->is_full( _instance_list_pipe_class_t[21] ); }
static bool_t pipe_class_t_is_full_instance_22( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->is_full( _instance_list_pipe_class_t[22] ); }
static bool_t pipe_class_t_is_full_instance_23( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->is_full( _instance_list_pipe_class_t[23] ); }
static bool_t pipe_class_t_is_full_instance_24( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->is_full( _instance_list_pipe_class_t[24] ); }
static bool_t pipe_class_t_is_full_instance_25( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->is_full( _instance_list_pipe_class_t[25] ); }
static bool_t pipe_class_t_is_full_instance_26( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->is_full( _instance_list_pipe_class_t[26] ); }
static bool_t pipe_class_t_is_full_instance_27( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->is_full( _instance_list_pipe_class_t[27] ); }
static bool_t pipe_class_t_is_full_instance_28( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->is_full( _instance_list_pipe_class_t[28] ); }
static bool_t pipe_class_t_is_full_instance_29( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->is_full( _instance_list_pipe_class_t[29] ); }
static bool_t pipe_class_t_is_full_instance_30( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->is_full( _instance_list_pipe_class_t[30] ); }
static bool_t pipe_class_t_is_full_instance_31( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->is_full( _instance_list_pipe_class_t[31] ); }

static const pipe_class_t_is_full_t _pipe_class_t_is_full_list[32] =
{
    pipe_class_t_is_full_instance_00,
    pipe_class_t_is_full_instance_01,
    pipe_class_t_is_full_instance_02,
    pipe_class_t_is_full_instance_03,
    pipe_class_t_is_full_instance_04,
    pipe_class_t_is_full_instance_05,
    pipe_class_t_is_full_instance_06,
    pipe_class_t_is_full_instance_07,
    pipe_class_t_is_full_instance_08,
    pipe_class_t_is_full_instance_09,
    pipe_class_t_is_full_instance_10,
    pipe_class_t_is_full_instance_11,
    pipe_class_t_is_full_instance_12,
    pipe_class_t_is_full_instance_13,
    pipe_class_t_is_full_instance_14,
    pipe_class_t_is_full_instance_15,
    pipe_class_t_is_full_instance_16,
    pipe_class_t_is_full_instance_17,
    pipe_class_t_is_full_instance_18,
    pipe_class_t_is_full_instance_19,
    pipe_class_t_is_full_instance_20,
    pipe_class_t_is_full_instance_21,
    pipe_class_t_is_full_instance_22,
    pipe_class_t_is_full_instance_23,
    pipe_class_t_is_full_instance_24,
    pipe_class_t_is_full_instance_25,
    pipe_class_t_is_full_instance_26,
    pipe_class_t_is_full_instance_27,
    pipe_class_t_is_full_instance_28,
    pipe_class_t_is_full_instance_29,
    pipe_class_t_is_full_instance_30,
    pipe_class_t_is_full_instance_31,
};

typedef bool_t ( *pipe_class_t_is_empty_t )( void );

static bool_t pipe_class_t_is_empty_instance_00( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 0]->__api )->is_empty( _instance_list_pipe_class_t[ 0] ); }
static bool_t pipe_class_t_is_empty_instance_01( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 1]->__api )->is_empty( _instance_list_pipe_class_t[ 1] ); }
static bool_t pipe_class_t_is_empty_instance_02( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 2]->__api )->is_empty( _instance_list_pipe_class_t[ 2] ); }
static bool_t pipe_class_t_is_empty_instance_03( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 3]->__api )->is_empty( _instance_list_pipe_class_t[ 3] ); }
static bool_t pipe_class_t_is_empty_instance_04( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 4]->__api )->is_empty( _instance_list_pipe_class_t[ 4] ); }
static bool_t pipe_class_t_is_empty_instance_05( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 5]->__api )->is_empty( _instance_list_pipe_class_t[ 5] ); }
static bool_t pipe_class_t_is_empty_instance_06( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 6]->__api )->is_empty( _instance_list_pipe_class_t[ 6] ); }
static bool_t pipe_class_t_is_empty_instance_07( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 7]->__api )->is_empty( _instance_list_pipe_class_t[ 7] ); }
static bool_t pipe_class_t_is_empty_instance_08( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 8]->__api )->is_empty( _instance_list_pipe_class_t[ 8] ); }
static bool_t pipe_class_t_is_empty_instance_09( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[ 9]->__api )->is_empty( _instance_list_pipe_class_t[ 9] ); }
static bool_t pipe_class_t_is_empty_instance_10( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[10]->__api )->is_empty( _instance_list_pipe_class_t[10] ); }
static bool_t pipe_class_t_is_empty_instance_11( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[11]->__api )->is_empty( _instance_list_pipe_class_t[11] ); }
static bool_t pipe_class_t_is_empty_instance_12( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[12]->__api )->is_empty( _instance_list_pipe_class_t[12] ); }
static bool_t pipe_class_t_is_empty_instance_13( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[13]->__api )->is_empty( _instance_list_pipe_class_t[13] ); }
static bool_t pipe_class_t_is_empty_instance_14( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[14]->__api )->is_empty( _instance_list_pipe_class_t[14] ); }
static bool_t pipe_class_t_is_empty_instance_15( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[15]->__api )->is_empty( _instance_list_pipe_class_t[15] ); }
static bool_t pipe_class_t_is_empty_instance_16( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[16]->__api )->is_empty( _instance_list_pipe_class_t[16] ); }
static bool_t pipe_class_t_is_empty_instance_17( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[17]->__api )->is_empty( _instance_list_pipe_class_t[17] ); }
static bool_t pipe_class_t_is_empty_instance_18( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[18]->__api )->is_empty( _instance_list_pipe_class_t[18] ); }
static bool_t pipe_class_t_is_empty_instance_19( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[19]->__api )->is_empty( _instance_list_pipe_class_t[19] ); }
static bool_t pipe_class_t_is_empty_instance_20( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[20]->__api )->is_empty( _instance_list_pipe_class_t[20] ); }
static bool_t pipe_class_t_is_empty_instance_21( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[21]->__api )->is_empty( _instance_list_pipe_class_t[21] ); }
static bool_t pipe_class_t_is_empty_instance_22( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[22]->__api )->is_empty( _instance_list_pipe_class_t[22] ); }
static bool_t pipe_class_t_is_empty_instance_23( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[23]->__api )->is_empty( _instance_list_pipe_class_t[23] ); }
static bool_t pipe_class_t_is_empty_instance_24( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[24]->__api )->is_empty( _instance_list_pipe_class_t[24] ); }
static bool_t pipe_class_t_is_empty_instance_25( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[25]->__api )->is_empty( _instance_list_pipe_class_t[25] ); }
static bool_t pipe_class_t_is_empty_instance_26( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[26]->__api )->is_empty( _instance_list_pipe_class_t[26] ); }
static bool_t pipe_class_t_is_empty_instance_27( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[27]->__api )->is_empty( _instance_list_pipe_class_t[27] ); }
static bool_t pipe_class_t_is_empty_instance_28( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[28]->__api )->is_empty( _instance_list_pipe_class_t[28] ); }
static bool_t pipe_class_t_is_empty_instance_29( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[29]->__api )->is_empty( _instance_list_pipe_class_t[29] ); }
static bool_t pipe_class_t_is_empty_instance_30( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[30]->__api )->is_empty( _instance_list_pipe_class_t[30] ); }
static bool_t pipe_class_t_is_empty_instance_31( void ){ return ( ( api_pipe_class_t * )_instance_list_pipe_class_t[31]->__api )->is_empty( _instance_list_pipe_class_t[31] ); }

static const pipe_class_t_is_empty_t _pipe_class_t_is_empty_list[32] =
{
    pipe_class_t_is_empty_instance_00,
    pipe_class_t_is_empty_instance_01,
    pipe_class_t_is_empty_instance_02,
    pipe_class_t_is_empty_instance_03,
    pipe_class_t_is_empty_instance_04,
    pipe_class_t_is_empty_instance_05,
    pipe_class_t_is_empty_instance_06,
    pipe_class_t_is_empty_instance_07,
    pipe_class_t_is_empty_instance_08,
    pipe_class_t_is_empty_instance_09,
    pipe_class_t_is_empty_instance_10,
    pipe_class_t_is_empty_instance_11,
    pipe_class_t_is_empty_instance_12,
    pipe_class_t_is_empty_instance_13,
    pipe_class_t_is_empty_instance_14,
    pipe_class_t_is_empty_instance_15,
    pipe_class_t_is_empty_instance_16,
    pipe_class_t_is_empty_instance_17,
    pipe_class_t_is_empty_instance_18,
    pipe_class_t_is_empty_instance_19,
    pipe_class_t_is_empty_instance_20,
    pipe_class_t_is_empty_instance_21,
    pipe_class_t_is_empty_instance_22,
    pipe_class_t_is_empty_instance_23,
    pipe_class_t_is_empty_instance_24,
    pipe_class_t_is_empty_instance_25,
    pipe_class_t_is_empty_instance_26,
    pipe_class_t_is_empty_instance_27,
    pipe_class_t_is_empty_instance_28,
    pipe_class_t_is_empty_instance_29,
    pipe_class_t_is_empty_instance_30,
    pipe_class_t_is_empty_instance_31,
};

void * _instance_new_pipe_class_t_ex( void * __api, uint32_t max_size )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_pipe_class_t, sizeof(pipe_class_t), 32 );
    if( _instance_index == -1 ) return NULL;
    pipe_class_t * ret = _instance_list_pipe_class_t[_instance_index];
    ret->__api = __api;
    ret->get = _pipe_class_t_get_list[_instance_index];
    ret->read = _pipe_class_t_read_list[_instance_index];
    ret->wait_for_data = _pipe_class_t_wait_for_data_list[_instance_index];
    ret->write = _pipe_class_t_write_list[_instance_index];
    ret->send = _pipe_class_t_send_list[_instance_index];
    ret->is_full = _pipe_class_t_is_full_list[_instance_index];
    ret->is_empty = _pipe_class_t_is_empty_list[_instance_index];
    api_pipe_class_t_class->creator( ret, max_size );
    ret->__default_del = _pipe_class_t_delete_pipe_list[_instance_index];
    return ret;
}

void * _instance_new_pipe_class_t( uint32_t max_size )
{
    return _instance_new_pipe_class_t_ex( api_pipe_class_t_class, max_size );
}

void * _instance_static_pipe_class_t_method( void * __api )
{
    return api_pipe_class_t_class;
}

#if 0 // method definition for pipe_class_t

#include "pipe_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( pipe_class_t * p_data, uint32_t max_size )
{
}

DELETE static void delete_pipe( pipe_class_t * p_data )
{
}

METHOD static void * get( pipe_class_t * p_data, uint32_t * size )
{
}

METHOD static void * read( pipe_class_t * p_data, uint32_t * size )
{
}

METHOD static void * wait_for_data( pipe_class_t * p_data, uint32_t * size )
{
}

METHOD static void write( pipe_class_t * p_data, void * buffer, uint32_t size )
{
}

METHOD static void send( pipe_class_t * p_data, void * buffer, uint32_t size )
{
}

METHOD static bool_t is_full( pipe_class_t * p_data )
{
}

METHOD static bool_t is_empty( pipe_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( pipe_class_t );

////////////////////////////////////////////////////////////////////

#endif // pipe_class_t

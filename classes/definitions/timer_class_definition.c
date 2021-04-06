#include "timer_class_private.h"
#include "timer_class.h"

////////////////////////////////////////////////////////////////////

api_timer_class_t * api_timer_class_t_class = NULL;

static timer_class_t * _instance_list_timer_class_t[32] = {0};

typedef void ( *timer_class_t_start_t )( uint32_t period );

static void timer_class_t_start_instance_00( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->start( _instance_list_timer_class_t[ 0], period ); }
static void timer_class_t_start_instance_01( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->start( _instance_list_timer_class_t[ 1], period ); }
static void timer_class_t_start_instance_02( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->start( _instance_list_timer_class_t[ 2], period ); }
static void timer_class_t_start_instance_03( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->start( _instance_list_timer_class_t[ 3], period ); }
static void timer_class_t_start_instance_04( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->start( _instance_list_timer_class_t[ 4], period ); }
static void timer_class_t_start_instance_05( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->start( _instance_list_timer_class_t[ 5], period ); }
static void timer_class_t_start_instance_06( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->start( _instance_list_timer_class_t[ 6], period ); }
static void timer_class_t_start_instance_07( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->start( _instance_list_timer_class_t[ 7], period ); }
static void timer_class_t_start_instance_08( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->start( _instance_list_timer_class_t[ 8], period ); }
static void timer_class_t_start_instance_09( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->start( _instance_list_timer_class_t[ 9], period ); }
static void timer_class_t_start_instance_10( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->start( _instance_list_timer_class_t[10], period ); }
static void timer_class_t_start_instance_11( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->start( _instance_list_timer_class_t[11], period ); }
static void timer_class_t_start_instance_12( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->start( _instance_list_timer_class_t[12], period ); }
static void timer_class_t_start_instance_13( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->start( _instance_list_timer_class_t[13], period ); }
static void timer_class_t_start_instance_14( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->start( _instance_list_timer_class_t[14], period ); }
static void timer_class_t_start_instance_15( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->start( _instance_list_timer_class_t[15], period ); }
static void timer_class_t_start_instance_16( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->start( _instance_list_timer_class_t[16], period ); }
static void timer_class_t_start_instance_17( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->start( _instance_list_timer_class_t[17], period ); }
static void timer_class_t_start_instance_18( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->start( _instance_list_timer_class_t[18], period ); }
static void timer_class_t_start_instance_19( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->start( _instance_list_timer_class_t[19], period ); }
static void timer_class_t_start_instance_20( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->start( _instance_list_timer_class_t[20], period ); }
static void timer_class_t_start_instance_21( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->start( _instance_list_timer_class_t[21], period ); }
static void timer_class_t_start_instance_22( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->start( _instance_list_timer_class_t[22], period ); }
static void timer_class_t_start_instance_23( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->start( _instance_list_timer_class_t[23], period ); }
static void timer_class_t_start_instance_24( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->start( _instance_list_timer_class_t[24], period ); }
static void timer_class_t_start_instance_25( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->start( _instance_list_timer_class_t[25], period ); }
static void timer_class_t_start_instance_26( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->start( _instance_list_timer_class_t[26], period ); }
static void timer_class_t_start_instance_27( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->start( _instance_list_timer_class_t[27], period ); }
static void timer_class_t_start_instance_28( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->start( _instance_list_timer_class_t[28], period ); }
static void timer_class_t_start_instance_29( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->start( _instance_list_timer_class_t[29], period ); }
static void timer_class_t_start_instance_30( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->start( _instance_list_timer_class_t[30], period ); }
static void timer_class_t_start_instance_31( uint32_t period ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->start( _instance_list_timer_class_t[31], period ); }

static const timer_class_t_start_t _timer_class_t_start_list[32] =
{
    timer_class_t_start_instance_00,
    timer_class_t_start_instance_01,
    timer_class_t_start_instance_02,
    timer_class_t_start_instance_03,
    timer_class_t_start_instance_04,
    timer_class_t_start_instance_05,
    timer_class_t_start_instance_06,
    timer_class_t_start_instance_07,
    timer_class_t_start_instance_08,
    timer_class_t_start_instance_09,
    timer_class_t_start_instance_10,
    timer_class_t_start_instance_11,
    timer_class_t_start_instance_12,
    timer_class_t_start_instance_13,
    timer_class_t_start_instance_14,
    timer_class_t_start_instance_15,
    timer_class_t_start_instance_16,
    timer_class_t_start_instance_17,
    timer_class_t_start_instance_18,
    timer_class_t_start_instance_19,
    timer_class_t_start_instance_20,
    timer_class_t_start_instance_21,
    timer_class_t_start_instance_22,
    timer_class_t_start_instance_23,
    timer_class_t_start_instance_24,
    timer_class_t_start_instance_25,
    timer_class_t_start_instance_26,
    timer_class_t_start_instance_27,
    timer_class_t_start_instance_28,
    timer_class_t_start_instance_29,
    timer_class_t_start_instance_30,
    timer_class_t_start_instance_31,
};

typedef void ( *timer_class_t_reload_t )( void );

static void timer_class_t_reload_instance_00( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->reload( _instance_list_timer_class_t[ 0] ); }
static void timer_class_t_reload_instance_01( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->reload( _instance_list_timer_class_t[ 1] ); }
static void timer_class_t_reload_instance_02( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->reload( _instance_list_timer_class_t[ 2] ); }
static void timer_class_t_reload_instance_03( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->reload( _instance_list_timer_class_t[ 3] ); }
static void timer_class_t_reload_instance_04( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->reload( _instance_list_timer_class_t[ 4] ); }
static void timer_class_t_reload_instance_05( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->reload( _instance_list_timer_class_t[ 5] ); }
static void timer_class_t_reload_instance_06( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->reload( _instance_list_timer_class_t[ 6] ); }
static void timer_class_t_reload_instance_07( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->reload( _instance_list_timer_class_t[ 7] ); }
static void timer_class_t_reload_instance_08( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->reload( _instance_list_timer_class_t[ 8] ); }
static void timer_class_t_reload_instance_09( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->reload( _instance_list_timer_class_t[ 9] ); }
static void timer_class_t_reload_instance_10( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->reload( _instance_list_timer_class_t[10] ); }
static void timer_class_t_reload_instance_11( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->reload( _instance_list_timer_class_t[11] ); }
static void timer_class_t_reload_instance_12( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->reload( _instance_list_timer_class_t[12] ); }
static void timer_class_t_reload_instance_13( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->reload( _instance_list_timer_class_t[13] ); }
static void timer_class_t_reload_instance_14( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->reload( _instance_list_timer_class_t[14] ); }
static void timer_class_t_reload_instance_15( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->reload( _instance_list_timer_class_t[15] ); }
static void timer_class_t_reload_instance_16( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->reload( _instance_list_timer_class_t[16] ); }
static void timer_class_t_reload_instance_17( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->reload( _instance_list_timer_class_t[17] ); }
static void timer_class_t_reload_instance_18( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->reload( _instance_list_timer_class_t[18] ); }
static void timer_class_t_reload_instance_19( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->reload( _instance_list_timer_class_t[19] ); }
static void timer_class_t_reload_instance_20( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->reload( _instance_list_timer_class_t[20] ); }
static void timer_class_t_reload_instance_21( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->reload( _instance_list_timer_class_t[21] ); }
static void timer_class_t_reload_instance_22( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->reload( _instance_list_timer_class_t[22] ); }
static void timer_class_t_reload_instance_23( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->reload( _instance_list_timer_class_t[23] ); }
static void timer_class_t_reload_instance_24( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->reload( _instance_list_timer_class_t[24] ); }
static void timer_class_t_reload_instance_25( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->reload( _instance_list_timer_class_t[25] ); }
static void timer_class_t_reload_instance_26( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->reload( _instance_list_timer_class_t[26] ); }
static void timer_class_t_reload_instance_27( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->reload( _instance_list_timer_class_t[27] ); }
static void timer_class_t_reload_instance_28( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->reload( _instance_list_timer_class_t[28] ); }
static void timer_class_t_reload_instance_29( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->reload( _instance_list_timer_class_t[29] ); }
static void timer_class_t_reload_instance_30( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->reload( _instance_list_timer_class_t[30] ); }
static void timer_class_t_reload_instance_31( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->reload( _instance_list_timer_class_t[31] ); }

static const timer_class_t_reload_t _timer_class_t_reload_list[32] =
{
    timer_class_t_reload_instance_00,
    timer_class_t_reload_instance_01,
    timer_class_t_reload_instance_02,
    timer_class_t_reload_instance_03,
    timer_class_t_reload_instance_04,
    timer_class_t_reload_instance_05,
    timer_class_t_reload_instance_06,
    timer_class_t_reload_instance_07,
    timer_class_t_reload_instance_08,
    timer_class_t_reload_instance_09,
    timer_class_t_reload_instance_10,
    timer_class_t_reload_instance_11,
    timer_class_t_reload_instance_12,
    timer_class_t_reload_instance_13,
    timer_class_t_reload_instance_14,
    timer_class_t_reload_instance_15,
    timer_class_t_reload_instance_16,
    timer_class_t_reload_instance_17,
    timer_class_t_reload_instance_18,
    timer_class_t_reload_instance_19,
    timer_class_t_reload_instance_20,
    timer_class_t_reload_instance_21,
    timer_class_t_reload_instance_22,
    timer_class_t_reload_instance_23,
    timer_class_t_reload_instance_24,
    timer_class_t_reload_instance_25,
    timer_class_t_reload_instance_26,
    timer_class_t_reload_instance_27,
    timer_class_t_reload_instance_28,
    timer_class_t_reload_instance_29,
    timer_class_t_reload_instance_30,
    timer_class_t_reload_instance_31,
};

typedef void ( *timer_class_t_stop_t )( void );

static void timer_class_t_stop_instance_00( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->stop( _instance_list_timer_class_t[ 0] ); }
static void timer_class_t_stop_instance_01( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->stop( _instance_list_timer_class_t[ 1] ); }
static void timer_class_t_stop_instance_02( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->stop( _instance_list_timer_class_t[ 2] ); }
static void timer_class_t_stop_instance_03( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->stop( _instance_list_timer_class_t[ 3] ); }
static void timer_class_t_stop_instance_04( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->stop( _instance_list_timer_class_t[ 4] ); }
static void timer_class_t_stop_instance_05( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->stop( _instance_list_timer_class_t[ 5] ); }
static void timer_class_t_stop_instance_06( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->stop( _instance_list_timer_class_t[ 6] ); }
static void timer_class_t_stop_instance_07( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->stop( _instance_list_timer_class_t[ 7] ); }
static void timer_class_t_stop_instance_08( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->stop( _instance_list_timer_class_t[ 8] ); }
static void timer_class_t_stop_instance_09( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->stop( _instance_list_timer_class_t[ 9] ); }
static void timer_class_t_stop_instance_10( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->stop( _instance_list_timer_class_t[10] ); }
static void timer_class_t_stop_instance_11( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->stop( _instance_list_timer_class_t[11] ); }
static void timer_class_t_stop_instance_12( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->stop( _instance_list_timer_class_t[12] ); }
static void timer_class_t_stop_instance_13( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->stop( _instance_list_timer_class_t[13] ); }
static void timer_class_t_stop_instance_14( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->stop( _instance_list_timer_class_t[14] ); }
static void timer_class_t_stop_instance_15( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->stop( _instance_list_timer_class_t[15] ); }
static void timer_class_t_stop_instance_16( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->stop( _instance_list_timer_class_t[16] ); }
static void timer_class_t_stop_instance_17( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->stop( _instance_list_timer_class_t[17] ); }
static void timer_class_t_stop_instance_18( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->stop( _instance_list_timer_class_t[18] ); }
static void timer_class_t_stop_instance_19( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->stop( _instance_list_timer_class_t[19] ); }
static void timer_class_t_stop_instance_20( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->stop( _instance_list_timer_class_t[20] ); }
static void timer_class_t_stop_instance_21( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->stop( _instance_list_timer_class_t[21] ); }
static void timer_class_t_stop_instance_22( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->stop( _instance_list_timer_class_t[22] ); }
static void timer_class_t_stop_instance_23( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->stop( _instance_list_timer_class_t[23] ); }
static void timer_class_t_stop_instance_24( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->stop( _instance_list_timer_class_t[24] ); }
static void timer_class_t_stop_instance_25( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->stop( _instance_list_timer_class_t[25] ); }
static void timer_class_t_stop_instance_26( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->stop( _instance_list_timer_class_t[26] ); }
static void timer_class_t_stop_instance_27( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->stop( _instance_list_timer_class_t[27] ); }
static void timer_class_t_stop_instance_28( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->stop( _instance_list_timer_class_t[28] ); }
static void timer_class_t_stop_instance_29( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->stop( _instance_list_timer_class_t[29] ); }
static void timer_class_t_stop_instance_30( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->stop( _instance_list_timer_class_t[30] ); }
static void timer_class_t_stop_instance_31( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->stop( _instance_list_timer_class_t[31] ); }

static const timer_class_t_stop_t _timer_class_t_stop_list[32] =
{
    timer_class_t_stop_instance_00,
    timer_class_t_stop_instance_01,
    timer_class_t_stop_instance_02,
    timer_class_t_stop_instance_03,
    timer_class_t_stop_instance_04,
    timer_class_t_stop_instance_05,
    timer_class_t_stop_instance_06,
    timer_class_t_stop_instance_07,
    timer_class_t_stop_instance_08,
    timer_class_t_stop_instance_09,
    timer_class_t_stop_instance_10,
    timer_class_t_stop_instance_11,
    timer_class_t_stop_instance_12,
    timer_class_t_stop_instance_13,
    timer_class_t_stop_instance_14,
    timer_class_t_stop_instance_15,
    timer_class_t_stop_instance_16,
    timer_class_t_stop_instance_17,
    timer_class_t_stop_instance_18,
    timer_class_t_stop_instance_19,
    timer_class_t_stop_instance_20,
    timer_class_t_stop_instance_21,
    timer_class_t_stop_instance_22,
    timer_class_t_stop_instance_23,
    timer_class_t_stop_instance_24,
    timer_class_t_stop_instance_25,
    timer_class_t_stop_instance_26,
    timer_class_t_stop_instance_27,
    timer_class_t_stop_instance_28,
    timer_class_t_stop_instance_29,
    timer_class_t_stop_instance_30,
    timer_class_t_stop_instance_31,
};

typedef void ( *timer_class_t_expire_t )( void );

static void timer_class_t_expire_instance_00( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->expire( _instance_list_timer_class_t[ 0] ); }
static void timer_class_t_expire_instance_01( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->expire( _instance_list_timer_class_t[ 1] ); }
static void timer_class_t_expire_instance_02( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->expire( _instance_list_timer_class_t[ 2] ); }
static void timer_class_t_expire_instance_03( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->expire( _instance_list_timer_class_t[ 3] ); }
static void timer_class_t_expire_instance_04( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->expire( _instance_list_timer_class_t[ 4] ); }
static void timer_class_t_expire_instance_05( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->expire( _instance_list_timer_class_t[ 5] ); }
static void timer_class_t_expire_instance_06( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->expire( _instance_list_timer_class_t[ 6] ); }
static void timer_class_t_expire_instance_07( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->expire( _instance_list_timer_class_t[ 7] ); }
static void timer_class_t_expire_instance_08( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->expire( _instance_list_timer_class_t[ 8] ); }
static void timer_class_t_expire_instance_09( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->expire( _instance_list_timer_class_t[ 9] ); }
static void timer_class_t_expire_instance_10( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->expire( _instance_list_timer_class_t[10] ); }
static void timer_class_t_expire_instance_11( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->expire( _instance_list_timer_class_t[11] ); }
static void timer_class_t_expire_instance_12( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->expire( _instance_list_timer_class_t[12] ); }
static void timer_class_t_expire_instance_13( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->expire( _instance_list_timer_class_t[13] ); }
static void timer_class_t_expire_instance_14( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->expire( _instance_list_timer_class_t[14] ); }
static void timer_class_t_expire_instance_15( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->expire( _instance_list_timer_class_t[15] ); }
static void timer_class_t_expire_instance_16( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->expire( _instance_list_timer_class_t[16] ); }
static void timer_class_t_expire_instance_17( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->expire( _instance_list_timer_class_t[17] ); }
static void timer_class_t_expire_instance_18( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->expire( _instance_list_timer_class_t[18] ); }
static void timer_class_t_expire_instance_19( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->expire( _instance_list_timer_class_t[19] ); }
static void timer_class_t_expire_instance_20( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->expire( _instance_list_timer_class_t[20] ); }
static void timer_class_t_expire_instance_21( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->expire( _instance_list_timer_class_t[21] ); }
static void timer_class_t_expire_instance_22( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->expire( _instance_list_timer_class_t[22] ); }
static void timer_class_t_expire_instance_23( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->expire( _instance_list_timer_class_t[23] ); }
static void timer_class_t_expire_instance_24( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->expire( _instance_list_timer_class_t[24] ); }
static void timer_class_t_expire_instance_25( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->expire( _instance_list_timer_class_t[25] ); }
static void timer_class_t_expire_instance_26( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->expire( _instance_list_timer_class_t[26] ); }
static void timer_class_t_expire_instance_27( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->expire( _instance_list_timer_class_t[27] ); }
static void timer_class_t_expire_instance_28( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->expire( _instance_list_timer_class_t[28] ); }
static void timer_class_t_expire_instance_29( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->expire( _instance_list_timer_class_t[29] ); }
static void timer_class_t_expire_instance_30( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->expire( _instance_list_timer_class_t[30] ); }
static void timer_class_t_expire_instance_31( void ){ ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->expire( _instance_list_timer_class_t[31] ); }

static const timer_class_t_expire_t _timer_class_t_expire_list[32] =
{
    timer_class_t_expire_instance_00,
    timer_class_t_expire_instance_01,
    timer_class_t_expire_instance_02,
    timer_class_t_expire_instance_03,
    timer_class_t_expire_instance_04,
    timer_class_t_expire_instance_05,
    timer_class_t_expire_instance_06,
    timer_class_t_expire_instance_07,
    timer_class_t_expire_instance_08,
    timer_class_t_expire_instance_09,
    timer_class_t_expire_instance_10,
    timer_class_t_expire_instance_11,
    timer_class_t_expire_instance_12,
    timer_class_t_expire_instance_13,
    timer_class_t_expire_instance_14,
    timer_class_t_expire_instance_15,
    timer_class_t_expire_instance_16,
    timer_class_t_expire_instance_17,
    timer_class_t_expire_instance_18,
    timer_class_t_expire_instance_19,
    timer_class_t_expire_instance_20,
    timer_class_t_expire_instance_21,
    timer_class_t_expire_instance_22,
    timer_class_t_expire_instance_23,
    timer_class_t_expire_instance_24,
    timer_class_t_expire_instance_25,
    timer_class_t_expire_instance_26,
    timer_class_t_expire_instance_27,
    timer_class_t_expire_instance_28,
    timer_class_t_expire_instance_29,
    timer_class_t_expire_instance_30,
    timer_class_t_expire_instance_31,
};

typedef bool_t ( *timer_class_t_check_t )( void );

static bool_t timer_class_t_check_instance_00( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->check( _instance_list_timer_class_t[ 0] ); }
static bool_t timer_class_t_check_instance_01( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->check( _instance_list_timer_class_t[ 1] ); }
static bool_t timer_class_t_check_instance_02( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->check( _instance_list_timer_class_t[ 2] ); }
static bool_t timer_class_t_check_instance_03( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->check( _instance_list_timer_class_t[ 3] ); }
static bool_t timer_class_t_check_instance_04( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->check( _instance_list_timer_class_t[ 4] ); }
static bool_t timer_class_t_check_instance_05( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->check( _instance_list_timer_class_t[ 5] ); }
static bool_t timer_class_t_check_instance_06( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->check( _instance_list_timer_class_t[ 6] ); }
static bool_t timer_class_t_check_instance_07( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->check( _instance_list_timer_class_t[ 7] ); }
static bool_t timer_class_t_check_instance_08( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->check( _instance_list_timer_class_t[ 8] ); }
static bool_t timer_class_t_check_instance_09( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->check( _instance_list_timer_class_t[ 9] ); }
static bool_t timer_class_t_check_instance_10( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->check( _instance_list_timer_class_t[10] ); }
static bool_t timer_class_t_check_instance_11( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->check( _instance_list_timer_class_t[11] ); }
static bool_t timer_class_t_check_instance_12( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->check( _instance_list_timer_class_t[12] ); }
static bool_t timer_class_t_check_instance_13( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->check( _instance_list_timer_class_t[13] ); }
static bool_t timer_class_t_check_instance_14( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->check( _instance_list_timer_class_t[14] ); }
static bool_t timer_class_t_check_instance_15( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->check( _instance_list_timer_class_t[15] ); }
static bool_t timer_class_t_check_instance_16( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->check( _instance_list_timer_class_t[16] ); }
static bool_t timer_class_t_check_instance_17( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->check( _instance_list_timer_class_t[17] ); }
static bool_t timer_class_t_check_instance_18( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->check( _instance_list_timer_class_t[18] ); }
static bool_t timer_class_t_check_instance_19( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->check( _instance_list_timer_class_t[19] ); }
static bool_t timer_class_t_check_instance_20( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->check( _instance_list_timer_class_t[20] ); }
static bool_t timer_class_t_check_instance_21( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->check( _instance_list_timer_class_t[21] ); }
static bool_t timer_class_t_check_instance_22( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->check( _instance_list_timer_class_t[22] ); }
static bool_t timer_class_t_check_instance_23( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->check( _instance_list_timer_class_t[23] ); }
static bool_t timer_class_t_check_instance_24( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->check( _instance_list_timer_class_t[24] ); }
static bool_t timer_class_t_check_instance_25( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->check( _instance_list_timer_class_t[25] ); }
static bool_t timer_class_t_check_instance_26( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->check( _instance_list_timer_class_t[26] ); }
static bool_t timer_class_t_check_instance_27( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->check( _instance_list_timer_class_t[27] ); }
static bool_t timer_class_t_check_instance_28( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->check( _instance_list_timer_class_t[28] ); }
static bool_t timer_class_t_check_instance_29( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->check( _instance_list_timer_class_t[29] ); }
static bool_t timer_class_t_check_instance_30( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->check( _instance_list_timer_class_t[30] ); }
static bool_t timer_class_t_check_instance_31( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->check( _instance_list_timer_class_t[31] ); }

static const timer_class_t_check_t _timer_class_t_check_list[32] =
{
    timer_class_t_check_instance_00,
    timer_class_t_check_instance_01,
    timer_class_t_check_instance_02,
    timer_class_t_check_instance_03,
    timer_class_t_check_instance_04,
    timer_class_t_check_instance_05,
    timer_class_t_check_instance_06,
    timer_class_t_check_instance_07,
    timer_class_t_check_instance_08,
    timer_class_t_check_instance_09,
    timer_class_t_check_instance_10,
    timer_class_t_check_instance_11,
    timer_class_t_check_instance_12,
    timer_class_t_check_instance_13,
    timer_class_t_check_instance_14,
    timer_class_t_check_instance_15,
    timer_class_t_check_instance_16,
    timer_class_t_check_instance_17,
    timer_class_t_check_instance_18,
    timer_class_t_check_instance_19,
    timer_class_t_check_instance_20,
    timer_class_t_check_instance_21,
    timer_class_t_check_instance_22,
    timer_class_t_check_instance_23,
    timer_class_t_check_instance_24,
    timer_class_t_check_instance_25,
    timer_class_t_check_instance_26,
    timer_class_t_check_instance_27,
    timer_class_t_check_instance_28,
    timer_class_t_check_instance_29,
    timer_class_t_check_instance_30,
    timer_class_t_check_instance_31,
};

typedef uint32_t ( *timer_class_t_get_counter_t )( void );

static uint32_t timer_class_t_get_counter_instance_00( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 0]->__api )->get_counter( _instance_list_timer_class_t[ 0] ); }
static uint32_t timer_class_t_get_counter_instance_01( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 1]->__api )->get_counter( _instance_list_timer_class_t[ 1] ); }
static uint32_t timer_class_t_get_counter_instance_02( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 2]->__api )->get_counter( _instance_list_timer_class_t[ 2] ); }
static uint32_t timer_class_t_get_counter_instance_03( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 3]->__api )->get_counter( _instance_list_timer_class_t[ 3] ); }
static uint32_t timer_class_t_get_counter_instance_04( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 4]->__api )->get_counter( _instance_list_timer_class_t[ 4] ); }
static uint32_t timer_class_t_get_counter_instance_05( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 5]->__api )->get_counter( _instance_list_timer_class_t[ 5] ); }
static uint32_t timer_class_t_get_counter_instance_06( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 6]->__api )->get_counter( _instance_list_timer_class_t[ 6] ); }
static uint32_t timer_class_t_get_counter_instance_07( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 7]->__api )->get_counter( _instance_list_timer_class_t[ 7] ); }
static uint32_t timer_class_t_get_counter_instance_08( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 8]->__api )->get_counter( _instance_list_timer_class_t[ 8] ); }
static uint32_t timer_class_t_get_counter_instance_09( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[ 9]->__api )->get_counter( _instance_list_timer_class_t[ 9] ); }
static uint32_t timer_class_t_get_counter_instance_10( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[10]->__api )->get_counter( _instance_list_timer_class_t[10] ); }
static uint32_t timer_class_t_get_counter_instance_11( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[11]->__api )->get_counter( _instance_list_timer_class_t[11] ); }
static uint32_t timer_class_t_get_counter_instance_12( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[12]->__api )->get_counter( _instance_list_timer_class_t[12] ); }
static uint32_t timer_class_t_get_counter_instance_13( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[13]->__api )->get_counter( _instance_list_timer_class_t[13] ); }
static uint32_t timer_class_t_get_counter_instance_14( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[14]->__api )->get_counter( _instance_list_timer_class_t[14] ); }
static uint32_t timer_class_t_get_counter_instance_15( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[15]->__api )->get_counter( _instance_list_timer_class_t[15] ); }
static uint32_t timer_class_t_get_counter_instance_16( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[16]->__api )->get_counter( _instance_list_timer_class_t[16] ); }
static uint32_t timer_class_t_get_counter_instance_17( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[17]->__api )->get_counter( _instance_list_timer_class_t[17] ); }
static uint32_t timer_class_t_get_counter_instance_18( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[18]->__api )->get_counter( _instance_list_timer_class_t[18] ); }
static uint32_t timer_class_t_get_counter_instance_19( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[19]->__api )->get_counter( _instance_list_timer_class_t[19] ); }
static uint32_t timer_class_t_get_counter_instance_20( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[20]->__api )->get_counter( _instance_list_timer_class_t[20] ); }
static uint32_t timer_class_t_get_counter_instance_21( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[21]->__api )->get_counter( _instance_list_timer_class_t[21] ); }
static uint32_t timer_class_t_get_counter_instance_22( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[22]->__api )->get_counter( _instance_list_timer_class_t[22] ); }
static uint32_t timer_class_t_get_counter_instance_23( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[23]->__api )->get_counter( _instance_list_timer_class_t[23] ); }
static uint32_t timer_class_t_get_counter_instance_24( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[24]->__api )->get_counter( _instance_list_timer_class_t[24] ); }
static uint32_t timer_class_t_get_counter_instance_25( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[25]->__api )->get_counter( _instance_list_timer_class_t[25] ); }
static uint32_t timer_class_t_get_counter_instance_26( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[26]->__api )->get_counter( _instance_list_timer_class_t[26] ); }
static uint32_t timer_class_t_get_counter_instance_27( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[27]->__api )->get_counter( _instance_list_timer_class_t[27] ); }
static uint32_t timer_class_t_get_counter_instance_28( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[28]->__api )->get_counter( _instance_list_timer_class_t[28] ); }
static uint32_t timer_class_t_get_counter_instance_29( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[29]->__api )->get_counter( _instance_list_timer_class_t[29] ); }
static uint32_t timer_class_t_get_counter_instance_30( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[30]->__api )->get_counter( _instance_list_timer_class_t[30] ); }
static uint32_t timer_class_t_get_counter_instance_31( void ){ return ( ( api_timer_class_t * )_instance_list_timer_class_t[31]->__api )->get_counter( _instance_list_timer_class_t[31] ); }

static const timer_class_t_get_counter_t _timer_class_t_get_counter_list[32] =
{
    timer_class_t_get_counter_instance_00,
    timer_class_t_get_counter_instance_01,
    timer_class_t_get_counter_instance_02,
    timer_class_t_get_counter_instance_03,
    timer_class_t_get_counter_instance_04,
    timer_class_t_get_counter_instance_05,
    timer_class_t_get_counter_instance_06,
    timer_class_t_get_counter_instance_07,
    timer_class_t_get_counter_instance_08,
    timer_class_t_get_counter_instance_09,
    timer_class_t_get_counter_instance_10,
    timer_class_t_get_counter_instance_11,
    timer_class_t_get_counter_instance_12,
    timer_class_t_get_counter_instance_13,
    timer_class_t_get_counter_instance_14,
    timer_class_t_get_counter_instance_15,
    timer_class_t_get_counter_instance_16,
    timer_class_t_get_counter_instance_17,
    timer_class_t_get_counter_instance_18,
    timer_class_t_get_counter_instance_19,
    timer_class_t_get_counter_instance_20,
    timer_class_t_get_counter_instance_21,
    timer_class_t_get_counter_instance_22,
    timer_class_t_get_counter_instance_23,
    timer_class_t_get_counter_instance_24,
    timer_class_t_get_counter_instance_25,
    timer_class_t_get_counter_instance_26,
    timer_class_t_get_counter_instance_27,
    timer_class_t_get_counter_instance_28,
    timer_class_t_get_counter_instance_29,
    timer_class_t_get_counter_instance_30,
    timer_class_t_get_counter_instance_31,
};

void * _instance_new_timer_class_t_ex( void * __api, uint32_t period )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_timer_class_t, sizeof(timer_class_t), 32 );
    if( _instance_index == -1 ) return NULL;
    timer_class_t * ret = _instance_list_timer_class_t[_instance_index];
    ret->__api = __api;
    ret->start = _timer_class_t_start_list[_instance_index];
    ret->reload = _timer_class_t_reload_list[_instance_index];
    ret->stop = _timer_class_t_stop_list[_instance_index];
    ret->expire = _timer_class_t_expire_list[_instance_index];
    ret->check = _timer_class_t_check_list[_instance_index];
    ret->get_counter = _timer_class_t_get_counter_list[_instance_index];
    api_timer_class_t_class->creator( ret, period );
    return ret;
}

void * _instance_new_timer_class_t( uint32_t period )
{
    return _instance_new_timer_class_t_ex( api_timer_class_t_class, period );
}

void * _instance_static_timer_class_t_method( void * __api )
{
    return api_timer_class_t_class;
}

#if 0 // method definition for timer_class_t

#include "timer_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( timer_class_t * p_data, uint32_t period )
{
}

METHOD static void start( timer_class_t * p_data, uint32_t period )
{
}

METHOD static void reload( timer_class_t * p_data )
{
}

METHOD static void stop( timer_class_t * p_data )
{
}

METHOD static void expire( timer_class_t * p_data )
{
}

METHOD static bool_t check( timer_class_t * p_data )
{
}

METHOD static uint32_t get_counter( timer_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( timer_class_t );

////////////////////////////////////////////////////////////////////

#endif // timer_class_t

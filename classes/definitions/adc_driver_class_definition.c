#include "adc_driver_class_private.h"
#include "adc_driver_class.h"

////////////////////////////////////////////////////////////////////

api_adc_driver_class_t * api_adc_driver_class_t_class = NULL;

static adc_driver_class_t * _instance_list_adc_driver_class_t[16] = {0};

typedef void ( *adc_driver_class_t_start_t )( void );

static void adc_driver_class_t_start_instance_00( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 0]->__api )->start( _instance_list_adc_driver_class_t[ 0] ); }
static void adc_driver_class_t_start_instance_01( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 1]->__api )->start( _instance_list_adc_driver_class_t[ 1] ); }
static void adc_driver_class_t_start_instance_02( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 2]->__api )->start( _instance_list_adc_driver_class_t[ 2] ); }
static void adc_driver_class_t_start_instance_03( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 3]->__api )->start( _instance_list_adc_driver_class_t[ 3] ); }
static void adc_driver_class_t_start_instance_04( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 4]->__api )->start( _instance_list_adc_driver_class_t[ 4] ); }
static void adc_driver_class_t_start_instance_05( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 5]->__api )->start( _instance_list_adc_driver_class_t[ 5] ); }
static void adc_driver_class_t_start_instance_06( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 6]->__api )->start( _instance_list_adc_driver_class_t[ 6] ); }
static void adc_driver_class_t_start_instance_07( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 7]->__api )->start( _instance_list_adc_driver_class_t[ 7] ); }
static void adc_driver_class_t_start_instance_08( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 8]->__api )->start( _instance_list_adc_driver_class_t[ 8] ); }
static void adc_driver_class_t_start_instance_09( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 9]->__api )->start( _instance_list_adc_driver_class_t[ 9] ); }
static void adc_driver_class_t_start_instance_10( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[10]->__api )->start( _instance_list_adc_driver_class_t[10] ); }
static void adc_driver_class_t_start_instance_11( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[11]->__api )->start( _instance_list_adc_driver_class_t[11] ); }
static void adc_driver_class_t_start_instance_12( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[12]->__api )->start( _instance_list_adc_driver_class_t[12] ); }
static void adc_driver_class_t_start_instance_13( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[13]->__api )->start( _instance_list_adc_driver_class_t[13] ); }
static void adc_driver_class_t_start_instance_14( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[14]->__api )->start( _instance_list_adc_driver_class_t[14] ); }
static void adc_driver_class_t_start_instance_15( void ){ ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[15]->__api )->start( _instance_list_adc_driver_class_t[15] ); }

static const adc_driver_class_t_start_t _adc_driver_class_t_start_list[16] =
{
    adc_driver_class_t_start_instance_00,
    adc_driver_class_t_start_instance_01,
    adc_driver_class_t_start_instance_02,
    adc_driver_class_t_start_instance_03,
    adc_driver_class_t_start_instance_04,
    adc_driver_class_t_start_instance_05,
    adc_driver_class_t_start_instance_06,
    adc_driver_class_t_start_instance_07,
    adc_driver_class_t_start_instance_08,
    adc_driver_class_t_start_instance_09,
    adc_driver_class_t_start_instance_10,
    adc_driver_class_t_start_instance_11,
    adc_driver_class_t_start_instance_12,
    adc_driver_class_t_start_instance_13,
    adc_driver_class_t_start_instance_14,
    adc_driver_class_t_start_instance_15,
};

typedef bool_t ( *adc_driver_class_t_is_ready_t )( void );

static bool_t adc_driver_class_t_is_ready_instance_00( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 0]->__api )->is_ready( _instance_list_adc_driver_class_t[ 0] ); }
static bool_t adc_driver_class_t_is_ready_instance_01( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 1]->__api )->is_ready( _instance_list_adc_driver_class_t[ 1] ); }
static bool_t adc_driver_class_t_is_ready_instance_02( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 2]->__api )->is_ready( _instance_list_adc_driver_class_t[ 2] ); }
static bool_t adc_driver_class_t_is_ready_instance_03( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 3]->__api )->is_ready( _instance_list_adc_driver_class_t[ 3] ); }
static bool_t adc_driver_class_t_is_ready_instance_04( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 4]->__api )->is_ready( _instance_list_adc_driver_class_t[ 4] ); }
static bool_t adc_driver_class_t_is_ready_instance_05( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 5]->__api )->is_ready( _instance_list_adc_driver_class_t[ 5] ); }
static bool_t adc_driver_class_t_is_ready_instance_06( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 6]->__api )->is_ready( _instance_list_adc_driver_class_t[ 6] ); }
static bool_t adc_driver_class_t_is_ready_instance_07( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 7]->__api )->is_ready( _instance_list_adc_driver_class_t[ 7] ); }
static bool_t adc_driver_class_t_is_ready_instance_08( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 8]->__api )->is_ready( _instance_list_adc_driver_class_t[ 8] ); }
static bool_t adc_driver_class_t_is_ready_instance_09( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 9]->__api )->is_ready( _instance_list_adc_driver_class_t[ 9] ); }
static bool_t adc_driver_class_t_is_ready_instance_10( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[10]->__api )->is_ready( _instance_list_adc_driver_class_t[10] ); }
static bool_t adc_driver_class_t_is_ready_instance_11( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[11]->__api )->is_ready( _instance_list_adc_driver_class_t[11] ); }
static bool_t adc_driver_class_t_is_ready_instance_12( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[12]->__api )->is_ready( _instance_list_adc_driver_class_t[12] ); }
static bool_t adc_driver_class_t_is_ready_instance_13( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[13]->__api )->is_ready( _instance_list_adc_driver_class_t[13] ); }
static bool_t adc_driver_class_t_is_ready_instance_14( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[14]->__api )->is_ready( _instance_list_adc_driver_class_t[14] ); }
static bool_t adc_driver_class_t_is_ready_instance_15( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[15]->__api )->is_ready( _instance_list_adc_driver_class_t[15] ); }

static const adc_driver_class_t_is_ready_t _adc_driver_class_t_is_ready_list[16] =
{
    adc_driver_class_t_is_ready_instance_00,
    adc_driver_class_t_is_ready_instance_01,
    adc_driver_class_t_is_ready_instance_02,
    adc_driver_class_t_is_ready_instance_03,
    adc_driver_class_t_is_ready_instance_04,
    adc_driver_class_t_is_ready_instance_05,
    adc_driver_class_t_is_ready_instance_06,
    adc_driver_class_t_is_ready_instance_07,
    adc_driver_class_t_is_ready_instance_08,
    adc_driver_class_t_is_ready_instance_09,
    adc_driver_class_t_is_ready_instance_10,
    adc_driver_class_t_is_ready_instance_11,
    adc_driver_class_t_is_ready_instance_12,
    adc_driver_class_t_is_ready_instance_13,
    adc_driver_class_t_is_ready_instance_14,
    adc_driver_class_t_is_ready_instance_15,
};

typedef uint16_t ( *adc_driver_class_t_read_t )( void );

static uint16_t adc_driver_class_t_read_instance_00( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 0]->__api )->read( _instance_list_adc_driver_class_t[ 0] ); }
static uint16_t adc_driver_class_t_read_instance_01( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 1]->__api )->read( _instance_list_adc_driver_class_t[ 1] ); }
static uint16_t adc_driver_class_t_read_instance_02( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 2]->__api )->read( _instance_list_adc_driver_class_t[ 2] ); }
static uint16_t adc_driver_class_t_read_instance_03( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 3]->__api )->read( _instance_list_adc_driver_class_t[ 3] ); }
static uint16_t adc_driver_class_t_read_instance_04( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 4]->__api )->read( _instance_list_adc_driver_class_t[ 4] ); }
static uint16_t adc_driver_class_t_read_instance_05( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 5]->__api )->read( _instance_list_adc_driver_class_t[ 5] ); }
static uint16_t adc_driver_class_t_read_instance_06( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 6]->__api )->read( _instance_list_adc_driver_class_t[ 6] ); }
static uint16_t adc_driver_class_t_read_instance_07( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 7]->__api )->read( _instance_list_adc_driver_class_t[ 7] ); }
static uint16_t adc_driver_class_t_read_instance_08( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 8]->__api )->read( _instance_list_adc_driver_class_t[ 8] ); }
static uint16_t adc_driver_class_t_read_instance_09( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[ 9]->__api )->read( _instance_list_adc_driver_class_t[ 9] ); }
static uint16_t adc_driver_class_t_read_instance_10( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[10]->__api )->read( _instance_list_adc_driver_class_t[10] ); }
static uint16_t adc_driver_class_t_read_instance_11( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[11]->__api )->read( _instance_list_adc_driver_class_t[11] ); }
static uint16_t adc_driver_class_t_read_instance_12( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[12]->__api )->read( _instance_list_adc_driver_class_t[12] ); }
static uint16_t adc_driver_class_t_read_instance_13( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[13]->__api )->read( _instance_list_adc_driver_class_t[13] ); }
static uint16_t adc_driver_class_t_read_instance_14( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[14]->__api )->read( _instance_list_adc_driver_class_t[14] ); }
static uint16_t adc_driver_class_t_read_instance_15( void ){ return ( ( api_adc_driver_class_t * )_instance_list_adc_driver_class_t[15]->__api )->read( _instance_list_adc_driver_class_t[15] ); }

static const adc_driver_class_t_read_t _adc_driver_class_t_read_list[16] =
{
    adc_driver_class_t_read_instance_00,
    adc_driver_class_t_read_instance_01,
    adc_driver_class_t_read_instance_02,
    adc_driver_class_t_read_instance_03,
    adc_driver_class_t_read_instance_04,
    adc_driver_class_t_read_instance_05,
    adc_driver_class_t_read_instance_06,
    adc_driver_class_t_read_instance_07,
    adc_driver_class_t_read_instance_08,
    adc_driver_class_t_read_instance_09,
    adc_driver_class_t_read_instance_10,
    adc_driver_class_t_read_instance_11,
    adc_driver_class_t_read_instance_12,
    adc_driver_class_t_read_instance_13,
    adc_driver_class_t_read_instance_14,
    adc_driver_class_t_read_instance_15,
};

void * _instance_new_adc_driver_class_t_ex( void * __api, uint8_t index )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_adc_driver_class_t, sizeof(adc_driver_class_t), 16 );
    if( _instance_index == -1 ) return NULL;
    adc_driver_class_t * ret = _instance_list_adc_driver_class_t[_instance_index];
    ret->__api = __api;
    ret->start = _adc_driver_class_t_start_list[_instance_index];
    ret->is_ready = _adc_driver_class_t_is_ready_list[_instance_index];
    ret->read = _adc_driver_class_t_read_list[_instance_index];
    api_adc_driver_class_t_class->init( ret, index );
    return ret;
}

void * _instance_new_adc_driver_class_t( uint8_t index )
{
    return _instance_new_adc_driver_class_t_ex( api_adc_driver_class_t_class, index );
}

void * _instance_static_adc_driver_class_t_method( void * __api )
{
    return api_adc_driver_class_t_class;
}

#if 0 // method definition for adc_driver_class_t

#include "adc_driver_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void init( adc_driver_class_t * p_data, uint8_t index )
{
}

METHOD static void start( adc_driver_class_t * p_data )
{
}

METHOD static bool_t is_ready( adc_driver_class_t * p_data )
{
}

METHOD static uint16_t read( adc_driver_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( adc_driver_class_t );

////////////////////////////////////////////////////////////////////

#endif // adc_driver_class_t

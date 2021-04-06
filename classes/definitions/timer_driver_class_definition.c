#include "timer_driver_class_private.h"
#include "timer_driver_class.h"

////////////////////////////////////////////////////////////////////

api_timer_driver_class_t * api_timer_driver_class_t_class = NULL;

static timer_driver_class_t * _instance_list_timer_driver_class_t[1] = {0};

typedef uint32_t ( *timer_driver_class_t_get_ms_t )( void );

static uint32_t timer_driver_class_t_get_ms_instance_00( void ){ return ( ( api_timer_driver_class_t * )_instance_list_timer_driver_class_t[ 0]->__api )->get_ms( _instance_list_timer_driver_class_t[ 0] ); }

static const timer_driver_class_t_get_ms_t _timer_driver_class_t_get_ms_list[1] =
{
    timer_driver_class_t_get_ms_instance_00,
};

typedef uint64_t ( *timer_driver_class_t_get_us_t )( void );

static uint64_t timer_driver_class_t_get_us_instance_00( void ){ return ( ( api_timer_driver_class_t * )_instance_list_timer_driver_class_t[ 0]->__api )->get_us( _instance_list_timer_driver_class_t[ 0] ); }

static const timer_driver_class_t_get_us_t _timer_driver_class_t_get_us_list[1] =
{
    timer_driver_class_t_get_us_instance_00,
};

void * _instance_new_timer_driver_class_t_ex( void * __api )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_timer_driver_class_t, sizeof(timer_driver_class_t), 1 );
    if( _instance_index == -1 ) return NULL;
    timer_driver_class_t * ret = _instance_list_timer_driver_class_t[_instance_index];
    ret->__api = __api;
    ret->get_ms = _timer_driver_class_t_get_ms_list[_instance_index];
    ret->get_us = _timer_driver_class_t_get_us_list[_instance_index];
    api_timer_driver_class_t_class->creator( ret );
    return ret;
}

void * _instance_new_timer_driver_class_t( void )
{
    return _instance_new_timer_driver_class_t_ex( api_timer_driver_class_t_class );
}

void * _instance_static_timer_driver_class_t_method( void * __api )
{
    return api_timer_driver_class_t_class;
}

#if 0 // method definition for timer_driver_class_t

#include "timer_driver_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( timer_driver_class_t * p_data )
{
}

METHOD static uint32_t get_ms( timer_driver_class_t * p_data )
{
}

METHOD static uint64_t get_us( timer_driver_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( timer_driver_class_t );

////////////////////////////////////////////////////////////////////

#endif // timer_driver_class_t

#include "hardware_class_private.h"
#include "hardware_class.h"

////////////////////////////////////////////////////////////////////

api_hardware_class_t * api_hardware_class_t_class = NULL;

static hardware_class_t * _instance_list_hardware_class_t[1] = {0};

typedef timer_driver_class_t * ( *hardware_class_t_get_timer_driver_t )( void );

static timer_driver_class_t * hardware_class_t_get_timer_driver_instance_00( void ){ return ( ( api_hardware_class_t * )_instance_list_hardware_class_t[ 0]->__api )->get_timer_driver( _instance_list_hardware_class_t[ 0] ); }

static const hardware_class_t_get_timer_driver_t _hardware_class_t_get_timer_driver_list[1] =
{
    hardware_class_t_get_timer_driver_instance_00,
};

typedef adc_driver_class_t * ( *hardware_class_t_get_adc_driver_t )( uint8_t index );

static adc_driver_class_t * hardware_class_t_get_adc_driver_instance_00( uint8_t index ){ return ( ( api_hardware_class_t * )_instance_list_hardware_class_t[ 0]->__api )->get_adc_driver( _instance_list_hardware_class_t[ 0], index ); }

static const hardware_class_t_get_adc_driver_t _hardware_class_t_get_adc_driver_list[1] =
{
    hardware_class_t_get_adc_driver_instance_00,
};

typedef lcd_driver_class_t * ( *hardware_class_t_get_lcd_driver_t )( void );

static lcd_driver_class_t * hardware_class_t_get_lcd_driver_instance_00( void ){ return ( ( api_hardware_class_t * )_instance_list_hardware_class_t[ 0]->__api )->get_lcd_driver( _instance_list_hardware_class_t[ 0] ); }

static const hardware_class_t_get_lcd_driver_t _hardware_class_t_get_lcd_driver_list[1] =
{
    hardware_class_t_get_lcd_driver_instance_00,
};

void * _instance_new_hardware_class_t_ex( void * __api )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_hardware_class_t, sizeof(hardware_class_t), 1 );
    if( _instance_index == -1 ) return NULL;
    hardware_class_t * ret = _instance_list_hardware_class_t[_instance_index];
    ret->__api = __api;
    ret->get_timer_driver = _hardware_class_t_get_timer_driver_list[_instance_index];
    ret->get_adc_driver = _hardware_class_t_get_adc_driver_list[_instance_index];
    ret->get_lcd_driver = _hardware_class_t_get_lcd_driver_list[_instance_index];
    api_hardware_class_t_class->creator( ret );
    ret->get_class = ( ( api_hardware_class_t * )__api )->get_class;
    ret->init = ( ( api_hardware_class_t * )__api )->init;
    return ret;
}

void * _instance_new_hardware_class_t( void )
{
    return _instance_new_hardware_class_t_ex( api_hardware_class_t_class );
}

void * _instance_static_hardware_class_t_method( void * __api )
{
    return api_hardware_class_t_class;
}

#if 0 // method definition for hardware_class_t

#include "hardware_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( hardware_class_t * p_data )
{
}

METHOD static timer_driver_class_t * get_timer_driver( hardware_class_t * p_data )
{
}

METHOD static adc_driver_class_t * get_adc_driver( hardware_class_t * p_data, uint8_t index )
{
}

METHOD static lcd_driver_class_t * get_lcd_driver( hardware_class_t * p_data )
{
}

STATIC static CLASS(hardware_class_t) * get_class( void )
{
}

STATIC static void init( void )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( hardware_class_t );

////////////////////////////////////////////////////////////////////

#endif // hardware_class_t

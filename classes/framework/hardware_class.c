#include "hardware_class_private.h"

////////////////////////////////////////////////////////////////////

typedef struct hardware_data_t_
{
    timer_driver_class_t * timer_driver_class;
    adc_driver_class_t * adc_driver_class[16];
    lcd_driver_class_t * lcd_driver_class;
    
} hardware_data_t;

////////////////////////////////////////////////////////////////////

static hardware_class_t * singleton = NULL;

////////////////////////////////////////////////////////////////////

CREATOR static void creator( hardware_class_t * p_data )
{
    hardware_data_t * hardware_data = ( hardware_data_t * )MMALLOC( sizeof( hardware_data_t ) );
    if( hardware_data != NULL )
    {
        p_data->p_data = hardware_data;
        
        hardware_data->lcd_driver_class = NEW_CLASS( lcd_driver_class_t )();
        hardware_data->timer_driver_class = NEW_CLASS( timer_driver_class_t )();
    }
}

METHOD static timer_driver_class_t * get_timer_driver( hardware_class_t * p_data )
{
    hardware_data_t * hardware_data = ( hardware_data_t * )p_data->p_data;
    return hardware_data->timer_driver_class;
}

METHOD static adc_driver_class_t * get_adc_driver( hardware_class_t * p_data, uint8_t index )
{
    hardware_data_t * hardware_data = ( hardware_data_t * )p_data->p_data;
    if( hardware_data->adc_driver_class[index] == NULL ) hardware_data->adc_driver_class[index] = NEW_CLASS( adc_driver_class_t )( index );
    return hardware_data->adc_driver_class[ index ];
}

METHOD static lcd_driver_class_t * get_lcd_driver( hardware_class_t * p_data )
{
    hardware_data_t * hardware_data = ( hardware_data_t * )p_data->p_data;
    return hardware_data->lcd_driver_class;
}

STATIC static CLASS(hardware_class_t) * get_class( void )
{
    if( singleton == NULL )
    {
        singleton = NEW_CLASS( hardware_class_t )();
    }
    
    return singleton;
}

STATIC static void init( void )
{
    if( singleton == NULL )
    {
        singleton = NEW_CLASS( hardware_class_t )();
    }
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( hardware_class_t );

////////////////////////////////////////////////////////////////////

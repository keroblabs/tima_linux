#include "lcd_driver_class_private.h"
#include "lcd_driver_class.h"

////////////////////////////////////////////////////////////////////

api_lcd_driver_class_t * api_lcd_driver_class_t_class = NULL;

static lcd_driver_class_t * _instance_list_lcd_driver_class_t[1] = {0};

typedef uint16_t ( *lcd_driver_class_t_get_width_t )( void );

static uint16_t lcd_driver_class_t_get_width_instance_00( void ){ return ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->get_width( _instance_list_lcd_driver_class_t[ 0] ); }

static const lcd_driver_class_t_get_width_t _lcd_driver_class_t_get_width_list[1] =
{
    lcd_driver_class_t_get_width_instance_00,
};

typedef uint16_t ( *lcd_driver_class_t_get_height_t )( void );

static uint16_t lcd_driver_class_t_get_height_instance_00( void ){ return ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->get_height( _instance_list_lcd_driver_class_t[ 0] ); }

static const lcd_driver_class_t_get_height_t _lcd_driver_class_t_get_height_list[1] =
{
    lcd_driver_class_t_get_height_instance_00,
};

typedef uint32_t ( *lcd_driver_class_t_get_pixel_t )( uint16_t posx, uint16_t posy );

static uint32_t lcd_driver_class_t_get_pixel_instance_00( uint16_t posx, uint16_t posy ){ return ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->get_pixel( _instance_list_lcd_driver_class_t[ 0], posx, posy ); }

static const lcd_driver_class_t_get_pixel_t _lcd_driver_class_t_get_pixel_list[1] =
{
    lcd_driver_class_t_get_pixel_instance_00,
};

typedef void ( *lcd_driver_class_t_set_pixel_t )( uint16_t posx, uint16_t posy, uint32_t pixel );

static void lcd_driver_class_t_set_pixel_instance_00( uint16_t posx, uint16_t posy, uint32_t pixel ){ ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->set_pixel( _instance_list_lcd_driver_class_t[ 0], posx, posy, pixel ); }

static const lcd_driver_class_t_set_pixel_t _lcd_driver_class_t_set_pixel_list[1] =
{
    lcd_driver_class_t_set_pixel_instance_00,
};

typedef void * ( *lcd_driver_class_t_get_buffer_t )( void );

static void * lcd_driver_class_t_get_buffer_instance_00( void ){ return ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->get_buffer( _instance_list_lcd_driver_class_t[ 0] ); }

static const lcd_driver_class_t_get_buffer_t _lcd_driver_class_t_get_buffer_list[1] =
{
    lcd_driver_class_t_get_buffer_instance_00,
};

typedef void ( *lcd_driver_class_t_release_t )( void );

static void lcd_driver_class_t_release_instance_00( void ){ ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->release( _instance_list_lcd_driver_class_t[ 0] ); }

static const lcd_driver_class_t_release_t _lcd_driver_class_t_release_list[1] =
{
    lcd_driver_class_t_release_instance_00,
};

typedef void ( *lcd_driver_class_t_process_t )( void );

static void lcd_driver_class_t_process_instance_00( void ){ ( ( api_lcd_driver_class_t * )_instance_list_lcd_driver_class_t[ 0]->__api )->process( _instance_list_lcd_driver_class_t[ 0] ); }

static const lcd_driver_class_t_process_t _lcd_driver_class_t_process_list[1] =
{
    lcd_driver_class_t_process_instance_00,
};

void * _instance_new_lcd_driver_class_t_ex( void * __api )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_lcd_driver_class_t, sizeof(lcd_driver_class_t), 1 );
    if( _instance_index == -1 ) return NULL;
    lcd_driver_class_t * ret = _instance_list_lcd_driver_class_t[_instance_index];
    ret->__api = __api;
    ret->get_width = _lcd_driver_class_t_get_width_list[_instance_index];
    ret->get_height = _lcd_driver_class_t_get_height_list[_instance_index];
    ret->get_pixel = _lcd_driver_class_t_get_pixel_list[_instance_index];
    ret->set_pixel = _lcd_driver_class_t_set_pixel_list[_instance_index];
    ret->get_buffer = _lcd_driver_class_t_get_buffer_list[_instance_index];
    ret->release = _lcd_driver_class_t_release_list[_instance_index];
    ret->process = _lcd_driver_class_t_process_list[_instance_index];
    api_lcd_driver_class_t_class->creator( ret );
    return ret;
}

void * _instance_new_lcd_driver_class_t( void )
{
    return _instance_new_lcd_driver_class_t_ex( api_lcd_driver_class_t_class );
}

void * _instance_static_lcd_driver_class_t_method( void * __api )
{
    return api_lcd_driver_class_t_class;
}

#if 0 // method definition for lcd_driver_class_t

#include "lcd_driver_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( lcd_driver_class_t * p_data )
{
}

METHOD static uint16_t get_width( lcd_driver_class_t * p_data )
{
}

METHOD static uint16_t get_height( lcd_driver_class_t * p_data )
{
}

METHOD static uint32_t get_pixel( lcd_driver_class_t * p_data, uint16_t posx, uint16_t posy )
{
}

METHOD static void set_pixel( lcd_driver_class_t * p_data, uint16_t posx, uint16_t posy, uint32_t pixel )
{
}

METHOD static void * get_buffer( lcd_driver_class_t * p_data )
{
}

METHOD static void release( lcd_driver_class_t * p_data )
{
}

METHOD static void process( lcd_driver_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( lcd_driver_class_t );

////////////////////////////////////////////////////////////////////

#endif // lcd_driver_class_t

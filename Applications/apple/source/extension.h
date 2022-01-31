#ifndef extension_h
#define extension_h

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "graphics.h"

//////////////////////////////////////////////////////////////////////////////////////

typedef void ( *event_t )( void * data );

typedef struct _button_data_t
{
    uint16_t posx;
    uint16_t posy;
    uint16_t width;
    uint16_t height;
    
    uint32_t id_button;
    
} button_data_t;

typedef struct _form_data_t
{
    button_data_t * button_data;
    button_data_t ** curr_id;
    event_t on_click;
    event_t on_down;
    event_t on_up;
    event_t on_display;
    
} form_data_t;

//////////////////////////////////////////////////////////////////////////////////////

void graphics_button_show( bitmap_t * lcd, button_data_t * button, char * caption, pixel_t colour0, pixel_t colour1 );
void graphics_button_handler( form_data_t * form, uint16_t posx, uint16_t posy, uint16_t posz );
void graphics_button_update( form_data_t * form );

//////////////////////////////////////////////////////////////////////////////////////

#endif /* extension_h */

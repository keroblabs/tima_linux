//
//  extension.c
//  instruments_simulator
//
//  Created by Marcio Cherobim on 02/06/2017.
//  Copyright © 2017 Marcio Cherobim. All rights reserved.
//

#include "extension.h"
#include "graphics.h"
#include "draw.h"
#include "board.h"

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

void graphics_button_show( bitmap_t * lcd, button_data_t * button, char * caption, pixel_t colour0, pixel_t colour1 )
{
    uint16_t text_width;
    uint16_t text_height;
    uint16_t text_posx;
    uint16_t text_posy;
    
    text_width = draw_get_text_width( caption );
    text_height = draw_get_text_height( caption );
    
    graphics_fill_box( lcd, button->posx, button->posy, button->width, button->height, colour1 );
    
    if( ( text_width < button->width ) && ( text_height < button->height ) )
    {
        text_posx = ( ( button->width - text_width ) >> 1 ) + button->posx;
        text_posy = ( ( button->height - text_height ) >> 1 ) + button->posy;
        
        draw_font_init( FONT_8x8 );
        draw_text( lcd, text_posx, text_posy, caption, colour0, colour1 );
    }
}

void graphics_button_update( form_data_t * form )
{
    uint32_t counter;
    
    ( *form->curr_id ) = NULL;
    
    for( counter = 0; counter < 255; counter++ )
    {
        if( form->button_data[counter].id_button == NEG_U32 ) break;
        
        form->on_display( &form->button_data[counter] );
    }
}

void graphics_button_handler( form_data_t * form, uint16_t posx, uint16_t posy, uint16_t posz )
{
    uint32_t counter;
    bool_t clicked;
    void * prev_id;
    
    //( *form->state ) = FALSE;
    clicked = FALSE;
    
    for( counter = 0; counter < 255; counter++ )
    {
        if( form->button_data[counter].id_button == NEG_U32 ) break;
        
        if( ( posx >= form->button_data[counter].posx ) &&
           ( posx < ( form->button_data[counter].posx + form->button_data[counter].width ) ) &&
           ( posy >= form->button_data[counter].posy ) &&
           ( posy < ( form->button_data[counter].posy + form->button_data[counter].height ) ) )
        {
            if( ( posz > 0 ) && ( ( (*form->curr_id) == NULL ) ||
                                 ( (*form->curr_id)->id_button != form->button_data[counter].id_button ) ) )
            {
                *form->curr_id = &form->button_data[counter];
                form->on_down( *form->curr_id );
                form->on_display( *form->curr_id );
                clicked = TRUE;
            }
        }
        else if( ( *form->curr_id != NULL ) && ( clicked == FALSE ) )
        {
            form->on_up( *form->curr_id );
            form->on_click( *form->curr_id );
            prev_id = *form->curr_id;
            *form->curr_id = NULL;
            form->on_display( prev_id );
        }
    }
}


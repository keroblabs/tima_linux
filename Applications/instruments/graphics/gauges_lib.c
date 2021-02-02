#include "gauges_lib.h"
#include "tima_libc.h"
#include "draw.h"
#include "fill_flood.h"
#include "t_threads.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////////////////////////

static void gauge_thread( void * args )
{
    instruments_gauge_t * p_data = ( instruments_gauge_t * )args;
    uint32_t refresh_rate;
    uint64_t draw_time;
    void * lcd;
    int inc = p_data->max_inc;
    int diff;
    int curr_value = 0;
    int target;
    
    refresh_rate = p_data->initial_rate;
    
    p_data->max_drawtime = 0;
    
    while( 1 )
    {
        tthread_sleep_ms( refresh_rate );
        tthread_mutex_lock( p_data->mutex );
        target = p_data->target;
        curr_value = p_data->curr_value;
        tthread_mutex_unlock( p_data->mutex );
        
        diff = target - curr_value;
        
        if( ( diff > ( 0 - p_data->min_diff ) ) && ( diff < p_data->min_diff ) )
        {
            curr_value = target;
            diff = 0;
        }
        else
        {
            if( ( diff > ( 0 - p_data->base_diff ) ) && ( diff < p_data->base_diff ) ) inc = p_data->min_inc;
            else inc = p_data->max_inc;
            
            if( diff > 0 ) curr_value += inc;
            else curr_value -= inc;
        }
        
        tthread_mutex_lock( p_data->mutex );
        p_data->curr_value = curr_value;
        tthread_mutex_unlock( p_data->mutex );
        
        lcd = graphics_claim();
        //lcd = graphics_claim_pre_flip();
        
        draw_time = 0 - timer_get_microsecs();
        p_data->show_handler( lcd, p_data->data, curr_value );
        draw_time += timer_get_microsecs();
        
        graphics_release();
        
        if( draw_time > p_data->max_drawtime ) p_data->max_drawtime = draw_time;
        
        if( diff == 0 )
        {
            refresh_rate = p_data->run_rate;
            tthread_condition_wait( p_data->cond );
        }
    }
}

void gauge_thread_start( void * args )
{
    tthread_create_ex( gauge_thread, args );
}

void gauge_thread_force_value( instruments_gauge_t * gauge, int value )
{
    tthread_mutex_lock( gauge->mutex );
    gauge->saved_value = gauge->curr_value;
    gauge->curr_value = value;
    gauge->target = value;
    tthread_mutex_unlock( gauge->mutex );
    
    tthread_condition_signal( gauge->cond );
}

void gauge_thread_restore_value( instruments_gauge_t * gauge )
{
    tthread_mutex_lock( gauge->mutex );
    gauge->target = gauge->saved_value;
    tthread_mutex_unlock( gauge->mutex );
    
    tthread_condition_signal( gauge->cond );
}

void gauge_print( void * p_lcd, uint16_t posx, uint16_t posy, uint16_t ratio, pixel_t colour, pixel_t back_colour, char * info, int angle )
{
    uint16_t x1, y1;
    int shift_num;
    int offset;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    shift_num = 0;
    offset = 8;
    
    x1 = posx - ( ( cos_table( angle ) * (ratio) ) >> 15 );
    y1 = posy - ( ( sin_table( angle ) * (ratio) ) >> 15 );
    
    if( angle > 512 ) shift_num = 1;
    if( angle > 720 ) offset = 13;
    
    draw_text(lcd, x1-((strlen(info)*12)>>shift_num), y1-offset, info, colour, back_colour);
}

uint16_t gauge_show_digits( void * p_lcd, uint16_t posx, uint16_t posy, int ratio, pixel_t colour, pixel_t back_colour,
                            int start_angle, int end_angle, int angle_step, uint16_t start_num, uint16_t num_step )
{
    uint16_t x1, y1;
    int i;
    uint16_t curr_num;
    char num_str[5];
    int shift_num;
    int offset;
    int offsetx;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;

    curr_num = start_num;
    shift_num = 0;
    offset = 8;
    offsetx = 0;
    
    for( i = start_angle; i < end_angle; i += angle_step )
    {
        x1 = posx - ( uint16_t )( ( cos_table( i ) * (ratio) ) >> 15 );
        y1 = posy - ( uint16_t )( ( sin_table( i ) * (ratio) ) >> 15 );
        
        offsetx = 0;
        
        if( i > 512 ) shift_num = 1;
        if( i > 720 ) offset = 13;
        if( ( ( i < ( 32-1024 ) ) && ( i > ( 0-32-1024 ) ) ) || ( ( i > ( 1024-32 ) ) && ( i < ( 1024+32 ) ) ) ) offsetx = 5;
        
        sprintf( num_str, "%d", curr_num );
        curr_num += num_step;
        
        draw_text(lcd, x1-((strlen(num_str)*12)>>shift_num)+offsetx, y1-offset, num_str, colour, back_colour);
    }
    
    return curr_num;
}

void gauge_show_marks( void * p_lcd, uint16_t posx, uint16_t posy, int curr_angle, gauge_data_t * data )
{
    int x1, y1, x2, y2;
    int i;
    int cnt;
    int incr;
    pixel_t draw_colour;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;

    incr = ( ( data->end_angle - data->start_angle ) / data->angle_step ) / ( data->marks - 1 );
    
    if( data->angle_step >= 0 )
    {
        for( i = data->start_angle, cnt = 0; i < data->end_angle; i += data->angle_step, cnt++ )
        {
            x1 = posx - ( ( cos_table( i ) * data->ratio ) >> 15 );
            y1 = posy - ( ( sin_table( i ) * data->ratio ) >> 15 );
            
            if( ( cnt == incr ) || ( cnt == 0 ) )
            {
                cnt = 0;
                x2 = posx - ( ( cos_table( i ) * (data->ratio-data->len2) ) >> 15 );
                y2 = posy - ( ( sin_table( i ) * (data->ratio-data->len2) ) >> 15 );
            }
            else
            {
                x2 = posx - ( ( cos_table( i ) * (data->ratio-data->len1) ) >> 15 );
                y2 = posy - ( ( sin_table( i ) * (data->ratio-data->len1) ) >> 15 );
            }
            
            if( i < data->angle1 ) draw_colour = data->colour1;
            else draw_colour = data->colour2;
            
            if( i > curr_angle ) draw_colour = data->colour3;
            
            draw_line(lcd,  (uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, draw_colour );
        }
    }
    else
    {
        for( i = data->start_angle, cnt = 0; i > data->end_angle; i += data->angle_step, cnt++ )
        {
            x1 = posx - ( ( cos_table( i ) * data->ratio ) >> 15 );
            y1 = posy - ( ( sin_table( i ) * data->ratio ) >> 15 );
            
            if( ( cnt == incr ) || ( cnt == 0 ) )
            {
                cnt = 0;
                x2 = posx - ( ( cos_table( i ) * (data->ratio-data->len2) ) >> 15 );
                y2 = posy - ( ( sin_table( i ) * (data->ratio-data->len2) ) >> 15 );
            }
            else
            {
                x2 = posx - ( ( cos_table( i ) * (data->ratio-data->len1) ) >> 15 );
                y2 = posy - ( ( sin_table( i ) * (data->ratio-data->len1) ) >> 15 );
            }
            
            if( i > data->angle1 ) draw_colour = data->colour1;
            else draw_colour = data->colour2;
            
            if( i < curr_angle ) draw_colour = data->colour3;
            
            draw_line(lcd,  (uint16_t)x1, (uint16_t)y1, (uint16_t)x2, (uint16_t)y2, draw_colour );
        }
    }
}

void gauge_draw_niddle( void * p_lcd, niddle_data_t * data, int rad )
{
    uint16_t posx_end, posy_end;
    uint16_t posx_end_left, posy_end_left;
    uint16_t posx_end_right, posy_end_right;
    
    uint16_t posx_start, posy_start;
    uint16_t posx_start_left, posy_start_left;
    uint16_t posx_start_right, posy_start_right;
    
    uint16_t posx_flood, posy_flood;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    graphics_restore_backup( lcd, data->niddle_backup );

    if( data->draw_circle )
    {
        draw_circle( lcd, data->posx, data->posy, data->circle_ratio, data->circle_colour, data->niddle_backup );
    }
    
    posx_start = data->posx - ( ( cos_table( rad ) * ( data->circle_ratio ) ) >> 15 );
    posy_start = data->posy - ( ( sin_table( rad ) * ( data->circle_ratio ) ) >> 15 );
    
    posx_start_left = posx_start - ( ( cos_table( rad + 1024 ) * data->niddle_width ) >> 15 );
    posy_start_left = posy_start - ( ( sin_table( rad + 1024 ) * data->niddle_width ) >> 15 );
    
    posx_start_right = posx_start - ( ( cos_table( rad - 1024 ) * data->niddle_width ) >> 15 );
    posy_start_right = posy_start - ( ( sin_table( rad - 1024 ) * data->niddle_width ) >> 15 );
    
    posx_end = data->posx - ( ( cos_table( rad ) * data->niddle_len ) >> 15 );
    posy_end = data->posy - ( ( sin_table( rad ) * data->niddle_len ) >> 15 );
    
    posx_end_left = posx_end - ( ( cos_table( rad + 1024 ) * (data->niddle_width_edge) ) >> 15 );
    posy_end_left = posy_end - ( ( sin_table( rad + 1024 ) * (data->niddle_width_edge) ) >> 15 );
    
    posx_end_right = posx_end - ( ( cos_table( rad - 1024 ) * (data->niddle_width_edge) ) >> 15 );
    posy_end_right = posy_end - ( ( sin_table( rad - 1024 ) * (data->niddle_width_edge) ) >> 15 );
    
    posx_flood = data->posx - ( ( cos_table( rad ) * ( data->niddle_len/3 ) ) >> 15 );
    posy_flood = data->posy - ( ( sin_table( rad ) * ( data->niddle_len/3 ) ) >> 15 );
    
    // comments below refer to looking at the niddle at vertical position
    // bottom
    if( data->end_niddle )
    {
        draw_line_backup( lcd, posx_start_left, posy_start_left, posx_start_right, posy_start_right, data->niddle_colour, data->niddle_backup );
    }
    
    // right line
    draw_line_backup( lcd, posx_start_left, posy_start_left, posx_end_left, posy_end_left, data->niddle_colour, data->niddle_backup );
    
    // left line
    draw_line_backup( lcd, posx_start_right, posy_start_right, posx_end_right, posy_end_right, data->niddle_colour, data->niddle_backup );
    
    // top line
    draw_line_backup( lcd, posx_end_left, posy_end_left, posx_end_right, posy_end_right, data->niddle_colour, data->niddle_backup );
    
    // niddle
    if( ( data->niddle_width > 1 ) || ( data->niddle_width_edge > 1 ) )
    {
        graphics_flood_fill_area( lcd, posx_flood, posy_flood, data->niddle_colour, data->niddle_backup );
    }
    
    data->prev_rad = rad;
}


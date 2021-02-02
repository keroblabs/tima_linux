#ifndef gauges_lib_h
#define gauges_lib_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "graphics.h"

////////////////////////////////////////////////////////////////////////////////////////

#define LCD_REFRESH_RATE_MS         22
#define FUEL_REFRESH_RATE_MS        20
#define TEMP_REFRESH_RATE_MS        25
#define SPEED_REFRESH_RATE_MS       150

////////////////////////////////////////////////////////////////////////////////////////

typedef struct _mark_data_t_
{
    int start_angle;
    int end_angle;
    int angle_step;
    int angle1;
    
    int ratio;
    int len1;
    int len2;
    
    uint16_t marks;
    
    pixel_t colour1;
    pixel_t colour2;
    pixel_t colour3;
    
} gauge_data_t;

typedef struct _draw_niddle_data_t
{
    uint16_t posx;
    uint16_t posy;
    
    int prev_rad;
    
    uint16_t circle_ratio;
    
    bool_t draw_circle;
    bool_t end_niddle;
    
    uint16_t niddle_len;
    uint16_t niddle_width;
    uint16_t niddle_width_edge;

    pixel_t circle_colour;
    pixel_t niddle_colour;
    pixel_t edge_colour;
    
    graphics_backup_t * niddle_backup;
    
} niddle_data_t;

typedef struct _instruments_gauge_t
{
    int target;
    int curr_value;
    int saved_value;
    
    void * cond;
    void * mutex;
    void * thread;
    void * data;
    
    uint32_t initial_rate;
    uint32_t run_rate;
    
    int min_diff;
    int base_diff;
    int min_inc;
    int max_inc;
    
    uint16_t posx;
    uint16_t posy;
    
    uint64_t max_drawtime;
    
    niddle_data_t   niddle_data;
    
    void ( *show_handler )( void * lcd, void * data, int value );
    
} instruments_gauge_t;

////////////////////////////////////////////////////////////////////////////////////////

void gauge_thread_start( void * args );
void gauge_thread_force_value( instruments_gauge_t * gauge, int value );
void gauge_thread_restore_value( instruments_gauge_t * gauge );

void gauge_show_marks( void * p_lcd, uint16_t posx, uint16_t posy, int curr_angle, gauge_data_t * data );

uint16_t gauge_show_digits( void * p_lcd, uint16_t posx, uint16_t posy, int ratio, pixel_t colour, pixel_t back_colour,
                           int start_angle, int end_angle, int angle_step, uint16_t start_num, uint16_t num_step );

// void gauge_erase_niddle( void * p_lcd, niddle_data_t * data );
void gauge_draw_niddle( void * p_lcd, niddle_data_t * data, int rad );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* gauges_lib_h */

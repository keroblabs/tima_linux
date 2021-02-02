#include "fill_flood.h"
#include "t_threads.h"
//#include "hardware.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

typedef struct _flood_data_t
{
    graphics_backup_t * backup;
    pixel_t colour;
    bitmap_t * curr_driver;
    
} flood_data_t;

////////////////////////////////////////////////////////////////////

static void _fill_right( uint32_t index, flood_data_t * data )
{
    if(data->curr_driver->buffer[index] != data->colour)
    {
        graphics_set_pixel_index_backup( data->curr_driver, data->backup, index, data->colour );
        
        _fill_right( index+1, data );
        _fill_right( index-data->curr_driver->width, data );
        _fill_right( index+data->curr_driver->width, data );
    }
}

static void _fill_left( uint32_t index, flood_data_t * data )
{
    if(data->curr_driver->buffer[index] != data->colour)
    {
        graphics_set_pixel_index_backup( data->curr_driver, data->backup, index, data->colour );
        
        _fill_left( index-1, data );
        _fill_left( index-data->curr_driver->width, data );
        _fill_left( index+data->curr_driver->width, data );
    }
}

void graphics_flood_fill_area( bitmap_t * curr_driver, uint16_t x, uint16_t y, pixel_t colour, graphics_backup_t * backup )
{
    uint32_t index = ( y * curr_driver->width ) + x;
    flood_data_t data;
    
    data.colour = colour;
    data.backup = backup;
    data.curr_driver = curr_driver;
    
    _fill_right(index, &data);
    _fill_left(index-1, &data);
}

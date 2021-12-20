#include "yuv_to_rgb.h"

////////////////////////////////////////////////////////////////////

typedef struct yuv_pixel_t_
{
    uint8_t y0;
    uint8_t u;
    uint8_t y1;
    uint8_t v;

} yuv_pixel;

typedef struct pixel_4_t_
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;

} pixel_4_t;

typedef union pixel_data_t_
{
    pixel_4_t split;
    pixel_t   value;

} pixel_data_t;

////////////////////////////////////////////////////////////////////

#define GET_TABLE_POS(x,y)      ((y>>1)*128 + (x>>1))
#define CLAMP_VALUE(v,min,max)  (( v > max ) ? max : (( v < min ) ? min : v ))

////////////////////////////////////////////////////////////////////

static uint8_t yv_to_r[64*1024];
static int8_t uv_to_g1[64*1024];
static uint8_t g1_to_g2[64*1024];
static uint8_t yu_to_b[64*1024];

////////////////////////////////////////////////////////////////////

void yuv_to_rgb_init( void )
{
    int table_x, table_y;
    int temp_value1;
    int temp_value2;
    int index_temp;

    for( table_y = 0; table_y < 256; table_y++ )
    {
        index_temp = 256 * table_y;

        for( table_x = 0; table_x < 256; table_x++ )
        {
            temp_value1 = table_y + ( ( ( table_x - 128 ) * 359 ) >> 8 );
            yv_to_r[index_temp+table_x] = ( uint8_t )CLAMP_VALUE( temp_value1, 0, 255 );

            temp_value1 = ( ( ( table_x - 128 ) * 88 ) >> 8 ) + ( ( ( table_y - 128 ) * 183 ) >> 8 );
            uv_to_g1[index_temp+table_x] = ( int8_t )CLAMP_VALUE( temp_value1, -126, 126 );

            temp_value1 = table_y - ( table_x - 127 );
            g1_to_g2[index_temp+table_x] = ( int8_t )CLAMP_VALUE( temp_value1, 0, 255 );

            temp_value1 = table_y + ( ( ( table_x - 128 ) * 453 ) >> 8 );
            yu_to_b[index_temp+table_x] = ( uint8_t )CLAMP_VALUE( temp_value1, 0, 255 );
        }
    }
}

static inline pixel_t get_pixel( pixel_data_t * frame_buffer, uint32_t y, uint8_t u, uint8_t v, int8_t pre_g )
{
    pixel_t ret;

    if( ( frame_buffer == NULL ) || ( ( frame_buffer->split.red < 32 ) && ( frame_buffer->split.green < 32 ) && ( frame_buffer->split.blue < 32 ) ) )
    {
        uint32_t offset = y * 256;

        uint8_t r = yv_to_r[offset+v];
        uint8_t g = g1_to_g2[offset+pre_g];
        uint8_t b = yu_to_b[offset+u];
        ret = APP_RGB(r, g, b);
    }
    else
    {
        ret = frame_buffer->value;
    }

    return ret;
}

void yuv_to_rgb_display( const void * input, bitmap_t * frame, bitmap_t * output, uint16_t width, uint16_t height, uint16_t posx, uint16_t posy )
{
    uint16_t count_x;
    uint16_t count_y;
    uint32_t index;
    uint32_t index_frame;

    yuv_pixel * yuv_buffer = ( yuv_pixel * )input;
    pixel_data_t * frame_buffer = ( pixel_data_t * )frame;
    pixel_t   * rgb_buffer;
    uint8_t     r, g, b;
    int8_t      pre_g;

    index = ( output->width * posy ) + posx;
    index_frame = 0;

    for( count_y = 0; count_y < height; count_y++ )
    {
        rgb_buffer = &output->buffer[index];

        for( count_x = 0; count_x < width; count_x += 2 )
        {
            pre_g = uv_to_g1[(yuv_buffer->v * 256) + yuv_buffer->u] + 127;
            uint8_t mid_y = ( yuv_buffer->y0 >> 1 ) + ( yuv_buffer->y1 >> 1 );

            *rgb_buffer = get_pixel( frame_buffer, yuv_buffer->y0, yuv_buffer->u, yuv_buffer->v, pre_g );
            if( frame != NULL ) frame_buffer++;
            rgb_buffer++;

            *rgb_buffer = get_pixel( frame_buffer, mid_y, yuv_buffer->u, yuv_buffer->v, pre_g );
            if( frame != NULL ) frame_buffer++;
            rgb_buffer++;

            *rgb_buffer = get_pixel( frame_buffer, yuv_buffer->y1, yuv_buffer->u, yuv_buffer->v, pre_g );
            if( frame != NULL ) frame_buffer++;
            rgb_buffer++;

            yuv_buffer++;
        }

        index += output->width;
    }

    graphics_release();
}

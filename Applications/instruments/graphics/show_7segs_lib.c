#include "show_7segs_lib.h"
#include "draw.h"
#include "bitmap.h"

///////////////////////////////////////////////////////////////////////////

#define SEG_A	(1<<0)
#define SEG_B	(1<<1)
#define SEG_C	(1<<2)
#define SEG_D	(1<<3)
#define SEG_E	(1<<4)
#define SEG_F	(1<<5)
#define SEG_G	(1<<6)

#define SEG_C1	(1<<7)
#define SEG_D1	(1<<8)

#define LARGE_DIGITS_BACKUP_MAX_LEN     10000

///////////////////////////////////////////////////////////////////////////

typedef struct _number_7seg_t_
{
    uint16_t width;
    uint16_t height;
    
    uint16_t vert_width;
    uint16_t vert_height;
    uint16_t horz_width;
    uint16_t horz_height;
    
    uint16_t dp_offsetx;
    uint16_t dp_offsety;
    
    const uint8_t * vert_7seg;
    const uint8_t * horz_7seg;
    
} number_7seg_t;

///////////////////////////////////////////////////////////////////////////

static const uint8_t vert_7seg_xbig[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xff,0xff,0xff,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static const uint8_t horz_7seg_xbig[] =
{
    0x00,0x0E,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
    0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
    0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0E,0x06,0x00,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};


static const uint8_t vert_7seg_big[] =
{
    0x00,0x00,0xe0,0xfe,0xff,0xff,0xff,0x1e,
    0xe0,0xfe,0xff,0xff,0xff,0x1f,0x01,0x00,
    0x01,0x03,0x03,0x03,0x01,0x00,0x00,0x00,
};

static const uint8_t horz_7seg_big[] =
{
    0x00, 0x0E, 0x1E, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x1E, 0x0e, 0x00
};

static const uint8_t vert_7seg[] =
{
    0xF0,
    0xf8,
    0x7f,
    0x0F,
};

static const uint8_t horz_7seg[] =
{
    0x06, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x06,
};

static const number_7seg_t data_7seg_big =
{
    34, 46,
    8, 18,
    14, 5,
    2, 36,
    
    vert_7seg_big,
    horz_7seg_big
};

static const number_7seg_t data_7seg_xbig =
{
    68, 117,
    19, 66,
    38, 12,
    2, 36,
    
    vert_7seg_xbig,
    horz_7seg_xbig
};

static const number_7seg_t data_7seg_small =
{
    20, 24,
    4, 8,
    11, 4,
    2, 20,
    
    vert_7seg,
    horz_7seg
};

static const uint16_t seg_list[] =
{
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
    SEG_C | SEG_D,
    SEG_E | SEG_F | SEG_G | SEG_C | SEG_B,
    SEG_E | SEG_F | SEG_G | SEG_C | SEG_D,
    SEG_C | SEG_D | SEG_A | SEG_F,
    SEG_E | SEG_F | SEG_G | SEG_A | SEG_D,
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_C | SEG_D | SEG_E,
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
};

///////////////////////////////////////////////////////////////////////////

#define SEG_A_POS		posx+(p_data->vert_width/2),						posy+(p_data->horz_height/2)
#define SEG_B_POS		posx,												posy+p_data->horz_height+p_data->vert_height
#define SEG_C_POS		posx+p_data->horz_width+p_data->vert_width,			posy+(p_data->horz_height/2)
#define SEG_D_POS		posx+p_data->horz_width+(p_data->vert_width/2),		posy+p_data->horz_height+p_data->vert_height

#define SEG_C1_POS		posx+(p_data->horz_width+p_data->vert_width)/2,		posy+(p_data->horz_height/2)
#define SEG_D1_POS		posx+(p_data->horz_width/2),						posy+p_data->horz_height+p_data->vert_height

#define SEG_E_POS		posx+(p_data->vert_width+(p_data->vert_width/2)),	posy
#define SEG_F_POS		posx+(p_data->vert_width),							posy+(p_data->horz_height/2)+p_data->vert_height
#define SEG_G_POS		posx+(p_data->vert_width/2),						posy+p_data->horz_height+(p_data->vert_height)*2

#define HORZ_SEGMENT	p_data->horz_width, p_data->horz_height, ( uint8_t * )p_data->horz_7seg
#define VERT_SEGMENT	p_data->vert_width, p_data->vert_height, ( uint8_t * )p_data->vert_7seg

///////////////////////////////////////////////////////////////////////////

uint16_t show_7seg_collect_backup( void * p_lcd, uint16_t posx, uint16_t posy, uint8_t num_digits, void * data, graphics_backup_t * backup )
{
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    int i;
    int j;
    uint32_t prev_size;

    number_7seg_t * p_data = ( number_7seg_t * )data;

    for( i = 0; i < (int)num_digits; i++ )
    {
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_A_POS, VERT_SEGMENT, backup ); // 600
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_B_POS, VERT_SEGMENT, backup );
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_C_POS, VERT_SEGMENT, backup );
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_D_POS, VERT_SEGMENT, backup );
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_E_POS, HORZ_SEGMENT, backup ); // 200
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_F_POS, HORZ_SEGMENT, backup );
        graphics_bitmap_1bb_ex_collect_backup( lcd, SEG_G_POS, HORZ_SEGMENT, backup );

        posx += p_data->width;
    }

    return posx;
}

uint16_t show_7seg_draw_digits( void * p_lcd, uint16_t posx, uint16_t posy, char * value, pixel_t colour, void * data, graphics_backup_t * backup )
{
    uint16_t curr_segs;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    int i;
    int j;

    number_7seg_t * p_data = ( number_7seg_t * )data;
    graphics_restore_backup( p_lcd, backup );

    for( i = 0; i < (int)strlen(value); i++ )
    {
        curr_segs = ( ( value[i] >= 0x30 ) && ( value[i] <= 0x39 ) ) ? seg_list[value[i] & 0x0F] : 0;

        if( curr_segs & SEG_A ) graphics_bitmap_1bb_ex( p_lcd, SEG_A_POS, VERT_SEGMENT, colour, backup ); // 600
        if( curr_segs & SEG_B ) graphics_bitmap_1bb_ex( p_lcd, SEG_B_POS, VERT_SEGMENT, colour, backup );
        if( curr_segs & SEG_C ) graphics_bitmap_1bb_ex( p_lcd, SEG_C_POS, VERT_SEGMENT, colour, backup );
        if( curr_segs & SEG_D ) graphics_bitmap_1bb_ex( p_lcd, SEG_D_POS, VERT_SEGMENT, colour, backup );
        if( curr_segs & SEG_E ) graphics_bitmap_1bb_ex( p_lcd, SEG_E_POS, HORZ_SEGMENT, colour, backup ); // 200
        if( curr_segs & SEG_F ) graphics_bitmap_1bb_ex( p_lcd, SEG_F_POS, HORZ_SEGMENT, colour, backup );
        if( curr_segs & SEG_G ) graphics_bitmap_1bb_ex( p_lcd, SEG_G_POS, HORZ_SEGMENT, colour, backup );

        if( ( i > 0 ) && ( value[i-1] == '.' ) )
        {
            for( j = 0; j < 5; j++ )
            {
                graphics_set_pixel( lcd, posx-6+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
                graphics_set_pixel( lcd, posx-5+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
                graphics_set_pixel( lcd, posx-4+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
            }
        }

        posx += p_data->width;
    }

    return posx;
}

uint16_t show_7seg_draw_digits_old( void * p_lcd, uint16_t posx, uint16_t posy, char * value, pixel_t colour, void * data, graphics_backup_t * backup )
{
    uint16_t curr_segs;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    int i;
    int j;
    graphics_backup_t * output;
    
    number_7seg_t * p_data = ( number_7seg_t * )data;
    output = graphics_backup_create( LARGE_DIGITS_BACKUP_MAX_LEN );

    for( i = 0; i < (int)strlen(value); i++ )
    {
        curr_segs = ( ( value[i] >= 0x30 ) && ( value[i] <= 0x39 ) ) ? seg_list[value[i] & 0x0F] : 0;
        
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_A ) ? FALSE : TRUE, VERT_SEGMENT,  colour, backup, output ); // 600
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_B ) ? FALSE : TRUE, VERT_SEGMENT,  colour, backup, output );
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_C ) ? FALSE : TRUE, VERT_SEGMENT,  colour, backup, output );
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_D ) ? FALSE : TRUE, VERT_SEGMENT,  colour, backup, output );
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_E ) ? FALSE : TRUE, HORZ_SEGMENT,  colour, backup, output ); // 200
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_F ) ? FALSE : TRUE, HORZ_SEGMENT,  colour, backup, output );
        graphics_bitmap_1bb_ex_backup_merge( ( curr_segs & SEG_G ) ? FALSE : TRUE, HORZ_SEGMENT,  colour, backup, output );
        
        if( ( i > 0 ) && ( value[i-1] == '.' ) )
        {
            for( j = 0; j < 5; j++ )
            {
                graphics_set_pixel( lcd, posx-6+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
                graphics_set_pixel( lcd, posx-5+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
                graphics_set_pixel( lcd, posx-4+p_data->dp_offsetx, posy+j+p_data->dp_offsety, colour );
            }
        }
        
        posx += p_data->width;
    }
    
    graphics_restore_backup( p_lcd, output );
    graphics_destroy_backup( output );
    return posx;
}

void show_7segs_small_digits( void * p_lcd, uint16_t posx, uint16_t posy, uint16_t value, char * str_unit, pixel_t colour, graphics_backup_t * backup )
{
    char str_angle[20];
    uint16_t new_posx;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;

    //graphics_fill_box( lcd, posx-5, posy-2, (data_7seg_small.width*3) + 10, data_7seg_small.height+5, back_colour );
    
    //if( value <= 9999 ) posx += 22;
    //if( value <= 999 ) posx += 22;
    if( value <= 99 ) posx += data_7seg_small.width;
    if( value <= 9 ) posx += data_7seg_small.width;
    
    sprintf( str_angle, "%d", value );
    new_posx = show_7seg_draw_digits( lcd, posx, posy, str_angle, colour, ( void * )&data_7seg_small, backup );
    draw_text_ex( lcd, new_posx+10, posy+4, str_unit, colour, backup );
}

void show_7segs_digits_create_data( digits_data_t * data, uint16_t posx, uint16_t posy, uint8_t num_digits, pixel_t colour )
{
    data->backup = graphics_backup_create( LARGE_DIGITS_BACKUP_MAX_LEN );
    data->posx = posx;
    data->posy = posy;
    data->colour = colour;
    data->num_digits = num_digits;
}

void show_7segs_large_digits_show( void * p_lcd, digits_data_t * data, uint16_t value )
{
    char str_angle[20];
    char str_ctrl[20];
    uint16_t new_posx;
    uint16_t posx = data->posx;
    uint16_t posy = data->posy;
    
    //if( value <= 9999 ) posx += 22;
    //if( value <= 999 ) posx += 22;
    //if( value <= 99 ) posx += data_7seg_xbig.width;
    //if( value <= 9 ) posx += data_7seg_xbig.width;
    
    sprintf( str_ctrl,  "%%%dd", data->num_digits );
    sprintf( str_angle, str_ctrl, value );
    new_posx = show_7seg_draw_digits( p_lcd, posx, data->posy, str_angle, data->colour, ( void * )&data_7seg_xbig, data->backup );
}

void show_7segs_large_digits_collect_backup( void * p_lcd, digits_data_t * data )
{
    show_7seg_collect_backup( p_lcd, data->posx, data->posy, data->num_digits, ( void * )&data_7seg_xbig, data->backup );
}

void show_7segs_small_digits_fraction( void * p_lcd, uint16_t posx, uint16_t posy, uint32_t value, uint32_t div, pixel_t colour, pixel_t back_colour )
{
    char str_angle[20];
    uint16_t new_posx;
    uint16_t xdec = 0;
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    if( div == 10 ) xdec += data_7seg_small.width;
    if( div == 100 ) xdec += data_7seg_small.width;
    if( div == 1000 ) xdec += data_7seg_small.width;
    
    graphics_fill_box( lcd, posx-5, posy-2, (data_7seg_small.width*8)+10+xdec, data_7seg_small.height+5, back_colour );
    
    if( value <= 999999 ) posx += data_7seg_small.width;
    if( value <= 99999 ) posx += data_7seg_small.width;
    if( value <= 9999 ) posx += data_7seg_small.width;
    if( value <= 999 ) posx += data_7seg_small.width;
    if( value <= 99 ) posx += data_7seg_small.width;
    if( ( value <= 9 ) && ( div == 1 ) ) posx += data_7seg_small.width;
    posx += data_7seg_small.width;
    
    if( div == 1 ) sprintf( str_angle, "%d", value );
    else if( div == 10 ) sprintf( str_angle, "%d.%d", value / div, value % div );
    else if( div == 100 ) sprintf( str_angle, "%d.%02d", value / div, value % div );
    else if( div == 1000 ) sprintf( str_angle, "%d.%03d", value / div, value % div );
    new_posx = show_7seg_draw_digits( lcd, posx, posy, str_angle, colour, FALSE, ( void * )&data_7seg_small );
}



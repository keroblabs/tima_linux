#include "bitmap_draw_class_private.h"
#include "bitmap_draw_class.h"

////////////////////////////////////////////////////////////////////

api_bitmap_draw_class_t * api_bitmap_draw_class_t_class = NULL;

static bitmap_draw_class_t * _instance_list_bitmap_draw_class_t[64] = {0};

typedef void ( *bitmap_draw_class_t_delete_bitmap_t )( void );

static void bitmap_draw_class_t_delete_bitmap_instance_00( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 0] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_01( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 1] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_02( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 2] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_03( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 3] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_04( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 4] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_05( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 5] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_06( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 6] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_07( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 7] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_08( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 8] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_09( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[ 9] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_10( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[10] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_11( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[11] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_12( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[12] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_13( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[13] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_14( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[14] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_15( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[15] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_16( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[16] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_17( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[17] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_18( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[18] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_19( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[19] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_20( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[20] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_21( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[21] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_22( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[22] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_23( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[23] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_24( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[24] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_25( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[25] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_26( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[26] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_27( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[27] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_28( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[28] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_29( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[29] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_30( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[30] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_31( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[31] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_32( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[32] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_33( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[33] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_34( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[34] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_35( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[35] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_36( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[36] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_37( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[37] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_38( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[38] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_39( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[39] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_40( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[40] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_41( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[41] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_42( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[42] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_43( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[43] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_44( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[44] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_45( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[45] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_46( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[46] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_47( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[47] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_48( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[48] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_49( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[49] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_50( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[50] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_51( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[51] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_52( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[52] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_53( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[53] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_54( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[54] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_55( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[55] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_56( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[56] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_57( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[57] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_58( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[58] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_59( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[59] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_60( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[60] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_61( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[61] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_62( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[62] ); }
static void bitmap_draw_class_t_delete_bitmap_instance_63( void ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->delete_bitmap( _instance_list_bitmap_draw_class_t[63] ); }

static const bitmap_draw_class_t_delete_bitmap_t _bitmap_draw_class_t_delete_bitmap_list[64] =
{
    bitmap_draw_class_t_delete_bitmap_instance_00,
    bitmap_draw_class_t_delete_bitmap_instance_01,
    bitmap_draw_class_t_delete_bitmap_instance_02,
    bitmap_draw_class_t_delete_bitmap_instance_03,
    bitmap_draw_class_t_delete_bitmap_instance_04,
    bitmap_draw_class_t_delete_bitmap_instance_05,
    bitmap_draw_class_t_delete_bitmap_instance_06,
    bitmap_draw_class_t_delete_bitmap_instance_07,
    bitmap_draw_class_t_delete_bitmap_instance_08,
    bitmap_draw_class_t_delete_bitmap_instance_09,
    bitmap_draw_class_t_delete_bitmap_instance_10,
    bitmap_draw_class_t_delete_bitmap_instance_11,
    bitmap_draw_class_t_delete_bitmap_instance_12,
    bitmap_draw_class_t_delete_bitmap_instance_13,
    bitmap_draw_class_t_delete_bitmap_instance_14,
    bitmap_draw_class_t_delete_bitmap_instance_15,
    bitmap_draw_class_t_delete_bitmap_instance_16,
    bitmap_draw_class_t_delete_bitmap_instance_17,
    bitmap_draw_class_t_delete_bitmap_instance_18,
    bitmap_draw_class_t_delete_bitmap_instance_19,
    bitmap_draw_class_t_delete_bitmap_instance_20,
    bitmap_draw_class_t_delete_bitmap_instance_21,
    bitmap_draw_class_t_delete_bitmap_instance_22,
    bitmap_draw_class_t_delete_bitmap_instance_23,
    bitmap_draw_class_t_delete_bitmap_instance_24,
    bitmap_draw_class_t_delete_bitmap_instance_25,
    bitmap_draw_class_t_delete_bitmap_instance_26,
    bitmap_draw_class_t_delete_bitmap_instance_27,
    bitmap_draw_class_t_delete_bitmap_instance_28,
    bitmap_draw_class_t_delete_bitmap_instance_29,
    bitmap_draw_class_t_delete_bitmap_instance_30,
    bitmap_draw_class_t_delete_bitmap_instance_31,
    bitmap_draw_class_t_delete_bitmap_instance_32,
    bitmap_draw_class_t_delete_bitmap_instance_33,
    bitmap_draw_class_t_delete_bitmap_instance_34,
    bitmap_draw_class_t_delete_bitmap_instance_35,
    bitmap_draw_class_t_delete_bitmap_instance_36,
    bitmap_draw_class_t_delete_bitmap_instance_37,
    bitmap_draw_class_t_delete_bitmap_instance_38,
    bitmap_draw_class_t_delete_bitmap_instance_39,
    bitmap_draw_class_t_delete_bitmap_instance_40,
    bitmap_draw_class_t_delete_bitmap_instance_41,
    bitmap_draw_class_t_delete_bitmap_instance_42,
    bitmap_draw_class_t_delete_bitmap_instance_43,
    bitmap_draw_class_t_delete_bitmap_instance_44,
    bitmap_draw_class_t_delete_bitmap_instance_45,
    bitmap_draw_class_t_delete_bitmap_instance_46,
    bitmap_draw_class_t_delete_bitmap_instance_47,
    bitmap_draw_class_t_delete_bitmap_instance_48,
    bitmap_draw_class_t_delete_bitmap_instance_49,
    bitmap_draw_class_t_delete_bitmap_instance_50,
    bitmap_draw_class_t_delete_bitmap_instance_51,
    bitmap_draw_class_t_delete_bitmap_instance_52,
    bitmap_draw_class_t_delete_bitmap_instance_53,
    bitmap_draw_class_t_delete_bitmap_instance_54,
    bitmap_draw_class_t_delete_bitmap_instance_55,
    bitmap_draw_class_t_delete_bitmap_instance_56,
    bitmap_draw_class_t_delete_bitmap_instance_57,
    bitmap_draw_class_t_delete_bitmap_instance_58,
    bitmap_draw_class_t_delete_bitmap_instance_59,
    bitmap_draw_class_t_delete_bitmap_instance_60,
    bitmap_draw_class_t_delete_bitmap_instance_61,
    bitmap_draw_class_t_delete_bitmap_instance_62,
    bitmap_draw_class_t_delete_bitmap_instance_63,
};

typedef void ( *bitmap_draw_class_t_fill_box_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );

static void bitmap_draw_class_t_fill_box_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 0], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 1], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 2], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 3], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 4], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 5], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 6], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 7], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 8], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->fill_box( _instance_list_bitmap_draw_class_t[ 9], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->fill_box( _instance_list_bitmap_draw_class_t[10], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->fill_box( _instance_list_bitmap_draw_class_t[11], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->fill_box( _instance_list_bitmap_draw_class_t[12], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->fill_box( _instance_list_bitmap_draw_class_t[13], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->fill_box( _instance_list_bitmap_draw_class_t[14], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->fill_box( _instance_list_bitmap_draw_class_t[15], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->fill_box( _instance_list_bitmap_draw_class_t[16], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->fill_box( _instance_list_bitmap_draw_class_t[17], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->fill_box( _instance_list_bitmap_draw_class_t[18], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->fill_box( _instance_list_bitmap_draw_class_t[19], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->fill_box( _instance_list_bitmap_draw_class_t[20], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->fill_box( _instance_list_bitmap_draw_class_t[21], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->fill_box( _instance_list_bitmap_draw_class_t[22], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->fill_box( _instance_list_bitmap_draw_class_t[23], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->fill_box( _instance_list_bitmap_draw_class_t[24], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->fill_box( _instance_list_bitmap_draw_class_t[25], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->fill_box( _instance_list_bitmap_draw_class_t[26], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->fill_box( _instance_list_bitmap_draw_class_t[27], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->fill_box( _instance_list_bitmap_draw_class_t[28], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->fill_box( _instance_list_bitmap_draw_class_t[29], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->fill_box( _instance_list_bitmap_draw_class_t[30], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->fill_box( _instance_list_bitmap_draw_class_t[31], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->fill_box( _instance_list_bitmap_draw_class_t[32], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->fill_box( _instance_list_bitmap_draw_class_t[33], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->fill_box( _instance_list_bitmap_draw_class_t[34], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->fill_box( _instance_list_bitmap_draw_class_t[35], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->fill_box( _instance_list_bitmap_draw_class_t[36], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->fill_box( _instance_list_bitmap_draw_class_t[37], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->fill_box( _instance_list_bitmap_draw_class_t[38], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->fill_box( _instance_list_bitmap_draw_class_t[39], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->fill_box( _instance_list_bitmap_draw_class_t[40], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->fill_box( _instance_list_bitmap_draw_class_t[41], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->fill_box( _instance_list_bitmap_draw_class_t[42], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->fill_box( _instance_list_bitmap_draw_class_t[43], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->fill_box( _instance_list_bitmap_draw_class_t[44], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->fill_box( _instance_list_bitmap_draw_class_t[45], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->fill_box( _instance_list_bitmap_draw_class_t[46], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->fill_box( _instance_list_bitmap_draw_class_t[47], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->fill_box( _instance_list_bitmap_draw_class_t[48], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->fill_box( _instance_list_bitmap_draw_class_t[49], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->fill_box( _instance_list_bitmap_draw_class_t[50], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->fill_box( _instance_list_bitmap_draw_class_t[51], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->fill_box( _instance_list_bitmap_draw_class_t[52], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->fill_box( _instance_list_bitmap_draw_class_t[53], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->fill_box( _instance_list_bitmap_draw_class_t[54], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->fill_box( _instance_list_bitmap_draw_class_t[55], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->fill_box( _instance_list_bitmap_draw_class_t[56], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->fill_box( _instance_list_bitmap_draw_class_t[57], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->fill_box( _instance_list_bitmap_draw_class_t[58], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->fill_box( _instance_list_bitmap_draw_class_t[59], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->fill_box( _instance_list_bitmap_draw_class_t[60], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->fill_box( _instance_list_bitmap_draw_class_t[61], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->fill_box( _instance_list_bitmap_draw_class_t[62], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_fill_box_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->fill_box( _instance_list_bitmap_draw_class_t[63], posx, posy, width, height, colour ); }

static const bitmap_draw_class_t_fill_box_t _bitmap_draw_class_t_fill_box_list[64] =
{
    bitmap_draw_class_t_fill_box_instance_00,
    bitmap_draw_class_t_fill_box_instance_01,
    bitmap_draw_class_t_fill_box_instance_02,
    bitmap_draw_class_t_fill_box_instance_03,
    bitmap_draw_class_t_fill_box_instance_04,
    bitmap_draw_class_t_fill_box_instance_05,
    bitmap_draw_class_t_fill_box_instance_06,
    bitmap_draw_class_t_fill_box_instance_07,
    bitmap_draw_class_t_fill_box_instance_08,
    bitmap_draw_class_t_fill_box_instance_09,
    bitmap_draw_class_t_fill_box_instance_10,
    bitmap_draw_class_t_fill_box_instance_11,
    bitmap_draw_class_t_fill_box_instance_12,
    bitmap_draw_class_t_fill_box_instance_13,
    bitmap_draw_class_t_fill_box_instance_14,
    bitmap_draw_class_t_fill_box_instance_15,
    bitmap_draw_class_t_fill_box_instance_16,
    bitmap_draw_class_t_fill_box_instance_17,
    bitmap_draw_class_t_fill_box_instance_18,
    bitmap_draw_class_t_fill_box_instance_19,
    bitmap_draw_class_t_fill_box_instance_20,
    bitmap_draw_class_t_fill_box_instance_21,
    bitmap_draw_class_t_fill_box_instance_22,
    bitmap_draw_class_t_fill_box_instance_23,
    bitmap_draw_class_t_fill_box_instance_24,
    bitmap_draw_class_t_fill_box_instance_25,
    bitmap_draw_class_t_fill_box_instance_26,
    bitmap_draw_class_t_fill_box_instance_27,
    bitmap_draw_class_t_fill_box_instance_28,
    bitmap_draw_class_t_fill_box_instance_29,
    bitmap_draw_class_t_fill_box_instance_30,
    bitmap_draw_class_t_fill_box_instance_31,
    bitmap_draw_class_t_fill_box_instance_32,
    bitmap_draw_class_t_fill_box_instance_33,
    bitmap_draw_class_t_fill_box_instance_34,
    bitmap_draw_class_t_fill_box_instance_35,
    bitmap_draw_class_t_fill_box_instance_36,
    bitmap_draw_class_t_fill_box_instance_37,
    bitmap_draw_class_t_fill_box_instance_38,
    bitmap_draw_class_t_fill_box_instance_39,
    bitmap_draw_class_t_fill_box_instance_40,
    bitmap_draw_class_t_fill_box_instance_41,
    bitmap_draw_class_t_fill_box_instance_42,
    bitmap_draw_class_t_fill_box_instance_43,
    bitmap_draw_class_t_fill_box_instance_44,
    bitmap_draw_class_t_fill_box_instance_45,
    bitmap_draw_class_t_fill_box_instance_46,
    bitmap_draw_class_t_fill_box_instance_47,
    bitmap_draw_class_t_fill_box_instance_48,
    bitmap_draw_class_t_fill_box_instance_49,
    bitmap_draw_class_t_fill_box_instance_50,
    bitmap_draw_class_t_fill_box_instance_51,
    bitmap_draw_class_t_fill_box_instance_52,
    bitmap_draw_class_t_fill_box_instance_53,
    bitmap_draw_class_t_fill_box_instance_54,
    bitmap_draw_class_t_fill_box_instance_55,
    bitmap_draw_class_t_fill_box_instance_56,
    bitmap_draw_class_t_fill_box_instance_57,
    bitmap_draw_class_t_fill_box_instance_58,
    bitmap_draw_class_t_fill_box_instance_59,
    bitmap_draw_class_t_fill_box_instance_60,
    bitmap_draw_class_t_fill_box_instance_61,
    bitmap_draw_class_t_fill_box_instance_62,
    bitmap_draw_class_t_fill_box_instance_63,
};

typedef void ( *bitmap_draw_class_t_draw_line_t )( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour );

static void bitmap_draw_class_t_draw_line_instance_00( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 0], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_01( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 1], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_02( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 2], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_03( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 3], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_04( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 4], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_05( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 5], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_06( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 6], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_07( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 7], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_08( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 8], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_09( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->draw_line( _instance_list_bitmap_draw_class_t[ 9], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_10( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->draw_line( _instance_list_bitmap_draw_class_t[10], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_11( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->draw_line( _instance_list_bitmap_draw_class_t[11], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_12( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->draw_line( _instance_list_bitmap_draw_class_t[12], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_13( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->draw_line( _instance_list_bitmap_draw_class_t[13], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_14( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->draw_line( _instance_list_bitmap_draw_class_t[14], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_15( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->draw_line( _instance_list_bitmap_draw_class_t[15], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_16( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->draw_line( _instance_list_bitmap_draw_class_t[16], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_17( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->draw_line( _instance_list_bitmap_draw_class_t[17], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_18( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->draw_line( _instance_list_bitmap_draw_class_t[18], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_19( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->draw_line( _instance_list_bitmap_draw_class_t[19], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_20( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->draw_line( _instance_list_bitmap_draw_class_t[20], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_21( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->draw_line( _instance_list_bitmap_draw_class_t[21], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_22( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->draw_line( _instance_list_bitmap_draw_class_t[22], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_23( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->draw_line( _instance_list_bitmap_draw_class_t[23], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_24( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->draw_line( _instance_list_bitmap_draw_class_t[24], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_25( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->draw_line( _instance_list_bitmap_draw_class_t[25], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_26( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->draw_line( _instance_list_bitmap_draw_class_t[26], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_27( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->draw_line( _instance_list_bitmap_draw_class_t[27], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_28( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->draw_line( _instance_list_bitmap_draw_class_t[28], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_29( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->draw_line( _instance_list_bitmap_draw_class_t[29], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_30( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->draw_line( _instance_list_bitmap_draw_class_t[30], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_31( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->draw_line( _instance_list_bitmap_draw_class_t[31], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_32( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->draw_line( _instance_list_bitmap_draw_class_t[32], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_33( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->draw_line( _instance_list_bitmap_draw_class_t[33], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_34( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->draw_line( _instance_list_bitmap_draw_class_t[34], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_35( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->draw_line( _instance_list_bitmap_draw_class_t[35], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_36( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->draw_line( _instance_list_bitmap_draw_class_t[36], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_37( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->draw_line( _instance_list_bitmap_draw_class_t[37], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_38( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->draw_line( _instance_list_bitmap_draw_class_t[38], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_39( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->draw_line( _instance_list_bitmap_draw_class_t[39], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_40( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->draw_line( _instance_list_bitmap_draw_class_t[40], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_41( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->draw_line( _instance_list_bitmap_draw_class_t[41], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_42( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->draw_line( _instance_list_bitmap_draw_class_t[42], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_43( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->draw_line( _instance_list_bitmap_draw_class_t[43], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_44( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->draw_line( _instance_list_bitmap_draw_class_t[44], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_45( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->draw_line( _instance_list_bitmap_draw_class_t[45], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_46( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->draw_line( _instance_list_bitmap_draw_class_t[46], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_47( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->draw_line( _instance_list_bitmap_draw_class_t[47], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_48( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->draw_line( _instance_list_bitmap_draw_class_t[48], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_49( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->draw_line( _instance_list_bitmap_draw_class_t[49], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_50( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->draw_line( _instance_list_bitmap_draw_class_t[50], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_51( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->draw_line( _instance_list_bitmap_draw_class_t[51], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_52( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->draw_line( _instance_list_bitmap_draw_class_t[52], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_53( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->draw_line( _instance_list_bitmap_draw_class_t[53], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_54( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->draw_line( _instance_list_bitmap_draw_class_t[54], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_55( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->draw_line( _instance_list_bitmap_draw_class_t[55], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_56( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->draw_line( _instance_list_bitmap_draw_class_t[56], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_57( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->draw_line( _instance_list_bitmap_draw_class_t[57], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_58( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->draw_line( _instance_list_bitmap_draw_class_t[58], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_59( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->draw_line( _instance_list_bitmap_draw_class_t[59], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_60( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->draw_line( _instance_list_bitmap_draw_class_t[60], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_61( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->draw_line( _instance_list_bitmap_draw_class_t[61], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_62( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->draw_line( _instance_list_bitmap_draw_class_t[62], posx1, posy1, posx2, posy2, colour ); }
static void bitmap_draw_class_t_draw_line_instance_63( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->draw_line( _instance_list_bitmap_draw_class_t[63], posx1, posy1, posx2, posy2, colour ); }

static const bitmap_draw_class_t_draw_line_t _bitmap_draw_class_t_draw_line_list[64] =
{
    bitmap_draw_class_t_draw_line_instance_00,
    bitmap_draw_class_t_draw_line_instance_01,
    bitmap_draw_class_t_draw_line_instance_02,
    bitmap_draw_class_t_draw_line_instance_03,
    bitmap_draw_class_t_draw_line_instance_04,
    bitmap_draw_class_t_draw_line_instance_05,
    bitmap_draw_class_t_draw_line_instance_06,
    bitmap_draw_class_t_draw_line_instance_07,
    bitmap_draw_class_t_draw_line_instance_08,
    bitmap_draw_class_t_draw_line_instance_09,
    bitmap_draw_class_t_draw_line_instance_10,
    bitmap_draw_class_t_draw_line_instance_11,
    bitmap_draw_class_t_draw_line_instance_12,
    bitmap_draw_class_t_draw_line_instance_13,
    bitmap_draw_class_t_draw_line_instance_14,
    bitmap_draw_class_t_draw_line_instance_15,
    bitmap_draw_class_t_draw_line_instance_16,
    bitmap_draw_class_t_draw_line_instance_17,
    bitmap_draw_class_t_draw_line_instance_18,
    bitmap_draw_class_t_draw_line_instance_19,
    bitmap_draw_class_t_draw_line_instance_20,
    bitmap_draw_class_t_draw_line_instance_21,
    bitmap_draw_class_t_draw_line_instance_22,
    bitmap_draw_class_t_draw_line_instance_23,
    bitmap_draw_class_t_draw_line_instance_24,
    bitmap_draw_class_t_draw_line_instance_25,
    bitmap_draw_class_t_draw_line_instance_26,
    bitmap_draw_class_t_draw_line_instance_27,
    bitmap_draw_class_t_draw_line_instance_28,
    bitmap_draw_class_t_draw_line_instance_29,
    bitmap_draw_class_t_draw_line_instance_30,
    bitmap_draw_class_t_draw_line_instance_31,
    bitmap_draw_class_t_draw_line_instance_32,
    bitmap_draw_class_t_draw_line_instance_33,
    bitmap_draw_class_t_draw_line_instance_34,
    bitmap_draw_class_t_draw_line_instance_35,
    bitmap_draw_class_t_draw_line_instance_36,
    bitmap_draw_class_t_draw_line_instance_37,
    bitmap_draw_class_t_draw_line_instance_38,
    bitmap_draw_class_t_draw_line_instance_39,
    bitmap_draw_class_t_draw_line_instance_40,
    bitmap_draw_class_t_draw_line_instance_41,
    bitmap_draw_class_t_draw_line_instance_42,
    bitmap_draw_class_t_draw_line_instance_43,
    bitmap_draw_class_t_draw_line_instance_44,
    bitmap_draw_class_t_draw_line_instance_45,
    bitmap_draw_class_t_draw_line_instance_46,
    bitmap_draw_class_t_draw_line_instance_47,
    bitmap_draw_class_t_draw_line_instance_48,
    bitmap_draw_class_t_draw_line_instance_49,
    bitmap_draw_class_t_draw_line_instance_50,
    bitmap_draw_class_t_draw_line_instance_51,
    bitmap_draw_class_t_draw_line_instance_52,
    bitmap_draw_class_t_draw_line_instance_53,
    bitmap_draw_class_t_draw_line_instance_54,
    bitmap_draw_class_t_draw_line_instance_55,
    bitmap_draw_class_t_draw_line_instance_56,
    bitmap_draw_class_t_draw_line_instance_57,
    bitmap_draw_class_t_draw_line_instance_58,
    bitmap_draw_class_t_draw_line_instance_59,
    bitmap_draw_class_t_draw_line_instance_60,
    bitmap_draw_class_t_draw_line_instance_61,
    bitmap_draw_class_t_draw_line_instance_62,
    bitmap_draw_class_t_draw_line_instance_63,
};

typedef void ( *bitmap_draw_class_t_draw_rectangle_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour );

static void bitmap_draw_class_t_draw_rectangle_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 0], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 1], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 2], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 3], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 4], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 5], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 6], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 7], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 8], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[ 9], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[10], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[11], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[12], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[13], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[14], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[15], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[16], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[17], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[18], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[19], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[20], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[21], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[22], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[23], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[24], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[25], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[26], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[27], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[28], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[29], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[30], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[31], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[32], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[33], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[34], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[35], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[36], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[37], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[38], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[39], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[40], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[41], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[42], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[43], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[44], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[45], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[46], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[47], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[48], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[49], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[50], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[51], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[52], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[53], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[54], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[55], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[56], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[57], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[58], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[59], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[60], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[61], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[62], posx, posy, width, height, colour ); }
static void bitmap_draw_class_t_draw_rectangle_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->draw_rectangle( _instance_list_bitmap_draw_class_t[63], posx, posy, width, height, colour ); }

static const bitmap_draw_class_t_draw_rectangle_t _bitmap_draw_class_t_draw_rectangle_list[64] =
{
    bitmap_draw_class_t_draw_rectangle_instance_00,
    bitmap_draw_class_t_draw_rectangle_instance_01,
    bitmap_draw_class_t_draw_rectangle_instance_02,
    bitmap_draw_class_t_draw_rectangle_instance_03,
    bitmap_draw_class_t_draw_rectangle_instance_04,
    bitmap_draw_class_t_draw_rectangle_instance_05,
    bitmap_draw_class_t_draw_rectangle_instance_06,
    bitmap_draw_class_t_draw_rectangle_instance_07,
    bitmap_draw_class_t_draw_rectangle_instance_08,
    bitmap_draw_class_t_draw_rectangle_instance_09,
    bitmap_draw_class_t_draw_rectangle_instance_10,
    bitmap_draw_class_t_draw_rectangle_instance_11,
    bitmap_draw_class_t_draw_rectangle_instance_12,
    bitmap_draw_class_t_draw_rectangle_instance_13,
    bitmap_draw_class_t_draw_rectangle_instance_14,
    bitmap_draw_class_t_draw_rectangle_instance_15,
    bitmap_draw_class_t_draw_rectangle_instance_16,
    bitmap_draw_class_t_draw_rectangle_instance_17,
    bitmap_draw_class_t_draw_rectangle_instance_18,
    bitmap_draw_class_t_draw_rectangle_instance_19,
    bitmap_draw_class_t_draw_rectangle_instance_20,
    bitmap_draw_class_t_draw_rectangle_instance_21,
    bitmap_draw_class_t_draw_rectangle_instance_22,
    bitmap_draw_class_t_draw_rectangle_instance_23,
    bitmap_draw_class_t_draw_rectangle_instance_24,
    bitmap_draw_class_t_draw_rectangle_instance_25,
    bitmap_draw_class_t_draw_rectangle_instance_26,
    bitmap_draw_class_t_draw_rectangle_instance_27,
    bitmap_draw_class_t_draw_rectangle_instance_28,
    bitmap_draw_class_t_draw_rectangle_instance_29,
    bitmap_draw_class_t_draw_rectangle_instance_30,
    bitmap_draw_class_t_draw_rectangle_instance_31,
    bitmap_draw_class_t_draw_rectangle_instance_32,
    bitmap_draw_class_t_draw_rectangle_instance_33,
    bitmap_draw_class_t_draw_rectangle_instance_34,
    bitmap_draw_class_t_draw_rectangle_instance_35,
    bitmap_draw_class_t_draw_rectangle_instance_36,
    bitmap_draw_class_t_draw_rectangle_instance_37,
    bitmap_draw_class_t_draw_rectangle_instance_38,
    bitmap_draw_class_t_draw_rectangle_instance_39,
    bitmap_draw_class_t_draw_rectangle_instance_40,
    bitmap_draw_class_t_draw_rectangle_instance_41,
    bitmap_draw_class_t_draw_rectangle_instance_42,
    bitmap_draw_class_t_draw_rectangle_instance_43,
    bitmap_draw_class_t_draw_rectangle_instance_44,
    bitmap_draw_class_t_draw_rectangle_instance_45,
    bitmap_draw_class_t_draw_rectangle_instance_46,
    bitmap_draw_class_t_draw_rectangle_instance_47,
    bitmap_draw_class_t_draw_rectangle_instance_48,
    bitmap_draw_class_t_draw_rectangle_instance_49,
    bitmap_draw_class_t_draw_rectangle_instance_50,
    bitmap_draw_class_t_draw_rectangle_instance_51,
    bitmap_draw_class_t_draw_rectangle_instance_52,
    bitmap_draw_class_t_draw_rectangle_instance_53,
    bitmap_draw_class_t_draw_rectangle_instance_54,
    bitmap_draw_class_t_draw_rectangle_instance_55,
    bitmap_draw_class_t_draw_rectangle_instance_56,
    bitmap_draw_class_t_draw_rectangle_instance_57,
    bitmap_draw_class_t_draw_rectangle_instance_58,
    bitmap_draw_class_t_draw_rectangle_instance_59,
    bitmap_draw_class_t_draw_rectangle_instance_60,
    bitmap_draw_class_t_draw_rectangle_instance_61,
    bitmap_draw_class_t_draw_rectangle_instance_62,
    bitmap_draw_class_t_draw_rectangle_instance_63,
};

typedef void ( *bitmap_draw_class_t_draw_circle_t )( uint16_t posx, uint16_t posy, int ratio, pixel_t colour );

static void bitmap_draw_class_t_draw_circle_instance_00( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 0], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_01( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 1], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_02( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 2], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_03( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 3], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_04( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 4], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_05( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 5], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_06( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 6], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_07( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 7], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_08( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 8], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_09( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[ 9], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_10( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[10], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_11( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[11], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_12( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[12], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_13( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[13], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_14( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[14], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_15( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[15], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_16( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[16], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_17( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[17], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_18( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[18], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_19( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[19], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_20( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[20], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_21( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[21], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_22( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[22], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_23( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[23], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_24( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[24], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_25( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[25], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_26( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[26], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_27( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[27], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_28( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[28], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_29( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[29], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_30( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[30], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_31( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[31], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_32( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[32], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_33( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[33], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_34( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[34], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_35( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[35], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_36( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[36], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_37( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[37], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_38( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[38], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_39( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[39], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_40( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[40], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_41( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[41], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_42( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[42], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_43( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[43], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_44( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[44], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_45( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[45], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_46( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[46], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_47( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[47], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_48( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[48], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_49( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[49], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_50( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[50], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_51( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[51], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_52( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[52], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_53( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[53], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_54( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[54], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_55( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[55], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_56( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[56], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_57( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[57], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_58( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[58], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_59( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[59], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_60( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[60], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_61( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[61], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_62( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[62], posx, posy, ratio, colour ); }
static void bitmap_draw_class_t_draw_circle_instance_63( uint16_t posx, uint16_t posy, int ratio, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->draw_circle( _instance_list_bitmap_draw_class_t[63], posx, posy, ratio, colour ); }

static const bitmap_draw_class_t_draw_circle_t _bitmap_draw_class_t_draw_circle_list[64] =
{
    bitmap_draw_class_t_draw_circle_instance_00,
    bitmap_draw_class_t_draw_circle_instance_01,
    bitmap_draw_class_t_draw_circle_instance_02,
    bitmap_draw_class_t_draw_circle_instance_03,
    bitmap_draw_class_t_draw_circle_instance_04,
    bitmap_draw_class_t_draw_circle_instance_05,
    bitmap_draw_class_t_draw_circle_instance_06,
    bitmap_draw_class_t_draw_circle_instance_07,
    bitmap_draw_class_t_draw_circle_instance_08,
    bitmap_draw_class_t_draw_circle_instance_09,
    bitmap_draw_class_t_draw_circle_instance_10,
    bitmap_draw_class_t_draw_circle_instance_11,
    bitmap_draw_class_t_draw_circle_instance_12,
    bitmap_draw_class_t_draw_circle_instance_13,
    bitmap_draw_class_t_draw_circle_instance_14,
    bitmap_draw_class_t_draw_circle_instance_15,
    bitmap_draw_class_t_draw_circle_instance_16,
    bitmap_draw_class_t_draw_circle_instance_17,
    bitmap_draw_class_t_draw_circle_instance_18,
    bitmap_draw_class_t_draw_circle_instance_19,
    bitmap_draw_class_t_draw_circle_instance_20,
    bitmap_draw_class_t_draw_circle_instance_21,
    bitmap_draw_class_t_draw_circle_instance_22,
    bitmap_draw_class_t_draw_circle_instance_23,
    bitmap_draw_class_t_draw_circle_instance_24,
    bitmap_draw_class_t_draw_circle_instance_25,
    bitmap_draw_class_t_draw_circle_instance_26,
    bitmap_draw_class_t_draw_circle_instance_27,
    bitmap_draw_class_t_draw_circle_instance_28,
    bitmap_draw_class_t_draw_circle_instance_29,
    bitmap_draw_class_t_draw_circle_instance_30,
    bitmap_draw_class_t_draw_circle_instance_31,
    bitmap_draw_class_t_draw_circle_instance_32,
    bitmap_draw_class_t_draw_circle_instance_33,
    bitmap_draw_class_t_draw_circle_instance_34,
    bitmap_draw_class_t_draw_circle_instance_35,
    bitmap_draw_class_t_draw_circle_instance_36,
    bitmap_draw_class_t_draw_circle_instance_37,
    bitmap_draw_class_t_draw_circle_instance_38,
    bitmap_draw_class_t_draw_circle_instance_39,
    bitmap_draw_class_t_draw_circle_instance_40,
    bitmap_draw_class_t_draw_circle_instance_41,
    bitmap_draw_class_t_draw_circle_instance_42,
    bitmap_draw_class_t_draw_circle_instance_43,
    bitmap_draw_class_t_draw_circle_instance_44,
    bitmap_draw_class_t_draw_circle_instance_45,
    bitmap_draw_class_t_draw_circle_instance_46,
    bitmap_draw_class_t_draw_circle_instance_47,
    bitmap_draw_class_t_draw_circle_instance_48,
    bitmap_draw_class_t_draw_circle_instance_49,
    bitmap_draw_class_t_draw_circle_instance_50,
    bitmap_draw_class_t_draw_circle_instance_51,
    bitmap_draw_class_t_draw_circle_instance_52,
    bitmap_draw_class_t_draw_circle_instance_53,
    bitmap_draw_class_t_draw_circle_instance_54,
    bitmap_draw_class_t_draw_circle_instance_55,
    bitmap_draw_class_t_draw_circle_instance_56,
    bitmap_draw_class_t_draw_circle_instance_57,
    bitmap_draw_class_t_draw_circle_instance_58,
    bitmap_draw_class_t_draw_circle_instance_59,
    bitmap_draw_class_t_draw_circle_instance_60,
    bitmap_draw_class_t_draw_circle_instance_61,
    bitmap_draw_class_t_draw_circle_instance_62,
    bitmap_draw_class_t_draw_circle_instance_63,
};

typedef void ( *bitmap_draw_class_t_draw_circle_arc_t )( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour );

static void bitmap_draw_class_t_draw_circle_arc_instance_00( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 0], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_01( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 1], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_02( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 2], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_03( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 3], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_04( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 4], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_05( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 5], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_06( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 6], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_07( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 7], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_08( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 8], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_09( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[ 9], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_10( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[10], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_11( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[11], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_12( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[12], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_13( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[13], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_14( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[14], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_15( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[15], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_16( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[16], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_17( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[17], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_18( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[18], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_19( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[19], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_20( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[20], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_21( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[21], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_22( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[22], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_23( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[23], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_24( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[24], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_25( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[25], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_26( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[26], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_27( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[27], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_28( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[28], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_29( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[29], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_30( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[30], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_31( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[31], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_32( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[32], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_33( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[33], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_34( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[34], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_35( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[35], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_36( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[36], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_37( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[37], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_38( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[38], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_39( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[39], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_40( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[40], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_41( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[41], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_42( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[42], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_43( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[43], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_44( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[44], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_45( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[45], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_46( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[46], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_47( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[47], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_48( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[48], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_49( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[49], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_50( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[50], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_51( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[51], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_52( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[52], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_53( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[53], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_54( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[54], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_55( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[55], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_56( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[56], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_57( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[57], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_58( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[58], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_59( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[59], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_60( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[60], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_61( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[61], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_62( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[62], posx, posy, ratio, start, end, colour ); }
static void bitmap_draw_class_t_draw_circle_arc_instance_63( uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->draw_circle_arc( _instance_list_bitmap_draw_class_t[63], posx, posy, ratio, start, end, colour ); }

static const bitmap_draw_class_t_draw_circle_arc_t _bitmap_draw_class_t_draw_circle_arc_list[64] =
{
    bitmap_draw_class_t_draw_circle_arc_instance_00,
    bitmap_draw_class_t_draw_circle_arc_instance_01,
    bitmap_draw_class_t_draw_circle_arc_instance_02,
    bitmap_draw_class_t_draw_circle_arc_instance_03,
    bitmap_draw_class_t_draw_circle_arc_instance_04,
    bitmap_draw_class_t_draw_circle_arc_instance_05,
    bitmap_draw_class_t_draw_circle_arc_instance_06,
    bitmap_draw_class_t_draw_circle_arc_instance_07,
    bitmap_draw_class_t_draw_circle_arc_instance_08,
    bitmap_draw_class_t_draw_circle_arc_instance_09,
    bitmap_draw_class_t_draw_circle_arc_instance_10,
    bitmap_draw_class_t_draw_circle_arc_instance_11,
    bitmap_draw_class_t_draw_circle_arc_instance_12,
    bitmap_draw_class_t_draw_circle_arc_instance_13,
    bitmap_draw_class_t_draw_circle_arc_instance_14,
    bitmap_draw_class_t_draw_circle_arc_instance_15,
    bitmap_draw_class_t_draw_circle_arc_instance_16,
    bitmap_draw_class_t_draw_circle_arc_instance_17,
    bitmap_draw_class_t_draw_circle_arc_instance_18,
    bitmap_draw_class_t_draw_circle_arc_instance_19,
    bitmap_draw_class_t_draw_circle_arc_instance_20,
    bitmap_draw_class_t_draw_circle_arc_instance_21,
    bitmap_draw_class_t_draw_circle_arc_instance_22,
    bitmap_draw_class_t_draw_circle_arc_instance_23,
    bitmap_draw_class_t_draw_circle_arc_instance_24,
    bitmap_draw_class_t_draw_circle_arc_instance_25,
    bitmap_draw_class_t_draw_circle_arc_instance_26,
    bitmap_draw_class_t_draw_circle_arc_instance_27,
    bitmap_draw_class_t_draw_circle_arc_instance_28,
    bitmap_draw_class_t_draw_circle_arc_instance_29,
    bitmap_draw_class_t_draw_circle_arc_instance_30,
    bitmap_draw_class_t_draw_circle_arc_instance_31,
    bitmap_draw_class_t_draw_circle_arc_instance_32,
    bitmap_draw_class_t_draw_circle_arc_instance_33,
    bitmap_draw_class_t_draw_circle_arc_instance_34,
    bitmap_draw_class_t_draw_circle_arc_instance_35,
    bitmap_draw_class_t_draw_circle_arc_instance_36,
    bitmap_draw_class_t_draw_circle_arc_instance_37,
    bitmap_draw_class_t_draw_circle_arc_instance_38,
    bitmap_draw_class_t_draw_circle_arc_instance_39,
    bitmap_draw_class_t_draw_circle_arc_instance_40,
    bitmap_draw_class_t_draw_circle_arc_instance_41,
    bitmap_draw_class_t_draw_circle_arc_instance_42,
    bitmap_draw_class_t_draw_circle_arc_instance_43,
    bitmap_draw_class_t_draw_circle_arc_instance_44,
    bitmap_draw_class_t_draw_circle_arc_instance_45,
    bitmap_draw_class_t_draw_circle_arc_instance_46,
    bitmap_draw_class_t_draw_circle_arc_instance_47,
    bitmap_draw_class_t_draw_circle_arc_instance_48,
    bitmap_draw_class_t_draw_circle_arc_instance_49,
    bitmap_draw_class_t_draw_circle_arc_instance_50,
    bitmap_draw_class_t_draw_circle_arc_instance_51,
    bitmap_draw_class_t_draw_circle_arc_instance_52,
    bitmap_draw_class_t_draw_circle_arc_instance_53,
    bitmap_draw_class_t_draw_circle_arc_instance_54,
    bitmap_draw_class_t_draw_circle_arc_instance_55,
    bitmap_draw_class_t_draw_circle_arc_instance_56,
    bitmap_draw_class_t_draw_circle_arc_instance_57,
    bitmap_draw_class_t_draw_circle_arc_instance_58,
    bitmap_draw_class_t_draw_circle_arc_instance_59,
    bitmap_draw_class_t_draw_circle_arc_instance_60,
    bitmap_draw_class_t_draw_circle_arc_instance_61,
    bitmap_draw_class_t_draw_circle_arc_instance_62,
    bitmap_draw_class_t_draw_circle_arc_instance_63,
};

typedef void ( *bitmap_draw_class_t_flood_fill_t )( uint16_t x, uint16_t y, pixel_t colour );

static void bitmap_draw_class_t_flood_fill_instance_00( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 0], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_01( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 1], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_02( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 2], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_03( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 3], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_04( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 4], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_05( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 5], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_06( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 6], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_07( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 7], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_08( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 8], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_09( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[ 9], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_10( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[10], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_11( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[11], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_12( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[12], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_13( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[13], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_14( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[14], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_15( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[15], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_16( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[16], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_17( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[17], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_18( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[18], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_19( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[19], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_20( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[20], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_21( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[21], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_22( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[22], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_23( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[23], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_24( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[24], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_25( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[25], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_26( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[26], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_27( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[27], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_28( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[28], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_29( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[29], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_30( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[30], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_31( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[31], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_32( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[32], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_33( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[33], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_34( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[34], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_35( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[35], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_36( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[36], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_37( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[37], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_38( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[38], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_39( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[39], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_40( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[40], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_41( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[41], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_42( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[42], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_43( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[43], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_44( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[44], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_45( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[45], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_46( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[46], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_47( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[47], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_48( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[48], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_49( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[49], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_50( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[50], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_51( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[51], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_52( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[52], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_53( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[53], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_54( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[54], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_55( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[55], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_56( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[56], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_57( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[57], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_58( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[58], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_59( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[59], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_60( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[60], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_61( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[61], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_62( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[62], x, y, colour ); }
static void bitmap_draw_class_t_flood_fill_instance_63( uint16_t x, uint16_t y, pixel_t colour ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->flood_fill( _instance_list_bitmap_draw_class_t[63], x, y, colour ); }

static const bitmap_draw_class_t_flood_fill_t _bitmap_draw_class_t_flood_fill_list[64] =
{
    bitmap_draw_class_t_flood_fill_instance_00,
    bitmap_draw_class_t_flood_fill_instance_01,
    bitmap_draw_class_t_flood_fill_instance_02,
    bitmap_draw_class_t_flood_fill_instance_03,
    bitmap_draw_class_t_flood_fill_instance_04,
    bitmap_draw_class_t_flood_fill_instance_05,
    bitmap_draw_class_t_flood_fill_instance_06,
    bitmap_draw_class_t_flood_fill_instance_07,
    bitmap_draw_class_t_flood_fill_instance_08,
    bitmap_draw_class_t_flood_fill_instance_09,
    bitmap_draw_class_t_flood_fill_instance_10,
    bitmap_draw_class_t_flood_fill_instance_11,
    bitmap_draw_class_t_flood_fill_instance_12,
    bitmap_draw_class_t_flood_fill_instance_13,
    bitmap_draw_class_t_flood_fill_instance_14,
    bitmap_draw_class_t_flood_fill_instance_15,
    bitmap_draw_class_t_flood_fill_instance_16,
    bitmap_draw_class_t_flood_fill_instance_17,
    bitmap_draw_class_t_flood_fill_instance_18,
    bitmap_draw_class_t_flood_fill_instance_19,
    bitmap_draw_class_t_flood_fill_instance_20,
    bitmap_draw_class_t_flood_fill_instance_21,
    bitmap_draw_class_t_flood_fill_instance_22,
    bitmap_draw_class_t_flood_fill_instance_23,
    bitmap_draw_class_t_flood_fill_instance_24,
    bitmap_draw_class_t_flood_fill_instance_25,
    bitmap_draw_class_t_flood_fill_instance_26,
    bitmap_draw_class_t_flood_fill_instance_27,
    bitmap_draw_class_t_flood_fill_instance_28,
    bitmap_draw_class_t_flood_fill_instance_29,
    bitmap_draw_class_t_flood_fill_instance_30,
    bitmap_draw_class_t_flood_fill_instance_31,
    bitmap_draw_class_t_flood_fill_instance_32,
    bitmap_draw_class_t_flood_fill_instance_33,
    bitmap_draw_class_t_flood_fill_instance_34,
    bitmap_draw_class_t_flood_fill_instance_35,
    bitmap_draw_class_t_flood_fill_instance_36,
    bitmap_draw_class_t_flood_fill_instance_37,
    bitmap_draw_class_t_flood_fill_instance_38,
    bitmap_draw_class_t_flood_fill_instance_39,
    bitmap_draw_class_t_flood_fill_instance_40,
    bitmap_draw_class_t_flood_fill_instance_41,
    bitmap_draw_class_t_flood_fill_instance_42,
    bitmap_draw_class_t_flood_fill_instance_43,
    bitmap_draw_class_t_flood_fill_instance_44,
    bitmap_draw_class_t_flood_fill_instance_45,
    bitmap_draw_class_t_flood_fill_instance_46,
    bitmap_draw_class_t_flood_fill_instance_47,
    bitmap_draw_class_t_flood_fill_instance_48,
    bitmap_draw_class_t_flood_fill_instance_49,
    bitmap_draw_class_t_flood_fill_instance_50,
    bitmap_draw_class_t_flood_fill_instance_51,
    bitmap_draw_class_t_flood_fill_instance_52,
    bitmap_draw_class_t_flood_fill_instance_53,
    bitmap_draw_class_t_flood_fill_instance_54,
    bitmap_draw_class_t_flood_fill_instance_55,
    bitmap_draw_class_t_flood_fill_instance_56,
    bitmap_draw_class_t_flood_fill_instance_57,
    bitmap_draw_class_t_flood_fill_instance_58,
    bitmap_draw_class_t_flood_fill_instance_59,
    bitmap_draw_class_t_flood_fill_instance_60,
    bitmap_draw_class_t_flood_fill_instance_61,
    bitmap_draw_class_t_flood_fill_instance_62,
    bitmap_draw_class_t_flood_fill_instance_63,
};

typedef void ( *bitmap_draw_class_t_set_bitmap_rgb_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent );

static void bitmap_draw_class_t_set_bitmap_rgb_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 0], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 1], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 2], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 3], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 4], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 5], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 6], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 7], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 8], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 9], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[10], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[11], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[12], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[13], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[14], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[15], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[16], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[17], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[18], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[19], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[20], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[21], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[22], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[23], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[24], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[25], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[26], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[27], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[28], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[29], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[30], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[31], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[32], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[33], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[34], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[35], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[36], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[37], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[38], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[39], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[40], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[41], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[42], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[43], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[44], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[45], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[46], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[47], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[48], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[49], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[50], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[51], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[52], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[53], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[54], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[55], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[56], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[57], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[58], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[59], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[60], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[61], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[62], posx, posy, width, height, data, transparent, use_transparent ); }
static void bitmap_draw_class_t_set_bitmap_rgb_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->set_bitmap_rgb( _instance_list_bitmap_draw_class_t[63], posx, posy, width, height, data, transparent, use_transparent ); }

static const bitmap_draw_class_t_set_bitmap_rgb_t _bitmap_draw_class_t_set_bitmap_rgb_list[64] =
{
    bitmap_draw_class_t_set_bitmap_rgb_instance_00,
    bitmap_draw_class_t_set_bitmap_rgb_instance_01,
    bitmap_draw_class_t_set_bitmap_rgb_instance_02,
    bitmap_draw_class_t_set_bitmap_rgb_instance_03,
    bitmap_draw_class_t_set_bitmap_rgb_instance_04,
    bitmap_draw_class_t_set_bitmap_rgb_instance_05,
    bitmap_draw_class_t_set_bitmap_rgb_instance_06,
    bitmap_draw_class_t_set_bitmap_rgb_instance_07,
    bitmap_draw_class_t_set_bitmap_rgb_instance_08,
    bitmap_draw_class_t_set_bitmap_rgb_instance_09,
    bitmap_draw_class_t_set_bitmap_rgb_instance_10,
    bitmap_draw_class_t_set_bitmap_rgb_instance_11,
    bitmap_draw_class_t_set_bitmap_rgb_instance_12,
    bitmap_draw_class_t_set_bitmap_rgb_instance_13,
    bitmap_draw_class_t_set_bitmap_rgb_instance_14,
    bitmap_draw_class_t_set_bitmap_rgb_instance_15,
    bitmap_draw_class_t_set_bitmap_rgb_instance_16,
    bitmap_draw_class_t_set_bitmap_rgb_instance_17,
    bitmap_draw_class_t_set_bitmap_rgb_instance_18,
    bitmap_draw_class_t_set_bitmap_rgb_instance_19,
    bitmap_draw_class_t_set_bitmap_rgb_instance_20,
    bitmap_draw_class_t_set_bitmap_rgb_instance_21,
    bitmap_draw_class_t_set_bitmap_rgb_instance_22,
    bitmap_draw_class_t_set_bitmap_rgb_instance_23,
    bitmap_draw_class_t_set_bitmap_rgb_instance_24,
    bitmap_draw_class_t_set_bitmap_rgb_instance_25,
    bitmap_draw_class_t_set_bitmap_rgb_instance_26,
    bitmap_draw_class_t_set_bitmap_rgb_instance_27,
    bitmap_draw_class_t_set_bitmap_rgb_instance_28,
    bitmap_draw_class_t_set_bitmap_rgb_instance_29,
    bitmap_draw_class_t_set_bitmap_rgb_instance_30,
    bitmap_draw_class_t_set_bitmap_rgb_instance_31,
    bitmap_draw_class_t_set_bitmap_rgb_instance_32,
    bitmap_draw_class_t_set_bitmap_rgb_instance_33,
    bitmap_draw_class_t_set_bitmap_rgb_instance_34,
    bitmap_draw_class_t_set_bitmap_rgb_instance_35,
    bitmap_draw_class_t_set_bitmap_rgb_instance_36,
    bitmap_draw_class_t_set_bitmap_rgb_instance_37,
    bitmap_draw_class_t_set_bitmap_rgb_instance_38,
    bitmap_draw_class_t_set_bitmap_rgb_instance_39,
    bitmap_draw_class_t_set_bitmap_rgb_instance_40,
    bitmap_draw_class_t_set_bitmap_rgb_instance_41,
    bitmap_draw_class_t_set_bitmap_rgb_instance_42,
    bitmap_draw_class_t_set_bitmap_rgb_instance_43,
    bitmap_draw_class_t_set_bitmap_rgb_instance_44,
    bitmap_draw_class_t_set_bitmap_rgb_instance_45,
    bitmap_draw_class_t_set_bitmap_rgb_instance_46,
    bitmap_draw_class_t_set_bitmap_rgb_instance_47,
    bitmap_draw_class_t_set_bitmap_rgb_instance_48,
    bitmap_draw_class_t_set_bitmap_rgb_instance_49,
    bitmap_draw_class_t_set_bitmap_rgb_instance_50,
    bitmap_draw_class_t_set_bitmap_rgb_instance_51,
    bitmap_draw_class_t_set_bitmap_rgb_instance_52,
    bitmap_draw_class_t_set_bitmap_rgb_instance_53,
    bitmap_draw_class_t_set_bitmap_rgb_instance_54,
    bitmap_draw_class_t_set_bitmap_rgb_instance_55,
    bitmap_draw_class_t_set_bitmap_rgb_instance_56,
    bitmap_draw_class_t_set_bitmap_rgb_instance_57,
    bitmap_draw_class_t_set_bitmap_rgb_instance_58,
    bitmap_draw_class_t_set_bitmap_rgb_instance_59,
    bitmap_draw_class_t_set_bitmap_rgb_instance_60,
    bitmap_draw_class_t_set_bitmap_rgb_instance_61,
    bitmap_draw_class_t_set_bitmap_rgb_instance_62,
    bitmap_draw_class_t_set_bitmap_rgb_instance_63,
};

typedef void ( *bitmap_draw_class_t_get_bitmap_rgb_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data );

static void bitmap_draw_class_t_get_bitmap_rgb_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 0]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 0], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 1]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 1], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 2]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 2], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 3]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 3], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 4]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 4], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 5]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 5], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 6]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 6], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 7]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 7], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 8]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 8], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[ 9]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[ 9], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[10]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[10], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[11]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[11], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[12]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[12], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[13]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[13], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[14]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[14], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[15]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[15], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[16]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[16], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[17]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[17], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[18]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[18], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[19]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[19], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[20]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[20], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[21]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[21], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[22]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[22], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[23]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[23], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[24]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[24], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[25]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[25], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[26]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[26], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[27]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[27], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[28]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[28], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[29]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[29], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[30]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[30], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[31]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[31], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[32]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[32], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[33]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[33], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[34]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[34], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[35]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[35], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[36]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[36], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[37]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[37], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[38]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[38], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[39]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[39], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[40]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[40], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[41]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[41], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[42]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[42], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[43]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[43], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[44]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[44], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[45]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[45], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[46]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[46], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[47]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[47], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[48]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[48], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[49]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[49], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[50]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[50], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[51]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[51], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[52]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[52], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[53]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[53], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[54]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[54], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[55]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[55], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[56]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[56], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[57]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[57], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[58]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[58], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[59]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[59], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[60]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[60], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[61]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[61], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[62]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[62], posx, posy, width, height, data ); }
static void bitmap_draw_class_t_get_bitmap_rgb_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data ){ ( ( api_bitmap_draw_class_t * )_instance_list_bitmap_draw_class_t[63]->__api )->get_bitmap_rgb( _instance_list_bitmap_draw_class_t[63], posx, posy, width, height, data ); }

static const bitmap_draw_class_t_get_bitmap_rgb_t _bitmap_draw_class_t_get_bitmap_rgb_list[64] =
{
    bitmap_draw_class_t_get_bitmap_rgb_instance_00,
    bitmap_draw_class_t_get_bitmap_rgb_instance_01,
    bitmap_draw_class_t_get_bitmap_rgb_instance_02,
    bitmap_draw_class_t_get_bitmap_rgb_instance_03,
    bitmap_draw_class_t_get_bitmap_rgb_instance_04,
    bitmap_draw_class_t_get_bitmap_rgb_instance_05,
    bitmap_draw_class_t_get_bitmap_rgb_instance_06,
    bitmap_draw_class_t_get_bitmap_rgb_instance_07,
    bitmap_draw_class_t_get_bitmap_rgb_instance_08,
    bitmap_draw_class_t_get_bitmap_rgb_instance_09,
    bitmap_draw_class_t_get_bitmap_rgb_instance_10,
    bitmap_draw_class_t_get_bitmap_rgb_instance_11,
    bitmap_draw_class_t_get_bitmap_rgb_instance_12,
    bitmap_draw_class_t_get_bitmap_rgb_instance_13,
    bitmap_draw_class_t_get_bitmap_rgb_instance_14,
    bitmap_draw_class_t_get_bitmap_rgb_instance_15,
    bitmap_draw_class_t_get_bitmap_rgb_instance_16,
    bitmap_draw_class_t_get_bitmap_rgb_instance_17,
    bitmap_draw_class_t_get_bitmap_rgb_instance_18,
    bitmap_draw_class_t_get_bitmap_rgb_instance_19,
    bitmap_draw_class_t_get_bitmap_rgb_instance_20,
    bitmap_draw_class_t_get_bitmap_rgb_instance_21,
    bitmap_draw_class_t_get_bitmap_rgb_instance_22,
    bitmap_draw_class_t_get_bitmap_rgb_instance_23,
    bitmap_draw_class_t_get_bitmap_rgb_instance_24,
    bitmap_draw_class_t_get_bitmap_rgb_instance_25,
    bitmap_draw_class_t_get_bitmap_rgb_instance_26,
    bitmap_draw_class_t_get_bitmap_rgb_instance_27,
    bitmap_draw_class_t_get_bitmap_rgb_instance_28,
    bitmap_draw_class_t_get_bitmap_rgb_instance_29,
    bitmap_draw_class_t_get_bitmap_rgb_instance_30,
    bitmap_draw_class_t_get_bitmap_rgb_instance_31,
    bitmap_draw_class_t_get_bitmap_rgb_instance_32,
    bitmap_draw_class_t_get_bitmap_rgb_instance_33,
    bitmap_draw_class_t_get_bitmap_rgb_instance_34,
    bitmap_draw_class_t_get_bitmap_rgb_instance_35,
    bitmap_draw_class_t_get_bitmap_rgb_instance_36,
    bitmap_draw_class_t_get_bitmap_rgb_instance_37,
    bitmap_draw_class_t_get_bitmap_rgb_instance_38,
    bitmap_draw_class_t_get_bitmap_rgb_instance_39,
    bitmap_draw_class_t_get_bitmap_rgb_instance_40,
    bitmap_draw_class_t_get_bitmap_rgb_instance_41,
    bitmap_draw_class_t_get_bitmap_rgb_instance_42,
    bitmap_draw_class_t_get_bitmap_rgb_instance_43,
    bitmap_draw_class_t_get_bitmap_rgb_instance_44,
    bitmap_draw_class_t_get_bitmap_rgb_instance_45,
    bitmap_draw_class_t_get_bitmap_rgb_instance_46,
    bitmap_draw_class_t_get_bitmap_rgb_instance_47,
    bitmap_draw_class_t_get_bitmap_rgb_instance_48,
    bitmap_draw_class_t_get_bitmap_rgb_instance_49,
    bitmap_draw_class_t_get_bitmap_rgb_instance_50,
    bitmap_draw_class_t_get_bitmap_rgb_instance_51,
    bitmap_draw_class_t_get_bitmap_rgb_instance_52,
    bitmap_draw_class_t_get_bitmap_rgb_instance_53,
    bitmap_draw_class_t_get_bitmap_rgb_instance_54,
    bitmap_draw_class_t_get_bitmap_rgb_instance_55,
    bitmap_draw_class_t_get_bitmap_rgb_instance_56,
    bitmap_draw_class_t_get_bitmap_rgb_instance_57,
    bitmap_draw_class_t_get_bitmap_rgb_instance_58,
    bitmap_draw_class_t_get_bitmap_rgb_instance_59,
    bitmap_draw_class_t_get_bitmap_rgb_instance_60,
    bitmap_draw_class_t_get_bitmap_rgb_instance_61,
    bitmap_draw_class_t_get_bitmap_rgb_instance_62,
    bitmap_draw_class_t_get_bitmap_rgb_instance_63,
};

void * _instance_new_bitmap_draw_class_t_ex( void * __api, bitmap_class_t * bitmap_class )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_bitmap_draw_class_t, sizeof(bitmap_draw_class_t), 64 );
    if( _instance_index == -1 ) return NULL;
    bitmap_draw_class_t * ret = _instance_list_bitmap_draw_class_t[_instance_index];
    ret->__api = __api;
    ret->fill_box = _bitmap_draw_class_t_fill_box_list[_instance_index];
    ret->draw_line = _bitmap_draw_class_t_draw_line_list[_instance_index];
    ret->draw_rectangle = _bitmap_draw_class_t_draw_rectangle_list[_instance_index];
    ret->draw_circle = _bitmap_draw_class_t_draw_circle_list[_instance_index];
    ret->draw_circle_arc = _bitmap_draw_class_t_draw_circle_arc_list[_instance_index];
    ret->flood_fill = _bitmap_draw_class_t_flood_fill_list[_instance_index];
    ret->set_bitmap_rgb = _bitmap_draw_class_t_set_bitmap_rgb_list[_instance_index];
    ret->get_bitmap_rgb = _bitmap_draw_class_t_get_bitmap_rgb_list[_instance_index];
    api_bitmap_draw_class_t_class->creator_bitmap( ret, bitmap_class );
    ret->__default_del = _bitmap_draw_class_t_delete_bitmap_list[_instance_index];
    return ret;
}

void * _instance_new_bitmap_draw_class_t( bitmap_class_t * bitmap_class )
{
    return _instance_new_bitmap_draw_class_t_ex( api_bitmap_draw_class_t_class, bitmap_class );
}

void * _instance_static_bitmap_draw_class_t_method( void * __api )
{
    return api_bitmap_draw_class_t_class;
}

#if 0 // method definition for bitmap_draw_class_t

#include "bitmap_draw_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator_bitmap( bitmap_draw_class_t * p_data, bitmap_class_t * bitmap_class )
{
}

DELETE static void delete_bitmap( bitmap_draw_class_t * p_data )
{
}

METHOD static void fill_box( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
}

METHOD static void draw_line( bitmap_draw_class_t * p_data, uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, pixel_t colour )
{
}

METHOD static void draw_rectangle( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t colour )
{
}

METHOD static void draw_circle( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, int ratio, pixel_t colour )
{
}

METHOD static void draw_circle_arc( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, int ratio, int start, int end, pixel_t colour )
{
}

METHOD static void flood_fill( bitmap_draw_class_t * p_data, uint16_t x, uint16_t y, pixel_t colour )
{
}

METHOD static void set_bitmap_rgb( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data, pixel_t transparent, bool_t use_transparent )
{
}

METHOD static void get_bitmap_rgb( bitmap_draw_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t height, pixel_t * data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_draw_class_t );

////////////////////////////////////////////////////////////////////

#endif // bitmap_draw_class_t

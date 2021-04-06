#include "draw_text_class_private.h"
#include "draw_text_class.h"

////////////////////////////////////////////////////////////////////

api_text_bitmap_class_t * api_text_bitmap_class_t_class = NULL;

static text_bitmap_class_t * _instance_list_text_bitmap_class_t[64] = {0};

typedef void ( *text_bitmap_class_t_delete_t )( void );

static void text_bitmap_class_t_delete_instance_00( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->delete( _instance_list_text_bitmap_class_t[ 0] ); }
static void text_bitmap_class_t_delete_instance_01( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->delete( _instance_list_text_bitmap_class_t[ 1] ); }
static void text_bitmap_class_t_delete_instance_02( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->delete( _instance_list_text_bitmap_class_t[ 2] ); }
static void text_bitmap_class_t_delete_instance_03( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->delete( _instance_list_text_bitmap_class_t[ 3] ); }
static void text_bitmap_class_t_delete_instance_04( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->delete( _instance_list_text_bitmap_class_t[ 4] ); }
static void text_bitmap_class_t_delete_instance_05( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->delete( _instance_list_text_bitmap_class_t[ 5] ); }
static void text_bitmap_class_t_delete_instance_06( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->delete( _instance_list_text_bitmap_class_t[ 6] ); }
static void text_bitmap_class_t_delete_instance_07( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->delete( _instance_list_text_bitmap_class_t[ 7] ); }
static void text_bitmap_class_t_delete_instance_08( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->delete( _instance_list_text_bitmap_class_t[ 8] ); }
static void text_bitmap_class_t_delete_instance_09( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->delete( _instance_list_text_bitmap_class_t[ 9] ); }
static void text_bitmap_class_t_delete_instance_10( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->delete( _instance_list_text_bitmap_class_t[10] ); }
static void text_bitmap_class_t_delete_instance_11( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->delete( _instance_list_text_bitmap_class_t[11] ); }
static void text_bitmap_class_t_delete_instance_12( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->delete( _instance_list_text_bitmap_class_t[12] ); }
static void text_bitmap_class_t_delete_instance_13( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->delete( _instance_list_text_bitmap_class_t[13] ); }
static void text_bitmap_class_t_delete_instance_14( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->delete( _instance_list_text_bitmap_class_t[14] ); }
static void text_bitmap_class_t_delete_instance_15( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->delete( _instance_list_text_bitmap_class_t[15] ); }
static void text_bitmap_class_t_delete_instance_16( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->delete( _instance_list_text_bitmap_class_t[16] ); }
static void text_bitmap_class_t_delete_instance_17( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->delete( _instance_list_text_bitmap_class_t[17] ); }
static void text_bitmap_class_t_delete_instance_18( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->delete( _instance_list_text_bitmap_class_t[18] ); }
static void text_bitmap_class_t_delete_instance_19( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->delete( _instance_list_text_bitmap_class_t[19] ); }
static void text_bitmap_class_t_delete_instance_20( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->delete( _instance_list_text_bitmap_class_t[20] ); }
static void text_bitmap_class_t_delete_instance_21( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->delete( _instance_list_text_bitmap_class_t[21] ); }
static void text_bitmap_class_t_delete_instance_22( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->delete( _instance_list_text_bitmap_class_t[22] ); }
static void text_bitmap_class_t_delete_instance_23( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->delete( _instance_list_text_bitmap_class_t[23] ); }
static void text_bitmap_class_t_delete_instance_24( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->delete( _instance_list_text_bitmap_class_t[24] ); }
static void text_bitmap_class_t_delete_instance_25( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->delete( _instance_list_text_bitmap_class_t[25] ); }
static void text_bitmap_class_t_delete_instance_26( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->delete( _instance_list_text_bitmap_class_t[26] ); }
static void text_bitmap_class_t_delete_instance_27( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->delete( _instance_list_text_bitmap_class_t[27] ); }
static void text_bitmap_class_t_delete_instance_28( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->delete( _instance_list_text_bitmap_class_t[28] ); }
static void text_bitmap_class_t_delete_instance_29( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->delete( _instance_list_text_bitmap_class_t[29] ); }
static void text_bitmap_class_t_delete_instance_30( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->delete( _instance_list_text_bitmap_class_t[30] ); }
static void text_bitmap_class_t_delete_instance_31( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->delete( _instance_list_text_bitmap_class_t[31] ); }
static void text_bitmap_class_t_delete_instance_32( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->delete( _instance_list_text_bitmap_class_t[32] ); }
static void text_bitmap_class_t_delete_instance_33( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->delete( _instance_list_text_bitmap_class_t[33] ); }
static void text_bitmap_class_t_delete_instance_34( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->delete( _instance_list_text_bitmap_class_t[34] ); }
static void text_bitmap_class_t_delete_instance_35( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->delete( _instance_list_text_bitmap_class_t[35] ); }
static void text_bitmap_class_t_delete_instance_36( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->delete( _instance_list_text_bitmap_class_t[36] ); }
static void text_bitmap_class_t_delete_instance_37( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->delete( _instance_list_text_bitmap_class_t[37] ); }
static void text_bitmap_class_t_delete_instance_38( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->delete( _instance_list_text_bitmap_class_t[38] ); }
static void text_bitmap_class_t_delete_instance_39( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->delete( _instance_list_text_bitmap_class_t[39] ); }
static void text_bitmap_class_t_delete_instance_40( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->delete( _instance_list_text_bitmap_class_t[40] ); }
static void text_bitmap_class_t_delete_instance_41( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->delete( _instance_list_text_bitmap_class_t[41] ); }
static void text_bitmap_class_t_delete_instance_42( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->delete( _instance_list_text_bitmap_class_t[42] ); }
static void text_bitmap_class_t_delete_instance_43( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->delete( _instance_list_text_bitmap_class_t[43] ); }
static void text_bitmap_class_t_delete_instance_44( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->delete( _instance_list_text_bitmap_class_t[44] ); }
static void text_bitmap_class_t_delete_instance_45( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->delete( _instance_list_text_bitmap_class_t[45] ); }
static void text_bitmap_class_t_delete_instance_46( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->delete( _instance_list_text_bitmap_class_t[46] ); }
static void text_bitmap_class_t_delete_instance_47( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->delete( _instance_list_text_bitmap_class_t[47] ); }
static void text_bitmap_class_t_delete_instance_48( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->delete( _instance_list_text_bitmap_class_t[48] ); }
static void text_bitmap_class_t_delete_instance_49( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->delete( _instance_list_text_bitmap_class_t[49] ); }
static void text_bitmap_class_t_delete_instance_50( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->delete( _instance_list_text_bitmap_class_t[50] ); }
static void text_bitmap_class_t_delete_instance_51( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->delete( _instance_list_text_bitmap_class_t[51] ); }
static void text_bitmap_class_t_delete_instance_52( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->delete( _instance_list_text_bitmap_class_t[52] ); }
static void text_bitmap_class_t_delete_instance_53( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->delete( _instance_list_text_bitmap_class_t[53] ); }
static void text_bitmap_class_t_delete_instance_54( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->delete( _instance_list_text_bitmap_class_t[54] ); }
static void text_bitmap_class_t_delete_instance_55( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->delete( _instance_list_text_bitmap_class_t[55] ); }
static void text_bitmap_class_t_delete_instance_56( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->delete( _instance_list_text_bitmap_class_t[56] ); }
static void text_bitmap_class_t_delete_instance_57( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->delete( _instance_list_text_bitmap_class_t[57] ); }
static void text_bitmap_class_t_delete_instance_58( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->delete( _instance_list_text_bitmap_class_t[58] ); }
static void text_bitmap_class_t_delete_instance_59( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->delete( _instance_list_text_bitmap_class_t[59] ); }
static void text_bitmap_class_t_delete_instance_60( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->delete( _instance_list_text_bitmap_class_t[60] ); }
static void text_bitmap_class_t_delete_instance_61( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->delete( _instance_list_text_bitmap_class_t[61] ); }
static void text_bitmap_class_t_delete_instance_62( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->delete( _instance_list_text_bitmap_class_t[62] ); }
static void text_bitmap_class_t_delete_instance_63( void ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->delete( _instance_list_text_bitmap_class_t[63] ); }

static const text_bitmap_class_t_delete_t _text_bitmap_class_t_delete_list[64] =
{
    text_bitmap_class_t_delete_instance_00,
    text_bitmap_class_t_delete_instance_01,
    text_bitmap_class_t_delete_instance_02,
    text_bitmap_class_t_delete_instance_03,
    text_bitmap_class_t_delete_instance_04,
    text_bitmap_class_t_delete_instance_05,
    text_bitmap_class_t_delete_instance_06,
    text_bitmap_class_t_delete_instance_07,
    text_bitmap_class_t_delete_instance_08,
    text_bitmap_class_t_delete_instance_09,
    text_bitmap_class_t_delete_instance_10,
    text_bitmap_class_t_delete_instance_11,
    text_bitmap_class_t_delete_instance_12,
    text_bitmap_class_t_delete_instance_13,
    text_bitmap_class_t_delete_instance_14,
    text_bitmap_class_t_delete_instance_15,
    text_bitmap_class_t_delete_instance_16,
    text_bitmap_class_t_delete_instance_17,
    text_bitmap_class_t_delete_instance_18,
    text_bitmap_class_t_delete_instance_19,
    text_bitmap_class_t_delete_instance_20,
    text_bitmap_class_t_delete_instance_21,
    text_bitmap_class_t_delete_instance_22,
    text_bitmap_class_t_delete_instance_23,
    text_bitmap_class_t_delete_instance_24,
    text_bitmap_class_t_delete_instance_25,
    text_bitmap_class_t_delete_instance_26,
    text_bitmap_class_t_delete_instance_27,
    text_bitmap_class_t_delete_instance_28,
    text_bitmap_class_t_delete_instance_29,
    text_bitmap_class_t_delete_instance_30,
    text_bitmap_class_t_delete_instance_31,
    text_bitmap_class_t_delete_instance_32,
    text_bitmap_class_t_delete_instance_33,
    text_bitmap_class_t_delete_instance_34,
    text_bitmap_class_t_delete_instance_35,
    text_bitmap_class_t_delete_instance_36,
    text_bitmap_class_t_delete_instance_37,
    text_bitmap_class_t_delete_instance_38,
    text_bitmap_class_t_delete_instance_39,
    text_bitmap_class_t_delete_instance_40,
    text_bitmap_class_t_delete_instance_41,
    text_bitmap_class_t_delete_instance_42,
    text_bitmap_class_t_delete_instance_43,
    text_bitmap_class_t_delete_instance_44,
    text_bitmap_class_t_delete_instance_45,
    text_bitmap_class_t_delete_instance_46,
    text_bitmap_class_t_delete_instance_47,
    text_bitmap_class_t_delete_instance_48,
    text_bitmap_class_t_delete_instance_49,
    text_bitmap_class_t_delete_instance_50,
    text_bitmap_class_t_delete_instance_51,
    text_bitmap_class_t_delete_instance_52,
    text_bitmap_class_t_delete_instance_53,
    text_bitmap_class_t_delete_instance_54,
    text_bitmap_class_t_delete_instance_55,
    text_bitmap_class_t_delete_instance_56,
    text_bitmap_class_t_delete_instance_57,
    text_bitmap_class_t_delete_instance_58,
    text_bitmap_class_t_delete_instance_59,
    text_bitmap_class_t_delete_instance_60,
    text_bitmap_class_t_delete_instance_61,
    text_bitmap_class_t_delete_instance_62,
    text_bitmap_class_t_delete_instance_63,
};

typedef void ( *text_bitmap_class_t_set_text_t )( char * text );

static void text_bitmap_class_t_set_text_instance_00( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->set_text( _instance_list_text_bitmap_class_t[ 0], text ); }
static void text_bitmap_class_t_set_text_instance_01( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->set_text( _instance_list_text_bitmap_class_t[ 1], text ); }
static void text_bitmap_class_t_set_text_instance_02( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->set_text( _instance_list_text_bitmap_class_t[ 2], text ); }
static void text_bitmap_class_t_set_text_instance_03( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->set_text( _instance_list_text_bitmap_class_t[ 3], text ); }
static void text_bitmap_class_t_set_text_instance_04( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->set_text( _instance_list_text_bitmap_class_t[ 4], text ); }
static void text_bitmap_class_t_set_text_instance_05( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->set_text( _instance_list_text_bitmap_class_t[ 5], text ); }
static void text_bitmap_class_t_set_text_instance_06( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->set_text( _instance_list_text_bitmap_class_t[ 6], text ); }
static void text_bitmap_class_t_set_text_instance_07( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->set_text( _instance_list_text_bitmap_class_t[ 7], text ); }
static void text_bitmap_class_t_set_text_instance_08( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->set_text( _instance_list_text_bitmap_class_t[ 8], text ); }
static void text_bitmap_class_t_set_text_instance_09( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->set_text( _instance_list_text_bitmap_class_t[ 9], text ); }
static void text_bitmap_class_t_set_text_instance_10( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->set_text( _instance_list_text_bitmap_class_t[10], text ); }
static void text_bitmap_class_t_set_text_instance_11( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->set_text( _instance_list_text_bitmap_class_t[11], text ); }
static void text_bitmap_class_t_set_text_instance_12( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->set_text( _instance_list_text_bitmap_class_t[12], text ); }
static void text_bitmap_class_t_set_text_instance_13( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->set_text( _instance_list_text_bitmap_class_t[13], text ); }
static void text_bitmap_class_t_set_text_instance_14( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->set_text( _instance_list_text_bitmap_class_t[14], text ); }
static void text_bitmap_class_t_set_text_instance_15( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->set_text( _instance_list_text_bitmap_class_t[15], text ); }
static void text_bitmap_class_t_set_text_instance_16( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->set_text( _instance_list_text_bitmap_class_t[16], text ); }
static void text_bitmap_class_t_set_text_instance_17( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->set_text( _instance_list_text_bitmap_class_t[17], text ); }
static void text_bitmap_class_t_set_text_instance_18( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->set_text( _instance_list_text_bitmap_class_t[18], text ); }
static void text_bitmap_class_t_set_text_instance_19( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->set_text( _instance_list_text_bitmap_class_t[19], text ); }
static void text_bitmap_class_t_set_text_instance_20( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->set_text( _instance_list_text_bitmap_class_t[20], text ); }
static void text_bitmap_class_t_set_text_instance_21( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->set_text( _instance_list_text_bitmap_class_t[21], text ); }
static void text_bitmap_class_t_set_text_instance_22( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->set_text( _instance_list_text_bitmap_class_t[22], text ); }
static void text_bitmap_class_t_set_text_instance_23( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->set_text( _instance_list_text_bitmap_class_t[23], text ); }
static void text_bitmap_class_t_set_text_instance_24( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->set_text( _instance_list_text_bitmap_class_t[24], text ); }
static void text_bitmap_class_t_set_text_instance_25( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->set_text( _instance_list_text_bitmap_class_t[25], text ); }
static void text_bitmap_class_t_set_text_instance_26( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->set_text( _instance_list_text_bitmap_class_t[26], text ); }
static void text_bitmap_class_t_set_text_instance_27( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->set_text( _instance_list_text_bitmap_class_t[27], text ); }
static void text_bitmap_class_t_set_text_instance_28( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->set_text( _instance_list_text_bitmap_class_t[28], text ); }
static void text_bitmap_class_t_set_text_instance_29( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->set_text( _instance_list_text_bitmap_class_t[29], text ); }
static void text_bitmap_class_t_set_text_instance_30( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->set_text( _instance_list_text_bitmap_class_t[30], text ); }
static void text_bitmap_class_t_set_text_instance_31( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->set_text( _instance_list_text_bitmap_class_t[31], text ); }
static void text_bitmap_class_t_set_text_instance_32( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->set_text( _instance_list_text_bitmap_class_t[32], text ); }
static void text_bitmap_class_t_set_text_instance_33( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->set_text( _instance_list_text_bitmap_class_t[33], text ); }
static void text_bitmap_class_t_set_text_instance_34( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->set_text( _instance_list_text_bitmap_class_t[34], text ); }
static void text_bitmap_class_t_set_text_instance_35( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->set_text( _instance_list_text_bitmap_class_t[35], text ); }
static void text_bitmap_class_t_set_text_instance_36( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->set_text( _instance_list_text_bitmap_class_t[36], text ); }
static void text_bitmap_class_t_set_text_instance_37( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->set_text( _instance_list_text_bitmap_class_t[37], text ); }
static void text_bitmap_class_t_set_text_instance_38( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->set_text( _instance_list_text_bitmap_class_t[38], text ); }
static void text_bitmap_class_t_set_text_instance_39( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->set_text( _instance_list_text_bitmap_class_t[39], text ); }
static void text_bitmap_class_t_set_text_instance_40( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->set_text( _instance_list_text_bitmap_class_t[40], text ); }
static void text_bitmap_class_t_set_text_instance_41( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->set_text( _instance_list_text_bitmap_class_t[41], text ); }
static void text_bitmap_class_t_set_text_instance_42( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->set_text( _instance_list_text_bitmap_class_t[42], text ); }
static void text_bitmap_class_t_set_text_instance_43( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->set_text( _instance_list_text_bitmap_class_t[43], text ); }
static void text_bitmap_class_t_set_text_instance_44( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->set_text( _instance_list_text_bitmap_class_t[44], text ); }
static void text_bitmap_class_t_set_text_instance_45( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->set_text( _instance_list_text_bitmap_class_t[45], text ); }
static void text_bitmap_class_t_set_text_instance_46( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->set_text( _instance_list_text_bitmap_class_t[46], text ); }
static void text_bitmap_class_t_set_text_instance_47( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->set_text( _instance_list_text_bitmap_class_t[47], text ); }
static void text_bitmap_class_t_set_text_instance_48( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->set_text( _instance_list_text_bitmap_class_t[48], text ); }
static void text_bitmap_class_t_set_text_instance_49( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->set_text( _instance_list_text_bitmap_class_t[49], text ); }
static void text_bitmap_class_t_set_text_instance_50( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->set_text( _instance_list_text_bitmap_class_t[50], text ); }
static void text_bitmap_class_t_set_text_instance_51( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->set_text( _instance_list_text_bitmap_class_t[51], text ); }
static void text_bitmap_class_t_set_text_instance_52( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->set_text( _instance_list_text_bitmap_class_t[52], text ); }
static void text_bitmap_class_t_set_text_instance_53( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->set_text( _instance_list_text_bitmap_class_t[53], text ); }
static void text_bitmap_class_t_set_text_instance_54( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->set_text( _instance_list_text_bitmap_class_t[54], text ); }
static void text_bitmap_class_t_set_text_instance_55( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->set_text( _instance_list_text_bitmap_class_t[55], text ); }
static void text_bitmap_class_t_set_text_instance_56( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->set_text( _instance_list_text_bitmap_class_t[56], text ); }
static void text_bitmap_class_t_set_text_instance_57( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->set_text( _instance_list_text_bitmap_class_t[57], text ); }
static void text_bitmap_class_t_set_text_instance_58( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->set_text( _instance_list_text_bitmap_class_t[58], text ); }
static void text_bitmap_class_t_set_text_instance_59( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->set_text( _instance_list_text_bitmap_class_t[59], text ); }
static void text_bitmap_class_t_set_text_instance_60( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->set_text( _instance_list_text_bitmap_class_t[60], text ); }
static void text_bitmap_class_t_set_text_instance_61( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->set_text( _instance_list_text_bitmap_class_t[61], text ); }
static void text_bitmap_class_t_set_text_instance_62( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->set_text( _instance_list_text_bitmap_class_t[62], text ); }
static void text_bitmap_class_t_set_text_instance_63( char * text ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->set_text( _instance_list_text_bitmap_class_t[63], text ); }

static const text_bitmap_class_t_set_text_t _text_bitmap_class_t_set_text_list[64] =
{
    text_bitmap_class_t_set_text_instance_00,
    text_bitmap_class_t_set_text_instance_01,
    text_bitmap_class_t_set_text_instance_02,
    text_bitmap_class_t_set_text_instance_03,
    text_bitmap_class_t_set_text_instance_04,
    text_bitmap_class_t_set_text_instance_05,
    text_bitmap_class_t_set_text_instance_06,
    text_bitmap_class_t_set_text_instance_07,
    text_bitmap_class_t_set_text_instance_08,
    text_bitmap_class_t_set_text_instance_09,
    text_bitmap_class_t_set_text_instance_10,
    text_bitmap_class_t_set_text_instance_11,
    text_bitmap_class_t_set_text_instance_12,
    text_bitmap_class_t_set_text_instance_13,
    text_bitmap_class_t_set_text_instance_14,
    text_bitmap_class_t_set_text_instance_15,
    text_bitmap_class_t_set_text_instance_16,
    text_bitmap_class_t_set_text_instance_17,
    text_bitmap_class_t_set_text_instance_18,
    text_bitmap_class_t_set_text_instance_19,
    text_bitmap_class_t_set_text_instance_20,
    text_bitmap_class_t_set_text_instance_21,
    text_bitmap_class_t_set_text_instance_22,
    text_bitmap_class_t_set_text_instance_23,
    text_bitmap_class_t_set_text_instance_24,
    text_bitmap_class_t_set_text_instance_25,
    text_bitmap_class_t_set_text_instance_26,
    text_bitmap_class_t_set_text_instance_27,
    text_bitmap_class_t_set_text_instance_28,
    text_bitmap_class_t_set_text_instance_29,
    text_bitmap_class_t_set_text_instance_30,
    text_bitmap_class_t_set_text_instance_31,
    text_bitmap_class_t_set_text_instance_32,
    text_bitmap_class_t_set_text_instance_33,
    text_bitmap_class_t_set_text_instance_34,
    text_bitmap_class_t_set_text_instance_35,
    text_bitmap_class_t_set_text_instance_36,
    text_bitmap_class_t_set_text_instance_37,
    text_bitmap_class_t_set_text_instance_38,
    text_bitmap_class_t_set_text_instance_39,
    text_bitmap_class_t_set_text_instance_40,
    text_bitmap_class_t_set_text_instance_41,
    text_bitmap_class_t_set_text_instance_42,
    text_bitmap_class_t_set_text_instance_43,
    text_bitmap_class_t_set_text_instance_44,
    text_bitmap_class_t_set_text_instance_45,
    text_bitmap_class_t_set_text_instance_46,
    text_bitmap_class_t_set_text_instance_47,
    text_bitmap_class_t_set_text_instance_48,
    text_bitmap_class_t_set_text_instance_49,
    text_bitmap_class_t_set_text_instance_50,
    text_bitmap_class_t_set_text_instance_51,
    text_bitmap_class_t_set_text_instance_52,
    text_bitmap_class_t_set_text_instance_53,
    text_bitmap_class_t_set_text_instance_54,
    text_bitmap_class_t_set_text_instance_55,
    text_bitmap_class_t_set_text_instance_56,
    text_bitmap_class_t_set_text_instance_57,
    text_bitmap_class_t_set_text_instance_58,
    text_bitmap_class_t_set_text_instance_59,
    text_bitmap_class_t_set_text_instance_60,
    text_bitmap_class_t_set_text_instance_61,
    text_bitmap_class_t_set_text_instance_62,
    text_bitmap_class_t_set_text_instance_63,
};

typedef void ( *text_bitmap_class_t_draw_t )( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );

static void text_bitmap_class_t_draw_instance_00( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->draw( _instance_list_text_bitmap_class_t[ 0], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_01( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->draw( _instance_list_text_bitmap_class_t[ 1], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_02( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->draw( _instance_list_text_bitmap_class_t[ 2], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_03( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->draw( _instance_list_text_bitmap_class_t[ 3], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_04( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->draw( _instance_list_text_bitmap_class_t[ 4], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_05( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->draw( _instance_list_text_bitmap_class_t[ 5], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_06( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->draw( _instance_list_text_bitmap_class_t[ 6], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_07( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->draw( _instance_list_text_bitmap_class_t[ 7], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_08( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->draw( _instance_list_text_bitmap_class_t[ 8], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_09( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->draw( _instance_list_text_bitmap_class_t[ 9], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_10( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->draw( _instance_list_text_bitmap_class_t[10], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_11( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->draw( _instance_list_text_bitmap_class_t[11], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_12( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->draw( _instance_list_text_bitmap_class_t[12], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_13( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->draw( _instance_list_text_bitmap_class_t[13], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_14( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->draw( _instance_list_text_bitmap_class_t[14], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_15( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->draw( _instance_list_text_bitmap_class_t[15], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_16( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->draw( _instance_list_text_bitmap_class_t[16], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_17( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->draw( _instance_list_text_bitmap_class_t[17], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_18( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->draw( _instance_list_text_bitmap_class_t[18], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_19( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->draw( _instance_list_text_bitmap_class_t[19], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_20( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->draw( _instance_list_text_bitmap_class_t[20], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_21( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->draw( _instance_list_text_bitmap_class_t[21], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_22( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->draw( _instance_list_text_bitmap_class_t[22], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_23( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->draw( _instance_list_text_bitmap_class_t[23], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_24( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->draw( _instance_list_text_bitmap_class_t[24], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_25( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->draw( _instance_list_text_bitmap_class_t[25], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_26( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->draw( _instance_list_text_bitmap_class_t[26], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_27( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->draw( _instance_list_text_bitmap_class_t[27], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_28( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->draw( _instance_list_text_bitmap_class_t[28], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_29( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->draw( _instance_list_text_bitmap_class_t[29], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_30( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->draw( _instance_list_text_bitmap_class_t[30], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_31( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->draw( _instance_list_text_bitmap_class_t[31], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_32( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->draw( _instance_list_text_bitmap_class_t[32], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_33( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->draw( _instance_list_text_bitmap_class_t[33], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_34( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->draw( _instance_list_text_bitmap_class_t[34], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_35( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->draw( _instance_list_text_bitmap_class_t[35], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_36( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->draw( _instance_list_text_bitmap_class_t[36], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_37( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->draw( _instance_list_text_bitmap_class_t[37], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_38( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->draw( _instance_list_text_bitmap_class_t[38], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_39( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->draw( _instance_list_text_bitmap_class_t[39], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_40( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->draw( _instance_list_text_bitmap_class_t[40], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_41( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->draw( _instance_list_text_bitmap_class_t[41], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_42( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->draw( _instance_list_text_bitmap_class_t[42], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_43( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->draw( _instance_list_text_bitmap_class_t[43], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_44( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->draw( _instance_list_text_bitmap_class_t[44], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_45( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->draw( _instance_list_text_bitmap_class_t[45], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_46( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->draw( _instance_list_text_bitmap_class_t[46], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_47( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->draw( _instance_list_text_bitmap_class_t[47], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_48( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->draw( _instance_list_text_bitmap_class_t[48], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_49( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->draw( _instance_list_text_bitmap_class_t[49], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_50( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->draw( _instance_list_text_bitmap_class_t[50], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_51( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->draw( _instance_list_text_bitmap_class_t[51], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_52( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->draw( _instance_list_text_bitmap_class_t[52], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_53( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->draw( _instance_list_text_bitmap_class_t[53], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_54( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->draw( _instance_list_text_bitmap_class_t[54], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_55( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->draw( _instance_list_text_bitmap_class_t[55], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_56( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->draw( _instance_list_text_bitmap_class_t[56], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_57( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->draw( _instance_list_text_bitmap_class_t[57], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_58( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->draw( _instance_list_text_bitmap_class_t[58], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_59( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->draw( _instance_list_text_bitmap_class_t[59], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_60( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->draw( _instance_list_text_bitmap_class_t[60], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_61( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->draw( _instance_list_text_bitmap_class_t[61], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_62( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->draw( _instance_list_text_bitmap_class_t[62], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_instance_63( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->draw( _instance_list_text_bitmap_class_t[63], posx, posy, fore_colour, back_colour ); }

static const text_bitmap_class_t_draw_t _text_bitmap_class_t_draw_list[64] =
{
    text_bitmap_class_t_draw_instance_00,
    text_bitmap_class_t_draw_instance_01,
    text_bitmap_class_t_draw_instance_02,
    text_bitmap_class_t_draw_instance_03,
    text_bitmap_class_t_draw_instance_04,
    text_bitmap_class_t_draw_instance_05,
    text_bitmap_class_t_draw_instance_06,
    text_bitmap_class_t_draw_instance_07,
    text_bitmap_class_t_draw_instance_08,
    text_bitmap_class_t_draw_instance_09,
    text_bitmap_class_t_draw_instance_10,
    text_bitmap_class_t_draw_instance_11,
    text_bitmap_class_t_draw_instance_12,
    text_bitmap_class_t_draw_instance_13,
    text_bitmap_class_t_draw_instance_14,
    text_bitmap_class_t_draw_instance_15,
    text_bitmap_class_t_draw_instance_16,
    text_bitmap_class_t_draw_instance_17,
    text_bitmap_class_t_draw_instance_18,
    text_bitmap_class_t_draw_instance_19,
    text_bitmap_class_t_draw_instance_20,
    text_bitmap_class_t_draw_instance_21,
    text_bitmap_class_t_draw_instance_22,
    text_bitmap_class_t_draw_instance_23,
    text_bitmap_class_t_draw_instance_24,
    text_bitmap_class_t_draw_instance_25,
    text_bitmap_class_t_draw_instance_26,
    text_bitmap_class_t_draw_instance_27,
    text_bitmap_class_t_draw_instance_28,
    text_bitmap_class_t_draw_instance_29,
    text_bitmap_class_t_draw_instance_30,
    text_bitmap_class_t_draw_instance_31,
    text_bitmap_class_t_draw_instance_32,
    text_bitmap_class_t_draw_instance_33,
    text_bitmap_class_t_draw_instance_34,
    text_bitmap_class_t_draw_instance_35,
    text_bitmap_class_t_draw_instance_36,
    text_bitmap_class_t_draw_instance_37,
    text_bitmap_class_t_draw_instance_38,
    text_bitmap_class_t_draw_instance_39,
    text_bitmap_class_t_draw_instance_40,
    text_bitmap_class_t_draw_instance_41,
    text_bitmap_class_t_draw_instance_42,
    text_bitmap_class_t_draw_instance_43,
    text_bitmap_class_t_draw_instance_44,
    text_bitmap_class_t_draw_instance_45,
    text_bitmap_class_t_draw_instance_46,
    text_bitmap_class_t_draw_instance_47,
    text_bitmap_class_t_draw_instance_48,
    text_bitmap_class_t_draw_instance_49,
    text_bitmap_class_t_draw_instance_50,
    text_bitmap_class_t_draw_instance_51,
    text_bitmap_class_t_draw_instance_52,
    text_bitmap_class_t_draw_instance_53,
    text_bitmap_class_t_draw_instance_54,
    text_bitmap_class_t_draw_instance_55,
    text_bitmap_class_t_draw_instance_56,
    text_bitmap_class_t_draw_instance_57,
    text_bitmap_class_t_draw_instance_58,
    text_bitmap_class_t_draw_instance_59,
    text_bitmap_class_t_draw_instance_60,
    text_bitmap_class_t_draw_instance_61,
    text_bitmap_class_t_draw_instance_62,
    text_bitmap_class_t_draw_instance_63,
};

typedef void ( *text_bitmap_class_t_draw_vertical_t )( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour );

static void text_bitmap_class_t_draw_vertical_instance_00( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 0], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_01( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 1], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_02( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 2], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_03( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 3], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_04( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 4], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_05( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 5], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_06( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 6], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_07( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 7], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_08( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 8], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_09( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[ 9], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_10( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[10], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_11( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[11], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_12( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[12], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_13( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[13], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_14( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[14], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_15( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[15], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_16( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[16], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_17( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[17], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_18( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[18], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_19( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[19], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_20( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[20], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_21( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[21], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_22( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[22], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_23( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[23], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_24( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[24], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_25( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[25], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_26( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[26], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_27( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[27], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_28( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[28], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_29( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[29], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_30( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[30], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_31( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[31], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_32( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[32], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_33( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[33], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_34( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[34], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_35( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[35], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_36( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[36], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_37( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[37], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_38( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[38], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_39( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[39], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_40( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[40], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_41( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[41], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_42( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[42], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_43( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[43], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_44( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[44], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_45( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[45], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_46( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[46], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_47( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[47], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_48( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[48], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_49( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[49], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_50( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[50], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_51( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[51], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_52( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[52], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_53( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[53], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_54( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[54], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_55( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[55], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_56( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[56], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_57( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[57], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_58( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[58], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_59( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[59], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_60( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[60], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_61( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[61], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_62( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[62], posx, posy, fore_colour, back_colour ); }
static void text_bitmap_class_t_draw_vertical_instance_63( uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour ){ ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->draw_vertical( _instance_list_text_bitmap_class_t[63], posx, posy, fore_colour, back_colour ); }

static const text_bitmap_class_t_draw_vertical_t _text_bitmap_class_t_draw_vertical_list[64] =
{
    text_bitmap_class_t_draw_vertical_instance_00,
    text_bitmap_class_t_draw_vertical_instance_01,
    text_bitmap_class_t_draw_vertical_instance_02,
    text_bitmap_class_t_draw_vertical_instance_03,
    text_bitmap_class_t_draw_vertical_instance_04,
    text_bitmap_class_t_draw_vertical_instance_05,
    text_bitmap_class_t_draw_vertical_instance_06,
    text_bitmap_class_t_draw_vertical_instance_07,
    text_bitmap_class_t_draw_vertical_instance_08,
    text_bitmap_class_t_draw_vertical_instance_09,
    text_bitmap_class_t_draw_vertical_instance_10,
    text_bitmap_class_t_draw_vertical_instance_11,
    text_bitmap_class_t_draw_vertical_instance_12,
    text_bitmap_class_t_draw_vertical_instance_13,
    text_bitmap_class_t_draw_vertical_instance_14,
    text_bitmap_class_t_draw_vertical_instance_15,
    text_bitmap_class_t_draw_vertical_instance_16,
    text_bitmap_class_t_draw_vertical_instance_17,
    text_bitmap_class_t_draw_vertical_instance_18,
    text_bitmap_class_t_draw_vertical_instance_19,
    text_bitmap_class_t_draw_vertical_instance_20,
    text_bitmap_class_t_draw_vertical_instance_21,
    text_bitmap_class_t_draw_vertical_instance_22,
    text_bitmap_class_t_draw_vertical_instance_23,
    text_bitmap_class_t_draw_vertical_instance_24,
    text_bitmap_class_t_draw_vertical_instance_25,
    text_bitmap_class_t_draw_vertical_instance_26,
    text_bitmap_class_t_draw_vertical_instance_27,
    text_bitmap_class_t_draw_vertical_instance_28,
    text_bitmap_class_t_draw_vertical_instance_29,
    text_bitmap_class_t_draw_vertical_instance_30,
    text_bitmap_class_t_draw_vertical_instance_31,
    text_bitmap_class_t_draw_vertical_instance_32,
    text_bitmap_class_t_draw_vertical_instance_33,
    text_bitmap_class_t_draw_vertical_instance_34,
    text_bitmap_class_t_draw_vertical_instance_35,
    text_bitmap_class_t_draw_vertical_instance_36,
    text_bitmap_class_t_draw_vertical_instance_37,
    text_bitmap_class_t_draw_vertical_instance_38,
    text_bitmap_class_t_draw_vertical_instance_39,
    text_bitmap_class_t_draw_vertical_instance_40,
    text_bitmap_class_t_draw_vertical_instance_41,
    text_bitmap_class_t_draw_vertical_instance_42,
    text_bitmap_class_t_draw_vertical_instance_43,
    text_bitmap_class_t_draw_vertical_instance_44,
    text_bitmap_class_t_draw_vertical_instance_45,
    text_bitmap_class_t_draw_vertical_instance_46,
    text_bitmap_class_t_draw_vertical_instance_47,
    text_bitmap_class_t_draw_vertical_instance_48,
    text_bitmap_class_t_draw_vertical_instance_49,
    text_bitmap_class_t_draw_vertical_instance_50,
    text_bitmap_class_t_draw_vertical_instance_51,
    text_bitmap_class_t_draw_vertical_instance_52,
    text_bitmap_class_t_draw_vertical_instance_53,
    text_bitmap_class_t_draw_vertical_instance_54,
    text_bitmap_class_t_draw_vertical_instance_55,
    text_bitmap_class_t_draw_vertical_instance_56,
    text_bitmap_class_t_draw_vertical_instance_57,
    text_bitmap_class_t_draw_vertical_instance_58,
    text_bitmap_class_t_draw_vertical_instance_59,
    text_bitmap_class_t_draw_vertical_instance_60,
    text_bitmap_class_t_draw_vertical_instance_61,
    text_bitmap_class_t_draw_vertical_instance_62,
    text_bitmap_class_t_draw_vertical_instance_63,
};

typedef uint16_t ( *text_bitmap_class_t_get_width_t )( void );

static uint16_t text_bitmap_class_t_get_width_instance_00( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->get_width( _instance_list_text_bitmap_class_t[ 0] ); }
static uint16_t text_bitmap_class_t_get_width_instance_01( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->get_width( _instance_list_text_bitmap_class_t[ 1] ); }
static uint16_t text_bitmap_class_t_get_width_instance_02( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->get_width( _instance_list_text_bitmap_class_t[ 2] ); }
static uint16_t text_bitmap_class_t_get_width_instance_03( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->get_width( _instance_list_text_bitmap_class_t[ 3] ); }
static uint16_t text_bitmap_class_t_get_width_instance_04( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->get_width( _instance_list_text_bitmap_class_t[ 4] ); }
static uint16_t text_bitmap_class_t_get_width_instance_05( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->get_width( _instance_list_text_bitmap_class_t[ 5] ); }
static uint16_t text_bitmap_class_t_get_width_instance_06( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->get_width( _instance_list_text_bitmap_class_t[ 6] ); }
static uint16_t text_bitmap_class_t_get_width_instance_07( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->get_width( _instance_list_text_bitmap_class_t[ 7] ); }
static uint16_t text_bitmap_class_t_get_width_instance_08( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->get_width( _instance_list_text_bitmap_class_t[ 8] ); }
static uint16_t text_bitmap_class_t_get_width_instance_09( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->get_width( _instance_list_text_bitmap_class_t[ 9] ); }
static uint16_t text_bitmap_class_t_get_width_instance_10( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->get_width( _instance_list_text_bitmap_class_t[10] ); }
static uint16_t text_bitmap_class_t_get_width_instance_11( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->get_width( _instance_list_text_bitmap_class_t[11] ); }
static uint16_t text_bitmap_class_t_get_width_instance_12( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->get_width( _instance_list_text_bitmap_class_t[12] ); }
static uint16_t text_bitmap_class_t_get_width_instance_13( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->get_width( _instance_list_text_bitmap_class_t[13] ); }
static uint16_t text_bitmap_class_t_get_width_instance_14( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->get_width( _instance_list_text_bitmap_class_t[14] ); }
static uint16_t text_bitmap_class_t_get_width_instance_15( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->get_width( _instance_list_text_bitmap_class_t[15] ); }
static uint16_t text_bitmap_class_t_get_width_instance_16( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->get_width( _instance_list_text_bitmap_class_t[16] ); }
static uint16_t text_bitmap_class_t_get_width_instance_17( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->get_width( _instance_list_text_bitmap_class_t[17] ); }
static uint16_t text_bitmap_class_t_get_width_instance_18( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->get_width( _instance_list_text_bitmap_class_t[18] ); }
static uint16_t text_bitmap_class_t_get_width_instance_19( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->get_width( _instance_list_text_bitmap_class_t[19] ); }
static uint16_t text_bitmap_class_t_get_width_instance_20( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->get_width( _instance_list_text_bitmap_class_t[20] ); }
static uint16_t text_bitmap_class_t_get_width_instance_21( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->get_width( _instance_list_text_bitmap_class_t[21] ); }
static uint16_t text_bitmap_class_t_get_width_instance_22( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->get_width( _instance_list_text_bitmap_class_t[22] ); }
static uint16_t text_bitmap_class_t_get_width_instance_23( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->get_width( _instance_list_text_bitmap_class_t[23] ); }
static uint16_t text_bitmap_class_t_get_width_instance_24( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->get_width( _instance_list_text_bitmap_class_t[24] ); }
static uint16_t text_bitmap_class_t_get_width_instance_25( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->get_width( _instance_list_text_bitmap_class_t[25] ); }
static uint16_t text_bitmap_class_t_get_width_instance_26( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->get_width( _instance_list_text_bitmap_class_t[26] ); }
static uint16_t text_bitmap_class_t_get_width_instance_27( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->get_width( _instance_list_text_bitmap_class_t[27] ); }
static uint16_t text_bitmap_class_t_get_width_instance_28( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->get_width( _instance_list_text_bitmap_class_t[28] ); }
static uint16_t text_bitmap_class_t_get_width_instance_29( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->get_width( _instance_list_text_bitmap_class_t[29] ); }
static uint16_t text_bitmap_class_t_get_width_instance_30( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->get_width( _instance_list_text_bitmap_class_t[30] ); }
static uint16_t text_bitmap_class_t_get_width_instance_31( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->get_width( _instance_list_text_bitmap_class_t[31] ); }
static uint16_t text_bitmap_class_t_get_width_instance_32( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->get_width( _instance_list_text_bitmap_class_t[32] ); }
static uint16_t text_bitmap_class_t_get_width_instance_33( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->get_width( _instance_list_text_bitmap_class_t[33] ); }
static uint16_t text_bitmap_class_t_get_width_instance_34( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->get_width( _instance_list_text_bitmap_class_t[34] ); }
static uint16_t text_bitmap_class_t_get_width_instance_35( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->get_width( _instance_list_text_bitmap_class_t[35] ); }
static uint16_t text_bitmap_class_t_get_width_instance_36( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->get_width( _instance_list_text_bitmap_class_t[36] ); }
static uint16_t text_bitmap_class_t_get_width_instance_37( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->get_width( _instance_list_text_bitmap_class_t[37] ); }
static uint16_t text_bitmap_class_t_get_width_instance_38( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->get_width( _instance_list_text_bitmap_class_t[38] ); }
static uint16_t text_bitmap_class_t_get_width_instance_39( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->get_width( _instance_list_text_bitmap_class_t[39] ); }
static uint16_t text_bitmap_class_t_get_width_instance_40( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->get_width( _instance_list_text_bitmap_class_t[40] ); }
static uint16_t text_bitmap_class_t_get_width_instance_41( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->get_width( _instance_list_text_bitmap_class_t[41] ); }
static uint16_t text_bitmap_class_t_get_width_instance_42( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->get_width( _instance_list_text_bitmap_class_t[42] ); }
static uint16_t text_bitmap_class_t_get_width_instance_43( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->get_width( _instance_list_text_bitmap_class_t[43] ); }
static uint16_t text_bitmap_class_t_get_width_instance_44( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->get_width( _instance_list_text_bitmap_class_t[44] ); }
static uint16_t text_bitmap_class_t_get_width_instance_45( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->get_width( _instance_list_text_bitmap_class_t[45] ); }
static uint16_t text_bitmap_class_t_get_width_instance_46( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->get_width( _instance_list_text_bitmap_class_t[46] ); }
static uint16_t text_bitmap_class_t_get_width_instance_47( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->get_width( _instance_list_text_bitmap_class_t[47] ); }
static uint16_t text_bitmap_class_t_get_width_instance_48( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->get_width( _instance_list_text_bitmap_class_t[48] ); }
static uint16_t text_bitmap_class_t_get_width_instance_49( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->get_width( _instance_list_text_bitmap_class_t[49] ); }
static uint16_t text_bitmap_class_t_get_width_instance_50( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->get_width( _instance_list_text_bitmap_class_t[50] ); }
static uint16_t text_bitmap_class_t_get_width_instance_51( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->get_width( _instance_list_text_bitmap_class_t[51] ); }
static uint16_t text_bitmap_class_t_get_width_instance_52( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->get_width( _instance_list_text_bitmap_class_t[52] ); }
static uint16_t text_bitmap_class_t_get_width_instance_53( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->get_width( _instance_list_text_bitmap_class_t[53] ); }
static uint16_t text_bitmap_class_t_get_width_instance_54( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->get_width( _instance_list_text_bitmap_class_t[54] ); }
static uint16_t text_bitmap_class_t_get_width_instance_55( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->get_width( _instance_list_text_bitmap_class_t[55] ); }
static uint16_t text_bitmap_class_t_get_width_instance_56( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->get_width( _instance_list_text_bitmap_class_t[56] ); }
static uint16_t text_bitmap_class_t_get_width_instance_57( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->get_width( _instance_list_text_bitmap_class_t[57] ); }
static uint16_t text_bitmap_class_t_get_width_instance_58( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->get_width( _instance_list_text_bitmap_class_t[58] ); }
static uint16_t text_bitmap_class_t_get_width_instance_59( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->get_width( _instance_list_text_bitmap_class_t[59] ); }
static uint16_t text_bitmap_class_t_get_width_instance_60( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->get_width( _instance_list_text_bitmap_class_t[60] ); }
static uint16_t text_bitmap_class_t_get_width_instance_61( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->get_width( _instance_list_text_bitmap_class_t[61] ); }
static uint16_t text_bitmap_class_t_get_width_instance_62( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->get_width( _instance_list_text_bitmap_class_t[62] ); }
static uint16_t text_bitmap_class_t_get_width_instance_63( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->get_width( _instance_list_text_bitmap_class_t[63] ); }

static const text_bitmap_class_t_get_width_t _text_bitmap_class_t_get_width_list[64] =
{
    text_bitmap_class_t_get_width_instance_00,
    text_bitmap_class_t_get_width_instance_01,
    text_bitmap_class_t_get_width_instance_02,
    text_bitmap_class_t_get_width_instance_03,
    text_bitmap_class_t_get_width_instance_04,
    text_bitmap_class_t_get_width_instance_05,
    text_bitmap_class_t_get_width_instance_06,
    text_bitmap_class_t_get_width_instance_07,
    text_bitmap_class_t_get_width_instance_08,
    text_bitmap_class_t_get_width_instance_09,
    text_bitmap_class_t_get_width_instance_10,
    text_bitmap_class_t_get_width_instance_11,
    text_bitmap_class_t_get_width_instance_12,
    text_bitmap_class_t_get_width_instance_13,
    text_bitmap_class_t_get_width_instance_14,
    text_bitmap_class_t_get_width_instance_15,
    text_bitmap_class_t_get_width_instance_16,
    text_bitmap_class_t_get_width_instance_17,
    text_bitmap_class_t_get_width_instance_18,
    text_bitmap_class_t_get_width_instance_19,
    text_bitmap_class_t_get_width_instance_20,
    text_bitmap_class_t_get_width_instance_21,
    text_bitmap_class_t_get_width_instance_22,
    text_bitmap_class_t_get_width_instance_23,
    text_bitmap_class_t_get_width_instance_24,
    text_bitmap_class_t_get_width_instance_25,
    text_bitmap_class_t_get_width_instance_26,
    text_bitmap_class_t_get_width_instance_27,
    text_bitmap_class_t_get_width_instance_28,
    text_bitmap_class_t_get_width_instance_29,
    text_bitmap_class_t_get_width_instance_30,
    text_bitmap_class_t_get_width_instance_31,
    text_bitmap_class_t_get_width_instance_32,
    text_bitmap_class_t_get_width_instance_33,
    text_bitmap_class_t_get_width_instance_34,
    text_bitmap_class_t_get_width_instance_35,
    text_bitmap_class_t_get_width_instance_36,
    text_bitmap_class_t_get_width_instance_37,
    text_bitmap_class_t_get_width_instance_38,
    text_bitmap_class_t_get_width_instance_39,
    text_bitmap_class_t_get_width_instance_40,
    text_bitmap_class_t_get_width_instance_41,
    text_bitmap_class_t_get_width_instance_42,
    text_bitmap_class_t_get_width_instance_43,
    text_bitmap_class_t_get_width_instance_44,
    text_bitmap_class_t_get_width_instance_45,
    text_bitmap_class_t_get_width_instance_46,
    text_bitmap_class_t_get_width_instance_47,
    text_bitmap_class_t_get_width_instance_48,
    text_bitmap_class_t_get_width_instance_49,
    text_bitmap_class_t_get_width_instance_50,
    text_bitmap_class_t_get_width_instance_51,
    text_bitmap_class_t_get_width_instance_52,
    text_bitmap_class_t_get_width_instance_53,
    text_bitmap_class_t_get_width_instance_54,
    text_bitmap_class_t_get_width_instance_55,
    text_bitmap_class_t_get_width_instance_56,
    text_bitmap_class_t_get_width_instance_57,
    text_bitmap_class_t_get_width_instance_58,
    text_bitmap_class_t_get_width_instance_59,
    text_bitmap_class_t_get_width_instance_60,
    text_bitmap_class_t_get_width_instance_61,
    text_bitmap_class_t_get_width_instance_62,
    text_bitmap_class_t_get_width_instance_63,
};

typedef uint16_t ( *text_bitmap_class_t_get_height_t )( void );

static uint16_t text_bitmap_class_t_get_height_instance_00( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 0]->__api )->get_height( _instance_list_text_bitmap_class_t[ 0] ); }
static uint16_t text_bitmap_class_t_get_height_instance_01( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 1]->__api )->get_height( _instance_list_text_bitmap_class_t[ 1] ); }
static uint16_t text_bitmap_class_t_get_height_instance_02( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 2]->__api )->get_height( _instance_list_text_bitmap_class_t[ 2] ); }
static uint16_t text_bitmap_class_t_get_height_instance_03( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 3]->__api )->get_height( _instance_list_text_bitmap_class_t[ 3] ); }
static uint16_t text_bitmap_class_t_get_height_instance_04( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 4]->__api )->get_height( _instance_list_text_bitmap_class_t[ 4] ); }
static uint16_t text_bitmap_class_t_get_height_instance_05( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 5]->__api )->get_height( _instance_list_text_bitmap_class_t[ 5] ); }
static uint16_t text_bitmap_class_t_get_height_instance_06( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 6]->__api )->get_height( _instance_list_text_bitmap_class_t[ 6] ); }
static uint16_t text_bitmap_class_t_get_height_instance_07( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 7]->__api )->get_height( _instance_list_text_bitmap_class_t[ 7] ); }
static uint16_t text_bitmap_class_t_get_height_instance_08( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 8]->__api )->get_height( _instance_list_text_bitmap_class_t[ 8] ); }
static uint16_t text_bitmap_class_t_get_height_instance_09( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[ 9]->__api )->get_height( _instance_list_text_bitmap_class_t[ 9] ); }
static uint16_t text_bitmap_class_t_get_height_instance_10( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[10]->__api )->get_height( _instance_list_text_bitmap_class_t[10] ); }
static uint16_t text_bitmap_class_t_get_height_instance_11( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[11]->__api )->get_height( _instance_list_text_bitmap_class_t[11] ); }
static uint16_t text_bitmap_class_t_get_height_instance_12( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[12]->__api )->get_height( _instance_list_text_bitmap_class_t[12] ); }
static uint16_t text_bitmap_class_t_get_height_instance_13( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[13]->__api )->get_height( _instance_list_text_bitmap_class_t[13] ); }
static uint16_t text_bitmap_class_t_get_height_instance_14( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[14]->__api )->get_height( _instance_list_text_bitmap_class_t[14] ); }
static uint16_t text_bitmap_class_t_get_height_instance_15( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[15]->__api )->get_height( _instance_list_text_bitmap_class_t[15] ); }
static uint16_t text_bitmap_class_t_get_height_instance_16( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[16]->__api )->get_height( _instance_list_text_bitmap_class_t[16] ); }
static uint16_t text_bitmap_class_t_get_height_instance_17( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[17]->__api )->get_height( _instance_list_text_bitmap_class_t[17] ); }
static uint16_t text_bitmap_class_t_get_height_instance_18( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[18]->__api )->get_height( _instance_list_text_bitmap_class_t[18] ); }
static uint16_t text_bitmap_class_t_get_height_instance_19( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[19]->__api )->get_height( _instance_list_text_bitmap_class_t[19] ); }
static uint16_t text_bitmap_class_t_get_height_instance_20( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[20]->__api )->get_height( _instance_list_text_bitmap_class_t[20] ); }
static uint16_t text_bitmap_class_t_get_height_instance_21( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[21]->__api )->get_height( _instance_list_text_bitmap_class_t[21] ); }
static uint16_t text_bitmap_class_t_get_height_instance_22( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[22]->__api )->get_height( _instance_list_text_bitmap_class_t[22] ); }
static uint16_t text_bitmap_class_t_get_height_instance_23( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[23]->__api )->get_height( _instance_list_text_bitmap_class_t[23] ); }
static uint16_t text_bitmap_class_t_get_height_instance_24( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[24]->__api )->get_height( _instance_list_text_bitmap_class_t[24] ); }
static uint16_t text_bitmap_class_t_get_height_instance_25( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[25]->__api )->get_height( _instance_list_text_bitmap_class_t[25] ); }
static uint16_t text_bitmap_class_t_get_height_instance_26( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[26]->__api )->get_height( _instance_list_text_bitmap_class_t[26] ); }
static uint16_t text_bitmap_class_t_get_height_instance_27( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[27]->__api )->get_height( _instance_list_text_bitmap_class_t[27] ); }
static uint16_t text_bitmap_class_t_get_height_instance_28( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[28]->__api )->get_height( _instance_list_text_bitmap_class_t[28] ); }
static uint16_t text_bitmap_class_t_get_height_instance_29( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[29]->__api )->get_height( _instance_list_text_bitmap_class_t[29] ); }
static uint16_t text_bitmap_class_t_get_height_instance_30( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[30]->__api )->get_height( _instance_list_text_bitmap_class_t[30] ); }
static uint16_t text_bitmap_class_t_get_height_instance_31( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[31]->__api )->get_height( _instance_list_text_bitmap_class_t[31] ); }
static uint16_t text_bitmap_class_t_get_height_instance_32( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[32]->__api )->get_height( _instance_list_text_bitmap_class_t[32] ); }
static uint16_t text_bitmap_class_t_get_height_instance_33( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[33]->__api )->get_height( _instance_list_text_bitmap_class_t[33] ); }
static uint16_t text_bitmap_class_t_get_height_instance_34( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[34]->__api )->get_height( _instance_list_text_bitmap_class_t[34] ); }
static uint16_t text_bitmap_class_t_get_height_instance_35( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[35]->__api )->get_height( _instance_list_text_bitmap_class_t[35] ); }
static uint16_t text_bitmap_class_t_get_height_instance_36( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[36]->__api )->get_height( _instance_list_text_bitmap_class_t[36] ); }
static uint16_t text_bitmap_class_t_get_height_instance_37( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[37]->__api )->get_height( _instance_list_text_bitmap_class_t[37] ); }
static uint16_t text_bitmap_class_t_get_height_instance_38( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[38]->__api )->get_height( _instance_list_text_bitmap_class_t[38] ); }
static uint16_t text_bitmap_class_t_get_height_instance_39( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[39]->__api )->get_height( _instance_list_text_bitmap_class_t[39] ); }
static uint16_t text_bitmap_class_t_get_height_instance_40( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[40]->__api )->get_height( _instance_list_text_bitmap_class_t[40] ); }
static uint16_t text_bitmap_class_t_get_height_instance_41( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[41]->__api )->get_height( _instance_list_text_bitmap_class_t[41] ); }
static uint16_t text_bitmap_class_t_get_height_instance_42( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[42]->__api )->get_height( _instance_list_text_bitmap_class_t[42] ); }
static uint16_t text_bitmap_class_t_get_height_instance_43( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[43]->__api )->get_height( _instance_list_text_bitmap_class_t[43] ); }
static uint16_t text_bitmap_class_t_get_height_instance_44( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[44]->__api )->get_height( _instance_list_text_bitmap_class_t[44] ); }
static uint16_t text_bitmap_class_t_get_height_instance_45( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[45]->__api )->get_height( _instance_list_text_bitmap_class_t[45] ); }
static uint16_t text_bitmap_class_t_get_height_instance_46( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[46]->__api )->get_height( _instance_list_text_bitmap_class_t[46] ); }
static uint16_t text_bitmap_class_t_get_height_instance_47( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[47]->__api )->get_height( _instance_list_text_bitmap_class_t[47] ); }
static uint16_t text_bitmap_class_t_get_height_instance_48( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[48]->__api )->get_height( _instance_list_text_bitmap_class_t[48] ); }
static uint16_t text_bitmap_class_t_get_height_instance_49( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[49]->__api )->get_height( _instance_list_text_bitmap_class_t[49] ); }
static uint16_t text_bitmap_class_t_get_height_instance_50( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[50]->__api )->get_height( _instance_list_text_bitmap_class_t[50] ); }
static uint16_t text_bitmap_class_t_get_height_instance_51( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[51]->__api )->get_height( _instance_list_text_bitmap_class_t[51] ); }
static uint16_t text_bitmap_class_t_get_height_instance_52( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[52]->__api )->get_height( _instance_list_text_bitmap_class_t[52] ); }
static uint16_t text_bitmap_class_t_get_height_instance_53( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[53]->__api )->get_height( _instance_list_text_bitmap_class_t[53] ); }
static uint16_t text_bitmap_class_t_get_height_instance_54( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[54]->__api )->get_height( _instance_list_text_bitmap_class_t[54] ); }
static uint16_t text_bitmap_class_t_get_height_instance_55( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[55]->__api )->get_height( _instance_list_text_bitmap_class_t[55] ); }
static uint16_t text_bitmap_class_t_get_height_instance_56( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[56]->__api )->get_height( _instance_list_text_bitmap_class_t[56] ); }
static uint16_t text_bitmap_class_t_get_height_instance_57( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[57]->__api )->get_height( _instance_list_text_bitmap_class_t[57] ); }
static uint16_t text_bitmap_class_t_get_height_instance_58( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[58]->__api )->get_height( _instance_list_text_bitmap_class_t[58] ); }
static uint16_t text_bitmap_class_t_get_height_instance_59( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[59]->__api )->get_height( _instance_list_text_bitmap_class_t[59] ); }
static uint16_t text_bitmap_class_t_get_height_instance_60( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[60]->__api )->get_height( _instance_list_text_bitmap_class_t[60] ); }
static uint16_t text_bitmap_class_t_get_height_instance_61( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[61]->__api )->get_height( _instance_list_text_bitmap_class_t[61] ); }
static uint16_t text_bitmap_class_t_get_height_instance_62( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[62]->__api )->get_height( _instance_list_text_bitmap_class_t[62] ); }
static uint16_t text_bitmap_class_t_get_height_instance_63( void ){ return ( ( api_text_bitmap_class_t * )_instance_list_text_bitmap_class_t[63]->__api )->get_height( _instance_list_text_bitmap_class_t[63] ); }

static const text_bitmap_class_t_get_height_t _text_bitmap_class_t_get_height_list[64] =
{
    text_bitmap_class_t_get_height_instance_00,
    text_bitmap_class_t_get_height_instance_01,
    text_bitmap_class_t_get_height_instance_02,
    text_bitmap_class_t_get_height_instance_03,
    text_bitmap_class_t_get_height_instance_04,
    text_bitmap_class_t_get_height_instance_05,
    text_bitmap_class_t_get_height_instance_06,
    text_bitmap_class_t_get_height_instance_07,
    text_bitmap_class_t_get_height_instance_08,
    text_bitmap_class_t_get_height_instance_09,
    text_bitmap_class_t_get_height_instance_10,
    text_bitmap_class_t_get_height_instance_11,
    text_bitmap_class_t_get_height_instance_12,
    text_bitmap_class_t_get_height_instance_13,
    text_bitmap_class_t_get_height_instance_14,
    text_bitmap_class_t_get_height_instance_15,
    text_bitmap_class_t_get_height_instance_16,
    text_bitmap_class_t_get_height_instance_17,
    text_bitmap_class_t_get_height_instance_18,
    text_bitmap_class_t_get_height_instance_19,
    text_bitmap_class_t_get_height_instance_20,
    text_bitmap_class_t_get_height_instance_21,
    text_bitmap_class_t_get_height_instance_22,
    text_bitmap_class_t_get_height_instance_23,
    text_bitmap_class_t_get_height_instance_24,
    text_bitmap_class_t_get_height_instance_25,
    text_bitmap_class_t_get_height_instance_26,
    text_bitmap_class_t_get_height_instance_27,
    text_bitmap_class_t_get_height_instance_28,
    text_bitmap_class_t_get_height_instance_29,
    text_bitmap_class_t_get_height_instance_30,
    text_bitmap_class_t_get_height_instance_31,
    text_bitmap_class_t_get_height_instance_32,
    text_bitmap_class_t_get_height_instance_33,
    text_bitmap_class_t_get_height_instance_34,
    text_bitmap_class_t_get_height_instance_35,
    text_bitmap_class_t_get_height_instance_36,
    text_bitmap_class_t_get_height_instance_37,
    text_bitmap_class_t_get_height_instance_38,
    text_bitmap_class_t_get_height_instance_39,
    text_bitmap_class_t_get_height_instance_40,
    text_bitmap_class_t_get_height_instance_41,
    text_bitmap_class_t_get_height_instance_42,
    text_bitmap_class_t_get_height_instance_43,
    text_bitmap_class_t_get_height_instance_44,
    text_bitmap_class_t_get_height_instance_45,
    text_bitmap_class_t_get_height_instance_46,
    text_bitmap_class_t_get_height_instance_47,
    text_bitmap_class_t_get_height_instance_48,
    text_bitmap_class_t_get_height_instance_49,
    text_bitmap_class_t_get_height_instance_50,
    text_bitmap_class_t_get_height_instance_51,
    text_bitmap_class_t_get_height_instance_52,
    text_bitmap_class_t_get_height_instance_53,
    text_bitmap_class_t_get_height_instance_54,
    text_bitmap_class_t_get_height_instance_55,
    text_bitmap_class_t_get_height_instance_56,
    text_bitmap_class_t_get_height_instance_57,
    text_bitmap_class_t_get_height_instance_58,
    text_bitmap_class_t_get_height_instance_59,
    text_bitmap_class_t_get_height_instance_60,
    text_bitmap_class_t_get_height_instance_61,
    text_bitmap_class_t_get_height_instance_62,
    text_bitmap_class_t_get_height_instance_63,
};

void * _instance_new_text_bitmap_class_t_ex( void * __api, char * text, bitmap_class_t * dest )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_text_bitmap_class_t, sizeof(text_bitmap_class_t), 64 );
    if( _instance_index == -1 ) return NULL;
    text_bitmap_class_t * ret = _instance_list_text_bitmap_class_t[_instance_index];
    ret->__api = __api;
    ret->set_text = _text_bitmap_class_t_set_text_list[_instance_index];
    ret->draw = _text_bitmap_class_t_draw_list[_instance_index];
    ret->draw_vertical = _text_bitmap_class_t_draw_vertical_list[_instance_index];
    ret->get_width = _text_bitmap_class_t_get_width_list[_instance_index];
    ret->get_height = _text_bitmap_class_t_get_height_list[_instance_index];
    api_text_bitmap_class_t_class->creator( ret, text, dest );
    ret->__default_del = _text_bitmap_class_t_delete_list[_instance_index];
    return ret;
}

void * _instance_new_text_bitmap_class_t( char * text, bitmap_class_t * dest )
{
    return _instance_new_text_bitmap_class_t_ex( api_text_bitmap_class_t_class, text, dest );
}

void * _instance_static_text_bitmap_class_t_method( void * __api )
{
    return api_text_bitmap_class_t_class;
}

#if 0 // method definition for text_bitmap_class_t

#include "draw_text_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator( text_bitmap_class_t * p_data, char * text, bitmap_class_t * dest )
{
}

DELETE static void delete( text_bitmap_class_t * p_data )
{
}

METHOD static void set_text( text_bitmap_class_t * p_data, char * text )
{
}

METHOD static void draw( text_bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour )
{
}

METHOD static void draw_vertical( text_bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t fore_colour, pixel_t back_colour )
{
}

METHOD static uint16_t get_width( text_bitmap_class_t * p_data )
{
}

METHOD static uint16_t get_height( text_bitmap_class_t * p_data )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( text_bitmap_class_t );

////////////////////////////////////////////////////////////////////

#endif // text_bitmap_class_t

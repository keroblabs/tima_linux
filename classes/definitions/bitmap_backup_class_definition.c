#include "bitmap_backup_class_private.h"
#include "bitmap_backup_class.h"

////////////////////////////////////////////////////////////////////

api_bitmap_backup_class_t * api_bitmap_backup_class_t_class = NULL;

static bitmap_backup_class_t * _instance_list_bitmap_backup_class_t[64] = {0};

typedef void ( *bitmap_backup_class_t_delete_backup_t )( void );

static void bitmap_backup_class_t_delete_backup_instance_00( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 0] ); }
static void bitmap_backup_class_t_delete_backup_instance_01( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 1] ); }
static void bitmap_backup_class_t_delete_backup_instance_02( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 2] ); }
static void bitmap_backup_class_t_delete_backup_instance_03( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 3] ); }
static void bitmap_backup_class_t_delete_backup_instance_04( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 4] ); }
static void bitmap_backup_class_t_delete_backup_instance_05( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 5] ); }
static void bitmap_backup_class_t_delete_backup_instance_06( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 6] ); }
static void bitmap_backup_class_t_delete_backup_instance_07( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 7] ); }
static void bitmap_backup_class_t_delete_backup_instance_08( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 8] ); }
static void bitmap_backup_class_t_delete_backup_instance_09( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[ 9] ); }
static void bitmap_backup_class_t_delete_backup_instance_10( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[10] ); }
static void bitmap_backup_class_t_delete_backup_instance_11( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[11] ); }
static void bitmap_backup_class_t_delete_backup_instance_12( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[12] ); }
static void bitmap_backup_class_t_delete_backup_instance_13( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[13] ); }
static void bitmap_backup_class_t_delete_backup_instance_14( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[14] ); }
static void bitmap_backup_class_t_delete_backup_instance_15( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[15] ); }
static void bitmap_backup_class_t_delete_backup_instance_16( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[16] ); }
static void bitmap_backup_class_t_delete_backup_instance_17( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[17] ); }
static void bitmap_backup_class_t_delete_backup_instance_18( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[18] ); }
static void bitmap_backup_class_t_delete_backup_instance_19( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[19] ); }
static void bitmap_backup_class_t_delete_backup_instance_20( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[20] ); }
static void bitmap_backup_class_t_delete_backup_instance_21( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[21] ); }
static void bitmap_backup_class_t_delete_backup_instance_22( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[22] ); }
static void bitmap_backup_class_t_delete_backup_instance_23( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[23] ); }
static void bitmap_backup_class_t_delete_backup_instance_24( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[24] ); }
static void bitmap_backup_class_t_delete_backup_instance_25( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[25] ); }
static void bitmap_backup_class_t_delete_backup_instance_26( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[26] ); }
static void bitmap_backup_class_t_delete_backup_instance_27( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[27] ); }
static void bitmap_backup_class_t_delete_backup_instance_28( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[28] ); }
static void bitmap_backup_class_t_delete_backup_instance_29( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[29] ); }
static void bitmap_backup_class_t_delete_backup_instance_30( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[30] ); }
static void bitmap_backup_class_t_delete_backup_instance_31( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[31] ); }
static void bitmap_backup_class_t_delete_backup_instance_32( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[32] ); }
static void bitmap_backup_class_t_delete_backup_instance_33( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[33] ); }
static void bitmap_backup_class_t_delete_backup_instance_34( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[34] ); }
static void bitmap_backup_class_t_delete_backup_instance_35( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[35] ); }
static void bitmap_backup_class_t_delete_backup_instance_36( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[36] ); }
static void bitmap_backup_class_t_delete_backup_instance_37( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[37] ); }
static void bitmap_backup_class_t_delete_backup_instance_38( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[38] ); }
static void bitmap_backup_class_t_delete_backup_instance_39( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[39] ); }
static void bitmap_backup_class_t_delete_backup_instance_40( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[40] ); }
static void bitmap_backup_class_t_delete_backup_instance_41( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[41] ); }
static void bitmap_backup_class_t_delete_backup_instance_42( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[42] ); }
static void bitmap_backup_class_t_delete_backup_instance_43( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[43] ); }
static void bitmap_backup_class_t_delete_backup_instance_44( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[44] ); }
static void bitmap_backup_class_t_delete_backup_instance_45( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[45] ); }
static void bitmap_backup_class_t_delete_backup_instance_46( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[46] ); }
static void bitmap_backup_class_t_delete_backup_instance_47( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[47] ); }
static void bitmap_backup_class_t_delete_backup_instance_48( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[48] ); }
static void bitmap_backup_class_t_delete_backup_instance_49( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[49] ); }
static void bitmap_backup_class_t_delete_backup_instance_50( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[50] ); }
static void bitmap_backup_class_t_delete_backup_instance_51( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[51] ); }
static void bitmap_backup_class_t_delete_backup_instance_52( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[52] ); }
static void bitmap_backup_class_t_delete_backup_instance_53( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[53] ); }
static void bitmap_backup_class_t_delete_backup_instance_54( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[54] ); }
static void bitmap_backup_class_t_delete_backup_instance_55( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[55] ); }
static void bitmap_backup_class_t_delete_backup_instance_56( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[56] ); }
static void bitmap_backup_class_t_delete_backup_instance_57( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[57] ); }
static void bitmap_backup_class_t_delete_backup_instance_58( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[58] ); }
static void bitmap_backup_class_t_delete_backup_instance_59( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[59] ); }
static void bitmap_backup_class_t_delete_backup_instance_60( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[60] ); }
static void bitmap_backup_class_t_delete_backup_instance_61( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[61] ); }
static void bitmap_backup_class_t_delete_backup_instance_62( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[62] ); }
static void bitmap_backup_class_t_delete_backup_instance_63( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->delete_backup( _instance_list_bitmap_backup_class_t[63] ); }

static const bitmap_backup_class_t_delete_backup_t _bitmap_backup_class_t_delete_backup_list[64] =
{
    bitmap_backup_class_t_delete_backup_instance_00,
    bitmap_backup_class_t_delete_backup_instance_01,
    bitmap_backup_class_t_delete_backup_instance_02,
    bitmap_backup_class_t_delete_backup_instance_03,
    bitmap_backup_class_t_delete_backup_instance_04,
    bitmap_backup_class_t_delete_backup_instance_05,
    bitmap_backup_class_t_delete_backup_instance_06,
    bitmap_backup_class_t_delete_backup_instance_07,
    bitmap_backup_class_t_delete_backup_instance_08,
    bitmap_backup_class_t_delete_backup_instance_09,
    bitmap_backup_class_t_delete_backup_instance_10,
    bitmap_backup_class_t_delete_backup_instance_11,
    bitmap_backup_class_t_delete_backup_instance_12,
    bitmap_backup_class_t_delete_backup_instance_13,
    bitmap_backup_class_t_delete_backup_instance_14,
    bitmap_backup_class_t_delete_backup_instance_15,
    bitmap_backup_class_t_delete_backup_instance_16,
    bitmap_backup_class_t_delete_backup_instance_17,
    bitmap_backup_class_t_delete_backup_instance_18,
    bitmap_backup_class_t_delete_backup_instance_19,
    bitmap_backup_class_t_delete_backup_instance_20,
    bitmap_backup_class_t_delete_backup_instance_21,
    bitmap_backup_class_t_delete_backup_instance_22,
    bitmap_backup_class_t_delete_backup_instance_23,
    bitmap_backup_class_t_delete_backup_instance_24,
    bitmap_backup_class_t_delete_backup_instance_25,
    bitmap_backup_class_t_delete_backup_instance_26,
    bitmap_backup_class_t_delete_backup_instance_27,
    bitmap_backup_class_t_delete_backup_instance_28,
    bitmap_backup_class_t_delete_backup_instance_29,
    bitmap_backup_class_t_delete_backup_instance_30,
    bitmap_backup_class_t_delete_backup_instance_31,
    bitmap_backup_class_t_delete_backup_instance_32,
    bitmap_backup_class_t_delete_backup_instance_33,
    bitmap_backup_class_t_delete_backup_instance_34,
    bitmap_backup_class_t_delete_backup_instance_35,
    bitmap_backup_class_t_delete_backup_instance_36,
    bitmap_backup_class_t_delete_backup_instance_37,
    bitmap_backup_class_t_delete_backup_instance_38,
    bitmap_backup_class_t_delete_backup_instance_39,
    bitmap_backup_class_t_delete_backup_instance_40,
    bitmap_backup_class_t_delete_backup_instance_41,
    bitmap_backup_class_t_delete_backup_instance_42,
    bitmap_backup_class_t_delete_backup_instance_43,
    bitmap_backup_class_t_delete_backup_instance_44,
    bitmap_backup_class_t_delete_backup_instance_45,
    bitmap_backup_class_t_delete_backup_instance_46,
    bitmap_backup_class_t_delete_backup_instance_47,
    bitmap_backup_class_t_delete_backup_instance_48,
    bitmap_backup_class_t_delete_backup_instance_49,
    bitmap_backup_class_t_delete_backup_instance_50,
    bitmap_backup_class_t_delete_backup_instance_51,
    bitmap_backup_class_t_delete_backup_instance_52,
    bitmap_backup_class_t_delete_backup_instance_53,
    bitmap_backup_class_t_delete_backup_instance_54,
    bitmap_backup_class_t_delete_backup_instance_55,
    bitmap_backup_class_t_delete_backup_instance_56,
    bitmap_backup_class_t_delete_backup_instance_57,
    bitmap_backup_class_t_delete_backup_instance_58,
    bitmap_backup_class_t_delete_backup_instance_59,
    bitmap_backup_class_t_delete_backup_instance_60,
    bitmap_backup_class_t_delete_backup_instance_61,
    bitmap_backup_class_t_delete_backup_instance_62,
    bitmap_backup_class_t_delete_backup_instance_63,
};

typedef void ( *bitmap_backup_class_t_reset_t )( void );

static void bitmap_backup_class_t_reset_instance_00( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->reset( _instance_list_bitmap_backup_class_t[ 0] ); }
static void bitmap_backup_class_t_reset_instance_01( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->reset( _instance_list_bitmap_backup_class_t[ 1] ); }
static void bitmap_backup_class_t_reset_instance_02( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->reset( _instance_list_bitmap_backup_class_t[ 2] ); }
static void bitmap_backup_class_t_reset_instance_03( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->reset( _instance_list_bitmap_backup_class_t[ 3] ); }
static void bitmap_backup_class_t_reset_instance_04( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->reset( _instance_list_bitmap_backup_class_t[ 4] ); }
static void bitmap_backup_class_t_reset_instance_05( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->reset( _instance_list_bitmap_backup_class_t[ 5] ); }
static void bitmap_backup_class_t_reset_instance_06( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->reset( _instance_list_bitmap_backup_class_t[ 6] ); }
static void bitmap_backup_class_t_reset_instance_07( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->reset( _instance_list_bitmap_backup_class_t[ 7] ); }
static void bitmap_backup_class_t_reset_instance_08( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->reset( _instance_list_bitmap_backup_class_t[ 8] ); }
static void bitmap_backup_class_t_reset_instance_09( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->reset( _instance_list_bitmap_backup_class_t[ 9] ); }
static void bitmap_backup_class_t_reset_instance_10( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->reset( _instance_list_bitmap_backup_class_t[10] ); }
static void bitmap_backup_class_t_reset_instance_11( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->reset( _instance_list_bitmap_backup_class_t[11] ); }
static void bitmap_backup_class_t_reset_instance_12( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->reset( _instance_list_bitmap_backup_class_t[12] ); }
static void bitmap_backup_class_t_reset_instance_13( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->reset( _instance_list_bitmap_backup_class_t[13] ); }
static void bitmap_backup_class_t_reset_instance_14( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->reset( _instance_list_bitmap_backup_class_t[14] ); }
static void bitmap_backup_class_t_reset_instance_15( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->reset( _instance_list_bitmap_backup_class_t[15] ); }
static void bitmap_backup_class_t_reset_instance_16( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->reset( _instance_list_bitmap_backup_class_t[16] ); }
static void bitmap_backup_class_t_reset_instance_17( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->reset( _instance_list_bitmap_backup_class_t[17] ); }
static void bitmap_backup_class_t_reset_instance_18( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->reset( _instance_list_bitmap_backup_class_t[18] ); }
static void bitmap_backup_class_t_reset_instance_19( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->reset( _instance_list_bitmap_backup_class_t[19] ); }
static void bitmap_backup_class_t_reset_instance_20( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->reset( _instance_list_bitmap_backup_class_t[20] ); }
static void bitmap_backup_class_t_reset_instance_21( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->reset( _instance_list_bitmap_backup_class_t[21] ); }
static void bitmap_backup_class_t_reset_instance_22( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->reset( _instance_list_bitmap_backup_class_t[22] ); }
static void bitmap_backup_class_t_reset_instance_23( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->reset( _instance_list_bitmap_backup_class_t[23] ); }
static void bitmap_backup_class_t_reset_instance_24( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->reset( _instance_list_bitmap_backup_class_t[24] ); }
static void bitmap_backup_class_t_reset_instance_25( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->reset( _instance_list_bitmap_backup_class_t[25] ); }
static void bitmap_backup_class_t_reset_instance_26( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->reset( _instance_list_bitmap_backup_class_t[26] ); }
static void bitmap_backup_class_t_reset_instance_27( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->reset( _instance_list_bitmap_backup_class_t[27] ); }
static void bitmap_backup_class_t_reset_instance_28( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->reset( _instance_list_bitmap_backup_class_t[28] ); }
static void bitmap_backup_class_t_reset_instance_29( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->reset( _instance_list_bitmap_backup_class_t[29] ); }
static void bitmap_backup_class_t_reset_instance_30( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->reset( _instance_list_bitmap_backup_class_t[30] ); }
static void bitmap_backup_class_t_reset_instance_31( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->reset( _instance_list_bitmap_backup_class_t[31] ); }
static void bitmap_backup_class_t_reset_instance_32( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->reset( _instance_list_bitmap_backup_class_t[32] ); }
static void bitmap_backup_class_t_reset_instance_33( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->reset( _instance_list_bitmap_backup_class_t[33] ); }
static void bitmap_backup_class_t_reset_instance_34( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->reset( _instance_list_bitmap_backup_class_t[34] ); }
static void bitmap_backup_class_t_reset_instance_35( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->reset( _instance_list_bitmap_backup_class_t[35] ); }
static void bitmap_backup_class_t_reset_instance_36( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->reset( _instance_list_bitmap_backup_class_t[36] ); }
static void bitmap_backup_class_t_reset_instance_37( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->reset( _instance_list_bitmap_backup_class_t[37] ); }
static void bitmap_backup_class_t_reset_instance_38( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->reset( _instance_list_bitmap_backup_class_t[38] ); }
static void bitmap_backup_class_t_reset_instance_39( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->reset( _instance_list_bitmap_backup_class_t[39] ); }
static void bitmap_backup_class_t_reset_instance_40( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->reset( _instance_list_bitmap_backup_class_t[40] ); }
static void bitmap_backup_class_t_reset_instance_41( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->reset( _instance_list_bitmap_backup_class_t[41] ); }
static void bitmap_backup_class_t_reset_instance_42( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->reset( _instance_list_bitmap_backup_class_t[42] ); }
static void bitmap_backup_class_t_reset_instance_43( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->reset( _instance_list_bitmap_backup_class_t[43] ); }
static void bitmap_backup_class_t_reset_instance_44( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->reset( _instance_list_bitmap_backup_class_t[44] ); }
static void bitmap_backup_class_t_reset_instance_45( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->reset( _instance_list_bitmap_backup_class_t[45] ); }
static void bitmap_backup_class_t_reset_instance_46( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->reset( _instance_list_bitmap_backup_class_t[46] ); }
static void bitmap_backup_class_t_reset_instance_47( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->reset( _instance_list_bitmap_backup_class_t[47] ); }
static void bitmap_backup_class_t_reset_instance_48( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->reset( _instance_list_bitmap_backup_class_t[48] ); }
static void bitmap_backup_class_t_reset_instance_49( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->reset( _instance_list_bitmap_backup_class_t[49] ); }
static void bitmap_backup_class_t_reset_instance_50( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->reset( _instance_list_bitmap_backup_class_t[50] ); }
static void bitmap_backup_class_t_reset_instance_51( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->reset( _instance_list_bitmap_backup_class_t[51] ); }
static void bitmap_backup_class_t_reset_instance_52( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->reset( _instance_list_bitmap_backup_class_t[52] ); }
static void bitmap_backup_class_t_reset_instance_53( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->reset( _instance_list_bitmap_backup_class_t[53] ); }
static void bitmap_backup_class_t_reset_instance_54( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->reset( _instance_list_bitmap_backup_class_t[54] ); }
static void bitmap_backup_class_t_reset_instance_55( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->reset( _instance_list_bitmap_backup_class_t[55] ); }
static void bitmap_backup_class_t_reset_instance_56( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->reset( _instance_list_bitmap_backup_class_t[56] ); }
static void bitmap_backup_class_t_reset_instance_57( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->reset( _instance_list_bitmap_backup_class_t[57] ); }
static void bitmap_backup_class_t_reset_instance_58( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->reset( _instance_list_bitmap_backup_class_t[58] ); }
static void bitmap_backup_class_t_reset_instance_59( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->reset( _instance_list_bitmap_backup_class_t[59] ); }
static void bitmap_backup_class_t_reset_instance_60( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->reset( _instance_list_bitmap_backup_class_t[60] ); }
static void bitmap_backup_class_t_reset_instance_61( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->reset( _instance_list_bitmap_backup_class_t[61] ); }
static void bitmap_backup_class_t_reset_instance_62( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->reset( _instance_list_bitmap_backup_class_t[62] ); }
static void bitmap_backup_class_t_reset_instance_63( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->reset( _instance_list_bitmap_backup_class_t[63] ); }

static const bitmap_backup_class_t_reset_t _bitmap_backup_class_t_reset_list[64] =
{
    bitmap_backup_class_t_reset_instance_00,
    bitmap_backup_class_t_reset_instance_01,
    bitmap_backup_class_t_reset_instance_02,
    bitmap_backup_class_t_reset_instance_03,
    bitmap_backup_class_t_reset_instance_04,
    bitmap_backup_class_t_reset_instance_05,
    bitmap_backup_class_t_reset_instance_06,
    bitmap_backup_class_t_reset_instance_07,
    bitmap_backup_class_t_reset_instance_08,
    bitmap_backup_class_t_reset_instance_09,
    bitmap_backup_class_t_reset_instance_10,
    bitmap_backup_class_t_reset_instance_11,
    bitmap_backup_class_t_reset_instance_12,
    bitmap_backup_class_t_reset_instance_13,
    bitmap_backup_class_t_reset_instance_14,
    bitmap_backup_class_t_reset_instance_15,
    bitmap_backup_class_t_reset_instance_16,
    bitmap_backup_class_t_reset_instance_17,
    bitmap_backup_class_t_reset_instance_18,
    bitmap_backup_class_t_reset_instance_19,
    bitmap_backup_class_t_reset_instance_20,
    bitmap_backup_class_t_reset_instance_21,
    bitmap_backup_class_t_reset_instance_22,
    bitmap_backup_class_t_reset_instance_23,
    bitmap_backup_class_t_reset_instance_24,
    bitmap_backup_class_t_reset_instance_25,
    bitmap_backup_class_t_reset_instance_26,
    bitmap_backup_class_t_reset_instance_27,
    bitmap_backup_class_t_reset_instance_28,
    bitmap_backup_class_t_reset_instance_29,
    bitmap_backup_class_t_reset_instance_30,
    bitmap_backup_class_t_reset_instance_31,
    bitmap_backup_class_t_reset_instance_32,
    bitmap_backup_class_t_reset_instance_33,
    bitmap_backup_class_t_reset_instance_34,
    bitmap_backup_class_t_reset_instance_35,
    bitmap_backup_class_t_reset_instance_36,
    bitmap_backup_class_t_reset_instance_37,
    bitmap_backup_class_t_reset_instance_38,
    bitmap_backup_class_t_reset_instance_39,
    bitmap_backup_class_t_reset_instance_40,
    bitmap_backup_class_t_reset_instance_41,
    bitmap_backup_class_t_reset_instance_42,
    bitmap_backup_class_t_reset_instance_43,
    bitmap_backup_class_t_reset_instance_44,
    bitmap_backup_class_t_reset_instance_45,
    bitmap_backup_class_t_reset_instance_46,
    bitmap_backup_class_t_reset_instance_47,
    bitmap_backup_class_t_reset_instance_48,
    bitmap_backup_class_t_reset_instance_49,
    bitmap_backup_class_t_reset_instance_50,
    bitmap_backup_class_t_reset_instance_51,
    bitmap_backup_class_t_reset_instance_52,
    bitmap_backup_class_t_reset_instance_53,
    bitmap_backup_class_t_reset_instance_54,
    bitmap_backup_class_t_reset_instance_55,
    bitmap_backup_class_t_reset_instance_56,
    bitmap_backup_class_t_reset_instance_57,
    bitmap_backup_class_t_reset_instance_58,
    bitmap_backup_class_t_reset_instance_59,
    bitmap_backup_class_t_reset_instance_60,
    bitmap_backup_class_t_reset_instance_61,
    bitmap_backup_class_t_reset_instance_62,
    bitmap_backup_class_t_reset_instance_63,
};

typedef void ( *bitmap_backup_class_t_apply_to_t )( bitmap_class_t * bitmap_class );

static void bitmap_backup_class_t_apply_to_instance_00( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 0], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_01( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 1], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_02( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 2], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_03( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 3], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_04( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 4], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_05( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 5], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_06( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 6], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_07( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 7], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_08( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 8], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_09( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->apply_to( _instance_list_bitmap_backup_class_t[ 9], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_10( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->apply_to( _instance_list_bitmap_backup_class_t[10], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_11( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->apply_to( _instance_list_bitmap_backup_class_t[11], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_12( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->apply_to( _instance_list_bitmap_backup_class_t[12], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_13( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->apply_to( _instance_list_bitmap_backup_class_t[13], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_14( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->apply_to( _instance_list_bitmap_backup_class_t[14], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_15( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->apply_to( _instance_list_bitmap_backup_class_t[15], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_16( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->apply_to( _instance_list_bitmap_backup_class_t[16], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_17( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->apply_to( _instance_list_bitmap_backup_class_t[17], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_18( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->apply_to( _instance_list_bitmap_backup_class_t[18], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_19( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->apply_to( _instance_list_bitmap_backup_class_t[19], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_20( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->apply_to( _instance_list_bitmap_backup_class_t[20], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_21( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->apply_to( _instance_list_bitmap_backup_class_t[21], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_22( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->apply_to( _instance_list_bitmap_backup_class_t[22], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_23( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->apply_to( _instance_list_bitmap_backup_class_t[23], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_24( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->apply_to( _instance_list_bitmap_backup_class_t[24], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_25( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->apply_to( _instance_list_bitmap_backup_class_t[25], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_26( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->apply_to( _instance_list_bitmap_backup_class_t[26], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_27( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->apply_to( _instance_list_bitmap_backup_class_t[27], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_28( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->apply_to( _instance_list_bitmap_backup_class_t[28], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_29( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->apply_to( _instance_list_bitmap_backup_class_t[29], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_30( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->apply_to( _instance_list_bitmap_backup_class_t[30], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_31( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->apply_to( _instance_list_bitmap_backup_class_t[31], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_32( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->apply_to( _instance_list_bitmap_backup_class_t[32], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_33( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->apply_to( _instance_list_bitmap_backup_class_t[33], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_34( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->apply_to( _instance_list_bitmap_backup_class_t[34], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_35( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->apply_to( _instance_list_bitmap_backup_class_t[35], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_36( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->apply_to( _instance_list_bitmap_backup_class_t[36], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_37( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->apply_to( _instance_list_bitmap_backup_class_t[37], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_38( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->apply_to( _instance_list_bitmap_backup_class_t[38], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_39( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->apply_to( _instance_list_bitmap_backup_class_t[39], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_40( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->apply_to( _instance_list_bitmap_backup_class_t[40], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_41( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->apply_to( _instance_list_bitmap_backup_class_t[41], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_42( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->apply_to( _instance_list_bitmap_backup_class_t[42], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_43( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->apply_to( _instance_list_bitmap_backup_class_t[43], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_44( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->apply_to( _instance_list_bitmap_backup_class_t[44], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_45( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->apply_to( _instance_list_bitmap_backup_class_t[45], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_46( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->apply_to( _instance_list_bitmap_backup_class_t[46], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_47( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->apply_to( _instance_list_bitmap_backup_class_t[47], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_48( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->apply_to( _instance_list_bitmap_backup_class_t[48], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_49( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->apply_to( _instance_list_bitmap_backup_class_t[49], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_50( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->apply_to( _instance_list_bitmap_backup_class_t[50], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_51( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->apply_to( _instance_list_bitmap_backup_class_t[51], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_52( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->apply_to( _instance_list_bitmap_backup_class_t[52], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_53( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->apply_to( _instance_list_bitmap_backup_class_t[53], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_54( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->apply_to( _instance_list_bitmap_backup_class_t[54], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_55( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->apply_to( _instance_list_bitmap_backup_class_t[55], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_56( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->apply_to( _instance_list_bitmap_backup_class_t[56], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_57( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->apply_to( _instance_list_bitmap_backup_class_t[57], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_58( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->apply_to( _instance_list_bitmap_backup_class_t[58], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_59( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->apply_to( _instance_list_bitmap_backup_class_t[59], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_60( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->apply_to( _instance_list_bitmap_backup_class_t[60], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_61( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->apply_to( _instance_list_bitmap_backup_class_t[61], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_62( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->apply_to( _instance_list_bitmap_backup_class_t[62], bitmap_class ); }
static void bitmap_backup_class_t_apply_to_instance_63( bitmap_class_t * bitmap_class ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->apply_to( _instance_list_bitmap_backup_class_t[63], bitmap_class ); }

static const bitmap_backup_class_t_apply_to_t _bitmap_backup_class_t_apply_to_list[64] =
{
    bitmap_backup_class_t_apply_to_instance_00,
    bitmap_backup_class_t_apply_to_instance_01,
    bitmap_backup_class_t_apply_to_instance_02,
    bitmap_backup_class_t_apply_to_instance_03,
    bitmap_backup_class_t_apply_to_instance_04,
    bitmap_backup_class_t_apply_to_instance_05,
    bitmap_backup_class_t_apply_to_instance_06,
    bitmap_backup_class_t_apply_to_instance_07,
    bitmap_backup_class_t_apply_to_instance_08,
    bitmap_backup_class_t_apply_to_instance_09,
    bitmap_backup_class_t_apply_to_instance_10,
    bitmap_backup_class_t_apply_to_instance_11,
    bitmap_backup_class_t_apply_to_instance_12,
    bitmap_backup_class_t_apply_to_instance_13,
    bitmap_backup_class_t_apply_to_instance_14,
    bitmap_backup_class_t_apply_to_instance_15,
    bitmap_backup_class_t_apply_to_instance_16,
    bitmap_backup_class_t_apply_to_instance_17,
    bitmap_backup_class_t_apply_to_instance_18,
    bitmap_backup_class_t_apply_to_instance_19,
    bitmap_backup_class_t_apply_to_instance_20,
    bitmap_backup_class_t_apply_to_instance_21,
    bitmap_backup_class_t_apply_to_instance_22,
    bitmap_backup_class_t_apply_to_instance_23,
    bitmap_backup_class_t_apply_to_instance_24,
    bitmap_backup_class_t_apply_to_instance_25,
    bitmap_backup_class_t_apply_to_instance_26,
    bitmap_backup_class_t_apply_to_instance_27,
    bitmap_backup_class_t_apply_to_instance_28,
    bitmap_backup_class_t_apply_to_instance_29,
    bitmap_backup_class_t_apply_to_instance_30,
    bitmap_backup_class_t_apply_to_instance_31,
    bitmap_backup_class_t_apply_to_instance_32,
    bitmap_backup_class_t_apply_to_instance_33,
    bitmap_backup_class_t_apply_to_instance_34,
    bitmap_backup_class_t_apply_to_instance_35,
    bitmap_backup_class_t_apply_to_instance_36,
    bitmap_backup_class_t_apply_to_instance_37,
    bitmap_backup_class_t_apply_to_instance_38,
    bitmap_backup_class_t_apply_to_instance_39,
    bitmap_backup_class_t_apply_to_instance_40,
    bitmap_backup_class_t_apply_to_instance_41,
    bitmap_backup_class_t_apply_to_instance_42,
    bitmap_backup_class_t_apply_to_instance_43,
    bitmap_backup_class_t_apply_to_instance_44,
    bitmap_backup_class_t_apply_to_instance_45,
    bitmap_backup_class_t_apply_to_instance_46,
    bitmap_backup_class_t_apply_to_instance_47,
    bitmap_backup_class_t_apply_to_instance_48,
    bitmap_backup_class_t_apply_to_instance_49,
    bitmap_backup_class_t_apply_to_instance_50,
    bitmap_backup_class_t_apply_to_instance_51,
    bitmap_backup_class_t_apply_to_instance_52,
    bitmap_backup_class_t_apply_to_instance_53,
    bitmap_backup_class_t_apply_to_instance_54,
    bitmap_backup_class_t_apply_to_instance_55,
    bitmap_backup_class_t_apply_to_instance_56,
    bitmap_backup_class_t_apply_to_instance_57,
    bitmap_backup_class_t_apply_to_instance_58,
    bitmap_backup_class_t_apply_to_instance_59,
    bitmap_backup_class_t_apply_to_instance_60,
    bitmap_backup_class_t_apply_to_instance_61,
    bitmap_backup_class_t_apply_to_instance_62,
    bitmap_backup_class_t_apply_to_instance_63,
};

typedef void ( *bitmap_backup_class_t_apply_t )( void );

static void bitmap_backup_class_t_apply_instance_00( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->apply( _instance_list_bitmap_backup_class_t[ 0] ); }
static void bitmap_backup_class_t_apply_instance_01( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->apply( _instance_list_bitmap_backup_class_t[ 1] ); }
static void bitmap_backup_class_t_apply_instance_02( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->apply( _instance_list_bitmap_backup_class_t[ 2] ); }
static void bitmap_backup_class_t_apply_instance_03( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->apply( _instance_list_bitmap_backup_class_t[ 3] ); }
static void bitmap_backup_class_t_apply_instance_04( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->apply( _instance_list_bitmap_backup_class_t[ 4] ); }
static void bitmap_backup_class_t_apply_instance_05( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->apply( _instance_list_bitmap_backup_class_t[ 5] ); }
static void bitmap_backup_class_t_apply_instance_06( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->apply( _instance_list_bitmap_backup_class_t[ 6] ); }
static void bitmap_backup_class_t_apply_instance_07( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->apply( _instance_list_bitmap_backup_class_t[ 7] ); }
static void bitmap_backup_class_t_apply_instance_08( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->apply( _instance_list_bitmap_backup_class_t[ 8] ); }
static void bitmap_backup_class_t_apply_instance_09( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->apply( _instance_list_bitmap_backup_class_t[ 9] ); }
static void bitmap_backup_class_t_apply_instance_10( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->apply( _instance_list_bitmap_backup_class_t[10] ); }
static void bitmap_backup_class_t_apply_instance_11( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->apply( _instance_list_bitmap_backup_class_t[11] ); }
static void bitmap_backup_class_t_apply_instance_12( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->apply( _instance_list_bitmap_backup_class_t[12] ); }
static void bitmap_backup_class_t_apply_instance_13( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->apply( _instance_list_bitmap_backup_class_t[13] ); }
static void bitmap_backup_class_t_apply_instance_14( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->apply( _instance_list_bitmap_backup_class_t[14] ); }
static void bitmap_backup_class_t_apply_instance_15( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->apply( _instance_list_bitmap_backup_class_t[15] ); }
static void bitmap_backup_class_t_apply_instance_16( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->apply( _instance_list_bitmap_backup_class_t[16] ); }
static void bitmap_backup_class_t_apply_instance_17( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->apply( _instance_list_bitmap_backup_class_t[17] ); }
static void bitmap_backup_class_t_apply_instance_18( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->apply( _instance_list_bitmap_backup_class_t[18] ); }
static void bitmap_backup_class_t_apply_instance_19( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->apply( _instance_list_bitmap_backup_class_t[19] ); }
static void bitmap_backup_class_t_apply_instance_20( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->apply( _instance_list_bitmap_backup_class_t[20] ); }
static void bitmap_backup_class_t_apply_instance_21( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->apply( _instance_list_bitmap_backup_class_t[21] ); }
static void bitmap_backup_class_t_apply_instance_22( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->apply( _instance_list_bitmap_backup_class_t[22] ); }
static void bitmap_backup_class_t_apply_instance_23( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->apply( _instance_list_bitmap_backup_class_t[23] ); }
static void bitmap_backup_class_t_apply_instance_24( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->apply( _instance_list_bitmap_backup_class_t[24] ); }
static void bitmap_backup_class_t_apply_instance_25( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->apply( _instance_list_bitmap_backup_class_t[25] ); }
static void bitmap_backup_class_t_apply_instance_26( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->apply( _instance_list_bitmap_backup_class_t[26] ); }
static void bitmap_backup_class_t_apply_instance_27( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->apply( _instance_list_bitmap_backup_class_t[27] ); }
static void bitmap_backup_class_t_apply_instance_28( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->apply( _instance_list_bitmap_backup_class_t[28] ); }
static void bitmap_backup_class_t_apply_instance_29( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->apply( _instance_list_bitmap_backup_class_t[29] ); }
static void bitmap_backup_class_t_apply_instance_30( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->apply( _instance_list_bitmap_backup_class_t[30] ); }
static void bitmap_backup_class_t_apply_instance_31( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->apply( _instance_list_bitmap_backup_class_t[31] ); }
static void bitmap_backup_class_t_apply_instance_32( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->apply( _instance_list_bitmap_backup_class_t[32] ); }
static void bitmap_backup_class_t_apply_instance_33( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->apply( _instance_list_bitmap_backup_class_t[33] ); }
static void bitmap_backup_class_t_apply_instance_34( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->apply( _instance_list_bitmap_backup_class_t[34] ); }
static void bitmap_backup_class_t_apply_instance_35( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->apply( _instance_list_bitmap_backup_class_t[35] ); }
static void bitmap_backup_class_t_apply_instance_36( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->apply( _instance_list_bitmap_backup_class_t[36] ); }
static void bitmap_backup_class_t_apply_instance_37( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->apply( _instance_list_bitmap_backup_class_t[37] ); }
static void bitmap_backup_class_t_apply_instance_38( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->apply( _instance_list_bitmap_backup_class_t[38] ); }
static void bitmap_backup_class_t_apply_instance_39( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->apply( _instance_list_bitmap_backup_class_t[39] ); }
static void bitmap_backup_class_t_apply_instance_40( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->apply( _instance_list_bitmap_backup_class_t[40] ); }
static void bitmap_backup_class_t_apply_instance_41( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->apply( _instance_list_bitmap_backup_class_t[41] ); }
static void bitmap_backup_class_t_apply_instance_42( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->apply( _instance_list_bitmap_backup_class_t[42] ); }
static void bitmap_backup_class_t_apply_instance_43( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->apply( _instance_list_bitmap_backup_class_t[43] ); }
static void bitmap_backup_class_t_apply_instance_44( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->apply( _instance_list_bitmap_backup_class_t[44] ); }
static void bitmap_backup_class_t_apply_instance_45( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->apply( _instance_list_bitmap_backup_class_t[45] ); }
static void bitmap_backup_class_t_apply_instance_46( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->apply( _instance_list_bitmap_backup_class_t[46] ); }
static void bitmap_backup_class_t_apply_instance_47( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->apply( _instance_list_bitmap_backup_class_t[47] ); }
static void bitmap_backup_class_t_apply_instance_48( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->apply( _instance_list_bitmap_backup_class_t[48] ); }
static void bitmap_backup_class_t_apply_instance_49( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->apply( _instance_list_bitmap_backup_class_t[49] ); }
static void bitmap_backup_class_t_apply_instance_50( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->apply( _instance_list_bitmap_backup_class_t[50] ); }
static void bitmap_backup_class_t_apply_instance_51( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->apply( _instance_list_bitmap_backup_class_t[51] ); }
static void bitmap_backup_class_t_apply_instance_52( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->apply( _instance_list_bitmap_backup_class_t[52] ); }
static void bitmap_backup_class_t_apply_instance_53( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->apply( _instance_list_bitmap_backup_class_t[53] ); }
static void bitmap_backup_class_t_apply_instance_54( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->apply( _instance_list_bitmap_backup_class_t[54] ); }
static void bitmap_backup_class_t_apply_instance_55( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->apply( _instance_list_bitmap_backup_class_t[55] ); }
static void bitmap_backup_class_t_apply_instance_56( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->apply( _instance_list_bitmap_backup_class_t[56] ); }
static void bitmap_backup_class_t_apply_instance_57( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->apply( _instance_list_bitmap_backup_class_t[57] ); }
static void bitmap_backup_class_t_apply_instance_58( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->apply( _instance_list_bitmap_backup_class_t[58] ); }
static void bitmap_backup_class_t_apply_instance_59( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->apply( _instance_list_bitmap_backup_class_t[59] ); }
static void bitmap_backup_class_t_apply_instance_60( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->apply( _instance_list_bitmap_backup_class_t[60] ); }
static void bitmap_backup_class_t_apply_instance_61( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->apply( _instance_list_bitmap_backup_class_t[61] ); }
static void bitmap_backup_class_t_apply_instance_62( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->apply( _instance_list_bitmap_backup_class_t[62] ); }
static void bitmap_backup_class_t_apply_instance_63( void ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->apply( _instance_list_bitmap_backup_class_t[63] ); }

static const bitmap_backup_class_t_apply_t _bitmap_backup_class_t_apply_list[64] =
{
    bitmap_backup_class_t_apply_instance_00,
    bitmap_backup_class_t_apply_instance_01,
    bitmap_backup_class_t_apply_instance_02,
    bitmap_backup_class_t_apply_instance_03,
    bitmap_backup_class_t_apply_instance_04,
    bitmap_backup_class_t_apply_instance_05,
    bitmap_backup_class_t_apply_instance_06,
    bitmap_backup_class_t_apply_instance_07,
    bitmap_backup_class_t_apply_instance_08,
    bitmap_backup_class_t_apply_instance_09,
    bitmap_backup_class_t_apply_instance_10,
    bitmap_backup_class_t_apply_instance_11,
    bitmap_backup_class_t_apply_instance_12,
    bitmap_backup_class_t_apply_instance_13,
    bitmap_backup_class_t_apply_instance_14,
    bitmap_backup_class_t_apply_instance_15,
    bitmap_backup_class_t_apply_instance_16,
    bitmap_backup_class_t_apply_instance_17,
    bitmap_backup_class_t_apply_instance_18,
    bitmap_backup_class_t_apply_instance_19,
    bitmap_backup_class_t_apply_instance_20,
    bitmap_backup_class_t_apply_instance_21,
    bitmap_backup_class_t_apply_instance_22,
    bitmap_backup_class_t_apply_instance_23,
    bitmap_backup_class_t_apply_instance_24,
    bitmap_backup_class_t_apply_instance_25,
    bitmap_backup_class_t_apply_instance_26,
    bitmap_backup_class_t_apply_instance_27,
    bitmap_backup_class_t_apply_instance_28,
    bitmap_backup_class_t_apply_instance_29,
    bitmap_backup_class_t_apply_instance_30,
    bitmap_backup_class_t_apply_instance_31,
    bitmap_backup_class_t_apply_instance_32,
    bitmap_backup_class_t_apply_instance_33,
    bitmap_backup_class_t_apply_instance_34,
    bitmap_backup_class_t_apply_instance_35,
    bitmap_backup_class_t_apply_instance_36,
    bitmap_backup_class_t_apply_instance_37,
    bitmap_backup_class_t_apply_instance_38,
    bitmap_backup_class_t_apply_instance_39,
    bitmap_backup_class_t_apply_instance_40,
    bitmap_backup_class_t_apply_instance_41,
    bitmap_backup_class_t_apply_instance_42,
    bitmap_backup_class_t_apply_instance_43,
    bitmap_backup_class_t_apply_instance_44,
    bitmap_backup_class_t_apply_instance_45,
    bitmap_backup_class_t_apply_instance_46,
    bitmap_backup_class_t_apply_instance_47,
    bitmap_backup_class_t_apply_instance_48,
    bitmap_backup_class_t_apply_instance_49,
    bitmap_backup_class_t_apply_instance_50,
    bitmap_backup_class_t_apply_instance_51,
    bitmap_backup_class_t_apply_instance_52,
    bitmap_backup_class_t_apply_instance_53,
    bitmap_backup_class_t_apply_instance_54,
    bitmap_backup_class_t_apply_instance_55,
    bitmap_backup_class_t_apply_instance_56,
    bitmap_backup_class_t_apply_instance_57,
    bitmap_backup_class_t_apply_instance_58,
    bitmap_backup_class_t_apply_instance_59,
    bitmap_backup_class_t_apply_instance_60,
    bitmap_backup_class_t_apply_instance_61,
    bitmap_backup_class_t_apply_instance_62,
    bitmap_backup_class_t_apply_instance_63,
};

typedef void ( *bitmap_backup_class_t_draw_1bbp_collect_from_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input );

static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 0], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 1], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 2], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 3], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 4], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 5], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 6], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 7], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 8], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[ 9], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[10], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[11], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[12], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[13], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[14], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[15], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[16], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[17], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[18], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[19], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[20], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[21], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[22], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[23], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[24], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[25], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[26], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[27], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[28], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[29], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[30], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[31], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[32], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[33], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[34], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[35], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[36], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[37], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[38], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[39], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[40], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[41], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[42], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[43], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[44], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[45], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[46], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[47], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[48], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[49], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[50], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[51], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[52], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[53], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[54], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[55], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[56], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[57], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[58], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[59], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[60], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[61], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[62], posx, posy, width, heigth, from, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_from_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->draw_1bbp_collect_from( _instance_list_bitmap_backup_class_t[63], posx, posy, width, heigth, from, input ); }

static const bitmap_backup_class_t_draw_1bbp_collect_from_t _bitmap_backup_class_t_draw_1bbp_collect_from_list[64] =
{
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_00,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_01,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_02,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_03,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_04,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_05,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_06,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_07,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_08,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_09,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_10,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_11,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_12,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_13,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_14,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_15,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_16,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_17,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_18,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_19,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_20,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_21,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_22,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_23,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_24,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_25,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_26,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_27,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_28,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_29,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_30,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_31,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_32,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_33,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_34,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_35,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_36,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_37,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_38,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_39,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_40,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_41,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_42,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_43,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_44,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_45,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_46,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_47,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_48,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_49,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_50,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_51,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_52,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_53,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_54,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_55,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_56,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_57,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_58,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_59,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_60,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_61,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_62,
    bitmap_backup_class_t_draw_1bbp_collect_from_instance_63,
};

typedef void ( *bitmap_backup_class_t_draw_1bbp_collect_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input );

static void bitmap_backup_class_t_draw_1bbp_collect_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 0], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 1], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 2], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 3], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 4], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 5], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 6], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 7], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 8], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[ 9], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[10], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[11], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[12], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[13], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[14], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[15], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[16], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[17], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[18], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[19], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[20], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[21], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[22], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[23], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[24], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[25], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[26], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[27], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[28], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[29], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[30], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[31], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[32], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[33], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[34], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[35], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[36], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[37], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[38], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[39], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[40], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[41], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[42], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[43], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[44], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[45], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[46], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[47], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[48], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[49], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[50], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[51], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[52], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[53], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[54], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[55], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[56], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[57], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[58], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[59], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[60], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[61], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[62], posx, posy, width, heigth, input ); }
static void bitmap_backup_class_t_draw_1bbp_collect_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->draw_1bbp_collect( _instance_list_bitmap_backup_class_t[63], posx, posy, width, heigth, input ); }

static const bitmap_backup_class_t_draw_1bbp_collect_t _bitmap_backup_class_t_draw_1bbp_collect_list[64] =
{
    bitmap_backup_class_t_draw_1bbp_collect_instance_00,
    bitmap_backup_class_t_draw_1bbp_collect_instance_01,
    bitmap_backup_class_t_draw_1bbp_collect_instance_02,
    bitmap_backup_class_t_draw_1bbp_collect_instance_03,
    bitmap_backup_class_t_draw_1bbp_collect_instance_04,
    bitmap_backup_class_t_draw_1bbp_collect_instance_05,
    bitmap_backup_class_t_draw_1bbp_collect_instance_06,
    bitmap_backup_class_t_draw_1bbp_collect_instance_07,
    bitmap_backup_class_t_draw_1bbp_collect_instance_08,
    bitmap_backup_class_t_draw_1bbp_collect_instance_09,
    bitmap_backup_class_t_draw_1bbp_collect_instance_10,
    bitmap_backup_class_t_draw_1bbp_collect_instance_11,
    bitmap_backup_class_t_draw_1bbp_collect_instance_12,
    bitmap_backup_class_t_draw_1bbp_collect_instance_13,
    bitmap_backup_class_t_draw_1bbp_collect_instance_14,
    bitmap_backup_class_t_draw_1bbp_collect_instance_15,
    bitmap_backup_class_t_draw_1bbp_collect_instance_16,
    bitmap_backup_class_t_draw_1bbp_collect_instance_17,
    bitmap_backup_class_t_draw_1bbp_collect_instance_18,
    bitmap_backup_class_t_draw_1bbp_collect_instance_19,
    bitmap_backup_class_t_draw_1bbp_collect_instance_20,
    bitmap_backup_class_t_draw_1bbp_collect_instance_21,
    bitmap_backup_class_t_draw_1bbp_collect_instance_22,
    bitmap_backup_class_t_draw_1bbp_collect_instance_23,
    bitmap_backup_class_t_draw_1bbp_collect_instance_24,
    bitmap_backup_class_t_draw_1bbp_collect_instance_25,
    bitmap_backup_class_t_draw_1bbp_collect_instance_26,
    bitmap_backup_class_t_draw_1bbp_collect_instance_27,
    bitmap_backup_class_t_draw_1bbp_collect_instance_28,
    bitmap_backup_class_t_draw_1bbp_collect_instance_29,
    bitmap_backup_class_t_draw_1bbp_collect_instance_30,
    bitmap_backup_class_t_draw_1bbp_collect_instance_31,
    bitmap_backup_class_t_draw_1bbp_collect_instance_32,
    bitmap_backup_class_t_draw_1bbp_collect_instance_33,
    bitmap_backup_class_t_draw_1bbp_collect_instance_34,
    bitmap_backup_class_t_draw_1bbp_collect_instance_35,
    bitmap_backup_class_t_draw_1bbp_collect_instance_36,
    bitmap_backup_class_t_draw_1bbp_collect_instance_37,
    bitmap_backup_class_t_draw_1bbp_collect_instance_38,
    bitmap_backup_class_t_draw_1bbp_collect_instance_39,
    bitmap_backup_class_t_draw_1bbp_collect_instance_40,
    bitmap_backup_class_t_draw_1bbp_collect_instance_41,
    bitmap_backup_class_t_draw_1bbp_collect_instance_42,
    bitmap_backup_class_t_draw_1bbp_collect_instance_43,
    bitmap_backup_class_t_draw_1bbp_collect_instance_44,
    bitmap_backup_class_t_draw_1bbp_collect_instance_45,
    bitmap_backup_class_t_draw_1bbp_collect_instance_46,
    bitmap_backup_class_t_draw_1bbp_collect_instance_47,
    bitmap_backup_class_t_draw_1bbp_collect_instance_48,
    bitmap_backup_class_t_draw_1bbp_collect_instance_49,
    bitmap_backup_class_t_draw_1bbp_collect_instance_50,
    bitmap_backup_class_t_draw_1bbp_collect_instance_51,
    bitmap_backup_class_t_draw_1bbp_collect_instance_52,
    bitmap_backup_class_t_draw_1bbp_collect_instance_53,
    bitmap_backup_class_t_draw_1bbp_collect_instance_54,
    bitmap_backup_class_t_draw_1bbp_collect_instance_55,
    bitmap_backup_class_t_draw_1bbp_collect_instance_56,
    bitmap_backup_class_t_draw_1bbp_collect_instance_57,
    bitmap_backup_class_t_draw_1bbp_collect_instance_58,
    bitmap_backup_class_t_draw_1bbp_collect_instance_59,
    bitmap_backup_class_t_draw_1bbp_collect_instance_60,
    bitmap_backup_class_t_draw_1bbp_collect_instance_61,
    bitmap_backup_class_t_draw_1bbp_collect_instance_62,
    bitmap_backup_class_t_draw_1bbp_collect_instance_63,
};

typedef void ( *bitmap_backup_class_t_draw_1bbp_merge_t )( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip );

static void bitmap_backup_class_t_draw_1bbp_merge_instance_00( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 0], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_01( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 1], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_02( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 2], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_03( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 3], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_04( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 4], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_05( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 5], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_06( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 6], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_07( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 7], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_08( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 8], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_09( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[ 9], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_10( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[10], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_11( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[11], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_12( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[12], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_13( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[13], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_14( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[14], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_15( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[15], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_16( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[16], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_17( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[17], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_18( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[18], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_19( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[19], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_20( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[20], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_21( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[21], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_22( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[22], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_23( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[23], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_24( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[24], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_25( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[25], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_26( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[26], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_27( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[27], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_28( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[28], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_29( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[29], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_30( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[30], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_31( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[31], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_32( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[32], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_33( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[33], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_34( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[34], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_35( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[35], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_36( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[36], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_37( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[37], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_38( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[38], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_39( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[39], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_40( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[40], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_41( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[41], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_42( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[42], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_43( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[43], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_44( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[44], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_45( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[45], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_46( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[46], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_47( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[47], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_48( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[48], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_49( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[49], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_50( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[50], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_51( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[51], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_52( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[52], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_53( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[53], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_54( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[54], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_55( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[55], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_56( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[56], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_57( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[57], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_58( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[58], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_59( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[59], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_60( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[60], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_61( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[61], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_62( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[62], width, heigth, input, fore_colour, output, is_skip ); }
static void bitmap_backup_class_t_draw_1bbp_merge_instance_63( uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->draw_1bbp_merge( _instance_list_bitmap_backup_class_t[63], width, heigth, input, fore_colour, output, is_skip ); }

static const bitmap_backup_class_t_draw_1bbp_merge_t _bitmap_backup_class_t_draw_1bbp_merge_list[64] =
{
    bitmap_backup_class_t_draw_1bbp_merge_instance_00,
    bitmap_backup_class_t_draw_1bbp_merge_instance_01,
    bitmap_backup_class_t_draw_1bbp_merge_instance_02,
    bitmap_backup_class_t_draw_1bbp_merge_instance_03,
    bitmap_backup_class_t_draw_1bbp_merge_instance_04,
    bitmap_backup_class_t_draw_1bbp_merge_instance_05,
    bitmap_backup_class_t_draw_1bbp_merge_instance_06,
    bitmap_backup_class_t_draw_1bbp_merge_instance_07,
    bitmap_backup_class_t_draw_1bbp_merge_instance_08,
    bitmap_backup_class_t_draw_1bbp_merge_instance_09,
    bitmap_backup_class_t_draw_1bbp_merge_instance_10,
    bitmap_backup_class_t_draw_1bbp_merge_instance_11,
    bitmap_backup_class_t_draw_1bbp_merge_instance_12,
    bitmap_backup_class_t_draw_1bbp_merge_instance_13,
    bitmap_backup_class_t_draw_1bbp_merge_instance_14,
    bitmap_backup_class_t_draw_1bbp_merge_instance_15,
    bitmap_backup_class_t_draw_1bbp_merge_instance_16,
    bitmap_backup_class_t_draw_1bbp_merge_instance_17,
    bitmap_backup_class_t_draw_1bbp_merge_instance_18,
    bitmap_backup_class_t_draw_1bbp_merge_instance_19,
    bitmap_backup_class_t_draw_1bbp_merge_instance_20,
    bitmap_backup_class_t_draw_1bbp_merge_instance_21,
    bitmap_backup_class_t_draw_1bbp_merge_instance_22,
    bitmap_backup_class_t_draw_1bbp_merge_instance_23,
    bitmap_backup_class_t_draw_1bbp_merge_instance_24,
    bitmap_backup_class_t_draw_1bbp_merge_instance_25,
    bitmap_backup_class_t_draw_1bbp_merge_instance_26,
    bitmap_backup_class_t_draw_1bbp_merge_instance_27,
    bitmap_backup_class_t_draw_1bbp_merge_instance_28,
    bitmap_backup_class_t_draw_1bbp_merge_instance_29,
    bitmap_backup_class_t_draw_1bbp_merge_instance_30,
    bitmap_backup_class_t_draw_1bbp_merge_instance_31,
    bitmap_backup_class_t_draw_1bbp_merge_instance_32,
    bitmap_backup_class_t_draw_1bbp_merge_instance_33,
    bitmap_backup_class_t_draw_1bbp_merge_instance_34,
    bitmap_backup_class_t_draw_1bbp_merge_instance_35,
    bitmap_backup_class_t_draw_1bbp_merge_instance_36,
    bitmap_backup_class_t_draw_1bbp_merge_instance_37,
    bitmap_backup_class_t_draw_1bbp_merge_instance_38,
    bitmap_backup_class_t_draw_1bbp_merge_instance_39,
    bitmap_backup_class_t_draw_1bbp_merge_instance_40,
    bitmap_backup_class_t_draw_1bbp_merge_instance_41,
    bitmap_backup_class_t_draw_1bbp_merge_instance_42,
    bitmap_backup_class_t_draw_1bbp_merge_instance_43,
    bitmap_backup_class_t_draw_1bbp_merge_instance_44,
    bitmap_backup_class_t_draw_1bbp_merge_instance_45,
    bitmap_backup_class_t_draw_1bbp_merge_instance_46,
    bitmap_backup_class_t_draw_1bbp_merge_instance_47,
    bitmap_backup_class_t_draw_1bbp_merge_instance_48,
    bitmap_backup_class_t_draw_1bbp_merge_instance_49,
    bitmap_backup_class_t_draw_1bbp_merge_instance_50,
    bitmap_backup_class_t_draw_1bbp_merge_instance_51,
    bitmap_backup_class_t_draw_1bbp_merge_instance_52,
    bitmap_backup_class_t_draw_1bbp_merge_instance_53,
    bitmap_backup_class_t_draw_1bbp_merge_instance_54,
    bitmap_backup_class_t_draw_1bbp_merge_instance_55,
    bitmap_backup_class_t_draw_1bbp_merge_instance_56,
    bitmap_backup_class_t_draw_1bbp_merge_instance_57,
    bitmap_backup_class_t_draw_1bbp_merge_instance_58,
    bitmap_backup_class_t_draw_1bbp_merge_instance_59,
    bitmap_backup_class_t_draw_1bbp_merge_instance_60,
    bitmap_backup_class_t_draw_1bbp_merge_instance_61,
    bitmap_backup_class_t_draw_1bbp_merge_instance_62,
    bitmap_backup_class_t_draw_1bbp_merge_instance_63,
};

typedef void ( *bitmap_backup_class_t_set_pixel_t )( uint16_t posx, uint16_t posy, pixel_t pixel );

static void bitmap_backup_class_t_set_pixel_instance_00( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 0], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_01( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 1], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_02( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 2], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_03( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 3], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_04( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 4], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_05( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 5], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_06( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 6], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_07( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 7], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_08( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 8], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_09( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[ 9], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_10( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[10], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_11( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[11], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_12( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[12], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_13( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[13], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_14( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[14], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_15( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[15], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_16( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[16], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_17( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[17], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_18( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[18], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_19( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[19], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_20( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[20], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_21( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[21], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_22( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[22], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_23( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[23], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_24( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[24], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_25( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[25], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_26( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[26], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_27( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[27], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_28( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[28], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_29( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[29], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_30( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[30], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_31( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[31], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_32( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[32], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_33( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[33], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_34( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[34], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_35( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[35], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_36( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[36], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_37( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[37], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_38( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[38], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_39( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[39], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_40( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[40], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_41( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[41], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_42( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[42], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_43( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[43], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_44( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[44], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_45( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[45], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_46( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[46], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_47( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[47], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_48( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[48], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_49( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[49], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_50( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[50], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_51( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[51], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_52( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[52], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_53( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[53], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_54( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[54], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_55( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[55], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_56( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[56], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_57( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[57], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_58( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[58], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_59( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[59], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_60( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[60], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_61( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[61], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_62( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[62], posx, posy, pixel ); }
static void bitmap_backup_class_t_set_pixel_instance_63( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->set_pixel( _instance_list_bitmap_backup_class_t[63], posx, posy, pixel ); }

static const bitmap_backup_class_t_set_pixel_t _bitmap_backup_class_t_set_pixel_list[64] =
{
    bitmap_backup_class_t_set_pixel_instance_00,
    bitmap_backup_class_t_set_pixel_instance_01,
    bitmap_backup_class_t_set_pixel_instance_02,
    bitmap_backup_class_t_set_pixel_instance_03,
    bitmap_backup_class_t_set_pixel_instance_04,
    bitmap_backup_class_t_set_pixel_instance_05,
    bitmap_backup_class_t_set_pixel_instance_06,
    bitmap_backup_class_t_set_pixel_instance_07,
    bitmap_backup_class_t_set_pixel_instance_08,
    bitmap_backup_class_t_set_pixel_instance_09,
    bitmap_backup_class_t_set_pixel_instance_10,
    bitmap_backup_class_t_set_pixel_instance_11,
    bitmap_backup_class_t_set_pixel_instance_12,
    bitmap_backup_class_t_set_pixel_instance_13,
    bitmap_backup_class_t_set_pixel_instance_14,
    bitmap_backup_class_t_set_pixel_instance_15,
    bitmap_backup_class_t_set_pixel_instance_16,
    bitmap_backup_class_t_set_pixel_instance_17,
    bitmap_backup_class_t_set_pixel_instance_18,
    bitmap_backup_class_t_set_pixel_instance_19,
    bitmap_backup_class_t_set_pixel_instance_20,
    bitmap_backup_class_t_set_pixel_instance_21,
    bitmap_backup_class_t_set_pixel_instance_22,
    bitmap_backup_class_t_set_pixel_instance_23,
    bitmap_backup_class_t_set_pixel_instance_24,
    bitmap_backup_class_t_set_pixel_instance_25,
    bitmap_backup_class_t_set_pixel_instance_26,
    bitmap_backup_class_t_set_pixel_instance_27,
    bitmap_backup_class_t_set_pixel_instance_28,
    bitmap_backup_class_t_set_pixel_instance_29,
    bitmap_backup_class_t_set_pixel_instance_30,
    bitmap_backup_class_t_set_pixel_instance_31,
    bitmap_backup_class_t_set_pixel_instance_32,
    bitmap_backup_class_t_set_pixel_instance_33,
    bitmap_backup_class_t_set_pixel_instance_34,
    bitmap_backup_class_t_set_pixel_instance_35,
    bitmap_backup_class_t_set_pixel_instance_36,
    bitmap_backup_class_t_set_pixel_instance_37,
    bitmap_backup_class_t_set_pixel_instance_38,
    bitmap_backup_class_t_set_pixel_instance_39,
    bitmap_backup_class_t_set_pixel_instance_40,
    bitmap_backup_class_t_set_pixel_instance_41,
    bitmap_backup_class_t_set_pixel_instance_42,
    bitmap_backup_class_t_set_pixel_instance_43,
    bitmap_backup_class_t_set_pixel_instance_44,
    bitmap_backup_class_t_set_pixel_instance_45,
    bitmap_backup_class_t_set_pixel_instance_46,
    bitmap_backup_class_t_set_pixel_instance_47,
    bitmap_backup_class_t_set_pixel_instance_48,
    bitmap_backup_class_t_set_pixel_instance_49,
    bitmap_backup_class_t_set_pixel_instance_50,
    bitmap_backup_class_t_set_pixel_instance_51,
    bitmap_backup_class_t_set_pixel_instance_52,
    bitmap_backup_class_t_set_pixel_instance_53,
    bitmap_backup_class_t_set_pixel_instance_54,
    bitmap_backup_class_t_set_pixel_instance_55,
    bitmap_backup_class_t_set_pixel_instance_56,
    bitmap_backup_class_t_set_pixel_instance_57,
    bitmap_backup_class_t_set_pixel_instance_58,
    bitmap_backup_class_t_set_pixel_instance_59,
    bitmap_backup_class_t_set_pixel_instance_60,
    bitmap_backup_class_t_set_pixel_instance_61,
    bitmap_backup_class_t_set_pixel_instance_62,
    bitmap_backup_class_t_set_pixel_instance_63,
};

typedef void ( *bitmap_backup_class_t_set_pixel_index_t )( uint32_t index, pixel_t pixel );

static void bitmap_backup_class_t_set_pixel_index_instance_00( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 0]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 0], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_01( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 1]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 1], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_02( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 2]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 2], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_03( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 3]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 3], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_04( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 4]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 4], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_05( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 5]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 5], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_06( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 6]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 6], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_07( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 7]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 7], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_08( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 8]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 8], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_09( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[ 9]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[ 9], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_10( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[10]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[10], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_11( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[11]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[11], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_12( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[12]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[12], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_13( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[13]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[13], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_14( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[14]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[14], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_15( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[15]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[15], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_16( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[16]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[16], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_17( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[17]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[17], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_18( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[18]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[18], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_19( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[19]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[19], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_20( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[20]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[20], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_21( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[21]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[21], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_22( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[22]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[22], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_23( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[23]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[23], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_24( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[24]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[24], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_25( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[25]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[25], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_26( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[26]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[26], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_27( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[27]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[27], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_28( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[28]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[28], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_29( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[29]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[29], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_30( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[30]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[30], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_31( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[31]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[31], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_32( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[32]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[32], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_33( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[33]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[33], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_34( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[34]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[34], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_35( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[35]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[35], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_36( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[36]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[36], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_37( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[37]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[37], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_38( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[38]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[38], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_39( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[39]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[39], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_40( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[40]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[40], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_41( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[41]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[41], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_42( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[42]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[42], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_43( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[43]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[43], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_44( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[44]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[44], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_45( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[45]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[45], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_46( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[46]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[46], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_47( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[47]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[47], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_48( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[48]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[48], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_49( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[49]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[49], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_50( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[50]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[50], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_51( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[51]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[51], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_52( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[52]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[52], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_53( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[53]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[53], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_54( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[54]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[54], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_55( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[55]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[55], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_56( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[56]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[56], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_57( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[57]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[57], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_58( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[58]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[58], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_59( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[59]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[59], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_60( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[60]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[60], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_61( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[61]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[61], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_62( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[62]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[62], index, pixel ); }
static void bitmap_backup_class_t_set_pixel_index_instance_63( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_backup_class_t * )_instance_list_bitmap_backup_class_t[63]->__api )->set_pixel_index( _instance_list_bitmap_backup_class_t[63], index, pixel ); }

static const bitmap_backup_class_t_set_pixel_index_t _bitmap_backup_class_t_set_pixel_index_list[64] =
{
    bitmap_backup_class_t_set_pixel_index_instance_00,
    bitmap_backup_class_t_set_pixel_index_instance_01,
    bitmap_backup_class_t_set_pixel_index_instance_02,
    bitmap_backup_class_t_set_pixel_index_instance_03,
    bitmap_backup_class_t_set_pixel_index_instance_04,
    bitmap_backup_class_t_set_pixel_index_instance_05,
    bitmap_backup_class_t_set_pixel_index_instance_06,
    bitmap_backup_class_t_set_pixel_index_instance_07,
    bitmap_backup_class_t_set_pixel_index_instance_08,
    bitmap_backup_class_t_set_pixel_index_instance_09,
    bitmap_backup_class_t_set_pixel_index_instance_10,
    bitmap_backup_class_t_set_pixel_index_instance_11,
    bitmap_backup_class_t_set_pixel_index_instance_12,
    bitmap_backup_class_t_set_pixel_index_instance_13,
    bitmap_backup_class_t_set_pixel_index_instance_14,
    bitmap_backup_class_t_set_pixel_index_instance_15,
    bitmap_backup_class_t_set_pixel_index_instance_16,
    bitmap_backup_class_t_set_pixel_index_instance_17,
    bitmap_backup_class_t_set_pixel_index_instance_18,
    bitmap_backup_class_t_set_pixel_index_instance_19,
    bitmap_backup_class_t_set_pixel_index_instance_20,
    bitmap_backup_class_t_set_pixel_index_instance_21,
    bitmap_backup_class_t_set_pixel_index_instance_22,
    bitmap_backup_class_t_set_pixel_index_instance_23,
    bitmap_backup_class_t_set_pixel_index_instance_24,
    bitmap_backup_class_t_set_pixel_index_instance_25,
    bitmap_backup_class_t_set_pixel_index_instance_26,
    bitmap_backup_class_t_set_pixel_index_instance_27,
    bitmap_backup_class_t_set_pixel_index_instance_28,
    bitmap_backup_class_t_set_pixel_index_instance_29,
    bitmap_backup_class_t_set_pixel_index_instance_30,
    bitmap_backup_class_t_set_pixel_index_instance_31,
    bitmap_backup_class_t_set_pixel_index_instance_32,
    bitmap_backup_class_t_set_pixel_index_instance_33,
    bitmap_backup_class_t_set_pixel_index_instance_34,
    bitmap_backup_class_t_set_pixel_index_instance_35,
    bitmap_backup_class_t_set_pixel_index_instance_36,
    bitmap_backup_class_t_set_pixel_index_instance_37,
    bitmap_backup_class_t_set_pixel_index_instance_38,
    bitmap_backup_class_t_set_pixel_index_instance_39,
    bitmap_backup_class_t_set_pixel_index_instance_40,
    bitmap_backup_class_t_set_pixel_index_instance_41,
    bitmap_backup_class_t_set_pixel_index_instance_42,
    bitmap_backup_class_t_set_pixel_index_instance_43,
    bitmap_backup_class_t_set_pixel_index_instance_44,
    bitmap_backup_class_t_set_pixel_index_instance_45,
    bitmap_backup_class_t_set_pixel_index_instance_46,
    bitmap_backup_class_t_set_pixel_index_instance_47,
    bitmap_backup_class_t_set_pixel_index_instance_48,
    bitmap_backup_class_t_set_pixel_index_instance_49,
    bitmap_backup_class_t_set_pixel_index_instance_50,
    bitmap_backup_class_t_set_pixel_index_instance_51,
    bitmap_backup_class_t_set_pixel_index_instance_52,
    bitmap_backup_class_t_set_pixel_index_instance_53,
    bitmap_backup_class_t_set_pixel_index_instance_54,
    bitmap_backup_class_t_set_pixel_index_instance_55,
    bitmap_backup_class_t_set_pixel_index_instance_56,
    bitmap_backup_class_t_set_pixel_index_instance_57,
    bitmap_backup_class_t_set_pixel_index_instance_58,
    bitmap_backup_class_t_set_pixel_index_instance_59,
    bitmap_backup_class_t_set_pixel_index_instance_60,
    bitmap_backup_class_t_set_pixel_index_instance_61,
    bitmap_backup_class_t_set_pixel_index_instance_62,
    bitmap_backup_class_t_set_pixel_index_instance_63,
};

void * _instance_new_bitmap_backup_class_t_ex( void * __api, bitmap_class_t * bitmap_class, uint32_t max_size )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_bitmap_backup_class_t, sizeof(bitmap_backup_class_t), 64 );
    if( _instance_index == -1 ) return NULL;
    bitmap_backup_class_t * ret = _instance_list_bitmap_backup_class_t[_instance_index];
    ret->__api = __api;
    ret->reset = _bitmap_backup_class_t_reset_list[_instance_index];
    ret->apply_to = _bitmap_backup_class_t_apply_to_list[_instance_index];
    ret->apply = _bitmap_backup_class_t_apply_list[_instance_index];
    ret->draw_1bbp_collect_from = _bitmap_backup_class_t_draw_1bbp_collect_from_list[_instance_index];
    ret->draw_1bbp_collect = _bitmap_backup_class_t_draw_1bbp_collect_list[_instance_index];
    ret->draw_1bbp_merge = _bitmap_backup_class_t_draw_1bbp_merge_list[_instance_index];
    ret->set_pixel = _bitmap_backup_class_t_set_pixel_list[_instance_index];
    ret->set_pixel_index = _bitmap_backup_class_t_set_pixel_index_list[_instance_index];
    api_bitmap_backup_class_t_class->create_backup( ret, bitmap_class, max_size );
    ret->__default_del = _bitmap_backup_class_t_delete_backup_list[_instance_index];
    return ret;
}

void * _instance_new_bitmap_backup_class_t( bitmap_class_t * bitmap_class, uint32_t max_size )
{
    return _instance_new_bitmap_backup_class_t_ex( api_bitmap_backup_class_t_class, bitmap_class, max_size );
}

void * _instance_static_bitmap_backup_class_t_method( void * __api )
{
    return api_bitmap_backup_class_t_class;
}

#if 0 // method definition for bitmap_backup_class_t

#include "bitmap_backup_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void create_backup( bitmap_backup_class_t * p_data, bitmap_class_t * bitmap_class, uint32_t max_size )
{
}

DELETE static void delete_backup( bitmap_backup_class_t * p_data )
{
}

METHOD static void reset( bitmap_backup_class_t * p_data )
{
}

METHOD static void apply_to( bitmap_backup_class_t * p_data, bitmap_class_t * bitmap_class )
{
}

METHOD static void apply( bitmap_backup_class_t * p_data )
{
}

METHOD static void draw_1bbp_collect_from( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, CLASS(bitmap_backup_class_t) * from, uint8_t * input )
{
}

METHOD static void draw_1bbp_collect( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input )
{
}

METHOD static void draw_1bbp_merge( bitmap_backup_class_t * p_data, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t fore_colour, CLASS(bitmap_backup_class_t) * output, bool_t is_skip )
{
}

METHOD static void set_pixel( bitmap_backup_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t pixel )
{
}

METHOD static void set_pixel_index( bitmap_backup_class_t * p_data, uint32_t index, pixel_t pixel )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_backup_class_t );

////////////////////////////////////////////////////////////////////

#endif // bitmap_backup_class_t

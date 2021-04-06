#include "bitmap_class_private.h"
#include "bitmap_class.h"

////////////////////////////////////////////////////////////////////

api_bitmap_class_t * api_bitmap_class_t_class = NULL;

static bitmap_class_t * _instance_list_bitmap_class_t[64] = {0};

typedef void ( *bitmap_class_t_delete_bitmap_t )( void );

static void bitmap_class_t_delete_bitmap_instance_00( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 0] ); }
static void bitmap_class_t_delete_bitmap_instance_01( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 1] ); }
static void bitmap_class_t_delete_bitmap_instance_02( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 2] ); }
static void bitmap_class_t_delete_bitmap_instance_03( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 3] ); }
static void bitmap_class_t_delete_bitmap_instance_04( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 4] ); }
static void bitmap_class_t_delete_bitmap_instance_05( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 5] ); }
static void bitmap_class_t_delete_bitmap_instance_06( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 6] ); }
static void bitmap_class_t_delete_bitmap_instance_07( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 7] ); }
static void bitmap_class_t_delete_bitmap_instance_08( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 8] ); }
static void bitmap_class_t_delete_bitmap_instance_09( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->delete_bitmap( _instance_list_bitmap_class_t[ 9] ); }
static void bitmap_class_t_delete_bitmap_instance_10( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->delete_bitmap( _instance_list_bitmap_class_t[10] ); }
static void bitmap_class_t_delete_bitmap_instance_11( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->delete_bitmap( _instance_list_bitmap_class_t[11] ); }
static void bitmap_class_t_delete_bitmap_instance_12( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->delete_bitmap( _instance_list_bitmap_class_t[12] ); }
static void bitmap_class_t_delete_bitmap_instance_13( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->delete_bitmap( _instance_list_bitmap_class_t[13] ); }
static void bitmap_class_t_delete_bitmap_instance_14( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->delete_bitmap( _instance_list_bitmap_class_t[14] ); }
static void bitmap_class_t_delete_bitmap_instance_15( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->delete_bitmap( _instance_list_bitmap_class_t[15] ); }
static void bitmap_class_t_delete_bitmap_instance_16( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->delete_bitmap( _instance_list_bitmap_class_t[16] ); }
static void bitmap_class_t_delete_bitmap_instance_17( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->delete_bitmap( _instance_list_bitmap_class_t[17] ); }
static void bitmap_class_t_delete_bitmap_instance_18( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->delete_bitmap( _instance_list_bitmap_class_t[18] ); }
static void bitmap_class_t_delete_bitmap_instance_19( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->delete_bitmap( _instance_list_bitmap_class_t[19] ); }
static void bitmap_class_t_delete_bitmap_instance_20( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->delete_bitmap( _instance_list_bitmap_class_t[20] ); }
static void bitmap_class_t_delete_bitmap_instance_21( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->delete_bitmap( _instance_list_bitmap_class_t[21] ); }
static void bitmap_class_t_delete_bitmap_instance_22( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->delete_bitmap( _instance_list_bitmap_class_t[22] ); }
static void bitmap_class_t_delete_bitmap_instance_23( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->delete_bitmap( _instance_list_bitmap_class_t[23] ); }
static void bitmap_class_t_delete_bitmap_instance_24( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->delete_bitmap( _instance_list_bitmap_class_t[24] ); }
static void bitmap_class_t_delete_bitmap_instance_25( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->delete_bitmap( _instance_list_bitmap_class_t[25] ); }
static void bitmap_class_t_delete_bitmap_instance_26( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->delete_bitmap( _instance_list_bitmap_class_t[26] ); }
static void bitmap_class_t_delete_bitmap_instance_27( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->delete_bitmap( _instance_list_bitmap_class_t[27] ); }
static void bitmap_class_t_delete_bitmap_instance_28( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->delete_bitmap( _instance_list_bitmap_class_t[28] ); }
static void bitmap_class_t_delete_bitmap_instance_29( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->delete_bitmap( _instance_list_bitmap_class_t[29] ); }
static void bitmap_class_t_delete_bitmap_instance_30( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->delete_bitmap( _instance_list_bitmap_class_t[30] ); }
static void bitmap_class_t_delete_bitmap_instance_31( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->delete_bitmap( _instance_list_bitmap_class_t[31] ); }
static void bitmap_class_t_delete_bitmap_instance_32( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->delete_bitmap( _instance_list_bitmap_class_t[32] ); }
static void bitmap_class_t_delete_bitmap_instance_33( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->delete_bitmap( _instance_list_bitmap_class_t[33] ); }
static void bitmap_class_t_delete_bitmap_instance_34( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->delete_bitmap( _instance_list_bitmap_class_t[34] ); }
static void bitmap_class_t_delete_bitmap_instance_35( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->delete_bitmap( _instance_list_bitmap_class_t[35] ); }
static void bitmap_class_t_delete_bitmap_instance_36( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->delete_bitmap( _instance_list_bitmap_class_t[36] ); }
static void bitmap_class_t_delete_bitmap_instance_37( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->delete_bitmap( _instance_list_bitmap_class_t[37] ); }
static void bitmap_class_t_delete_bitmap_instance_38( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->delete_bitmap( _instance_list_bitmap_class_t[38] ); }
static void bitmap_class_t_delete_bitmap_instance_39( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->delete_bitmap( _instance_list_bitmap_class_t[39] ); }
static void bitmap_class_t_delete_bitmap_instance_40( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->delete_bitmap( _instance_list_bitmap_class_t[40] ); }
static void bitmap_class_t_delete_bitmap_instance_41( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->delete_bitmap( _instance_list_bitmap_class_t[41] ); }
static void bitmap_class_t_delete_bitmap_instance_42( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->delete_bitmap( _instance_list_bitmap_class_t[42] ); }
static void bitmap_class_t_delete_bitmap_instance_43( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->delete_bitmap( _instance_list_bitmap_class_t[43] ); }
static void bitmap_class_t_delete_bitmap_instance_44( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->delete_bitmap( _instance_list_bitmap_class_t[44] ); }
static void bitmap_class_t_delete_bitmap_instance_45( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->delete_bitmap( _instance_list_bitmap_class_t[45] ); }
static void bitmap_class_t_delete_bitmap_instance_46( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->delete_bitmap( _instance_list_bitmap_class_t[46] ); }
static void bitmap_class_t_delete_bitmap_instance_47( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->delete_bitmap( _instance_list_bitmap_class_t[47] ); }
static void bitmap_class_t_delete_bitmap_instance_48( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->delete_bitmap( _instance_list_bitmap_class_t[48] ); }
static void bitmap_class_t_delete_bitmap_instance_49( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->delete_bitmap( _instance_list_bitmap_class_t[49] ); }
static void bitmap_class_t_delete_bitmap_instance_50( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->delete_bitmap( _instance_list_bitmap_class_t[50] ); }
static void bitmap_class_t_delete_bitmap_instance_51( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->delete_bitmap( _instance_list_bitmap_class_t[51] ); }
static void bitmap_class_t_delete_bitmap_instance_52( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->delete_bitmap( _instance_list_bitmap_class_t[52] ); }
static void bitmap_class_t_delete_bitmap_instance_53( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->delete_bitmap( _instance_list_bitmap_class_t[53] ); }
static void bitmap_class_t_delete_bitmap_instance_54( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->delete_bitmap( _instance_list_bitmap_class_t[54] ); }
static void bitmap_class_t_delete_bitmap_instance_55( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->delete_bitmap( _instance_list_bitmap_class_t[55] ); }
static void bitmap_class_t_delete_bitmap_instance_56( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->delete_bitmap( _instance_list_bitmap_class_t[56] ); }
static void bitmap_class_t_delete_bitmap_instance_57( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->delete_bitmap( _instance_list_bitmap_class_t[57] ); }
static void bitmap_class_t_delete_bitmap_instance_58( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->delete_bitmap( _instance_list_bitmap_class_t[58] ); }
static void bitmap_class_t_delete_bitmap_instance_59( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->delete_bitmap( _instance_list_bitmap_class_t[59] ); }
static void bitmap_class_t_delete_bitmap_instance_60( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->delete_bitmap( _instance_list_bitmap_class_t[60] ); }
static void bitmap_class_t_delete_bitmap_instance_61( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->delete_bitmap( _instance_list_bitmap_class_t[61] ); }
static void bitmap_class_t_delete_bitmap_instance_62( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->delete_bitmap( _instance_list_bitmap_class_t[62] ); }
static void bitmap_class_t_delete_bitmap_instance_63( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->delete_bitmap( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_delete_bitmap_t _bitmap_class_t_delete_bitmap_list[64] =
{
    bitmap_class_t_delete_bitmap_instance_00,
    bitmap_class_t_delete_bitmap_instance_01,
    bitmap_class_t_delete_bitmap_instance_02,
    bitmap_class_t_delete_bitmap_instance_03,
    bitmap_class_t_delete_bitmap_instance_04,
    bitmap_class_t_delete_bitmap_instance_05,
    bitmap_class_t_delete_bitmap_instance_06,
    bitmap_class_t_delete_bitmap_instance_07,
    bitmap_class_t_delete_bitmap_instance_08,
    bitmap_class_t_delete_bitmap_instance_09,
    bitmap_class_t_delete_bitmap_instance_10,
    bitmap_class_t_delete_bitmap_instance_11,
    bitmap_class_t_delete_bitmap_instance_12,
    bitmap_class_t_delete_bitmap_instance_13,
    bitmap_class_t_delete_bitmap_instance_14,
    bitmap_class_t_delete_bitmap_instance_15,
    bitmap_class_t_delete_bitmap_instance_16,
    bitmap_class_t_delete_bitmap_instance_17,
    bitmap_class_t_delete_bitmap_instance_18,
    bitmap_class_t_delete_bitmap_instance_19,
    bitmap_class_t_delete_bitmap_instance_20,
    bitmap_class_t_delete_bitmap_instance_21,
    bitmap_class_t_delete_bitmap_instance_22,
    bitmap_class_t_delete_bitmap_instance_23,
    bitmap_class_t_delete_bitmap_instance_24,
    bitmap_class_t_delete_bitmap_instance_25,
    bitmap_class_t_delete_bitmap_instance_26,
    bitmap_class_t_delete_bitmap_instance_27,
    bitmap_class_t_delete_bitmap_instance_28,
    bitmap_class_t_delete_bitmap_instance_29,
    bitmap_class_t_delete_bitmap_instance_30,
    bitmap_class_t_delete_bitmap_instance_31,
    bitmap_class_t_delete_bitmap_instance_32,
    bitmap_class_t_delete_bitmap_instance_33,
    bitmap_class_t_delete_bitmap_instance_34,
    bitmap_class_t_delete_bitmap_instance_35,
    bitmap_class_t_delete_bitmap_instance_36,
    bitmap_class_t_delete_bitmap_instance_37,
    bitmap_class_t_delete_bitmap_instance_38,
    bitmap_class_t_delete_bitmap_instance_39,
    bitmap_class_t_delete_bitmap_instance_40,
    bitmap_class_t_delete_bitmap_instance_41,
    bitmap_class_t_delete_bitmap_instance_42,
    bitmap_class_t_delete_bitmap_instance_43,
    bitmap_class_t_delete_bitmap_instance_44,
    bitmap_class_t_delete_bitmap_instance_45,
    bitmap_class_t_delete_bitmap_instance_46,
    bitmap_class_t_delete_bitmap_instance_47,
    bitmap_class_t_delete_bitmap_instance_48,
    bitmap_class_t_delete_bitmap_instance_49,
    bitmap_class_t_delete_bitmap_instance_50,
    bitmap_class_t_delete_bitmap_instance_51,
    bitmap_class_t_delete_bitmap_instance_52,
    bitmap_class_t_delete_bitmap_instance_53,
    bitmap_class_t_delete_bitmap_instance_54,
    bitmap_class_t_delete_bitmap_instance_55,
    bitmap_class_t_delete_bitmap_instance_56,
    bitmap_class_t_delete_bitmap_instance_57,
    bitmap_class_t_delete_bitmap_instance_58,
    bitmap_class_t_delete_bitmap_instance_59,
    bitmap_class_t_delete_bitmap_instance_60,
    bitmap_class_t_delete_bitmap_instance_61,
    bitmap_class_t_delete_bitmap_instance_62,
    bitmap_class_t_delete_bitmap_instance_63,
};

typedef void ( *bitmap_class_t_claim_t )( void );

static void bitmap_class_t_claim_instance_00( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->claim( _instance_list_bitmap_class_t[ 0] ); }
static void bitmap_class_t_claim_instance_01( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->claim( _instance_list_bitmap_class_t[ 1] ); }
static void bitmap_class_t_claim_instance_02( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->claim( _instance_list_bitmap_class_t[ 2] ); }
static void bitmap_class_t_claim_instance_03( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->claim( _instance_list_bitmap_class_t[ 3] ); }
static void bitmap_class_t_claim_instance_04( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->claim( _instance_list_bitmap_class_t[ 4] ); }
static void bitmap_class_t_claim_instance_05( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->claim( _instance_list_bitmap_class_t[ 5] ); }
static void bitmap_class_t_claim_instance_06( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->claim( _instance_list_bitmap_class_t[ 6] ); }
static void bitmap_class_t_claim_instance_07( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->claim( _instance_list_bitmap_class_t[ 7] ); }
static void bitmap_class_t_claim_instance_08( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->claim( _instance_list_bitmap_class_t[ 8] ); }
static void bitmap_class_t_claim_instance_09( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->claim( _instance_list_bitmap_class_t[ 9] ); }
static void bitmap_class_t_claim_instance_10( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->claim( _instance_list_bitmap_class_t[10] ); }
static void bitmap_class_t_claim_instance_11( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->claim( _instance_list_bitmap_class_t[11] ); }
static void bitmap_class_t_claim_instance_12( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->claim( _instance_list_bitmap_class_t[12] ); }
static void bitmap_class_t_claim_instance_13( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->claim( _instance_list_bitmap_class_t[13] ); }
static void bitmap_class_t_claim_instance_14( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->claim( _instance_list_bitmap_class_t[14] ); }
static void bitmap_class_t_claim_instance_15( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->claim( _instance_list_bitmap_class_t[15] ); }
static void bitmap_class_t_claim_instance_16( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->claim( _instance_list_bitmap_class_t[16] ); }
static void bitmap_class_t_claim_instance_17( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->claim( _instance_list_bitmap_class_t[17] ); }
static void bitmap_class_t_claim_instance_18( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->claim( _instance_list_bitmap_class_t[18] ); }
static void bitmap_class_t_claim_instance_19( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->claim( _instance_list_bitmap_class_t[19] ); }
static void bitmap_class_t_claim_instance_20( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->claim( _instance_list_bitmap_class_t[20] ); }
static void bitmap_class_t_claim_instance_21( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->claim( _instance_list_bitmap_class_t[21] ); }
static void bitmap_class_t_claim_instance_22( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->claim( _instance_list_bitmap_class_t[22] ); }
static void bitmap_class_t_claim_instance_23( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->claim( _instance_list_bitmap_class_t[23] ); }
static void bitmap_class_t_claim_instance_24( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->claim( _instance_list_bitmap_class_t[24] ); }
static void bitmap_class_t_claim_instance_25( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->claim( _instance_list_bitmap_class_t[25] ); }
static void bitmap_class_t_claim_instance_26( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->claim( _instance_list_bitmap_class_t[26] ); }
static void bitmap_class_t_claim_instance_27( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->claim( _instance_list_bitmap_class_t[27] ); }
static void bitmap_class_t_claim_instance_28( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->claim( _instance_list_bitmap_class_t[28] ); }
static void bitmap_class_t_claim_instance_29( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->claim( _instance_list_bitmap_class_t[29] ); }
static void bitmap_class_t_claim_instance_30( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->claim( _instance_list_bitmap_class_t[30] ); }
static void bitmap_class_t_claim_instance_31( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->claim( _instance_list_bitmap_class_t[31] ); }
static void bitmap_class_t_claim_instance_32( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->claim( _instance_list_bitmap_class_t[32] ); }
static void bitmap_class_t_claim_instance_33( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->claim( _instance_list_bitmap_class_t[33] ); }
static void bitmap_class_t_claim_instance_34( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->claim( _instance_list_bitmap_class_t[34] ); }
static void bitmap_class_t_claim_instance_35( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->claim( _instance_list_bitmap_class_t[35] ); }
static void bitmap_class_t_claim_instance_36( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->claim( _instance_list_bitmap_class_t[36] ); }
static void bitmap_class_t_claim_instance_37( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->claim( _instance_list_bitmap_class_t[37] ); }
static void bitmap_class_t_claim_instance_38( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->claim( _instance_list_bitmap_class_t[38] ); }
static void bitmap_class_t_claim_instance_39( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->claim( _instance_list_bitmap_class_t[39] ); }
static void bitmap_class_t_claim_instance_40( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->claim( _instance_list_bitmap_class_t[40] ); }
static void bitmap_class_t_claim_instance_41( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->claim( _instance_list_bitmap_class_t[41] ); }
static void bitmap_class_t_claim_instance_42( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->claim( _instance_list_bitmap_class_t[42] ); }
static void bitmap_class_t_claim_instance_43( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->claim( _instance_list_bitmap_class_t[43] ); }
static void bitmap_class_t_claim_instance_44( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->claim( _instance_list_bitmap_class_t[44] ); }
static void bitmap_class_t_claim_instance_45( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->claim( _instance_list_bitmap_class_t[45] ); }
static void bitmap_class_t_claim_instance_46( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->claim( _instance_list_bitmap_class_t[46] ); }
static void bitmap_class_t_claim_instance_47( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->claim( _instance_list_bitmap_class_t[47] ); }
static void bitmap_class_t_claim_instance_48( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->claim( _instance_list_bitmap_class_t[48] ); }
static void bitmap_class_t_claim_instance_49( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->claim( _instance_list_bitmap_class_t[49] ); }
static void bitmap_class_t_claim_instance_50( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->claim( _instance_list_bitmap_class_t[50] ); }
static void bitmap_class_t_claim_instance_51( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->claim( _instance_list_bitmap_class_t[51] ); }
static void bitmap_class_t_claim_instance_52( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->claim( _instance_list_bitmap_class_t[52] ); }
static void bitmap_class_t_claim_instance_53( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->claim( _instance_list_bitmap_class_t[53] ); }
static void bitmap_class_t_claim_instance_54( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->claim( _instance_list_bitmap_class_t[54] ); }
static void bitmap_class_t_claim_instance_55( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->claim( _instance_list_bitmap_class_t[55] ); }
static void bitmap_class_t_claim_instance_56( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->claim( _instance_list_bitmap_class_t[56] ); }
static void bitmap_class_t_claim_instance_57( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->claim( _instance_list_bitmap_class_t[57] ); }
static void bitmap_class_t_claim_instance_58( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->claim( _instance_list_bitmap_class_t[58] ); }
static void bitmap_class_t_claim_instance_59( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->claim( _instance_list_bitmap_class_t[59] ); }
static void bitmap_class_t_claim_instance_60( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->claim( _instance_list_bitmap_class_t[60] ); }
static void bitmap_class_t_claim_instance_61( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->claim( _instance_list_bitmap_class_t[61] ); }
static void bitmap_class_t_claim_instance_62( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->claim( _instance_list_bitmap_class_t[62] ); }
static void bitmap_class_t_claim_instance_63( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->claim( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_claim_t _bitmap_class_t_claim_list[64] =
{
    bitmap_class_t_claim_instance_00,
    bitmap_class_t_claim_instance_01,
    bitmap_class_t_claim_instance_02,
    bitmap_class_t_claim_instance_03,
    bitmap_class_t_claim_instance_04,
    bitmap_class_t_claim_instance_05,
    bitmap_class_t_claim_instance_06,
    bitmap_class_t_claim_instance_07,
    bitmap_class_t_claim_instance_08,
    bitmap_class_t_claim_instance_09,
    bitmap_class_t_claim_instance_10,
    bitmap_class_t_claim_instance_11,
    bitmap_class_t_claim_instance_12,
    bitmap_class_t_claim_instance_13,
    bitmap_class_t_claim_instance_14,
    bitmap_class_t_claim_instance_15,
    bitmap_class_t_claim_instance_16,
    bitmap_class_t_claim_instance_17,
    bitmap_class_t_claim_instance_18,
    bitmap_class_t_claim_instance_19,
    bitmap_class_t_claim_instance_20,
    bitmap_class_t_claim_instance_21,
    bitmap_class_t_claim_instance_22,
    bitmap_class_t_claim_instance_23,
    bitmap_class_t_claim_instance_24,
    bitmap_class_t_claim_instance_25,
    bitmap_class_t_claim_instance_26,
    bitmap_class_t_claim_instance_27,
    bitmap_class_t_claim_instance_28,
    bitmap_class_t_claim_instance_29,
    bitmap_class_t_claim_instance_30,
    bitmap_class_t_claim_instance_31,
    bitmap_class_t_claim_instance_32,
    bitmap_class_t_claim_instance_33,
    bitmap_class_t_claim_instance_34,
    bitmap_class_t_claim_instance_35,
    bitmap_class_t_claim_instance_36,
    bitmap_class_t_claim_instance_37,
    bitmap_class_t_claim_instance_38,
    bitmap_class_t_claim_instance_39,
    bitmap_class_t_claim_instance_40,
    bitmap_class_t_claim_instance_41,
    bitmap_class_t_claim_instance_42,
    bitmap_class_t_claim_instance_43,
    bitmap_class_t_claim_instance_44,
    bitmap_class_t_claim_instance_45,
    bitmap_class_t_claim_instance_46,
    bitmap_class_t_claim_instance_47,
    bitmap_class_t_claim_instance_48,
    bitmap_class_t_claim_instance_49,
    bitmap_class_t_claim_instance_50,
    bitmap_class_t_claim_instance_51,
    bitmap_class_t_claim_instance_52,
    bitmap_class_t_claim_instance_53,
    bitmap_class_t_claim_instance_54,
    bitmap_class_t_claim_instance_55,
    bitmap_class_t_claim_instance_56,
    bitmap_class_t_claim_instance_57,
    bitmap_class_t_claim_instance_58,
    bitmap_class_t_claim_instance_59,
    bitmap_class_t_claim_instance_60,
    bitmap_class_t_claim_instance_61,
    bitmap_class_t_claim_instance_62,
    bitmap_class_t_claim_instance_63,
};

typedef void ( *bitmap_class_t_release_t )( void );

static void bitmap_class_t_release_instance_00( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->release( _instance_list_bitmap_class_t[ 0] ); }
static void bitmap_class_t_release_instance_01( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->release( _instance_list_bitmap_class_t[ 1] ); }
static void bitmap_class_t_release_instance_02( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->release( _instance_list_bitmap_class_t[ 2] ); }
static void bitmap_class_t_release_instance_03( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->release( _instance_list_bitmap_class_t[ 3] ); }
static void bitmap_class_t_release_instance_04( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->release( _instance_list_bitmap_class_t[ 4] ); }
static void bitmap_class_t_release_instance_05( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->release( _instance_list_bitmap_class_t[ 5] ); }
static void bitmap_class_t_release_instance_06( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->release( _instance_list_bitmap_class_t[ 6] ); }
static void bitmap_class_t_release_instance_07( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->release( _instance_list_bitmap_class_t[ 7] ); }
static void bitmap_class_t_release_instance_08( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->release( _instance_list_bitmap_class_t[ 8] ); }
static void bitmap_class_t_release_instance_09( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->release( _instance_list_bitmap_class_t[ 9] ); }
static void bitmap_class_t_release_instance_10( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->release( _instance_list_bitmap_class_t[10] ); }
static void bitmap_class_t_release_instance_11( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->release( _instance_list_bitmap_class_t[11] ); }
static void bitmap_class_t_release_instance_12( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->release( _instance_list_bitmap_class_t[12] ); }
static void bitmap_class_t_release_instance_13( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->release( _instance_list_bitmap_class_t[13] ); }
static void bitmap_class_t_release_instance_14( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->release( _instance_list_bitmap_class_t[14] ); }
static void bitmap_class_t_release_instance_15( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->release( _instance_list_bitmap_class_t[15] ); }
static void bitmap_class_t_release_instance_16( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->release( _instance_list_bitmap_class_t[16] ); }
static void bitmap_class_t_release_instance_17( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->release( _instance_list_bitmap_class_t[17] ); }
static void bitmap_class_t_release_instance_18( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->release( _instance_list_bitmap_class_t[18] ); }
static void bitmap_class_t_release_instance_19( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->release( _instance_list_bitmap_class_t[19] ); }
static void bitmap_class_t_release_instance_20( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->release( _instance_list_bitmap_class_t[20] ); }
static void bitmap_class_t_release_instance_21( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->release( _instance_list_bitmap_class_t[21] ); }
static void bitmap_class_t_release_instance_22( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->release( _instance_list_bitmap_class_t[22] ); }
static void bitmap_class_t_release_instance_23( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->release( _instance_list_bitmap_class_t[23] ); }
static void bitmap_class_t_release_instance_24( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->release( _instance_list_bitmap_class_t[24] ); }
static void bitmap_class_t_release_instance_25( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->release( _instance_list_bitmap_class_t[25] ); }
static void bitmap_class_t_release_instance_26( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->release( _instance_list_bitmap_class_t[26] ); }
static void bitmap_class_t_release_instance_27( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->release( _instance_list_bitmap_class_t[27] ); }
static void bitmap_class_t_release_instance_28( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->release( _instance_list_bitmap_class_t[28] ); }
static void bitmap_class_t_release_instance_29( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->release( _instance_list_bitmap_class_t[29] ); }
static void bitmap_class_t_release_instance_30( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->release( _instance_list_bitmap_class_t[30] ); }
static void bitmap_class_t_release_instance_31( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->release( _instance_list_bitmap_class_t[31] ); }
static void bitmap_class_t_release_instance_32( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->release( _instance_list_bitmap_class_t[32] ); }
static void bitmap_class_t_release_instance_33( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->release( _instance_list_bitmap_class_t[33] ); }
static void bitmap_class_t_release_instance_34( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->release( _instance_list_bitmap_class_t[34] ); }
static void bitmap_class_t_release_instance_35( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->release( _instance_list_bitmap_class_t[35] ); }
static void bitmap_class_t_release_instance_36( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->release( _instance_list_bitmap_class_t[36] ); }
static void bitmap_class_t_release_instance_37( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->release( _instance_list_bitmap_class_t[37] ); }
static void bitmap_class_t_release_instance_38( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->release( _instance_list_bitmap_class_t[38] ); }
static void bitmap_class_t_release_instance_39( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->release( _instance_list_bitmap_class_t[39] ); }
static void bitmap_class_t_release_instance_40( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->release( _instance_list_bitmap_class_t[40] ); }
static void bitmap_class_t_release_instance_41( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->release( _instance_list_bitmap_class_t[41] ); }
static void bitmap_class_t_release_instance_42( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->release( _instance_list_bitmap_class_t[42] ); }
static void bitmap_class_t_release_instance_43( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->release( _instance_list_bitmap_class_t[43] ); }
static void bitmap_class_t_release_instance_44( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->release( _instance_list_bitmap_class_t[44] ); }
static void bitmap_class_t_release_instance_45( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->release( _instance_list_bitmap_class_t[45] ); }
static void bitmap_class_t_release_instance_46( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->release( _instance_list_bitmap_class_t[46] ); }
static void bitmap_class_t_release_instance_47( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->release( _instance_list_bitmap_class_t[47] ); }
static void bitmap_class_t_release_instance_48( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->release( _instance_list_bitmap_class_t[48] ); }
static void bitmap_class_t_release_instance_49( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->release( _instance_list_bitmap_class_t[49] ); }
static void bitmap_class_t_release_instance_50( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->release( _instance_list_bitmap_class_t[50] ); }
static void bitmap_class_t_release_instance_51( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->release( _instance_list_bitmap_class_t[51] ); }
static void bitmap_class_t_release_instance_52( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->release( _instance_list_bitmap_class_t[52] ); }
static void bitmap_class_t_release_instance_53( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->release( _instance_list_bitmap_class_t[53] ); }
static void bitmap_class_t_release_instance_54( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->release( _instance_list_bitmap_class_t[54] ); }
static void bitmap_class_t_release_instance_55( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->release( _instance_list_bitmap_class_t[55] ); }
static void bitmap_class_t_release_instance_56( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->release( _instance_list_bitmap_class_t[56] ); }
static void bitmap_class_t_release_instance_57( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->release( _instance_list_bitmap_class_t[57] ); }
static void bitmap_class_t_release_instance_58( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->release( _instance_list_bitmap_class_t[58] ); }
static void bitmap_class_t_release_instance_59( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->release( _instance_list_bitmap_class_t[59] ); }
static void bitmap_class_t_release_instance_60( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->release( _instance_list_bitmap_class_t[60] ); }
static void bitmap_class_t_release_instance_61( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->release( _instance_list_bitmap_class_t[61] ); }
static void bitmap_class_t_release_instance_62( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->release( _instance_list_bitmap_class_t[62] ); }
static void bitmap_class_t_release_instance_63( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->release( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_release_t _bitmap_class_t_release_list[64] =
{
    bitmap_class_t_release_instance_00,
    bitmap_class_t_release_instance_01,
    bitmap_class_t_release_instance_02,
    bitmap_class_t_release_instance_03,
    bitmap_class_t_release_instance_04,
    bitmap_class_t_release_instance_05,
    bitmap_class_t_release_instance_06,
    bitmap_class_t_release_instance_07,
    bitmap_class_t_release_instance_08,
    bitmap_class_t_release_instance_09,
    bitmap_class_t_release_instance_10,
    bitmap_class_t_release_instance_11,
    bitmap_class_t_release_instance_12,
    bitmap_class_t_release_instance_13,
    bitmap_class_t_release_instance_14,
    bitmap_class_t_release_instance_15,
    bitmap_class_t_release_instance_16,
    bitmap_class_t_release_instance_17,
    bitmap_class_t_release_instance_18,
    bitmap_class_t_release_instance_19,
    bitmap_class_t_release_instance_20,
    bitmap_class_t_release_instance_21,
    bitmap_class_t_release_instance_22,
    bitmap_class_t_release_instance_23,
    bitmap_class_t_release_instance_24,
    bitmap_class_t_release_instance_25,
    bitmap_class_t_release_instance_26,
    bitmap_class_t_release_instance_27,
    bitmap_class_t_release_instance_28,
    bitmap_class_t_release_instance_29,
    bitmap_class_t_release_instance_30,
    bitmap_class_t_release_instance_31,
    bitmap_class_t_release_instance_32,
    bitmap_class_t_release_instance_33,
    bitmap_class_t_release_instance_34,
    bitmap_class_t_release_instance_35,
    bitmap_class_t_release_instance_36,
    bitmap_class_t_release_instance_37,
    bitmap_class_t_release_instance_38,
    bitmap_class_t_release_instance_39,
    bitmap_class_t_release_instance_40,
    bitmap_class_t_release_instance_41,
    bitmap_class_t_release_instance_42,
    bitmap_class_t_release_instance_43,
    bitmap_class_t_release_instance_44,
    bitmap_class_t_release_instance_45,
    bitmap_class_t_release_instance_46,
    bitmap_class_t_release_instance_47,
    bitmap_class_t_release_instance_48,
    bitmap_class_t_release_instance_49,
    bitmap_class_t_release_instance_50,
    bitmap_class_t_release_instance_51,
    bitmap_class_t_release_instance_52,
    bitmap_class_t_release_instance_53,
    bitmap_class_t_release_instance_54,
    bitmap_class_t_release_instance_55,
    bitmap_class_t_release_instance_56,
    bitmap_class_t_release_instance_57,
    bitmap_class_t_release_instance_58,
    bitmap_class_t_release_instance_59,
    bitmap_class_t_release_instance_60,
    bitmap_class_t_release_instance_61,
    bitmap_class_t_release_instance_62,
    bitmap_class_t_release_instance_63,
};

typedef void ( *bitmap_class_t_clear_t )( void );

static void bitmap_class_t_clear_instance_00( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->clear( _instance_list_bitmap_class_t[ 0] ); }
static void bitmap_class_t_clear_instance_01( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->clear( _instance_list_bitmap_class_t[ 1] ); }
static void bitmap_class_t_clear_instance_02( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->clear( _instance_list_bitmap_class_t[ 2] ); }
static void bitmap_class_t_clear_instance_03( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->clear( _instance_list_bitmap_class_t[ 3] ); }
static void bitmap_class_t_clear_instance_04( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->clear( _instance_list_bitmap_class_t[ 4] ); }
static void bitmap_class_t_clear_instance_05( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->clear( _instance_list_bitmap_class_t[ 5] ); }
static void bitmap_class_t_clear_instance_06( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->clear( _instance_list_bitmap_class_t[ 6] ); }
static void bitmap_class_t_clear_instance_07( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->clear( _instance_list_bitmap_class_t[ 7] ); }
static void bitmap_class_t_clear_instance_08( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->clear( _instance_list_bitmap_class_t[ 8] ); }
static void bitmap_class_t_clear_instance_09( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->clear( _instance_list_bitmap_class_t[ 9] ); }
static void bitmap_class_t_clear_instance_10( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->clear( _instance_list_bitmap_class_t[10] ); }
static void bitmap_class_t_clear_instance_11( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->clear( _instance_list_bitmap_class_t[11] ); }
static void bitmap_class_t_clear_instance_12( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->clear( _instance_list_bitmap_class_t[12] ); }
static void bitmap_class_t_clear_instance_13( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->clear( _instance_list_bitmap_class_t[13] ); }
static void bitmap_class_t_clear_instance_14( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->clear( _instance_list_bitmap_class_t[14] ); }
static void bitmap_class_t_clear_instance_15( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->clear( _instance_list_bitmap_class_t[15] ); }
static void bitmap_class_t_clear_instance_16( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->clear( _instance_list_bitmap_class_t[16] ); }
static void bitmap_class_t_clear_instance_17( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->clear( _instance_list_bitmap_class_t[17] ); }
static void bitmap_class_t_clear_instance_18( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->clear( _instance_list_bitmap_class_t[18] ); }
static void bitmap_class_t_clear_instance_19( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->clear( _instance_list_bitmap_class_t[19] ); }
static void bitmap_class_t_clear_instance_20( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->clear( _instance_list_bitmap_class_t[20] ); }
static void bitmap_class_t_clear_instance_21( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->clear( _instance_list_bitmap_class_t[21] ); }
static void bitmap_class_t_clear_instance_22( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->clear( _instance_list_bitmap_class_t[22] ); }
static void bitmap_class_t_clear_instance_23( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->clear( _instance_list_bitmap_class_t[23] ); }
static void bitmap_class_t_clear_instance_24( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->clear( _instance_list_bitmap_class_t[24] ); }
static void bitmap_class_t_clear_instance_25( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->clear( _instance_list_bitmap_class_t[25] ); }
static void bitmap_class_t_clear_instance_26( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->clear( _instance_list_bitmap_class_t[26] ); }
static void bitmap_class_t_clear_instance_27( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->clear( _instance_list_bitmap_class_t[27] ); }
static void bitmap_class_t_clear_instance_28( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->clear( _instance_list_bitmap_class_t[28] ); }
static void bitmap_class_t_clear_instance_29( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->clear( _instance_list_bitmap_class_t[29] ); }
static void bitmap_class_t_clear_instance_30( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->clear( _instance_list_bitmap_class_t[30] ); }
static void bitmap_class_t_clear_instance_31( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->clear( _instance_list_bitmap_class_t[31] ); }
static void bitmap_class_t_clear_instance_32( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->clear( _instance_list_bitmap_class_t[32] ); }
static void bitmap_class_t_clear_instance_33( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->clear( _instance_list_bitmap_class_t[33] ); }
static void bitmap_class_t_clear_instance_34( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->clear( _instance_list_bitmap_class_t[34] ); }
static void bitmap_class_t_clear_instance_35( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->clear( _instance_list_bitmap_class_t[35] ); }
static void bitmap_class_t_clear_instance_36( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->clear( _instance_list_bitmap_class_t[36] ); }
static void bitmap_class_t_clear_instance_37( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->clear( _instance_list_bitmap_class_t[37] ); }
static void bitmap_class_t_clear_instance_38( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->clear( _instance_list_bitmap_class_t[38] ); }
static void bitmap_class_t_clear_instance_39( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->clear( _instance_list_bitmap_class_t[39] ); }
static void bitmap_class_t_clear_instance_40( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->clear( _instance_list_bitmap_class_t[40] ); }
static void bitmap_class_t_clear_instance_41( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->clear( _instance_list_bitmap_class_t[41] ); }
static void bitmap_class_t_clear_instance_42( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->clear( _instance_list_bitmap_class_t[42] ); }
static void bitmap_class_t_clear_instance_43( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->clear( _instance_list_bitmap_class_t[43] ); }
static void bitmap_class_t_clear_instance_44( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->clear( _instance_list_bitmap_class_t[44] ); }
static void bitmap_class_t_clear_instance_45( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->clear( _instance_list_bitmap_class_t[45] ); }
static void bitmap_class_t_clear_instance_46( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->clear( _instance_list_bitmap_class_t[46] ); }
static void bitmap_class_t_clear_instance_47( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->clear( _instance_list_bitmap_class_t[47] ); }
static void bitmap_class_t_clear_instance_48( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->clear( _instance_list_bitmap_class_t[48] ); }
static void bitmap_class_t_clear_instance_49( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->clear( _instance_list_bitmap_class_t[49] ); }
static void bitmap_class_t_clear_instance_50( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->clear( _instance_list_bitmap_class_t[50] ); }
static void bitmap_class_t_clear_instance_51( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->clear( _instance_list_bitmap_class_t[51] ); }
static void bitmap_class_t_clear_instance_52( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->clear( _instance_list_bitmap_class_t[52] ); }
static void bitmap_class_t_clear_instance_53( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->clear( _instance_list_bitmap_class_t[53] ); }
static void bitmap_class_t_clear_instance_54( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->clear( _instance_list_bitmap_class_t[54] ); }
static void bitmap_class_t_clear_instance_55( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->clear( _instance_list_bitmap_class_t[55] ); }
static void bitmap_class_t_clear_instance_56( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->clear( _instance_list_bitmap_class_t[56] ); }
static void bitmap_class_t_clear_instance_57( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->clear( _instance_list_bitmap_class_t[57] ); }
static void bitmap_class_t_clear_instance_58( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->clear( _instance_list_bitmap_class_t[58] ); }
static void bitmap_class_t_clear_instance_59( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->clear( _instance_list_bitmap_class_t[59] ); }
static void bitmap_class_t_clear_instance_60( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->clear( _instance_list_bitmap_class_t[60] ); }
static void bitmap_class_t_clear_instance_61( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->clear( _instance_list_bitmap_class_t[61] ); }
static void bitmap_class_t_clear_instance_62( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->clear( _instance_list_bitmap_class_t[62] ); }
static void bitmap_class_t_clear_instance_63( void ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->clear( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_clear_t _bitmap_class_t_clear_list[64] =
{
    bitmap_class_t_clear_instance_00,
    bitmap_class_t_clear_instance_01,
    bitmap_class_t_clear_instance_02,
    bitmap_class_t_clear_instance_03,
    bitmap_class_t_clear_instance_04,
    bitmap_class_t_clear_instance_05,
    bitmap_class_t_clear_instance_06,
    bitmap_class_t_clear_instance_07,
    bitmap_class_t_clear_instance_08,
    bitmap_class_t_clear_instance_09,
    bitmap_class_t_clear_instance_10,
    bitmap_class_t_clear_instance_11,
    bitmap_class_t_clear_instance_12,
    bitmap_class_t_clear_instance_13,
    bitmap_class_t_clear_instance_14,
    bitmap_class_t_clear_instance_15,
    bitmap_class_t_clear_instance_16,
    bitmap_class_t_clear_instance_17,
    bitmap_class_t_clear_instance_18,
    bitmap_class_t_clear_instance_19,
    bitmap_class_t_clear_instance_20,
    bitmap_class_t_clear_instance_21,
    bitmap_class_t_clear_instance_22,
    bitmap_class_t_clear_instance_23,
    bitmap_class_t_clear_instance_24,
    bitmap_class_t_clear_instance_25,
    bitmap_class_t_clear_instance_26,
    bitmap_class_t_clear_instance_27,
    bitmap_class_t_clear_instance_28,
    bitmap_class_t_clear_instance_29,
    bitmap_class_t_clear_instance_30,
    bitmap_class_t_clear_instance_31,
    bitmap_class_t_clear_instance_32,
    bitmap_class_t_clear_instance_33,
    bitmap_class_t_clear_instance_34,
    bitmap_class_t_clear_instance_35,
    bitmap_class_t_clear_instance_36,
    bitmap_class_t_clear_instance_37,
    bitmap_class_t_clear_instance_38,
    bitmap_class_t_clear_instance_39,
    bitmap_class_t_clear_instance_40,
    bitmap_class_t_clear_instance_41,
    bitmap_class_t_clear_instance_42,
    bitmap_class_t_clear_instance_43,
    bitmap_class_t_clear_instance_44,
    bitmap_class_t_clear_instance_45,
    bitmap_class_t_clear_instance_46,
    bitmap_class_t_clear_instance_47,
    bitmap_class_t_clear_instance_48,
    bitmap_class_t_clear_instance_49,
    bitmap_class_t_clear_instance_50,
    bitmap_class_t_clear_instance_51,
    bitmap_class_t_clear_instance_52,
    bitmap_class_t_clear_instance_53,
    bitmap_class_t_clear_instance_54,
    bitmap_class_t_clear_instance_55,
    bitmap_class_t_clear_instance_56,
    bitmap_class_t_clear_instance_57,
    bitmap_class_t_clear_instance_58,
    bitmap_class_t_clear_instance_59,
    bitmap_class_t_clear_instance_60,
    bitmap_class_t_clear_instance_61,
    bitmap_class_t_clear_instance_62,
    bitmap_class_t_clear_instance_63,
};

typedef uint16_t ( *bitmap_class_t_get_width_t )( void );

static uint16_t bitmap_class_t_get_width_instance_00( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->get_width( _instance_list_bitmap_class_t[ 0] ); }
static uint16_t bitmap_class_t_get_width_instance_01( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->get_width( _instance_list_bitmap_class_t[ 1] ); }
static uint16_t bitmap_class_t_get_width_instance_02( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->get_width( _instance_list_bitmap_class_t[ 2] ); }
static uint16_t bitmap_class_t_get_width_instance_03( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->get_width( _instance_list_bitmap_class_t[ 3] ); }
static uint16_t bitmap_class_t_get_width_instance_04( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->get_width( _instance_list_bitmap_class_t[ 4] ); }
static uint16_t bitmap_class_t_get_width_instance_05( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->get_width( _instance_list_bitmap_class_t[ 5] ); }
static uint16_t bitmap_class_t_get_width_instance_06( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->get_width( _instance_list_bitmap_class_t[ 6] ); }
static uint16_t bitmap_class_t_get_width_instance_07( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->get_width( _instance_list_bitmap_class_t[ 7] ); }
static uint16_t bitmap_class_t_get_width_instance_08( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->get_width( _instance_list_bitmap_class_t[ 8] ); }
static uint16_t bitmap_class_t_get_width_instance_09( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->get_width( _instance_list_bitmap_class_t[ 9] ); }
static uint16_t bitmap_class_t_get_width_instance_10( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->get_width( _instance_list_bitmap_class_t[10] ); }
static uint16_t bitmap_class_t_get_width_instance_11( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->get_width( _instance_list_bitmap_class_t[11] ); }
static uint16_t bitmap_class_t_get_width_instance_12( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->get_width( _instance_list_bitmap_class_t[12] ); }
static uint16_t bitmap_class_t_get_width_instance_13( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->get_width( _instance_list_bitmap_class_t[13] ); }
static uint16_t bitmap_class_t_get_width_instance_14( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->get_width( _instance_list_bitmap_class_t[14] ); }
static uint16_t bitmap_class_t_get_width_instance_15( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->get_width( _instance_list_bitmap_class_t[15] ); }
static uint16_t bitmap_class_t_get_width_instance_16( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->get_width( _instance_list_bitmap_class_t[16] ); }
static uint16_t bitmap_class_t_get_width_instance_17( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->get_width( _instance_list_bitmap_class_t[17] ); }
static uint16_t bitmap_class_t_get_width_instance_18( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->get_width( _instance_list_bitmap_class_t[18] ); }
static uint16_t bitmap_class_t_get_width_instance_19( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->get_width( _instance_list_bitmap_class_t[19] ); }
static uint16_t bitmap_class_t_get_width_instance_20( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->get_width( _instance_list_bitmap_class_t[20] ); }
static uint16_t bitmap_class_t_get_width_instance_21( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->get_width( _instance_list_bitmap_class_t[21] ); }
static uint16_t bitmap_class_t_get_width_instance_22( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->get_width( _instance_list_bitmap_class_t[22] ); }
static uint16_t bitmap_class_t_get_width_instance_23( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->get_width( _instance_list_bitmap_class_t[23] ); }
static uint16_t bitmap_class_t_get_width_instance_24( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->get_width( _instance_list_bitmap_class_t[24] ); }
static uint16_t bitmap_class_t_get_width_instance_25( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->get_width( _instance_list_bitmap_class_t[25] ); }
static uint16_t bitmap_class_t_get_width_instance_26( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->get_width( _instance_list_bitmap_class_t[26] ); }
static uint16_t bitmap_class_t_get_width_instance_27( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->get_width( _instance_list_bitmap_class_t[27] ); }
static uint16_t bitmap_class_t_get_width_instance_28( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->get_width( _instance_list_bitmap_class_t[28] ); }
static uint16_t bitmap_class_t_get_width_instance_29( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->get_width( _instance_list_bitmap_class_t[29] ); }
static uint16_t bitmap_class_t_get_width_instance_30( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->get_width( _instance_list_bitmap_class_t[30] ); }
static uint16_t bitmap_class_t_get_width_instance_31( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->get_width( _instance_list_bitmap_class_t[31] ); }
static uint16_t bitmap_class_t_get_width_instance_32( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->get_width( _instance_list_bitmap_class_t[32] ); }
static uint16_t bitmap_class_t_get_width_instance_33( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->get_width( _instance_list_bitmap_class_t[33] ); }
static uint16_t bitmap_class_t_get_width_instance_34( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->get_width( _instance_list_bitmap_class_t[34] ); }
static uint16_t bitmap_class_t_get_width_instance_35( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->get_width( _instance_list_bitmap_class_t[35] ); }
static uint16_t bitmap_class_t_get_width_instance_36( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->get_width( _instance_list_bitmap_class_t[36] ); }
static uint16_t bitmap_class_t_get_width_instance_37( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->get_width( _instance_list_bitmap_class_t[37] ); }
static uint16_t bitmap_class_t_get_width_instance_38( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->get_width( _instance_list_bitmap_class_t[38] ); }
static uint16_t bitmap_class_t_get_width_instance_39( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->get_width( _instance_list_bitmap_class_t[39] ); }
static uint16_t bitmap_class_t_get_width_instance_40( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->get_width( _instance_list_bitmap_class_t[40] ); }
static uint16_t bitmap_class_t_get_width_instance_41( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->get_width( _instance_list_bitmap_class_t[41] ); }
static uint16_t bitmap_class_t_get_width_instance_42( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->get_width( _instance_list_bitmap_class_t[42] ); }
static uint16_t bitmap_class_t_get_width_instance_43( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->get_width( _instance_list_bitmap_class_t[43] ); }
static uint16_t bitmap_class_t_get_width_instance_44( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->get_width( _instance_list_bitmap_class_t[44] ); }
static uint16_t bitmap_class_t_get_width_instance_45( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->get_width( _instance_list_bitmap_class_t[45] ); }
static uint16_t bitmap_class_t_get_width_instance_46( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->get_width( _instance_list_bitmap_class_t[46] ); }
static uint16_t bitmap_class_t_get_width_instance_47( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->get_width( _instance_list_bitmap_class_t[47] ); }
static uint16_t bitmap_class_t_get_width_instance_48( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->get_width( _instance_list_bitmap_class_t[48] ); }
static uint16_t bitmap_class_t_get_width_instance_49( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->get_width( _instance_list_bitmap_class_t[49] ); }
static uint16_t bitmap_class_t_get_width_instance_50( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->get_width( _instance_list_bitmap_class_t[50] ); }
static uint16_t bitmap_class_t_get_width_instance_51( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->get_width( _instance_list_bitmap_class_t[51] ); }
static uint16_t bitmap_class_t_get_width_instance_52( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->get_width( _instance_list_bitmap_class_t[52] ); }
static uint16_t bitmap_class_t_get_width_instance_53( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->get_width( _instance_list_bitmap_class_t[53] ); }
static uint16_t bitmap_class_t_get_width_instance_54( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->get_width( _instance_list_bitmap_class_t[54] ); }
static uint16_t bitmap_class_t_get_width_instance_55( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->get_width( _instance_list_bitmap_class_t[55] ); }
static uint16_t bitmap_class_t_get_width_instance_56( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->get_width( _instance_list_bitmap_class_t[56] ); }
static uint16_t bitmap_class_t_get_width_instance_57( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->get_width( _instance_list_bitmap_class_t[57] ); }
static uint16_t bitmap_class_t_get_width_instance_58( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->get_width( _instance_list_bitmap_class_t[58] ); }
static uint16_t bitmap_class_t_get_width_instance_59( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->get_width( _instance_list_bitmap_class_t[59] ); }
static uint16_t bitmap_class_t_get_width_instance_60( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->get_width( _instance_list_bitmap_class_t[60] ); }
static uint16_t bitmap_class_t_get_width_instance_61( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->get_width( _instance_list_bitmap_class_t[61] ); }
static uint16_t bitmap_class_t_get_width_instance_62( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->get_width( _instance_list_bitmap_class_t[62] ); }
static uint16_t bitmap_class_t_get_width_instance_63( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->get_width( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_get_width_t _bitmap_class_t_get_width_list[64] =
{
    bitmap_class_t_get_width_instance_00,
    bitmap_class_t_get_width_instance_01,
    bitmap_class_t_get_width_instance_02,
    bitmap_class_t_get_width_instance_03,
    bitmap_class_t_get_width_instance_04,
    bitmap_class_t_get_width_instance_05,
    bitmap_class_t_get_width_instance_06,
    bitmap_class_t_get_width_instance_07,
    bitmap_class_t_get_width_instance_08,
    bitmap_class_t_get_width_instance_09,
    bitmap_class_t_get_width_instance_10,
    bitmap_class_t_get_width_instance_11,
    bitmap_class_t_get_width_instance_12,
    bitmap_class_t_get_width_instance_13,
    bitmap_class_t_get_width_instance_14,
    bitmap_class_t_get_width_instance_15,
    bitmap_class_t_get_width_instance_16,
    bitmap_class_t_get_width_instance_17,
    bitmap_class_t_get_width_instance_18,
    bitmap_class_t_get_width_instance_19,
    bitmap_class_t_get_width_instance_20,
    bitmap_class_t_get_width_instance_21,
    bitmap_class_t_get_width_instance_22,
    bitmap_class_t_get_width_instance_23,
    bitmap_class_t_get_width_instance_24,
    bitmap_class_t_get_width_instance_25,
    bitmap_class_t_get_width_instance_26,
    bitmap_class_t_get_width_instance_27,
    bitmap_class_t_get_width_instance_28,
    bitmap_class_t_get_width_instance_29,
    bitmap_class_t_get_width_instance_30,
    bitmap_class_t_get_width_instance_31,
    bitmap_class_t_get_width_instance_32,
    bitmap_class_t_get_width_instance_33,
    bitmap_class_t_get_width_instance_34,
    bitmap_class_t_get_width_instance_35,
    bitmap_class_t_get_width_instance_36,
    bitmap_class_t_get_width_instance_37,
    bitmap_class_t_get_width_instance_38,
    bitmap_class_t_get_width_instance_39,
    bitmap_class_t_get_width_instance_40,
    bitmap_class_t_get_width_instance_41,
    bitmap_class_t_get_width_instance_42,
    bitmap_class_t_get_width_instance_43,
    bitmap_class_t_get_width_instance_44,
    bitmap_class_t_get_width_instance_45,
    bitmap_class_t_get_width_instance_46,
    bitmap_class_t_get_width_instance_47,
    bitmap_class_t_get_width_instance_48,
    bitmap_class_t_get_width_instance_49,
    bitmap_class_t_get_width_instance_50,
    bitmap_class_t_get_width_instance_51,
    bitmap_class_t_get_width_instance_52,
    bitmap_class_t_get_width_instance_53,
    bitmap_class_t_get_width_instance_54,
    bitmap_class_t_get_width_instance_55,
    bitmap_class_t_get_width_instance_56,
    bitmap_class_t_get_width_instance_57,
    bitmap_class_t_get_width_instance_58,
    bitmap_class_t_get_width_instance_59,
    bitmap_class_t_get_width_instance_60,
    bitmap_class_t_get_width_instance_61,
    bitmap_class_t_get_width_instance_62,
    bitmap_class_t_get_width_instance_63,
};

typedef uint16_t ( *bitmap_class_t_get_height_t )( void );

static uint16_t bitmap_class_t_get_height_instance_00( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->get_height( _instance_list_bitmap_class_t[ 0] ); }
static uint16_t bitmap_class_t_get_height_instance_01( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->get_height( _instance_list_bitmap_class_t[ 1] ); }
static uint16_t bitmap_class_t_get_height_instance_02( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->get_height( _instance_list_bitmap_class_t[ 2] ); }
static uint16_t bitmap_class_t_get_height_instance_03( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->get_height( _instance_list_bitmap_class_t[ 3] ); }
static uint16_t bitmap_class_t_get_height_instance_04( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->get_height( _instance_list_bitmap_class_t[ 4] ); }
static uint16_t bitmap_class_t_get_height_instance_05( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->get_height( _instance_list_bitmap_class_t[ 5] ); }
static uint16_t bitmap_class_t_get_height_instance_06( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->get_height( _instance_list_bitmap_class_t[ 6] ); }
static uint16_t bitmap_class_t_get_height_instance_07( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->get_height( _instance_list_bitmap_class_t[ 7] ); }
static uint16_t bitmap_class_t_get_height_instance_08( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->get_height( _instance_list_bitmap_class_t[ 8] ); }
static uint16_t bitmap_class_t_get_height_instance_09( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->get_height( _instance_list_bitmap_class_t[ 9] ); }
static uint16_t bitmap_class_t_get_height_instance_10( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->get_height( _instance_list_bitmap_class_t[10] ); }
static uint16_t bitmap_class_t_get_height_instance_11( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->get_height( _instance_list_bitmap_class_t[11] ); }
static uint16_t bitmap_class_t_get_height_instance_12( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->get_height( _instance_list_bitmap_class_t[12] ); }
static uint16_t bitmap_class_t_get_height_instance_13( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->get_height( _instance_list_bitmap_class_t[13] ); }
static uint16_t bitmap_class_t_get_height_instance_14( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->get_height( _instance_list_bitmap_class_t[14] ); }
static uint16_t bitmap_class_t_get_height_instance_15( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->get_height( _instance_list_bitmap_class_t[15] ); }
static uint16_t bitmap_class_t_get_height_instance_16( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->get_height( _instance_list_bitmap_class_t[16] ); }
static uint16_t bitmap_class_t_get_height_instance_17( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->get_height( _instance_list_bitmap_class_t[17] ); }
static uint16_t bitmap_class_t_get_height_instance_18( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->get_height( _instance_list_bitmap_class_t[18] ); }
static uint16_t bitmap_class_t_get_height_instance_19( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->get_height( _instance_list_bitmap_class_t[19] ); }
static uint16_t bitmap_class_t_get_height_instance_20( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->get_height( _instance_list_bitmap_class_t[20] ); }
static uint16_t bitmap_class_t_get_height_instance_21( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->get_height( _instance_list_bitmap_class_t[21] ); }
static uint16_t bitmap_class_t_get_height_instance_22( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->get_height( _instance_list_bitmap_class_t[22] ); }
static uint16_t bitmap_class_t_get_height_instance_23( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->get_height( _instance_list_bitmap_class_t[23] ); }
static uint16_t bitmap_class_t_get_height_instance_24( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->get_height( _instance_list_bitmap_class_t[24] ); }
static uint16_t bitmap_class_t_get_height_instance_25( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->get_height( _instance_list_bitmap_class_t[25] ); }
static uint16_t bitmap_class_t_get_height_instance_26( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->get_height( _instance_list_bitmap_class_t[26] ); }
static uint16_t bitmap_class_t_get_height_instance_27( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->get_height( _instance_list_bitmap_class_t[27] ); }
static uint16_t bitmap_class_t_get_height_instance_28( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->get_height( _instance_list_bitmap_class_t[28] ); }
static uint16_t bitmap_class_t_get_height_instance_29( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->get_height( _instance_list_bitmap_class_t[29] ); }
static uint16_t bitmap_class_t_get_height_instance_30( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->get_height( _instance_list_bitmap_class_t[30] ); }
static uint16_t bitmap_class_t_get_height_instance_31( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->get_height( _instance_list_bitmap_class_t[31] ); }
static uint16_t bitmap_class_t_get_height_instance_32( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->get_height( _instance_list_bitmap_class_t[32] ); }
static uint16_t bitmap_class_t_get_height_instance_33( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->get_height( _instance_list_bitmap_class_t[33] ); }
static uint16_t bitmap_class_t_get_height_instance_34( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->get_height( _instance_list_bitmap_class_t[34] ); }
static uint16_t bitmap_class_t_get_height_instance_35( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->get_height( _instance_list_bitmap_class_t[35] ); }
static uint16_t bitmap_class_t_get_height_instance_36( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->get_height( _instance_list_bitmap_class_t[36] ); }
static uint16_t bitmap_class_t_get_height_instance_37( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->get_height( _instance_list_bitmap_class_t[37] ); }
static uint16_t bitmap_class_t_get_height_instance_38( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->get_height( _instance_list_bitmap_class_t[38] ); }
static uint16_t bitmap_class_t_get_height_instance_39( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->get_height( _instance_list_bitmap_class_t[39] ); }
static uint16_t bitmap_class_t_get_height_instance_40( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->get_height( _instance_list_bitmap_class_t[40] ); }
static uint16_t bitmap_class_t_get_height_instance_41( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->get_height( _instance_list_bitmap_class_t[41] ); }
static uint16_t bitmap_class_t_get_height_instance_42( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->get_height( _instance_list_bitmap_class_t[42] ); }
static uint16_t bitmap_class_t_get_height_instance_43( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->get_height( _instance_list_bitmap_class_t[43] ); }
static uint16_t bitmap_class_t_get_height_instance_44( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->get_height( _instance_list_bitmap_class_t[44] ); }
static uint16_t bitmap_class_t_get_height_instance_45( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->get_height( _instance_list_bitmap_class_t[45] ); }
static uint16_t bitmap_class_t_get_height_instance_46( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->get_height( _instance_list_bitmap_class_t[46] ); }
static uint16_t bitmap_class_t_get_height_instance_47( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->get_height( _instance_list_bitmap_class_t[47] ); }
static uint16_t bitmap_class_t_get_height_instance_48( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->get_height( _instance_list_bitmap_class_t[48] ); }
static uint16_t bitmap_class_t_get_height_instance_49( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->get_height( _instance_list_bitmap_class_t[49] ); }
static uint16_t bitmap_class_t_get_height_instance_50( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->get_height( _instance_list_bitmap_class_t[50] ); }
static uint16_t bitmap_class_t_get_height_instance_51( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->get_height( _instance_list_bitmap_class_t[51] ); }
static uint16_t bitmap_class_t_get_height_instance_52( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->get_height( _instance_list_bitmap_class_t[52] ); }
static uint16_t bitmap_class_t_get_height_instance_53( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->get_height( _instance_list_bitmap_class_t[53] ); }
static uint16_t bitmap_class_t_get_height_instance_54( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->get_height( _instance_list_bitmap_class_t[54] ); }
static uint16_t bitmap_class_t_get_height_instance_55( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->get_height( _instance_list_bitmap_class_t[55] ); }
static uint16_t bitmap_class_t_get_height_instance_56( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->get_height( _instance_list_bitmap_class_t[56] ); }
static uint16_t bitmap_class_t_get_height_instance_57( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->get_height( _instance_list_bitmap_class_t[57] ); }
static uint16_t bitmap_class_t_get_height_instance_58( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->get_height( _instance_list_bitmap_class_t[58] ); }
static uint16_t bitmap_class_t_get_height_instance_59( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->get_height( _instance_list_bitmap_class_t[59] ); }
static uint16_t bitmap_class_t_get_height_instance_60( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->get_height( _instance_list_bitmap_class_t[60] ); }
static uint16_t bitmap_class_t_get_height_instance_61( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->get_height( _instance_list_bitmap_class_t[61] ); }
static uint16_t bitmap_class_t_get_height_instance_62( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->get_height( _instance_list_bitmap_class_t[62] ); }
static uint16_t bitmap_class_t_get_height_instance_63( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->get_height( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_get_height_t _bitmap_class_t_get_height_list[64] =
{
    bitmap_class_t_get_height_instance_00,
    bitmap_class_t_get_height_instance_01,
    bitmap_class_t_get_height_instance_02,
    bitmap_class_t_get_height_instance_03,
    bitmap_class_t_get_height_instance_04,
    bitmap_class_t_get_height_instance_05,
    bitmap_class_t_get_height_instance_06,
    bitmap_class_t_get_height_instance_07,
    bitmap_class_t_get_height_instance_08,
    bitmap_class_t_get_height_instance_09,
    bitmap_class_t_get_height_instance_10,
    bitmap_class_t_get_height_instance_11,
    bitmap_class_t_get_height_instance_12,
    bitmap_class_t_get_height_instance_13,
    bitmap_class_t_get_height_instance_14,
    bitmap_class_t_get_height_instance_15,
    bitmap_class_t_get_height_instance_16,
    bitmap_class_t_get_height_instance_17,
    bitmap_class_t_get_height_instance_18,
    bitmap_class_t_get_height_instance_19,
    bitmap_class_t_get_height_instance_20,
    bitmap_class_t_get_height_instance_21,
    bitmap_class_t_get_height_instance_22,
    bitmap_class_t_get_height_instance_23,
    bitmap_class_t_get_height_instance_24,
    bitmap_class_t_get_height_instance_25,
    bitmap_class_t_get_height_instance_26,
    bitmap_class_t_get_height_instance_27,
    bitmap_class_t_get_height_instance_28,
    bitmap_class_t_get_height_instance_29,
    bitmap_class_t_get_height_instance_30,
    bitmap_class_t_get_height_instance_31,
    bitmap_class_t_get_height_instance_32,
    bitmap_class_t_get_height_instance_33,
    bitmap_class_t_get_height_instance_34,
    bitmap_class_t_get_height_instance_35,
    bitmap_class_t_get_height_instance_36,
    bitmap_class_t_get_height_instance_37,
    bitmap_class_t_get_height_instance_38,
    bitmap_class_t_get_height_instance_39,
    bitmap_class_t_get_height_instance_40,
    bitmap_class_t_get_height_instance_41,
    bitmap_class_t_get_height_instance_42,
    bitmap_class_t_get_height_instance_43,
    bitmap_class_t_get_height_instance_44,
    bitmap_class_t_get_height_instance_45,
    bitmap_class_t_get_height_instance_46,
    bitmap_class_t_get_height_instance_47,
    bitmap_class_t_get_height_instance_48,
    bitmap_class_t_get_height_instance_49,
    bitmap_class_t_get_height_instance_50,
    bitmap_class_t_get_height_instance_51,
    bitmap_class_t_get_height_instance_52,
    bitmap_class_t_get_height_instance_53,
    bitmap_class_t_get_height_instance_54,
    bitmap_class_t_get_height_instance_55,
    bitmap_class_t_get_height_instance_56,
    bitmap_class_t_get_height_instance_57,
    bitmap_class_t_get_height_instance_58,
    bitmap_class_t_get_height_instance_59,
    bitmap_class_t_get_height_instance_60,
    bitmap_class_t_get_height_instance_61,
    bitmap_class_t_get_height_instance_62,
    bitmap_class_t_get_height_instance_63,
};

typedef uint32_t ( *bitmap_class_t_get_pixel_t )( uint16_t posx, uint16_t posy );

static uint32_t bitmap_class_t_get_pixel_instance_00( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->get_pixel( _instance_list_bitmap_class_t[ 0], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_01( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->get_pixel( _instance_list_bitmap_class_t[ 1], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_02( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->get_pixel( _instance_list_bitmap_class_t[ 2], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_03( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->get_pixel( _instance_list_bitmap_class_t[ 3], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_04( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->get_pixel( _instance_list_bitmap_class_t[ 4], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_05( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->get_pixel( _instance_list_bitmap_class_t[ 5], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_06( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->get_pixel( _instance_list_bitmap_class_t[ 6], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_07( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->get_pixel( _instance_list_bitmap_class_t[ 7], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_08( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->get_pixel( _instance_list_bitmap_class_t[ 8], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_09( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->get_pixel( _instance_list_bitmap_class_t[ 9], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_10( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->get_pixel( _instance_list_bitmap_class_t[10], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_11( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->get_pixel( _instance_list_bitmap_class_t[11], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_12( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->get_pixel( _instance_list_bitmap_class_t[12], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_13( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->get_pixel( _instance_list_bitmap_class_t[13], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_14( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->get_pixel( _instance_list_bitmap_class_t[14], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_15( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->get_pixel( _instance_list_bitmap_class_t[15], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_16( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->get_pixel( _instance_list_bitmap_class_t[16], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_17( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->get_pixel( _instance_list_bitmap_class_t[17], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_18( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->get_pixel( _instance_list_bitmap_class_t[18], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_19( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->get_pixel( _instance_list_bitmap_class_t[19], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_20( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->get_pixel( _instance_list_bitmap_class_t[20], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_21( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->get_pixel( _instance_list_bitmap_class_t[21], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_22( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->get_pixel( _instance_list_bitmap_class_t[22], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_23( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->get_pixel( _instance_list_bitmap_class_t[23], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_24( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->get_pixel( _instance_list_bitmap_class_t[24], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_25( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->get_pixel( _instance_list_bitmap_class_t[25], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_26( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->get_pixel( _instance_list_bitmap_class_t[26], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_27( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->get_pixel( _instance_list_bitmap_class_t[27], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_28( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->get_pixel( _instance_list_bitmap_class_t[28], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_29( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->get_pixel( _instance_list_bitmap_class_t[29], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_30( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->get_pixel( _instance_list_bitmap_class_t[30], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_31( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->get_pixel( _instance_list_bitmap_class_t[31], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_32( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->get_pixel( _instance_list_bitmap_class_t[32], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_33( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->get_pixel( _instance_list_bitmap_class_t[33], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_34( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->get_pixel( _instance_list_bitmap_class_t[34], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_35( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->get_pixel( _instance_list_bitmap_class_t[35], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_36( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->get_pixel( _instance_list_bitmap_class_t[36], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_37( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->get_pixel( _instance_list_bitmap_class_t[37], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_38( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->get_pixel( _instance_list_bitmap_class_t[38], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_39( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->get_pixel( _instance_list_bitmap_class_t[39], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_40( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->get_pixel( _instance_list_bitmap_class_t[40], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_41( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->get_pixel( _instance_list_bitmap_class_t[41], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_42( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->get_pixel( _instance_list_bitmap_class_t[42], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_43( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->get_pixel( _instance_list_bitmap_class_t[43], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_44( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->get_pixel( _instance_list_bitmap_class_t[44], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_45( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->get_pixel( _instance_list_bitmap_class_t[45], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_46( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->get_pixel( _instance_list_bitmap_class_t[46], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_47( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->get_pixel( _instance_list_bitmap_class_t[47], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_48( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->get_pixel( _instance_list_bitmap_class_t[48], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_49( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->get_pixel( _instance_list_bitmap_class_t[49], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_50( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->get_pixel( _instance_list_bitmap_class_t[50], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_51( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->get_pixel( _instance_list_bitmap_class_t[51], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_52( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->get_pixel( _instance_list_bitmap_class_t[52], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_53( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->get_pixel( _instance_list_bitmap_class_t[53], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_54( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->get_pixel( _instance_list_bitmap_class_t[54], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_55( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->get_pixel( _instance_list_bitmap_class_t[55], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_56( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->get_pixel( _instance_list_bitmap_class_t[56], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_57( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->get_pixel( _instance_list_bitmap_class_t[57], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_58( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->get_pixel( _instance_list_bitmap_class_t[58], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_59( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->get_pixel( _instance_list_bitmap_class_t[59], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_60( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->get_pixel( _instance_list_bitmap_class_t[60], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_61( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->get_pixel( _instance_list_bitmap_class_t[61], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_62( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->get_pixel( _instance_list_bitmap_class_t[62], posx, posy ); }
static uint32_t bitmap_class_t_get_pixel_instance_63( uint16_t posx, uint16_t posy ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->get_pixel( _instance_list_bitmap_class_t[63], posx, posy ); }

static const bitmap_class_t_get_pixel_t _bitmap_class_t_get_pixel_list[64] =
{
    bitmap_class_t_get_pixel_instance_00,
    bitmap_class_t_get_pixel_instance_01,
    bitmap_class_t_get_pixel_instance_02,
    bitmap_class_t_get_pixel_instance_03,
    bitmap_class_t_get_pixel_instance_04,
    bitmap_class_t_get_pixel_instance_05,
    bitmap_class_t_get_pixel_instance_06,
    bitmap_class_t_get_pixel_instance_07,
    bitmap_class_t_get_pixel_instance_08,
    bitmap_class_t_get_pixel_instance_09,
    bitmap_class_t_get_pixel_instance_10,
    bitmap_class_t_get_pixel_instance_11,
    bitmap_class_t_get_pixel_instance_12,
    bitmap_class_t_get_pixel_instance_13,
    bitmap_class_t_get_pixel_instance_14,
    bitmap_class_t_get_pixel_instance_15,
    bitmap_class_t_get_pixel_instance_16,
    bitmap_class_t_get_pixel_instance_17,
    bitmap_class_t_get_pixel_instance_18,
    bitmap_class_t_get_pixel_instance_19,
    bitmap_class_t_get_pixel_instance_20,
    bitmap_class_t_get_pixel_instance_21,
    bitmap_class_t_get_pixel_instance_22,
    bitmap_class_t_get_pixel_instance_23,
    bitmap_class_t_get_pixel_instance_24,
    bitmap_class_t_get_pixel_instance_25,
    bitmap_class_t_get_pixel_instance_26,
    bitmap_class_t_get_pixel_instance_27,
    bitmap_class_t_get_pixel_instance_28,
    bitmap_class_t_get_pixel_instance_29,
    bitmap_class_t_get_pixel_instance_30,
    bitmap_class_t_get_pixel_instance_31,
    bitmap_class_t_get_pixel_instance_32,
    bitmap_class_t_get_pixel_instance_33,
    bitmap_class_t_get_pixel_instance_34,
    bitmap_class_t_get_pixel_instance_35,
    bitmap_class_t_get_pixel_instance_36,
    bitmap_class_t_get_pixel_instance_37,
    bitmap_class_t_get_pixel_instance_38,
    bitmap_class_t_get_pixel_instance_39,
    bitmap_class_t_get_pixel_instance_40,
    bitmap_class_t_get_pixel_instance_41,
    bitmap_class_t_get_pixel_instance_42,
    bitmap_class_t_get_pixel_instance_43,
    bitmap_class_t_get_pixel_instance_44,
    bitmap_class_t_get_pixel_instance_45,
    bitmap_class_t_get_pixel_instance_46,
    bitmap_class_t_get_pixel_instance_47,
    bitmap_class_t_get_pixel_instance_48,
    bitmap_class_t_get_pixel_instance_49,
    bitmap_class_t_get_pixel_instance_50,
    bitmap_class_t_get_pixel_instance_51,
    bitmap_class_t_get_pixel_instance_52,
    bitmap_class_t_get_pixel_instance_53,
    bitmap_class_t_get_pixel_instance_54,
    bitmap_class_t_get_pixel_instance_55,
    bitmap_class_t_get_pixel_instance_56,
    bitmap_class_t_get_pixel_instance_57,
    bitmap_class_t_get_pixel_instance_58,
    bitmap_class_t_get_pixel_instance_59,
    bitmap_class_t_get_pixel_instance_60,
    bitmap_class_t_get_pixel_instance_61,
    bitmap_class_t_get_pixel_instance_62,
    bitmap_class_t_get_pixel_instance_63,
};

typedef void ( *bitmap_class_t_set_pixel_t )( uint16_t posx, uint16_t posy, pixel_t pixel );

static void bitmap_class_t_set_pixel_instance_00( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->set_pixel( _instance_list_bitmap_class_t[ 0], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_01( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->set_pixel( _instance_list_bitmap_class_t[ 1], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_02( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->set_pixel( _instance_list_bitmap_class_t[ 2], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_03( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->set_pixel( _instance_list_bitmap_class_t[ 3], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_04( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->set_pixel( _instance_list_bitmap_class_t[ 4], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_05( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->set_pixel( _instance_list_bitmap_class_t[ 5], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_06( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->set_pixel( _instance_list_bitmap_class_t[ 6], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_07( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->set_pixel( _instance_list_bitmap_class_t[ 7], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_08( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->set_pixel( _instance_list_bitmap_class_t[ 8], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_09( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->set_pixel( _instance_list_bitmap_class_t[ 9], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_10( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->set_pixel( _instance_list_bitmap_class_t[10], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_11( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->set_pixel( _instance_list_bitmap_class_t[11], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_12( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->set_pixel( _instance_list_bitmap_class_t[12], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_13( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->set_pixel( _instance_list_bitmap_class_t[13], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_14( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->set_pixel( _instance_list_bitmap_class_t[14], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_15( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->set_pixel( _instance_list_bitmap_class_t[15], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_16( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->set_pixel( _instance_list_bitmap_class_t[16], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_17( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->set_pixel( _instance_list_bitmap_class_t[17], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_18( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->set_pixel( _instance_list_bitmap_class_t[18], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_19( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->set_pixel( _instance_list_bitmap_class_t[19], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_20( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->set_pixel( _instance_list_bitmap_class_t[20], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_21( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->set_pixel( _instance_list_bitmap_class_t[21], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_22( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->set_pixel( _instance_list_bitmap_class_t[22], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_23( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->set_pixel( _instance_list_bitmap_class_t[23], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_24( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->set_pixel( _instance_list_bitmap_class_t[24], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_25( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->set_pixel( _instance_list_bitmap_class_t[25], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_26( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->set_pixel( _instance_list_bitmap_class_t[26], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_27( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->set_pixel( _instance_list_bitmap_class_t[27], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_28( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->set_pixel( _instance_list_bitmap_class_t[28], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_29( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->set_pixel( _instance_list_bitmap_class_t[29], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_30( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->set_pixel( _instance_list_bitmap_class_t[30], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_31( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->set_pixel( _instance_list_bitmap_class_t[31], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_32( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->set_pixel( _instance_list_bitmap_class_t[32], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_33( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->set_pixel( _instance_list_bitmap_class_t[33], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_34( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->set_pixel( _instance_list_bitmap_class_t[34], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_35( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->set_pixel( _instance_list_bitmap_class_t[35], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_36( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->set_pixel( _instance_list_bitmap_class_t[36], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_37( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->set_pixel( _instance_list_bitmap_class_t[37], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_38( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->set_pixel( _instance_list_bitmap_class_t[38], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_39( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->set_pixel( _instance_list_bitmap_class_t[39], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_40( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->set_pixel( _instance_list_bitmap_class_t[40], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_41( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->set_pixel( _instance_list_bitmap_class_t[41], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_42( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->set_pixel( _instance_list_bitmap_class_t[42], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_43( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->set_pixel( _instance_list_bitmap_class_t[43], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_44( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->set_pixel( _instance_list_bitmap_class_t[44], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_45( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->set_pixel( _instance_list_bitmap_class_t[45], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_46( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->set_pixel( _instance_list_bitmap_class_t[46], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_47( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->set_pixel( _instance_list_bitmap_class_t[47], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_48( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->set_pixel( _instance_list_bitmap_class_t[48], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_49( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->set_pixel( _instance_list_bitmap_class_t[49], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_50( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->set_pixel( _instance_list_bitmap_class_t[50], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_51( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->set_pixel( _instance_list_bitmap_class_t[51], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_52( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->set_pixel( _instance_list_bitmap_class_t[52], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_53( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->set_pixel( _instance_list_bitmap_class_t[53], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_54( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->set_pixel( _instance_list_bitmap_class_t[54], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_55( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->set_pixel( _instance_list_bitmap_class_t[55], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_56( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->set_pixel( _instance_list_bitmap_class_t[56], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_57( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->set_pixel( _instance_list_bitmap_class_t[57], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_58( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->set_pixel( _instance_list_bitmap_class_t[58], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_59( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->set_pixel( _instance_list_bitmap_class_t[59], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_60( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->set_pixel( _instance_list_bitmap_class_t[60], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_61( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->set_pixel( _instance_list_bitmap_class_t[61], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_62( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->set_pixel( _instance_list_bitmap_class_t[62], posx, posy, pixel ); }
static void bitmap_class_t_set_pixel_instance_63( uint16_t posx, uint16_t posy, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->set_pixel( _instance_list_bitmap_class_t[63], posx, posy, pixel ); }

static const bitmap_class_t_set_pixel_t _bitmap_class_t_set_pixel_list[64] =
{
    bitmap_class_t_set_pixel_instance_00,
    bitmap_class_t_set_pixel_instance_01,
    bitmap_class_t_set_pixel_instance_02,
    bitmap_class_t_set_pixel_instance_03,
    bitmap_class_t_set_pixel_instance_04,
    bitmap_class_t_set_pixel_instance_05,
    bitmap_class_t_set_pixel_instance_06,
    bitmap_class_t_set_pixel_instance_07,
    bitmap_class_t_set_pixel_instance_08,
    bitmap_class_t_set_pixel_instance_09,
    bitmap_class_t_set_pixel_instance_10,
    bitmap_class_t_set_pixel_instance_11,
    bitmap_class_t_set_pixel_instance_12,
    bitmap_class_t_set_pixel_instance_13,
    bitmap_class_t_set_pixel_instance_14,
    bitmap_class_t_set_pixel_instance_15,
    bitmap_class_t_set_pixel_instance_16,
    bitmap_class_t_set_pixel_instance_17,
    bitmap_class_t_set_pixel_instance_18,
    bitmap_class_t_set_pixel_instance_19,
    bitmap_class_t_set_pixel_instance_20,
    bitmap_class_t_set_pixel_instance_21,
    bitmap_class_t_set_pixel_instance_22,
    bitmap_class_t_set_pixel_instance_23,
    bitmap_class_t_set_pixel_instance_24,
    bitmap_class_t_set_pixel_instance_25,
    bitmap_class_t_set_pixel_instance_26,
    bitmap_class_t_set_pixel_instance_27,
    bitmap_class_t_set_pixel_instance_28,
    bitmap_class_t_set_pixel_instance_29,
    bitmap_class_t_set_pixel_instance_30,
    bitmap_class_t_set_pixel_instance_31,
    bitmap_class_t_set_pixel_instance_32,
    bitmap_class_t_set_pixel_instance_33,
    bitmap_class_t_set_pixel_instance_34,
    bitmap_class_t_set_pixel_instance_35,
    bitmap_class_t_set_pixel_instance_36,
    bitmap_class_t_set_pixel_instance_37,
    bitmap_class_t_set_pixel_instance_38,
    bitmap_class_t_set_pixel_instance_39,
    bitmap_class_t_set_pixel_instance_40,
    bitmap_class_t_set_pixel_instance_41,
    bitmap_class_t_set_pixel_instance_42,
    bitmap_class_t_set_pixel_instance_43,
    bitmap_class_t_set_pixel_instance_44,
    bitmap_class_t_set_pixel_instance_45,
    bitmap_class_t_set_pixel_instance_46,
    bitmap_class_t_set_pixel_instance_47,
    bitmap_class_t_set_pixel_instance_48,
    bitmap_class_t_set_pixel_instance_49,
    bitmap_class_t_set_pixel_instance_50,
    bitmap_class_t_set_pixel_instance_51,
    bitmap_class_t_set_pixel_instance_52,
    bitmap_class_t_set_pixel_instance_53,
    bitmap_class_t_set_pixel_instance_54,
    bitmap_class_t_set_pixel_instance_55,
    bitmap_class_t_set_pixel_instance_56,
    bitmap_class_t_set_pixel_instance_57,
    bitmap_class_t_set_pixel_instance_58,
    bitmap_class_t_set_pixel_instance_59,
    bitmap_class_t_set_pixel_instance_60,
    bitmap_class_t_set_pixel_instance_61,
    bitmap_class_t_set_pixel_instance_62,
    bitmap_class_t_set_pixel_instance_63,
};

typedef void ( *bitmap_class_t_set_pixel_index_t )( uint32_t index, pixel_t pixel );

static void bitmap_class_t_set_pixel_index_instance_00( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 0], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_01( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 1], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_02( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 2], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_03( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 3], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_04( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 4], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_05( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 5], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_06( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 6], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_07( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 7], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_08( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 8], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_09( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->set_pixel_index( _instance_list_bitmap_class_t[ 9], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_10( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->set_pixel_index( _instance_list_bitmap_class_t[10], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_11( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->set_pixel_index( _instance_list_bitmap_class_t[11], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_12( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->set_pixel_index( _instance_list_bitmap_class_t[12], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_13( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->set_pixel_index( _instance_list_bitmap_class_t[13], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_14( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->set_pixel_index( _instance_list_bitmap_class_t[14], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_15( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->set_pixel_index( _instance_list_bitmap_class_t[15], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_16( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->set_pixel_index( _instance_list_bitmap_class_t[16], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_17( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->set_pixel_index( _instance_list_bitmap_class_t[17], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_18( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->set_pixel_index( _instance_list_bitmap_class_t[18], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_19( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->set_pixel_index( _instance_list_bitmap_class_t[19], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_20( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->set_pixel_index( _instance_list_bitmap_class_t[20], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_21( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->set_pixel_index( _instance_list_bitmap_class_t[21], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_22( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->set_pixel_index( _instance_list_bitmap_class_t[22], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_23( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->set_pixel_index( _instance_list_bitmap_class_t[23], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_24( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->set_pixel_index( _instance_list_bitmap_class_t[24], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_25( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->set_pixel_index( _instance_list_bitmap_class_t[25], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_26( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->set_pixel_index( _instance_list_bitmap_class_t[26], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_27( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->set_pixel_index( _instance_list_bitmap_class_t[27], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_28( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->set_pixel_index( _instance_list_bitmap_class_t[28], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_29( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->set_pixel_index( _instance_list_bitmap_class_t[29], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_30( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->set_pixel_index( _instance_list_bitmap_class_t[30], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_31( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->set_pixel_index( _instance_list_bitmap_class_t[31], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_32( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->set_pixel_index( _instance_list_bitmap_class_t[32], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_33( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->set_pixel_index( _instance_list_bitmap_class_t[33], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_34( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->set_pixel_index( _instance_list_bitmap_class_t[34], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_35( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->set_pixel_index( _instance_list_bitmap_class_t[35], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_36( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->set_pixel_index( _instance_list_bitmap_class_t[36], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_37( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->set_pixel_index( _instance_list_bitmap_class_t[37], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_38( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->set_pixel_index( _instance_list_bitmap_class_t[38], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_39( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->set_pixel_index( _instance_list_bitmap_class_t[39], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_40( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->set_pixel_index( _instance_list_bitmap_class_t[40], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_41( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->set_pixel_index( _instance_list_bitmap_class_t[41], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_42( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->set_pixel_index( _instance_list_bitmap_class_t[42], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_43( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->set_pixel_index( _instance_list_bitmap_class_t[43], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_44( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->set_pixel_index( _instance_list_bitmap_class_t[44], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_45( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->set_pixel_index( _instance_list_bitmap_class_t[45], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_46( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->set_pixel_index( _instance_list_bitmap_class_t[46], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_47( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->set_pixel_index( _instance_list_bitmap_class_t[47], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_48( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->set_pixel_index( _instance_list_bitmap_class_t[48], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_49( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->set_pixel_index( _instance_list_bitmap_class_t[49], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_50( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->set_pixel_index( _instance_list_bitmap_class_t[50], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_51( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->set_pixel_index( _instance_list_bitmap_class_t[51], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_52( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->set_pixel_index( _instance_list_bitmap_class_t[52], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_53( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->set_pixel_index( _instance_list_bitmap_class_t[53], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_54( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->set_pixel_index( _instance_list_bitmap_class_t[54], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_55( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->set_pixel_index( _instance_list_bitmap_class_t[55], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_56( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->set_pixel_index( _instance_list_bitmap_class_t[56], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_57( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->set_pixel_index( _instance_list_bitmap_class_t[57], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_58( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->set_pixel_index( _instance_list_bitmap_class_t[58], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_59( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->set_pixel_index( _instance_list_bitmap_class_t[59], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_60( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->set_pixel_index( _instance_list_bitmap_class_t[60], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_61( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->set_pixel_index( _instance_list_bitmap_class_t[61], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_62( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->set_pixel_index( _instance_list_bitmap_class_t[62], index, pixel ); }
static void bitmap_class_t_set_pixel_index_instance_63( uint32_t index, pixel_t pixel ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->set_pixel_index( _instance_list_bitmap_class_t[63], index, pixel ); }

static const bitmap_class_t_set_pixel_index_t _bitmap_class_t_set_pixel_index_list[64] =
{
    bitmap_class_t_set_pixel_index_instance_00,
    bitmap_class_t_set_pixel_index_instance_01,
    bitmap_class_t_set_pixel_index_instance_02,
    bitmap_class_t_set_pixel_index_instance_03,
    bitmap_class_t_set_pixel_index_instance_04,
    bitmap_class_t_set_pixel_index_instance_05,
    bitmap_class_t_set_pixel_index_instance_06,
    bitmap_class_t_set_pixel_index_instance_07,
    bitmap_class_t_set_pixel_index_instance_08,
    bitmap_class_t_set_pixel_index_instance_09,
    bitmap_class_t_set_pixel_index_instance_10,
    bitmap_class_t_set_pixel_index_instance_11,
    bitmap_class_t_set_pixel_index_instance_12,
    bitmap_class_t_set_pixel_index_instance_13,
    bitmap_class_t_set_pixel_index_instance_14,
    bitmap_class_t_set_pixel_index_instance_15,
    bitmap_class_t_set_pixel_index_instance_16,
    bitmap_class_t_set_pixel_index_instance_17,
    bitmap_class_t_set_pixel_index_instance_18,
    bitmap_class_t_set_pixel_index_instance_19,
    bitmap_class_t_set_pixel_index_instance_20,
    bitmap_class_t_set_pixel_index_instance_21,
    bitmap_class_t_set_pixel_index_instance_22,
    bitmap_class_t_set_pixel_index_instance_23,
    bitmap_class_t_set_pixel_index_instance_24,
    bitmap_class_t_set_pixel_index_instance_25,
    bitmap_class_t_set_pixel_index_instance_26,
    bitmap_class_t_set_pixel_index_instance_27,
    bitmap_class_t_set_pixel_index_instance_28,
    bitmap_class_t_set_pixel_index_instance_29,
    bitmap_class_t_set_pixel_index_instance_30,
    bitmap_class_t_set_pixel_index_instance_31,
    bitmap_class_t_set_pixel_index_instance_32,
    bitmap_class_t_set_pixel_index_instance_33,
    bitmap_class_t_set_pixel_index_instance_34,
    bitmap_class_t_set_pixel_index_instance_35,
    bitmap_class_t_set_pixel_index_instance_36,
    bitmap_class_t_set_pixel_index_instance_37,
    bitmap_class_t_set_pixel_index_instance_38,
    bitmap_class_t_set_pixel_index_instance_39,
    bitmap_class_t_set_pixel_index_instance_40,
    bitmap_class_t_set_pixel_index_instance_41,
    bitmap_class_t_set_pixel_index_instance_42,
    bitmap_class_t_set_pixel_index_instance_43,
    bitmap_class_t_set_pixel_index_instance_44,
    bitmap_class_t_set_pixel_index_instance_45,
    bitmap_class_t_set_pixel_index_instance_46,
    bitmap_class_t_set_pixel_index_instance_47,
    bitmap_class_t_set_pixel_index_instance_48,
    bitmap_class_t_set_pixel_index_instance_49,
    bitmap_class_t_set_pixel_index_instance_50,
    bitmap_class_t_set_pixel_index_instance_51,
    bitmap_class_t_set_pixel_index_instance_52,
    bitmap_class_t_set_pixel_index_instance_53,
    bitmap_class_t_set_pixel_index_instance_54,
    bitmap_class_t_set_pixel_index_instance_55,
    bitmap_class_t_set_pixel_index_instance_56,
    bitmap_class_t_set_pixel_index_instance_57,
    bitmap_class_t_set_pixel_index_instance_58,
    bitmap_class_t_set_pixel_index_instance_59,
    bitmap_class_t_set_pixel_index_instance_60,
    bitmap_class_t_set_pixel_index_instance_61,
    bitmap_class_t_set_pixel_index_instance_62,
    bitmap_class_t_set_pixel_index_instance_63,
};

typedef void * ( *bitmap_class_t_get_buffer_t )( void );

static void * bitmap_class_t_get_buffer_instance_00( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->get_buffer( _instance_list_bitmap_class_t[ 0] ); }
static void * bitmap_class_t_get_buffer_instance_01( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->get_buffer( _instance_list_bitmap_class_t[ 1] ); }
static void * bitmap_class_t_get_buffer_instance_02( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->get_buffer( _instance_list_bitmap_class_t[ 2] ); }
static void * bitmap_class_t_get_buffer_instance_03( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->get_buffer( _instance_list_bitmap_class_t[ 3] ); }
static void * bitmap_class_t_get_buffer_instance_04( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->get_buffer( _instance_list_bitmap_class_t[ 4] ); }
static void * bitmap_class_t_get_buffer_instance_05( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->get_buffer( _instance_list_bitmap_class_t[ 5] ); }
static void * bitmap_class_t_get_buffer_instance_06( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->get_buffer( _instance_list_bitmap_class_t[ 6] ); }
static void * bitmap_class_t_get_buffer_instance_07( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->get_buffer( _instance_list_bitmap_class_t[ 7] ); }
static void * bitmap_class_t_get_buffer_instance_08( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->get_buffer( _instance_list_bitmap_class_t[ 8] ); }
static void * bitmap_class_t_get_buffer_instance_09( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->get_buffer( _instance_list_bitmap_class_t[ 9] ); }
static void * bitmap_class_t_get_buffer_instance_10( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->get_buffer( _instance_list_bitmap_class_t[10] ); }
static void * bitmap_class_t_get_buffer_instance_11( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->get_buffer( _instance_list_bitmap_class_t[11] ); }
static void * bitmap_class_t_get_buffer_instance_12( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->get_buffer( _instance_list_bitmap_class_t[12] ); }
static void * bitmap_class_t_get_buffer_instance_13( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->get_buffer( _instance_list_bitmap_class_t[13] ); }
static void * bitmap_class_t_get_buffer_instance_14( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->get_buffer( _instance_list_bitmap_class_t[14] ); }
static void * bitmap_class_t_get_buffer_instance_15( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->get_buffer( _instance_list_bitmap_class_t[15] ); }
static void * bitmap_class_t_get_buffer_instance_16( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->get_buffer( _instance_list_bitmap_class_t[16] ); }
static void * bitmap_class_t_get_buffer_instance_17( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->get_buffer( _instance_list_bitmap_class_t[17] ); }
static void * bitmap_class_t_get_buffer_instance_18( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->get_buffer( _instance_list_bitmap_class_t[18] ); }
static void * bitmap_class_t_get_buffer_instance_19( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->get_buffer( _instance_list_bitmap_class_t[19] ); }
static void * bitmap_class_t_get_buffer_instance_20( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->get_buffer( _instance_list_bitmap_class_t[20] ); }
static void * bitmap_class_t_get_buffer_instance_21( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->get_buffer( _instance_list_bitmap_class_t[21] ); }
static void * bitmap_class_t_get_buffer_instance_22( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->get_buffer( _instance_list_bitmap_class_t[22] ); }
static void * bitmap_class_t_get_buffer_instance_23( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->get_buffer( _instance_list_bitmap_class_t[23] ); }
static void * bitmap_class_t_get_buffer_instance_24( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->get_buffer( _instance_list_bitmap_class_t[24] ); }
static void * bitmap_class_t_get_buffer_instance_25( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->get_buffer( _instance_list_bitmap_class_t[25] ); }
static void * bitmap_class_t_get_buffer_instance_26( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->get_buffer( _instance_list_bitmap_class_t[26] ); }
static void * bitmap_class_t_get_buffer_instance_27( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->get_buffer( _instance_list_bitmap_class_t[27] ); }
static void * bitmap_class_t_get_buffer_instance_28( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->get_buffer( _instance_list_bitmap_class_t[28] ); }
static void * bitmap_class_t_get_buffer_instance_29( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->get_buffer( _instance_list_bitmap_class_t[29] ); }
static void * bitmap_class_t_get_buffer_instance_30( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->get_buffer( _instance_list_bitmap_class_t[30] ); }
static void * bitmap_class_t_get_buffer_instance_31( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->get_buffer( _instance_list_bitmap_class_t[31] ); }
static void * bitmap_class_t_get_buffer_instance_32( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->get_buffer( _instance_list_bitmap_class_t[32] ); }
static void * bitmap_class_t_get_buffer_instance_33( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->get_buffer( _instance_list_bitmap_class_t[33] ); }
static void * bitmap_class_t_get_buffer_instance_34( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->get_buffer( _instance_list_bitmap_class_t[34] ); }
static void * bitmap_class_t_get_buffer_instance_35( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->get_buffer( _instance_list_bitmap_class_t[35] ); }
static void * bitmap_class_t_get_buffer_instance_36( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->get_buffer( _instance_list_bitmap_class_t[36] ); }
static void * bitmap_class_t_get_buffer_instance_37( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->get_buffer( _instance_list_bitmap_class_t[37] ); }
static void * bitmap_class_t_get_buffer_instance_38( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->get_buffer( _instance_list_bitmap_class_t[38] ); }
static void * bitmap_class_t_get_buffer_instance_39( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->get_buffer( _instance_list_bitmap_class_t[39] ); }
static void * bitmap_class_t_get_buffer_instance_40( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->get_buffer( _instance_list_bitmap_class_t[40] ); }
static void * bitmap_class_t_get_buffer_instance_41( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->get_buffer( _instance_list_bitmap_class_t[41] ); }
static void * bitmap_class_t_get_buffer_instance_42( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->get_buffer( _instance_list_bitmap_class_t[42] ); }
static void * bitmap_class_t_get_buffer_instance_43( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->get_buffer( _instance_list_bitmap_class_t[43] ); }
static void * bitmap_class_t_get_buffer_instance_44( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->get_buffer( _instance_list_bitmap_class_t[44] ); }
static void * bitmap_class_t_get_buffer_instance_45( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->get_buffer( _instance_list_bitmap_class_t[45] ); }
static void * bitmap_class_t_get_buffer_instance_46( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->get_buffer( _instance_list_bitmap_class_t[46] ); }
static void * bitmap_class_t_get_buffer_instance_47( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->get_buffer( _instance_list_bitmap_class_t[47] ); }
static void * bitmap_class_t_get_buffer_instance_48( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->get_buffer( _instance_list_bitmap_class_t[48] ); }
static void * bitmap_class_t_get_buffer_instance_49( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->get_buffer( _instance_list_bitmap_class_t[49] ); }
static void * bitmap_class_t_get_buffer_instance_50( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->get_buffer( _instance_list_bitmap_class_t[50] ); }
static void * bitmap_class_t_get_buffer_instance_51( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->get_buffer( _instance_list_bitmap_class_t[51] ); }
static void * bitmap_class_t_get_buffer_instance_52( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->get_buffer( _instance_list_bitmap_class_t[52] ); }
static void * bitmap_class_t_get_buffer_instance_53( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->get_buffer( _instance_list_bitmap_class_t[53] ); }
static void * bitmap_class_t_get_buffer_instance_54( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->get_buffer( _instance_list_bitmap_class_t[54] ); }
static void * bitmap_class_t_get_buffer_instance_55( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->get_buffer( _instance_list_bitmap_class_t[55] ); }
static void * bitmap_class_t_get_buffer_instance_56( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->get_buffer( _instance_list_bitmap_class_t[56] ); }
static void * bitmap_class_t_get_buffer_instance_57( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->get_buffer( _instance_list_bitmap_class_t[57] ); }
static void * bitmap_class_t_get_buffer_instance_58( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->get_buffer( _instance_list_bitmap_class_t[58] ); }
static void * bitmap_class_t_get_buffer_instance_59( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->get_buffer( _instance_list_bitmap_class_t[59] ); }
static void * bitmap_class_t_get_buffer_instance_60( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->get_buffer( _instance_list_bitmap_class_t[60] ); }
static void * bitmap_class_t_get_buffer_instance_61( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->get_buffer( _instance_list_bitmap_class_t[61] ); }
static void * bitmap_class_t_get_buffer_instance_62( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->get_buffer( _instance_list_bitmap_class_t[62] ); }
static void * bitmap_class_t_get_buffer_instance_63( void ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->get_buffer( _instance_list_bitmap_class_t[63] ); }

static const bitmap_class_t_get_buffer_t _bitmap_class_t_get_buffer_list[64] =
{
    bitmap_class_t_get_buffer_instance_00,
    bitmap_class_t_get_buffer_instance_01,
    bitmap_class_t_get_buffer_instance_02,
    bitmap_class_t_get_buffer_instance_03,
    bitmap_class_t_get_buffer_instance_04,
    bitmap_class_t_get_buffer_instance_05,
    bitmap_class_t_get_buffer_instance_06,
    bitmap_class_t_get_buffer_instance_07,
    bitmap_class_t_get_buffer_instance_08,
    bitmap_class_t_get_buffer_instance_09,
    bitmap_class_t_get_buffer_instance_10,
    bitmap_class_t_get_buffer_instance_11,
    bitmap_class_t_get_buffer_instance_12,
    bitmap_class_t_get_buffer_instance_13,
    bitmap_class_t_get_buffer_instance_14,
    bitmap_class_t_get_buffer_instance_15,
    bitmap_class_t_get_buffer_instance_16,
    bitmap_class_t_get_buffer_instance_17,
    bitmap_class_t_get_buffer_instance_18,
    bitmap_class_t_get_buffer_instance_19,
    bitmap_class_t_get_buffer_instance_20,
    bitmap_class_t_get_buffer_instance_21,
    bitmap_class_t_get_buffer_instance_22,
    bitmap_class_t_get_buffer_instance_23,
    bitmap_class_t_get_buffer_instance_24,
    bitmap_class_t_get_buffer_instance_25,
    bitmap_class_t_get_buffer_instance_26,
    bitmap_class_t_get_buffer_instance_27,
    bitmap_class_t_get_buffer_instance_28,
    bitmap_class_t_get_buffer_instance_29,
    bitmap_class_t_get_buffer_instance_30,
    bitmap_class_t_get_buffer_instance_31,
    bitmap_class_t_get_buffer_instance_32,
    bitmap_class_t_get_buffer_instance_33,
    bitmap_class_t_get_buffer_instance_34,
    bitmap_class_t_get_buffer_instance_35,
    bitmap_class_t_get_buffer_instance_36,
    bitmap_class_t_get_buffer_instance_37,
    bitmap_class_t_get_buffer_instance_38,
    bitmap_class_t_get_buffer_instance_39,
    bitmap_class_t_get_buffer_instance_40,
    bitmap_class_t_get_buffer_instance_41,
    bitmap_class_t_get_buffer_instance_42,
    bitmap_class_t_get_buffer_instance_43,
    bitmap_class_t_get_buffer_instance_44,
    bitmap_class_t_get_buffer_instance_45,
    bitmap_class_t_get_buffer_instance_46,
    bitmap_class_t_get_buffer_instance_47,
    bitmap_class_t_get_buffer_instance_48,
    bitmap_class_t_get_buffer_instance_49,
    bitmap_class_t_get_buffer_instance_50,
    bitmap_class_t_get_buffer_instance_51,
    bitmap_class_t_get_buffer_instance_52,
    bitmap_class_t_get_buffer_instance_53,
    bitmap_class_t_get_buffer_instance_54,
    bitmap_class_t_get_buffer_instance_55,
    bitmap_class_t_get_buffer_instance_56,
    bitmap_class_t_get_buffer_instance_57,
    bitmap_class_t_get_buffer_instance_58,
    bitmap_class_t_get_buffer_instance_59,
    bitmap_class_t_get_buffer_instance_60,
    bitmap_class_t_get_buffer_instance_61,
    bitmap_class_t_get_buffer_instance_62,
    bitmap_class_t_get_buffer_instance_63,
};

typedef CLASS(bitmap_class_t) * ( *bitmap_class_t_get_frame_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth );

static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->get_frame( _instance_list_bitmap_class_t[ 0], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->get_frame( _instance_list_bitmap_class_t[ 1], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->get_frame( _instance_list_bitmap_class_t[ 2], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->get_frame( _instance_list_bitmap_class_t[ 3], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->get_frame( _instance_list_bitmap_class_t[ 4], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->get_frame( _instance_list_bitmap_class_t[ 5], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->get_frame( _instance_list_bitmap_class_t[ 6], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->get_frame( _instance_list_bitmap_class_t[ 7], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->get_frame( _instance_list_bitmap_class_t[ 8], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->get_frame( _instance_list_bitmap_class_t[ 9], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->get_frame( _instance_list_bitmap_class_t[10], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->get_frame( _instance_list_bitmap_class_t[11], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->get_frame( _instance_list_bitmap_class_t[12], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->get_frame( _instance_list_bitmap_class_t[13], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->get_frame( _instance_list_bitmap_class_t[14], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->get_frame( _instance_list_bitmap_class_t[15], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->get_frame( _instance_list_bitmap_class_t[16], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->get_frame( _instance_list_bitmap_class_t[17], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->get_frame( _instance_list_bitmap_class_t[18], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->get_frame( _instance_list_bitmap_class_t[19], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->get_frame( _instance_list_bitmap_class_t[20], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->get_frame( _instance_list_bitmap_class_t[21], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->get_frame( _instance_list_bitmap_class_t[22], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->get_frame( _instance_list_bitmap_class_t[23], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->get_frame( _instance_list_bitmap_class_t[24], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->get_frame( _instance_list_bitmap_class_t[25], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->get_frame( _instance_list_bitmap_class_t[26], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->get_frame( _instance_list_bitmap_class_t[27], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->get_frame( _instance_list_bitmap_class_t[28], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->get_frame( _instance_list_bitmap_class_t[29], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->get_frame( _instance_list_bitmap_class_t[30], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->get_frame( _instance_list_bitmap_class_t[31], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->get_frame( _instance_list_bitmap_class_t[32], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->get_frame( _instance_list_bitmap_class_t[33], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->get_frame( _instance_list_bitmap_class_t[34], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->get_frame( _instance_list_bitmap_class_t[35], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->get_frame( _instance_list_bitmap_class_t[36], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->get_frame( _instance_list_bitmap_class_t[37], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->get_frame( _instance_list_bitmap_class_t[38], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->get_frame( _instance_list_bitmap_class_t[39], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->get_frame( _instance_list_bitmap_class_t[40], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->get_frame( _instance_list_bitmap_class_t[41], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->get_frame( _instance_list_bitmap_class_t[42], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->get_frame( _instance_list_bitmap_class_t[43], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->get_frame( _instance_list_bitmap_class_t[44], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->get_frame( _instance_list_bitmap_class_t[45], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->get_frame( _instance_list_bitmap_class_t[46], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->get_frame( _instance_list_bitmap_class_t[47], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->get_frame( _instance_list_bitmap_class_t[48], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->get_frame( _instance_list_bitmap_class_t[49], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->get_frame( _instance_list_bitmap_class_t[50], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->get_frame( _instance_list_bitmap_class_t[51], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->get_frame( _instance_list_bitmap_class_t[52], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->get_frame( _instance_list_bitmap_class_t[53], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->get_frame( _instance_list_bitmap_class_t[54], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->get_frame( _instance_list_bitmap_class_t[55], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->get_frame( _instance_list_bitmap_class_t[56], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->get_frame( _instance_list_bitmap_class_t[57], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->get_frame( _instance_list_bitmap_class_t[58], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->get_frame( _instance_list_bitmap_class_t[59], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->get_frame( _instance_list_bitmap_class_t[60], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->get_frame( _instance_list_bitmap_class_t[61], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->get_frame( _instance_list_bitmap_class_t[62], posx, posy, width, heigth ); }
static CLASS(bitmap_class_t) * bitmap_class_t_get_frame_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth ){ return ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->get_frame( _instance_list_bitmap_class_t[63], posx, posy, width, heigth ); }

static const bitmap_class_t_get_frame_t _bitmap_class_t_get_frame_list[64] =
{
    bitmap_class_t_get_frame_instance_00,
    bitmap_class_t_get_frame_instance_01,
    bitmap_class_t_get_frame_instance_02,
    bitmap_class_t_get_frame_instance_03,
    bitmap_class_t_get_frame_instance_04,
    bitmap_class_t_get_frame_instance_05,
    bitmap_class_t_get_frame_instance_06,
    bitmap_class_t_get_frame_instance_07,
    bitmap_class_t_get_frame_instance_08,
    bitmap_class_t_get_frame_instance_09,
    bitmap_class_t_get_frame_instance_10,
    bitmap_class_t_get_frame_instance_11,
    bitmap_class_t_get_frame_instance_12,
    bitmap_class_t_get_frame_instance_13,
    bitmap_class_t_get_frame_instance_14,
    bitmap_class_t_get_frame_instance_15,
    bitmap_class_t_get_frame_instance_16,
    bitmap_class_t_get_frame_instance_17,
    bitmap_class_t_get_frame_instance_18,
    bitmap_class_t_get_frame_instance_19,
    bitmap_class_t_get_frame_instance_20,
    bitmap_class_t_get_frame_instance_21,
    bitmap_class_t_get_frame_instance_22,
    bitmap_class_t_get_frame_instance_23,
    bitmap_class_t_get_frame_instance_24,
    bitmap_class_t_get_frame_instance_25,
    bitmap_class_t_get_frame_instance_26,
    bitmap_class_t_get_frame_instance_27,
    bitmap_class_t_get_frame_instance_28,
    bitmap_class_t_get_frame_instance_29,
    bitmap_class_t_get_frame_instance_30,
    bitmap_class_t_get_frame_instance_31,
    bitmap_class_t_get_frame_instance_32,
    bitmap_class_t_get_frame_instance_33,
    bitmap_class_t_get_frame_instance_34,
    bitmap_class_t_get_frame_instance_35,
    bitmap_class_t_get_frame_instance_36,
    bitmap_class_t_get_frame_instance_37,
    bitmap_class_t_get_frame_instance_38,
    bitmap_class_t_get_frame_instance_39,
    bitmap_class_t_get_frame_instance_40,
    bitmap_class_t_get_frame_instance_41,
    bitmap_class_t_get_frame_instance_42,
    bitmap_class_t_get_frame_instance_43,
    bitmap_class_t_get_frame_instance_44,
    bitmap_class_t_get_frame_instance_45,
    bitmap_class_t_get_frame_instance_46,
    bitmap_class_t_get_frame_instance_47,
    bitmap_class_t_get_frame_instance_48,
    bitmap_class_t_get_frame_instance_49,
    bitmap_class_t_get_frame_instance_50,
    bitmap_class_t_get_frame_instance_51,
    bitmap_class_t_get_frame_instance_52,
    bitmap_class_t_get_frame_instance_53,
    bitmap_class_t_get_frame_instance_54,
    bitmap_class_t_get_frame_instance_55,
    bitmap_class_t_get_frame_instance_56,
    bitmap_class_t_get_frame_instance_57,
    bitmap_class_t_get_frame_instance_58,
    bitmap_class_t_get_frame_instance_59,
    bitmap_class_t_get_frame_instance_60,
    bitmap_class_t_get_frame_instance_61,
    bitmap_class_t_get_frame_instance_62,
    bitmap_class_t_get_frame_instance_63,
};

typedef void ( *bitmap_class_t_copy_bitmap_t )( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy );

static void bitmap_class_t_copy_bitmap_instance_00( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 0], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_01( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 1], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_02( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 2], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_03( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 3], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_04( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 4], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_05( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 5], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_06( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 6], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_07( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 7], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_08( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 8], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_09( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->copy_bitmap( _instance_list_bitmap_class_t[ 9], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_10( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->copy_bitmap( _instance_list_bitmap_class_t[10], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_11( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->copy_bitmap( _instance_list_bitmap_class_t[11], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_12( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->copy_bitmap( _instance_list_bitmap_class_t[12], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_13( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->copy_bitmap( _instance_list_bitmap_class_t[13], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_14( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->copy_bitmap( _instance_list_bitmap_class_t[14], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_15( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->copy_bitmap( _instance_list_bitmap_class_t[15], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_16( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->copy_bitmap( _instance_list_bitmap_class_t[16], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_17( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->copy_bitmap( _instance_list_bitmap_class_t[17], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_18( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->copy_bitmap( _instance_list_bitmap_class_t[18], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_19( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->copy_bitmap( _instance_list_bitmap_class_t[19], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_20( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->copy_bitmap( _instance_list_bitmap_class_t[20], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_21( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->copy_bitmap( _instance_list_bitmap_class_t[21], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_22( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->copy_bitmap( _instance_list_bitmap_class_t[22], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_23( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->copy_bitmap( _instance_list_bitmap_class_t[23], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_24( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->copy_bitmap( _instance_list_bitmap_class_t[24], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_25( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->copy_bitmap( _instance_list_bitmap_class_t[25], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_26( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->copy_bitmap( _instance_list_bitmap_class_t[26], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_27( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->copy_bitmap( _instance_list_bitmap_class_t[27], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_28( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->copy_bitmap( _instance_list_bitmap_class_t[28], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_29( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->copy_bitmap( _instance_list_bitmap_class_t[29], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_30( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->copy_bitmap( _instance_list_bitmap_class_t[30], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_31( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->copy_bitmap( _instance_list_bitmap_class_t[31], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_32( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->copy_bitmap( _instance_list_bitmap_class_t[32], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_33( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->copy_bitmap( _instance_list_bitmap_class_t[33], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_34( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->copy_bitmap( _instance_list_bitmap_class_t[34], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_35( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->copy_bitmap( _instance_list_bitmap_class_t[35], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_36( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->copy_bitmap( _instance_list_bitmap_class_t[36], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_37( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->copy_bitmap( _instance_list_bitmap_class_t[37], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_38( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->copy_bitmap( _instance_list_bitmap_class_t[38], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_39( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->copy_bitmap( _instance_list_bitmap_class_t[39], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_40( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->copy_bitmap( _instance_list_bitmap_class_t[40], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_41( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->copy_bitmap( _instance_list_bitmap_class_t[41], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_42( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->copy_bitmap( _instance_list_bitmap_class_t[42], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_43( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->copy_bitmap( _instance_list_bitmap_class_t[43], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_44( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->copy_bitmap( _instance_list_bitmap_class_t[44], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_45( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->copy_bitmap( _instance_list_bitmap_class_t[45], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_46( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->copy_bitmap( _instance_list_bitmap_class_t[46], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_47( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->copy_bitmap( _instance_list_bitmap_class_t[47], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_48( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->copy_bitmap( _instance_list_bitmap_class_t[48], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_49( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->copy_bitmap( _instance_list_bitmap_class_t[49], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_50( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->copy_bitmap( _instance_list_bitmap_class_t[50], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_51( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->copy_bitmap( _instance_list_bitmap_class_t[51], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_52( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->copy_bitmap( _instance_list_bitmap_class_t[52], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_53( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->copy_bitmap( _instance_list_bitmap_class_t[53], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_54( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->copy_bitmap( _instance_list_bitmap_class_t[54], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_55( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->copy_bitmap( _instance_list_bitmap_class_t[55], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_56( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->copy_bitmap( _instance_list_bitmap_class_t[56], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_57( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->copy_bitmap( _instance_list_bitmap_class_t[57], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_58( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->copy_bitmap( _instance_list_bitmap_class_t[58], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_59( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->copy_bitmap( _instance_list_bitmap_class_t[59], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_60( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->copy_bitmap( _instance_list_bitmap_class_t[60], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_61( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->copy_bitmap( _instance_list_bitmap_class_t[61], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_62( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->copy_bitmap( _instance_list_bitmap_class_t[62], bitmap, posx, posy ); }
static void bitmap_class_t_copy_bitmap_instance_63( const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->copy_bitmap( _instance_list_bitmap_class_t[63], bitmap, posx, posy ); }

static const bitmap_class_t_copy_bitmap_t _bitmap_class_t_copy_bitmap_list[64] =
{
    bitmap_class_t_copy_bitmap_instance_00,
    bitmap_class_t_copy_bitmap_instance_01,
    bitmap_class_t_copy_bitmap_instance_02,
    bitmap_class_t_copy_bitmap_instance_03,
    bitmap_class_t_copy_bitmap_instance_04,
    bitmap_class_t_copy_bitmap_instance_05,
    bitmap_class_t_copy_bitmap_instance_06,
    bitmap_class_t_copy_bitmap_instance_07,
    bitmap_class_t_copy_bitmap_instance_08,
    bitmap_class_t_copy_bitmap_instance_09,
    bitmap_class_t_copy_bitmap_instance_10,
    bitmap_class_t_copy_bitmap_instance_11,
    bitmap_class_t_copy_bitmap_instance_12,
    bitmap_class_t_copy_bitmap_instance_13,
    bitmap_class_t_copy_bitmap_instance_14,
    bitmap_class_t_copy_bitmap_instance_15,
    bitmap_class_t_copy_bitmap_instance_16,
    bitmap_class_t_copy_bitmap_instance_17,
    bitmap_class_t_copy_bitmap_instance_18,
    bitmap_class_t_copy_bitmap_instance_19,
    bitmap_class_t_copy_bitmap_instance_20,
    bitmap_class_t_copy_bitmap_instance_21,
    bitmap_class_t_copy_bitmap_instance_22,
    bitmap_class_t_copy_bitmap_instance_23,
    bitmap_class_t_copy_bitmap_instance_24,
    bitmap_class_t_copy_bitmap_instance_25,
    bitmap_class_t_copy_bitmap_instance_26,
    bitmap_class_t_copy_bitmap_instance_27,
    bitmap_class_t_copy_bitmap_instance_28,
    bitmap_class_t_copy_bitmap_instance_29,
    bitmap_class_t_copy_bitmap_instance_30,
    bitmap_class_t_copy_bitmap_instance_31,
    bitmap_class_t_copy_bitmap_instance_32,
    bitmap_class_t_copy_bitmap_instance_33,
    bitmap_class_t_copy_bitmap_instance_34,
    bitmap_class_t_copy_bitmap_instance_35,
    bitmap_class_t_copy_bitmap_instance_36,
    bitmap_class_t_copy_bitmap_instance_37,
    bitmap_class_t_copy_bitmap_instance_38,
    bitmap_class_t_copy_bitmap_instance_39,
    bitmap_class_t_copy_bitmap_instance_40,
    bitmap_class_t_copy_bitmap_instance_41,
    bitmap_class_t_copy_bitmap_instance_42,
    bitmap_class_t_copy_bitmap_instance_43,
    bitmap_class_t_copy_bitmap_instance_44,
    bitmap_class_t_copy_bitmap_instance_45,
    bitmap_class_t_copy_bitmap_instance_46,
    bitmap_class_t_copy_bitmap_instance_47,
    bitmap_class_t_copy_bitmap_instance_48,
    bitmap_class_t_copy_bitmap_instance_49,
    bitmap_class_t_copy_bitmap_instance_50,
    bitmap_class_t_copy_bitmap_instance_51,
    bitmap_class_t_copy_bitmap_instance_52,
    bitmap_class_t_copy_bitmap_instance_53,
    bitmap_class_t_copy_bitmap_instance_54,
    bitmap_class_t_copy_bitmap_instance_55,
    bitmap_class_t_copy_bitmap_instance_56,
    bitmap_class_t_copy_bitmap_instance_57,
    bitmap_class_t_copy_bitmap_instance_58,
    bitmap_class_t_copy_bitmap_instance_59,
    bitmap_class_t_copy_bitmap_instance_60,
    bitmap_class_t_copy_bitmap_instance_61,
    bitmap_class_t_copy_bitmap_instance_62,
    bitmap_class_t_copy_bitmap_instance_63,
};

typedef void ( *bitmap_class_t_draw_1bbp_t )( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour );

static void bitmap_class_t_draw_1bbp_instance_00( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 0]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 0], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_01( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 1]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 1], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_02( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 2]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 2], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_03( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 3]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 3], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_04( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 4]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 4], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_05( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 5]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 5], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_06( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 6]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 6], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_07( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 7]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 7], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_08( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 8]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 8], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_09( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[ 9]->__api )->draw_1bbp( _instance_list_bitmap_class_t[ 9], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_10( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[10]->__api )->draw_1bbp( _instance_list_bitmap_class_t[10], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_11( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[11]->__api )->draw_1bbp( _instance_list_bitmap_class_t[11], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_12( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[12]->__api )->draw_1bbp( _instance_list_bitmap_class_t[12], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_13( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[13]->__api )->draw_1bbp( _instance_list_bitmap_class_t[13], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_14( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[14]->__api )->draw_1bbp( _instance_list_bitmap_class_t[14], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_15( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[15]->__api )->draw_1bbp( _instance_list_bitmap_class_t[15], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_16( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[16]->__api )->draw_1bbp( _instance_list_bitmap_class_t[16], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_17( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[17]->__api )->draw_1bbp( _instance_list_bitmap_class_t[17], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_18( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[18]->__api )->draw_1bbp( _instance_list_bitmap_class_t[18], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_19( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[19]->__api )->draw_1bbp( _instance_list_bitmap_class_t[19], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_20( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[20]->__api )->draw_1bbp( _instance_list_bitmap_class_t[20], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_21( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[21]->__api )->draw_1bbp( _instance_list_bitmap_class_t[21], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_22( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[22]->__api )->draw_1bbp( _instance_list_bitmap_class_t[22], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_23( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[23]->__api )->draw_1bbp( _instance_list_bitmap_class_t[23], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_24( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[24]->__api )->draw_1bbp( _instance_list_bitmap_class_t[24], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_25( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[25]->__api )->draw_1bbp( _instance_list_bitmap_class_t[25], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_26( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[26]->__api )->draw_1bbp( _instance_list_bitmap_class_t[26], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_27( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[27]->__api )->draw_1bbp( _instance_list_bitmap_class_t[27], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_28( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[28]->__api )->draw_1bbp( _instance_list_bitmap_class_t[28], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_29( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[29]->__api )->draw_1bbp( _instance_list_bitmap_class_t[29], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_30( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[30]->__api )->draw_1bbp( _instance_list_bitmap_class_t[30], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_31( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[31]->__api )->draw_1bbp( _instance_list_bitmap_class_t[31], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_32( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[32]->__api )->draw_1bbp( _instance_list_bitmap_class_t[32], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_33( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[33]->__api )->draw_1bbp( _instance_list_bitmap_class_t[33], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_34( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[34]->__api )->draw_1bbp( _instance_list_bitmap_class_t[34], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_35( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[35]->__api )->draw_1bbp( _instance_list_bitmap_class_t[35], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_36( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[36]->__api )->draw_1bbp( _instance_list_bitmap_class_t[36], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_37( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[37]->__api )->draw_1bbp( _instance_list_bitmap_class_t[37], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_38( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[38]->__api )->draw_1bbp( _instance_list_bitmap_class_t[38], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_39( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[39]->__api )->draw_1bbp( _instance_list_bitmap_class_t[39], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_40( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[40]->__api )->draw_1bbp( _instance_list_bitmap_class_t[40], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_41( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[41]->__api )->draw_1bbp( _instance_list_bitmap_class_t[41], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_42( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[42]->__api )->draw_1bbp( _instance_list_bitmap_class_t[42], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_43( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[43]->__api )->draw_1bbp( _instance_list_bitmap_class_t[43], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_44( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[44]->__api )->draw_1bbp( _instance_list_bitmap_class_t[44], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_45( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[45]->__api )->draw_1bbp( _instance_list_bitmap_class_t[45], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_46( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[46]->__api )->draw_1bbp( _instance_list_bitmap_class_t[46], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_47( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[47]->__api )->draw_1bbp( _instance_list_bitmap_class_t[47], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_48( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[48]->__api )->draw_1bbp( _instance_list_bitmap_class_t[48], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_49( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[49]->__api )->draw_1bbp( _instance_list_bitmap_class_t[49], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_50( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[50]->__api )->draw_1bbp( _instance_list_bitmap_class_t[50], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_51( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[51]->__api )->draw_1bbp( _instance_list_bitmap_class_t[51], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_52( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[52]->__api )->draw_1bbp( _instance_list_bitmap_class_t[52], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_53( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[53]->__api )->draw_1bbp( _instance_list_bitmap_class_t[53], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_54( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[54]->__api )->draw_1bbp( _instance_list_bitmap_class_t[54], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_55( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[55]->__api )->draw_1bbp( _instance_list_bitmap_class_t[55], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_56( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[56]->__api )->draw_1bbp( _instance_list_bitmap_class_t[56], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_57( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[57]->__api )->draw_1bbp( _instance_list_bitmap_class_t[57], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_58( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[58]->__api )->draw_1bbp( _instance_list_bitmap_class_t[58], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_59( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[59]->__api )->draw_1bbp( _instance_list_bitmap_class_t[59], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_60( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[60]->__api )->draw_1bbp( _instance_list_bitmap_class_t[60], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_61( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[61]->__api )->draw_1bbp( _instance_list_bitmap_class_t[61], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_62( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[62]->__api )->draw_1bbp( _instance_list_bitmap_class_t[62], posx, posy, width, heigth, input, back_colour, fore_colour ); }
static void bitmap_class_t_draw_1bbp_instance_63( uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour ){ ( ( api_bitmap_class_t * )_instance_list_bitmap_class_t[63]->__api )->draw_1bbp( _instance_list_bitmap_class_t[63], posx, posy, width, heigth, input, back_colour, fore_colour ); }

static const bitmap_class_t_draw_1bbp_t _bitmap_class_t_draw_1bbp_list[64] =
{
    bitmap_class_t_draw_1bbp_instance_00,
    bitmap_class_t_draw_1bbp_instance_01,
    bitmap_class_t_draw_1bbp_instance_02,
    bitmap_class_t_draw_1bbp_instance_03,
    bitmap_class_t_draw_1bbp_instance_04,
    bitmap_class_t_draw_1bbp_instance_05,
    bitmap_class_t_draw_1bbp_instance_06,
    bitmap_class_t_draw_1bbp_instance_07,
    bitmap_class_t_draw_1bbp_instance_08,
    bitmap_class_t_draw_1bbp_instance_09,
    bitmap_class_t_draw_1bbp_instance_10,
    bitmap_class_t_draw_1bbp_instance_11,
    bitmap_class_t_draw_1bbp_instance_12,
    bitmap_class_t_draw_1bbp_instance_13,
    bitmap_class_t_draw_1bbp_instance_14,
    bitmap_class_t_draw_1bbp_instance_15,
    bitmap_class_t_draw_1bbp_instance_16,
    bitmap_class_t_draw_1bbp_instance_17,
    bitmap_class_t_draw_1bbp_instance_18,
    bitmap_class_t_draw_1bbp_instance_19,
    bitmap_class_t_draw_1bbp_instance_20,
    bitmap_class_t_draw_1bbp_instance_21,
    bitmap_class_t_draw_1bbp_instance_22,
    bitmap_class_t_draw_1bbp_instance_23,
    bitmap_class_t_draw_1bbp_instance_24,
    bitmap_class_t_draw_1bbp_instance_25,
    bitmap_class_t_draw_1bbp_instance_26,
    bitmap_class_t_draw_1bbp_instance_27,
    bitmap_class_t_draw_1bbp_instance_28,
    bitmap_class_t_draw_1bbp_instance_29,
    bitmap_class_t_draw_1bbp_instance_30,
    bitmap_class_t_draw_1bbp_instance_31,
    bitmap_class_t_draw_1bbp_instance_32,
    bitmap_class_t_draw_1bbp_instance_33,
    bitmap_class_t_draw_1bbp_instance_34,
    bitmap_class_t_draw_1bbp_instance_35,
    bitmap_class_t_draw_1bbp_instance_36,
    bitmap_class_t_draw_1bbp_instance_37,
    bitmap_class_t_draw_1bbp_instance_38,
    bitmap_class_t_draw_1bbp_instance_39,
    bitmap_class_t_draw_1bbp_instance_40,
    bitmap_class_t_draw_1bbp_instance_41,
    bitmap_class_t_draw_1bbp_instance_42,
    bitmap_class_t_draw_1bbp_instance_43,
    bitmap_class_t_draw_1bbp_instance_44,
    bitmap_class_t_draw_1bbp_instance_45,
    bitmap_class_t_draw_1bbp_instance_46,
    bitmap_class_t_draw_1bbp_instance_47,
    bitmap_class_t_draw_1bbp_instance_48,
    bitmap_class_t_draw_1bbp_instance_49,
    bitmap_class_t_draw_1bbp_instance_50,
    bitmap_class_t_draw_1bbp_instance_51,
    bitmap_class_t_draw_1bbp_instance_52,
    bitmap_class_t_draw_1bbp_instance_53,
    bitmap_class_t_draw_1bbp_instance_54,
    bitmap_class_t_draw_1bbp_instance_55,
    bitmap_class_t_draw_1bbp_instance_56,
    bitmap_class_t_draw_1bbp_instance_57,
    bitmap_class_t_draw_1bbp_instance_58,
    bitmap_class_t_draw_1bbp_instance_59,
    bitmap_class_t_draw_1bbp_instance_60,
    bitmap_class_t_draw_1bbp_instance_61,
    bitmap_class_t_draw_1bbp_instance_62,
    bitmap_class_t_draw_1bbp_instance_63,
};

void * _instance_new_bitmap_class_t_ex( void * __api, uint16_t width, uint16_t height )
{
    if( __api == NULL ) return NULL;
    int _instance_index = create_instance_class( ( void ** )_instance_list_bitmap_class_t, sizeof(bitmap_class_t), 64 );
    if( _instance_index == -1 ) return NULL;
    bitmap_class_t * ret = _instance_list_bitmap_class_t[_instance_index];
    ret->__api = __api;
    ret->claim = _bitmap_class_t_claim_list[_instance_index];
    ret->release = _bitmap_class_t_release_list[_instance_index];
    ret->clear = _bitmap_class_t_clear_list[_instance_index];
    ret->get_width = _bitmap_class_t_get_width_list[_instance_index];
    ret->get_height = _bitmap_class_t_get_height_list[_instance_index];
    ret->get_pixel = _bitmap_class_t_get_pixel_list[_instance_index];
    ret->set_pixel = _bitmap_class_t_set_pixel_list[_instance_index];
    ret->set_pixel_index = _bitmap_class_t_set_pixel_index_list[_instance_index];
    ret->get_buffer = _bitmap_class_t_get_buffer_list[_instance_index];
    ret->get_frame = _bitmap_class_t_get_frame_list[_instance_index];
    ret->copy_bitmap = _bitmap_class_t_copy_bitmap_list[_instance_index];
    ret->draw_1bbp = _bitmap_class_t_draw_1bbp_list[_instance_index];
    api_bitmap_class_t_class->creator_bitmap( ret, width, height );
    ret->__default_del = _bitmap_class_t_delete_bitmap_list[_instance_index];
    ret->from_driver = ( ( api_bitmap_class_t * )__api )->from_driver;
    return ret;
}

void * _instance_new_bitmap_class_t( uint16_t width, uint16_t height )
{
    return _instance_new_bitmap_class_t_ex( api_bitmap_class_t_class, width, height );
}

void * _instance_static_bitmap_class_t_method( void * __api )
{
    return api_bitmap_class_t_class;
}

#if 0 // method definition for bitmap_class_t

#include "bitmap_class_private.h"

////////////////////////////////////////////////////////////////////

CREATOR static void creator_bitmap( bitmap_class_t * p_data, uint16_t width, uint16_t height )
{
}

DELETE static void delete_bitmap( bitmap_class_t * p_data )
{
}

STATIC static CLASS(bitmap_class_t) * from_driver( void )
{
}

METHOD static void claim( bitmap_class_t * p_data )
{
}

METHOD static void release( bitmap_class_t * p_data )
{
}

METHOD static void clear( bitmap_class_t * p_data )
{
}

METHOD static uint16_t get_width( bitmap_class_t * p_data )
{
}

METHOD static uint16_t get_height( bitmap_class_t * p_data )
{
}

METHOD static uint32_t get_pixel( bitmap_class_t * p_data, uint16_t posx, uint16_t posy )
{
}

METHOD static void set_pixel( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, pixel_t pixel )
{
}

METHOD static void set_pixel_index( bitmap_class_t * p_data, uint32_t index, pixel_t pixel )
{
}

METHOD static void * get_buffer( bitmap_class_t * p_data )
{
}

METHOD static CLASS(bitmap_class_t) * get_frame( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth )
{
}

METHOD static void copy_bitmap( bitmap_class_t * p_data, const CLASS(bitmap_class_t) * bitmap, uint16_t posx, uint16_t posy )
{
}

METHOD static void draw_1bbp( bitmap_class_t * p_data, uint16_t posx, uint16_t posy, uint16_t width, uint16_t heigth, uint8_t * input, pixel_t back_colour, pixel_t fore_colour )
{
}

////////////////////////////////////////////////////////////////////

CREATE_CLASS( bitmap_class_t );

////////////////////////////////////////////////////////////////////

#endif // bitmap_class_t

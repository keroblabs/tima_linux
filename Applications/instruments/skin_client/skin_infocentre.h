#ifndef _SKIN_INFOCENTRE_H_
#define _SKIN_INFOCENTRE_H_

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "driving_data.h"

//////////////////////////////////////////////////////////////////////////////////////

#define INFOCENTRE_MESSAGE_MAX_LEN          40
#define INFOCENTRE_MESSAGE_MAX_COUNT        40

#define INFOCENTRE_MESSAGE_TYPE_OBD         0
#define INFOCENTRE_MESSAGE_TYPE_WARNING     1

//////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    InfoCentre_Update_Time     = 0x01,
    InfoCentre_Update_Info     = 0x02,
    InfoCentre_Update_Messages = 0x04,
    InfoCentre_Update_Odometer = 0x08,
    InfoCentre_Update_ELM327   = 0x10,
    
    InfoCentre_Update_All = 0xFF
    
} infocentre_update_mask_t;

typedef enum
{
    Column_Info_Engine_Temp,
    Column_Info_Oil_Temp,
    Column_Info_Fuel_Used,
    Column_Info_Fuel_InTank,
    Column_Info_Fuel_ToEmpty,
    Column_Info_Consuption_Instant,
    Column_Info_Consuption_Average,
    Column_Info_Battery_Voltage,
    Column_Info_Speed_Average,
    Column_Info_Speed_GPS,

    Column_Info_MAX
    
} column_info_t;

typedef enum
{
    Column_Index_Info,
    Column_Index_Message,
    Column_Index_Odometer,
    Column_Index_ELM327,

    Column_Index_MAX

} column_index_t;

typedef enum
{
    InfoCentre_DTC_Detected,
    InfoCentre_Brake_Failure,
    InfoCentre_Engine_Overheat,
    InfoCentre_Low_BrakeFluid,
    InfoCentre_Door_Open,
    InfoCentre_Low_Fuel,
    InfoCentre_Low_Washer,
    InfoCentre_CAN_Failure,
    InfoCentre_Key_Failure,
    
    InfoCentre_Message_MAX = 31
    
} infocentre_msg_index_t;

typedef enum
{
    InfoCentre_ELM327_Bitmap,
    InfoCentre_ELM327_Field1,
    InfoCentre_ELM327_Field2,
    InfoCentre_ELM327_Field3,

    InfoCentre_ELM327_MAX,
} infocentre_elm327_index_t;

typedef enum
{
    /*
    InfoCentre_Set_Fuel_Used,
    InfoCentre_Set_Fuel_In_Tank,
    InfoCentre_Set_Fuel_Level,
    InfoCentre_Set_Consuption_Average,
    InfoCentre_Set_Consuption_Instant,
    InfoCentre_Set_Speed_Average,
    InfoCentre_Set_Speed_GPS,
    InfoCentre_Set_RPM,
    InfoCentre_Set_EngineTemperature,
    InfoCentre_Set_BatteryVoltage,

    InfoCentre_Set_DTC_Indicator,
    InfoCentre_Set_Brake_Failure,
    InfoCentre_Set_Engine_Overheat,
    InfoCentre_Set_Door_Open,
    InfoCentre_Set_Low_BrakeFluid,
    InfoCentre_Set_Low_Fuel,
    InfoCentre_Set_Low_Washer,
    InfoCentre_Set_CAN_Failure,
   */
    InfoCentre_Reload,
    InfoCentre_Hide,
    
    InfoCentre_Change_Column,
    InfoCentre_Change_Row,
	InfoCentre_SetColumn,
/*
    InfoCentre_Set_OBD_Failure,
    InfoCentre_Set_OBD_Failure_MAX = InfoCentre_Set_OBD_Failure + 16,
*/
    InfoCentre_Show_Messages,
    
} infocentre_mode_t;

//////////////////////////////////////////////////////////////////////////////////////

typedef struct info_row_message_t_
{
    char                     message[INFOCENTRE_MESSAGE_MAX_LEN+1];
    infocentre_msg_index_t   index;
    bool_t                   is_show;
    uint8_t                  type;
} info_row_message_t;

typedef struct _infocentre_data_t
{
    void * mutex;
    void * cond;
    
    info_row_message_t row_message[InfoCentre_Message_MAX];

    int elm_327_data[InfoCentre_ELM327_MAX];

    uint32_t odometer;
    uint32_t trip_list[ODOMETER_TRIP_MAX_INDEX];

    uint32_t flags;
    uint32_t info_list[Column_Info_MAX];
    uint16_t *message_code_list;
    
    uint32_t flags_backup;
    
    struct tm std_time;
    
    bool_t is_enable;
    
    uint8_t update_mask;
    
    uint8_t column_index;
    uint8_t row_index;
    uint8_t max_row_index;
    
    /*
     1234567890123456
     MESSAGES: 00
     LOW BRAKE
     BRAKE FAILURE
     ENGINE OVERHEAT
     
     00.00 L USED
     00.00 L IN TANK
     000 KM TO EMPTY
     00.00 KM/L
     00.00 KM/L AVG
     000 KM/H AVG
     00 DEGREE
     
     FAULT CODE 0000
     
     INDICATOR: 00
     LOW WASHER
     LOW FUEL
     DOOR OPEN
     */
    
} infocentre_data_t;

//////////////////////////////////////////////////////////////////////////////////////

void infocentre_set_flag( void * pp_data, state_mask_t mask, bool_t state );
void infocentre_set_reading( void * pp_data, reading_values_t reading, int value );

void infocentre_load_trips( void * pp_data, uint32_t * trips );

void infocentre_change_column( void * pp_data, int dir );
void infocentre_set_column( void * pp_data, int value );
void infocentre_change_row( void * pp_data, int dir );

void infocentre_set_time( void * pp_data, struct tm * time_now );
void infocentre_reload( void * pp_data );
void infocentre_hide( void * pp_data );
void * infocentre_init( void );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _SKIN_INFOCENTRE_H_


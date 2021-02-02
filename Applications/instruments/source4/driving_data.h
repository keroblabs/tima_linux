#ifndef _DRIVING_DATA_H_
#define _DRIVING_DATA_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "message.h"
#include "string_lib.h"

////////////////////////////////////////////////////////////////////

#define MESSAGE_CODE_MAX            50
#define ODOMETER_TRIP_MAX_INDEX     5
#define MAX_APPLICATION_SKIN        10

////////////////////////////////////////////////////////////////////

#if defined _USE_MACOS_SDL
#define BITMAP_DIR "/Users/marciocherobim/Projects/linux_a20/tima_linux/Applications/instruments/bitmaps/"
#else
#define BITMAP_DIR                  "./bitmaps/"
#endif

////////////////////////////////////////////////////////////////////

typedef enum
{
    Unit_Km,
    Unit_Miles,
    
} unit_display_t;

typedef enum // set_value
{
    Reading_Speed,                  // 0
    Reading_RPM,                    // 1
    Reading_Fuel,                   // 2
    Reading_EngineTemp,             // 3
    
    Reading_FuelUsed,               // 4
    Reading_FuelInTank,             // 5
    Reading_ConsuptionAverage,      // 6
    Reading_ConsuptionInstant,      // 7
    Reading_SpeedAverage,           // 8
    Reading_SpeedGPS,               // 9
    Reading_BatteryVoltage,         // 10
    Reading_ShiftLightRPM,          // 11
    
    Reading_Odometer,               // 12

    Reading_MAX,
} reading_values_t;

typedef enum // setmask
{
    StateMask_OilPressure,
    StateMask_FullBeam,
    StateMask_FogLight,
    StateMask_Headlights,
    StateMask_MainBeam,
    StateMask_Battery,
    StateMask_EngineRun,

    StateMask_Washers,
    StateMask_BrakeFailure,
    StateMask_BrakeFluid,
    StateMask_DoorLeftOpen,
    StateMask_DoorRightOpen,
    StateMask_BonnetOpen,
    StateMask_BootOpen,
    StateMask_LowFuel,
    StateMask_EngineTemperature,
    StateMask_EngineFault,
    StateMask_KeyMissing,
    StateMask_CANFailure,
    StateMask_DTC_Indicator,

    StateMask_MAX
    
} state_mask_t;

typedef enum
{
    Start_Mode_Idle,
    Start_Mode_Acc,
    Start_Mode_Run_Wait,
    Start_Mode_Run,
    Start_Mode_Starter,
    Start_Mode_Done,
    Start_Mode_Ignition,
    Start_Mode_Engine_on,
    Start_Mode_Engine_off,
    
} start_mode_t;

typedef enum // set_handbrake
{
    HandBrake_Pulled,
    HandBrake_Moving,
    HandBrake_Released,

} handbrake_state_t;

typedef enum
{
    Indicator_None,
    Indicator_Left,
    Indicator_Right,
    Indicator_Hazard,
    
} indicator_state_t;

enum
{
    MessageSkin_Reload,
    MessageSkin_Hide,
    
    MessageSkin_ReadingValues,
    MessageSkin_StartMode,
    MessageSkin_HandbrakeIcon,
    MessageSkin_IndicatorIcon,
    MessageSkin_StateMask,
    MessageSkin_UpdateTime,
    
    MessageSkin_Button0,
    MessageSkin_Button1,
    MessageSkin_Button2,
    MessageSkin_Button3,

    MessageSkin_Page1,
    MessageSkin_Page2,

    MessageSkin_LoadTrip,
    MessageSkin_NextTrip,

    MessageSkin_MAX
};

////////////////////////////////////////////////////////////////////

typedef struct _driving_data_t
{
    int                 reading_values[Reading_MAX];
    
    uint32_t            trip_list[ODOMETER_TRIP_MAX_INDEX];

    start_mode_t        start_mode;
    handbrake_state_t   handbrake_mode;
    handbrake_state_t   handbrake_icon;
    indicator_state_t   indicator_mode;
    indicator_state_t   indicator_icon;
    
    unit_display_t      main_unit;
    unit_display_t      secondary_unit;

    uint32_t            state_mask;
    
    message_data_t *    message_data[MAX_APPLICATION_SKIN];
    
    struct tm *         std_time;

} driving_data_t;

////////////////////////////////////////////////////////////////////

void driving_data_execute_command( string_t * command );

driving_data_t * driving_data_lock( void );

void driving_data_set_time( struct tm * time );

void driving_data_release( void );

void driving_data_get_updated( driving_data_t * data );

void driving_data_state_mask( state_mask_t flag, bool_t state );
void driving_data_set_mask( uint32_t mask );
uint32_t driving_data_get_mask( void );

void driving_data_set_start_mode( start_mode_t mode );

void driving_data_set_indication_icon( indicator_state_t mode );

void driving_data_set_handbrake_icon( handbrake_state_t mode );

void driving_data_handbrake_icon( bool_t state );

void driving_data_set_reading_value( reading_values_t index, int value );

int driving_data_get_reading_value( reading_values_t index );

void driving_data_send_message( uint16_t message );

void driving_data_init( void );

void driving_data_attach_skin( message_data_t * message );

void driving_data_set_trips( uint32_t * value );
void driving_data_reset_trip( uint8_t index );
void driving_data_next_trip( void );

////////////////////////////////////////////////////////////////////

#endif /* _DRIVING_DATA_H_ */

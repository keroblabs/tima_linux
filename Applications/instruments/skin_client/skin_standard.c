#include "skin_standard.h"
#include "bitmap.h"
#include "warning_lights.h"
#include "t_threads.h"
#include "message.h"
#include "driving_data.h"

#include "infocentre.h"
#include "skin_infocentre.h"

#include "skin_odometer.h"
#include "skin_rpm.h"
#include "skin_speed.h"
#include "skin_warning.h"
#include "skin_fuel.h"
#include "skin_temperature.h"
#include "skin_handbrake.h"

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////

#define STATE_MASK_LIGHTS       ( ( 1 << StateMask_FullBeam ) | \
                                  ( 1 << StateMask_FogLight ) | \
                                  ( 1 << StateMask_MainBeam ) | \
                                  ( 1 << StateMask_Headlights ) )

///////////////////////////////////////////////////////////////////////////////////////

static infocentre_data_t * pp_data;
static message_data_t message_data;
static driving_data_t local_driving_data;

///////////////////////////////////////////////////////////////////////////////////////

static void update_hide( void )
{
    void * lcd;
    
    skin_odometer_hide();
    skin_rpm_hide();
    skin_speed_hide();
    skin_fuel_hide();
    skin_warning_hide();
    skin_temperature_hide();
    skin_handbrake_hide();
    
    infocentre_hide( pp_data );

    lcd = graphics_claim();
    graphics_clear_screen( lcd );
    graphics_release();
}

static void update_reload( void )
{
    void * lcd;
    
    lcd = graphics_claim();
    bitmap_load_to_lcd(lcd, BITMAP_DIR"dashboard_5.bmp", 0, 0);
    skin_handbrake_reload();
    graphics_release();

    infocentre_reload( pp_data );

    skin_odometer_reload();
    skin_rpm_reload();
    skin_speed_reload();
    skin_fuel_reload();
    skin_warning_reload();
    skin_temperature_reload();
}

static void update_skin_readings( reading_values_t reading, uint32_t value )
{
    switch( reading )
    {
        case Reading_RPM:
            skin_rpm_set_value( value );
            break;

        case Reading_Speed:
            skin_speed_set_value( value );
            break;

        case Reading_Fuel:
            skin_fuel_set_value( value );
            break;

        case Reading_EngineTemp:
            skin_temperature_set_value( value );
            break;

        case Reading_ShiftLightRPM:
            skin_rpm_set_shift_light_value( value );
            break;

        case Reading_Odometer:
            skin_odometer_set_value( value );
            break;
    }
}

static bool_t update_and_check_mask_bit( uint32_t state_mask, state_mask_t mask )
{
    bool_t ret = FALSE;

    if( ( state_mask & ( 1 << mask ) ) != ( local_driving_data.state_mask & ( 1 << mask ) ) )
    {
        ret = TRUE;

        if( state_mask & ( 1 << mask ) )
        {
            local_driving_data.state_mask |= ( 1 << mask );
        }
        else
        {
            local_driving_data.state_mask &= ~( 1 << mask );
        }
    }

    return ret;
}

static void update_all_state_mask( uint32_t state_mask )
{
    uint32_t state_index;
    
    //printf( "update_all_state_mask %d - %d\n", state_mask & STATE_MASK_LIGHTS, local_driving_data.state_mask & STATE_MASK_LIGHTS );

    if( ( state_mask & STATE_MASK_LIGHTS ) != ( local_driving_data.state_mask & STATE_MASK_LIGHTS ) )
    {
        skin_warning_update_mask( StateMask_MainBeam, FALSE );

        if( state_mask & ( 1 << StateMask_FullBeam ) )
        {
            skin_warning_update_mask( StateMask_FullBeam, TRUE );
        }
        else if( state_mask & ( 1 << StateMask_FogLight ) )
        {
            skin_warning_update_mask( StateMask_FogLight, TRUE );
        }
        else if( ( state_mask & ( 1 << StateMask_Headlights ) ) && !( state_mask & ( 1 << StateMask_MainBeam ) ) )
        {
            skin_warning_update_mask( StateMask_Headlights, TRUE );
        }

        local_driving_data.state_mask &= ~STATE_MASK_LIGHTS;
        local_driving_data.state_mask |= state_mask & STATE_MASK_LIGHTS;
    }

    // Now lights will not be processed here
    //printf( "local = 0x%08x, new = 0x%08x\n", local_driving_data.state_mask, state_mask );
    for( state_index = 0; state_index < StateMask_MAX; state_index++ )
    {
        if( update_and_check_mask_bit( state_mask, state_index ) )
        {
            bool_t state = ( local_driving_data.state_mask & ( 1 << state_index ) ) ? TRUE : FALSE;
            skin_warning_update_mask( state_index, state );
            infocentre_set_flag( pp_data, state_index, state );
        }
    }
}

static void update_all_readings( int * reading_values )
{
    uint32_t reading_index;
    
    for( reading_index = 0; reading_index < Reading_MAX; reading_index++ )
    {
        int value = reading_values[reading_index];
        if( value != local_driving_data.reading_values[reading_index] )
        {
            infocentre_set_reading( pp_data, reading_index, value );
            update_skin_readings( reading_index, value );
            
            local_driving_data.reading_values[reading_index] = value;
        }
    }
}

static void update_indicator_icon( indicator_state_t indicator_icon )
{
    switch( indicator_icon )
    {
        case Indicator_None:
            skin_warning_update( WARNING_SLOT_INDICATOR, Warning_Indicator_Left, FALSE );
            break;

        case Indicator_Left:
            skin_warning_update( WARNING_SLOT_INDICATOR, Warning_Indicator_Left, TRUE );
            break;

        case Indicator_Right:
            skin_warning_update( WARNING_SLOT_INDICATOR, Warning_Indicator_Right, TRUE );
            break;

        case Indicator_Hazard:
            skin_warning_update( WARNING_SLOT_INDICATOR, Warning_Hazard, TRUE );
            break;
    }
}

static void skin_message_thread( void )
{
    uint16_t message;
    driving_data_t rcvr_driving_data;

    while( 1 )
    {
        if( ( message = message_Get( &message_data ) ) != Message_NoMessage )
        {
            driving_data_get_updated( &rcvr_driving_data );
            message -= Message_User_Space;
            
            switch( message )
            {
                case MessageSkin_StateMask:
                    update_all_state_mask( rcvr_driving_data.state_mask );
                    break;
                    
                case MessageSkin_ReadingValues:
                    update_all_readings( rcvr_driving_data.reading_values );
                    break;

                case MessageSkin_LoadTrip:
                    infocentre_load_trips( pp_data, rcvr_driving_data.trip_list );
                    skin_odometer_load_trip( rcvr_driving_data.trip_list );
                    skin_odometer_set_value( rcvr_driving_data.reading_values[Reading_Odometer] );
                    break;
                    
                case MessageSkin_NextTrip:
                    skin_odometer_select_trip();
                    break;
                    
                case MessageSkin_UpdateTime:
                    infocentre_set_time( pp_data, rcvr_driving_data.std_time );
                    local_driving_data.std_time = rcvr_driving_data.std_time;
                    break;
                    
                case MessageSkin_HandbrakeIcon:
                    skin_handbrake_set_value( rcvr_driving_data.handbrake_icon );
                    break;
                    
                case MessageSkin_IndicatorIcon:
                    update_indicator_icon( rcvr_driving_data.indicator_icon );
                    break;
                    
                case MessageSkin_Button0:
                case MessageSkin_Button1:
                    infocentre_change_row( pp_data, message == MessageSkin_Button0 ? 1 : -1 );
                    break;
                    
                case MessageSkin_Button2:
                case MessageSkin_Button3:
                    infocentre_change_column( pp_data, message == MessageSkin_Button2 ? 1 : -1 );
                    break;
                    
                case MessageSkin_Page1:
                    break;
                    
                case MessageSkin_Page2:
                    break;
                    
                case MessageSkin_Reload:
                    update_reload();
                    break;
                    
                case MessageSkin_Hide:
                    update_hide();
                    break;
            }
        }
    }
}

void skin_standard_init( void * p_data )
{
    message_Init( &message_data );    
    driving_data_attach_skin( &message_data );
    
    graphics_init();
    
    pp_data = ( infocentre_data_t * )p_data;
    infocentre_graphics_init( pp_data );

    skin_odometer_init();
    skin_rpm_init();
    skin_speed_init();
    skin_fuel_init();
    skin_warning_init();
    skin_temperature_init();
    skin_handbrake_init();
    
    tthread_create( skin_message_thread );
}


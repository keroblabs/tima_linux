#include "skin_warning.h"
#include "t_threads.h"
#include "graphics.h"
#include "warning_lights.h"

////////////////////////////////////////////////////////////////////////////////////////

#define WARNINGS_POSX               5
#define WARNINGS_SPACE              72
#define WARNINGS_LINE              410

////////////////////////////////////////////////////////////////////////////////////////

static warning_t slot_data[SLOT_MAX_COUNT];
static bool_t is_enabled;

////////////////////////////////////////////////////////////////////////////////////////

static bool_t get_pos( uint32_t slot, uint16_t * x, uint16_t * y )
{
    bool_t ret = TRUE;

    switch( slot )
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 8:
            *x = WARNINGS_POSX + ( WARNINGS_SPACE * slot );
            *y = WARNINGS_LINE;
            break;
        case 5:
        case 6:
        case 7:
            *x = WARNINGS_POSX + ( WARNINGS_SPACE * 4 );
            *y = WARNINGS_LINE - ( WARNINGS_SPACE * ( slot - 4 ) );
            break;
            
        default:
            *x = 0;
            *y = 0;
            ret = FALSE;
            break;
    }

    return ret;
}

static void warning_reload( void )
{
    uint32_t slot_cnt;
    uint16_t x, y;
    void * lcd;
    
    lcd = graphics_claim();
    
    for( slot_cnt = 0; slot_cnt < SLOT_MAX_COUNT; slot_cnt++ )
    {
        if( slot_data[slot_cnt] == Warning_Unused )
        {
            if( get_pos( slot_cnt, &x, &y ) )
            {
                graphics_fill_box( lcd, x, y, 64, 64, APP_RGB(0,0,0) );
            }
        }
        else
        {
            if( get_pos( slot_cnt, &x, &y ) )
            {
                get_pos( slot_cnt, &x, &y );
                warning_lights_show( lcd, slot_data[slot_cnt], x, y );
            }
        }
    }
    
    graphics_release();
}

void skin_warning_update( uint8_t slot, uint32_t warning, bool_t state )
{
    uint16_t x, y;
    void * lcd;
    
    if( state == TRUE )
    {
        slot_data[slot] = warning;
        if( is_enabled == TRUE )
        {
            if( get_pos( slot, &x, &y ) )
            {
                lcd = graphics_claim();
                warning_lights_show( lcd, warning, x, y );
                graphics_release();
            }
        }
    }
    else
    {
        slot_data[slot] = Warning_Unused;
        if( is_enabled == TRUE )
        {
            if( get_pos( slot, &x, &y ) )
            {
                lcd = graphics_claim();
                graphics_fill_box( lcd, x, y, 64, 64, APP_RGB(0,0,0) );
                graphics_release();
            }
        }
    }
}

void skin_warning_update_mask( state_mask_t mask, bool_t state )
{
    switch( mask )
    {
        case StateMask_Battery:
            skin_warning_update( WARNING_SLOT_BATTERY, Warning_Battery, state );
            break;

        case StateMask_OilPressure:
            skin_warning_update( WARNING_SLOT_OIL, Warning_OilPressure, state );
            break;

        case StateMask_FogLight:
            skin_warning_update( WARNING_SLOT_HEADLIGHT, Warning_Lights_Fog, state );
            break;

        case StateMask_FullBeam:
            skin_warning_update( WARNING_SLOT_HEADLIGHT, Warning_Lights_FullBeam, state );
            break;

        case StateMask_Headlights:
            skin_warning_update( WARNING_SLOT_HEADLIGHT, Warning_Headlamps, state );
            break;

        case StateMask_MainBeam:
            skin_warning_update( WARNING_SLOT_HEADLIGHT, Warning_Lights_Dimmed, state );
            break;

        case StateMask_Washers:
            skin_warning_update( WARNING_SLOT_WASHERS, Warning_Washers, state );
            break;

        case StateMask_LowFuel:
            skin_warning_update( WARNING_SLOT_LOW_FUEL, Warning_Fuel_Warning, state );
            break;

        case StateMask_EngineTemperature:
            skin_warning_update( WARNING_SLOT_OVERHEAT, Warning_Temperature_Warning, state );
            break;

        case StateMask_EngineFault:
            skin_warning_update( WARNING_SLOT_FAULT, Warning_EngineFault, state );
            break;

        case StateMask_BrakeFluid:
            skin_warning_update( WARNING_SLOT_BRAKE, Warning_Brake_Service, state );
            break;

        case StateMask_BrakeFailure:
            skin_warning_update( WARNING_SLOT_BRAKE, Warning_Brake_Service, state );
            break;

        case StateMask_KeyMissing:
            skin_warning_update( WARNING_SLOT_FAULT, Warning_Key, state );
            break;
    }
}

void skin_warning_hide( void )
{
    is_enabled = FALSE;
}

void skin_warning_reload( void )
{
    is_enabled = TRUE;
    warning_reload();
}

void skin_warning_init( void )
{
    uint32_t slot_cnt;
    is_enabled = FALSE;
    
    warning_lights_init();

    for( slot_cnt = 0; slot_cnt < SLOT_MAX_COUNT; slot_cnt++ )
    {
        slot_data[slot_cnt] = Warning_Unused;
    }
}

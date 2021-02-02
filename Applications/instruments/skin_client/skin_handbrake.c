#include "skin_handbrake.h"
#include "t_threads.h"
#include "gauges_lib.h"
#include "warning_lights.h"
#include "skin_warning.h"

////////////////////////////////////////////////////////////////////////////////////////

#define FUEL_NIDDLE_BACKUP_LEN      256
#define HANBRAKE_ICON_FLASH_MS      300

////////////////////////////////////////////////////////////////////////////////////////

static bool_t is_enabled;
static void * icon_mutex;
static void * icon_cond;
static handbrake_state_t main_state;
static handbrake_state_t saved_state;

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

static void handbrake_thread( void )
{
    handbrake_state_t local_state = HandBrake_Released;
    bool_t state = FALSE;
    
    while( 1 )
    {
        tthread_mutex_lock( icon_mutex );
        local_state = main_state;
        tthread_mutex_unlock( icon_mutex );
        
        if( local_state == HandBrake_Moving )
        {
            state = state ? FALSE : TRUE;
            skin_warning_update( WARNING_SLOT_HANDBRAKE, Warning_Brake_Parking, state );
            tthread_sleep_ms( HANBRAKE_ICON_FLASH_MS );
            
            state = state ? FALSE : TRUE;
            skin_warning_update( WARNING_SLOT_HANDBRAKE, Warning_Brake_Parking, state );
            tthread_sleep_ms( HANBRAKE_ICON_FLASH_MS );
        }
        else if( local_state == HandBrake_Released )
        {
            state = FALSE;
            skin_warning_update( WARNING_SLOT_HANDBRAKE, Warning_Brake_Parking, state );
        }
        else if( local_state == HandBrake_Pulled )
        {
            state = TRUE;
            skin_warning_update( WARNING_SLOT_HANDBRAKE, Warning_Brake_Parking, state );
        }

        if( local_state != HandBrake_Moving )
        {
            tthread_condition_wait( icon_cond );
        }        
    }
}

void skin_handbrake_set_value( handbrake_state_t value )
{
    if( is_enabled == TRUE )
    {
        tthread_mutex_lock( icon_mutex );
        main_state = value;
        tthread_mutex_unlock( icon_mutex );

        tthread_condition_signal( icon_cond );
    }
    else
    {
        saved_state = value;
    }
}

void skin_handbrake_hide( void )
{
    saved_state = main_state;
    skin_handbrake_set_value( HandBrake_Released );
    is_enabled = FALSE;
}

void skin_handbrake_reload( void )
{
    is_enabled = TRUE;
    skin_handbrake_set_value( saved_state );
}

void skin_handbrake_init( void )
{
    is_enabled = FALSE;
    
    main_state = HandBrake_Released;
    saved_state = HandBrake_Released;

    icon_cond = tthread_condition_create();
    icon_mutex = tthread_mutex_init();
    
    tthread_create( handbrake_thread );
}

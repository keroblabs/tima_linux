#include "skin_infocentre.h"
#include "touchscreen_lib.h"
#include "t_threads.h"
#include "driving_data.h"

////////////////////////////////////////////////////////////////////////////////////////////////

#define INFOCENTRE_MESSAGE_LEN              30

#define UPDATE_FLAG(m,i,s)                  if((s)) m|=(1<<(i)); else m&=~(1<<(i));

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

static bool_t touchscreen_event( touchscreen_event_t event, uint16_t posx, uint16_t posy, uint16_t posz )
{
    bool_t ret = FALSE;

    switch( event )
    {
        case Touchscreen_Event_Start:
            break;

        case Touchscreen_Event_Short:
            //printf( "infocentre - touch\n" );
            driving_data_send_message( MessageSkin_Button0 );
            break;

        case Touchscreen_Event_MoveLeft:
        case Touchscreen_Event_MoveRight:
            //printf( "infocentre - move\n" );
            driving_data_send_message( MessageSkin_Button2 );
            break;

        case Touchscreen_Event_End :
            break;
    }

    return ret;
}

static infocentre_msg_index_t get_infocentre_message_from_mask( state_mask_t mask )
{
    switch( mask )
    {
        case StateMask_BrakeFailure:        return InfoCentre_Brake_Failure;
        case StateMask_BrakeFluid:          return InfoCentre_Low_BrakeFluid;
        case StateMask_Washers:             return InfoCentre_Low_Washer;
        case StateMask_LowFuel:             return InfoCentre_Low_Fuel;
        case StateMask_EngineTemperature:   return InfoCentre_Engine_Overheat;
        case StateMask_CANFailure:          return InfoCentre_CAN_Failure;
        case StateMask_DTC_Indicator:       return InfoCentre_DTC_Detected;
        case StateMask_KeyMissing:          return InfoCentre_Key_Failure;
    }

    return InfoCentre_Message_MAX;
}

static column_info_t get_column_from_reading( reading_values_t reading )
{
    switch( reading )
    {
        case Reading_FuelInTank:        return Column_Info_Fuel_InTank;
        case Reading_FuelUsed:          return Column_Info_Fuel_Used;
        case Reading_ConsuptionAverage: return Column_Info_Consuption_Average;
        case Reading_ConsuptionInstant: return Column_Info_Consuption_Instant;
        case Reading_SpeedAverage:      return Column_Info_Speed_Average;
        case Reading_EngineTemp:        return Column_Info_Engine_Temp;
        case Reading_BatteryVoltage:    return Column_Info_Battery_Voltage;
        case Reading_SpeedGPS:          return Column_Info_Speed_GPS;
        case Reading_OilTemp:           return Column_Info_Oil_Temp;
    }

    return Column_Info_MAX;
}

void infocentre_set_flag( void * pp_data, state_mask_t mask, bool_t state )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;
    infocentre_msg_index_t infocentre_msg = get_infocentre_message_from_mask( mask );
    bool_t is_update = FALSE;
    
    if( infocentre_msg != InfoCentre_Message_MAX )
    {
        tthread_mutex_lock( p_data->mutex );
        uint32_t old_flag = p_data->flags;
        UPDATE_FLAG( p_data->flags, infocentre_msg, state );
        is_update = ( old_flag != p_data->flags );
        //printf( "infocentre_set_flag %d %d %d %d\n", state, is_update, p_data->column_index, p_data->is_enable );
        if( ( state == TRUE ) && ( is_update == TRUE ) && ( p_data->column_index != Column_Index_Message ) )
        {
            p_data->update_mask |= InfoCentre_Update_All;
            p_data->column_index = Column_Index_Message;
        }
        tthread_mutex_unlock( p_data->mutex );

        if( ( p_data->is_enable == TRUE ) && ( is_update == TRUE ) )
        {
            p_data->update_mask |= InfoCentre_Update_Messages;
            tthread_condition_signal( p_data->cond );
        }
    }
}

void infocentre_set_reading( void * pp_data, reading_values_t reading, int value )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;
    column_info_t column_info = get_column_from_reading( reading );
    bool_t is_update = FALSE;
    uint8_t elm_327_row;

    if( column_info != Column_Info_MAX )
    {
        tthread_mutex_lock( p_data->mutex );
        if( p_data->info_list[column_info] != value ) is_update = TRUE;
        p_data->info_list[column_info] = value;
        tthread_mutex_unlock( p_data->mutex );

        if( ( p_data->is_enable == TRUE ) && ( is_update == TRUE ) &&
            ( p_data->column_index == Column_Index_Info ) && ( p_data->row_index == column_info ) )
        {
            p_data->update_mask |= InfoCentre_Update_Info;
            tthread_condition_signal( p_data->cond );
        }
    }
    else
    {
        switch( reading )
        {
            case Reading_Odometer:
                tthread_mutex_lock( p_data->mutex );
                if( p_data->odometer != value ) is_update = TRUE;
                p_data->odometer = value;
                tthread_mutex_unlock( p_data->mutex );

                if( ( p_data->is_enable == TRUE ) && ( is_update == TRUE ) && ( p_data->column_index == Column_Index_Odometer ) )
                {
                    p_data->update_mask |= InfoCentre_Update_Odometer;
                    tthread_condition_signal( p_data->cond );
                }
                break;

            case Reading_ELM327_Bitmap:
            case Reading_ELM327_Field1:
            case Reading_ELM327_Field2:
            case Reading_ELM327_Field3:
                elm_327_row = reading - Reading_ELM327_Bitmap;
                if( p_data->elm_327_data[elm_327_row] != value ) is_update = TRUE;
                p_data->elm_327_data[elm_327_row] = value;

                if( ( p_data->is_enable == TRUE ) && ( is_update == TRUE ) &&
                    ( p_data->column_index == Column_Index_ELM327 ) && ( p_data->row_index == elm_327_row ) )
                {
                    p_data->update_mask |= InfoCentre_Update_ELM327;
                    tthread_condition_signal( p_data->cond );
                }
                break;
        }
    }
}

void infocentre_load_trips( void * pp_data, uint32_t * trips )
{
    uint32_t cnt;
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;

    tthread_mutex_lock( p_data->mutex );
    for( cnt = 0; cnt < ODOMETER_TRIP_MAX_INDEX; cnt++ )
    {
        p_data->trip_list[cnt] = trips[cnt];
    }
    tthread_mutex_unlock( p_data->mutex );

    if( ( p_data->is_enable == TRUE ) && ( p_data->column_index == Column_Index_Odometer ) )
    {
        p_data->update_mask |= InfoCentre_Update_Odometer;
        tthread_condition_signal( p_data->cond );
    }
}

void infocentre_change_column( void * pp_data, int dir )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;

    tthread_mutex_lock( p_data->mutex );
    if( ( dir > 0 ) && ( ++p_data->column_index >= Column_Index_MAX ) ) p_data->column_index = 0;
    else if( ( dir < 0 ) && ( --p_data->column_index >= Column_Index_MAX ) ) p_data->column_index = Column_Index_MAX - 1; // unsigned uses rollover

    p_data->row_index = 0;
    tthread_mutex_unlock( p_data->mutex );

    if( p_data->is_enable == TRUE )
    {
        p_data->update_mask |= InfoCentre_Update_All;
        tthread_condition_signal( p_data->cond );
    }
}

void infocentre_set_column( void * pp_data, int value )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;

    tthread_mutex_lock( p_data->mutex );
    if( value < Column_Index_MAX ) p_data->column_index = value;
    tthread_mutex_unlock( p_data->mutex );

    if( p_data->is_enable == TRUE )
    {
        p_data->update_mask |= InfoCentre_Update_All;
        tthread_condition_signal( p_data->cond );
    }
}

void infocentre_change_row( void * pp_data, int dir )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;

    tthread_mutex_lock( p_data->mutex );
    if( ( dir > 0 ) && ( ++p_data->row_index >= p_data->max_row_index ) ) p_data->row_index = 0;
    else if( ( dir < 0 ) && ( p_data->max_row_index > 1 ) && ( --p_data->row_index >= p_data->max_row_index ) ) p_data->row_index = p_data->max_row_index - 1; // unsigned uses rollover
    tthread_mutex_unlock( p_data->mutex );

    if( p_data->is_enable == TRUE )
    {
        p_data->update_mask |= InfoCentre_Update_All;
        tthread_condition_signal( p_data->cond );
    }
}

void infocentre_set_time( void * pp_data, struct tm * time_now )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;

    tthread_mutex_lock( p_data->mutex );
    memcpy( &p_data->std_time, time_now, sizeof( struct tm ) );
    p_data->update_mask |= InfoCentre_Update_Time;
    tthread_mutex_unlock( p_data->mutex );
 
    if( p_data->is_enable == TRUE )
    {
        tthread_condition_signal( p_data->cond );
    }
}

void infocentre_hide( void * pp_data )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;
    p_data->is_enable = FALSE;
}

void infocentre_reload( void * pp_data )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;
    
    p_data->is_enable = TRUE;
    p_data->flags_backup = 0;
    p_data->update_mask |= InfoCentre_Update_All;
    
    tthread_condition_signal( p_data->cond );
}

void * infocentre_init( void )
{
    infocentre_data_t * p_data;
    
    p_data = ( infocentre_data_t * )MMALLOC( sizeof( infocentre_data_t ) );
    if( p_data == NULL ) return NULL;
    memset( p_data, 0x00, sizeof( infocentre_data_t ) );
    
    memset( p_data->row_message, 0x00, sizeof( p_data->row_message ) );

    touchscreen_lib_set_handler( 420, 25, 640, 100, touchscreen_event );

    p_data->mutex = tthread_mutex_init();
    p_data->cond = tthread_condition_create();
    
    return p_data;
}

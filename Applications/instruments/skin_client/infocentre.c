#include "infocentre.h"
#include "t_threads.h"
#include "skin_infocentre.h"
#include "skin_standard.h"
#include "fill_flood.h"
#include "draw.h"

////////////////////////////////////////////////////////////////////////////////////////

#define DATE_TIME_BACKUP_SIZE               1024
#define INFOCENTRE_BACKUP_SIZE              4096
#define INFOCENTRE_MESSAGE_LEN              30

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

#define UPDATE_FLAG(m,i,s)          if(s) m|=(1<<i); else m&=~(1<<i);
#define LINE_HEIGHT					20
#define INFOCENTRE_LINE_BASE        85
#define INFOCENTRE_LINE1            (INFOCENTRE_LINE_BASE-LINE_HEIGHT-LINE_HEIGHT-LINE_HEIGHT)
#define INFOCENTRE_LINE2			(INFOCENTRE_LINE_BASE-LINE_HEIGHT-LINE_HEIGHT)
#define INFOCENTRE_LINE3			(INFOCENTRE_LINE_BASE-LINE_HEIGHT)
#define INFOCENTRE_LINE4			(INFOCENTRE_LINE_BASE)

#define INFOCENTRE_POSX(x)			(430+(x*12))

#define INFOCENTRE_TEXT_COLOUR      APP_RGB(180, 255, 180)

////////////////////////////////////////////////////////////////////////////////////////

const info_row_message_t init_row_message[] =
{
    { "BRAKE FAILURE",      InfoCentre_Brake_Failure,       FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "ENGINE OVERHEAT",    InfoCentre_Engine_Overheat,     FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "LOW BRAKE FLUID",    InfoCentre_Low_BrakeFluid,      FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "DOOR OPEN",          InfoCentre_Door_Open,           FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "LOW FUEL",           InfoCentre_Low_Fuel,            FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "LOW_WASHER",         InfoCentre_Low_Washer,          FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "CAN FAILURE",        InfoCentre_CAN_Failure,         FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
    { "KEY FAILURE",        InfoCentre_Key_Failure,         FALSE,  INFOCENTRE_MESSAGE_TYPE_WARNING },
};

////////////////////////////////////////////////////////////////////////////////////////

static graphics_backup_t * date_time_backup;
static graphics_backup_t * backup_line1;
static graphics_backup_t * backup_line2;
static graphics_backup_t * backup_line3;

////////////////////////////////////////////////////////////////////////////////////////

static const char * info_row_text[Column_Info_MAX] =
{
    "ENGINE TEMP",
    "OIL TEMP",
    "FUEL USED",
    "FUEL IN TANK",
    "FUEL TO EMPTY",
    "KM/L INSTANST",
    "KM/L AVERAGE",
    "BATTERY VOLTS",
    "SPEED AVERAGE",
    "SPEED GPS",
};

static const char * info_row_message[InfoCentre_Message_MAX] =
{
    "DTC DETECTED",
    "BRAKE FAILURE",
    "ENGINE OVERHEAT",
    "LOW BRAKE FLUID",
    "DOOR OPEN",
    "LOW FUEL",
    "LOW_WASHER",
	"CAN FAILURE",
	"KEY_FAILURE",
};

static const char * info_row_elm_327[InfoCentre_ELM327_MAX] =
{
    "BITMAP",
    "A1 29 [2:3]",
    "A1 29 [4]",
    "A1 7B",
};

static uint8_t infocentre_get_message_cnt( infocentre_data_t * p_data )
{
    uint8_t i;
    uint8_t ret;
    
    ret = 0;
    
    for( i = 0; i < 32; i++ )
    {
        if( ( 1 << i ) & p_data->flags ) ret++;
    }
    
    return ret;
}

static void infocentre_show_elm327_row( void * p_lcd, infocentre_data_t * p_data )
{
    char info_str[INFOCENTRE_MESSAGE_LEN];
    bitmap_t * lcd = ( bitmap_t * )p_lcd;

    p_data->max_row_index = InfoCentre_ELM327_MAX;

    graphics_restore_backup( lcd, backup_line1 );
    graphics_restore_backup( lcd, backup_line2 );
    graphics_restore_backup( lcd, backup_line3 );
    draw_font_init(FONT_12x16);

    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE1, "ELM327 DATA", INFOCENTRE_TEXT_COLOUR, backup_line1 );
    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE2, info_row_elm_327[p_data->row_index], INFOCENTRE_TEXT_COLOUR, backup_line1 );

    if( p_data->row_index == InfoCentre_ELM327_Bitmap )
    {
        sprintf( info_str, "0x%02x", p_data->elm_327_data[p_data->row_index] );
    }
    else
    {
        sprintf( info_str, "%d      ", p_data->elm_327_data[p_data->row_index] );
    }

    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE3, info_str, INFOCENTRE_TEXT_COLOUR, backup_line1 );
}

static void infocentre_show_trip_row( void * p_lcd, infocentre_data_t * p_data )
{
    char info_str[INFOCENTRE_MESSAGE_LEN];
    bitmap_t * lcd = ( bitmap_t * )p_lcd;

    p_data->max_row_index = ODOMETER_TRIP_MAX_INDEX;

    graphics_restore_backup( lcd, backup_line1 );
    graphics_restore_backup( lcd, backup_line2 );
    graphics_restore_backup( lcd, backup_line3 );
    draw_font_init(FONT_12x16);

    uint32_t trip_odometer = (p_data->odometer - p_data->trip_list[p_data->row_index]) % 100000;
    sprintf( info_str, "TRIP %d %5d.%02d", p_data->row_index + 1, trip_odometer/100, trip_odometer%100 );
    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE1, info_str, INFOCENTRE_TEXT_COLOUR, backup_line1 );

    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE2, "ODOMETER", INFOCENTRE_TEXT_COLOUR, backup_line2 );
    sprintf( info_str, "%12d.%02d", p_data->odometer/100, p_data->odometer%100 );

    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE3, info_str, INFOCENTRE_TEXT_COLOUR, backup_line3 );
}

static void infocentre_show_info_row( void * p_lcd, infocentre_data_t * p_data )
{
    char info_str[INFOCENTRE_MESSAGE_LEN];
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    
    p_data->max_row_index = Column_Info_MAX;
    
    graphics_restore_backup( lcd, backup_line1 );
    graphics_restore_backup( lcd, backup_line2 );
    graphics_restore_backup( lcd, backup_line3 );
    draw_font_init(FONT_12x16);
    
    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE1, info_row_text[p_data->row_index], INFOCENTRE_TEXT_COLOUR, backup_line1 );

    switch( p_data->row_index )
    {
        case Column_Info_Fuel_Used:
        case Column_Info_Fuel_InTank:
        case Column_Info_Fuel_ToEmpty:
            sprintf( info_str, "%2d.%d L ", p_data->info_list[p_data->row_index] / 100, p_data->info_list[p_data->row_index] % 100 );
            break;
        
        case Column_Info_Consuption_Average:
        case Column_Info_Consuption_Instant:
            sprintf( info_str, "%2d.%d KM/L ", p_data->info_list[p_data->row_index] / 100, p_data->info_list[p_data->row_index] % 100 );
            break;
        
        case Column_Info_Speed_Average:
        case Column_Info_Speed_GPS:
            sprintf( info_str, "%3d KM/H ", p_data->info_list[p_data->row_index] );
            break;
        
        case Column_Info_Engine_Temp:
        case Column_Info_Oil_Temp:
            sprintf( info_str, "%3d DEGREE ", (int)p_data->info_list[p_data->row_index] );
            break;

        case Column_Info_Battery_Voltage:
            sprintf( info_str, "%2d.%d V ", p_data->info_list[p_data->row_index] / 10, p_data->info_list[p_data->row_index] % 10 );
        	break;
    }
    
    draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE2, info_str, INFOCENTRE_TEXT_COLOUR, backup_line2 );
}

static void infocentre_show_message_row( void * p_lcd, infocentre_data_t * p_data )
{
    bitmap_t * lcd = ( bitmap_t * )p_lcd;
    uint8_t msg_cnt;
    uint32_t counter;
    uint32_t msg_mask;
    uint32_t message_index;
    char message_str[INFOCENTRE_MESSAGE_LEN];

    graphics_restore_backup( lcd, backup_line1 );
    graphics_restore_backup( lcd, backup_line2 );
    graphics_restore_backup( lcd, backup_line3 );
    draw_font_init(FONT_12x16);

    msg_cnt = infocentre_get_message_cnt( p_data );
    
    if( msg_cnt == 0 )
    {
        p_data->max_row_index = 0;
        draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE1, "NO MESSAGE", INFOCENTRE_TEXT_COLOUR, backup_line1 );
    }
    else
    {
        p_data->max_row_index = msg_cnt;
        message_index = p_data->row_index+1;
        
        sprintf( message_str, "MESSAGE %d/%d  ", message_index, msg_cnt );
        draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE1, message_str, INFOCENTRE_TEXT_COLOUR, backup_line1 );

        counter = 0;
        msg_mask = 0;
        
        // find the message_index'th message
        while( ( msg_mask < 32 ) && ( counter < message_index ) )
        {
            if( ( ( 1 << msg_mask ) & p_data->flags ) != 0 ) counter++;
            msg_mask++;
        }
        
        if( ( msg_mask > 0 ) && ( msg_mask < 32 ) )
        {
            draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE2, info_row_message[msg_mask-1], INFOCENTRE_TEXT_COLOUR, backup_line2 );
        }
    }
}

static void infocentre_display( void * lcd, infocentre_data_t * p_data )
{
    switch( p_data->column_index )
    {
        case Column_Index_Info:
            if( p_data->update_mask & InfoCentre_Update_Info )
            {
                infocentre_show_info_row( lcd, p_data );
                p_data->update_mask &= ~InfoCentre_Update_Info;
            }
            break;
            
        case Column_Index_Message:
            if( p_data->update_mask & InfoCentre_Update_Messages )
            {
                infocentre_show_message_row( lcd, p_data );
                p_data->update_mask &= ~InfoCentre_Update_Messages;
            }
            break;

        case Column_Index_Odometer:
            if( p_data->update_mask & InfoCentre_Update_Odometer )
            {
                infocentre_show_trip_row( lcd, p_data );
                p_data->update_mask &= ~InfoCentre_Update_Odometer;
            }
            break;

        case Column_Index_ELM327:
            if( p_data->update_mask & InfoCentre_Update_ELM327 )
            {
                infocentre_show_elm327_row( lcd, p_data );
                p_data->update_mask &= ~InfoCentre_Update_ELM327;
            }
            break;
    }
}

static void infocentre_thread( void * args )
{
    char time_now_str[INFOCENTRE_MESSAGE_LEN];
    infocentre_data_t * p_data = ( infocentre_data_t * )args;
    bitmap_t *          lcd;
    
    while( 1 )
    {
        tthread_condition_wait( p_data->cond );
        lcd = graphics_claim();
        
        infocentre_display( lcd, p_data );
        
        if( p_data->update_mask & InfoCentre_Update_Time )
        {
            p_data->update_mask &= ~InfoCentre_Update_Time;
            
            graphics_restore_backup( lcd, date_time_backup );
            sprintf( time_now_str, "%2d:%02d", p_data->std_time.tm_hour, p_data->std_time.tm_min );
            
            draw_font_init(FONT_12x16);
            draw_text_ex( lcd, INFOCENTRE_POSX(0), INFOCENTRE_LINE4, time_now_str, INFOCENTRE_TEXT_COLOUR, date_time_backup );
        }

        graphics_release();
    }
}

void infocentre_graphics_init( void * pp_data )
{
    infocentre_data_t * p_data = ( infocentre_data_t * )pp_data;
    
    date_time_backup = graphics_backup_create( DATE_TIME_BACKUP_SIZE );
    backup_line1 = graphics_backup_create( INFOCENTRE_BACKUP_SIZE );
    backup_line2 = graphics_backup_create( INFOCENTRE_BACKUP_SIZE );
    backup_line3 = graphics_backup_create( INFOCENTRE_BACKUP_SIZE );
    
    memcpy( p_data->row_message, init_row_message, sizeof( init_row_message ) );
    
    tthread_create_ex( infocentre_thread, pp_data );
}

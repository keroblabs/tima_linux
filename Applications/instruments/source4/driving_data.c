#include "driving_data.h"
#include "t_threads.h"
#include "tima_libc.h"

////////////////////////////////////////////////////////////////////

typedef struct driving_data_command_t_
{
    char * command;
    void ( *handler )( const char *arg1, string_t * comand, uint32_t pos );
} driving_data_command_t;

////////////////////////////////////////////////////////////////////

static void process_set_mask( const char *arg1, string_t * command, uint32_t pos );
static void process_set_value( const char *arg1, string_t * command, uint32_t pos );
static void process_set_indicator( const char *arg1, string_t * command, uint32_t pos );
static void process_set_start_mode( const char *arg1, string_t * command, uint32_t pos );
static void process_set_handbrake( const char *arg1, string_t * command, uint32_t pos );
static void process_send_message( const char *arg1, string_t * command, uint32_t pos );
static void process_reset_trip( const char *arg1, string_t * command, uint32_t pos );

////////////////////////////////////////////////////////////////////

static driving_data_command_t driving_commands[] =
{
    { "setmask",        process_set_mask },
    { "set_value",      process_set_value },
    { "set_indicator",  process_set_indicator },
    { "set_start_mode", process_set_start_mode },
    { "set_handbrake",  process_set_handbrake },
    { "send_message",   process_send_message },
    { "reset_trip",     process_reset_trip },
    { "",               NULL },
};

////////////////////////////////////////////////////////////////////

static driving_data_t driving_data;
static void * driving_mutex;

////////////////////////////////////////////////////////////////////

static void send_message( uint16_t message )
{
    int count;
    
    for( count = 0; count < MAX_APPLICATION_SKIN; count++ )
    {
        if( driving_data.message_data[count] != NULL )
        {
            message_Post( driving_data.message_data[count], message+Message_User_Space );
        }
    }
}

static void process_set_mask( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    string_t * arg3 = string_parse( command, &pos, " " );

    state_mask_t flag = ( state_mask_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    bool_t state = ( bool_t )tima_atoi( string_get_char_buffer( arg3 ), 10 );
    driving_data_state_mask( flag, state );
}

static void process_set_value( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    string_t * arg3 = string_parse( command, &pos, " " );
    
    reading_values_t index = ( reading_values_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    int value = ( int )tima_atoi( string_get_char_buffer( arg3 ), 10 );
    driving_data_set_reading_value( index, value );
}

static void process_set_indicator( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    indicator_state_t mode = ( indicator_state_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    driving_data_set_indication_icon( mode );
}

static void process_set_start_mode( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    start_mode_t mode = ( start_mode_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    driving_data_set_start_mode( mode );
}

static void process_set_handbrake( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    handbrake_state_t mode = ( handbrake_state_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    driving_data_set_handbrake_icon( mode );
}

static void process_reset_trip( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    uint8_t index = ( uint16_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    driving_data_reset_trip( index );
}

static void process_send_message( const char *arg1, string_t * command, uint32_t pos )
{
    string_t * arg2 = string_parse( command, &pos, " " );
    uint16_t message = ( uint16_t )tima_atoi( string_get_char_buffer( arg2 ), 10 );
    driving_data_send_message( message );
}

void driving_data_execute_command( string_t * command )
{
    int i = 0;
    
    uint32_t pos = 0;
    string_t * argv_1 = string_parse( command, &pos, " " );

    while( driving_commands[i].handler != NULL )
    {
        char * buffer = string_get_char_buffer( argv_1 );
        if( !strcmp( driving_commands[i].command, buffer ) )
        {
            driving_commands[i].handler( buffer, command, pos );
            break;
        }
        
        i++;
    }

    string_destroy( argv_1 );
}

driving_data_t * driving_data_lock( void )
{
    tthread_mutex_lock( driving_mutex );
    return &driving_data;
}

void driving_data_release( void )
{
    tthread_mutex_unlock( driving_mutex );
}

void driving_data_get_updated( driving_data_t * data )
{
    tthread_mutex_lock( driving_mutex );
    memcpy( data, &driving_data, sizeof( driving_data_t ) );
    tthread_mutex_unlock( driving_mutex );
}

void driving_data_set_time( struct tm * time )
{
    tthread_mutex_lock( driving_mutex );
    driving_data.std_time = time;
    tthread_mutex_unlock( driving_mutex );
    
    send_message( MessageSkin_UpdateTime );
}

void driving_data_state_mask( state_mask_t flag, bool_t state )
{
    tthread_mutex_lock( driving_mutex );
    if( state ) driving_data.state_mask |= ( 1 << (uint32_t)flag );
    else driving_data.state_mask &= ~( 1 << (uint32_t)flag );
    //printf( "driving_data.state_mask= 0x%08x\n", driving_data.state_mask );
    tthread_mutex_unlock( driving_mutex );
    
    send_message( MessageSkin_StateMask );
}

uint32_t driving_data_get_mask( void )
{
    uint32_t ret;
    tthread_mutex_lock( driving_mutex );
    ret = driving_data.state_mask;
    return ret;
}

void driving_data_set_mask( uint32_t mask )
{
    driving_data.state_mask = mask;
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_StateMask );
}

void driving_data_set_reading_value( reading_values_t index, int value )
{
    tthread_mutex_lock( driving_mutex );
    if( index < Reading_MAX ) driving_data.reading_values[index] = value;
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_ReadingValues );
}

int driving_data_get_reading_value( reading_values_t index )
{
    int ret = 0;
    
    tthread_mutex_lock( driving_mutex );
    if( index < Reading_MAX ) ret = driving_data.reading_values[index];
    tthread_mutex_unlock( driving_mutex );
    
    return ret;
}

void driving_data_set_indication_icon( indicator_state_t mode )
{
    tthread_mutex_lock( driving_mutex );
    driving_data.indicator_icon = mode;
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_IndicatorIcon );
}

void driving_data_set_start_mode( start_mode_t mode )
{
    tthread_mutex_lock( driving_mutex );
    driving_data.start_mode = mode;
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_StartMode );
}

void driving_data_set_handbrake_icon( handbrake_state_t mode )
{
    tthread_mutex_lock( driving_mutex );
    driving_data.handbrake_icon = mode;
    tthread_mutex_unlock( driving_mutex );
    
    send_message( MessageSkin_HandbrakeIcon );
}

void driving_data_set_trips( uint32_t * value )
{
    tthread_mutex_lock( driving_mutex );
    for( int i = 0; i < ODOMETER_TRIP_MAX_INDEX; i++ )
    {
        driving_data.trip_list[i] = value[i];
    }
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_LoadTrip );
}

void driving_data_reset_trip( uint8_t index )
{
    if( index >= ODOMETER_TRIP_MAX_INDEX ) return;

    tthread_mutex_lock( driving_mutex );
    driving_data.trip_list[index] = driving_data.reading_values[Reading_Odometer];
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_LoadTrip );
}

void driving_data_next_trip( void )
{
    send_message( MessageSkin_NextTrip );
}

void driving_data_handbrake_icon( bool_t state )
{
    tthread_mutex_lock( driving_mutex );
    driving_data.handbrake_icon = state ? HandBrake_Pulled : HandBrake_Released ;
    tthread_mutex_unlock( driving_mutex );

    send_message( MessageSkin_HandbrakeIcon );
}

void driving_data_send_message( uint16_t message )
{
    send_message( message );
}

void driving_data_init( void )
{
    driving_mutex = tthread_mutex_init();
    memset( &driving_data, 0x00, sizeof( driving_data_t ) );
}

void driving_data_attach_skin( message_data_t * message )
{
    int count;
    
    driving_data_t * attach_driving_data = driving_data_lock();

    for( count = 0; count < MAX_APPLICATION_SKIN; count++ )
    {
        if( attach_driving_data->message_data[count] == NULL )
        {
            attach_driving_data->message_data[count] = message;
            break;
        }
    }

    driving_data_release();
}

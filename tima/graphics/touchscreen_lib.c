#include "touchscreen_lib.h"
#include "timer.h"
#include "t_threads.h"

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

#define TOUCHSCREEN_APP_NOT_SET         -1
#define ODOMETER_LONG_PRESS             1800
#define TOUCHSCREEN_MOVE_DELTA          120
#define TOUCHSCREEN_TOUCH_DELTA         20
#define TOUCHSCREEN_MAX_HANDLER         10

////////////////////////////////////////////////////////////////////////////////////////

typedef struct touchscreen_app_data_t_
{
    bool_t is_set;

    uint16_t posx1;
    uint16_t posy1;
    uint16_t posx2;
    uint16_t posy2;

    uint16_t start_posx;
    uint16_t start_posy;

    uint16_t prev_posx;
    uint16_t prev_posy;

    timer_data_t timer;

    bool_t is_moved;
    bool_t is_done;

    touchscreen_event_handler_t handler;

} touchscreen_app_data_t;

////////////////////////////////////////////////////////////////////////////////////////

static touchscreen_app_data_t app_list[TOUCHSCREEN_MAX_HANDLER];

static uint16_t local_posx, local_posy, local_posz;
static void * reading_mutex;
static void * touch_cond;

////////////////////////////////////////////////////////////////////////////////////////

static bool_t is_touch_area( touchscreen_app_data_t * data, uint16_t posx, uint16_t posy )
{
    return ( data->handler && ( posx >= data->posx1 ) && ( posx < data->posx2 ) && ( posy >= data->posy1 ) && ( posy < data->posy2 ) ) ?
            TRUE : FALSE;
}

static touchscreen_event_t has_moved( touchscreen_app_data_t * data, uint16_t posx, uint16_t posy )
{
    if( ( posy < data->start_posy ) && ( ( data->start_posy - posy ) > TOUCHSCREEN_MOVE_DELTA ) )
    {
        return Touchscreen_Event_MoveUp;
    }
    else if( ( posy > data->start_posy ) && ( ( posy - data->start_posy ) > TOUCHSCREEN_MOVE_DELTA ) )
    {
        return Touchscreen_Event_MoveDown;
    }
    else if( ( posx < data->start_posx ) && ( ( data->start_posx - posx ) > TOUCHSCREEN_MOVE_DELTA ) )
    {
        return Touchscreen_Event_MoveLeft;
    }
    else if( ( posx > data->start_posx ) && ( ( posx - data->start_posx ) > TOUCHSCREEN_MOVE_DELTA ) )
    {
        return Touchscreen_Event_MoveRight;
    }
    else if( ( ABS( posx - data->start_posx ) < TOUCHSCREEN_TOUCH_DELTA ) && ( ABS( posy - data->start_posy ) <  TOUCHSCREEN_TOUCH_DELTA ) )
    {
        return Touchscreen_Event_Short;
    }

    return Touchscreen_Event_None;
}

static void touchscreen_lib_thread( void )
{
    int app_target = TOUCHSCREEN_APP_NOT_SET;
    int index;
    uint16_t posx;
    uint16_t posy;
    uint16_t posz;

    while( 1 )
    {
        if( app_target == TOUCHSCREEN_APP_NOT_SET )
        {
            tthread_condition_wait( touch_cond );
        }
        else
        {
            tthread_sleep_ms( 50 );

            if( ( app_list[app_target].is_moved == FALSE ) && ( app_list[app_target].is_done == FALSE ) )
            {
                if( timer_Check( &app_list[app_target].timer ) )
                {
                    //printf( "touchscreen Long %d\n", app_target );
                    app_list[app_target].handler( Touchscreen_Event_Long, app_list[app_target].prev_posx, app_list[app_target].prev_posy, 100 );
                    app_list[app_target].is_done = TRUE;
                }
            }
        }

        touchscreen_lib_get_reading( &posx, &posy, &posz );

        if( ( posz != 0 ) && ( app_target == TOUCHSCREEN_APP_NOT_SET ) )
        {
            for( index = 0; index < TOUCHSCREEN_MAX_HANDLER; index++ )
            {
                if( app_list[index].is_set == FALSE ) break;

                if( is_touch_area( &app_list[index], posx, posy ) )
                {
                    app_target = index;
                    app_list[app_target].handler( Touchscreen_Event_Start, posx, posy, posz );
                    timer_Start( &app_list[app_target].timer, ODOMETER_LONG_PRESS );

                    app_list[app_target].start_posx = posx;
                    app_list[app_target].start_posy = posy;
                    app_list[app_target].is_moved = FALSE;
                    app_list[app_target].is_done = FALSE;

                    //printf( "touchscreen start %d\n", app_target );
                    break;
                }
            }
        }

        if( app_target != TOUCHSCREEN_APP_NOT_SET )
        {
            if( !is_touch_area( &app_list[index], posx, posy ) || ( posz == 0 ) )
            {
                //printf( "touchscreen finish [%d] %d\n", app_list[app_target].is_moved, app_target );
                if( app_list[app_target].is_moved || app_list[app_target].is_done )
                {
                    app_list[app_target].handler( Touchscreen_Event_End, posx, posy, posz );
                }
                else if( has_moved( &app_list[app_target], posx, posy ) == Touchscreen_Event_Short )
                {
                    app_list[app_target].handler( Touchscreen_Event_Short, posx, posy, posz );
                }

                app_target = TOUCHSCREEN_APP_NOT_SET;
            }
            else
            {
                //printf( "touchscreen touch %d\n", app_target );

                if( app_list[app_target].is_done == FALSE )
                {
                    app_list[app_target].prev_posx = posx;
                    app_list[app_target].prev_posy = posy;

                    touchscreen_event_t move_event = has_moved( &app_list[app_target], posx, posy );
                    if( ( move_event != Touchscreen_Event_Short ) && ( move_event != Touchscreen_Event_None ) )
                    {
                        //printf( "touchscreen move [%d] %d\n", move_event, app_target );
                        if( ( move_event == Touchscreen_Event_MoveUp ) || ( move_event == Touchscreen_Event_MoveDown ) ) app_list[app_target].start_posy = posy;
                        if( ( move_event == Touchscreen_Event_MoveLeft ) || ( move_event == Touchscreen_Event_MoveRight ) ) app_list[app_target].start_posx = posx;

                        app_list[app_target].handler( move_event, posx, posy, posz );
                        app_list[app_target].is_moved = TRUE;
                    }
                }
            }
        }
    }
}

void touchscreen_lib_set_reading( uint16_t posx, uint16_t posy, uint16_t posz )
{
    tthread_mutex_lock( reading_mutex );
    local_posx = posx;
    local_posy = posy;
    local_posz = posz;
    tthread_mutex_unlock( reading_mutex );

    tthread_condition_signal( touch_cond );
}

void touchscreen_lib_get_reading( uint16_t *posx, uint16_t *posy, uint16_t *posz )
{
    tthread_mutex_lock( reading_mutex );
    *posx = local_posx;
    *posy = local_posy;
    *posz = local_posz;
    tthread_mutex_unlock( reading_mutex );
}

void touchscreen_lib_set_handler( uint16_t posx1, uint16_t posy1, uint16_t posx2, uint16_t posy2, touchscreen_event_handler_t handler )
{
    for( int i = 0; i < TOUCHSCREEN_MAX_HANDLER; i++ )
    {
        if( app_list[i].is_set == FALSE )
        {
            //printf( "touchscreen_lib_set_handler %d\n", i );
            app_list[i].posx1 = posx1;
            app_list[i].posy1 = posy1;
            app_list[i].posx2 = posx2;
            app_list[i].posy2 = posy2;
            app_list[i].is_set = TRUE;
            app_list[i].handler = handler;
            break;
        }
    }
}

void touchscreen_lib_init( void )
{
    memset( app_list, 0x00, sizeof( app_list ) );

    reading_mutex = tthread_mutex_init();
    touch_cond = tthread_condition_create();

    tthread_create( touchscreen_lib_thread );
}

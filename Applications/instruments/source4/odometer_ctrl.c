#include "odometer_ctrl.h"
#include "buffer.h"
#include "timer.h"
#include "driving_data.h"
#include "system.h"

////////////////////////////////////////////////////////////////////

#define ODOMETER_INCREMENT_SIZE     10000

////////////////////////////////////////////////////////////////////

typedef struct odometer_calc_t_
{
    uint32_t speed;
    uint32_t timestamp;

} odometer_calc_t;

////////////////////////////////////////////////////////////////////

static buffer_data_t speed_buffer;
static odometer_data_t odometer_data;
static void * odometer_cond;
static void * odometer_mutex;

////////////////////////////////////////////////////////////////////

static void odometer_control_thread( void )
{
    odometer_calc_t data_prev;
    odometer_calc_t data_curr;
    uint32_t dist;
    bool_t update_odometer;

    data_prev.timestamp = 0;

    while( 1 )
    {
        tthread_condition_wait( odometer_cond );

        while( buffer_is_empty( &speed_buffer ) == FALSE )
        {
            if( data_prev.timestamp == 0 )
            {
                buffer_read_buffer( &speed_buffer, ( uint8_t * )&data_prev, sizeof( odometer_calc_t ) );
            }
            else
            {
                buffer_read_buffer( &speed_buffer, ( uint8_t * )&data_curr, sizeof( odometer_calc_t ) );
                if( data_curr.timestamp == 0 )
                {
                    // odometer reset was requested
                    memcpy( &data_prev, &data_curr, sizeof( odometer_calc_t ) );
                }
                else
                {
                    dist =  MIN( data_curr.speed, data_prev.speed ) * ( data_curr.timestamp - data_prev.timestamp );
                    dist += ( MAX( data_curr.speed, data_prev.speed ) - MIN( data_curr.speed, data_prev.speed ) ) *
                            ( data_curr.timestamp - data_prev.timestamp ) / 2;
                    dist /= 1000;

                    //printf( "dist = %d (%d)\n", dist, ( data_curr.timestamp - data_prev.timestamp ) );

                    memcpy( &data_prev, &data_curr, sizeof( odometer_calc_t ) );

                    update_odometer = FALSE;

                    tthread_mutex_lock( odometer_mutex );
                    odometer_data.incr_counter += dist;
                    if( odometer_data.incr_counter > ODOMETER_INCREMENT_SIZE )
                    {
                        while( odometer_data.incr_counter > ODOMETER_INCREMENT_SIZE )
                        {
                            odometer_data.incr_counter -= ODOMETER_INCREMENT_SIZE;
                            odometer_data.full_counter += 1;
                            update_odometer = TRUE;
                        }
                    }
                    tthread_mutex_unlock( odometer_mutex );

                    if( update_odometer ) driving_data_set_reading_value( Reading_Odometer, odometer_data.full_counter );
                }
            }
        }
    }
}

void odometer_control_add_speed_value( int value )
{
    odometer_calc_t data;

    data.speed = (uint32_t)value * 278;
    data.timestamp = timer_get_MS();

    buffer_write_buffer( &speed_buffer, ( uint8_t * )&data, sizeof( data ) );
    tthread_condition_signal( odometer_cond );
}

void odometer_control_get( odometer_data_t * data )
{
    tthread_mutex_lock( odometer_mutex );
    memcpy( data, &odometer_data, sizeof( odometer_data ) );
    tthread_mutex_unlock( odometer_mutex );
}

void odometer_control_set( odometer_data_t * data )
{
    tthread_mutex_lock( odometer_mutex );
    memcpy( &odometer_data, data, sizeof( odometer_data ) );
    tthread_mutex_unlock( odometer_mutex );
}

void odometer_control_reset( void )
{
    odometer_calc_t data;

    data.speed = 0;
    data.timestamp = 0;  // request odometer reset

    buffer_write_buffer( &speed_buffer, ( uint8_t * )&data, sizeof( data ) );
    tthread_condition_signal( odometer_cond );
}

void odometer_control_init( void )
{
    buffer_init( &speed_buffer, 4 * sizeof( odometer_data_t ) );
    odometer_cond = tthread_condition_create();
    odometer_mutex = tthread_mutex_init();

    tthread_create( odometer_control_thread );
}

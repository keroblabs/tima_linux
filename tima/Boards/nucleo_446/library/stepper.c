#include "system.h"
#include "hardware.h"

//////////////////////////////////////////////////////////////////////////////

#define STEPPER_STACK_SIZE      2048
#define STEPPER_TIM_LONG_PULSE  55000
#define STEPPER_MAX_REFERENCE   31

#define STEPPER_SLEEP_TIME_MS   1000
#define STEPPER_UPDATE_MS       50

#define STEPPER_MAX_STEPS_Y     10170
#define STEPPER_ADJ_SPEED_Y     400

//////////////////////////////////////////////////////////////////////////////

typedef enum
{
    Pulse_Disabled,
    Pulse_Off,
    Pulse_On,

} output_status_t;

typedef enum
{
    Rotate_CW,
    Rotate_ACW,

} output_dir_t;

//////////////////////////////////////////////////////////////////////////////

static const uint16_t time_table[STEPPER_MAX_REFERENCE+1] = {
38236	,21533	,15869	,12982	,11214	,10012	,9136	,8466	,7934	,7501	,
7140	,6834	,6571	,6341	,6139	,5959	,5798	,5652	,5520	,5400	,
5289	,5188	,5093	,5006	,4924	,4848	,4777	,4710	,4646	,4587	,
4530	,4477	,

};

static const uint16_t position_ref[STEPPER_MAX_REFERENCE+1] = {
16	,29	,40	,49	,58	,65	,72	,79	,84	,90	,95	,99	,104	,108	,112	,115	,
119	,122	,125	,129	,131	,134	,137	,140	,142	,145	,
147	,149	,151	,154	,156	,158	,

};

//////////////////////////////////////////////////////////////////////////////

static thread_data_t step_context;
static uint8_t step_stack[ STEPPER_STACK_SIZE ];

//////////////////////////////////////////////////////////////////////////////

__IO  handler_t stepper_x_pulse;
__IO  handler_t stepper_y_pulse;
__IO  handler_t stepper_x_dir;
__IO  handler_t stepper_y_dir;

__IO  output_status_t output_x;
__IO  output_status_t output_y;

__IO  output_dir_t dir_x;
__IO  output_dir_t dir_y;

__IO  int32_t position_x;
__IO  int32_t position_y;

__IO  int32_t new_position_x;
__IO  int32_t new_position_y;

__IO uint16_t CCR1_Val;
__IO uint16_t CCR2_Val;

__IO  handler_t stepper_enable;

static uint16_t PrescalerValue = 0;
static uint16_t capture = 0;

static uint16_t speed_index_x;
static uint16_t speed_index_y;

static bool_t is_init = FALSE;
static bool_t is_loop = FALSE;
static bool_t full_stop_x;
static bool_t full_stop_y;

static bool_t south_mode;

//////////////////////////////////////////////////////////////////////////////

void stepper_timer_init( void )
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Enable the TIM3 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Compute the prescaler value */
    // PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 6000000) - 1;
    PrescalerValue = 117;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

    /* Output Compare Timing Mode configuration: Channel1 (X) */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* Output Compare Timing Mode configuration: Channel2 (Y) */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

    /* TIM Interrupts enable */
    TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);

    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);
}

void stepper_reset_motors( void )
{
    gpio_reset(stepper_x_pulse);
    gpio_reset(stepper_y_pulse);
    gpio_reset(stepper_x_dir);
    gpio_reset(stepper_y_dir);

    gpio_reset(stepper_enable);

    output_x = Pulse_Disabled;
    output_y = Pulse_Disabled;

    dir_x = Rotate_CW;
    dir_y = Rotate_CW;

    CCR1_Val = STEPPER_TIM_LONG_PULSE;
    CCR2_Val = STEPPER_TIM_LONG_PULSE;

    speed_index_x = 0;
    speed_index_y = 0;
}

void stepper_hw_init( void )
{
    stepper_x_pulse = gpio_get_port( GPIO_STEP_X );
    stepper_y_pulse = gpio_get_port( GPIO_STEP_Y );

    stepper_x_dir = gpio_get_port( GPIO_DIR_X );
    stepper_y_dir = gpio_get_port( GPIO_DIR_Y );

    stepper_enable = gpio_get_port( GPIO_STEP_EN );

    stepper_reset_motors();

    position_x = new_position_x = 0;
    position_y = new_position_y = 0;

    full_stop_x = full_stop_y = 0;

    south_mode = FALSE;

    stepper_timer_init();
}

void stepper_thread( void * args )
{
    int32_t distance_x;
    int32_t distance_y;
    bool_t is_trigger;

    timer_data_t step_timer;
    timer_data_t sleep_timer;

    is_loop = TRUE;

    timer_Start( &sleep_timer, STEPPER_SLEEP_TIME_MS );

    while( is_loop )
    {
        timer_Start( &step_timer, STEPPER_UPDATE_MS );
        is_trigger = FALSE;

        DI();

        if( ( new_position_x != position_x ) || ( full_stop_x == TRUE ) )
        {
            is_trigger = TRUE;

            if( output_x == Pulse_Disabled ) output_x = Pulse_Off;

            if( full_stop_x == TRUE )
            {
                distance_x = 0;
            }
            else if( new_position_x > position_x )
            {
                distance_x = new_position_x - position_x;
                dir_x = Rotate_CW;

                if( south_mode == FALSE) gpio_reset(stepper_x_dir);
                else gpio_set(stepper_x_dir);
            }
            else if( new_position_x < position_x )
            {
                distance_x = position_x - new_position_x;
                dir_x = Rotate_ACW;
                gpio_set(stepper_x_dir);

                if( south_mode == FALSE) gpio_set(stepper_x_dir);
                else gpio_reset(stepper_x_dir);
            }

            if( ( full_stop_x == TRUE ) && ( speed_index_x == 0 ) ) full_stop_x = FALSE;
            else if( ( distance_x > position_ref[speed_index_x] ) && ( speed_index_x < STEPPER_MAX_REFERENCE ) ) speed_index_x++;
            else if( ( distance_x <= position_ref[speed_index_x] ) && ( speed_index_x > 0 ) ) speed_index_x--;

            CCR1_Val = time_table[speed_index_x];
        }
        else
        {
            output_x = Pulse_Disabled;
            speed_index_x = 0;
            CCR1_Val = STEPPER_TIM_LONG_PULSE;
        }

        if( ( new_position_y != position_y ) || ( full_stop_y == TRUE ) )
        {
            is_trigger = TRUE;

            if( output_y == Pulse_Disabled ) output_y = Pulse_Off;

            if( full_stop_y == TRUE )
            {
                distance_y = 0;
            }
            else if( new_position_y > position_y )
            {
                distance_y = new_position_y - position_y;
                dir_y = Rotate_CW;
                gpio_set(stepper_y_dir);
            }
            else
            {
                distance_y = position_y - new_position_y;
                dir_y = Rotate_ACW;
                gpio_reset(stepper_y_dir);
            }

            if( distance_y > STEPPER_MAX_STEPS_Y )
            {
                if( dir_y == Rotate_ACW )
                {
                    dir_y = Rotate_CW;
                    gpio_set(stepper_y_dir);
                }
                else
                {
                    dir_y = Rotate_ACW;
                    gpio_reset(stepper_y_dir);
                }
            }

            if( ( full_stop_y == TRUE ) && ( speed_index_y == 0 ) ) full_stop_y = FALSE;
            else if( ( distance_y > position_ref[speed_index_y] ) && ( speed_index_y < STEPPER_MAX_REFERENCE ) ) speed_index_y++;
            else if( ( distance_y <= position_ref[speed_index_y] ) && ( speed_index_y > 0 ) ) speed_index_y--;

            CCR2_Val = time_table[speed_index_y] - STEPPER_ADJ_SPEED_Y;
        }
        else
        {
            output_y = Pulse_Disabled;
            speed_index_y = 0;
            CCR2_Val = STEPPER_TIM_LONG_PULSE;
        }

        EI();

        if( is_trigger == TRUE )
        {
            timer_Start( &sleep_timer, STEPPER_SLEEP_TIME_MS );
            is_trigger = FALSE;
            gpio_reset(stepper_enable);
        }

        if( timer_Check( &sleep_timer ) == TRUE )
        {
            gpio_set(stepper_enable);
        }

        thread_wait( timer_Check( &step_timer ) == TRUE );
    }

    // thread exited, disable steppers
    DI();
    stepper_reset_motors();
    position_x = new_position_x = 0;
    position_y = new_position_y = 0;
    EI();
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

        if( output_x == Pulse_Off )
        {
            output_x = Pulse_On;
            gpio_set(stepper_x_pulse);
        }
        else if( output_x == Pulse_On )
        {
            output_x = Pulse_Off;
            gpio_reset(stepper_x_pulse);

            if( dir_x == Rotate_CW ) position_x++;
            else position_x--;
        }

        capture = TIM_GetCapture1(TIM3);
        TIM_SetCompare1(TIM3, capture + CCR1_Val);
    }
    else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);

        if( output_y == Pulse_Off )
        {
            output_y = Pulse_On;
            gpio_set(stepper_y_pulse);
        }
        else if( output_y == Pulse_On )
        {
            output_y = Pulse_Off;
            gpio_reset(stepper_y_pulse);

            if( dir_y == Rotate_CW ) position_y++;
            else position_y--;

            if( position_y > STEPPER_MAX_STEPS_Y ) position_y = -STEPPER_MAX_STEPS_Y;
            else if( position_y < -STEPPER_MAX_STEPS_Y ) position_y = STEPPER_MAX_STEPS_Y;
        }

        capture = TIM_GetCapture2(TIM3);
        TIM_SetCompare2(TIM3, capture + CCR2_Val);
    }
}

//////////////////////////////////////////////////////////////////////////////

uint32_t _step_set_mode( uint32_t index, uint32_t * value, uint32_t size )
{
    if( ( size == 1 ) && ( index == 1 ) )
    {
        if( ( value[0] & 0x0FF ) == 'N' )
        {
            south_mode = FALSE;
        }
        else if( ( value[0] & 0x0FF ) == 'S' )
        {
            south_mode = TRUE;
        }
    }
}

uint32_t _step_get_position( uint32_t index, uint32_t * value, uint32_t size )
{
    if( size >= 16 )
    {
        if( index == 0 )
        {
            value[0] = position_x;
            value[1] = new_position_x;
            value[2] = FALSE;
            value[3] = south_mode;
            if( new_position_x != position_x ) value[2] = TRUE;
        }
        else
        {
            value[0] = position_y;
            value[1] = new_position_y;
            value[2] = FALSE;
            value[3] = FALSE;
            if( new_position_y != position_y ) value[2] = TRUE;
        }
    }
    else
    {
        size = 0;
    }

    return size;
}

uint32_t _step_ioctrl( uint32_t index, uint32_t param, void * data )
{
    int32_t * pos = ( int32_t * )data;

    if( param == DEVICE_GET_RUNTIME_VALUE )
    {
        DI();
        if( index == 0 ) *pos = position_x;
        else *pos = position_y;
        EI();
        return ( uint32_t )TRUE;
    }
    else if( param == DEVICE_SET_RUNTIME_VALUE )
    {
        DI();
        if( index == 0 )
        {
            new_position_x = *pos;
        }
        else
        {
            new_position_y = *pos;
        }

        EI();
        return ( uint32_t )TRUE;
    }
    else if( param == DEVICE_SET_CONFIG_DATA )
    {
        DI();
        if( index == 0 )
        {
            // stepper_reset_motors();
            position_x = new_position_x = *pos;
            // position_y = new_position_y = 0;
        }
        else
        {
            position_y = new_position_y = *pos;
        }
        EI();
        return ( uint32_t )TRUE;
    }

	return 0;
}

bool_t _step_validate( uint32_t index )
{
	if( index <= 1 ) return TRUE;
    return FALSE;
}

void _step_driver_init( uint32_t index )
{
    if( is_init == TRUE ) return;
    is_init = TRUE;

    thread_create( &step_context, stepper_thread, NULL, step_stack, STEPPER_STACK_SIZE );
}

void _step_driver_disable( uint32_t index )
{
    // is_loop = FALSE;
}

//////////////////////////////////////////////////////////////////////////////

static bool_t _in_use = FALSE;

const static device_data_t stepper_device =
{
    "stepper*",
    &_in_use,

    _step_driver_init,
    _step_driver_disable,
    NULL,
    _step_validate,
    NULL,
    _step_ioctrl,

    DEV_MODE_CHANNEL,

    _step_get_position,
    _step_set_mode,

};

DECLARE_DEVICE_SECTION( stepper_device );

˙( stepper_hw_init );

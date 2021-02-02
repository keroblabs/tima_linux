#ifndef _GPIO_DATA_H_
#define _GPIO_DATA_H_

//////////////////////////////////////////////////////////////////////////////////////

#define GPIO_RELAY_IND_LEFT             GPIO_PE01
#define GPIO_RELAY_IND_RIGHT            GPIO_PE03
#define GPIO_RELAY_ACC                  GPIO_PE05
#define GPIO_RELAY_RUN                  GPIO_PE07
#define GPIO_RELAY_STARTER              GPIO_PH24
#define GPIO_OUT_HAZARD_LED             GPIO_PH25

#define GPIO_RELAY_FOGLIGHTS            GPIO_PE02
#define GPIO_RELAY_HEADLIGHTS           GPIO_PE04
#define GPIO_OUT_BRAKE_DRIVER           GPIO_PE06

#define GPIO_INPUT_IND_LEFT             GPIO_PH12
#define GPIO_INPUT_IND_RIGHT            GPIO_PH13

#define GPIO_INPUT_START_BUTTON         GPIO_PB03
#define GPIO_INPUT_HAZARD_BTN           GPIO_PB04
#define GPIO_INPUT_BRAKE_FLUID          GPIO_PB05
#define GPIO_INPUT_WASHER_LEVEL         GPIO_PB06

#define GPIO_INPUT_ENGINE_RUN           GPIO_PB14
#define GPIO_INPUT_IGNITION_SW          GPIO_PB13
#define GPIO_INPUT_FULL_BEAM            GPIO_PB11
#define GPIO_INPUT_OIL_PRESSURE         GPIO_PH10

#define GPIO_INPUT_BRAKE_SWITCH         GPIO_PI00
#define GPIO_INPUT_BATTERY_INDICATOR	GPIO_PE00

#define GPIO_INPUT_HEADLIGHTS_BTN       GPIO_PB07
#define GPIO_INPUT_FOGLIGHTS_BTN        GPIO_PB08

#define GPIO_INPUT_BUTTON0_BTN          GPIO_PB10
#define GPIO_INPUT_BUTTON1_BTN          GPIO_PH00

#define GPIO_INPUT_HANDBRAKE_RELEASE    GPIO_PB17
#define GPIO_INPUT_HANDBRAKE_PULL       GPIO_PB16

#define GPIO_COUNTER_ODOMETER           GPIO_PH02
#define GPIO_COUNTER_TACOMETER          GPIO_PH07


//////////////////////////////////////////////////////////////////////////////////////

typedef struct _gpio_setup_t
{
    char * c_id;
    int index;
    int inverted;
    int initial;
    
} gpio_setup_t;

//////////////////////////////////////////////////////////////////////////////////////

#endif // _GPIO_DATA_H_


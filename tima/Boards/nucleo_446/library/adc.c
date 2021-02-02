#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "system.h"

//#include "debug.h"

//////////////////////////////////////////////////////////////////////////////

#define ADC_NB_SAMPLES      1
#define ADC_DMA_SIZE        (uint32_t)( ADC_NB_CHANNELS )
#define ADC_TOTAL_INDEX		2
#define ADC_NOT_IN_USE		0xFF

#define ADC1_DR_Address     ((u32)0x4001204C)

//////////////////////////////////////////////////////////////////////////////

enum
{
	ADC_STATE_IDLE,
	ADC_STATE_PENDING,
	ADC_STATE_CONVERTING,
	ADC_STATE_READY
};

//////////////////////////////////////////////////////////////////////////////

static bool_t adc_init = FALSE;

static uint8_t adc_busy;
static uint8_t adc_index;
static uint8_t adc_state[ADC_TOTAL_INDEX];
static uint16_t adc_value[ADC_TOTAL_INDEX];

//////////////////////////////////////////////////////////////////////////////
    
void hw_adc_start( uint32_t channel )
{
	switch( channel )
	{
		case 0:
			ADC_RegularChannelConfig( ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles );
			break;
			
		case 1:
			ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles );
			break;
			
		//case 2:
		//	ADC_RegularChannelConfig( ADC1, ADC_Channel_4, 1, ADC_SampleTime_480Cycles );
		//	break;

		//case 3:
		//	ADC_RegularChannelConfig( ADC1, ADC_Channel_8, 1, ADC_SampleTime_480Cycles );
		//	break;

		default:
			return;
	}

    /* Enable ADC1 external trigger conversion */
    ADC_Cmd(ADC1, ENABLE);

    /* Start ADC1 Software Conversion */
    ADC_SoftwareStartConv( ADC1 );
}

bool_t hw_adc_check( uint16_t * value )
{
	if( ADC_GetFlagStatus( ADC1, ADC_FLAG_EOC ) == FALSE ) return FALSE;
	*value = ( ADC_GetConversionValue( ADC1 ) );
	//*value >>= 4;
	return TRUE;
}

void hw_adc_init( void )
{
    int i; 

    ADC_InitTypeDef   ADC_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
    // Clocks for ADC
    /* Enable DMA clock */

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    //GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ADC Common configuration */
	ADC_CommonInitStructure.ADC_Mode 				= ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay 	= ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode 		= ADC_DMAAccessMode_Disabled;  
	ADC_CommonInitStructure.ADC_Prescaler 			= ADC_Prescaler_Div2; 
	ADC_CommonInit(&ADC_CommonInitStructure);
  
    /* ADC1 Configuration */
	ADC_InitStructure.ADC_Resolution 			= ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode 	= DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion 		= 1; //ADC_DMA_SIZE;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_ContinuousModeCmd(ADC1, DISABLE);

  	/* enable temperature sensor */
    ADC_TempSensorVrefintCmd(ENABLE); //%%
	
}

///////////////////////////////////////////////////////////////

static void adc_process( void )
{
	uint16_t adc_result = 0;
	int i;

	if( adc_init == FALSE ) return;

	if( adc_busy != ADC_NOT_IN_USE )
	{
		if( hw_adc_check( &adc_result ) )
		{
			if( adc_state[ adc_busy ] == ADC_STATE_CONVERTING )
			{
				DEBUG_PRINTK( "ADC end %d\r\n", adc_busy );
				adc_state[adc_busy] = ADC_STATE_READY;
				//if( adc_busy != 0 ) adc_result >>= 4;
				adc_value[adc_busy] = adc_result;
			}

			adc_busy = ADC_NOT_IN_USE;
		}
	}
	else
	{
		if( adc_state[ adc_index ] == ADC_STATE_PENDING )
		{
			DEBUG_PRINTK( "ADC start %d\r\n", adc_index );
			adc_state[ adc_index ] = ADC_STATE_CONVERTING;
			hw_adc_start( adc_index );
			adc_busy = adc_index;
		}

		adc_index++;
		if( adc_index >= ADC_TOTAL_INDEX ) adc_index = 0;
	}
}

static uint32_t adc_output( uint32_t index, uint8_t * buffer, uint32_t size )
{
	int ret = 0;

	return ret;
}

static uint32_t adc_input( uint32_t index, uint8_t * buffer, uint32_t size )
{
	uint32_t ret = 0;
	uint32_t ret_value;
	uint16_t * p_adc = ( uint16_t * )buffer;

	if( adc_state[index] == ADC_STATE_READY )
	{
		// if adc conversion has finished
		ret = sizeof( uint16_t );

		if( buffer != NULL )
		{
			adc_state[index] = ADC_STATE_IDLE;
			*p_adc = adc_value[index];
		}
	}

    return ret;
}

static void adc_drv_init( uint32_t index )
{
	int i;

	if( adc_init == TRUE ) return;

	for( i = 0; i < ADC_TOTAL_INDEX; i++ )
	{
		adc_value[i] = 0;
		adc_state[i] = ADC_STATE_IDLE;
	}

	adc_busy = ADC_NOT_IN_USE;
	adc_index = 0;

	hw_adc_init();

	adc_init = TRUE;
}

static void adc_drv_close( uint32_t index )
{
}

static uint32_t adc_drv_ioctl( uint32_t index, uint32_t param, void * value )
{
	//uint32_t * p_value = ( uint32_t * )value;

	switch( param )
	{
		case DEVICE_SET_RUNTIME_VALUE:
			// trigger adc
			adc_state[index] = ADC_STATE_PENDING;
			DEBUG_PRINTK( "ADC trigger %d\r\n", index );
			break;
	}

	return 0;
}

static bool_t adc_validate( uint32_t index )
{
    if( index < ADC_TOTAL_INDEX ) return TRUE;
    return FALSE;
}

static void adc_global_init( void )
{
	adc_init = FALSE;
}

///////////////////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t adc_device =
{
    "adc*",
    &_in_use,

    adc_drv_init,
    adc_drv_close,
    NULL,
    adc_validate,
    NULL,
    adc_drv_ioctl,
    NULL,

    DEV_MODE_CHANNEL,

    adc_input,
    adc_output,

};

DECLARE_INIT_POWERUP_SECTION( adc_global_init );
DECLARE_DEVICE_SECTION( adc_device );
DECLARE_PROCESS_SECTION( adc_process );

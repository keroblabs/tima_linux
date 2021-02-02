#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "audio_layer.h"
#include "system.h"
#include "portaudio.h"

//////////////////////////////////////////////////////////////////////////////////////

#define WM8731_MAX_REG                  9
#define I2C_W8731_ADDR_0                0x1A
#define AUDIO_TOTAL_BUFFERS				2
#define AUDIO_DEVICE_COUNT              2
#define AUDIO_DEVICE_INPUT_ID           0
#define AUDIO_DEVICE_OUTPUT_ID          1
#define AUDIO_DEVICE_VERSION            2
#define AUDIO_DEVICE_EMPTY				0xFF
#define I2S_STANDARD_LSB

/* Codec audio Standards */
#ifdef I2S_STANDARD_PHILLIPS
 #define  CODEC_STANDARD                0x04
 #define I2S_STANDARD                   I2S_Standard_Phillips
#elif defined(I2S_STANDARD_MSB)
 #define  CODEC_STANDARD                0x00
 #define I2S_STANDARD                   I2S_Standard_MSB
#elif defined(I2S_STANDARD_LSB)
 #define  CODEC_STANDARD                0x08
 #define I2S_STANDARD                   I2S_Standard_LSB
#else
 #error "Error: No audio communication standard selected !"
#endif /* I2S_STANDARD */

//////////////////////////////////////////////////////////////////////////////////////

typedef struct WaveDeviceDataT
{
    audio_data_t * audio;
    
    void * audio_data;
    PaStreamParameters streamParameters;
    uint32_t sample_rate;
    PaStreamCallback * audio_callback;
    uint8_t device_index;

	int16_t WaveBuffer[AUDIO_BUFFER_SIZE*AUDIO_NUM_CHANNELS*AUDIO_TOTAL_BUFFERS];
	int16_t * p_audio_wave;

} pa_wave_dev_t;

//////////////////////////////////////////////////////////////////////////////////////

static pa_wave_dev_t pa_wave_dev[AUDIO_DEVICE_COUNT];
static bool_t is_init;

static const PaDeviceInfo pa_device_info =
{
    AUDIO_DEVICE_VERSION,
    "WM8731",
    0, // PaHostApiIndex
    2, // maxInputChannels
    2, // maxOutputChannels

    0.0, // defaultLowInputLatency;
    0.0, // defaultLowOutputLatency;
    0.0, // defaultHighInputLatency;
    0.0, // defaultHighOutputLatency;

    0.0, // defaultSampleRate;
};

//////////////////////////////////////////////////////////////////////////////////////

static const uint16_t wm8731_regs[ WM8731_MAX_REG + 1 ] =
{
	0x017,			// Reg 00: Left Line In (0dB, mute off)
	0x017,			// Reg 01: Right Line In (0dB, mute off)
	0x079,			// Reg 02: Left Headphone out (0dB)
	0x079,			// Reg 03: Right Headphone out (0dB)
	0x012,			// Reg 04: Analog Audio Path Control (DAC sel, Mute Mic)
	0x000,			// Reg 05: Digital Audio Path Control
	0x002,			// Reg 06: Power Down Control (Clkout, Osc, Mic Off)
//	0x00E,			// Reg 07: Digital Audio Interface Format (i2s, 32-bit, slave)
	0x022,			// Reg 07: Digital Audio Interface Format (i2s, 16-bit, slave)
	0x00C,			// Reg 08: Sampling Control (Normal, 256x, 48k ADC/DAC)
	0x001			// Reg 09: Active Control    
};

//////////////////////////////////////////////////////////////////////////////////////

#define CODEC_I2S_ADDRESS              0x4000380C
#define CODEC_I2S_EXT_ADDRESS          0x4000340C

/* I2S DMA Stream definitions */
#define AUDIO_I2S_DMA_CLOCK            RCC_AHB1Periph_DMA1
#define AUDIO_I2S_DMA_STREAM           DMA1_Stream4
#define AUDIO_I2S_DMA_DREG             CODEC_I2S_ADDRESS
#define AUDIO_I2S_DMA_CHANNEL          DMA_Channel_0
#define AUDIO_I2S_DMA_IRQ              DMA1_Stream4_IRQn
#define AUDIO_I2S_DMA_IRQ_HANDLER      DMA1_Stream4_IRQHandler
#define AUDIO_I2S_DMA_FLAG_TC          DMA_FLAG_TCIF4
#define AUDIO_I2S_DMA_FLAG_HT          DMA_FLAG_HTIF4
#define AUDIO_I2S_DMA_FLAG_FE          DMA_FLAG_FEIF4
#define AUDIO_I2S_DMA_FLAG_TE          DMA_FLAG_TEIF4
#define AUDIO_I2S_DMA_FLAG_DME         DMA_FLAG_DMEIF4

#define AUDIO_I2S_EXT_DMA_STREAM       DMA1_Stream3
#define AUDIO_I2S_EXT_DMA_DREG         CODEC_I2S_EXT_ADDRESS
#define AUDIO_I2S_EXT_DMA_CHANNEL      DMA_Channel_3
#define AUDIO_I2S_EXT_DMA_IRQ          DMA1_Stream3_IRQn
#define AUDIO_I2S_EXT_DMA_IRQ_HANDLER  DMA1_Stream3_IRQHandler
#define AUDIO_I2S_EXT_DMA_FLAG_TC      DMA_FLAG_TCIF3
#define AUDIO_I2S_EXT_DMA_FLAG_HT      DMA_FLAG_HTIF3
#define AUDIO_I2S_EXT_DMA_FLAG_FE      DMA_FLAG_FEIF3
#define AUDIO_I2S_EXT_DMA_FLAG_TE      DMA_FLAG_TEIF3
#define AUDIO_I2S_EXT_DMA_FLAG_DME     DMA_FLAG_DMEIF3

#define AUDIO_CODEC_I2S                SPI2
#define AUDIO_CODEC_I2S_EXT            I2S2ext

//////////////////////////////////////////////////////////////////////////////////////

void AUDIO_I2S_DMA_IRQ_HANDLER( void )
{
    // audio out callback
    if (DMA_GetFlagStatus(AUDIO_I2S_DMA_STREAM, AUDIO_I2S_DMA_FLAG_TC) != RESET)
    {
        DMA_ClearITPendingBit(AUDIO_I2S_DMA_STREAM, AUDIO_I2S_DMA_FLAG_TC);
        pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].p_audio_wave = &pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].WaveBuffer[ AUDIO_BUFFER_SIZE << 1 ];
    }
    else if (DMA_GetFlagStatus(AUDIO_I2S_DMA_STREAM, AUDIO_I2S_DMA_FLAG_HT) != RESET)
    {
        DMA_ClearITPendingBit(AUDIO_I2S_DMA_STREAM, AUDIO_I2S_DMA_FLAG_HT);
        pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].p_audio_wave = &pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].WaveBuffer[ 0 ];
    }
}

void AUDIO_I2S_EXT_DMA_IRQ_HANDLER( void )
{
    // audio in callback
    if (DMA_GetFlagStatus(AUDIO_I2S_EXT_DMA_STREAM, AUDIO_I2S_EXT_DMA_FLAG_TC) != RESET)
    {
        pa_wave_dev[AUDIO_DEVICE_INPUT_ID].p_audio_wave = &pa_wave_dev[AUDIO_DEVICE_INPUT_ID].WaveBuffer[ AUDIO_BUFFER_SIZE << 1 ];
        DMA_ClearITPendingBit(AUDIO_I2S_EXT_DMA_STREAM, AUDIO_I2S_EXT_DMA_FLAG_TC);
    }
    else if (DMA_GetFlagStatus(AUDIO_I2S_EXT_DMA_STREAM, AUDIO_I2S_EXT_DMA_FLAG_HT) != RESET)
    {
        pa_wave_dev[AUDIO_DEVICE_INPUT_ID].p_audio_wave = &pa_wave_dev[AUDIO_DEVICE_INPUT_ID].WaveBuffer[ 0 ];
        DMA_ClearITPendingBit(AUDIO_I2S_EXT_DMA_STREAM, AUDIO_I2S_EXT_DMA_FLAG_HT);
    }
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* DMA TX IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = AUDIO_I2S_DMA_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* DMA RX IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = AUDIO_I2S_EXT_DMA_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Connect pins to I2S peripheral  */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    /* I2S3S_WS */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* I2S3_CK, I2S3_SD, I2S3ext_SD */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void DMA_Configuration( void )
{
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitTypeDef DMA_InitStructure2;
    
    RCC_AHB1PeriphClockCmd(AUDIO_I2S_DMA_CLOCK, ENABLE);

	/* Configure the TX DMA Stream */
	DMA_Cmd(AUDIO_I2S_DMA_STREAM, DISABLE);
	DMA_DeInit(AUDIO_I2S_DMA_STREAM);
	/* Set the parameters to be configured */
	DMA_InitStructure.DMA_Channel = AUDIO_I2S_DMA_CHANNEL;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = AUDIO_I2S_DMA_DREG;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].WaveBuffer[0]; // out
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = ((uint32_t)AUDIO_BUFFER_SIZE << 2);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	DMA_Init(AUDIO_I2S_DMA_STREAM, &DMA_InitStructure);  
	
	/* Enable the Half & Complete DMA interrupts  */
	DMA_ITConfig(AUDIO_I2S_DMA_STREAM, DMA_IT_TC | DMA_IT_HT, ENABLE);
    
	/* I2S DMA IRQ Channel configuration */
	//NVIC_EnableIRQ(AUDIO_I2S_DMA_IRQ);

	/* Enable the I2S DMA request */
	SPI_I2S_DMACmd(AUDIO_CODEC_I2S, SPI_I2S_DMAReq_Tx, ENABLE);

    /***********************************************/
    
	/* Configure the RX DMA Stream */
	DMA_Cmd(AUDIO_I2S_EXT_DMA_STREAM, DISABLE);
	DMA_DeInit(AUDIO_I2S_EXT_DMA_STREAM);
	
	/* Set the parameters to be configured */
	/* why is a separate initstructure needed here? */
	DMA_InitStructure2.DMA_Channel = AUDIO_I2S_EXT_DMA_CHANNEL;  
	DMA_InitStructure2.DMA_PeripheralBaseAddr = AUDIO_I2S_EXT_DMA_DREG;
	DMA_InitStructure2.DMA_Memory0BaseAddr = (uint32_t)&pa_wave_dev[AUDIO_DEVICE_INPUT_ID].WaveBuffer[0]; // in
	DMA_InitStructure2.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure2.DMA_BufferSize = (uint32_t)AUDIO_BUFFER_SIZE << 2;
	DMA_InitStructure2.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure2.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure2.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure2.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 
	DMA_InitStructure2.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure2.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure2.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure2.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStructure2.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure2.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	DMA_Init(AUDIO_I2S_EXT_DMA_STREAM, &DMA_InitStructure2);  
	
	/* Enable the Half & Complete DMA interrupts  */
	DMA_ITConfig(AUDIO_I2S_EXT_DMA_STREAM, DMA_IT_TC | DMA_IT_HT, ENABLE);
    
	/* I2S DMA IRQ Channel configuration */
	//NVIC_EnableIRQ(AUDIO_I2S_EXT_DMA_IRQ);

	/* Enable the I2S DMA request */
	SPI_I2S_DMACmd(AUDIO_CODEC_I2S_EXT, SPI_I2S_DMAReq_Rx, ENABLE);
}

static void I2S_Configuration(uint32_t I2S_AudioFreq)
{
    I2S_InitTypeDef I2S_InitStructure;

    /* Enable the CODEC_I2S peripheral clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    SPI_I2S_DeInit(AUDIO_CODEC_I2S);

    /* I2S peripheral configuration */
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq;
    I2S_InitStructure.I2S_Standard = I2S_STANDARD;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Enable;

    /* I2S2 configuration */
    I2S_Init(AUDIO_CODEC_I2S, &I2S_InitStructure);
    
	/* Initialize the I2S extended channel for RX */
	I2S_FullDuplexConfig(AUDIO_CODEC_I2S_EXT, &I2S_InitStructure);    
}

static void audio_codec_write( uint8_t addr, uint16_t data )
{
	/* Assemble 2-byte data in WM8731 format */
	uint8_t Byte1 = ((addr<<1)&0xFE) | ((data>>8)&0x01);
	uint8_t Byte2 = data&0xFF;
    
    I2C_Bus_Start_Transmit( I2C_W8731_ADDR_0 );
    I2C_Write_Data( Byte1 );
    I2C_Write_Data( Byte2 );
    I2C_Bus_Stop();
}

static uint32_t audio_driver_codec_cmd( audio_data_t * audio, uint32_t command, uint32_t param )
{
	return 0;
}

static void audio_hw_driver_init( uint32_t sample_rate )
{
    __IO uint32_t cnt;
    
    switch( sample_rate )
    {
    	case I2S_AudioFreq_8k:
    	case I2S_AudioFreq_16k:
    	case I2S_AudioFreq_32k:
    	case I2S_AudioFreq_44k:
    	case I2S_AudioFreq_48k:
    		break;

    	default:
    		return;
    }

    /* Configure PLLI2S prescalers */
    /* PLLI2S_VCO : VCO_344M */
    /* SAI_CLK(first level) = PLLI2S_VCO/PLLI2SQ = 344/7 = 49.142 Mhz */
    RCC_PLLI2SConfig(16, 344, 2, 7, 2);

    RCC_I2SCLKConfig(RCC_I2SBus_APB1, RCC_I2SCLKSource_PLLI2S);
    RCC_PLLI2SCmd(ENABLE);

    GPIO_Configuration();
    I2S_Configuration(sample_rate);
    
    DMA_Configuration();
    NVIC_Configuration();
        
    // reset??
    audio_codec_write( 0x0F, 0 );
    
    // load default values
    for( cnt = 0; cnt <= WM8731_MAX_REG; cnt++ )
    {
        audio_codec_write( cnt, wm8731_regs[ cnt ] );
    }
}

static void audio_dma_out_start( void )
{    
    NVIC_EnableIRQ(AUDIO_I2S_DMA_IRQ);
    DMA_Cmd(AUDIO_I2S_DMA_STREAM, ENABLE); 
    I2S_Cmd(AUDIO_CODEC_I2S, ENABLE);
}

static void audio_dma_in_start( void )
{
    NVIC_EnableIRQ(AUDIO_I2S_EXT_DMA_IRQ);
    DMA_Cmd(AUDIO_I2S_EXT_DMA_STREAM, ENABLE); 
    I2S_Cmd(AUDIO_CODEC_I2S_EXT, ENABLE);    
}

static void audio_dma_out_stop( void )
{
    I2S_Cmd(AUDIO_CODEC_I2S, DISABLE);
    DMA_Cmd(AUDIO_I2S_DMA_STREAM, DISABLE); 
    NVIC_DisableIRQ( AUDIO_I2S_DMA_IRQ );
}

static void audio_dma_in_stop( void )
{
    I2S_Cmd(AUDIO_CODEC_I2S_EXT, DISABLE);    
    DMA_Cmd(AUDIO_I2S_EXT_DMA_STREAM, DISABLE); 
    NVIC_DisableIRQ( AUDIO_I2S_EXT_DMA_IRQ );
}

////////////////////////////////////////////////////////////////////////////////

static void audio_driver_global_init( void )
{
	is_init = FALSE;
	pa_wave_dev[AUDIO_DEVICE_INPUT_ID].device_index = AUDIO_DEVICE_EMPTY;
	pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].device_index = AUDIO_DEVICE_EMPTY;
}

static void audio_driver_process( void )
{
	if( pa_wave_dev[AUDIO_DEVICE_INPUT_ID].device_index == AUDIO_DEVICE_INPUT_ID )
	{
		if( pa_wave_dev[AUDIO_DEVICE_INPUT_ID].p_audio_wave != NULL )
		{
			pa_wave_dev[AUDIO_DEVICE_INPUT_ID].audio_callback( pa_wave_dev[AUDIO_DEVICE_INPUT_ID].p_audio_wave,
															   NULL,
															   0,
															   NULL,
															   0,
															   pa_wave_dev[AUDIO_DEVICE_INPUT_ID].audio_data );

			pa_wave_dev[AUDIO_DEVICE_INPUT_ID].p_audio_wave = NULL;
		}
	}
	if( pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].device_index == AUDIO_DEVICE_OUTPUT_ID )
	{
		if( pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].p_audio_wave != NULL )
		{
			pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].audio_callback( NULL,
				    										    pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].p_audio_wave,
															    0,
															    NULL,
															    0,
															    pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].audio_data );

			pa_wave_dev[AUDIO_DEVICE_OUTPUT_ID].p_audio_wave = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

#if 0
PaHostApiIndex Pa_GetHostApiCount( void )
{
    return (PaHostApiIndex)0;
}

PaHostApiIndex Pa_GetDefaultHostApi( void )
{
    return (PaHostApiIndex)0;
}

const PaHostApiInfo * Pa_GetHostApiInfo( PaHostApiIndex hostApi )
{
    return NULL;
}

PaHostApiIndex Pa_HostApiTypeIdToHostApiIndex( PaHostApiTypeId type )
{
    return (PaHostApiIndex)0;
}

PaDeviceIndex Pa_HostApiDeviceIndexToDeviceIndex( PaHostApiIndex hostApi, int hostApiDeviceIndex )
{
    return (PaDeviceIndex)0;
}

const PaHostErrorInfo* Pa_GetLastHostErrorInfo( void )
{
    return NULL;
}

PaError Pa_IsFormatSupported( const PaStreamParameters *inputParameters,
                              const PaStreamParameters *outputParameters,
                              double sampleRate )
{
    return paNoError;
}

#endif
// AUDIO_DEVICE_COUNT

PaError Pa_Initialize( void )
{
    return paNoError;
}

PaDeviceIndex Pa_GetDeviceCount( void )
{
    return AUDIO_DEVICE_COUNT;
}

PaDeviceIndex Pa_GetDefaultOutputDevice( void )
{
    return (PaDeviceIndex)AUDIO_DEVICE_OUTPUT_ID;
}

PaDeviceIndex Pa_GetDefaultInputDevice( void )
{
    return (PaDeviceIndex)AUDIO_DEVICE_INPUT_ID;
}

const PaDeviceInfo* Pa_GetDeviceInfo( PaDeviceIndex device )
{
    return &pa_device_info;
}

PaError Pa_OpenStream( PaStream** stream,
                       const PaStreamParameters *inputParameters,
                       const PaStreamParameters *outputParameters,
                       double sampleRate,
                       unsigned long framesPerBuffer,
                       PaStreamFlags streamFlags,
                       PaStreamCallback *streamCallback,
                       void *userData )
{
    uint32_t index;
    pa_wave_dev_t * p_pa_wave_dev;

    if( inputParameters != NULL )
    {
        // this is input
        p_pa_wave_dev = &pa_wave_dev[inputParameters->device];
        memcpy( &p_pa_wave_dev->streamParameters, inputParameters, sizeof( PaStreamParameters ) );
    }
    else if( outputParameters != NULL )
    {
        // this is output
        p_pa_wave_dev = &pa_wave_dev[inputParameters->device];
        memcpy( &p_pa_wave_dev->streamParameters, outputParameters, sizeof( PaStreamParameters ) );
    }
    else
    {
        return paInvalidDevice;
    }

    if( is_init == FALSE )
    {
    	audio_hw_driver_init( framesPerBuffer );
    	is_init = TRUE;
    }

    p_pa_wave_dev->sample_rate = framesPerBuffer;
    p_pa_wave_dev->audio_data = userData;
    p_pa_wave_dev->audio_callback = streamCallback;
    p_pa_wave_dev->device_index = inputParameters->device;
    *stream = ( PaStream * )p_pa_wave_dev;

    return paNoError;
}

PaError Pa_StartStream( PaStream *stream )
{
    pa_wave_dev_t * p_pa_wave_dev = ( pa_wave_dev_t * )stream;

    if( p_pa_wave_dev->device_index == AUDIO_DEVICE_OUTPUT_ID )
    {
    	p_pa_wave_dev->p_audio_wave = NULL;
    	audio_dma_out_start();
    }
    else if( p_pa_wave_dev->device_index == AUDIO_DEVICE_INPUT_ID )
    {
    	p_pa_wave_dev->p_audio_wave = NULL;
    	audio_dma_in_start();
    }
    else
    {
    	return paInvalidDevice;
    }

	return paNoError;
}

PaError Pa_CloseStream( PaStream *stream )
{
	return paNoError;
}

PaError Pa_StopStream( PaStream *stream )
{
    pa_wave_dev_t * p_pa_wave_dev = ( pa_wave_dev_t * )stream;

    if( p_pa_wave_dev->device_index == AUDIO_DEVICE_OUTPUT_ID )
    {
    	audio_dma_out_stop();
    }
    else if( p_pa_wave_dev->device_index == AUDIO_DEVICE_INPUT_ID )
    {
    	audio_dma_in_stop();
    }
    else
    {
    	return paInvalidDevice;
    }

    return paNoError;
}

PaError Pa_AbortStream( PaStream *stream )
{
	return paNoError;
}

////////////////////////////////////////////////////////////////////////////////

DECLARE_INIT_POWERUP_SECTION( audio_driver_global_init );
DECLARE_PROCESS_SECTION( audio_driver_process );


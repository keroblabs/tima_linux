#include "SDL_internal.h"

#include "types.h"
#include "device.h"
#include "system.h"
#include "lcd.h"
#include "pipe.h"

///////////////////////////////////////////////////////////////

#define AUDIO_INDEX_OUTPUT              0
#define AUDIO_INDEX_INPUT               1

#define AUDIO_TEMP_BUFFER_COUNT         4

#define AUDIO_CHANNELS                  2
#define AUDIO_SAMPLE_COUNTER            160

///////////////////////////////////////////////////////////////

typedef struct WaveDeviceDataT
{
    int device;
    uint32_t sample_rate;
    pipe_data_t pipe;
    int16_t buffer[AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS * AUDIO_TEMP_BUFFER_COUNT];
    uint32_t pointer;
    
} audio_dev_t;

///////////////////////////////////////////////////////////////

static audio_dev_t audio_devs[2];
static bool_t first_init;

///////////////////////////////////////////////////////////////

static void input_audio_callback( void * userData, Uint8 * stream, int len )
{
    audio_dev_t * audio_dev = ( audio_dev_t * )userData; //  is the used defined data
    uint16_t size = AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS * sizeof( int16_t );
    
    // SDL_MixAudio( ( Uint8 * )( &audio_dev->buffer[audio_dev->pointer] ), stream, len, SDL_MIX_MAXVOLUME );
    memcpy( &audio_dev->buffer[audio_dev->pointer], stream, size );
    pipe_write( &audio_dev->pipe, ( uint8_t * )&audio_dev->buffer[ audio_dev->pointer ], size );
    
    //audio_dev->buffer[ audio_dev->pointer ] = 1;
    //audio_dev->buffer[ audio_dev->pointer+1 ] = 1;

    audio_dev->pointer += AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS;
    if( audio_dev->pointer >= ( AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS * AUDIO_TEMP_BUFFER_COUNT ) )
    {
        audio_dev->pointer = 0;
    }
}

static void output_audio_callback( void * userData, Uint8 * stream, int len )
{
    audio_dev_t * audio_dev = ( audio_dev_t * )userData; //  is the used defined data
    uint16_t size = AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS * sizeof( int16_t );
    
    memcpy( stream, &audio_dev->buffer[audio_dev->pointer], size );

    audio_dev->pointer += AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS;
    if( audio_dev->pointer >= ( AUDIO_SAMPLE_COUNTER * AUDIO_CHANNELS * AUDIO_TEMP_BUFFER_COUNT ) )
    {
        audio_dev->pointer = 0;
    }
    
    pipe_write( &audio_dev->pipe, ( uint8_t * )&audio_dev->buffer[ audio_dev->pointer ], size );
}

static int hw_init_audio_ex( int rec, audio_dev_t * audio_dev )
{
    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;
    
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0)
    {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
        {
            return 0;
        }
    }
    
    pipe_init( &audio_dev->pipe, rec ? "PIPE_AUDIO_REC" : "PIPE_AUDIO_PLAY", AUDIO_TEMP_BUFFER_COUNT );
    memset( &audio_dev->buffer, 0x00, sizeof( audio_dev->buffer ) );
    audio_dev->pointer = 0;
    
    memset( &want, 0, sizeof(want));
    want.freq = audio_dev->sample_rate;
    want.format = AUDIO_S16;
    want.channels = AUDIO_CHANNELS;
    want.samples = AUDIO_SAMPLE_COUNTER;
    want.callback = rec ? input_audio_callback : output_audio_callback;
    want.userdata = audio_dev;
    
    dev = SDL_OpenAudioDevice(SDL_GetAudioDeviceName( rec ? 0 : 1, rec ), rec, &want, &have, 0); // SDL_GetAudioDeviceName( rec ? 0 : 1, rec )
    if (dev == 0)
    {
        SDL_Log("Failed to open audio: %s", SDL_GetError());
    }
    else
    {
        if (have.format != want.format)
        {
            /* we let this one thing change. */
            SDL_Log("We didn't get Float32 audio format.");
        }
        
        SDL_PauseAudioDevice(dev, 0);
    }
    
    return (int)dev;
}

static void hw_close_audio( audio_dev_t * audio_dev )
{
    SDL_CloseAudioDevice( (SDL_AudioDeviceID)audio_dev->device );
}

///////////////////////////////////////////////////////////////

static void audio_driver_global_init( void )
{
    audio_devs[0].device = 0;
    audio_devs[1].device = 0;
    first_init = FALSE;
}

static void audio_driver_open( uint32_t index )
{
    if( audio_devs[index].device != 0 ) return;
    audio_devs[index].device = hw_init_audio_ex( index, &audio_devs[index] );
    
    if( index == AUDIO_INDEX_OUTPUT )
    {
        pipe_write( &audio_devs[AUDIO_INDEX_OUTPUT].pipe, ( uint8_t * )&audio_devs[AUDIO_INDEX_OUTPUT].buffer[0], 0 );
    }
}

static void audio_driver_close( uint32_t index )
{
    if( audio_devs[index].device == 0 ) return;
    hw_close_audio( &audio_devs[index] );
}

static int audio_driver_get_index( char * param )
{
    char temp_param[20];
    char * arg0, * arg1;
    uint8_t audio_mask;
    int index = -1;
    
    if( param[0] != '?' ) return -1;
    
    strncpy( temp_param, param, 19 );
    
    arg0 = &temp_param[1];
    arg1 = strchr( arg0, ',' ); if( arg1 == NULL ) return -1; *arg1 = 0; arg1++;
    
    audio_mask = 0;
    
    if( !strcmp( arg1, "out" ) ) index = AUDIO_INDEX_OUTPUT;
    else if( !strcmp( arg1, "in" ) ) index = AUDIO_INDEX_INPUT;
    else return -1;
    
    audio_devs[index].sample_rate = atoi(arg0);
    //if( !strcmp( arg0, "8000" ) ) audio_devs[index].sample_rate = 8000;
    //else return -1;
    
    return index;
}

static bool_t audio_driver_validate( uint32_t index )
{
    if( index == 0 ) return TRUE;
    return FALSE;
}

static uint32_t audio_driver_io_ctrl( uint32_t index, uint32_t param, void * value )
{
    if( param == DEVICE_SET_RUNTIME_VALUE )
    {
        // set volume to the audio DAC, if there is any
    }
    
    return 0;
}

static pipe_data_t * audio_input_pipe( void )
{
    return &audio_devs[AUDIO_INDEX_INPUT].pipe;
}

static pipe_data_t * audio_output_pipe( void )
{
    return &audio_devs[AUDIO_INDEX_OUTPUT].pipe;
}

///////////////////////////////////////////////////////////////

static bool_t _in_use;

const static device_data_t sdl_audio_device_driver =
{
    "audio?",
    &_in_use,
    
    audio_driver_open,
    audio_driver_close,
    NULL,
    audio_driver_validate,
    audio_driver_get_index,
    audio_driver_io_ctrl,
    NULL,
    
    DEV_MODE_PIPE,
    
    audio_input_pipe,
    audio_output_pipe,
    
};

//DECLARE_DEVICE_SECTION(sdl_audio_device_driver);
//DECLARE_INIT_CRITICAL_SECTION(audio_driver_global_init);

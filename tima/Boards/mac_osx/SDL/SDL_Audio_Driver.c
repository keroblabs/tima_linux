#include "SDL_internal.h"

#include "types.h"
#include "device.h"
#include "system.h"
#include "lcd.h"
#include "pipe.h"
#include "debug.h"
#include "audio_driver.h"

///////////////////////////////////////////////////////////////

#if 1

///////////////////////////////////////////////////////////////

#define AUDIO_TEMP_BUFFER_COUNT         8

///////////////////////////////////////////////////////////////

typedef struct _audio_hw_dev_t
{
    SDL_AudioDeviceID device;
    uint32_t sample_counter;
    pipe_data_t pipe_tx;
    pipe_data_t pipe_rx;

} audio_hw_dev_t;

///////////////////////////////////////////////////////////////

static audio_hw_dev_t audio_hw_devs[2];

///////////////////////////////////////////////////////////////

static void input_audio_callback( void * userData, Uint8 * stream, int len )
{
    audio_hw_dev_t * audio_hw_dev = ( audio_hw_dev_t * )userData; //  is the used defined data
    uint16_t size                 = audio_hw_dev->sample_counter * AUDIO_CHANNELS * sizeof( int16_t );
    int16_t * rx_buffer           = ( int16_t * )pipe_read( &audio_hw_dev->pipe_tx, NULL );
    
    if( rx_buffer != NULL )
    {
        memcpy( rx_buffer, stream, size );
        pipe_write( &audio_hw_dev->pipe_rx, ( uint8_t * )rx_buffer, size );
    }
}

static void output_audio_callback( void * userData, Uint8 * stream, int len )
{
    audio_hw_dev_t * audio_hw_dev = ( audio_hw_dev_t * )userData; //  is the used defined data
    uint16_t size                 = audio_hw_dev->sample_counter * AUDIO_CHANNELS * sizeof( int16_t );
    int16_t * tx_buffer           = ( int16_t * )pipe_read( &audio_hw_dev->pipe_tx, NULL );
    
    if( tx_buffer != NULL )
    {
        memcpy( stream, tx_buffer, size );
        pipe_write( &audio_hw_dev->pipe_rx, ( uint8_t * )tx_buffer, size );
    }
    else
    {
        memset( stream, 0x00, size );
    }
}

void * hw_audio_init( int rec, uint32_t sample_rate, uint32_t sample_counter )
{
    SDL_AudioSpec want, have;
    
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0)
    {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
        {
            return NULL;
        }
    }
    
    audio_hw_dev_t * audio_hw_dev = &audio_hw_devs[rec];

    pipe_init( &audio_hw_dev->pipe_tx, rec ? "PIPE_AUDIO_REC_FREE"   : "PIPE_AUDIO_LOADED", AUDIO_TEMP_BUFFER_COUNT );
    pipe_init( &audio_hw_dev->pipe_rx, rec ? "PIPE_AUDIO_REC_LOADED" : "PIPE_AUDIO_FREE",   AUDIO_TEMP_BUFFER_COUNT );
    audio_hw_dev->sample_counter = sample_counter;
    
    memset( &want, 0, sizeof(want));
    want.freq = sample_rate;
    want.format = AUDIO_S16;
    want.channels = AUDIO_CHANNELS;
    want.samples = sample_counter;
    want.callback = rec ? input_audio_callback : output_audio_callback;
    want.userdata = audio_hw_dev;
    
    DEBUG_PRINTK( "Total: %d (%s)\n", SDL_GetNumAudioDevices( rec ), rec ? "rec" : "play" );
    for( int i = 0; i < SDL_GetNumAudioDevices( rec ); i++ )
    {
        DEBUG_PRINTK( "%d: %s\n", i, SDL_GetAudioDeviceName( i, rec ) );
    }
    
    audio_hw_dev->device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName( rec ? 0 : 1, rec ), rec, &want, &have, 0);
    if (audio_hw_dev->device == 0)
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
        
        SDL_PauseAudioDevice(audio_hw_dev->device, 0);
    }
    
    return audio_hw_dev;
}

void hw_audio_close( void * p_data )
{
    audio_hw_dev_t * audio_hw_dev = ( audio_hw_dev_t * )p_data;
    SDL_CloseAudioDevice( (SDL_AudioDeviceID)audio_hw_dev->device );
}

void hw_audio_global_init( void )
{
}

uint8_t hw_audio_buffer_count( void )
{
    return AUDIO_TEMP_BUFFER_COUNT;
}

pipe_data_t * hw_audio_input_pipe( void * p_data )
{
    audio_hw_dev_t * audio_hw_dev = ( audio_hw_dev_t * )p_data;
    return &audio_hw_dev->pipe_rx;
}

pipe_data_t * hw_audio_output_pipe( void * p_data )
{
    audio_hw_dev_t * audio_hw_dev = ( audio_hw_dev_t * )p_data;
    return &audio_hw_dev->pipe_tx;
}

#endif

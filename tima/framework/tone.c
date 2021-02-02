#include "tone.h"
#include "tima_libc.h"

void toneInit( tone_t * tone, uint32_t freq, uint32_t sample_rate )
{
	tone->freq = freq;
	tone->sample_rate = sample_rate;
	tone->step = 0;
	tone->gain_N = 1;
	tone->gain_D = 2;

	tone->koeff = tone->freq * SINE_TABLE_SIZE / tone->sample_rate;
}

void toneSetFrequency( tone_t * tone, uint32_t freq )
{
	tone->freq = freq;
	tone->koeff = tone->freq * SINE_TABLE_SIZE / tone->sample_rate;
}

void toneSetGain( tone_t * tone, int32_t gain_N, int32_t gain_D )
{
	tone->gain_N = gain_N;
	tone->gain_D = gain_D;
}

void toneGenerate( tone_t * tone, short * data, int len )
{
	int i;

	for( i = 0; i < len; i++ )
	{
		data[i] = toneSample( tone );
	}
}

void toneGenerate90( tone_t * tone, short * data, int len )
{
	int i;

	for( i = 0; i < len; i++ )
	{
		data[i] = toneSample90( tone );
	}
}

int16_t toneSample( tone_t * tone )
{
	int16_t sample;

	sample = ( short )sin_table( tone->koeff * tone->step );
	sample = ( short )( ( sample * tone->gain_N ) / tone->gain_D );
	tone->step++;

	return sample;
}

int16_t toneSample90( tone_t * tone )
{
	int16_t sample;

	sample = ( short )cos_table( tone->koeff * tone->step );
	sample = ( short )( ( sample * tone->gain_N ) / tone->gain_D );
	tone->step++;

	return sample;
}


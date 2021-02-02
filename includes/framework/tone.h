#ifndef _TONE_H_
#define _TONE_H_

#include "types.h"

#define PI				3.14159265358979323844

typedef struct _tone_t_
{
	uint32_t sample_rate;
	uint32_t freq;
	
	int32_t gain_N;
	int32_t gain_D;

	int32_t koeff;
	int step;

} tone_t;

void toneInit( tone_t * tone, uint32_t freq, uint32_t sample_rate );
void toneSetGain( tone_t * tone, int32_t gain_N, int32_t gain_D );
void toneSetFrequency( tone_t * tone, uint32_t freq );

void toneGenerate( tone_t * tone, short * data, int len );
void toneGenerate90( tone_t * tone, short * data, int len );

int16_t toneSample( tone_t * tone );
int16_t toneSample90( tone_t * tone );

#endif // _TONE_H_

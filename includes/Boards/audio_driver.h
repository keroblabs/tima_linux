#ifndef BOARDS_COMMON_AUDIO_HW_API_H_
#define BOARDS_COMMON_AUDIO_HW_API_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

#define AUDIO_INDEX_OUTPUT              0
#define AUDIO_INDEX_INPUT               1

#define AUDIO_CHANNELS                  2

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void * hw_audio_init( int rec, uint32_t sample_rate, uint32_t sample_counter );
void hw_audio_close( void * p_data );

void hw_audio_global_init( void );

uint8_t hw_audio_buffer_count( void );

pipe_data_t * hw_audio_input_pipe( void * p_data );
pipe_data_t * hw_audio_output_pipe( void * p_data );

////////////////////////////////////////////////////////////////////

#endif /* BOARDS_COMMON_AUDIO_HW_API_H_ */

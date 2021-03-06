#include "frame_utils.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

uint16_t frame_utils_get_frame_control( const uint8_t * frame )
{
    return &((uint16_t *)frame);
}

uint8_t frame_utils_get_sequence_number( const uint8_t * frame )
{
    return &((int8_t *)&frame[2]);
}


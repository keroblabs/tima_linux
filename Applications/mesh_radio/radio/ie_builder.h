#ifndef RADIO_IE_BUILDER_H_
#define RADIO_IE_BUILDER_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

uint16_t ie_build_channel_info(uint8_t * frame, uint16_t offset, uint8 channel_num);
uint16_t ie_build_node_name(uint8_t * frame, uint16_t offset, const char * name);
uint16_t ie_build_node_data(uint8_t * frame, uint16_t offset, uint16_t short_address, uint64_t long_address, const char * name);

#endif /* RADIO_IE_BUILDER_H_ */

#include "ie_builder.h"

////////////////////////////////////////////////////////////////////

typedef enum
{
    Ie_Channel_Num,
    Ie_Node_Name,
    Ie_Node_Destination,
    Ie_Node_Associated,
    Ie_MAX
} ie_id_t;

////////////////////////////////////////////////////////////////////

typedef struct ie_header_t_
{
    ie_id_t id;
    uint8_t len;
} ie_header_t;

typedef struct ie_channel_num_t_
{
    ie_header_t header;
    uint8_t     channel;
} ie_channel_num_t;

typedef struct ie_node_name_t_
{
    ie_header_t header;
    uint8_t     name[];
} ie_node_name_t;

typedef struct ie_node_data_t_
{
    ie_header_t header;
    uint64_t    address;
    uint8_t     name_size;
    uint8_t     name[];
} ie_node_data_t;

////////////////////////////////////////////////////////////////////

uint16_t ie_build_channel_info(uint8_t * frame, uint16_t offset, uint8 channel_num)
{
    uint16_t size = sizeof(ie_channel_num_t);
    if (frame)
    {
        ie_channel_num_t * ie = (ie_channel_num_t *)&frame[offset];
        ie->header.id         = Ie_Channel_Num;
        ie->header.len        = sizeof(ie_channel_num_t) - sizeof(ie_header_t);
        ie->channel           = channel_num;
    }

    return size;
}

uint16_t ie_build_node_name(uint8_t * frame, uint16_t offset, const char * name)
{
    uint16_t size = sizeof(ie_node_name_t) + strlen(name);
    if (frame)
    {
        ie_node_name_t * ie   = (ie_node_name_t *)&frame[offset];
        ie->header.id         = Ie_Node_Name;
        ie->header.len        = strlen(name);
        memcpy(ie->name, name, ie->header.len);
    }

    return size;
}

static uint16_t ie_build_node_data(uint8_t * frame, uint16_t offset, ie_id_t id, uint64_t address, const char * name)
{
    uint16_t size = sizeof(ie_node_data_t) + strlen(name);
    if (frame)
    {
        ie_node_data_t * ie = (ie_node_data_t *)&frame[offset];
        ie->header.id       = id;
        ie->header.len      = sizeof(ie_node_data_t) - sizeof(ie_header_t) + strlen(name);
        ie->address         = address;
        ie->name_size       = strlen(name);
        memcpy(ie->name, name, ie->name_size);
    }

    return size;
}

uint16_t ie_build_destination_node(uint8_t * frame, uint16_t offset, uint64_t address, const char * name)
{
    return ie_build_node_data(frame, offset, Ie_Node_Destination, address, name);
}

uint16_t ie_build_associated_node(uint8_t * frame, uint16_t offset, uint64_t address, const char * name)
{
    return ie_build_node_data(frame, offset, Ie_Node_Associated, address, name);
}

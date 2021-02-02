#include "frame_builder.h"

////////////////////////////////////////////////////////////////////

typedef enum command_frame_t_
{
    Command_Association_Request,
    Command_Association_Response,
    Command_Disassociation_Indication,
    Command_Probe_Request,
    Command_Probe_Response,
    Command_Action
} command_frame_t;

////////////////////////////////////////////////////////////////////

typedef struct frame_header_broadcast_t_
{
    uint16_t fc;
    uint8_t  seq_num;
    uint16_t pan_id;
    uint64_t sa;
} frame_header_broadcast_t;

typedef struct frame_header_unicast_t_
{
    uint16_t fc;
    uint8_t  seq_num;
    uint16_t pan_id;
    uint64_t da;
    uint64_t sa;
} frame_header_unicast_t;

typedef struct frame_beacon_t_
{
    frame_header_broadcast_t header;
    uint16_t                 super_frame;
    uint32_t                 timestamp;
    uint32_t                 interval;
    uint16_t                 capability;
    uint8_t                  ies[];
} frame_beacon_t;

////////////////////////////////////////////////////////////////////

void frame_builder_create_beacon(uint8_t * frame)
{
    uint16_t offset = 0;
}

#ifndef _DATATYPES_H__
#define _DATATYPES_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

//////////////////////////////////////////////////////////////////////////////////////

#define ENABLE_VIDEO
#define ENABLE_AUXILIAR_MEMORY
#define ENABLE_OWN_MAIN_MEMORY
#define ENABLE_OWN_AUX_MEMORY
#define DONT_ENABLE_CONTEXT
#define ENABLE_ACCEL_GRAPHICS
#define ENABLE_VIDEO_SHADOW
#define ENABLE_EMBEDDED_ASM

//////////////////////////////////////////////////////////////////////////////////////

typedef void ( *event_t )( void * data );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _DATATYPES_H__

#ifndef __DEBUG_INTERFACE_h__
#define __DEBUG_INTERFACE_h__

///////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////

#define DEBUG_ENABLED

///////////////////////////////////////////////////////////////

#if defined _USE_LINUX
static INLINE bool_t debug_read_input( char * out ) { return FALSE; }
#else
bool_t debug_read_input( char * out );
#endif

#ifndef _NO_DEBUG
#ifdef DEBUG_PRINTK
#undef DEBUG_PRINTK
#endif

#if defined _USE_LINUX || defined _USE_MACOS_SDL
#define DEBUG_PRINTK printf
#elif defined USE_SERIAL_PRINTF
#define DEBUG_PRINTK debug_printk
int debug_printk( const char *fmt, ... );
#endif

#endif

///////////////////////////////////////////////////////////////

#endif // __DEBUG_INTERFACE_h__

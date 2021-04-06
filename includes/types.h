#ifndef __TYPES_H__
#define __TYPES_H__

////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#if defined _USE_LINUX
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#endif

#ifdef TIMA_USE_CONFIG
#include "config_tima.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#ifndef __IO
#define __IO            volatile
#endif

#ifndef NULL
#define NULL            0
#endif

////////////////////////////////////////////////////////////////////////////////////////

#ifndef __stringify
#define __stringify_1(x...) #x
#define __stringify(x...) __stringify_1(x)
#endif

////////////////////////////////////////////////////////////////////////////////////////

// defined types
//#if 1 // defined USE_TIMA_TYPES //  1 // !defined ARM
#ifndef USE_LOCAL_TYPES
typedef unsigned char uint8_t;
typedef unsigned char uint8;
typedef signed char int8_t;
typedef signed char int8;

typedef unsigned short uint16_t;
typedef unsigned short uint16;
typedef signed short int16_t;
typedef signed short int16;

#if !defined ARM
typedef unsigned int uint32_t;
#endif

typedef unsigned int uint32;

#if !defined ARM
typedef signed int int32_t;
#endif

typedef signed int int32;

#if !defined __x86_64__ 
typedef unsigned long long uint64_t;
typedef unsigned long long uint64;
typedef long long int64_t;
typedef long long int64;
#endif
typedef uint32_t  u32_t;
typedef int32_t   s32_t;
typedef uint16_t  u16_t;
typedef int16_t   s16_t;
typedef uint8_t   u08_t;
typedef int8_t    s08_t;
#endif

typedef unsigned char   bool_t;
typedef void *          handler_t;

#if defined WIN32

#include <windows.h>
#include <WindowsX.h>
/*
typedef char 		    INT8; 		// 8 bits
typedef short		    INT16;		// 16 bits
typedef unsigned char   BYTE;		// 8 bits
typedef unsigned short  WORD;		// 16 bits
typedef unsigned int    DWORD;		// 32 bits

typedef unsigned char   BOOL;
*/

#endif

////////////////////////////////////////////////////////////////////////////////////////

void _cpu_disable_irq( void );
void _cpu_enable_irq( void );

typedef void * HANDLE;

typedef void ( *ptr_module_t )( void );
typedef void ( *ptr_event_t )( void * sender, void * data );
typedef void ( *ptr_print_t )( const char *fmt, ... );

#if defined __GNUC__
#define NAKED         	__attribute__ (( naked ))
#define WEAK 			__attribute__ (( weak ))
#define INLINE			inline
#else
#define NAKED         	
#define WEAK 			
#define INLINE			__inline
#endif

#define NEG_U32			((uint32_t)-1)

////////////////////////////////////////////////////////////////////////////////////////

void * zmmalloc( size_t size, const char * file, int line );
void * mmalloc( size_t size, const char * file, int line );
void mfree( void * p, const char * file, int line  );

uint32_t mm_used( void );
void mm_init( void );

#define ZMMALLOC(s)        zmmalloc(s, __FILE__, __LINE__)
#define MMALLOC(s)         mmalloc(s, __FILE__, __LINE__)
#define MFREE(p)           mfree(p, __FILE__, __LINE__)

////////////////////////////////////////////////////////////////////////////////////////

#ifdef ABS
#undef ABS
#endif

#define ABS(a)				( ( ( a ) < 0 ) ? 0 - ( a ) : ( a ) )

#define SIZE_OF_ARRAY(a)  (sizeof(a)/sizeof(a[0]))

#ifdef MIN
#undef MIN
#endif

#define MIN(a,b)            ( ( ( a ) > ( b ) ? ( b ) : ( a ) ) )

#ifdef MAX
#undef MAX
#endif

#define MAX(a,b)            ( ( ( a ) > ( b ) ? ( a ) : ( b ) ) )

////////////////////////////////////////////////////////////////////////////////////////

#ifdef TIMA_OS
#ifdef USE_MULTITHREAD
#define SYSTEM_EVENTS() thread_yield()
#else
#define SYSTEM_EVENTS() system_Events()
#endif
#else
#define SYSTEM_EVENTS()
#endif

////////////////////////////////////////////////////////////////////////////////////////

#define APP_RGB(r,g,b) ( ( pixel_t )( ( ( 0xFF ) << 24 ) | ( ( r ) << 16 ) | ( ( g ) << 8 ) | ( ( ( b ) << 0 ) ) ) )

#ifdef _USE_LINUX
#define DEBUG_PRINTK		printf
#else
#define DEBUG_PRINTK(...)
#endif

#if defined USE_MULTITHREAD
//extern						cpu_api_t * CPU_driver;
#define DI					CPU_driver->disable_irq
#define EI					CPU_driver->enable_irq
#else
#define DI					_cpu_disable_irq
#define EI					_cpu_enable_irq
#endif

////////////////////////////////////////////////////////////////////////////////////////

#endif // __TYPES_H__


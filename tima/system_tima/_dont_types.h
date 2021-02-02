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

// defined types
#if defined USE_TIMA_TYPES //  1 // !defined ARM
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

void * sys_malloc( uint32_t size );
void sys_free( void * ptr );

#define MMALLOC         sys_malloc
#define MFREE           sys_free

////////////////////////////////////////////////////////////////////////////////////////

#ifdef ABS
#undef ABS
#endif

#define ABS(a)				( ( ( a ) < 0 ) ? 0 - ( a ) : ( a ) )

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

#define APP_RGB(r,g,b) ( ( uint16_t )( ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( ( ( b & 0xF8 ) >> 3 ) ) ) )

#define DEBUG_PRINTK(...)

#if defined USE_MULTITHREAD
//extern						cpu_api_t * CPU_driver;
#define DI					CPU_driver->disable_irq
#define EI					CPU_driver->enable_irq
#else
#define DI					_cpu_disable_irq
#define EI					_cpu_enable_irq
#endif

void CPU_pio_reset( bool_t state );

////////////////////////////////////////////////////////////////////////////////////////

void _cpu_pio( bool_t state );

////////////////////////////////////////////////////////////////////////////////////////

#endif // __TYPES_H__


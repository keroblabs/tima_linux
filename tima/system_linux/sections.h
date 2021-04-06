#ifndef tima_system_sections_h
#define tima_system_sections_h

//////////////////////////////////////////////////////////////////////////////

#include "system.h"

//////////////////////////////////////////////////////////////////////////////

#ifdef USE_SECTIONS
extern volatile uint32_t            __list_start;
extern volatile uint32_t            __list_end;
#else
extern volatile void *              _list_list_[];
extern volatile uint32_t            _list_ptr_;
#define __list_start                (_list_list_[0])
#define __list_end                  (_list_list_[_list_ptr_])
#endif

#define LIST_SECTION                 __attribute__ ((section(".list_section")))
#define _list_section                ( void * )&__list_start, ( void * )&__list_end

//////////////////////////////////////////////////////////////////////////////

typedef struct _data_section_t
{
    uint32_t type;
    void *handler;
    
} data_section_t;

//////////////////////////////////////////////////////////////////////////////

#if defined _MSC_VER
#define CCALL __cdecl
#pragma section(".CRT$XCU",read)
#define INITIALIZER2(f) \
                                static void __cdecl f(void); \
                                __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
                                static void __cdecl f(void)
#endif

//////////////////////////////////////////////////////////////////////////////

#ifdef USE_SECTIONS
#define DECLARE_ENTRY_SECTION(a,b,c)    b const ptr_module_t * c##a = ( const ptr_module_t * )&a;
#elif defined __GNUC__
#define DECLARE_ENTRY_SECTION(a,b,c)    static void __attribute__((constructor)) c##a(void) { c##list_[c##ptr_++]=(void *)&a; }
#elif defined _MSC_VER
#define DECLARE_ENTRY_SECTION(a,b,c)    INITIALIZER2( c##a ) { c##list_[c##ptr_++]=(void *)&a; }
#else
#error "unknown compiler type"
#endif

//////////////////////////////////////////////////////////////////////////////

#define SYSTEM_SECTION_DATA( handler, type )        const static data_section_t __data_##handler = { type, ( void * )&handler }; \
                                                        DECLARE_ENTRY_SECTION( __data_##handler, LIST_SECTION, _list_ )

#define SYSTEM_SECTION_CALL( handler, type )        const static data_section_t __call_##handler = { type, ( void * )&handler }; \
                                                        DECLARE_ENTRY_SECTION( __call_##handler, LIST_SECTION, _list_ )

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

#endif /* tima_system_sections_h */

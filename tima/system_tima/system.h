#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//////////////////////////////////////////////////////////////////////////////

#include "types.h"

#include "heap.h"
#include "mass_mal.h"
#include "device.h"
#include "t_threads.h"

#include "lcd.h"
#include "cpu_driver.h"

////////////////////////////////////////////////////////////////////////////////

#if !defined USE_SECTIONS
extern volatile void *      _list_list_[];
extern volatile uint32_t    _list_ptr_;
#endif

//////////////////////////////////////////////////////////////////////////////

#if defined _MSC_VER
#define CCALL __cdecl
#pragma section(".CRT$XCU",read)
#define INITIALIZER2(f) \
static void __cdecl f(void); \
__declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
static void __cdecl f(void)
#endif

//////////////////////////////////////////////////////////////////////////////////////

// type, api, name, asc name
#define SYSTEM_DRIVER_DEFINE(t,a,n,p,i)     static uint16_t _##n##_get_api( uint32_t index, t ** api, uint16_t size ) { \
												if( api != NULL ) *api = ( t * )&a;                                     \
                                                return sizeof( uint32_t );  }                                           \
                                            static uint32_t _##n##_get_api2( uint32_t ii, uint32_t pr, void * data ) {  \
												t ** p_api = ( t ** )data;												\
                                                if( pr == DEVICE_GET_API ) *p_api = ( t * )&a;	                        \
                                                return 0;                   }                                           \
                                            static bool_t _device_in_use = FALSE;                                       \
                                            const static device_data_t n##_device = {                                   \
                                                p, &_device_in_use, i, NULL, NULL, NULL, NULL, _##n##_get_api2,         \
                                                NULL, DEV_MODE_CHANNEL, _##n##_get_api, NULL };                         \
                                            DECLARE_DEVICE_SECTION( n##_device )

//////////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_DRIVER_VALIDATE(t,a,n,p,i,v) static uint16_t _##n##_get_api( uint32_t index, t ** api, uint16_t size ) {        \
												if( api != NULL ) *api = ( t * )&a;                                     \
                                                return sizeof( uint32_t );  }                                           \
                                            static uint32_t _##n##_get_api2( uint32_t index, uint32_t param, void * data ) {   \
												t * p_api = ( t * )data;												\
                                                if( param == DEVICE_GET_API ) p_api = ( t * )&a;			            \
                                                return 0;                   }                                           \
                                            static bool_t _device_in_use = FALSE;                                       \
                                            const static device_data_t n##_device = {                                   \
                                                p, &_device_in_use, i, NULL, NULL, v, NULL, _##n##_get_api2,            \
                                                NULL, DEV_MODE_CHANNEL, _##n##_get_api, NULL };                         \
                                            DECLARE_DEVICE_SECTION( n##_device )

//////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_SECTIONS
#define DECLARE_ENTRY_SECTION(a,b,c)    b const ptr_module_t * c##a = ( const ptr_module_t * )&a;
#elif defined __GNUC__
#define DECLARE_ENTRY_SECTION(a,b,c)    static void __attribute__((constructor)) c##a(void) { c##list_[c##ptr_++]=(void *)&a; }
#elif defined _MSC_VER
#define DECLARE_ENTRY_SECTION(a,b,c)	INITIALIZER2( c##a ) { c##list_[c##ptr_++]=(void *)&a; }
#else
#error "unknown compiler type"
#endif

//////////////////////////////////////////////////////////////////////////////

#ifdef USE_SECTIONS
extern volatile uint32_t 		    __list_start;
extern volatile uint32_t 		    __list_end;
#else
#define __list_start                (_list_list_[0])
#define __list_end                  (_list_list_[_list_ptr_])
#endif

#define LIST_SECTION 		    	__attribute__ ((section(".list_section")))
#define _list_section		    	( void * )&__list_start, ( void * )&__list_end

//////////////////////////////////////////////////////////////////////////////

enum
{
	SYSTEM_INIT_POWERUP,
	SYSTEM_INIT_CRITICAL,
	SYSTEM_INIT_DEBUG,
	SYSTEM_INIT_DEVICE,
	SYSTEM_INIT_MODULE,
	SYSTEM_INIT_APPLICATION,

	SYSTEM_START_MAIN_APPLICATION,
	SYSTEM_START_SUB_APPLICATION,

	SYSTEM_RUN_PROCESS,

	SYSTEM_RUN_POWERDOWN_CRITICAL,
	SYSTEM_RUN_POWERDOWN_DEVICE,
	SYSTEM_RUN_POWERDOWN_MODULE,
	SYSTEM_RUN_POWERDOWN_APPLICATION,

	SYSTEM_DEVICE_DATA,
	SYSTEM_CUSTOM_DEVICE,
	SYSTEM_STORAGE_DEVICE,

	SYSTEM_LIST_SECTION = 0x50
};

typedef struct _data_section_t
{
	uint32_t type;
	void *handler;

} data_section_t;

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_SECTION_DATA( handler, type )		const static data_section_t __data_##handler = { type, ( void * )handler }; \
															DECLARE_ENTRY_SECTION( __data_##handler, LIST_SECTION, _list_ )

#define SYSTEM_SECTION_PTR( handler, type )		    const static data_section_t __data_##handler = { type, ( void * )&handler }; \
                                                            DECLARE_ENTRY_SECTION( __data_##handler, LIST_SECTION, _list_ )

#define SYSTEM_SECTION_CALL( handler, type )		const static data_section_t __call_##handler = { type, ( void * )&handler }; \
                                                            DECLARE_ENTRY_SECTION( __call_##handler, LIST_SECTION, _list_ )

#define SYSTEM_SECTION_LIST( data, type )			const static data_section_t __list_##data = { type+SYSTEM_LIST_SECTION, ( void * )&data }; \
															DECLARE_ENTRY_SECTION( __list_##data, LIST_SECTION, _list_ )

////////////////////////////////////////////////////////////////////////////////

#define DECLARE_INIT_POWERUP_SECTION(a)         	SYSTEM_SECTION_CALL( a, SYSTEM_INIT_POWERUP  	)
#define DECLARE_INIT_CRITICAL_SECTION(a)         	SYSTEM_SECTION_CALL( a, SYSTEM_INIT_CRITICAL 	)
#define DECLARE_INIT_DEBUG_SECTION(a)         		SYSTEM_SECTION_CALL( a, SYSTEM_INIT_DEBUG    	)

#define DECLARE_INIT_DEVICE_SECTION(a)         		SYSTEM_SECTION_CALL( a, SYSTEM_INIT_DEVICE   	)
#define DECLARE_INIT_MODULE_SECTION(a)         		SYSTEM_SECTION_CALL( a, SYSTEM_INIT_MODULE   	)
#define DECLARE_INIT_APPLICATION_SECTION(a)         SYSTEM_SECTION_CALL( a, SYSTEM_INIT_APPLICATION )

#define DECLARE_APPLICATION_SECTION(a)  			SYSTEM_SECTION_CALL( a, SYSTEM_START_MAIN_APPLICATION  )
#define DECLARE_SUB_APPLICATION_SECTION(a)  		SYSTEM_SECTION_CALL( a, SYSTEM_START_SUB_APPLICATION   )

#define DECLARE_PROCESS_SECTION(a)      			SYSTEM_SECTION_CALL( a, SYSTEM_RUN_PROCESS  )

#define DECLARE_DEVICE_SECTION(a)       			SYSTEM_SECTION_PTR( a, SYSTEM_DEVICE_DATA  )
#define DECLARE_STORAGE_DEVICE_SECTION(a)       	SYSTEM_SECTION_PTR( a, SYSTEM_STORAGE_DEVICE  )
#define DECLARE_CUSTOM_DEVICE_SECTION(a)       		SYSTEM_SECTION_PTR( a, SYSTEM_CUSTOM_DEVICE  )

#define DECLARE_POWERDOWN_SECTION(a)                SYSTEM_SECTION_CALL( a, SYSTEM_RUN_POWERDOWN_APPLICATION )

////////////////////////////////////////////////////////////////////////////////

void system_Events( void );
void system_Startup( void );
void System_PowerDown( void );

bool_t system_syscall_entrypoint( uint32_t index );

void * system_Get_Item( uint32_t * start, uint32_t * end, uint32_t index );

void * system_List_Get_Item( uint8_t type, uint32_t index );

msd_driver_t * system_Get_Storage_Driver( uint32_t index );
device_data_t * system_Get_Device_Driver( uint32_t index );
void * system_Get_Custom_Driver( uint32_t index );

char * system_Get_Version( void );
uint16_t system_Get_Build_Time( void );
uint16_t system_Get_Build_Date( void );
        
uint32_t sys_heap_total( void );
uint32_t sys_heap_used( void );

void sys_heap_list( ptr_print_t dev );
void sys_heap_check( void );

//////////////////////////////////////////////////////////////////////////////

#endif // _SYSTEM_H_


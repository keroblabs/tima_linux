#ifndef t_threads_h
#define t_threads_h

////////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef void ( *tthread_handler_t )( void );
typedef void ( *tthread_handler_ex_t )( void * args );

////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_MUTEX_PROPERTY(name, type)               static type _value_##name;                                  \
                                                        static void * _mutex_##name;                                \
                                                        void _property_##name##_set( type value ) {                 \
                                                            tthread_mutex_lock( _mutex_##name );                    \
                                                            _value_##name = value;                                  \
                                                            tthread_mutex_unlock( _mutex_##name ); }                \
                                                        type _property_##name##_get( void ) {                       \
                                                            type value;                                             \
                                                            tthread_mutex_lock( _mutex_##name );                    \
                                                            value = _value_##name;                                  \
                                                            tthread_mutex_unlock( _mutex_##name );                  \
                                                            return value; }                                         \
                                                        void _property_##name##_init( type value ) {                \
                                                            _mutex_##name = tthread_mutex_init();                   \
                                                            _value_##name = value; }

#define EXPORT_PROPERTY(name)                           void _property_##name##_set( type value );                  \
                                                        type _property_##name##_get( void );

#define PROPERTY_GET(name)                              _property_##name##_get()
#define PROPERTY_SET(name, value)                       _property_##name##_set(value)
#define PROPERTY_INIT(name, value)                      _property_##name##_init(value)

////////////////////////////////////////////////////////////////////////////////////////

void * tthread_create( tthread_handler_t handler );
void * tthread_create_ex( tthread_handler_ex_t handler, void * args );

void * tthread_mutex_init( void );

void tthread_mutex_lock( void * p_mutex );
void tthread_mutex_unlock( void * p_mutex );

void tthread_sleep_ms( int timeInMs );
void tthread_sleep_secs( int timeInSecs );

void * tthread_condition_create( void );
void tthread_condition_wait( void * p_cond );
void tthread_condition_signal( void * p_cond );

void tthread_cancel( void * p_thread );
void tthread_wait_terminate( void * p_thread );

uint32_t mm_threads( void );

////////////////////////////////////////////////////////////////////////////////////////

#endif /* t_threads_h */

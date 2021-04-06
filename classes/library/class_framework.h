#ifndef TIMA_CLASSES_NEW_CLASSES_H_
#define TIMA_CLASSES_NEW_CLASSES_H_

////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

#define METHOD
#define CREATOR
#define DELETE
#define STATIC
#define CLASS(t)                struct t##_

#define CLASS_DATA              void * __api; \
                                delete_class_t __default_del; \
                                void

#define CLASS_DATA_VOID         void * __api; \
                                delete_class_t __default_del

#define NEW_CLASS(t)            ( t * )_instance_new_##t
#define NEW_CLASS_EX(t)         ( t * )_instance_new_##t##_ex

#define DELETE_CLASS(c)         do { if( c->__default_del != NULL ) c->__default_del();\
                                    MFREE(c); } while(0)

#define STATIC_METHOD(t,m)      ( ( api_##t * )_instance_static_##t##_method( api_##t##_class ) )->m

////////////////////////////////////////////////////////////////////

typedef void ( *delete_class_t )( void );
typedef void ( *delete_class_ex_t )( void * data );

////////////////////////////////////////////////////////////////////

int create_instance_class( void * list[], int size, int max );

////////////////////////////////////////////////////////////////////

#endif // TIMA_CLASSES_NEW_CLASSES_H_


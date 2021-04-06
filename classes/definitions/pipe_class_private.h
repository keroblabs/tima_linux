#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "pipe_class.h"
#include "sections.h"

////////////////////////////////////////////////////////////////////

#ifdef CREATE_CLASS
#undef CREATE_CLASS
#endif
#define CREATE_CLASS(t)        CREATE_CLASS_EX(t, api_##t##_class)

#ifdef CREATE_CLASS_EX
#undef CREATE_CLASS_EX
#endif
#define CREATE_CLASS_EX(t,api) \
    static api_##t _local_api_##t##_class; \
    static void class_##t##_global_init( void ) { \
    api = &_local_api_##t##_class; \
    api->creator = creator; \
    api->delete_pipe = delete_pipe; \
    api->get = get; \
    api->read = read; \
    api->wait_for_data = wait_for_data; \
    api->write = write; \
    api->send = send; \
    api->is_full = is_full; \
    api->is_empty = is_empty; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_PIPE_CLASS_PRIVATE_H

#ifndef _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_PRIVATE_H
#define _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_PRIVATE_H

////////////////////////////////////////////////////////////////////

#include "list_class.h"
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
    api->creator_list = creator_list; \
    api->delete_list = delete_list; \
    api->clear = clear; \
    api->insert_head = insert_head; \
    api->insert_tail = insert_tail; \
    api->remove_tail = remove_tail; \
    api->unlink_node = unlink_node; \
    api->remove_node = remove_node; \
    api->is_empty = is_empty; \
    api->get_head = get_head; \
    api->get_tail = get_tail; \
    api->get_next = get_next; \
    api->get_prev = get_prev; \
    api->size = size; \
    } SYSTEM_SECTION_CALL(class_##t##_global_init, SYSTEM_INIT_MODULE);

////////////////////////////////////////////////////////////////////

#endif // _USERS_MARCIOCHEROBIM_PROJECTS_GIT_DEV_TIMA_LINUX_CLASSES_FRAMEWORK_LIST_CLASS_PRIVATE_H

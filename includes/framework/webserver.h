#ifndef __webserver_h__
#define __webserver_h__

///////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////

enum
{
    FAIL_UNKNOWN_ERROR,
    FAIL_SERVER_NOT_READY,
    FAIL_FILE_NOT_FOUND,
    FAIL_PATH_NOT_FOUND,

    FAIL_INDEX_MAX
};

typedef struct _mime_list_t
{
    char * extension;
    char * mime_type;

} mime_list_t;

///////////////////////////////////////////////////////////////

extern const char * m_html_header;
extern const char * m_html_footer;

extern const char * m_mime_default;
extern const char * m_mime_html;
extern const char * m_mime_bmp;

extern const char * m_status_ok;
extern const char * m_status_not_found;

///////////////////////////////////////////////////////////////

void webserver_send_header( uint32_t resp_size, const char * status, const char * mime, void * p_ptr );
void webserver_send_fail_response( uint32_t resp_index, void * p_ptr );

bool_t webserver_send_file( char * path, const char * status, void * p_ptr );

void webserver_init( uint16_t port );
void webserver_process( void );

ptr_event_t webserver_set_handler( ptr_event_t new_event );

///////////////////////////////////////////////////////////////

#endif // __webserver_h__

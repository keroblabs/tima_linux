#ifndef _GENERATE_HTML_H_
#define _GENERATE_HTML_H_

////////////////////////////////////////////////////////////////////

#include "types.h"
#include "string_lib.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

void html_generate_header( string_t * response, const char * page_name );
void html_generate_title( string_t * response, const char * page_title );
void html_generate_box_header( string_t * response );
void html_generate_box_title( string_t * response, const char * box_title );
void html_generate_box_temperature( string_t * response, float temperature );
void html_generate_box_extra_info( string_t * response, const char * info );
void html_generate_box_image( string_t * response, const char * image_file );
void html_generate_button_header( string_t * response );
void html_generate_button( string_t * response, const char * link, const char * caption );
void html_generate_box_end( string_t * response );
void html_generate_footer( string_t * response );

void html_generate_box_header_title( string_t * response, const char * title );
void html_generate_box_title_end( string_t * response );

void html_generate_table_header( string_t * response );
void html_generate_table_content( string_t * response );
void html_generate_table_entry( string_t * response, const char * caption, const char * link );
void html_generate_table_end( string_t * response );
void html_generate_table_start_end( string_t * response, bool_t start );

////////////////////////////////////////////////////////////////////

#endif /* _GENERATE_HTML_H_ */

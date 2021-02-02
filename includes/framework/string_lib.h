#ifndef __string_lib_h__
#define __string_lib_h__

///////////////////////////////////////////////////////////////

#include "types.h"

///////////////////////////////////////////////////////////////

#define FOPEN_KEEP_FILENAME     TRUE
#define FOPEN_DESTROY_FILENAME  FALSE

///////////////////////////////////////////////////////////////

typedef struct _string_t_
{
	char * buffer;
	
	uint32_t size;
	// uint32_t curr_size;
	uint32_t step_size;

} string_t;

///////////////////////////////////////////////////////////////

typedef struct _file_string_t_
{
    FILE * fp;
    string_t * line;
    string_t * filename;
    
} file_string_t;

///////////////////////////////////////////////////////////////

string_t * string_create( void );
string_t * string_create_ex( const char * text );
string_t * string_create_size( uint32_t curr_size );
string_t * string_duplicate( string_t * input );

string_t * string_sprintf( const char *fmt, ... );
int string_append_sprintf( string_t * object, const char *fmt, ... );

void string_destroy( string_t * input );

uint32_t string_append_text( string_t * input, const char * text );
uint32_t string_append( string_t * input1, string_t * input2 );
uint32_t string_copy_text( string_t * input, const char * text );
uint32_t string_copy( string_t * input, string_t * input2 );
uint32_t string_insert_head( string_t * input, const char * text );
uint32_t string_right_justify( string_t * input, uint32_t len );

void string_replace_char ( string_t * input, char old_char, char new_char );

char * string_get_char_buffer( string_t * input );

string_t * string_get_substring( string_t * input, uint32_t start, uint32_t len );
string_t * string_parse( string_t * input, uint32_t * pos, char * delimiter );
string_t * string_extract( string_t * input, uint32_t * pos );

int string_locate_content( string_t * input, const char * content );
int string_locate_content_ex( string_t * input, uint32_t start_index, const char * content );
int string_compare( string_t * input1, string_t * input2 );
int string_length( string_t * input );

char string_char_at( string_t * input, uint32_t pos );

void string_clear( string_t * input );
void string_delete( string_t * object, uint32_t position, uint32_t len );
void string_trim( string_t * object );
void string_trail( string_t * object );

FILE * string_fopen( string_t * filename, const char * mode, bool_t is_keep );
string_t * string_file_line( FILE * fp );

///////////////////////////////////////////////////////////////

#endif // __string_lib_h__

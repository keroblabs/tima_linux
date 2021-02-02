#include "string_lib.h"

///////////////////////////////////////////////////////////////

#define STRING_SIZE_STEP		20
#define ROUNDUP_SIZE(a,b)		a + ( b->step_size - ( a % b->step_size ) )

///////////////////////////////////////////////////////////////

static string_t * _string_create_data( uint32_t buffer_size )
{
	string_t * ret;

	ret = ( string_t * )MMALLOC( sizeof( string_t ) );
	if( ret == NULL ) return NULL;

	memset( ret, 0x00, sizeof( string_t ) );

	if( ( buffer_size == 0 ) || ( buffer_size == NEG_U32 ) )
	{
		buffer_size = STRING_SIZE_STEP;
	}

	ret->step_size  = STRING_SIZE_STEP;
	ret->size = ROUNDUP_SIZE( buffer_size, ret );

	ret->buffer = ( char * )MMALLOC( ret->size );
	if( ret->buffer == NULL )
	{
		MFREE( ret );
		return NULL;
	}

	memset( ret->buffer, 0x00, ret->size );

	return ret;
}

static void _string_add_size( string_t * input, uint32_t add_size )
{
	char * temp_str;
	uint32_t new_size;

	new_size = add_size + (uint32_t)strlen( input->buffer );

	if( new_size > input->size )
	{
		new_size = ROUNDUP_SIZE( new_size, input );
		temp_str = ( char * )MMALLOC( new_size );
		if( temp_str == NULL ) return;
		memset( temp_str, 0x00, new_size );
		memcpy( temp_str, input->buffer, input->size );

		MFREE( input->buffer );
		input->buffer = temp_str;
		input->size = new_size;
	}
}

static void _string_update_size( string_t * input )
{
	uint32_t new_size;
	char * temp_str;

	new_size = ROUNDUP_SIZE( (uint32_t)strlen( input->buffer ), input );
	if( new_size != input->size )
	{
		temp_str = ( char * )MMALLOC( new_size );
		if( temp_str == NULL ) return;
		memset( temp_str, 0x00, new_size );
		strcpy( temp_str, input->buffer );

		MFREE( input->buffer );
		input->buffer = temp_str;
		input->size = new_size;
	}
}

///////////////////////////////////////////////////////////////

string_t * string_create( void )
{
	return _string_create_data( STRING_SIZE_STEP );
}

string_t * string_create_ex( const char * text )
{
	string_t * ret;

	ret = _string_create_data( (uint32_t)strlen( text ) + 1 );
	strcpy( ret->buffer, text );

	return ret;
}

string_t * string_duplicate( string_t * input )
{
    return (string_create_ex( string_get_char_buffer( input ) ) );
}

string_t * string_create_size( uint32_t curr_size )
{
	return _string_create_data( curr_size );
}

void string_destroy( string_t * input )
{
	if( input == NULL ) return;
	if( input->buffer != NULL ) MFREE( input->buffer );
	MFREE( input );
}

uint32_t string_copy_text( string_t * input, const char * text )
{
	_string_add_size( input, (uint32_t)strlen( text ) );
	strcpy( input->buffer, text );
	return (uint32_t)strlen( input->buffer );
}

uint32_t string_copy( string_t * input, string_t * input2 )
{
	_string_add_size( input, (uint32_t)strlen( input2->buffer ) );
	strcpy( input->buffer, input2->buffer );
	return (uint32_t)strlen( input->buffer );
}

uint32_t string_insert_head( string_t * input, const char * text )
{
    int add_size;
    int index;
    
    add_size = (int)strlen( text );
    _string_add_size( input, add_size );
    
    index = (int)strlen( input->buffer );
    while( index >= 0 )
    {
        input->buffer[index+add_size] = input->buffer[index];
        if( index < add_size )
        {
            input->buffer[index] = text[index];
        }
        index--;
    }
    
    return (uint32_t)strlen( input->buffer );
}

uint32_t string_right_justify( string_t * input, uint32_t len )
{
    string_t * ret = NULL;
    uint32_t white_len = len - string_length( input );

    ret = _string_create_data( white_len );
    memset( ret->buffer, 0x20, white_len );

    string_append( ret, input );

    MFREE( input->buffer );
    input->buffer = ret->buffer;
    MFREE( ret );

    return string_length( ret );
}

uint32_t string_append_text( string_t * input, const char * text )
{
	_string_add_size( input, (uint32_t)strlen( text ) + 2 );
	strcat( input->buffer, text );
    return (uint32_t)strlen( input->buffer );
}

uint32_t string_append( string_t * input1, string_t * input2 )
{
	return string_append_text( input1, input2->buffer );
}

void string_replace_char( string_t * input, char old_char, char new_char )
{
	uint32_t size = 0;
	uint32_t i;
	char * text;

	// get everything to determine new size
	text = ( char * )input->buffer;
	size = ( uint32_t )strlen( text );

	// process it
	for( i = 0; i < size; i++ )
	{
		if( text[i] == old_char ) text[i] = new_char;
	}    
}

char string_char_at( string_t * input, uint32_t pos )
{
	uint32_t size = 0;
	char * text;

	// get everything to determine new size
	text = ( char * )input->buffer;
	size = ( uint32_t )strlen( text );

    if( pos == NEG_U32 )
    {
        pos = size - 1;
    }
    
    return text[ pos ];
}

int string_compare( string_t * input1, string_t * input2 )
{
	return strcmp( input1->buffer, input2->buffer );
}

string_t * string_parse( string_t * input, uint32_t * pos, char * delimiter )
{
    string_t * ret = NULL;
    
    int index = string_locate_content_ex( input, *pos, delimiter );
    if( index != -1 )
    {
        ret = string_get_substring( input, *pos, index - *pos );
        *pos = index + ( uint32_t )strlen( delimiter );
    }
    else if( *pos < (uint32_t)strlen( input->buffer ) )
    {
        ret = string_get_substring( input, *pos, NEG_U32 );
    }
    
    return ret;
}

string_t * string_extract( string_t * input, uint32_t * pos )
{
    int start = -1;
    int end = -1;
    int len;

    for( ; *pos < strlen( input->buffer ); (*pos)++ )
    {
        if( input->buffer[*pos] > 0x20 )
        {
            start = *pos;
            break;
        }
    }

    if( start == -1 ) return NULL;

    for( ; *pos < strlen( input->buffer ); (*pos)++ )
    {
        if( input->buffer[*pos] <= 0x20 )
        {
            end = *pos - 1;
            break;
        }
    }

    if( end == -1 ) return NULL;

    len = ( end - start ) + 1;
    return string_get_substring( input, start, len );
}

int string_locate_content( string_t * input, const char * content )
{
	char * p_ptr;
	int ret;

	p_ptr = strstr( input->buffer, content );
	if( p_ptr == NULL ) return -1;

	ret = ( int )( p_ptr - input->buffer );

	return ret;
}

int string_locate_content_ex( string_t * input, uint32_t start_index, const char * content )
{
	char * p_ptr;
	int ret;

	if( start_index >= strlen( input->buffer ) ) return -1;
	p_ptr = strstr( &input->buffer[start_index], content );
	if( p_ptr == NULL ) return -1;

	ret = ( int )( p_ptr - input->buffer );

	return ret;
}

int string_length( string_t * input )
{
	return (int)strlen( input->buffer );
}

void string_clear( string_t * input )
{
	char * p_ptr;

	p_ptr = ( char * )MMALLOC( input->step_size );
	if( p_ptr != NULL )
	{
		if( input->buffer != NULL )
		{
			MFREE( input->buffer );
		}
		
		input->buffer = p_ptr;
		input->size = input->step_size;
	}

	memset( p_ptr, 0x00, input->step_size );

	input->buffer = ( char * )MMALLOC( input->size );
}

string_t * string_get_substring( string_t * input, uint32_t position, uint32_t len )
{
	uint32_t size = 0;
	string_t * new_object;

	// get everything to determine new size
	size = ( uint32_t )strlen( input->buffer );

	if( len == NEG_U32 ) len = size - position;

	// for exception
	if( ( position >= size ) || ( ( position+len ) > size ) )
	{
		return NULL;
	}

	new_object = string_create_size( len + 1 );

	// copy string
	strncpy( new_object->buffer, &input->buffer[position], len );

	return new_object;
}

void string_delete( string_t * object, uint32_t position, uint32_t len )
{
	uint32_t size = 0;
	char * text;

	// get everything to determine new size
	text = ( char * )( object->buffer );
	size = ( uint32_t )strlen( text );
    
    if( position == NEG_U32 ) position = size - 1;
    if( len == NEG_U32 ) len = size - position;

	// for exception
	if( ( position >= size ) || ( ( position+len ) > size ) )
	{
		//instance_error_string_out_of_bounds();
		return;
	}

	// copy string
	strcpy( &text[position], &text[position+len] );

	// resize
	_string_update_size( object );
}

char * string_get_char_buffer( string_t * input )
{
	return input->buffer;
}

void string_trim( string_t * object )
{
    char * text;
    char * text_out;
    uint32_t size = 0;
    uint32_t cnt;

    // get everything to determine new size
    text = ( char * )( object->buffer );
    size = ( uint32_t )strlen( text );

    for( cnt = 0; cnt < size; cnt++ )
    {
        if( text[cnt] > 0x20 )
        {
            text_out = ( char * )MMALLOC( size - cnt + 1 );
            if( text_out == NULL ) return;
            
            strcpy( text_out, &text[cnt] );
            MFREE( text );
            object->buffer = text_out;
            break;
        }
    }
}

void string_trail( string_t * object )
{
    char * text;
    uint32_t size = 0;
    
    // get everything to determine new size
    text = ( char * )( object->buffer );
    size = ( uint32_t )strlen( text );
    
    while( ( uint32_t )strlen( text ) > 0 )
    {
        if( text[ strlen( text ) - 1 ] > 0x20 ) break;
        text[ strlen( text ) - 1 ] = 0;
    }
    
    // resize
    _string_update_size( object );
}

#define VSF_PRINTF_BUF_SIZE 8192
static char vsf_printf_buf[VSF_PRINTF_BUF_SIZE];

string_t * string_sprintf( const char *fmt, ... )
{
    va_list args;
    int printed_len;

    /* Emit the output into the temporary buffer */
    va_start(args, fmt);
    printed_len = vsnprintf(vsf_printf_buf, VSF_PRINTF_BUF_SIZE, fmt, args);
    va_end(args);

    return string_create_ex( vsf_printf_buf );
}

int string_append_sprintf( string_t * object, const char *fmt, ... )
{
    va_list args;
    int printed_len;

    /* Emit the output into the temporary buffer */
    va_start(args, fmt);
    printed_len = vsnprintf(vsf_printf_buf, VSF_PRINTF_BUF_SIZE, fmt, args);
    va_end(args);

    string_append_text( object, vsf_printf_buf );
    return printed_len;
}

string_t * string_read_file( file_string_t * file_string )
{
    if( ( file_string == NULL ) || ( file_string->fp == NULL ) ) return NULL;
    if( fgets( vsf_printf_buf, VSF_PRINTF_BUF_SIZE-1, file_string->fp ) == NULL ) return NULL;
    
    if( file_string->line != NULL ) string_destroy( file_string->line );
    file_string->line = string_create_ex( vsf_printf_buf );
    return file_string->line;
}

FILE * string_fopen( string_t * filename, const char * mode, bool_t is_keep )
{
    FILE * fp = fopen( string_get_char_buffer( filename ), mode );
    if( is_keep == FALSE ) string_destroy( filename );
    return fp;
}

string_t * string_file_line( FILE * fp )
{
    if( fp == NULL ) return NULL;
    if( fgets( vsf_printf_buf, VSF_PRINTF_BUF_SIZE-1, fp ) == NULL ) return NULL;
    return string_create_ex( vsf_printf_buf );
}

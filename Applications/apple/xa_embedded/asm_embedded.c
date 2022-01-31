#include "datatypes.h"
#include "embedded.h"
#include "board.h"

//////////////////////////////////////////////////////////////////////////////////////

#define MAX_ASM_FILES		20
#define TEMP_BUFFER_SIZE	512

//////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	int pointer;
	const char * filename;

} source_entry_t;

//static int pointer;
char * filename;

static source_entry_t source_list[MAX_ASM_FILES];
static source_entry_t output_file;
static board_data_t * board;

static uint8_t temp_binary[TEMP_BUFFER_SIZE];
static int temp_index;

//////////////////////////////////////////////////////////////////////////////////////

void print_log(char *s)
{
	// print log (always defined, empty if not needed)
	//printf("%s",s);
	board->p_print(s);
}

int open_file( char * name )
{
	// open input source file
	int i;

	for( i = 0; i < MAX_ASM_FILES; i++ )
	{
		if( ( source_list[i].filename != NULL ) &&
			( strcmp( name, source_list[i].filename ) == 0 ) )
		{
			source_list[i].pointer = 0;
			if( board_disc_image_access( name, Disc_Mode_Size, 0, NULL, 0 ) == 0 ) return -1;
			return i;
		}
	}

	return -1;
}

int read_char( int index )
{
	// get one character
	uint8_t ret;
	if( board_disc_image_access( source_list[index].filename, Disc_Mode_Read, source_list[index].pointer, &ret, 1 ) == 0 ) return -1;
	source_list[index].pointer++;
	return (int)ret;
}

void unget_char( int index )
{
	// move back one character
	//ungetc( data, handler_list[index] );
	source_list[index].pointer--;
}

int write_file( unsigned char data )
{
	// write compiled byte
	temp_binary[temp_index++] = data;

	if( temp_index >= TEMP_BUFFER_SIZE )
	{
        board_disc_image_access( output_file.filename, Disc_Mode_Write, output_file.pointer, temp_binary, TEMP_BUFFER_SIZE );
		output_file.pointer += TEMP_BUFFER_SIZE;
		temp_index = 0;
	}

	return 1;
}

void close_file( int index )
{
	// close input source file
}

const file_hdl_t file_handler = 
{
	open_file,
	read_char,
	unget_char,
	write_file,
	close_file,
};

int assembler( const char ** filelist, int total_files, char * output, void * p_board )
{
	int i;
	int ret;

	board = ( board_data_t * )p_board;
	memset( source_list, 0x00, sizeof( source_list ) );

	for( i = 0; i < total_files; i++ )
	{
		source_list[i].filename = filelist[i];
		source_list[i].pointer = 0;
	}

	output_file.filename = output;
	output_file.pointer = 0;
	temp_index = 0;

	ret = assembler_embedded( filelist, total_files, ( file_hdl_t * )&file_handler, print_log, NULL );

	if( temp_index != 0 )
	{
        board_disc_image_access( output_file.filename, Disc_Mode_Write, output_file.pointer, temp_binary, temp_index );
	}

	return ret;
}

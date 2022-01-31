#ifndef _EMBEDDED_H_
#define _EMBEDDED_H_

//////////////////////////////////////////////////////////////////////////////////////

enum
{
	Asm_ErrorExtended = -200,
	Asm_ErrorOutOfMemory,
	Asm_ErrorPass2,
	Asm_ErrorPPMemory,
	Asm_ErrorBMemory,
	Asm_ErrorLMemory,
	Asm_ErrorAFile,
	Asm_ErrorPPFile,
	Asm_ErrorSrcFile,

	Asm_NoError = 0,

};

enum
{
	FileMode_ReadText,
	FileMode_WriteBin,
	FileMode_Remove
};

//////////////////////////////////////////////////////////////////////////////////////

typedef int ( *open_file_t )( char * name );
typedef int ( *read_file_t )( int index, char * line );
typedef int ( *read_char_t )( int index );
typedef void ( *unget_char_t )( int index );
typedef int ( *write_file_t )( unsigned char data );
typedef void ( *close_file_t )( int index );

typedef void ( *logout_hdl_t )(char *s);

typedef struct
{
	open_file_t open_file;
	read_char_t read_char;
	unget_char_t unget_char;
	write_file_t write_file;
	close_file_t close_file;

} file_hdl_t;

typedef struct
{
	int labels[2];
	int label_mem[2];
	int pp_defs[2];
	int pp_mem[2];
	int byte_mem[2];
	int blocks[2];

} stats_t;

//////////////////////////////////////////////////////////////////////////////////////

int assembler_embedded( const char ** filename, int nifiles, void * p_file, void * p_logout, void * p_stats );
int assembler( const char ** filelist, int total_files, char * output, void * p_board );

//////////////////////////////////////////////////////////////////////////////////////

#endif // _EMBEDDED_H_

//#define MINIMP3_ONLY_MP3
//#define MINIMP3_ONLY_SIMD
#define MINIMP3_NO_SIMD
//#define MINIMP3_NONSTANDARD_BUT_LOGICAL
//#define MINIMP3_FLOAT_OUTPUT
#define MINIMP3_IMPLEMENTATION
#include "minimp3_ex.h"
#include "types.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

static mp3dec_t mp3d;

////////////////////////////////////////////////////////////////////

void mp3player_init( void )
{
    mp3dec_init(&mp3d);
}
void mp3player_open_file( const char *filename )
{
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, filename, &info, NULL, NULL))
    {
        /* error */
    }
}

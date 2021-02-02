#include "tima_libc.h"

bool_t tima_string_extract( const char * input, uint32_t * pos, char * output )
{
    int len;
    int index_out = 0;
    int start_pos = *pos;

    for( ; *pos < strlen( input ); (*pos)++ )
    {
        if( input[*pos] > 0x20 )
        {
            break;
        }
    }

    for( ; *pos < strlen( input ); (*pos)++ )
    {
        if( input[*pos] > 0x20 )
        {
            output[index_out++] = input[*pos];
        }
        else
        {
            output[index_out] = 0;
            break;
        }
    }

    return (*pos != start_pos);
}

bool_t tima_tokenizer(const char *s1, const char ** exit, int * size, const char *delimit, char ** lastToken)
{
    const char *tmp;

    /* Skip leading delimiters if new string. */
    if ( s1 == NULL )
    {
        s1 = *lastToken;
        if (s1 == NULL)         /* End of story? */
            return FALSE;
    }
    else
    {
        s1 += strspn(s1, delimit);
    }

    /* Find end of segment */
    tmp = strpbrk(s1, delimit);
    if (tmp)
    {
        /* Found another delimiter, split string and save state. */
        *exit = s1;
        *size = ( int )tmp - ( int )s1;
        *lastToken = ( char * )tmp + 1;
    }
    else
    {
        /* Last segment, remember that. */
        *exit = s1;
        *size = ( uint32_t )strlen( *exit );
        *lastToken = NULL;
    }

    if( s1 != NULL ) return TRUE;
    return FALSE;
}

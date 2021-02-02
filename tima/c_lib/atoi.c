#include "types.h"

static char _isdigit( unsigned char c)
{
    if ( c >= '0' && c <= '9' )
        return 1;
    
    return 0;
}

int64_t tima_atoi_n( const char * str, uint32_t len, uint32_t base )
{
	uint32_t cnt;
	int64_t ret;
    bool_t is_neg;

    is_neg = FALSE;
	ret = 0;

	for( cnt = 0; cnt < len; cnt++ )
	{
        if( str[cnt] == '.' ) break;
        if( str[cnt] <= 0x20 ) continue;
        if( str[cnt] == '-' )
        {
            is_neg = TRUE;
            continue;
        }
        
		ret *= base;

		if( ( str[ cnt ] >= 'A' ) && ( str[ cnt ] <= 'F' ) )
		{
			ret += ( str[ cnt ] - (int32_t)'A' + 10 );
		}
		else if( ( str[ cnt ] >= 'a' ) && ( str[ cnt ] <= 'f' ) )
		{
			ret += ( str[ cnt ] - (int32_t)'a' + 10 );
		}
		else if( ( str[ cnt ] >= '0' ) && ( str[ cnt ] <= '9' ) )
		{
			ret += ( str[ cnt ] - (int32_t)'0' );
		}
		else
		{
			return 0;
		}
	}
    
    if( is_neg == TRUE )
    {
        ret = 0 - ret;
    }

	return ret;
}

int64_t tima_atoi( const char * str, uint32_t base )
{
	return tima_atoi_n( str, (uint32_t)strlen( str ), base );
}

bool_t tima_is_numeric( const char * str )
{
	int i;
	for( i = 0; i < (int)strlen( str ); i++ )
	{
		if( !_isdigit( ( *str ) ) ) return FALSE;
		str++;
	}

	return TRUE;
}

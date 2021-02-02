#include "tima_libc.h"

int strcmp_scs( char *str1, char *str2 )
{
	int len_str1 = (int)strlen( str1 );
	int len_str2 = (int)strlen( str2 );
	int length;
	int counter;

	char cmp_str1;
	char cmp_str2;

	if( len_str1 > len_str2 ) length = len_str1;
	else length = len_str2;

	for( counter = 0; counter < length; counter++ )
	{
		if( ( str1[ counter ] >= 'A' ) && ( str1[ counter ] <= 'Z' ) )
		{
			cmp_str1 = str1[ counter ] | 0x20;
		}
		else
		{
			cmp_str1 = str1[ counter ];
		}

		if( ( str2[ counter ] >= 'A' ) && ( str2[ counter ] <= 'Z' ) )
		{
			cmp_str2 = str2[ counter ] | 0x20;
		}
		else
		{
			cmp_str2 = str2[ counter ];
		}

		if( cmp_str1 == 0 ) return( -1 ); // return( 0 );
		if( cmp_str2 == 0 ) return( 1 ); // return( 0 );

		if( ( cmp_str1 > cmp_str2 ) || ( cmp_str1 < cmp_str2 ) ) return( cmp_str1 - cmp_str2 );
	}

	return( 0 );
}

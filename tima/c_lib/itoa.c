#include "tima_libc.h"
#include "types.h"

char local_buffer[20];
//char local_padding[25];

void tima_itoa_padding( int value, char * out, int base, int padding_size, char padding )
{
    uint16_t index;
	int padding_cnt;
    int temp_value;
    int local_value;
    uint8_t char_value;
    bool_t is_neg = FALSE;

    if( value == 0 )
    {
        strcpy( out, "0" );
        return;
    }
    
    if( value < 0 )
    {
        is_neg = TRUE;
        value = 0 - value;
    }

    index = 18;
    local_buffer[ index + 1 ] = 0;

    while( value )
    {
        local_value = value / base;
        temp_value = local_value * base;
        char_value = value - temp_value;

        if( char_value > 9 ) local_buffer[ index ] = 'A' - 10 + char_value;
        else local_buffer[ index ] = '0' + char_value;

        index--;
        value = local_value;
    }
    
    if( is_neg == TRUE )
    {
        local_buffer[ index ] = '-';
        index--;
    }

	out[0] = 0;
	while( (int)strlen( &local_buffer[ index + 1 ] ) < padding_size )
	{
		padding_cnt = (int)strlen(out);
		out[padding_cnt] = padding;
		out[padding_cnt+1] = 0;
		padding_size--;
	}

    strcat( out, &local_buffer[ index + 1 ] );
}

void tima_itoa( int value, char * out, int base )
{
	tima_itoa_padding( value, out, base, 0, ' ' );
}

void tima_ftoa( float value, char * out, int total_digits, int decimal_digits, char padding )
{
	int integer_part;
	int decimal_part;
	int power;
	int i;
	char control[20];

	power = 1;
	integer_part = ( int )value;
	value -= ( float )integer_part;

	for( i = 0; i < decimal_digits; i++ )
	{
		power *= 10;
	}

	value *= power;
	decimal_part = ( int )value;

	if( decimal_digits == 0 )
	{
		tima_itoa_padding( integer_part, out, 10, total_digits, padding );
	}
	else
	{
		tima_itoa_padding( integer_part, control, 10, total_digits - decimal_digits - 1, padding );
		strcpy( out, control );
		strcat( out, "." );

		tima_itoa_padding( decimal_part, control, 10, decimal_digits, '0' );
		strcat( out, control );
	}
}

#ifndef __TIMA_LIBC_H__
#define __TIMA_LIBC_H__

//////////////////////////////////////////////////////////////////////////////////////

#include "types.h"

////////////////////////////////////////////////////////////////////////////////////////////

#define VSF_PRINTK_BUF_SIZE         2048
#define SINE_TABLE_SIZE				4096

extern char vsf_printk_buf[];

////////////////////////////////////////////////////////////////////////////////////////////

// typedef long long time_t;

typedef struct _tm_ 
{
	int tm_sec;     /* seconds after the minute - [0,59] */
	int tm_min;     /* minutes after the hour - [0,59] */
	int tm_hour;    /* hours since midnight - [0,23] */
	int tm_mday;    /* day of the month - [1,31] */
	int tm_mon;     /* months since January - [0,11] */
	int tm_year;    /* years since 1900 */
	int tm_wday;    /* days since Sunday - [0,6] */
	int tm_yday;    /* days since January 1 - [0,365] */
	int tm_isdst;   /* daylight savings time flag */

} date_time_t;

//////////////////////////////////////////////////////////////////////////////////////

void tima_itoa( int value, char * out, int base );
int64_t tima_atoi( const char * str, uint32_t base );
int64_t tima_atoi_n( const char * str, uint32_t len, uint32_t base );
void tima_ftoa( float value, char * out, int total_digits, int decimal_digits, char padding );
void tima_itoa_padding( int value, char * out, int base, int padding_size, char padding );
bool_t tima_is_numeric( const char * str );

int vsnprintk(char *buf, int size, const char *fmt, va_list args);
int sprintk( char * out, const char *fmt, ... );

date_time_t * tima_localtime(const time_t tp);
char * tima_asctime( const date_time_t *tm );
char * tima_ctime( time_t tp );
time_t tima_mktime(const date_time_t *tm);

bool_t tima_tokenizer(const char *s1, const char ** exit, int * size, const char *delimit, char ** lastToken);
bool_t tima_string_extract( const char * input, uint32_t * pos, char * output );

int strcmp_scs( char *str1, char *str2 );

void * memcpy_be( void *v_dst, const void *v_src, long c );

bool_t tima_str_to_ip( char * input, uint8_t * output );

////////////////////////////////////////////////////////////////////////////////

/* rad: 0-4095 = 0-2PI */
/* cos/sin: -32766 to +32767 = -1 to +1 */

int sin_table( int rad );
int cos_table( int rad );
int acos_table( int val );

//////////////////////////////////////////////////////////////////////////////////////

#endif // __TIMA_LIBC_H__

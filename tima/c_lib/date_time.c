#include "tima_libc.h"

////////////////////////////////////////////////////////////////////////////////////////////

static const char day[][4] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
static const char mon[][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

static const int mday[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static date_time_t local_tm;

static char local_buf[80];
//static bool_t is_init = FALSE;

////////////////////////////////////////////////////////////////////////////////////////////

time_t tima_mktime(const date_time_t *tm)
{
	int i;
	time_t t = 0;
	for(i=70; i<tm->tm_year; i++){
		if(i%4 == 0)
			t += 86400 * 366;
		else
			t += 86400 * 365;
	}
	for(i=0; i<tm->tm_mon; i++){
		t += mday[i] * 86400;
		if (tm->tm_year % 4 == 0 && i == 2)
			t += 86400;
	}
	t += (tm->tm_mday-1) * 86400;
	t += tm->tm_hour * 3600;
	t += tm->tm_min * 60;
	t += tm->tm_sec;
	return t;
}

char * tima_ctime( time_t tp )
{
    return tima_asctime( tima_localtime( tp ) );
}

date_time_t * tima_localtime(const time_t tp)
{
	time_t t = tp;
	int isleap = 0;
	
	local_tm.tm_sec = t % 60;
	t /= 60;
	local_tm.tm_min = t % 60;
	t /= 60;
	local_tm.tm_hour = t % 24;
	t /= 24;
	local_tm.tm_wday = (t + 4) % 7;  // Jan 1 1970 = Thursday
	
	for (local_tm.tm_year=70;; local_tm.tm_year++) {
		isleap = (local_tm.tm_year+1900)%4 == 0;
		if (t < 365 + isleap)
			break;
		t -= 365 + isleap;
	}
	
	local_tm.tm_yday = (int)t;
	for (local_tm.tm_mon=0;; local_tm.tm_mon++) {
		isleap = (local_tm.tm_year+1900)%4 == 0 && local_tm.tm_mon == 1;
		if (t < mday[local_tm.tm_mon] + isleap)
			break;
		t -= mday[local_tm.tm_mon] + isleap;
	}
	local_tm.tm_mday = (int)t + 1;
	local_tm.tm_isdst = 0;

	return &local_tm;
}

char *tima_asctime( const date_time_t *tm )
{
	char *p;
	int y;
	
	p = local_buf;
	memcpy(p, day[tm->tm_wday], 3);
	p += 3;
	*p++ = ' ';
	memcpy(p, mon[tm->tm_mon], 3);
	p += 3;
	*p++ = ' ';
	*p++ = '0' + tm->tm_mday / 10;
	*p++ = '0' + tm->tm_mday % 10;
	*p++ = ' ';
	*p++ = '0' + tm->tm_hour / 10;
	*p++ = '0' + tm->tm_hour % 10;
	*p++ = ':';
	*p++ = '0' + tm->tm_min / 10;
	*p++ = '0' + tm->tm_min % 10;
	*p++ = ':';
	*p++ = '0' + tm->tm_sec / 10;
	*p++ = '0' + tm->tm_sec % 10;
	*p++ = ' ';
	y = tm->tm_year + 1900;
	*p++ = '0' + y / 1000;
	*p++ = '0' + (y / 100) % 10;
	*p++ = '0' + (y / 10) % 10;
	*p++ = '0' + y % 10;
	// *p++ = '\n';
	*p = 0;
	
	return local_buf;
}

////////////////////////////////////////////////////////////////////////////////////////////

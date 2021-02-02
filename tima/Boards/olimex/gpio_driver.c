#include "types.h"
#include <unistd.h>
#include <getopt.h>
#include <linux/types.h>
#include <errno.h>
#include "gpio_driver.h"
#include "gpio_map.h"
#include "t_threads.h"

///////////////////////////////////////////////////////////////////////////

#define MAX_SIZE			64

///////////////////////////////////////////////////////////////////////////

typedef struct gpio_data_t_
{
	void * mutex;
	gpio_t gpio;
	int fd;
	int mode;
	char path[MAX_SIZE];

} gpio_data_t;

typedef struct gpio_counter_t_
{
	void * mutex;
	gpio_t gpio;
	int fd;
	int mode;
	char path_counter[MAX_SIZE];
	char path_interval[MAX_SIZE];

} gpio_counter_t;

///////////////////////////////////////////////////////////////////////////

static const char * out_state[] = { "0", "1" };

///////////////////////////////////////////////////////////////////////////

void _gpio_init_export( char * path, gpio_t gpio )
{
	int fd;
	char command[4];

	if( access( path, F_OK ) != -1 )
	{
	    // file exists
		return;
	}

	sprintf( command, "%d", (int)gpio+1 );

	errno = 0;
	fd = open( "/sys/class/gpio/export", O_WRONLY );
	if( fd == -1 )
	{
		printf( "Failed to init %s (_gpio_init_export-open %d)\n", path, errno );
		return;
	}

	if( write( fd, command, strlen( command ) ) == -1 )
	{
		printf( "Failed to init %s (_gpio_init_export-write)\n", path );
	}

	close( fd );
}

static int _gpio_setup_direction( gpio_t gpio, char * dir )
{
	int fd;
	char path_str[MAX_SIZE];

	snprintf(path_str, MAX_SIZE, "/sys/class/gpio/%s/direction", gpio_map_fs[(int)gpio]);
	_gpio_init_export( path_str, gpio );

	fd = open(path_str, O_WRONLY);
	if( fd == -1 )
	{
		printf( "Failed to open %s\r\n", gpio_map_fs[(int)gpio] );
		return -3;
	}

	if( write( fd, dir, strlen(dir) ) == -1 )
	{
		printf( "Failed to set %s to out\r\n", gpio_map_fs[(int)gpio] );
		close(fd);
		return -4;
	}

	close(fd);

	return 0;
}

static void _gpio_setup_counter( gpio_t gpio, char * mode )
{
	int fd;
	char path_str[MAX_SIZE];

	snprintf(path_str, MAX_SIZE, "/sys/class/gpio/%s/edge", gpio_map_fs[(int)gpio]);

	errno = 0;
	fd = open( path_str, O_WRONLY );
	if( fd == -1 )
	{
		printf( "Failed to init %s (_gpio_setup_counter-open %d)\n", path_str, errno );
		return;
	}

	if( write( fd, mode, strlen( mode ) ) == -1 )
	{
		printf( "Failed to init %s (_gpio_setup_counter-write)\n", path_str );
	}

	close( fd );
}

static uint32_t _gpio_get_counter( gpio_counter_t * gpio_fs )
{
	int len;
	char in_state[12];

	tthread_mutex_lock( gpio_fs->mutex );

	gpio_fs->fd = open( gpio_fs->path_counter, O_RDONLY );
	if( gpio_fs->fd == -1 )
	{
		printf( "Failed to open %s\r\n", gpio_fs->path_counter );
		tthread_mutex_unlock( gpio_fs->mutex );
		return -1;
	}

	len = read( gpio_fs->fd, in_state, 12 );

	if( len == -1 )
	{
		printf( "Failed to get %s from input\r\n", gpio_fs->path_counter );
		tthread_mutex_unlock( gpio_fs->mutex );
		return -2;
	}

	close( gpio_fs->fd );
	tthread_mutex_unlock( gpio_fs->mutex );

	return ( uint32_t )atoi(in_state);
}

static int _gpio_get_interval( gpio_counter_t * gpio_fs, uint64_t * interval )
{
	int len;
	uint64_t prev_time, new_time;
	char log_data[32];

	tthread_mutex_lock( gpio_fs->mutex );

	gpio_fs->fd = open( gpio_fs->path_interval, O_RDONLY );
	if( gpio_fs->fd == -1 )
	{
		printf( "Failed to open %s\r\n", gpio_fs->path_interval );
		tthread_mutex_unlock( gpio_fs->mutex );
		return -1;
	}

	len = read( gpio_fs->fd, log_data, 32 );
	if( len == -1 )
	{
		printf( "Failed to get %s from input\r\n", gpio_fs->path_interval );
		tthread_mutex_unlock( gpio_fs->mutex );
		return -2;
	}

	sscanf( log_data, "%lld %lld", &prev_time, &new_time );
	*interval = new_time - prev_time;

	close( gpio_fs->fd );
	tthread_mutex_unlock( gpio_fs->mutex );

	return sizeof( uint64_t );
}

///////////////////////////////////////////////////////////////////////////

void gpio_init( void )
{
}

void * gpio_open_output( gpio_t gpio )
{
	gpio_data_t * gpio_fs;

	if( _gpio_setup_direction( gpio, "out" ) != 0 )
	{
		return NULL;
	}

	gpio_fs = ( gpio_data_t * )malloc( sizeof( gpio_data_t ) );
	if( gpio_fs == NULL ) return NULL;

	snprintf(gpio_fs->path, MAX_SIZE, "/sys/class/gpio/%s/value", gpio_map_fs[(int)gpio]);

	gpio_fs->mutex = tthread_mutex_init();
	gpio_fs->mode = MODE_OUTPUT;
	gpio_fs->gpio = gpio;

	return gpio_fs;
}

void * gpio_open_counter( gpio_t gpio )
{
	gpio_counter_t * gpio_fs;

	//if( _gpio_setup_direction( gpio, "in" ) != 0 )
	//{
	//	return NULL;
	//}

	gpio_fs = ( gpio_counter_t * )malloc( sizeof( gpio_counter_t ) );
	if( gpio_fs == NULL ) return NULL;

	snprintf(gpio_fs->path_counter, MAX_SIZE, "/sys/class/gpio/%s/counter", gpio_map_fs[(int)gpio]);
	snprintf(gpio_fs->path_interval, MAX_SIZE, "/sys/class/gpio/%s/interval", gpio_map_fs[(int)gpio]);

	_gpio_init_export( gpio_fs->path_counter, gpio );
	_gpio_setup_counter( gpio, "count" );

	gpio_fs->mutex = tthread_mutex_init();
	gpio_fs->mode = MODE_COUNTER;
	gpio_fs->gpio = gpio;

	return gpio_fs;
}

void * gpio_open_input( gpio_t gpio )
{
	gpio_data_t * gpio_fs;

	if( _gpio_setup_direction( gpio, "in" ) != 0 )
	{
		return NULL;
	}

	gpio_fs = ( gpio_data_t * )malloc( sizeof( gpio_data_t ) );
	if( gpio_fs == NULL ) return NULL;

	snprintf(gpio_fs->path, MAX_SIZE, "/sys/class/gpio/%s/value", gpio_map_fs[(int)gpio]);

	gpio_fs->mode = MODE_INPUT;
	gpio_fs->gpio = gpio;
	gpio_fs->mutex = tthread_mutex_init();

	return gpio_fs;
}

void gpio_output( void * p_gpio, int state )
{
	gpio_data_t * gpio_fs = ( gpio_data_t * )p_gpio;

	if( gpio_fs->mode != MODE_OUTPUT ) return;

	tthread_mutex_lock( gpio_fs->mutex );

	gpio_fs->fd = open(gpio_fs->path, O_WRONLY);
	if( gpio_fs->fd == -1 )
	{
		printf( "Failed to open %s\r\n", gpio_map_fs[(int)gpio_fs->gpio] );
		tthread_mutex_unlock( gpio_fs->mutex );
		return;
	}

	if( write( gpio_fs->fd, out_state[state], 1 ) == -1 )
	{
		printf( "Failed to set %s to out\r\n", gpio_map_fs[(int)gpio_fs->gpio] );
		tthread_mutex_unlock( gpio_fs->mutex );
		return;
	}

	close( gpio_fs->fd );
	tthread_mutex_unlock( gpio_fs->mutex );
}

int gpio_input( void * p_gpio )
{
	char in_state[3];
	int len;

	gpio_data_t * gpio_fs = ( gpio_data_t * )p_gpio;

	if( gpio_fs->mode != MODE_INPUT ) return 0;

	tthread_mutex_lock( gpio_fs->mutex );

	gpio_fs->fd = open(gpio_fs->path, O_RDONLY);
	if( gpio_fs->fd == -1 )
	{
		printf( "Failed to open %s\r\n", gpio_map_fs[(int)gpio_fs->gpio] );
		tthread_mutex_unlock( gpio_fs->mutex );
		return 0;
	}

	len = read( gpio_fs->fd, in_state, 3 );

	if( len == -1 )
	{
		printf( "Failed to get %s from input\r\n", gpio_map_fs[(int)gpio_fs->gpio] );
		tthread_mutex_unlock( gpio_fs->mutex );
		return 0;
	}

	close( gpio_fs->fd );
	tthread_mutex_unlock( gpio_fs->mutex );

	return atoi(in_state);
}

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval )
{
	gpio_counter_t * gpio_fs = ( gpio_counter_t * )p_gpio;

	if( gpio_fs->mode != MODE_COUNTER ) return 0;

	if( interval != NULL )
	{
		_gpio_get_interval( gpio_fs, interval );
	}

	return _gpio_get_counter( gpio_fs );
}

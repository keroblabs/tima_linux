#include "system.h"
#include "spawn_lib.h"
#include "wiringPi.h"

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

typedef struct _gpio_rpi_t
{
    gpio_t gpio;
    char * name;
    int index_bcm;
    int index_wpi;

} gpio_rpi_t;

////////////////////////////////////////////////////////////////////

#define GPIO_BACKLIGHT          -2
#define GPIO_BRIGHTNESS         -3

////////////////////////////////////////////////////////////////////
/*
 +------+-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+------+
 | Tima | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM | Tima |
 +------+-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+------+
 |      |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |      |
 |      |   2 |   8 |   SDA.1 | ALT0 | 1 |  3 || 4  |   |      | 5v      |     |     |      |
 |      |   3 |   9 |   SCL.1 | ALT0 | 1 |  5 || 6  |   |      | 0v      |     |     |      |
 |      |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | ALT5 | TxD     | 15  | 14  |      |
 |      |     |     |      0v |      |   |  9 || 10 | 1 | ALT5 | RxD     | 16  | 15  |      |
 |      |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  | PE01 |
 |      |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |      |
 |      |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 1 | OUT  | GPIO. 4 | 4   | 23  | PE00 |
 |      |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  | PE02 |
 |      |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |      |
 |      |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |      |
 |      |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |      |
 |      |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |      |
 |      |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |      |
 |      |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |      |
 |      |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |      |
 |      |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |      |
 |      |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |      |
 |      |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |      |
 |      |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |      |
 +------+-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+------+
 | Tima | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM | Tima |
 +------+-----+-----+---------+------+---+---Pi 3---+---+------+---------+-----+-----+------+
*/

static const gpio_rpi_t gpio_list[] =
{
    { GPIO_PG00, "GPIO_PG00", GPIO_BACKLIGHT, -1  },
    { GPIO_PG01, "GPIO_PG01", GPIO_BRIGHTNESS, -1  },

    { GPIO_PE00, "GPIO_PE00", 23,  4 },
    { GPIO_PE01, "GPIO_PE01", 18,  1 },
    { GPIO_PE02, "GPIO_PE02", 24,  5 },
    { GPIO_PE03, "GPIO_PE03", 26, 25 },

    { GPIO_PE04, "GPIO_PE04", 24,  5 },
    { GPIO_PE05, "GPIO_PE05", 17,  0 },
    { GPIO_PE06, "GPIO_PE06", 27,  2 },
    { GPIO_PE07, "GPIO_PE07", 22,  3 },

    { GPIO_MAX, NULL, -1,  -1 },
};

////////////////////////////////////////////////////////////////////

void setup_io( void )
{
    wiringPiSetup();
}

static gpio_rpi_t * get_gpio_data( gpio_t gpio )
{
    for( int i = 0; i < GPIO_MAX; i++ )
    {
        if( gpio_list[i].index_bcm == -1 ) break;
        if( gpio_list[i].gpio == gpio ) return ( gpio_rpi_t * )&gpio_list[i];
    }
    return NULL;
}

void gpio_init( void )
{
    setup_io();
}

void * gpio_open_output( gpio_t gpio )
{
    gpio_rpi_t * p_data = get_gpio_data( gpio );
    if( ( p_data != NULL ) && ( p_data->index_wpi >= 0 ) )
    {
        //printf( "gpio_open_output %s\n", p_data->name );
        pinMode( p_data->index_wpi, OUTPUT );
    }

    return p_data;
}

void * gpio_open_input( gpio_t gpio )
{
    gpio_rpi_t * p_data = get_gpio_data( gpio );
    if( ( p_data != NULL ) && ( p_data->index_wpi >= 0 ) )
    {
        pinMode( p_data->index_wpi, INPUT );
        pullUpDnControl(p_data->index_wpi, PUD_UP);
        //printf( "gpio_open_input %s\n", p_data->name );
    }

    return p_data;
}

void gpio_output( void * p_gpio, int state )
{
    char command[80];
    gpio_rpi_t * p_data = ( gpio_rpi_t * )p_gpio;
    if( p_data )
    {
        if( p_data->index_wpi >= 0 )
        {
            digitalWrite( p_data->index_wpi, state ? HIGH : LOW );
        }
        else if( p_data->index_bcm == GPIO_BACKLIGHT )
        {
            sprintf( command, "sudo bash -c \" echo %d > /sys/class/backlight/rpi_backlight/bl_power\"", state ? 0 : 1 );
            spawn_command( command );
        }
        else if( p_data->index_bcm == GPIO_BRIGHTNESS )
        {
            sprintf( command, "sudo bash -c \" echo %d > /sys/class/backlight/rpi_backlight/brightness\"", state );
            spawn_command( command );
        }
    }
}

int  gpio_input( void * p_gpio )
{
    int ret = 0;
    gpio_rpi_t * p_data = ( gpio_rpi_t * )p_gpio;
    if( ( p_data ) && ( p_data->index_wpi >= 0 ) )
    {
        ret = digitalRead( p_data->index_wpi );
    }

    return ret;
}

void * gpio_open_counter( gpio_t gpio )
{
    return NULL;
}

uint32_t gpio_get_counter( void * p_gpio, uint64_t * interval )
{
    *interval = 0;
    return 0;
}

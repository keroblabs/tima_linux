#include "lcd_driver.h"
#include "graphics.h"
#include "t_threads.h"
#include "touch.h"

////////////////////////////////////////////////////////////////////////////////////////

static uint32_t * display_fb;
static uint16_t lcd_width;
static uint16_t lcd_height;

static bitmap_t lcd_driver_bitmap;
static event_data_t event;

static void * mouse_mutex;

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

static void mouse_thread( void )
{
    event_data_t local_event;
    int fd;

    if ((fd = openTouchScreen()) == -1)
    {
        printf("error opening touch screen\r\n");   
        return;     
    }

    while( 1 )
    {
        if( getTouchSample( fd, &local_event ) )
        {
            tthread_mutex_lock( mouse_mutex );
            event.posx = local_event.posx;
            event.posy = local_event.posy;
            event.posz = local_event.posz;
            event.state = 1;
            tthread_mutex_unlock( mouse_mutex );
        }

        tthread_sleep_ms(30);
    }

}

static void mouse_init( void )
{
    mouse_mutex = tthread_mutex_init();
    tthread_create( mouse_thread );
}

static int lcd_init( void )
{
    int fd, x, y;
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;

    if ((fd = open("/dev/fb0", O_RDWR)) == -1) {
        printf("Can't open /dev/fb0\n");
        return -1;
    }

    if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("FBIOGET_FSCREENINFO failed\n");
        return -2;
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("FBIOGET_VSCREENINFO failed\n");
        return -3;
    }

    if (vinfo.bits_per_pixel != 32) {
        printf("Only 32bpp framebuffer is supported (%d)\n", vinfo.bits_per_pixel);
        return -4;
    }

    lcd_width = vinfo.xres;
    lcd_height = vinfo.yres;

    display_fb = mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (display_fb == (void *)-1) {
        printf("mmap failed\n");
        return -4;
    }

    lcd_driver_bitmap.buffer = display_fb;
    lcd_driver_bitmap.width = lcd_width;
    lcd_driver_bitmap.height = lcd_height;

    for (y = 0; y < vinfo.yres; y++)
        for (x = 0; x < vinfo.xres; x++)
            display_fb[y * vinfo.xres + x] = 0x00111111;

    return 0;
}

uint16_t lcd_driver_width( void )
{
	return lcd_width;
}

uint16_t lcd_driver_height( void )
{
	return lcd_height;
}

uint32_t * lcd_driver_get_buffer( void )
{
	return display_fb;
}

void lcd_driver_process( void )
{
}

int lcd_driver_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
    int ret = 0;

    tthread_mutex_lock( mouse_mutex );
    if( event.state )
    {
        *posx = event.posx;
        *posy = event.posy;
        *posz = event.posz;   
        event.state = 0;     
        ret = 1;
    }
    tthread_mutex_unlock( mouse_mutex );

    return ret;
}

int lcd_driver_init( void )
{
    mouse_init();
    return lcd_init();
}

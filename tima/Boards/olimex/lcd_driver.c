#include "lcd_driver.h"
#include "graphics.h"

////////////////////////////////////////////////////////////////////////////////////////

static uint32_t * display_fb;
static uint16_t lcd_width;
static uint16_t lcd_height;


////////////////////////////////////////////////////////////////////////////////////////

static int lcd_init( void )
{
    int fd, x, y;
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    uint32_t * local_fb;

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
        return -5;
    }

    lcd_width = vinfo.xres;
    lcd_height = vinfo.yres;
    frame_size = lcd_width * lcd_height * 4;

    local_fb = mmap(0, frame_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (local_fb == (void *)-1) {
        printf("mmap failed\n");
        return -6;
    }

    memset( local_fb, 0x00, frame_size );

    display_fb = &local_fb[0];

    return 0;
}

void lcd_driver_flip_frame( uint8_t frame )
{
}

uint16_t lcd_driver_width( void )
{
	return lcd_width;
}

uint16_t lcd_driver_height( void )
{
	return lcd_height;
}

void * lcd_driver_get_buffer( void )
{
    //printf( "lcd_driver_get_buffer\n" );
	return display_fb;
}

void lcd_driver_release_frame( void )
{
}

void lcd_driver_process( void )
{
}

int lcd_driver_read_mouse( uint16_t * posx, uint16_t * posy, uint16_t * posz )
{
}

int lcd_driver_init( void )
{

    return lcd_init();
}

#include "lcd_driver.h"
#include "graphics.h"

////////////////////////////////////////////////////////////////////////////////////////

static uint32_t * display_fb;
static uint16_t lcd_width;
static uint16_t lcd_height;

static bitmap_t lcd_driver_bitmap;

////////////////////////////////////////////////////////////////////////////////////////

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

int lcd_driver_init( void )
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
        	display_fb[y * vinfo.xres + x] = 0;

    return 0;
}

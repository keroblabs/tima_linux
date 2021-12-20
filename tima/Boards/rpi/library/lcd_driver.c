#include "lcd_driver.h"
#include "graphics.h"
#include "t_threads.h"
#include "touch.h"
#include "video.h"
#include "timer_driver.h"

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

static uint32_t * shown_fb;
static uint32_t * display_fb;
static uint16_t lcd_width;
static uint16_t lcd_height;
static uint32_t frame_size;

static VIDEO v_rpi;
static uint32_t frame_timestamp;
static uint32_t * curr_frame[2];
static uint8_t frame_index;
static bool_t frame_ready;

//static bitmap_t lcd_driver_bitmap;
static event_data_t event;

static void * mouse_mutex;

static int main_fd;

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

static int lcd_video_init( void )
{
    uint32_t cnt;

    v_rpi = video_start( 0 );
    frame_timestamp = ms_timer_get_ms();

    curr_frame[0] = video_get_empty_buffer( v_rpi ); 
    curr_frame[1] = video_get_empty_buffer( v_rpi ); 
    for( cnt = 0; cnt < video_get_pixel_count( v_rpi ); cnt++ )
    {
        curr_frame[0][cnt] = 0;
        curr_frame[1][cnt] = 0;
    }

    frame_ready = TRUE;
    frame_index = 0;

    display_fb = curr_frame[frame_index];

    printf( "video ready\n" );

    return 0;
}

static int lcd_init( void )
{
    int x, y;
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    uint32_t * local_fb;

    if ((main_fd = open("/dev/fb0", O_RDWR)) == -1) {
        printf("Can't open /dev/fb0\n");
        return -1;
    }

    if (ioctl(main_fd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("FBIOGET_FSCREENINFO failed\n");
        return -2;
    }

    if (ioctl(main_fd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("FBIOGET_VSCREENINFO failed\n");
        return -3;
    }

    vinfo.yres_virtual = vinfo.yres * 2;
    vinfo.yoffset = 0;

    if (ioctl(main_fd, FBIOPUT_VSCREENINFO, &vinfo)) {
        printf("FBIOPUT_VSCREENINFO failed\n");
        return -4;
    }

    if (vinfo.bits_per_pixel != 32) {
        printf("Only 32bpp framebuffer is supported (%d)\n", vinfo.bits_per_pixel);
        return -5;
    }

    lcd_width = vinfo.xres;
    lcd_height = vinfo.yres;
    frame_size = lcd_width * lcd_height * 4;

    printf( "finfo.smem_len = %d\n", finfo.smem_len );

    local_fb = mmap(0, frame_size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, main_fd, 0);
    if (local_fb == (void *)-1) {
        printf("mmap failed\n");
        return -6;
    }

    //lcd_driver_bitmap.buffer = display_fb;
    //lcd_driver_bitmap.width = lcd_width;
    //lcd_driver_bitmap.height = lcd_height;

    memset( local_fb, 0x00, frame_size * 2 );

    display_fb = &local_fb[frame_size];
    shown_fb = &local_fb[0];

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
    //printf( "lcd_driver_release_frame\n" );
    frame_ready = TRUE;
}

void lcd_driver_process( void )
{
    uint32_t frame_timeout = ms_timer_get_ms();
    if( ( frame_ready == TRUE ) && ( frame_timeout > ( frame_timestamp + FRAME_PERIOD ) ) )
    {
        memcpy( shown_fb, display_fb, frame_size );
        //uint32_t new_time = ms_timer_get_ms();
        //printf( "swap time = %d\n", new_time - frame_timeout );

        frame_ready = FALSE;     
        frame_timestamp = frame_timeout;
    }
/*
    if( ( v_rpi != NULL ) && ( frame_ready == TRUE ) && ( frame_timeout > ( frame_timestamp + FRAME_PERIOD ) ) )
    {
        printf( "lcd_driver_process %d\n", frame_index );

        frame_timestamp = frame_timeout;
        video_submit_frame( v_rpi, curr_frame[frame_index] );
        frame_index = ( frame_index + 1 ) & 0x01;

        video_get_current_pixel_data( v_rpi, curr_frame[frame_index], video_get_req_buffer_size( v_rpi ) );
        frame_ready = FALSE;     
        display_fb = curr_frame[frame_index];
    }   
    */
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
    v_rpi = NULL;

    mouse_init();
    return lcd_init();
    //return lcd_video_init();
}

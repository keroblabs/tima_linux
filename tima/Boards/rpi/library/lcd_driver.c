#include "lcd_driver.h"
#include "graphics.h"
#include "t_threads.h"
#include "touch.h"
#include "video.h"
#include "timer_driver.h"

////////////////////////////////////////////////////////////////////////////////////////

typedef void * ( *pixel_copy_t )( void *restrict to, const void *restrict from, size_t size );

typedef struct
{
    union
    {
        uint32_t pixel;
        struct
        {
            uint8_t b;
            uint8_t g;
            uint8_t r;
            uint8_t a;
        } rgb;
    } p;
} rgb_pixel_t;

////////////////////////////////////////////////////////////////////////////////////////

#define APP_RGB_16(r,g,b) ( ( uint16_t )( ( ( ( uint16_t )r & 0xF8 ) << 8 ) | ( ( ( uint16_t )g & 0xFC ) << 3 ) | ( ( ( ( uint16_t )b & 0xF8 ) >> 3 ) ) ) )

////////////////////////////////////////////////////////////////////////////////////////

static void * shown_fb;
static uint32_t * display_fb;
static uint16_t lcd_width;
static uint16_t lcd_height;
static uint32_t shown_size;
static uint32_t display_size;

static VIDEO v_rpi;
static uint32_t frame_timestamp;
static uint32_t * curr_frame[2];
static uint8_t frame_index;
static bool_t frame_ready;

static event_data_t event;

static void * mouse_mutex;

static pixel_copy_t pixel_copy;

////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////

static void * pixel_32_to_16_memcpy (void *restrict to, const void *restrict from, size_t size)
{
    uint32_t * input = ( uint32_t * )from;
    uint16_t * output = ( uint16_t * )to;
    uint32_t pix_max = ( uint32_t )( size >> 1 );

    uint8_t * p32;
    uint32_t cnt;

    for( cnt = 0; cnt < pix_max; cnt++ )
    {
        p32 = ( uint8_t * )input;
        *output = APP_RGB_16(p32[0], p32[1], p32[2] );
        input++;
        output++;
    }

    return to;
}

static void mouse_thread( void * args )
{
    event_data_t local_event;
    int fd = ( int )args;

    //if ((fd = openTouchScreen()) == -1)
    //{
    //    printf("error opening touch screen\r\n");
    //    return;
   // }

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

static int lcd_video_init( void )
{
    uint32_t cnt;

    v_rpi = video_start( 0 );
    frame_timestamp = ms_timer_hw_get_ms();

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

    vinfo.yres_virtual = vinfo.yres;
    vinfo.yoffset = 0;

    if (ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo)) {
        printf("FBIOPUT_VSCREENINFO failed\n");
        return -4;
    }

    lcd_width = vinfo.xres;
    lcd_height = vinfo.yres;

    if( vinfo.bits_per_pixel == 32 )
    {
        pixel_copy = memcpy;
    }
    else if( vinfo.bits_per_pixel == 16 )
    {
        pixel_copy = pixel_32_to_16_memcpy;
    }
    else
    {
        printf("Unsupported %dbpp framebuffer\n", vinfo.bits_per_pixel);
        return -5;
    }

    display_size = lcd_width * lcd_height * 4;
    shown_size = finfo.smem_len;
    printf( "finfo.smem_len = %d(%d)\n", finfo.smem_len, display_size );

    shown_fb = mmap(0, shown_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shown_fb == (void *)-1) {
        printf("mmap failed\n");
        return -6;
    }

    // display size is always for 32bits
    display_fb = ( uint32_t * )malloc( display_size );
    if( display_fb == NULL )
    {
        printf( "display buffer failed\n" );
        return -7;
    }
    memset( display_fb, 0x00, display_size );
    memset( shown_fb, 0x00, shown_size );

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
    uint32_t frame_timeout = ms_timer_hw_get_ms();
    if( ( frame_ready == TRUE ) && ( frame_timeout > ( frame_timestamp + FRAME_PERIOD ) ) )
    {
        pixel_copy( shown_fb, display_fb, shown_size );
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

int lcd_driver_mouse_init( const char * dev )
{
    int fd;

    if ((fd = openTouchScreen(dev)) == -1)
    {
        printf("error opening touch screen\r\n");
        return -1;
    }

    mouse_mutex = tthread_mutex_init();
    tthread_create_ex( mouse_thread, ( void * )fd );

    return 0;
}

int lcd_driver_init( void )
{
    v_rpi = NULL;

    //mouse_init();
    return lcd_init();
}

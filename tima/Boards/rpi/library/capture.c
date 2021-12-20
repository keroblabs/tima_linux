#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

#include "capture.h"
#include "t_threads.h"

#define CLEAR(x) memset(&(x), 0, sizeof(x))

struct buffer
{
    void   *start;
    size_t  length;
};

typedef struct capture_data_t_
{
    struct buffer      *buffers;
    struct v4l2_format fmt;
    uint32_t           n_buffers;
    int                fd;
    void              *mutex;
    bool_t             is_loop;
    frame_hdl_t        frame_hdl;
    void              *p_data;

} capture_data_t;

static void errno_exit(const char *s)
{
    printf("%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

static int xioctl(int fh, int request, void *arg)
{
    int r;

    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}

static void process_image(capture_data_t * capture, const void *p, int size)
{
    if( capture->frame_hdl ) capture->frame_hdl( capture->p_data, p, capture->fmt.fmt.pix.width, capture->fmt.fmt.pix.height );
    // yuv_to_rgb_display( p, NULL, capture->fmt.fmt.pix.width, capture->fmt.fmt.pix.height, 36, 100 );
}

static int read_frame(capture_data_t * capture)
{
    struct v4l2_buffer buf;

    CLEAR(buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(capture->fd, VIDIOC_DQBUF, &buf))
    {
        switch (errno)
        {
            case EAGAIN: return 0;
            case EIO:
                /* Could ignore EIO, see spec. */
                /* fall through */
            default:
                errno_exit("VIDIOC_DQBUF");
        }
    }

    assert(buf.index < capture->n_buffers);

    process_image(capture, capture->buffers[buf.index].start, buf.bytesused);

    if (-1 == xioctl(capture->fd, VIDIOC_QBUF, &buf)) errno_exit("VIDIOC_QBUF");

    return 1;
}

static void mainloop(capture_data_t * capture)
{
    int fd = capture->fd;

    while( 1 )
    {
        fd_set fds;
        struct timeval tv;
        int r;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select(fd + 1, &fds, NULL, NULL, &tv);

        if (-1 == r)
        {
            if (EINTR == errno) continue;
            errno_exit("select");
        }

        if (0 == r)
        {
            printf("select timeout\n");
            exit(EXIT_FAILURE);
        }

        if (read_frame(capture)) break;
        /* EAGAIN - continue select loop. */
    }
}

static void stop_capturing(int capture_fd)
{
    enum v4l2_buf_type type;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(capture_fd, VIDIOC_STREAMOFF, &type)) errno_exit("VIDIOC_STREAMOFF");
}

static void start_capturing(capture_data_t * capture)
{
    unsigned int i;
    enum v4l2_buf_type type;

    for (i = 0; i < capture->n_buffers; ++i)
    {
        struct v4l2_buffer buf;

        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (-1 == xioctl(capture->fd, VIDIOC_QBUF, &buf)) errno_exit("VIDIOC_QBUF");
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(capture->fd, VIDIOC_STREAMON, &type)) errno_exit("VIDIOC_STREAMON");
}

static void uninit_device(capture_data_t * capture)
{
    unsigned int i;

    for (i = 0; i < capture->n_buffers; ++i)
    {
        if (-1 == munmap(capture->buffers[i].start, capture->buffers[i].length)) errno_exit("munmap");
    }

    free(capture->buffers);
}

static void init_mmap(capture_data_t * capture)
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count  = 4;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(capture->fd, VIDIOC_REQBUFS, &req))
    {
        if (EINVAL == errno)
        {
            printf("device does not support memory mappingn");
            exit(EXIT_FAILURE);
        }
        else
        {
            errno_exit("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2)
    {
        printf("Insufficient buffer memory on the device\n");
        exit(EXIT_FAILURE);
    }

    capture->buffers = calloc(req.count, sizeof(*capture->buffers));

    if (!capture->buffers)
    {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (capture->n_buffers = 0; capture->n_buffers < req.count; ++capture->n_buffers)
    {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = capture->n_buffers;

        if (-1 == xioctl(capture->fd, VIDIOC_QUERYBUF, &buf)) errno_exit("VIDIOC_QUERYBUF");

        capture->buffers[capture->n_buffers].length = buf.length;
        capture->buffers[capture->n_buffers].start = mmap(NULL /* start anywhere */,
                                      buf.length,
                                      PROT_READ | PROT_WRITE /* required */,
                                      MAP_SHARED /* recommended */,
                                      capture->fd, buf.m.offset);

        if (MAP_FAILED == capture->buffers[capture->n_buffers].start) errno_exit("mmap");
    }
}

static capture_data_t * init_device(int capture_fd)
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    unsigned int min;

    capture_data_t * capture = ( capture_data_t * )malloc(sizeof( capture_data_t ) );
    if( capture == NULL ) return NULL;
    capture->fd = capture_fd;

    if (-1 == xioctl(capture_fd, VIDIOC_QUERYCAP, &cap))
    {
        if (EINVAL == errno)
        {
            errno_exit("device is no V4L2 device");
        }
        else
        {
            errno_exit("VIDIOC_QUERYCAP");
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        errno_exit("device is no video capture device");
    }

    if (!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        errno_exit("device does not support streaming i/o");
    }

    /* Select video input, video standard and tune here. */

    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(capture_fd, VIDIOC_CROPCAP, &cropcap))
    {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(capture_fd, VIDIOC_S_CROP, &crop))
        {
            switch (errno)
            {
                case EINVAL:
                    /* Cropping not supported. */
                    errno_exit("Cropping not supported");
                    break;
                default:
                    /* Errors ignored. */
                    break;
            }
        }
    }
    else
    {
        /* Errors ignored. */
    }

    CLEAR(capture->fmt);

    capture->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    capture->fmt.fmt.pix.width       = 450;
    capture->fmt.fmt.pix.height      = 350;
    capture->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB32; //V4L2_PIX_FMT_YUYV;
    capture->fmt.fmt.pix.field       = V4L2_FIELD_NONE;

    if (-1 == xioctl(capture_fd, VIDIOC_S_FMT, &capture->fmt))
        errno_exit("VIDIOC_S_FMT");

    /* Buggy driver paranoia. */
    min = capture->fmt.fmt.pix.width * 2;
    if (capture->fmt.fmt.pix.bytesperline < min)
        capture->fmt.fmt.pix.bytesperline = min;
    min = capture->fmt.fmt.pix.bytesperline * capture->fmt.fmt.pix.height;
    if (capture->fmt.fmt.pix.sizeimage < min)
        capture->fmt.fmt.pix.sizeimage = min;

    //printf( "fmt.fmt.pix.bytesperline = %d\n", capture->fmt.fmt.pix.bytesperline );
    //printf( "fmt.fmt.pix.width = %d\n", capture->fmt.fmt.pix.width );
    //printf( "fmt.fmt.pix.height = %d\n", capture->fmt.fmt.pix.height );
    //printf( "fmt.fmt.pix.pixelformat = 0x%08x [%d]\n", capture->fmt.fmt.pix.pixelformat, capture->fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_XRGB32 );
    //printf( "fmt.fmt.pix.flags = 0x%04x\n", capture->fmt.fmt.pix.flags );

    return capture;
}

static void close_device(int capture_fd)
{
    if (-1 == close(capture_fd)) errno_exit("close");
}

static int open_device(const char * dev_name)
{
    struct stat st;
    int capture_fd;

    if (-1 == stat(dev_name, &st)) {
        printf("Cannot identify '%s': %d, %s\n", dev_name, errno, strerror(errno));
        //exit(EXIT_FAILURE);
        return -1;
    }

    if (!S_ISCHR(st.st_mode)) {
        printf("%s is no devicen", dev_name);
        //exit(EXIT_FAILURE);
        return -1;
    }

    capture_fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

    if (-1 == capture_fd) {
        printf("Cannot open '%s': %d, %s\n", dev_name, errno, strerror(errno));
        //exit(EXIT_FAILURE);
        return -1;
    }

    return capture_fd;
}

static void capture_thread( void * data )
{
    capture_data_t * capture = ( capture_data_t * )data;
    bool_t is_loop = capture->is_loop;

    while( is_loop )
    {
        mainloop(capture);

        tthread_mutex_lock( capture->mutex );
        is_loop = capture->is_loop;
        tthread_mutex_unlock( capture->mutex );
    }
}

void capture_stop( void * n_cap )
{
    capture_data_t * capture = ( capture_data_t * )n_cap;

    tthread_mutex_lock( capture->mutex );
    capture->is_loop = FALSE;
    tthread_mutex_unlock( capture->mutex );
    tthread_sleep_ms( 100 );

    stop_capturing(capture->fd);
    uninit_device(capture);
    close_device(capture->fd);

    free( capture );
}

void * capture_start( const char * dev, frame_hdl_t hdl, void * p_data )
{
    capture_data_t * capture;

    int capture_fd = open_device(dev);
    if( capture_fd == -1 ) return NULL;

    capture = init_device(capture_fd);
    if( capture == NULL ) return NULL;

    capture->mutex = tthread_mutex_init();
    capture->is_loop = TRUE;
    capture->frame_hdl = hdl;
    capture->p_data    = p_data;

    init_mmap(capture);
    start_capturing(capture);

    tthread_create_ex( capture_thread, capture );

    return capture;
}

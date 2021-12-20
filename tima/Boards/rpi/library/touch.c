#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#include "touch.h"

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////

int openTouchScreen()
{
    int fd;
    if ((fd = open("/dev/input/event1", O_RDONLY)) >= 0)
    {
       return fd;
    }

    return -1;
}

int getTouchSample(int fd, event_data_t * event)
{
    int i;
    size_t rb;
    struct input_event ev[64];
    int update = 0;

    rb=read(fd,ev,sizeof(struct input_event)*64);
    for (i = 0;  i <  (rb / sizeof(struct input_event)); i++)
    {
        if (ev[i].type ==  EV_SYN) update = 1;
        else if (ev[i].type == EV_KEY && ev[i].code == 330 && ev[i].value == 1) event->posz = 1;
        else if (ev[i].type == EV_KEY && ev[i].code == 330 && ev[i].value == 0) event->posz = 0;
        else if (ev[i].type == EV_ABS && ev[i].code == 0   && ev[i].value > 0 ) event->posx = ev[i].value;
        else if (ev[i].type == EV_ABS  && ev[i].code == 1  && ev[i].value > 0 ) event->posy = ev[i].value;
        else if (ev[i].type == EV_ABS  && ev[i].code == 24 && ev[i].value > 0 ) { }
    }

    return update;
}

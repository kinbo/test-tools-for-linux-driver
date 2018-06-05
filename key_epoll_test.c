#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/epoll.h>

int main()
{
	int fd0,fd1;	                 //按键句柄
	int fd_count = 0, epfd = 0;
	int i=0,j=0,readsize=0,cnt=0;
	struct epoll_event fd_event0,fd_event1;
	struct epoll_event epfd_event[2] = {0};
	struct input_event temp_buf[2] = {0};

	epfd = epoll_create1(0);	// 创建 epoll 句柄

	fd0 = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);

	fd_event0.data.fd = fd0;
    fd_event0.events = EPOLLET | EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd0, &fd_event0);		//epoll的事件注册

	fd1 = open("/dev/input/event1", O_RDONLY | O_NONBLOCK);

	fd_event1.data.fd = fd1;
    fd_event1.events = EPOLLET | EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd1, &fd_event1);

	while(1)
	{
		epoll_wait(epfd, epfd_event, 2, -1);	//等待事件的产生
		for (i=0;i<2;i++)
		{
			if(0 != epfd_event[i].events)
			{
				if(EPOLLIN & epfd_event[i].events)
				{
					readsize=read(epfd_event[i].data.fd, temp_buf, sizeof(struct input_event) * 2);
					cnt = readsize/sizeof(struct input_event);
					for(j=0; j<cnt; j++)
					{
						printf("buf[%d]=(%d,%d,%d,%d,%d)\n", j, temp_buf[j].code, temp_buf[j].type, temp_buf[j].value, (int)temp_buf[j].time.tv_sec, (int)temp_buf[j].time.tv_usec);
					}
				}
				printf("********************\n");
			}
		}
	}

    return 0;

}



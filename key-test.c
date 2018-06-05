#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define NOKEY 0

int main()
{
	int keys_fd;	                 //按键句柄	
	struct input_event t;
      
    keys_fd = open("/dev/input/event1", O_RDONLY);

	if(keys_fd<=0)
	{
        printf("open /dev/input/event1 device error!\n");
		return 0;
	}

	while(1)
	{	
       if(read(keys_fd,&t,sizeof(t))==sizeof(t))
	  {
		 if(t.type==EV_KEY)			//获取的是按键消息
		{
			while(t.value==1)
			{	
				sleep(1);
				printf("key %d Pressed \n",t.code,t.time);
			}
			if(t.value==0)    //返回值是1或者0
			    printf("key %d %s\n",t.code,(t.value)?"Pressed":"Released");     //1表按下，0表弹起
		}
	  }
		close(keys_fd);
	
        return 0;
	}
}


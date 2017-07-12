#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define POWER_KEY_START_EFFECT 10*60

int main()
{
	int keys_fd;	                 //按键句柄	


	struct input_event ev;
	int retval;
      
    keys_fd = open("/dev/input/event0", O_RDONLY);

	if(keys_fd<=0)
	{
                printf("open /dev/input/event0 device error!\n");
		return 0;
	}


	
	while(1)
	{	
		retval = read(keys_fd,&ev,sizeof(ev));
       if(retval == sizeof(ev)) 
	  {
		  printf("hjb type:%d,coe:%d,value:%d,time: %d\n",ev.type,ev.code,ev.value,ev.time.tv_sec);
		 if(ev.type==EV_KEY && ev.time.tv_sec > POWER_KEY_START_EFFECT)			//获取的是按键消息
		{
			
			if(ev.value==1)
			{	
				printf("key %d Pressed time: %d\n",ev.code,ev.time);
			}
			if(ev.value==0)    //返回值是1或者0
   			    printf("key %d %s, time:\n",ev.code,(ev.value)?"Pressed":"Released" ,ev.time);     //1表按下，0表弹起
  		}
	}
	}	
	close(keys_fd);
	
        return 0;

}


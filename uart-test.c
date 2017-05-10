#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <termios.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int speed_arr[] = {B4000000, B3500000, B3000000, B2500000, B2000000, B1500000, B921600, B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300};  
int name_arr[] =  {4000000,  3500000,  3000000,  2500000,  2000000,  1500000,  921600,  115200,  38400,  19200,  9600,  4800,  2400,  1200,  300}; 

void set_speed(int fd, int speed){  
  int   i;   
  int   status;   
  struct termios   Opt;  
  tcgetattr(fd, &Opt);   											//获取与终端相关的参数
  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {   
    if  (speed == name_arr[i]) {       
      tcflush(fd, TCIOFLUSH);       								//清空终端未完成的输入/输出请求及数据
      cfsetispeed(&Opt, speed_arr[i]);    							//设置终端输出波特率
      cfsetospeed(&Opt, speed_arr[i]);     							//设置终端输入波特率
      status = tcsetattr(fd, TCSANOW, &Opt);    					//设置终端参数，TCSANOW：立即改变
      if  (status != 0) {          
        perror("tcsetattr fd1");    
        return;       
      }      
      tcflush(fd,TCIOFLUSH);
	  printf("set baud success\n");
    }
  }  
}  
 
int main(int argc, char *argv[])  
{  
  
    int fd,res;   
    char buf[256] = {0};  
	char Ubuf[10]={0x55, 0x55};
	char send_buf[256] = {0};
	char device[256] = {0};
	int len;
	int baud_rate = 0;
	int opt = 0;
	int receive_flag = 0;
	int i;
	
	while (opt != -1)
	{
		/* Handle input parameters */
		opt = getopt(argc, argv, "b:rs:f:hp");	
		switch(opt)
		{
			case 'b':
				if (optarg)
				{
					baud_rate = atoi(optarg);
					printf("Trace: baud=%d\n", baud_rate);
				}
				else
				{
					printf("please enter baud rate\n");
					return -1;
				}
				break;
			case 'r':
				receive_flag = 1;
				break;
			case 's':
				receive_flag  = 0;			
				if (optarg)
				{
					strcpy(send_buf ,optarg);				
				}
				else
				{
					strcpy(send_buf ,Ubuf);
				}
				printf("send_buf=%s\n", send_buf);
				break;
			case 'f':
				if (optarg)
				{
					strcpy(device ,optarg);
					printf("Trace: device=%s\n", device);
				}
				else
				{
					printf("please enter tty device\n");
					return -1;
				}
				break;
			case 'h':
				goto help;
				break;
			case 'p':
				printf("Support baud rate:\n");
				for(i=0; i < sizeof(name_arr)/sizeof(name_arr[0]); i++)
					printf("%d\n", name_arr[i]);
				return 0;
			default:
				break;
		}	
	}	


    printf("Start...\n");  

    fd = open(device, O_RDWR | O_NOCTTY);  
  
    if (fd < 0) {  
        perror(device); 
        exit(1);  
    }  
  	
    printf("Open...\n");

    set_speed(fd, baud_rate); 
  
	if(0 == receive_flag)  
	{  
		printf("Sending...\n");

		len = write(fd, send_buf, strlen(send_buf));   
		if(len > 0)  
			printf(" %d send data successful\n",len);  
		else  
			printf("send data failed!\n");         
	}  
    else  
    {    
		printf("Reading...\n");  
		while(1) {  
			res = read(fd, buf, 255);  
	  
			if(res==0)  
				continue;  
			buf[res]=0;  
	  
			printf("%s", buf);  
			
			if (buf[0] == 0x0d)  
				printf("\n");  
			  
			if (buf[0] == '@') break;  
		}
	}
  
    printf("Close...\n");  
    close(fd);  
	return 0;
	
help:
	printf("Usage:\n \
send: %s  -b baud_rate(115200) -f /dev/ttyHS* -s send_data \n \
reveice: %s  -b baud_rate(115200) -f /dev/ttyHS* -r \n \
quiry baud rate: %s -p \n",argv[0], argv[0], argv[0]); 
    return 0;  
} 
/*

rtc_test -r
rtc_test -w2019 

w 后面跟(1900 - 2100)

write time: 2019-10-05, 02:30:15 

*/

#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int rtc_open()
{
	int fd, ret;

	fd = open("/dev/rtc0", O_RDWR, 0);   
	if (fd == -1)
	{
		perror("/dev/rtc0");
		exit(errno);
	}
	
	return fd;
}

void rtc_read(int fd)
{
	int ret;
	struct rtc_time rtc_tm;
	
	ret = ioctl(fd, RTC_RD_TIME, &rtc_tm);  //read the current timer
	if (ret == -1)
	{
		perror("rtc ioctl RTC_RD_TIME error");
	}
	printf("get RTC date/time is %d-%d-%d, %02d:%02d:%02d\n",
			rtc_tm.tm_year+1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,  
			rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	
	printf("rtc_tm.tm_year = %d\n", rtc_tm.tm_year);
	
}

void rtc_write(int fd)
{
	struct rtc_time rtc_tm;
	int ret;

/* 2019-10-05, 02:30:15 */
 	rtc_tm.tm_mday = 05;
	rtc_tm.tm_mon = 9;
	rtc_tm.tm_year = 119;
	rtc_tm.tm_hour = 2;
	rtc_tm.tm_min = 30;
	rtc_tm.tm_sec = 15;
        
	
	ret == ioctl(fd, RTC_SET_TIME, &rtc_tm);
	if (ret == -1)
	{
		perror("rtc ioctl RTC_SET_TIME error");
	}
	
	printf("set RTC date/time is %d-%d-%d, %02d:%02d:%02d\n",
			rtc_tm.tm_year+1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,  
			rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	
}

/* test write year */
void rtc_write_year(int fd, int year)
{
	struct rtc_time rtc_tm;
	int ret;
	
	year = year -1900;

/* year-10-05, 02:30:15 */
 	rtc_tm.tm_mday = 05;
	rtc_tm.tm_mon = 9;
	rtc_tm.tm_year = year;
	rtc_tm.tm_hour = 2;
	rtc_tm.tm_min = 30;
	rtc_tm.tm_sec = 15;
        
	
	ret == ioctl(fd, RTC_SET_TIME, &rtc_tm);
	if (ret == -1)
	{
		perror("rtc ioctl RTC_SET_TIME error");
	}
	
	printf("set RTC date/time is %d-%d-%d, %02d:%02d:%02d\n",
			rtc_tm.tm_year+1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,  
			rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	
}

void rtc_release(int fd)
{
	
	close(fd);
	
}

int main(int argc, char *argv[])  
{
	int opt = 0;
	int fd_rtc, ret, rtc_year;
	struct rtc_time rtc_tm;
	unsigned long data;
	
	fd_rtc = rtc_open();
	
	while (opt != -1)
	{
		opt = getopt(argc, argv, "rw::");	
		switch(opt)
		{
			case 'r':
				rtc_read(fd_rtc);
				break;
			case 'w':
				rtc_year = atoi(optarg);
				rtc_write_year(fd_rtc, rtc_year); //  rtc_write(fd_rtc);
				rtc_read(fd_rtc);
				break;

			default:
				break;
		}	
	}	
	
	rtc_release(fd_rtc);
	
    return 0;
}

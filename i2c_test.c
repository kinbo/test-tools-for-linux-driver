/*

i2c test

*/

#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define I2C_DEVICE	 "/dev/i2c-0"

static int slave = 0x30;  //the slave address

int main()
{
  int fd;
  int buffer[10] = {0};
  int i;

  printf("hello,this is i2c tester \n");

  if(fd =open(I2C_DEVICE, O_RDWR)<0)
  {
    printf("open i2c failed \n");
    return -1;
  }

  if (ioctl(fd, I2C_SLAVE_FORCE, slave) < 0)
  {
    printf("i2c: ioctl failed!\n");
    return -1;
  }

  memset(buffer, 0x5A, sizeof(buffer));

  for (i = 0; i < sizeof(buffer); i++)
  {
    write(fd, &buffer[i], sizeof(buffer[i]));
  }

  close(fd);
  
  return 0;
}
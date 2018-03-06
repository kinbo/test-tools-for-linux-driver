#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define EVENT_PATH "/dev/input/event0"
#define CODE_A 193
#define CODE_B 194

typedef struct {
    int code;
    int value;
}code_type;

#define A_LAST 1
#define B_LAST 0

#define KEYCODE_VOLUME_UP "input keyevent 24"
#define KEYCODE_VOLUME_DOWN "input keyevent 25"


/************
 *
 * Name:     fan_system_call
 *
 * Purpose:  Execute a shell command.
 *
 * Parms:    command
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int encoder_system_call(const char *command)
{
  int result = 0;
  FILE *stream = NULL;

  printf("encoder system call: %s\n\n", command);

  stream = popen(command, "w");

  if (stream == NULL)
  {
    printf("encoder system command failed!\n\n");
    result = -1;
  }
  else if(pclose(stream) < 0)
  {
    printf("encoder pclose command failed!\n\n");
    result = -1;
  }

  return result;
}

int main()
{
  int keys_fd;
  struct input_event kevent;
  code_type code_a_type ={0};
  code_type code_b_type ={0};
  unsigned int last_key_flag = 0;
  unsigned int event_times = 0;

  keys_fd = open(EVENT_PATH, O_RDONLY);

  if(keys_fd<=0)
  {
    printf("open event device error!\n");
    return 0;
  }

  while(1)
  {
    if(read(keys_fd,&kevent,sizeof(kevent))==sizeof(kevent))
    {
      if(kevent.type == EV_KEY)             //is key message
      {
        printf("encoder key %d %d\n", kevent.code, kevent.value);

        if(kevent.code == CODE_A)
        {
          last_key_flag = A_LAST;
          event_times ++;
          code_a_type.value = kevent.value;
        }

        if(kevent.code == CODE_B)
        {
          last_key_flag = B_LAST;
          event_times ++;
          code_b_type.value = kevent.value;
        }

        printf("encodr last_key_flag=%d,event_times=%d\n", last_key_flag, event_times);

        if(event_times == 2)
        {
          if(code_b_type.value != code_a_type.value)
          {
            event_times = 1;
            continue;
          }

          event_times = 0;

          if(last_key_flag == A_LAST)
          {
            encoder_system_call(KEYCODE_VOLUME_DOWN);
          }
          else if(last_key_flag == B_LAST)
          {
            encoder_system_call(KEYCODE_VOLUME_UP);
          }

        }
      }
    }
  }

  close(keys_fd);

  return 0;
}


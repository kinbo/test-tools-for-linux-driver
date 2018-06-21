/******************************************************************************
2018-06-21

led_three_color()：
	set color for RGB-LED

led_trigger_open():
	enable led twinkle, default twinkle frequency is 1Hz

led_triger_close():
	disable led twinkle

led_timer_set():
	set twinkle frequency, it should execute after led_trigger_open().

main():
	this function only for led test and you can refer the code to finish other requirement.

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>

#define BRIGHTNESS_MIN 0
#define BRIGHTNESS_MAX 255

typedef enum {
  COLOR_RED = 0,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_MAX
} color_enum;

/************
 *
 * Name:     media_system_call
 *
 * Purpose:  execute a shell command.
 *
 * Parms:    command
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int media_system_call(const char *command)
{
  int result = 0;
  FILE *stream = NULL;

  stream = popen(command, "w");

  if (stream == NULL)
  {
    printf("media_system_call: popen failed!\n");
    result = -1;
  }
  else if(pclose(stream) < 0)
  {
    printf("media_system_call: pclose failed!\n");
    result = -1;
  }

  return result;
}

/************
 *
 * Name:     led_get_color
 *
 * Purpose:  get led color string.
 *
 * Parms:    color:red(0),green(1),blue(2); color_str:'red','green','blue'
 *
 * Return:   None
 *
 * Notes:    None
 *
 ************/
static void led_get_color(color_enum color,char *color_str)
{
  switch(color)
  {
    case COLOR_RED:
      strcpy(color_str, "red");
      break;

    case COLOR_GREEN:
      strcpy(color_str, "green");
      break;

    case COLOR_BLUE:
      strcpy(color_str, "blue");
      break;

    default:
      break;
  }
}

/************
 *
 * Name:     led_brightness
 *
 * Purpose:  set led brightness.
 *
 * Parms:    color:red(0),green(1),blue(2);brightness_level:0~255.
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int led_brightness(color_enum color, int brightness_level)
{
  char cmd[128] = {0};
  int result = 0;
  char color_string[8] = {0};

  if((BRIGHTNESS_MAX < brightness_level) || (BRIGHTNESS_MIN > brightness_level))
  {
	printf("led_red: brightness_level error!\n");
	result = -1;
  }

  led_get_color(color, color_string);

  sprintf(cmd, "echo %d > /sys/class/leds/led-%s/brightness", brightness_level, color_string);

  if(media_system_call(cmd))
  {
    printf("led_red: system call failed!\n");
	result = -1;
  }

  return result;
}

/************
 *
 * Name:     led_three_color
 *
 * Purpose:  set three color.
 *
 * Parms:    red_brightness; green_brightness; blue_brightness.
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int led_three_color(int red_brightness, int green_brightness, int blue_brightness)
{
  int result = 0;

  if(led_brightness(COLOR_RED, red_brightness))
  {
    printf("led_three_color: red brightnessl failed!\n");
    result = -1;
  }

  if(led_brightness(COLOR_GREEN, green_brightness))
  {
    printf("led_three_color: green brightnessl failed!\n");
    result = -1;
  }

  if(led_brightness(COLOR_BLUE, blue_brightness))
  {
    printf("led_three_color: bule brightnessl failed!\n");
    result = -1;
  }

  return result;
}

/************
 *
 * Name:     led_trigger_open
 *
 * Purpose:  echo timer to trigger.
 *
 * Parms:    color:red(0),green(1),blue(2)
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int led_trigger_open(color_enum color)
{
  char cmd[128] = {0};
  int result = 0;
  char color_string[8] = {0};

  led_get_color(color, color_string);

  sprintf(cmd, "echo timer > /sys/class/leds/led-%s/trigger", color_string);

  if(media_system_call(cmd))
  {
    printf("led_red: system call failed!\n");
    result = -1;
  }

  return result;
}

/************
 *
 * Name:     led_triger_close
 *
 * Purpose:  echo none to trigger.
 *
 * Parms:    color:red(0),green(1),blue(2)
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    None
 *
 ************/
int led_triger_close(color_enum color)
{
  char cmd[128] = {0};
  int result = 0;
  char color_string[8] = {0};

  led_get_color(color, color_string);

  sprintf(cmd, "echo none > /sys/class/leds/led-%s/trigger", color_string);

  if(media_system_call(cmd))
  {
    printf("led_red: system call failed!\n");
    result = -1;
  }

  return result;
}

/************
 *
 * Name:     led_timer_set
 *
 * Purpose:  set delay_on and delay_off.
 *
 * Parms:    color:red(0),green(1),blue(2);on_time:delay_on(ms);off_time:delay_off(ms)
 *
 * Return:   0:success, -1: fail
 *
 * Notes:    this function need after led_trigger_open
 *
 ************/
int led_timer_set(color_enum color, int on_time, int off_time)
{
  char cmd_on[128] = {0};
  char cmd_off[128] = {0};
  int result = 0;
  char color_string[8] = {0};

  led_get_color(color, color_string);

  sprintf(cmd_on, "echo %d > /sys/class/leds/led-%s/delay_on", on_time, color_string);
  sprintf(cmd_off, "echo %d > /sys/class/leds/led-%s/delay_on", off_time, color_string);

  if(media_system_call(cmd_on))
  {
    printf("led_red: system call cmd_on failed!\n");
    result = -1;
  }

  if(media_system_call(cmd_off))
  {
    printf("led_red: system call cmd_off failed!\n");
    result = -1;
  }

  return result;
}

/************
 *
 * Name:     main
 *
 * Purpose:  main function
 *
 * Parms:    None
 *
 * Return:   None
 *
 * Notes:    we can refer the code to finish other requirement
 *
 ************/
void main(void)
{
  printf("led_test: red led 3s\n");
  led_three_color(0, 255, 255);//red led
  sleep(3);

  printf("led_test: green led 3s\n");
  led_three_color(255, 0, 255);//green led
  sleep(3);

  printf("led_test: blue led 3s\n");
  led_three_color(255, 255, 0);//blue led
  sleep(3);

  printf("led_test: white led 3s\n");
  led_three_color(0, 0, 0);//white led
  sleep(3);

  printf("led_test: yellow led 3s\n");
  led_three_color(0, 0, 255);//yellow led
  sleep(3);

  printf("led_test: red led 1Hz 5s\n");
  led_three_color(0, 255, 255);//red led
  led_trigger_open(0);//default 1Hz
  sleep(5);
  led_triger_close(0);

  printf("led_test: blue led 4Hz \n");
  led_three_color(255, 255, 0);//blue led
  led_trigger_open(2);
  led_timer_set(2, 125, 125);//4Hz
}



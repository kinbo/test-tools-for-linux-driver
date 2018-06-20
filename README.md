# test-tools-for-linux-driver
test tools for linux driver, e.g. key/gpio/uart 

###############################################

How to use these file 

1. use your gcc tool compile the file.
2. send the bin file to your device.
3. use the bin file in your device.


###############################################

uart-test：
Default stty in linux can't support some baud_rate.
This file can add the baud_rate that you want.

###############################################

devmem2.c:
you can use devmem to read and srite register.

###############################################

key-test.c and key-test-2.c and key_epoll_test.c

you can this file to test your key driver.

###############################################

gpio_test_bash.sh and gpio_test_sh.sh

This shell script can test lot size GPIO that you want test.

###############################################

pwm_fan_test.sh

we use two pwms to control two fans.
 
this shell script can control fan level.
 
###############################################

rotational_encoder_test.c

EC60B1520402 rotational encoder test(two input key)

use rotational encoder to control volume

###############################################

rotational_encoder_test-fail.sh

this is a fail shell to test EC60B1520402 rotational encoder.

just for information and warning.

###############################################

vocie_board_test.py

this python script can test fan led tinyplay that for hardware test.

we can use pyinstaller to produce exe program that run on windows.

###############################################

routerCheckToo.py

this python script base on vocie_board_test.py.

1. fan test on voice board

2. led test on voice board

3. tinyplay on voice board

4. ssh(LAN) test on master board

5. wifi test on master board

6. fdisk harddisk test on master board

7. fdisk USB test on master board

8. ZIGBEE test on master board

9. bluetooth test on master board

###############################################

rtc_test.c:

you can use rtc_test to read rtc time.

###############################################

gpio-test-number.sh:

test single gpio out or in

###############################################

i2c_test.c:

you can use this code to test i2c, but the better way is porting i2c-tools

###############################################

led_three_color.sh:

you can use this script to test thress-color led.

###############################################

mem_ps.sh:

this script can print the memery of pid

###############################################














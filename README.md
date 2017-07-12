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

devkmem:
you can use devmem to read and srite register.

###############################################

key-test:
you can this file to test your key driver.

###############################################

gpio_test.sh
This shell script can test lot size GPIO that you want test.
###############################################

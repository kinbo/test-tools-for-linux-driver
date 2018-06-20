#!/bin/sh
#===========================================================================


echo "Test gpio start"


echo $1 > /sys/class/leds/led-red/brightness
echo $2 > /sys/class/leds/led-green/brightness
echo $3 > /sys/class/leds/led-blue/brightness
#!/bin/sh
# $1: gpio_number
# $2: out or in
# $3: 0 or 1
#===========================================================================

gpio_num=$1

if [ ! -d "/sys/class/gpio/gpio${gpio_num}" ]
then
	echo $gpio_num > /sys/class/gpio/export
fi

echo $2 > /sys/class/gpio/gpio$gpio_num/direction

if [ "$2" == "out" ]
then
	if [ $3 == 1 -o $3 == 0 ]
	then

			echo "set gpio${gpio_num} value to ${3}"
			echo $3 > /sys/class/gpio/gpio$gpio_num/value
	else
		echo "$3 is unknow argument"
	fi
else
	echo "set gpio${gpio_num} input "
fi
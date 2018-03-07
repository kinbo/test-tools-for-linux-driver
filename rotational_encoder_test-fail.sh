#!/bin/sh
#Test ec60b in linux.
#Write by Kinbo.
#2018.02.06
#===========================================================================

echo "ec70b rotating button test"


if [ ! -d "/sys/class/gpio/gpio1034" ];then
  echo "export gpio1034,alias gpio1_a2, CODE_A"
  echo 1034 > /sys/class/gpio/export
else
  echo "gpio1034 has been export"
fi

if [ ! -d "/sys/class/gpio/gpio1035" ];then
  echo "export gpio1035,alias gpio1_a3, CODE_B"
  echo 1035 > /sys/class/gpio/export
else
  echo "pgpio1035 has been export"
fi

echo both > /sys/class/gpio/gpio1034/edge


irq_old=$(cat /proc/interrupts | grep 'gpio1   2' | busybox awk -F '[ ;]+' '{print $2}')

echo "irq_old:"$irq_old

while true; do
  irq_new=$(cat /proc/interrupts | grep 'gpio1   2' | busybox awk -F '[ ;]+' '{print $2}')
  
  if [ $irq_new -eq $irq_old ];then
    usleep 5000
    continue
  fi
  
  a_value=$(cat /sys/class/gpio/gpio1034/value)
  b_value=$(cat /sys/class/gpio/gpio1035/value)
  
  echo "CODE_A:"$a_value"CODE_B:"$b_value
  
  if [ a_value -eq b_value ];then
    echo "clockwise, increase the volume"
    input keyevent 24
  else
	echo "anticlockwise, decrease the volume"
    input keyevent 25
  fi
	
  irq_old=$irq_new
  
  echo "irq_number:"$irq_new 
  
#  usleep 1000
	
done





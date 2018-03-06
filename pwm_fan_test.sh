#!/bin/sh
#Test pwm 0/1 in linux.
#Write by Kinbo.
#2018.02.02
#===========================================================================

echo "pwm pan test"

case $1 in

	--h | -h | h  )
		echo "*****************************************************"
		echo "please input two parameters:"
		echo "         parameter 1:    0 or 1 "
		echo "         parameter 2:    0 to 100 "	
		echo "*****************************************************"
		exit 0
		;;
esac

if [ ! -d "/sys/class/pwm/pwmchip0/pwm0" ];then
  echo "export pwm0"
  echo 0 > /sys/class/pwm/pwmchip0/export
else
  echo "pwm0 has been export"
fi

if [ ! -d "/sys/class/pwm/pwmchip1/pwm0" ];then
  echo "export pwm1"
  echo 0 > /sys/class/pwm/pwmchip1/export
else
  echo "pwm1 has been export"
fi

echo 1000000000 > /sys/class/pwm/pwmchip0/pwm0/period
echo 1000000000 > /sys/class/pwm/pwmchip1/pwm0/period

echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable
echo 1 > /sys/class/pwm/pwmchip1/pwm0/enable

if [ ! -n "$1" ]; then
    echo "Please Enter parm1 and parm2"
    exit
fi

if [ ! -n "$2" ]; then
    echo "Please Enter parm2"
    exit
fi

if [ $1 -ne 0 -a $1 -ne 1 ];then
  echo parameter 1 need input 0 or 1
  exit 1
fi

if [ $2 -lt 0 -o $2 -gt 100 ];then
  echo "parameter 2 need input 0 to 100"
  exit 1
fi

value=$((100 - $2))

duty_value=$(expr $value \* 10000000)


echo "duty_value is:"
echo $duty_value


echo $duty_value > /sys/class/pwm/pwmchip$1/pwm0/duty_cycle





























































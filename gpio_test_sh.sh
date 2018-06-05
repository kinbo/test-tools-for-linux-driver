#!/bin/sh
#Test gpio out/in high/low in linux for sh instead of bash.
#Write by Kinbo.
#===========================================================================

lenGpio="496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511"

echo "Test gpio start"


case $1 in

	export     )
		echo " "
		for i in $lenGpio;
		do
			gpio_num=$i
			echo "export gpio${gpio_num}"
			echo $gpio_num > /sys/class/gpio/export
		done

		;;

	unexport   )
		echo " "
		i=0
		for i in $lenGpio;
		do
			gpio_num=$i
			echo "unexport gpio${gpio_num}"
			echo $gpio_num > /sys/class/gpio/unexport
			let i++
		done

		;;
	out | in  )
		echo " "
		for i in $lenGpio;
		do
			gpio_num=$i
			echo "direction ${1} gpio${gpio_num}"
			echo $1 > /sys/class/gpio/gpio$gpio_num/direction
		done


		;;
	read      )
		echo " "
		for i in $lenGpio;
		do
			gpio_num=$i
			echo "cat gpio${gpio_num} value:"
			cat /sys/class/gpio/gpio$gpio_num/value
		done


		;;
	--h | -h | h  )
		echo "*****************************************************"
		echo "arg type:"
		echo "         export:      export gpio "
		echo "         unexport:    unexport gpio "
		echo "         out 0:       output 0 "
		echo "         out 1:       output 1 "
		echo "         in:          input, direction is in "
		echo "         read:        read the gpio value "
		echo "         h:           help "
		echo "*****************************************************"
		;;
	*         )
		echo "unknown argument arg"
		;;
esac

if [ "$1" == "out" ]
then
	if [ $2 == 1 -o $2 == 0 ]
	then
		echo " "
		for i in $lenGpio;
		do
			gpio_num=$i
			echo "set gpio${gpio_num} value to ${2}"
			echo $2 > /sys/class/gpio/gpio$gpio_num/value
		done

	else
		echo "$2 is unknow argument"
	fi
fi
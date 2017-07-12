#!/bin/sh
#Test gpio out/in high/low in linux.Write by Kinbo.
#http://www.jb51.net/article/52382.htm shell 数组
#2016.12.16
#===========================================================================


gpio_idx=(1 2 3 4 6 7 8 9 10 13 14 25 26 34 35 47 48 49 50 M1 M2 M3 M4)

#no codec version
#gpio_idx=(1 2 3 4 6 7 8 9 10 11 12 13 14 25 26 34 35 47 48 49 50 M1 M2 M3 M4)

#MFT version
gpio_idx=(1 6 7 8 9 10 13 14)

lenGpio=${#gpio_idx[@]}
echo "Test gpio sum: ${lenGpio}"


case $1 in

	export     )
		echo " "
		for((i=0;i<$lenGpio;i++))
		do
			gpio_num=${gpio_idx[$i]}
			echo "export gpio${gpio_num}"
			echo $gpio_num > /sys/class/gpio/export
		done

		;;
		
	unexport   )
		echo " "
		i=0
		while [ $i -lt $lenGpio ]
		do
			gpio_num=${gpio_idx[$i]}
			echo "unexport gpio${gpio_num}"
			echo $gpio_num > /sys/class/gpio/unexport
			let i++
		done

		;;
	out | in  )
		echo " "
		for((i=0;i<$lenGpio;i++))
		do
			gpio_num=${gpio_idx[$i]}
			echo "direction ${1} gpio${gpio_num}"
			echo $1 > /sys/class/gpio/gpio$gpio_num/direction
		done 


		;;
	read      )
		echo " "
		for((i=0;i<$lenGpio;i++))
		do
			gpio_num=${gpio_idx[$i]}
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
		for((i=0;i<$lenGpio;i++))
		do
			gpio_num=${gpio_idx[$i]}
			echo "set gpio${gpio_num} value to ${2}"
			echo $2 > /sys/class/gpio/gpio$gpio_num/value
		done

	else
		echo "$2 is unknow argument"
	fi
fi



























































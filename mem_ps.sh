#!/bin/sh

PROCESSES=$(ls /proc/ | grep -E "^[0-9]+$" | sort -n)
MEM_USE_TOTAL=0

printf "%-20s %-10s %10s\n" "Name" "PID" "MEM"
for proc in $PROCESSES; do
	proc_name=$(cat /proc/$proc/status 2>/dev/null | grep Name | awk '{ print $2 }')
	mem_used=$(cat /proc/$proc/status 2>/dev/null | grep VmRSS | awk '{ print $2" "$3 }')

	[ -z "$mem_used" ] || [ ! -z $(echo "$0" | grep "$proc_name") ] || {
		printf "%-20s %-10d %10s\n" ${proc_name} ${proc} "${mem_used}"
		let MEM_USE_TOTAL=$MEM_USE_TOTAL+$(echo $mem_used | awk '{ print $1 }')
	}
done

echo "=========================================="
echo "Total memory used: $MEM_USE_TOTAL kB"

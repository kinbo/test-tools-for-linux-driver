'''
this program be used to test voice board 
1. fan test
2. led test

Write by Kinbo.
2018.03.01
'''

import os
import time
import subprocess

def fan_test():
	print "########## fan test start ##########"
	
	print "### close fan 0 and 1 ###"
	os.system('adb shell hd_fan_test 0 0')
	os.system('adb shell hd_fan_test 1 0')
	time.sleep(3)
	
	print "### open fan 0 and 1 ###"
	os.system('adb shell hd_fan_test 0 4')
	os.system('adb shell hd_fan_test 1 4')
	time.sleep(10)
	
	print "### close fan 0 and 1 ###"
	os.system('adb shell hd_fan_test 0 0')
	os.system('adb shell hd_fan_test 1 0')
	
	print "########## fan test end ##########"
	
def led_test():
	print "########## led test start ##########"

	os.system('adb shell killall hd_led_test')
	time.sleep(1)
	
	print "### run hd_led_test  ###"
	led_pid = subprocess.Popen('adb shell hd_led_test', shell=True)

	time.sleep(10)
	
	print "### kill hd_led_test ###"
	led_pid.kill()
	
	print "########## led test end   ##########"
	
def tinyplay_test():
	print "########## tinyplay test start ##########"
	
	print "### push wav  ###"
	os.system('adb push 1.wav /data')
	time.sleep(1)
	
	print "### tinyplay wav ###"
	os.system('adb shell tinyplay /data/1.wav')
	time.sleep(1)
	
	print "########## tinyplay test end ##########"

def vocie_borad():
	os.system('adb root')
	time.sleep(2)
	
	fan_test()
	led_test()
	tinyplay_test()
	
	raw_input('--------------------------------------------')
	
if __name__ == "__main__":
    vocie_borad()
	

'''
this program be used to test 
1. fan test on voice board
2. led test on voice board
3. tinyplay on voice board
4. ssh(LAN) test on master board
5. wifi test on master board
6. fdisk harddisk test on master board
7. fdisk USB test on master board
8. ZIGBEE test on master board
9. bluetooth test on master board

'''

import paramiko
import threading
import os
import time
import subprocess
import sys

username = 'root'
pwdwzb210 = 'testchange'
ip = '192.168.10.1'
max_vap_count = 7
max_sda_count = 1

def fan_test():
    print "########## fan test start ##########"
	
    print "### close fan 0 ###"
    os.system('adb shell hd_fan_main 0 0')
    time.sleep(3)
	
    print "### open fan 0 ###"
    os.system('adb shell hd_fan_main 0 4')
    time.sleep(10)
	
    print "### close fan 0 ###"
    os.system('adb shell hd_fan_main 0 0')
	
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
    os.system('adb push test.wav /data')
    time.sleep(1)

    os.system('adb shell tinyplay /data/test.wav')
    time.sleep(1)
	
    print "########## tinyplay test end ##########"

def vocie_borad():
    os.system('adb kill-server')
    os.system('adb root')
    time.sleep(3)
	
    fan_test()
    led_test()
    tinyplay_test()
	
    #raw_input('--------------------------------------------\n')

def print_msg(flag):    
    if flag == 0:                        
        #print '\n'
        print '********************************'
        print '*        router check OK       *'
        print '********************************\n'
    else:                        
        #print '\n'
        print '********************************'
        print '*        router check fail     *'
        print '********************************\n'

def ssh2(ip,username,passwd):
    check_fail = 0
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(ip,22,username,passwd,timeout=5)
            
        print '\nLogin %s:22 sucussful..'%(ip)

        cmd = 'iwconfig 2>/dev/null | grep "Bit Rate" | wc -l'
        #print 'cmd=%s\n'%(cmd)
        stdin, stdout, stderr = ssh.exec_command(cmd)
        out = stdout.readlines()
        num = out[0]
        #print num
        if int(num) < max_vap_count:
            print "Check wifi fail."
            #ssh.close()
            #print_msg(1)
            #return 1
            check_fail = 1
        else:
            print "Check wifi success."

        cmd = 'fdisk -l | grep sda 2>/dev/null | wc -l'
        #print 'cmd=%s\n'%(cmd)
        stdin, stdout, stderr = ssh.exec_command(cmd)
        out = stdout.readlines()
        num = out[0]
        #print num
        if int(num) < max_sda_count:
            print "Check harddisk fail."
            #ssh.close()
            #print_msg(1)
            #return 1
            check_fail = 1
        else:
            print "Check harddisk success."

        cmd = 'fdisk -l | grep sdb 2>/dev/null | wc -l'
        #print 'cmd=%s\n'%(cmd)
        stdin, stdout, stderr = ssh.exec_command(cmd)
        out = stdout.readlines()
        num = out[0]
        #print num
        if int(num) < max_sda_count:
            print "Check USB fail."
            #ssh.close()
            #print_msg(1)
            #return 1
            check_fail = 1
        else:
            print "Check USB success."

        cmd = '[ -f /etc/system/zigbee_info ] && echo "1" || echo "0"'
        #print 'cmd=%s\n'%(cmd)
        stdin, stdout, stderr = ssh.exec_command(cmd)
        out = stdout.readlines()
        num = out[0]
        #print num
        if int(num) != 1:
            print "Check zigbee fail."
            #ssh.close()
            #print_msg(1)
            #return 1
            check_fail = 1
        else:
            print "Check zigbee success."

        cmd = 'hcitool lepair 2>/dev/null | grep failed | wc -l'
        #print 'cmd=%s\n'%(cmd)
        stdin, stdout, stderr = ssh.exec_command(cmd)
        out = stdout.readlines()
        num = out[0]
        #print num
        if int(num) == 0:
            print "Check bluetooth success."
        else:
            print "Check bluetooth fail."
            #ssh.close()
            #print_msg(1)
            #return 1
            check_fail = 1
            
        print_msg(check_fail)
        ssh.close()
        return check_fail
    except :
        print '%s\t %s\t %s\t Login Error,return!!\n'%(ip,username,passwd)
        print_msg(1)
        return 1
	
if __name__ == "__main__":
    #thd = threading.Thread(target=ssh2,args=(ip, username, pwdwzb210))
    #thd.start()
    while 1:
        ret = ssh2(ip,username,pwdwzb210)
        time.sleep(1)
		
        vocie_borad()

        t = raw_input("Input any key to continue(q:to quit):")
        if t.lower() == "q" or t.lower() == "quit":
            print "Bye"
            sys.exit()
	

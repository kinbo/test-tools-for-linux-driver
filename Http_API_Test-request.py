#coding=utf8

import requests
from collections import OrderedDict
import json, ast
import random
import datetime

url='http://192.168.10.1/cgi-bin/test1'
global tokenparam
tokenparam = ''

###################################


#路由器密码设置
def setRouterPassword():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "setRouterPassword","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"password": 12345678,"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#路由器密码验证
def verifyRouterPassword():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "verifyRouterPassword","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"password": 12345678,"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

###################################
	
#V1.1.8 获查看接入设备列表-58
def get_device_list():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "getDeviceList","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

	
#V1.1.8 修改接入设备名称-59
def set_device_name():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "setDeviceName","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"mac":"ec:d0:9f:a7:35:4d","device_name":"kinbo-mi-changed","token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#V1.1.8 设置接入设备限速-61
def set_device_speed_limit():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "setDeviceSpeedLimit","req_id": '+str(num)+',"timestamp": 1498111457196,"params":{"mac":"ec:d0:9f:a7:35:4d","up_limit_speed":12345,"down_limit_speed":54321,"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)
	
	
#V1.1.8 获取路由器黑名单信息-62
def get_blacklist_info():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "getRouterBlackList","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#V1.1.8 主机添加黑名单-63
def add_blacklist_info():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "setRouterBlackList","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"list":[{"mac":"ec:d0:9f:a7:35:4d","is_black":1},{"mac":"6c:4d:73:6f:43:1a","is_black":1}],"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#V1.1.8 主机从黑名单删除-64
def del_blacklist_info():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "setRouterBlackList","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"list":[{"mac":"ec:d0:9f:a7:35:4d","is_black":0},{"mac":"6c:4d:73:6f:43:1a","is_black":0}],"token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)
	
#V1.1.8 速率上报-mi-65
def device_speed_upload():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "subscribe","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"family_id": 1,"mode": "on","device_mac":["ec:d0:9f:a7:35:4d"],"subject": "dm_report_device_speed","token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#V1.1.8 速率上报-pc-66
def device_speed_upload_pc():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "subscribe","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"family_id": 1,"mode": "on","device_mac":["00:e0:4c:68:23:62"],"subject": "dm_report_device_speed","token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)
	
#V1.1.8 速率上报-two-mac-67
def device_speed_upload_two_mac():
    global tokenparam
    num=random.randint(100, 9999999)
    msg_on = ('{"method": "subscribe","req_id": '+str(num)+',"timestamp": 1498111457196,"params": {"family_id": 1,"mode": "on","device_mac":["00:e0:4c:68:23:62","ec:d0:9f:a7:35:4d"],"subject": "dm_report_device_speed","token":"%s"}}'%tokenparam)
    print msg_on+ "\r\n"
    return str(msg_on)

#发送http消息
def testapi(jsonstr):
    sendtime=datetime.datetime.now()
    WriteToFile('Log_HttpMsgs.txt',str(sendtime) +"     message sended： " +str(jsonstr) + "\r\n")
    headers = {}
    req = requests.post(url, headers=headers, data=jsonstr)
    jsontext=req.text
    print "received： "+str(jsontext)+ "\r\n"
    
    rectime=datetime.datetime.now()
    WriteToFile('Log_HttpMsgs.txt',str(rectime) +"     message received： " +str(jsontext) + "\r\n")

#发送http消息
def testapiPassword(jsonstr):
    global tokenparam
    sendtime=datetime.datetime.now()
    WriteToFile('Log_HttpMsgs.txt',str(sendtime) +"     message sended： " +str(jsonstr) + "\r\n")
    headers = {}
    req = requests.post(url, headers=headers, data=jsonstr)
    jsontext=req.text
    print "received： "+str(jsontext)+ "\r\n"
    
    load_json=json.loads(jsontext)
    tokenparam=load_json["result"]["token"]
	
    rectime=datetime.datetime.now()
    WriteToFile('Log_HttpMsgs.txt',str(rectime) +"     message received： " +str(jsontext) + "\r\n")

#写入日志
def WriteToFile(filename, data):
	# filename: Full path to file
	# data: data to be written to the szFile
	f = file(filename, 'a')
	f.write(data)
	f.close()


def main():
    #testapi()
    sendtime=datetime.datetime.now()
    a = input("请选择测试类型 \n\
3.路由器密码设置\n\
58.查看接入设备列表\n\
59.修改接入设备名称\n\
61.设置接入设备限速\n\
62.获取路由器黑名单信息\n\
63.主机添加黑名单\n\
64.主机从黑名单删除\n\
65.设备速率上报-mi\n\
66.设备速率上报-pc\n\
67.设备速率上报-two-mac\n\
请输入：".decode('utf-8').encode('gbk'))
    if(a==3):
        testapi(setRouterPassword())
        main() 
    elif(a==58):
        testapiPassword(verifyRouterPassword())
        testapi(get_device_list())
        main()
    elif(a==59):
        testapiPassword(verifyRouterPassword())
        testapi(set_device_name())
        main()
    elif(a==61):
        testapiPassword(verifyRouterPassword())
        testapi(set_device_speed_limit())
        main()
    elif(a==62):
        testapiPassword(verifyRouterPassword())
        testapi(get_blacklist_info())
        main()
    elif(a==63):
        testapiPassword(verifyRouterPassword())
        testapi(add_blacklist_info())
        main()
    elif(a==64):
        testapiPassword(verifyRouterPassword())
        testapi(del_blacklist_info())
        main()
    elif(a==65):
        testapiPassword(verifyRouterPassword())
        testapi(device_speed_upload())
        main()
    elif(a==66):
        testapiPassword(verifyRouterPassword())
        testapi(device_speed_upload_pc())
        main()
    elif(a==67):
        testapiPassword(verifyRouterPassword())
        testapi(device_speed_upload_two_mac())
        main()
        
main()

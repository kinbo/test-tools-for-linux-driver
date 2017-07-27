# $language = "python"
# $interface = "1.0"
# write by kinbo 2017-07-27

def Main():
  
	crt.Screen.Synchronous = True
	crt.Screen.IgnoreEscape = True		#不会获取特殊字符

	#EXT_GPIO 1, 2, 3, 4, 6, 7, 8, 9,10,13,14,25,26,34,35,47,48,49,50
	array = (15,14,13,12,16,17,43,49,50,37,36,26,44,11,10,51,25,58,38)
	
	pm_array = (1,2,3,4)

	conf = crt.OpenSessionConfiguration("serial-com3")
	objTab = conf.ConnectInTab()
	
	while True:	
		SwitchKey = crt.Screen.WaitForStrings(["ATGOUT 1","ATGOUT 0","ATGIN","ATGCAT"],4)

#******************************GPIO OUT 1'******************************
		if SwitchKey == 1:
			for i in array:
				objTab.Screen.Send("AT!BSGPIO=" + str(i) + ",1" + "\r\n")
				objTab.Screen.WaitForString("OK")
			
			for i in pm_array:
				objTab.Screen.Send("AT!PMGPIO=" + str(i) + ",1,1" + "\r\n")
				objTab.Screen.WaitForString("OK")

#******************************GPIO OUT 0'******************************
		if SwitchKey == 2:
			for i in array:
				objTab.Screen.Send("AT!BSGPIO=" + str(i) + ",0" + "\r\n")
				objTab.Screen.WaitForString("OK")
			
			for i in pm_array:
				objTab.Screen.Send("AT!PMGPIO=" + str(i) + ",1,0" + "\r\n")
				objTab.Screen.WaitForString("OK")

#******************************GPIO IN '******************************
		if SwitchKey == 3:
			for i in array:
				objTab.Screen.Send("AT!BSGPIO=" + str(i) + ",2" + "\r\n")
				objTab.Screen.WaitForString("OK")
			
			for i in pm_array:
				objTab.Screen.Send("AT!PMGPIO=" + str(i) + ",0" + "\r\n")
				objTab.Screen.WaitForString("OK")

#******************************GPIO OUT 1'******************************
		if SwitchKey == 4:
			for i in array:
				objTab.Screen.Send("AT!BSGPIO?" + str(i) + "\r\n")
				objTab.Screen.WaitForString("OK")
			
			for i in pm_array:
				objTab.Screen.Send("AT!PMGPIO?" + str(i) + "\r\n")
				objTab.Screen.WaitForString("OK")				



Main()

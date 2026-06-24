"""
y, 2022.7.8
win32com - multiple instances.py
https://stackoverflow.com/questions/51728428/how-can-i-create-multiple-application-instances-in-pythoncom
https://timgolden.me.uk/python/win32_how_do_i/start-a-new-com-instance.html
"""

import win32com.client
import ctypes


assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32 bit python'

# start first instance
exl1 = win32com.client.DispatchEx("Excel.Application")

# start second instance
exl2 = win32com.client.DispatchEx("Excel.Application")

exl1.Visible = True
exl2.Visible = True


import time

time.sleep(5)


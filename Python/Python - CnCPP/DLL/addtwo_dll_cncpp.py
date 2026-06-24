# -*- coding: utf-8 -*-
"""
Created on Sat Jan 30 23:47:36 2016

@author: user
"""

import ctypes

# add=cdll.loadlibrary('./addtwo/bin/Release/addtwo.dll')
add = ctypes.WinDLL(r'.\addtwo_dll_cncpp\bin\Release\addtwo_dll_cncpp.dll')
print("add=", add)
a = 2
b = 4
print("a=", a, "b=", b)
print("print(add[1](a,b))=", add[1](a, b))
print('print(add["addtwo@8"](a,b))=', add["addtwo@8"](a, b))

import _ctypes

_ctypes.FreeLibrary(add._handle)

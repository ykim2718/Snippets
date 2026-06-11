# -*- coding: utf-8 -*-
"""
Created on Sat Jan 30 23:47:36 2016

@author: user
"""

from ctypes import byref, cdll, c_int

# add=cdll.loadlibrary('./addtwo/bin/Release/addtwo.dll')
add = cdll.loadlibrary(
    r'd:\늑대\Homo academicus\yStudy on code - Python\Python with fortran\addtwo\bin\Release\addtwo.dll')
a = c_int(2)
b = c_int(4)
# print add.addtwo_(byval(a),byval(b))

"""
y, 2022.10.18
ctypes - load dll.py
https://ryanclaire.blogspot.com/2020/08/python-ctypes-loadlibrary-windows-dll.html
"""

import ctypes

ctypes.windll.loadLibrary(name)
ctypes.oledll.loadLibrary(name)

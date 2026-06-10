"""
y, 2022.10.26
ctypes - printf.py
"""

import ctypes

msvcrt = ctypes.CDLL('msvcrt')
printf = msvcrt.printf
printf(b"Hello .. printf()")
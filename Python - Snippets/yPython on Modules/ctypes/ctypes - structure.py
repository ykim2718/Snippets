"""
y, 2022.10.26
ctypes - structure.py
https://sdr1982.tistory.com/212
https://www.youtube.com/watch?v=SnEtWSZyBkY  ★
"""

import ctypes

msvcrt = ctypes.CDLL('msvcrt')


class tm(ctypes.Structure):
    _fields_ = [
        ('tm_sec', ctypes.c_int),
        ('tm_min', ctypes.c_int),
        ('tm_hour', ctypes.c_int),
        ('tm_mday', ctypes.c_int),
        ('tm_mon', ctypes.c_int),
        ('tm_year', ctypes.c_int),
        ('tm_wday', ctypes.c_int),
        ('tm_yday', ctypes.c_int),
        ('tm_isdst', ctypes.c_int),
    ]


localtime = msvcrt.localtime
localtime.argtypes = [ctypes.POINTER(ctypes.c_int)]
localtime.restype = ctypes.POINTER(tm)

asctime = msvcrt.asctime
asctime.argtypes = [ctypes.POINTER(tm)]
asctime.restype = ctypes.c_char_p

timer = ctypes.c_int(12345678)
print(f"{asctime(localtime(ctypes.byref(timer)))=}")
# asctime(localtime(ctypes.byref(timer)))=b'Sun May 24 06:21:18 1970\n'


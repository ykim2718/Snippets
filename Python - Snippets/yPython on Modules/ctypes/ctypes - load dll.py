"""
y, 2022.10.18 - 19
ctypes - load dll.py
https://ryanclaire.blogspot.com/2020/08/python-ctypes-loadlibrary-windows-dll.html
https://docs.python.org/ko/3/library/ctypes.html
https://www.programcreek.com/python/example/1243/ctypes.c_char_p
"""

import ctypes

assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32bit python'

file_path = r"c:\y\eBEST\xingAPI\xingAPI\xingAPI.dll"
my_dll = ctypes.windll.LoadLibrary(file_path)
# my_dll = ctypes.oledll.LoadLibrary(file_path)

from ctypes import WINFUNCTYPE, c_bool, c_int, c_int32, c_double, c_char_p, c_wchar_p
from ctypes.wintypes import HWND, LPCWSTR, UINT, BOOL


def c_str(string, encode='utf-8'):
    return ctypes.c_char_p(string.encode(encode))


prototype = WINFUNCTYPE(HWND, c_char_p, c_char_p, c_char_p, c_int, c_bool)
paramflags = (1, 'pszID', 'un'), (1, 'pszPwd', 'p1'), (1, 'pszCertPwd', 'p2'), (1, 'nType', 0),\
             (1, 'bShowCertErrDlg', True)
login = prototype(('ETK_Login', my_dll), paramflags)
print(f"{login=}")  # 0이 아니면 로그인 성공이 아니라 서버로 로그인 요청 전송 성공을 의미

is_connected = my_dll['ETK_IsConnected']
print(f"{is_connected()=}")
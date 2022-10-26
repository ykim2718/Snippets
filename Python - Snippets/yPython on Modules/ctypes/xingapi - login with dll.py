"""
y, 2022.10.18 - 26
xingapi - login with dll.py
https://ryanclaire.blogspot.com/2020/08/python-ctypes-loadlibrary-windows-dll.html
https://docs.python.org/ko/3/library/ctypes.html
https://www.programcreek.com/python/example/1243/ctypes.c_char_p
https://tinytools.tistory.com/2  >> dll_export_viewer
IXingApi.h
    BOOL IXingAPI::Login(HWND hWnd, LPCTSTR pszID, LPCTSTR pszPwd, LPCTSTR pszCertPwd, int nType, BOOL bShowCertErrDlg)
https://ghts.tistory.com/23
    초기화 과정에서 LoadLibrary() 호출은 반드시 Xing API DLL 파일이 존재하는 디렉토리에서 해야 한다.
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=youhavegot&logNo=110169723670
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32bit python'
import socket
import pathlib
import os

ip_address = socket.gethostbyname(socket.gethostname())
if ip_address.startswith('192'):  # home
    dll_path = r"c:\y\eBEST\xingAPI\xingAPI\xingAPI.dll"
    db_uri = 'mongodb://localhost:27017/yFDefine'
else:  # office
    dll_path = r"c:\y\eBEST\xingAPI\xingAPI.dll"
    db_uri = 'mongodb://10.163.130.184:27117/yFDefine'
print(f"{ip_address=}")
print(f"{db_uri=}")

server_ip = 'hts.ebestsec.co.kr'
server_port = 20001

xingAPI_folder = pathlib.Path(dll_path).parent
os.chdir(str(xingAPI_folder))
print(f"{pathlib.Path.cwd()=}")

# my_dll = ctypes.cdll.LoadLibrary(dll_path)  # cdecl
my_dll = ctypes.windll.LoadLibrary(dll_path)  # stdcall
# my_dll = ctypes.oledll.LoadLibrary(dll_path)  # stdcall

from ctypes import WINFUNCTYPE, CFUNCTYPE, PYFUNCTYPE, c_bool, c_int, c_int32, c_double, c_char_p, c_wchar_p
from ctypes.wintypes import HWND, PCHAR, LPSTR, LPCSTR, LPCWSTR, INT, UINT, BOOL


def c_str(string, encode='utf-8'):
    return ctypes.c_char_p(string.encode(encode))


if False:
    un = 'un'
    p1 = 'p1'
    p2 = 'p2'
else:
    from y.db import yMongo
    from finance.define import yMyKey
    y = yMongo.MongoEx(uri=db_uri)
    keys = yMyKey.keys(y, 'ebest', 'measure1')
    keys = [yMyKey.decrypt(key) for key in keys]
    print(f"{keys=}")
    un, p1, p2, *_ = keys

# connect
evaluation = 4
print(f"{evaluation=} to connect ".ljust(32, '-'))
if evaluation == 1:
    connect = my_dll['ETK_Connect']
    print(f"{connect()=}")
elif evaluation == 2:
    connect = my_dll['ETK_Connect']
    print(f"{connect()=}")
    get_server_name = my_dll['ETK_GetServerName']
    # get_server_name.restype = ctypes.c_wchar_p
    print(f"{get_server_name()=}")  # FIXME !!! OSError: exception: access violation reading 0x00000034
    #   OSError: exception: access violation writing 0x613FE60F
elif evaluation == 3:
    prototype = WINFUNCTYPE(c_int, HWND, LPCWSTR, INT, INT, INT, INT)
    paramflags = (1, 'hWnd', 0), (1, 'pszSvrIP', server_ip), (1, 'nPort', server_port), (1, 'nStartMsgID', 0), \
                 (1, 'nTimeOut', 100), (1, 'nSendMaxPacketSize', 999)
    connect = prototype(('ETK_Connect', my_dll), paramflags)
    print(f"{connect()=}")
    # prototype = WINFUNCTYPE(ctypes.POINTER(LPCWSTR * 256),)
    prototype = WINFUNCTYPE(ctypes.c_wchar_p,)
    # prototype = WINFUNCTYPE(ctypes.c_void_p,)
    # prototype = WINFUNCTYPE(LPCWSTR,)
    paramflags = ()
    get_server_name = prototype(('ETK_GetServerName', my_dll), paramflags)
    # get_server_name.restype = LPCWSTR
    print(f"{get_server_name()=}")  # FIXME !!! OSError: exception: access violation reading 0x00656C68
elif evaluation == 4:
    connect = my_dll.ETK_Connect
    connect.argtypes = [HWND, LPCSTR, INT, INT, INT, INT]
    connect.restype = ctypes.c_int
    print(f"{connect(0, c_str(server_ip), server_port, 0, 100, 999)=}")
    get_server_name = my_dll.ETK_GetServerName
    get_server_name.argtypes = []
    get_server_name.restype = ctypes.c_char_p
    server_name = get_server_name()  # FIXME !!! OSError: exception: access violation reading 0x00000016
    print(f"{server_name=}")

# login
evaluation = 3
print(f"{evaluation=} to login ".ljust(32, '-'))
if evaluation == 1:
    login = my_dll['ETK_Login']
    print(f"{login(None, un, p1, p2, 0, True)=}")  # not working
    print(f"{login(un, p1, p2)=}")  # not working
elif evaluation == 2:
    prototype = WINFUNCTYPE(c_int, HWND, c_char_p, c_char_p, c_char_p, c_int, c_bool)
    paramflags = (1, 'hWnd', 0), (1, 'pszID', un), (1, 'pszPwd', p1), (1, 'pszCertPwd', p2), (1, 'nType', 0),\
                 (1, 'bShowCertErrDlg', True)
    paramflags = (1, 'hWnd', 0), (1, 'pszID', c_str(un)), (1, 'pszPwd', c_str(p1)), (1, 'pszCertPwd', c_str(p2)), \
                 (1, 'nType', 0), (1, 'bShowCertErrDlg', 0)
    login = prototype(('ETK_Login', my_dll), paramflags)
    print(f"{login()=}")  # 0 로그인요청 전송실패, 1 요청성공
    print(f"{login(*[p[-1] for p in paramflags])=}")  # not working
elif evaluation == 3:
    prototype = WINFUNCTYPE(BOOL, HWND, LPCWSTR, LPCWSTR, LPCWSTR, INT, BOOL)
    paramflags = (1, 'hWnd', 0), (1, 'pszID', un), (1, 'pszPwd', p1), (1, 'pszCertPwd', p2), (1, 'nType', 0), \
                 (1, 'bShowCertErrDlg', True)
    login = prototype(('ETK_Login', my_dll), paramflags)
    print(f"{login(pszID=un, pszPwd=p1, pszCertPwd=p2)=}")  # 0

# confirm
is_connected = my_dll['ETK_IsConnected']
print(f"{is_connected()=}")


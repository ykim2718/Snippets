"""
y, 2022.10.18 - 27
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
DlgLogin.cpp
    // 서버접속
    BOOL bResult = g_iXingAPI.Connect(
		AfxGetMainWnd()->GetSafeHwnd(),	 Connect가 된 이후에 Disconnect 메시지를 받을 윈도우 Handle
										 Login 윈도우는 Login 만 처리하는 윈도우 이므로 Disconnect는 메인윈도우에서 받는다.
		strServerIP,					 서버주소
		nServerPort,					 서버포트
		WM_USER,						 XingAPI에서 사용하는 메시지의 시작번호, Windows에서는 사용자메시지를 0x400(=WM_USER) 이상을
										 사용해야 함. 기본적으로는 WM_USER를 사용하면 되지만 프로그램 내부에서 메시지 ID가 겹치게 되면
										 이 값을 조정하여 메시지 ID 충돌을 피할수 있음
		nConnectTimeOut,				 지정한 시간이상(1/1000 초 단위)으로 시간이 걸리게 될 경우 연결실패로 간주함
		nSendPacketSize					 보내어지는 Packet Size, -1 이면 기본값 사용
										 인터넷 공유기등에서는 특정 크기 이상의 데이터를 한번에 보내면 에러가 떨어지는 경우가 발생
										 이럴 경우에 한번에 보내는 Packet Size를 지정하여 그 이상 되는 Packet은 여러번에 걸쳐 전송
	);
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32bit python'
import socket
import pathlib
import os

ip_address = socket.gethostbyname(socket.gethostname())
if ip_address.startswith('192'):  # home
    dll_path = r"c:\y\eBEST\xingAPI\xingAPI\xingAPI.dll"
    db_uri = 'mongodb://localhost:27017'
else:  # office
    dll_path = r"c:\y\eBEST\xingAPI\xingAPI.dll"
    db_uri = 'mongodb://10.163.130.184:27117'
print(f"{ip_address=}")
print(f"{dll_path=}")
print(f"{db_uri=}")

server_ip = 'hts.ebestsec.co.kr'
server_port = 20001

xingAPI_folder = pathlib.Path(dll_path).parent
os.chdir(str(xingAPI_folder))
print(f"{pathlib.Path.cwd()=}")

# my_dll = ctypes.cdll.LoadLibrary(dll_path)  # cdecl
my_dll = ctypes.windll.LoadLibrary(dll_path)  # stdcall  << refer to IXingAPI.h
# my_dll = ctypes.oledll.LoadLibrary(dll_path)  # stdcall

from ctypes import WINFUNCTYPE, CFUNCTYPE, PYFUNCTYPE, c_bool, c_int, c_int32, c_double, c_char_p, c_wchar_p
from ctypes.wintypes import HWND, PCHAR, LPSTR, LPCSTR, LPCWSTR, INT, UINT, BOOL


def c_str(string, encode='utf-8'):
    return ctypes.c_char_p(string.encode(encode))
    # return string.encode(encode)


if False:
    un = 'un'
    p1 = 'p1'
    p2 = 'p2'
else:
    from y.db import yMongo
    from finance.define import yMyKey
    y = yMongo.MongoEx(uri=db_uri)
    keys = yMyKey.get_keys(server='ebest', field='user.measure1.keys')
    keys = yMyKey.decrypt(keys)
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
    paramflags = (1, 'hWnd', 0), (1, 'pszSvrIP', server_ip), (1, 'nPort', server_port), (1, 'nStartMsgID', 1024), \
                 (1, 'nTimeOut', 1000), (1, 'nSendMaxPacketSize', -1)
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
    # connect.argtypes = [HWND, LPCSTR, INT, INT, INT, INT]
    connect.argtypes = [HWND, ctypes.c_wchar_p, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    connect.restype = ctypes.c_int
    print(f"{connect(0, c_str(server_ip), server_port, 1024, 1000, -1)=}")
    if False:
        get_client_ip = my_dll.ETK_GetClientIP
        get_client_ip.argtypes = [ctypes.c_char_p]  # ctypes.c_wchar_p
        get_client_ip.restype = ctypes.c_int
        buffer = ctypes.create_string_buffer(256)  # buffer = ctypes.create_unicode_buffer(256)
        print(f"{get_client_ip(buffer)=}")
        print(f"get_client_ip: {buffer.value=}")  # WORKING AT LAST, 2022.10.27 ^____^;; b'012.056.025.250'
    get_server_name = my_dll.ETK_GetServerName
    get_server_name.argtypes = [ctypes.c_char_p]  # ctypes.c_wchar_p
    get_server_name.restype = ctypes.c_int
    buffer = ctypes.create_string_buffer(256)  # buffer = ctypes.create_unicode_buffer(256)
    print(f"{get_server_name(buffer)=}")
    print(f"get_server_name: {buffer.value=}")  # FIXME !!! empty string

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
                 (1, 'bShowCertErrDlg', False)
    login = prototype(('ETK_Login', my_dll), paramflags)
    print(f"{login(pszID=un, pszPwd=p1, pszCertPwd=p2)=}")  # 0

# confirm
is_connected = my_dll['ETK_IsConnected']
print(f"{is_connected()=}")


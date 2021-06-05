"""
y, winreg - basic.py, 2019.8.31
https://docs.python.org/3/library/winreg.html
https://docs.microsoft.com/en-us/windows/win32/sysinfo/structure-of-the-registry
https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry-value-types
"""

import winreg as wr


key_name = 'HKEY_LOCAL_MACHINE\SOFTWARE\Python\ContinuumAnalytics\Anaconda36-64\InstallPath'
hkey_name = key_name.split('\\')[0]
sub_key = key_name[len(hkey_name)+1:]
key = {
    'HKEY_CLASSES_ROOT': wr.HKEY_CLASSES_ROOT,
    'HKEY_CURRENT_USER': wr.HKEY_CURRENT_USER,
    'HKEY_LOCAL_MACHINE': wr.HKEY_LOCAL_MACHINE,
    'HKEY_USERS': wr.HKEY_USERS,
    'HKEY_CURRENT_CONFIG': wr.HKEY_CURRENT_CONFIG,
}[hkey_name]
with wr.OpenKey(key, sub_key) as key:
    print(wr.QueryValueEx(key, 'ExecutablePath'))  # ('C:\\Y\\Anaconda3\\python.exe', 1)

key = wr.HKEY_LOCAL_MACHINE
sub_key = 'SOFTWARE\Python\ContinuumAnalytics\Anaconda36-64\InstallPath'
with wr.OpenKey(key, sub_key, access=wr.KEY_WRITE) as key:
    wr.SetValueEx(key, 'Y_Test', None, wr.REG_DWORD, 8)

key = wr.HKEY_LOCAL_MACHINE
sub_key = 'SOFTWARE\Microsoft\COM3'
with wr.OpenKey(key, sub_key, access=wr.KEY_READ) as key:
    print(wr.QueryValueEx(key, 'BuildNumber'), wr.REG_DWORD)  #  (4720, 4) 4
    print(wr.QueryValueEx(key, 'BuildType'), wr.REG_SZ)  #  ('Free', 1) 1
    print(wr.QueryValueEx(key, 'REGDBVersion'), wr.REG_BINARY)  #  (b'\r\x00\x00\x00\x00\x00\x00\x00', 3) 3



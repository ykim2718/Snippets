"""
http://timgolden.me.uk/python/win32_how_do_i/get_dll_version.html
Get a DLL's Version Number
"""

from win32api import GetFileVersionInfo, LOWORD, HIWORD


def get_version_number(filename):
    info = GetFileVersionInfo(filename, "\\")
    ms = info['FileVersionMS']
    ls = info['FileVersionLS']
    return HIWORD(ms), LOWORD(ms), HIWORD(ls), LOWORD(ls)


if __name__ == '__main__':
    import os

    filename = os.environ["COMSPEC"]
    print(".".join([str(i) for i in get_version_number(filename)]))

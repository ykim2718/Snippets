"""
y, 2022.10.20
pythoncom - win32com wo threading.py
https://stackoverflow.com/questions/26764978/using-win32com-with-multithreading
https://stackoverflow.com/questions/41492210/win32com-excel-application-open-documents-anymore
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32bit python'
import pythoncom, win32com.client as w3c
import time
import pathlib


def start():
    global xl
    xl = w3c.Dispatch('Excel.Application')
    workbook = xl.Workbooks.Add()
    file_path = pathlib.Path.cwd() / 'test.xlsx'
    print(f"{file_path=}")
    workbook.SaveAs(str(file_path))


def stop():
    global xl
    xl.quit()
    xl = None


start()
time.sleep(2)
stop()
"""
y, yThreadingComExcel.py, 2016.6.26
"""

import threading
import time

import pythoncom
import win32com.client


def run_in_thread(hMarshalled):
    print('hMarshalled(thread)', id(hMarshalled), hMarshalled, time.ctime())
    pythoncom.CoInitialize()
    hDispatch = win32com.client.Dispatch(
        pythoncom.CoGetInterfaceAndReleaseStream(
            hMarshalled, pythoncom.IID_IDispatch))
    print('hDispatch(thread)', id(hDispatch), hDispatch, time.ctime())
    xl = hDispatch
    xl.Visible = True
    wb = xl.ActiveWorkbook if xl.ActiveWorkbook else xl.Workbooks.Add()
    ws = wb.Worksheets.Add()
    cell = ws.Cells(1)
    cell.Value = 'Hello excel'
    time.sleep(1)
    pythoncom.CoUninitialize()


if __name__ == '__main__':
    hDispatch = win32com.client.Dispatch("Excel.Application")
    print('hDispatch(main)', id(hDispatch), hDispatch, time.ctime())
    hMarshalled = pythoncom.CoMarshalInterThreadInterfaceInStream(
        pythoncom.IID_IDispatch, hDispatch)
    print('hMarshalled(main)', id(hMarshalled), hMarshalled, time.ctime())
    thread = threading.Thread(target=run_in_thread, args=(hMarshalled,))
    thread.start()
    # thread.join()
    print('end')

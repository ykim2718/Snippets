"""
y, 2021.11.7; 2022.10.20
pythoncom - win32com with threading.py
https://stackoverflow.com/questions/26764978/using-win32com-with-multithreading
"""

import ctypes
assert ctypes.sizeof(ctypes.c_voidp) * 8 == 32, 'need 32bit python'
import pythoncom, win32com.client, threading, time
import pathlib


def start():
    # Initialize
    pythoncom.CoInitialize()

    # Get instance
    xl = win32com.client.Dispatch('Excel.Application')
    print(f"{type(xl)=}")
    print(f"{isinstance(xl, win32com.client.CDispatch)=}")

    # Create id
    xl_id = pythoncom.CoMarshalInterThreadInterfaceInStream(pythoncom.IID_IDispatch, xl)
    print(f"{xl_id=}")
    print(f"{(xl_id.__class__.__name__ == 'PyIStream')=}")

    # Pass the id to the new thread
    thread = threading.Thread(target=run_in_thread, kwargs={'xl_id': xl_id})
    thread.start()

    # Wait for child to finish
    thread.join()


def run_in_thread(xl_id):
    # Initialize
    pythoncom.CoInitialize()

    # Get instance from the id
    xl = win32com.client.Dispatch(
        pythoncom.CoGetInterfaceAndReleaseStream(xl_id, pythoncom.IID_IDispatch)
    )
    file_path = pathlib.Path.cwd() / 'test.xlsx'
    print(f"{file_path=}")
    workbook = xl.Workbooks.Add()
    workbook.SaveAs(str(file_path))
    time.sleep(5)


if __name__ == '__main__':
    start()

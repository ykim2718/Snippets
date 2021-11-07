"""
y, 2021.11.7
pythoncom - threading.py
https://stackoverflow.com/questions/26764978/using-win32com-with-multithreading
"""

import pythoncom, win32com.client, threading, time


def start():
    # Initialize
    pythoncom.CoInitialize()

    # Get instance
    xl = win32com.client.Dispatch('Excel.Application')

    # Create id
    xl_id = pythoncom.CoMarshalInterThreadInterfaceInStream(pythoncom.IID_IDispatch, xl)

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
    time.sleep(5)


if __name__ == '__main__':
    start()

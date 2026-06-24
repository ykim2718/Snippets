"""
http://timgolden.me.uk/python/win32_how_do_i/see-if-an-excel-workbook-is-open.html
Find a running workbook
"""
import os
import pythoncom
import win32api
import win32com.client

FILENAME = win32api.GetLongPathName(os.path.join(os.environ["TEMP"], "temp.csv"))
open(FILENAME, "wb").write("1,2,3\n4,5,6\n")
obj = win32com.client.GetObject(FILENAME)

context = pythoncom.CreateBindCtx(0)
for moniker in pythoncom.GetRunningObjectTable():
    name = moniker.GetDisplayName(context, None)
    if name.endswith(FILENAME):
        print("Found", name)
        break
    else:
        print("Not found")

"""
http://timgolden.me.uk/python/win32_how_do_i/attach-to-a-com-instance.html
Attach to a running instance of a COM application
"""
import os, sys
import csv
import tempfile
import win32com.client

#
# Cheating slightly because I know a .csv
# file will register as an Excel object
#

filename = tempfile.mktemp(".csv")
f = open(filename, "wb")
writer = csv.writer(f)
writer.writerows(range(i, i + 5) for i in range(10))
f.close()

#
# NB filename must (in effect) be absolute
#
os.startfile(filename)

wb1 = win32com.client.GetObject(filename)
wb1_c11 = wb1.ActiveSheet.Cells(1, 1)
print(wb1_c11.Value)
wb1_c11.Value += 1

xl = win32com.client.GetObject(Class="Excel.Application")
# could also use:
# xl = win32com.client.GetActiveObject ("Excel.Application")
xl_c11 = xl.ActiveSheet.Cells(1, 1)
print(xl_c11.Value)
xl_c11.Value += 1

print(wb1_c11.Value)
print(xl_c11.Value)

wb1.Close()

os.remove(filename)

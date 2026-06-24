'''
Y. Kim, 2016.4.8
http://stackoverflow.com/questions/6337595/python-win32-com-closing-excel-workbook
'''

from win32com.client import Dispatch
import os

cwd = os.getcwd()
print(cwd)
xl = Dispatch('Excel.Application')
xl.Visible = False
wb = xl.Workbooks.Add()
ws = wb.Worksheets.Add()
cell = ws.Cells(1)
cell.Value = 'Some text'
file = cwd + r'\testExcel.xlsx'
wb.Close(True, file)
print(file, "<<< saved")

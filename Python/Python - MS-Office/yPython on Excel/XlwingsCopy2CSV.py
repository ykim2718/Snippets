"""
XlwingsCopy2CSV.py
y (copyRight) 2016.4.28
http://pydoc.net/Python/xlwings/0.2.3/xlwings._xlwindows/
"""


def GetDataFrameFromExcelSheet(sheet, row=999, col=999):
    import xlwings as xw

    df = xw.Range(sheet, (1, 1), (row, col)).value
    df = pd.DataFrame(df)
    df = df.dropna(how='all', axis=0)
    df = df.dropna(how='all', axis=1)

    return df


if __name__ == "__main__":

    import xlwings as xw

    try:
        wb = xw.Workbook.active()
    except Exception as ex:
        print("Can't find excel file open")

    row_max = 999
    col_max = 999

    sheet = wb.active_sheet
    print(sheet, "is going to be converted in the range of orw %s and col %s"
          % (row_max, col_max))

    import pandas as pd

    df = GetDataFrameFromExcelSheet(sheet, row=row_max, col=col_max)
    file = __file__[:-3] + '.csv'
    file = wb.fullname[:-5] + ".csv"  # assume file ending with ".xlsx"
    df.to_csv(file)
    print(file, "is written")

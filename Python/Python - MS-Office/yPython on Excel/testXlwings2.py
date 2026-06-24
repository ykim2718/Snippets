import xlwings as xw
import pandas as pd
import re


def GetDataFrame(Sheet, N, M):
    wb = xw.Workbook.active()
    Data = xw.Range(Sheet, (1, 1), (N, M)).value
    Data = pd.DataFrame(Data)
    Data = Data.dropna(how='all', axis=1)
    Data = Data.dropna(how='all', axis=0)
    return Data


if __name__ == "__main__":

    wb = None
    try:
        wb = xw.Workbook.active()
    except Exception as e:
        print("[{0}] {1!r}".format(type(e).__name__, e.args))
        import sys

        sys.exit()

    xw.Range('A1').value = list(map(list, zip([1, 2, 3, 4], [11, 12, 13, 14])))
    file = re.sub('\.py$', '-a.xlsx', __file__)
    print(file)
    # wb.save(file)

    selection = wb.get_selection().value
    print(selection)
    df = GetDataFrame('sheet1', 99, 99)
    df.sort_values(by=0, inplace=True)
    df.reset_index(drop=True, inplace=True)
    print(df)
    file = re.sub('.py$', '-b.xlsx', __file__)
    writer = pd.ExcelWriter(file, engine='xlsxwriter')
    df.to_excel(writer, sheet_name='Sheet1')
    writer.save()

import pandas as pd

xl = pd.ExcelFile("testPandasExcel_in.xlsx")
print(xl.sheet_names)
# [u'Sheet1', u'Sheet2', u'Sheet3']
# df = xl.parse("A015760")
df = xl.parse(0)  # sheet1
print(df.head())

# df.sort_values(by=['Date', 'Close'], ascending=[True, False], inplace=True)
df.sort_values(by='Date', ascending=True, inplace=True)
df.reset_index(drop=True, inplace=True)
print(df)

df = pd.DataFrame({'Data': [10, 20, 30, 20, 15, 30, 45]})
writer = pd.ExcelWriter('testPandasExcel_out.xlsx', engine='xlsxwriter')
df.to_excel(writer, sheet_name='Sheet1')
workbook = writer.book
worksheet = writer.sheets['Sheet1']
# worksheet.conditional_format('B2:B8', {'type': '3_color_scale'})
writer.save()

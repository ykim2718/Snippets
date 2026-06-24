# https://pypi.python.org/pypi/XlsxWriter

import xlsxwriter

# Create an new Excel file and add a worksheet.
workbook = xlsxwriter.Workbook('demo.xlsx')
worksheet = workbook.add_worksheet()

# Widen the first column to make the text clearer.
worksheet.set_column('A:A', 20)

# Add a bold format to use to highlight cells.
bold = workbook.add_format({'bold': True})

# Write some simple text.
worksheet.write('A1', 'Hello')

# Text with formatting.
worksheet.write('A2', 'World', bold)

# Write some numbers, with row/column notation.
worksheet.write(2, 0, 123)
worksheet.write(3, 0, 123.456)

# Insert an image.
# worksheet.insert_image('B5', 'logo.png')

worksheet = workbook.add_worksheet()
expenses = (['Rent', 1000], ['Gas', 100], ['Food', 300], ['Gym', 50])
row = col = 0
for item, cost in expenses:
    worksheet.write(row, col, item)
    worksheet.write(row, col + 1, cost)
    row = row + 1

worksheet.write(row, 0, 'Total')
worksheet.write(row, 1, '=sum(b1:b4)')

workbook.close()

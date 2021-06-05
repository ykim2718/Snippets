"""
y, pandas - to_excel.py, 2017.10.29
"""

import pandas as pd
import numpy as np
import os

file_path = os.path.splitext(__file__)[0] + '.xlsx'

writer = pd.ExcelWriter(file_path)
print(type(writer))
print(isinstance(writer, pd.io.excel._XlsxWriter))

frame = pd.DataFrame(np.random.randint(0, 99, size=(3, 2)), columns=list('AB'))
frame.to_excel(writer, sheet_name='s1')

frame = pd.DataFrame(np.random.randint(0, 99, size=(5, 2)), columns=list('AB'))
frame.to_excel(writer, sheet_name='s2')

writer.save()
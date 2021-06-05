"""
y, pandas - read empty csv.py, 2018.10.16
"""

import pandas as pd
import os

a_file = os.path.basename(os.path.splitext(__file__)[0]) + '.csv'

# write
with open(a_file, 'wt') as f:
    f.write('1st line\n')
    f.write('2nd line\n')

# read
try:
    df = pd.read_csv(a_file, skiprows=2)
    print(df)
except pd.errors.EmptyDataError as ex:
    print('empty csv')

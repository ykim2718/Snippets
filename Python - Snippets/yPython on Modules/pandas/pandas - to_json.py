"""
y, pandas - to_json.py, 2018.5.14, 5.25
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.to_json.html
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.read_json.html
"""

import pandas as pd

# 2018.5.14

df = pd.DataFrame({'col1': [1, 2], 'col2': [0.5, 0.75]}, index=pd.date_range('2018-1-1', periods=2))
df.index.name = 'y_index'
df.columns.name = 'y_column'

print(df)
for orient in ['split', 'records', 'index', 'columns', 'values']:
    print('-' * 8, orient, '-' * 32)
    dj = df.to_json(orient=orient, date_format='iso', date_unit='s')
    print(dj)
    print(pd.read_json(dj, orient='columns'))


# 2018.5.25
print()

df = pd.DataFrame({'col1': [1, 2], 'col2': [0.5, 0.75]}, index=pd.MultiIndex.from_product(
    [list('A'), list('ab')], names=['1st', '2nd']))
df.index.name = 'y_index'  # not working
df.columns.name = 'y_column'

print(df)
for orient in ['split', 'records', 'index', 'columns', 'values']:
    print('-' * 8, orient, '-' * 32)
    dj = df.to_json(orient=orient, date_format='iso', date_unit='s')
    print(dj)
    try:
        print(pd.read_json(dj, orient='columns'))
    except:
        print('....')
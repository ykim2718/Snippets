"""
y, pandas - to_dict.py, 2018.5.13, 5.25

https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.to_dict.html
https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.from_dict.html
"""

import pandas as pd


# 2018.5.13

df = pd.DataFrame({'col1': [1, 2], 'col2': [0.5, 0.75]}, index=['a', 'b'])
df.index.name = 'y_index'
df.columns.name = 'y_column'

print(df)
for orient in ['dict', 'list', 'series', 'split', 'records', 'index']:
    print('-' * 8, orient, '-' * 32)
    dd = df.to_dict(orient=orient)
    print(dd)
    print(pd.DataFrame.from_dict(dd, orient='columns'))  #  if orient in ['list', 'records', 'split'] else 'index'))

print('=' * 32)
df = pd.DataFrame.from_dict(df.to_dict(orient='split'), orient='columns')
df = pd.DataFrame(df['data'].tolist(), columns=df['columns'], index=df['index'])
print(df)
print(df.index.name)
print(df.columns.name)
print(df.columns)

# 2018.5.25
print()

df = pd.DataFrame({'col1': [1, 2], 'col2': [0.5, 0.75]}, index=pd.MultiIndex.from_product(
    [list('A'), list('ab')], names=['1st', '2nd']))
df.index.name = 'y_index'  # not working
df.columns.name = 'y_column'

print(df)
for orient in ['dict', 'list', 'series', 'split', 'records', 'index']:
    print('-' * 8, orient, '-' * 32)
    dd = df.to_dict(orient=orient)
    print(dd)
    try:
        print(pd.DataFrame.from_dict(dd, orient='index'))
    except:
        print('....')
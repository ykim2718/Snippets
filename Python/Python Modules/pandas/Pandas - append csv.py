"""
y, Pandas - append csv.py, 2017.5.15

How to add pandas data to an existing csv file?
stackoverflow...

"""

import pandas as pd

file_path = 'foo.csv'

# case 1

df = pd.DataFrame({'A': [1, 4], 'B': [2, 5], 'C': [3, 6]})
df.index.name = '(1)'
df.to_csv(file_path)

df = pd.read_csv(file_path, index_col=0)

with open(file_path, 'a') as f:
    (df * 6).to_csv(f, header=False)

df = pd.read_csv(file_path, index_col=0)
print(df)

# case 2

import datetime as dt

df = pd.DataFrame({'A': [1, 4], 'B': [2, 5], 'C': [3, 6]},
                  index=[dt.date(2017, 5, 15), dt.date(2017, 5, 16)])
df.index.name = '(2)'
df.to_csv(file_path)

df = pd.read_csv(file_path, index_col=0, parse_dates=True)

with open(file_path, 'a') as f:
    # (df * 6).to_csv(f, header=False)
    df.to_csv(f, header=True)

df = pd.read_csv(file_path, index_col=0, parse_dates=True)
print(df)
print(type(df.index[0]))


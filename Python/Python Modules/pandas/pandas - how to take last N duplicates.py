"""
y, pandas - how to take last N duplicates.py, 2018.3.21
https://stackoverflow.com/questions/46781195/keeping-the-last-n-duplicates-in-pandas
"""

import pandas as pd
lol = [['a', 1, 1], ['a', 1, 2], ['a', 1, 4], ['b', 2, 9], ['c', 2, 10],
       ['x', 2, 5], ['d', 2, 3], ['e', 3, 5], ['d', 2, 10], ['a', 3, 5]]
df = pd.DataFrame(lol)
df.rename(columns={0: 'value', 1: 'key', 2: 'something'}, inplace=True)
print(df)
# print(df.groupby('key').tail(2))  # bug, take last 2 of non-duplicates

columns = ['value', 'key']
# print(df.groupby(columns).tail(2))  # bug, take last 2 of non-duplicates
n = 2
locations = []
gr = df.groupby(columns)
for k, v in gr.groups.items():
    if len(v) >= n:
        locations.extend(v[-n:])
        print(k, '==', v, '==', v[-2:])
        print(locations)
print(df.iloc[locations])  # good
"""
duplicated = df.duplicated(subset=columns, keep=False)
print(df[duplicated])
keys = df[duplicated].groupby(columns).count() >= 3
print(keys)
duplicated_index = keys[keys].index
df = df[duplicated].set_index(columns[0], drop=False)
print(df.loc[duplicated_index])
"""

"""
y, Pandas - element with 2dlist.py, 2018.2.26
"""

import pandas as pd
import os

df = pd.DataFrame()  # instead of pd.DataFrame(columns=list('ABC'))
for j in range(4):
    df.loc[j, 'A'] = j
    df.loc[j, 'B'] = str([j for j in range(j)])
    df.loc[j, 'C'] = str([[j], [j for j in range(j)]])
df['B'] = df['B'].apply(lambda x: eval(x))
df['C'] = df['C'].apply(lambda x: eval(x))
df['D'] = [1, [2], [2, [3]], 4]

if True:
    file_path = os.path.splitext(__file__)[0] + '.csv'
    df.to_csv(file_path)
    df = pd.read_csv(file_path)
    df['C'] = df['C'].apply(lambda x: eval(x))
print(df)

a = df.loc[len(df) - 1, 'B']
print('b=', a, type(a))
a = df.loc[len(df) - 1, 'C']
print('c=', a, type(a))
a = a[0][0]
print('c[0][0]=', a, type(a))

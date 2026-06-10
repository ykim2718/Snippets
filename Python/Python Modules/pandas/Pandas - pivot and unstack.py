"""
y , 2016.7.15 - 7.20, Pandas - pivot and unstack.py
"""
import pandas as pd

df = pd.DataFrame({
    'c1': [1, 2, 3],
    'c2': [4, 5, 6],
    'c3': [7, 8, 9],
    'c4': ['a', 'b', 'c'],
    'c5': ['d', 'e', 'f']
}, index=['r1', 'r2', 'r3'])

dg = df.pivot(index='c1', columns='c2', values='c3')
print(dg)

dg = df.set_index(['c1', 'c2', 'c3']).unstack('c3')
print(dg)

print('y, 2016.7.20, df.pivot_table')
dg = df.pivot_table(
    values='c3',  # can be skipped
    index=['c1', 'c2'],  # mandatory
    columns=['c4', 'c5'],  # mandatory
    aggfunc=lambda x: x  # can be skipped
)
print(dg)

df = pd.DataFrame({
    'lot': ['a', 'a', 'b', 'b', 'c'],
    'wafer': [1, 1, 1, 4, 1],
    'x': [1, 1, 1, 2, 3],
    'y': [1, 2, 1, 3, 4],
    'd1': [11, 12, 13, 14, 15],
    'd2': [21, 22, 23, 24, 25],
    'd3': [31, 32, 33, 34, 35]
})
print('wafer data is given as\n', df)
df['xy'] = df[['x', 'y']].apply(lambda x: '{},{}'.format(x[0], x[1]), axis=1)
dg = df.pivot_table(index=['lot', 'wafer'], columns=['xy'], values=['d1', 'd2', 'd3'])
print(dg)

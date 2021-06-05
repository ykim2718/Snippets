"""
y, Pandas - element with list.py, 2018.2.22 - 23
"""

import pandas as pd
import numpy as np
import os

length = 8
frame = pd.DataFrame({'scalar': list(range(8)),
                      'list': [list(np.random.randint(j, 99, size=j)) for j in range(length)]},
                     index=list('abcdefgh'))
frame['count'] = frame['list'].apply(lambda a: len(a))
frame['sum'] = frame['list'].apply(lambda a: pd.Series(a).sum())
frame['list+sum'] = frame[['list', 'sum']].apply(lambda a: (a[0] + [a[1]]), axis=1)
print(frame)

file_path = os.path.splitext(__file__)[0] + '.csv'
frame.to_csv(file_path)
print(pd.read_csv(file_path))

"""
                           list  scalar  count  sum                               list+
0                            []       0      0    0                                 [0]
1                          [18]       1      1   18                            [18, 18]
2                      [58, 22]       2      2   80                        [58, 22, 80]
3                  [26, 29, 35]       3      3   90                    [26, 29, 35, 90]
4              [62, 59, 74, 18]       4      4  213               [62, 59, 74, 18, 213]
5           [27, 11, 9, 11, 98]       5      5  156            [27, 11, 9, 11, 98, 156]
6      [81, 93, 21, 85, 85, 33]       6      6  398       [81, 93, 21, 85, 85, 33, 398]
7  [93, 95, 79, 42, 39, 95, 54]       7      7  497   [93, 95, 79, 42, 39, 95, 54, 497]

"""

# melted = pd.melt(frame, id_vars=['scalar'], value_vars=['list'], var_name='variable', value_name='value')
# print(melted)
flatten = pd.DataFrame(frame['list'].tolist(), index=frame.index).add_prefix('_')
objs = [frame, flatten]
frame = pd.concat(objs, axis=1).drop('list', axis=1)
print(frame)
print('flattened column size =', flatten.columns.size)

print(flatten)
stacked = flatten.stack()
print(stacked)
print(stacked.index[0])

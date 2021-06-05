"""
y, 2021.2.8
pandas - multiindex - modify a level.py
"""

import pandas as pd

level1 = pd.date_range(start='2021-2-8', periods=4)
level0 = [f"{j:03d}" for j in range(len(level1))]
index = pd.MultiIndex.from_arrays([level0, level1], names=['level0', 'level1'])
print(index)
'''
MultiIndex([('000', '2021-02-08'), ('001', '2021-02-09'),
            ('002', '2021-02-10'), ('003', '2021-02-11')],
           names=['level0', 'level1'])
'''

index_values = pd.DatetimeIndex(index.get_level_values(1), tz='Asia/Seoul')[::-1]
print(index_values)
'''
DatetimeIndex(['2021-02-11 00:00:00+09:00', '2021-02-10 00:00:00+09:00',
               '2021-02-09 00:00:00+09:00', '2021-02-08 00:00:00+09:00'],
              dtype='datetime64[ns, Asia/Seoul]', name='level1', freq=None)
'''

index = index.set_levels(index_values, 1)
print(index)
'''
MultiIndex([('000', '2021-02-11 00:00:00+09:00'), ('001', '2021-02-10 00:00:00+09:00'),
            ('002', '2021-02-09 00:00:00+09:00'), ('003', '2021-02-08 00:00:00+09:00')],
           names=['level0', 'level1'])
'''

index = pd.MultiIndex.from_arrays([index.get_level_values(0), index_values])
print(index)
'''
MultiIndex([('000', '2021-02-11 00:00:00+09:00'), ('001', '2021-02-10 00:00:00+09:00'),
            ('002', '2021-02-09 00:00:00+09:00'), ('003', '2021-02-08 00:00:00+09:00')],
           names=['level0', 'level1'])
'''
"""
y, 2017.5.27, Pandas - column operation.py

"""

import pandas as pd

print('>> y, 2017.5.27')
df = pd.DataFrame({
    'a': [1, 2, 3],
    'b': [4, 5, 6],
    'c': [7, 8, 9],
    'd': [10, 11, 12]},
    index=[0, 1, 2])

select_few_columns = ['a', 'c']
print(df[select_few_columns])
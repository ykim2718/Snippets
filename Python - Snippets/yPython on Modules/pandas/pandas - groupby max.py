"""
y, pandas - groupby max.py, 2018.10.12
"""

import pandas as pd
import numpy as np


def printx(x):
    assert isinstance(x, str)
    print(x, '=')
    print(eval(x))


a = np.arange(0, 12, 1).reshape((4, 3))
printx('a')

df = pd.DataFrame(a, columns=list('ABC'), index=list('aabc'))
printx('df')

gr = df[['A']].groupby([df.index.get_level_values(0)]).max()
printx('gr')

gr = df[['A', 'B']].groupby(['B']).max()
printx('gr')

gr = df[['A', 'B', 'C']].groupby(['B']).max()
printx('gr')

print('-'*22)

df = pd.DataFrame({'A': [1, 2, 3], 'B': [1, 2, 2]})
printx('df')

gr = df[['A', 'B']].groupby(['B']).max()
printx('gr')





"""
y, pandas - groupby count.py, 2019.7.20

"""

import pandas as pd

df = pd.DataFrame([[0, -1, -2], [0, -1, -2], [-1, 2, 4], [-1, 2, 4], [-1, 0, 4]],
                  columns=list('ABC'), index=list('abcaa'))
print('-'*12, '\n', df)

gr = df.groupby(['A', 'B']).count()
print('-'*12, '\n', gr)


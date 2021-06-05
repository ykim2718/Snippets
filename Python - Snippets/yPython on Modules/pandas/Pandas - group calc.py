"""
y, Pandas - group calc.py, 2017.8.29

"""

import pandas as pd

df = pd.DataFrame([[0, 1, 2], [0, 3, 4], [1, 5, 6], [1, 7 , 8], [0, 9, 10]],
                  columns=list('ABC'),
                  index=list('abcaa'))
print(df)

gr = df[['A', 'B']].groupby([df.index.get_level_values(0), 'A']).sum()
print(gr)
print(type(gr), gr.index[0], gr.columns)
print(gr.loc[('a', 0), 'B'])
"""
y, pandas - index to dict.py, 2018.7.3
"""

import pandas as pd
tuples = [(1, 2), (2, 3), (3, 'four')]
print(tuples)
index = pd.MultiIndex.from_tuples(tuples, names=['first', 'second'])
print(index)
list_of_dict = list(index.to_frame(index=False).to_dict(orient='index').values())
print(list_of_dict)
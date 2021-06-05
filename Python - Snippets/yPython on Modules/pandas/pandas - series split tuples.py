"""
y, pandas - series split tuples.py, 2017.10.20

"""

import pandas as pd

ds = pd.Series([(0, 1), (2, 3), (4, 5)])
a, b = zip(*ds.apply(lambda x: x))

print('ds=%s' % ds)
print('a=%s, b=%s' % (a, b))
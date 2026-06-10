"""
y, pandas - index intersection.py, 2019.10.9
"""

import pandas as pd


a = pd.Index([('a', 'b'), ('a', 'c'), ('d', ''), 'e'])
print(a)
b = pd.Index([('a', 'b'), 'd', 'e'])
print(a.intersection(b))
print([c in a for c in b])

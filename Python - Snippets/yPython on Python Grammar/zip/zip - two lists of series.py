"""
y, zip - two lists of series.py, 2019.3.25, 3.26
"""

import pandas as pd

A = pd.Series([1, 2])
B = pd.Series([3, 4])
print(id(A), id(B))

C = []

for a, b, c in zip([A], [B], [C]):
    print(id(a), id(b))
    a *= 2
    b *= 3
    c.append((a, b))

print(A)
print(B)
print(C)

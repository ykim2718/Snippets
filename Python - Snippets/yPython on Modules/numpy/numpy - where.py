import numpy as np
import pandas as pd

print("y, 2016.5.1 List to numpy array and numpy.where")
vec = range(10)
vec = np.array(vec)
indices = np.where(vec > 5)
r = vec[indices]
print(r, type(r))
print(r[0])

print("y, 2016.5.1 Column to column comparision")
df = pd.DataFrame({'a': range(5), 'b': list(reversed(range(5))), 'c': range(5, 10)},
                  index=['o', 'p', 'q', 'r', 's'])
# df.ix[df.index[-1], 'b'] = float('nan')
print(df)
# print(np.where(df['a'] < 3, 1, 0))  # don't know how this does work
r = np.where(df['a'] >= df['b'])
d = np.ediff1d(r)
r = r[0]  # don't know why r[0]
print(r, r[0], type(r), len(r))
print(d)

print("y, 2016.10.29")
a = np.array([0, 1, 2, np.nan, 5])
print(a[np.where(a != a)])  # nan
print(a[np.isfinite(a)])

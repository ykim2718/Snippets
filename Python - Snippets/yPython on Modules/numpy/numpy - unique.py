"""
y, 2023.4.30
numpy - unique.py
https://stackoverflow.com/questions/28663856/how-do-i-count-the-occurrence-of-a-certain-item-in-an-ndarray
"""

import numpy as np

a = np.asarray([[1, 2], [3, 4], [5, 1]])
print(f"{a.shape=}")
print(f"{a.tolist()=}")
d = dict(zip(*np.unique(a, return_counts=True)))
print(f"{d=}")

a1 = np.take(a, [1], axis=-1)
print(f"{a1.tolist()=}")
d = dict(zip(*np.unique(a1, return_counts=True)))
print(f"{d=}")

"""
a.shape=(3, 2)
a.tolist()=[[1, 2], [3, 4], [5, 1]]
d={1: 2, 2: 1, 3: 1, 4: 1, 5: 1}
a1.tolist()=[[2], [4], [1]]
d={1: 1, 2: 1, 4: 1}
"""

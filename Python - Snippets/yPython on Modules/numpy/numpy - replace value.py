import numpy as np

a = np.array([1, 2, 3, 4, 5])
print(a)
# m = a == a.max()
m = np.where(a >= 3)
print(m)
a[m] = 10
print(a)

a = np.array([1, 2, 3, 4, 5])
np.place(a, a >= 3, [100, 200])
print(a)

a = np.array([1, 2, 3, 4, 5])
np.place(a, a >= 30, [1000, 2000])
print(a)

"""
y, 2022.5.27
python list - allocation.py
"""

import numpy as np

print('- ' * 16)
a = [0] * 2
print(a)  # [0, 0]
a[1] = 1
print(a)  # [0, 1]

print('- ' * 16)
a = [[0]] * 2
print(a)  # [[0], [0]]
a[1][0] = 1
print(a)  # [[1], [1]]  << CAUTIOUS

print('- ' * 16)
a = [[0] * 2] * 2
print(a, np.array(a).shape)  # [[0, 0], [0, 0]] (2, 2)
a[1][1] = 1
print(a)  # [[0, 1], [0, 1]]  << CAUTIOUS

print('- ' * 16)
a = [[0] * 2 for _ in range(2)]
print(a, np.array(a).shape)  # [[0, 0], [0, 0]] (2, 2)
a[1][1] = 1
print(a)  # [[0, 0], [0, 1]]

print('- ' * 16)
a = [[0] for _ in range(2)] * 2
print(a, np.array(a).shape)  # [[0], [0], [0], [0]] (4, 1)

print('- ' * 16)
a = [[0 for _ in range(2)] for _ in range(2)]
print(a, np.array(a).shape)  # [[0, 0], [0, 0]] (2, 2)
a[1][1] = 1
print(a)  # [[0, 0], [0, 1]]

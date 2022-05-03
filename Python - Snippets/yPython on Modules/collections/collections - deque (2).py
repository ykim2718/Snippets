"""
y, 2022.5.4
collections - deque (2).py
https://docs.python.org/3.7/library/collections.html#collections.deque
"""

from collections import deque

a = deque([1, 2], maxlen=4)
a.append(3)
a.extend([4])
a.appendleft(0)
print(a)  # deque([0, 1, 2, 3], maxlen=4)

a.rotate(1)
print(a)  # deque([3, 0, 1, 2], maxlen=4)
a.rotate(-2)
print(a)  # deque([1, 2, 3, 0], maxlen=4)

a.clear()
print(a)  # deque([], maxlen=4)
print(a.maxlen)  # 4

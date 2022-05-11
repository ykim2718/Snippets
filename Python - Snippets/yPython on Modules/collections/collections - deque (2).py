"""
y, 2022.5.4, 5.12
collections - deque (2).py
https://docs.python.org/3/library/index.html
https://docs.python.org/3/library/collections.html#collections.deque
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

a.pop()
print(a)  # deque([1, 2, 3], maxlen=4)
a.popleft()
print(a)  # deque([2, 3], maxlen=4)

a.remove(3)
print(a)  # deque([2], maxlen=4)

a.clear()
print(a)  # deque([], maxlen=4)
print(a.maxlen)  # 4

a.insert(1, 0)
a.insert(1, 1)
a.insert(2, 2)
a.insert(4, 4)
print(a)  # deque([0, 1, 2, 4], maxlen=4)
a.reverse()
print(a)  # deque([4, 2, 1, 0], maxlen=4)

a.append(0)
print(a)  # deque([2, 1, 0, 0], maxlen=4)
a.append(0)
print(a)  # deque([1, 0, 0, 0], maxlen=4)
a.append(0)
print(a)  # deque([0, 0, 0, 0], maxlen=4)


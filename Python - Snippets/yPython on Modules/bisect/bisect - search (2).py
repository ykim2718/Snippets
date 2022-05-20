"""
y, 2022.5.17
bisect - search.py
time complexity: O(n)
"""

import bisect

a = list(range(10))

print(f"{a=}")
print(f"{bisect.bisect_left(a, 5)=}, {a[:5]=}")
print(f"{bisect.bisect_right(a, 5)=}, {a[6:]=}")

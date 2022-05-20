"""
y, 2022.5.17, 5.20
bisect - search.py
time complexity: O(n)
"""

import bisect

a = list(range(10))
assert sorted(a) == a, 'need sorted array for binary search'

print(f"{a=}")
print(f"{bisect.bisect_left(a, 5)=}, {a[:5]=}")
print(f"{bisect.bisect_right(a, 5)=}, {a[6:]=}")

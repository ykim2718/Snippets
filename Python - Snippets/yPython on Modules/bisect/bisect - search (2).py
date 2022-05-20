"""
y, 2022.5.20
bisect - search (2).py
time complexity: O(n)
"""

import bisect


class ComparableNode:
    def __init__(self, value, compare):
        self.value = value
        self.compare = compare

    def __lt__(self, other):
        return self.compare(self.value, other.value)

    def __repr__(self):
        return str(self.value)


a = []
compare = lambda a, b: a < b
for j in [6, 5, 4, 7, 8, 9, 3, 2, 1, 0]:
    a.append(ComparableNode(j, compare))
print(f"{a=}")
a = sorted(a)  # need sorted array for binary search
print(f"{a=}")
print(f"{bisect.bisect_left(a, ComparableNode(5, compare))=}, {a[:5]=}")
print(f"{bisect.bisect_right(a, ComparableNode(5, compare))=}, {a[6:]=}")
"""
a=[6, 5, 4, 7, 8, 9, 3, 2, 1, 0]
a=[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
bisect.bisect_left(a, ComparableNode(5, compare))=5, a[:5]=[0, 1, 2, 3, 4]
bisect.bisect_right(a, ComparableNode(5, compare))=6, a[6:]=[6, 7, 8, 9]
"""

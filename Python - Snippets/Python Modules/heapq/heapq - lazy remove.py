"""
y, 2022.5.19 - 21
heapq - lazy remove.py
"""

import heapq as hq


class HeapNode:
    def __init__(self, index, value, compare):
        assert callable(compare)
        self.index = index
        self.value = value  # use tuple rather than list for speed
        self.compare = compare

    def __lt__(self, other):
        return self.compare(self.value, other.value)

    def __repr__(self):
        return f"({self.index}, {self.value})"


class LazyHeap:
    def __init__(self):
        self._pq = []  # priority queue
        self._flags = dict()  # use integer key for speed

    def push(self, a, data=True):
        assert hasattr(a, 'index') and isinstance(a.index, int)
        assert hasattr(a, 'value')
        hq.heappush(self._pq, a)
        self._flags[a.index] = data

    def pop(self):
        while self._pq and self._pq[0].index not in self._flags:
            hq.heappop(self._pq)
        return hq.heappop(self._pq) if self._pq else None

    def remove(self, index):
        assert isinstance(index, int)
        self._flags.pop(index, None)

    def get(self, index, default=None):
        assert isinstance(index, int)
        return self._flags.get(index, default)


lh = LazyHeap()
compare = lambda a, b: a < b
for j in [6, 5, 4, 7, 8, 9, 3, 2, 1, 0]:
    lh.push(HeapNode(j, j*10, compare))
    print(f"{lh._pq=}")
lh.remove(0)
lh.remove(1)
lh.remove(3)
lh.remove(5)
lh.remove(7)
print(f"{lh._flags=}")
print(f"{lh._pq=}")
print(f"{lh.pop()=}, {lh._pq=}")
print(f"{lh.pop()=}, {lh._pq=}")
print(f"{lh.pop()=}, {lh._pq=}")
print(f"{lh.pop()=}, {lh._pq=}")
print(f"{lh.get(8)=}")
print(f"{lh.pop()=}, {lh._pq=}")
print(f"{lh.pop()=}, {lh._pq=}")
"""
lh._pq=[(6, 60)]
lh._pq=[(5, 50), (6, 60)]
lh._pq=[(4, 40), (6, 60), (5, 50)]
lh._pq=[(4, 40), (6, 60), (5, 50), (7, 70)]
lh._pq=[(4, 40), (6, 60), (5, 50), (7, 70), (8, 80)]
lh._pq=[(4, 40), (6, 60), (5, 50), (7, 70), (8, 80), (9, 90)]
lh._pq=[(3, 30), (6, 60), (4, 40), (7, 70), (8, 80), (9, 90), (5, 50)]
lh._pq=[(2, 20), (3, 30), (4, 40), (6, 60), (8, 80), (9, 90), (5, 50), (7, 70)]
lh._pq=[(1, 10), (2, 20), (4, 40), (3, 30), (8, 80), (9, 90), (5, 50), (7, 70), (6, 60)]
lh._pq=[(0, 0), (1, 10), (4, 40), (3, 30), (2, 20), (9, 90), (5, 50), (7, 70), (6, 60), (8, 80)]
lh._flags={6: True, 4: True, 8: True, 9: True, 2: True}}
lh._pq=[(0, 0), (1, 10), (4, 40), (3, 30), (2, 20), (9, 90), (5, 50), (7, 70), (6, 60), (8, 80)]
lh.pop()=(2, 20), lh._pq=[(3, 30), (6, 60), (4, 40), (7, 70), (8, 80), (9, 90), (5, 50)]
lh.pop()=(4, 40), lh._pq=[(5, 50), (6, 60), (9, 90), (7, 70), (8, 80)]
lh.pop()=(6, 60), lh._pq=[(7, 70), (8, 80), (9, 90)]
lh.pop()=(8, 80), lh._pq=[(9, 90)]
lh.get(8)=True
lh.pop()=(9, 90), lh._pq=[]
lh.pop()=None, lh._pq=[]
"""

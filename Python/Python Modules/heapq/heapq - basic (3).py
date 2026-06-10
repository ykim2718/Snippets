"""
y, 2022.5.4
heapq - basic (3).py
https://docs.python.org/3/library/heapq.html
"""

from heapq import heappush, heappop, heapify, nlargest, nsmallest

a = []
heappush(a, (1, 2))
heappush(a, (2, 3))
heappush(a, (3, 1))
heappush(a, (0, 4))
print(f"{a=}")  # a=[(0, 4), (1, 2), (3, 1), (2, 3)]

print(f"{heappop(a)=}")  # heappop(a)=(0, 4)
print(f"{a=}")  # a=[(1, 2), (2, 3), (3, 1)]


class HeapData:
    def __init__(self, a, b, ascending=True):
        self.a = a
        self.b = b
        self.ascending=ascending

    def __lt__(self, other):
        if self.ascending:
            return (self.a, self.b) < (other.a, other.b)
        else:
            return (self.a, self.b) > (other.a, other.b)

    def __repr__(self):
        return f"({self.a}, {self.b})"


b = []
heappush(b, HeapData(0, 4, ascending=False))
heappush(b, HeapData(1, 3, ascending=False))
heappush(b, HeapData(2, 1, ascending=False))
print(f"{b[0]=}")  # b=(2, 1)

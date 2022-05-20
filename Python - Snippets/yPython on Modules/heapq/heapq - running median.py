"""
y, 2022.5.17 - 19
heapq - running median.py
"""

import heapq as hq
import operator


class HeapNode:
    def __init__(self, value, ascending=True):
        self.value = value
        self.comparator = operator.lt if ascending else operator.gt

    def __lt__(self, other):
        return self.comparator(self.value, other.value)


class RunningMedian:
    def __init__(self):
        self.stm = []  # smaller_than_median, max_heap
        self.btm = []  # bigger_than_median, min_heap
        self._median = float('nan')

    def add_value(self, a):
        if a < self._median:
            hq.heappush(self.stm, HeapNode(a, False))
        else:
            hq.heappush(self.btm, HeapNode(a))
        diff = len(self.btm) - len(self.stm)
        if diff > 1:
            hq.heappush(self.stm, HeapNode(hq.heappop(self.btm).value, False))
        elif diff < -1:
            hq.heappush(self.btm, HeapNode(hq.heappop(self.stm).value))
        if self.stm and self.btm:
            diff = len(self.btm) - len(self.stm)
            if diff > 0:
                self._median = self.btm[0].value
            elif diff < 0:
                self._median = self.stm[0].value
            else:
                self._median = (self.stm[0].value + self.btm[0].value) / 2
        elif self.stm:
            self._median = self.stm[0].value
        elif self.btm:
            self._median = self.btm[0].value

    @property
    def median(self):
        return self._median


if True:
    rm = RunningMedian()
    for a in [[5], [1, 2], [7, 4], [6, 3], [9, 9]]:
        for j in a:
            rm.add_value(j)
            print([n.value for n in rm.stm], [n.value for n in rm.btm])
        print(f"{rm.median=}")
    """
    [] [5]
    rm.median=5
    [1] [5]
    [2, 1] [5]
    rm.median=2
    [2, 1] [5, 7]
    [2, 1] [4, 7, 5]
    rm.median=4
    [4, 1, 2] [5, 6, 7]
    [4, 3, 2, 1] [5, 6, 7]
    rm.median=4
    [4, 3, 2, 1] [5, 6, 7, 9]
    [4, 3, 2, 1] [5, 6, 7, 9, 9]
    rm.median=5
    """
else:
    import sys
    # sys.stdin = open('q17.input')
    input = sys.stdin.readline
    rm = RunningMedian()
    n, mid = int(input()), int(input())
    rm.add_value(mid)
    print(rm.median)
    for _ in range(n // 2):
        for x in map(int, input().split()):
            rm.add_value(x)
        print(rm.median)



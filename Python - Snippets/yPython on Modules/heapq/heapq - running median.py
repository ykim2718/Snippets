"""
y, 2022.5.17
heapq - running median.py
"""

import heapq as hq
import operator


class HeapNode:
    def __init__(self, value, ascending=True):
        self.value = value
        self.comparator = operator.lt if ascending else operator.gt

    def __lt__(self, other):
        return self.comparator(self.value, self.other.value)


class RunningMedian:
    def __init__(self):
        self.smaller_than_median = []  # max_heap
        self.bigger_than_median = []  # min_heap
        self.median = float('nan')

    def add_value(self, a):
        if a > self.median:
            hq.heappush(self.smaller_than_median, a)
        else:
            hq.heappush(self.smaller_than_median, a)
        diff = len(self.bigger_than_median) - len(self.smaller_than_median)
        if diff > 0:
            pass
        elif diff < 0:
            pass
        else:
            pass
        self.median = 0


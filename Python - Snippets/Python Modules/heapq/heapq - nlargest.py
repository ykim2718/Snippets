"""
y, 2022.5.12
heaq - nlargest.py
"""

import heapq

a = [2, 6, 41, 85, 0, 3, 7, 6, 10]
n = 3
b = heapq.nlargest(n, a)
print(b)  # [85, 41, 10]

b = heapq.nsmallest(n, a)
print(b)  # [0, 2, 3]

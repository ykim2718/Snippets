"""
y, 2022.5.4
heapq - basic (2).py
https://docs.python.org/3.7/library/heapq.html
"""


from heapq import heappush, heappop, heapify, nlargest, nsmallest

a = []
heappush(a, 10)
heappush(a, 9)
heappush(a, 8)
heappush(a, 3)
heappush(a, 16)
heappush(a, 1)
print(f"{a=}")  # a=[1, 8, 3, 10, 16, 9]

a.sort(reverse=1)
print(f"{a=} << sorted")  # a=[16, 10, 9, 8, 3, 1]  << sorted

heapify(a)  # list를 heap 구조에 맞게 list data 순서를 바꿈.
print(f"{a=}")  # a=[1, 3, 9, 8, 10, 16]

heappush(a, 4)
print(f"{a=}")  # a=[1, 3, 4, 8, 10, 16, 9]

print(f"{heappop(a)=}")  # heappop(a)=1

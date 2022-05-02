"""
y, 2022.5.2
heapq - basic.py
https://docs.python.org/3.7/library/heapq.html
"""


from heapq import heappush, heappop, heapify, nlargest, nsmallest

h = []
heappush(h, (5, 'write code'))
heappush(h, (7, 'release product'))
heappush(h, (1, 'write spec'))
heappush(h, (3, 'create tests'))
print(f"{h=}")  # h=[(1, 'write spec'), (3, 'create tests'), (5, 'write code'), (7, 'release product')]
print(f"{h[0]=}")  # h[0]=(1, 'write spec')

print(f"{heappop(h)=}")  # heappop(h)=(1, 'write spec')


a = [4, 1, 7, 3, 8, 5]
heapify(a)
print(a, type(a))  # [1, 3, 5, 4, 8, 7] <class 'list'>
print(nlargest(3, a))  # [8, 7, 5]
print(nsmallest(3, a))  # [1, 3, 4]



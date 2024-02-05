"""
y, 2024.2.5
queue - PriorityQueue.py
"""

from queue import PriorityQueue

queue = PriorityQueue()
queue.put(4)
queue.put(8)
queue.put(2)
queue.put(6)

for j in range(3):
    print(j, f"{queue.get()=}")
"""
0 queue.get()=2
1 queue.get()=4
2 queue.get()=6
"""

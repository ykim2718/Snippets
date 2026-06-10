"""
y, 2020.2.26
queue - basic.py
https://www.geeksforgeeks.org/queue-in-python/
https://docs.python.org/3/library/queue.html
"""

from queue import Queue

q = Queue(maxsize=3)

print(f"q.maxsize={q.maxsize}")
print(f"q.size()={q.qsize()}")

print(f"q.put('a')={q.put('a')}")
print(f"q.put('b')={q.put('b')}")
print(f"q.put('c')={q.put('c')}")

print(f"q.queue={q.queue}")
print(f"q.queue[0]={q.queue[0]} << first item to be dequeued")
print(f"q.queue[-1]={q.queue[-1]} << last item enqueued")
print(f"q.size()={q.qsize()}")
print(f"q.full()={q.full()}")


print(f"q.get()={q.get()}")
print(f"q.get()={q.get()}")
print(f"q.get()={q.get()}")

print(f"q.size()={q.qsize()}")
print(f"q.empty()={q.empty()}")

print(f"q.put(1)={q.put(1)}")

print(f"q.size()={q.qsize()}")
print(f"q.empty()={q.empty()}")
print(f"q.full()={q.full()}")

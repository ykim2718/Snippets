"""
y, 2021.10.26
collections - deque.py
https://stackoverflow.com/questions/22772764/circular-queue-python/22772916
"""

from collections import deque

circular_queue = deque([1, 2], maxlen=4)
circular_queue.append(3)
circular_queue.extend([4])

# at this point you have [1,2,3,4]
print(circular_queue.pop())  # [1,2,3] --> 4

# key step. effectively rotate the pointer
circular_queue.rotate(-1)  # negative to the left. positive to the right

# at this point you have [2,3,1]
print(circular_queue.pop())  # [2,3] --> 1

# index
print(circular_queue)
for j in list('abcde'):
    circular_queue.append(j)
    print(circular_queue)
print(circular_queue[-1])
# print(circular_queue[2:])  # TypeError: sequence index must be integer, not 'slice'
print(min(circular_queue), max(circular_queue))
print(circular_queue > 'b')

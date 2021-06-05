"""
y, gc - 2nd.py, 2016.6.10
http://stackoverflow.com/questions/1641231/python-working-around-memory-leaks/1641280#141280
"""

from collections import defaultdict
from gc import get_objects

before = defaultdict(int)
after = defaultdict(int)
for i in get_objects():
    before[type(i)] += 1

leaked_things = [[x] for x in range(10)]
leaked_things = None  # ????

for i in get_objects():
    after[type(i)] += 1

print([(k, after[k] - before[k]) for k in after if after[k] - before[k]])

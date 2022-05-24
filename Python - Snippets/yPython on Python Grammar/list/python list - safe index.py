"""
y, 2022.5.24
python list - safe index.py
"""

import time

t = 999
a = list(range(t))
k = t - 1
n = 99999

start_time = time.time()
for _ in range(n):
    a.index(k)
print(f"running_time={(time.time() - start_time)*1000:.1f}ms")  # 1266.0ms

start_time = time.time()
for _ in range(n):
    try:
        a.index(k)
    except ValueError as ex:
        pass
print(f"running_time={(time.time() - start_time)*1000:.1f}ms")  # 1259.0ms

start_time = time.time()
for _ in range(n):
    try:
        a.index(t)  # ValueError
    except ValueError as ex:
        pass
print(f"running_time={(time.time() - start_time)*1000:.1f}ms")  # 1321.9ms

start_time = time.time()
for _ in range(n):
    if k in a:
        a.index(k)
print(f"running_time={(time.time() - start_time)*1000:.1f}ms")  # 2178.0ms

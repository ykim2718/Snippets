"""
y, 2024.8.27
python function - cache.py
"""


import time


def f(key, _cache=dict()):
    print(f"{key=}, {_cache=}")
    _cache[key] = time.ctime()


for j in range(4):
    f(j)
    time.sleep(1.0)

"""
key=0, _cache={}
key=1, _cache={0: 'Tue Aug 27 14:24:57 2024'}
key=2, _cache={0: 'Tue Aug 27 14:24:57 2024', 1: 'Tue Aug 27 14:24:58 2024'}
key=3, _cache={0: 'Tue Aug 27 14:24:57 2024', 1: 'Tue Aug 27 14:24:58 2024', 2: 'Tue Aug 27 14:24:59 2024'}
"""
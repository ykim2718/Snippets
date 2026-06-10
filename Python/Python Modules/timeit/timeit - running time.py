"""
y, timeit - running time.py, 2018.12.14
"""

import timeit
import time

start = timeit.default_timer()
time.sleep(1.5)
stop = timeit.default_timer()
running_time = stop - start
print(running_time)

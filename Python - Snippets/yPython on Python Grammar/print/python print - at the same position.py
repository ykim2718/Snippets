"""
y, python print - at the same position.py, 2018.9.19
"""

import time


for j in range(15, 0, -1):
    print('\r', j, end='', flush=True)
    time.sleep(1)
else:
    print('\r', 0)
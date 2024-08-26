"""
y, 2024.8.26
python function - recursive count.py
"""

import time

def f(_recursion=[0], _max_recursion=3):
    while 1:
        print(f"{_recursion[0]=}")
        time.sleep(0.5)
        _recursion[0] += 1
        if _recursion[0] == _max_recursion:
            break


f()

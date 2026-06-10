"""
y, 2024.2.5
bisect - insort.py
"""

import bisect

a = [60, 70, 80, 90]
bisect.insort(a, 85)
print(f"{a=}")
# a=[60, 70, 80, 85, 90]

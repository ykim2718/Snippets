"""
y, psutil - virtual_memory.py, 2018.11.20
"""

import psutil

a = psutil.virtual_memory()
print(a)
print("{:,}".format(a.available))

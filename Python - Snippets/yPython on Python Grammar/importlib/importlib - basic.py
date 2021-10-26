"""
y, 2021.10.22
importlib - basic.py
"""

import importlib

a = importlib.import_module('my module')  # 'my module.py'
print(a)

a.hello()
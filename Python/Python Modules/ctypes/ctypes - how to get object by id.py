"""
y, 2020.4.19
ctypes - how to get object by id.py
https://stackoverflow.com/questions/1396668/get-object-by-id
"""

import ctypes

a = "hello world"
print(ctypes.cast(id(a), ctypes.py_object).value)

"""
y, pathlib - file size.py, 2018.12.29
"""

import pathlib

path = pathlib.Path('./test.txt')
path.touch()
print(path.stat())
print(path.stat().st_size)

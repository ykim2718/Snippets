"""
y, pathlib - windows path to current os path.py, 2018.11.30
"""

from pathlib import Path, PureWindowsPath

a_path = r'..\pathlib'
print(a_path)
a_path = PureWindowsPath(a_path)
print(a_path)
a_path = Path(a_path)
print(a_path)
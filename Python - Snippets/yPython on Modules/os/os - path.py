"""
y, 2016.10.17, os path.py
"""
import os

a = r'a\b\c'
b = r'c\d'

c = os.path.join(a, b)
c = os.path.normpath(c)
print(c)

c = os.path.commonpath([a, b])
print(c)

c = os.path.relpath(a, b)
print(c)

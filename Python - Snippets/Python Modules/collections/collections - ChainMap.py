"""
y, 2022.5.3
collections - ChainMap.py
https://docs.python.org/3/library/collections.html#chainmap-objects
"""

from collections import ChainMap

baseline = {'music': 'bach', 'art': 'rembrandt'}
adjustments = {'art': 'van gogh', 'opera': 'carmen'}
a = ChainMap(adjustments, baseline)
print(a)  # ChainMap({'art': 'van gogh', 'opera': 'carmen'}, {'music': 'bach', 'art': 'rembrandt'})
print(f"{a.maps[0]=}")  # a.map[0]={'art': 'van gogh', 'opera': 'carmen'}
print(f"{a.maps[-1]=}")  # a.map[-1]={'music': 'bach', 'art': 'rembrandt'}

for k, v in a.items():
    print(k, v)
"""
music bach
art van gogh
opera carmen
"""
print(f"{adjustments=}")  # adjustments={'art': 'van gogh', 'opera': 'carmen'}
print(f"{baseline=}")  # baseline={'music': 'bach', 'art': 'rembrandt'}

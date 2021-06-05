"""
y, re - group basic.py, 2018.9.4
"""

import re
f = 'dc, 2018-1-1 12h13m14s, 2018-2-2 02h4m2s,2018-3-3 4h5m1s'
pattern = r'(\d+-\d+-\d+ \d+h\d+m\d+s), *(\d+-\d+-\d+ \d+h\d+m\d+s), *(\d+-\d+-\d+ \d+h\d+m\d+s)'
m = re.search(pattern, f)
print(m.group(1))
print(m.group(2))
print(m.group(3))

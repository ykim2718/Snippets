"""
y, re - find between the first parenthesis.py, 2018.8.28
"""

import re

s = 'a(21)b (cd)e'
r = re.search(r"\((.*?)\)", s).group(1)
print(r)
r = s[s.find("(")+1:s.find(")")]
print(r)

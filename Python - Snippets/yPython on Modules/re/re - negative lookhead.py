"""

y, re - negative lookhead.py, 2018.11.8
https://docs.python.org/3/library/re.html
https://wwww.regular-expressions.info/lookaround.html
"""

import re

strings = ['abc', 'a.bc', 'bcd', 'c.a.b']

pattern = r'(?<!a\.b)b\w+'
for string in strings:
    if re.search(pattern, string):
        print(string)


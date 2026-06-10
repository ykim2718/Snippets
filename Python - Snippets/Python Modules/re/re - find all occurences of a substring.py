"""
y, 2020.7.2
re - find all occurences of a substring.py
"""

import re

locations = [m.start() for m in re.finditer('a', 'abracadabra')]
print(locations)

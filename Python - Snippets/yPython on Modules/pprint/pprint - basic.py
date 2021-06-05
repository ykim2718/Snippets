"""
y, 2021.5.2
pprint - basic.py
"""

import pprint

a = [f"abc_{j}" for j in range(33)]
p = pprint.pformat(a, indent=1, width=80, compact=True)
print(p)
print('\t' + p.replace('\n', '\n\t'))

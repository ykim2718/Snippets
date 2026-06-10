"""
y, 2022.5.3
collections - ChainMap (2).py
https://docs.python.org/3/library/collections.html#chainmap-objects
"""

import builtins
from collections import ChainMap

pylookup = ChainMap(locals(), globals(), vars(builtins))
print(len(pylookup))  # 160

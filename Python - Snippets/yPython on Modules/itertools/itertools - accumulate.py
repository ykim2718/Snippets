"""
y, 2020.12.21
itertools - accumulate.py
https://docs.python.org/3/library/itertools.html#itertools.accumulate
https://docs.python.org/3/library/operator.html#operator.add
"""

import itertools
import numpy as np
import operator

a = np.arange(9)
for b in itertools.accumulate(a, func=operator.add):
    print(b)
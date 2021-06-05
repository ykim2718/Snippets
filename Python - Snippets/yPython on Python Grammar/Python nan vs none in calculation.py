"""
y, 2016.6.2, Python - nan vs none in calculation.py
"""

print('y, 2016.6.2, nan Vs. None in calculation')
import numpy as np

print("float('nan') + 2 = ", float('nan') + 2)
print("np.nan + 2 =", np.nan + 2)
print("None + 2 = ", None + 2)

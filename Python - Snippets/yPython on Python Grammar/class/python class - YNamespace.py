"""
y, Python - namespace.py, 2017.12.27
"""

import numpy as np

class Namespace:

    none = np.nan

    def __init__(self, none=np.nan):

        self.none = none

    def __getattribute__(self, item):

        try:
            return super().__getattribute__(item)
        except:
            return self.none


ns = Namespace()
ns.a = 1
print(ns.a)
print(ns.b)
print(vars(ns))
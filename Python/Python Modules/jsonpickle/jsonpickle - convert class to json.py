"""
y, jsonpickle - convert class to json.py, 2017.6.21 NO WORKING !!!!!

"""

import jsonpickle
import numpy as np

class Glass:

    integer = 1
    list_ = [0, np.nan, '', None, ]

g = Glass()

j = jsonpickle.encode(g, unpicklable=False)
print(j)

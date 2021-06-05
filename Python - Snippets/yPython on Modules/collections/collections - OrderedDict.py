"""
y, collections - OrderedDict.py, 2017.9.9
"""

import collections

a_dict = {6:7, 3: {4:5}, 1:2}
print(a_dict)

ordered_dict = collections.OrderedDict(a_dict)
print(ordered_dict)

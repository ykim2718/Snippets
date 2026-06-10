"""
y, 2016.5.15
http://stackoverflow.com/questions/6568007/how-do-i-save-and-restore-multiple-variables-in-python
http://www.benfrederickson.com/dont-pickle-your-data/
https://wiki.python.org/moin/UsingPickle
"""

import pickle
import pandas as pd

alist = [1, 2, 3]
adict = {'a': 11, 'b': 22, 'c': None}
df = pd.DataFrame(adict, index=[9])

file = __file__[:-3] + '.pickle'

# Saving the objects:
with open(file, 'wb') as f:
    pickle.dump([alist, adict], f)

# Getting back the objects:
with open(file, 'rb') as f:
    obj0, obj1 = pickle.load(f)

print(obj0)
print(obj1)

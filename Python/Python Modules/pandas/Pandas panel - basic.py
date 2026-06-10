"""
y, Pandas panel - basic.py, 2017.5.29
"""

my_file = 'Pandas panel - basic.xlsx'

import numpy as np
import pandas as pd

p = {}
p['one'] = pd.DataFrame([1, 2, 3], index=list('abc'))
p['two'] = pd.DataFrame([[10, 20], [30, 40]], columns=list('ab'), index=list('xy'))
panel = pd.Panel(p)
print(panel['one'])
print(panel['two'])

panel.to_excel(my_file)

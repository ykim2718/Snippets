"""
y, pandas - create dummy dataframe.py, 2017.12.12
"""

import pandas as pd
import numpy as np

frame = pd.DataFrame(np.arange(12).reshape(3, 4), columns=list('ABCD'))
print(frame)

frame = pd.DataFrame(np.random.randint(10, size=(5, 3)), columns=list('ABC'))
print(frame)

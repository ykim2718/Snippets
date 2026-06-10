"""
y, 2023.11.17
pandas - stack.py
https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.stack.html
"""

import pandas as pd
import numpy as np

f = pd.DataFrame(np.arange(12).reshape(3, 4))
f.index += 100
f.index.name = 'index'
f.columns = [list('AABB'), list('abab')]
f.columns.names = ['1st', '2nd']
"""
print(f)
1st  A      B    
2nd  a  b   a   
index
100  0  1   2   3
101  4  5   6   7
102  8  9  10  11
"""

print(f"{f.stack(level=0)=}")
"""
2nd         a   b
index 1st        
100   A     0   1
      B     2   3
101   A     4   5
      B     6   7
102   A     8   9
      B    10  11
"""

print(f"{f.stack(level=[0, 1])=}")
"""
f.stack(level=[0, 1])=index  1st  2nd
100    A    a       0
            b       1
       B    a       2
            b       3
101    A    a       4
            b       5
       B    a       6
            b       7
102    A    a       8
            b       9
       B    a      10
            b      11
dtype: int32
"""
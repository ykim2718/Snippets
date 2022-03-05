"""
y, 2022.3.5
mpl - table in the axes.py
https://www.delftstack.com/ko/howto/matplotlib/plot-table-using-matplotlib/
"""

import matplotlib.pyplot as plt
import pandas as pd

fig, ax1 = plt.subplots(1, 1)
a = pd.DataFrame(dict(a=[1, 2], b=[3, 'first\nsecond']), index=list('AB'))
ax1.axis('tight')
ax1.axis('off')
table = plt.table
ax1.table(
    cellText=a.values, cellLoc='left',
    rowLabels=a.index, rowLoc='right',
    colLabels=a.columns, colLoc='left',
    loc='center', edges='B'
)

plt.show()

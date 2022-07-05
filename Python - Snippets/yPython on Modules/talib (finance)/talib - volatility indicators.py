"""
y, talib - volatility indicators.py, 2018.7.25
http://ta-lib.org/
https://github.com/mrjbq7/ta-lib
http://mrjbq7.github.io/ta-lib/
http://mrjbq7.github.io/ta-lib/doc_index.html ★★★
https://www.tradingtechnologies.com/help/x-study/technical-indicator-definitions/ ★
"""

import pandas as pd
import numpy as np
import talib

_date, _open, _high, _low, _close, _volume = 'date', 'open', 'high', 'low', 'close', 'volume'
columns = [_date, _open, _high, _low, _close, _volume]
frame = pd.read_csv(r'..\_data\A000030-day.csv', usecols=columns, index_col=0, parse_dates=True, dtype=np.float32)
# print(frame.head(2))

atr = talib.ATR(frame[_high], frame[_low], frame[_close], timeperiod=14)  # Average True Range
natr = talib.NATR(frame[_high], frame[_low], frame[_close], timeperiod=14)  # Normalized Average True Range
trange = talib.TRANGE(frame[_high], frame[_low], frame[_close])  # True Range


import matplotlib.pyplot as plt
import os

fig, (ax1, ax2, ax3, ax4) = plt.subplots(nrows=4, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

file_path = __file__
file_name = os.path.basename(file_path)
fig.suptitle(file_name, fontsize='large')
fig.canvas.manager.set_window_title(file_path)

ax1.plot(frame[_open], 'r-', label='open', alpha=0.5)
ax1.plot(frame[_high], 'g-', label='high', alpha=0.5)
ax1.plot(frame[_low], 'b-', label='low', alpha=0.5)
ax1.plot(frame[_close], 'k-', label='close')
ax2.plot(atr, 'r-', label='atr')
ax3.plot(natr, 'r-', label='natr')
ax4.plot(trange, 'r-', label='trange')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


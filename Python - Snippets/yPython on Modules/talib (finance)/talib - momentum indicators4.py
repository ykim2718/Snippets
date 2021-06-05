"""
y, talib - momentum indicators4.py, 2018.7.25
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

minus_di = talib.MINUS_DI(frame[_high], frame[_low], frame[_close], timeperiod=14)  # Minus Directional Indicator
minus_dm = talib.MINUS_DM(frame[_high], frame[_low], timeperiod=14)  # Minus Directional Movement
plus_di = talib.PLUS_DI(frame[_high], frame[_low], frame[_close], timeperiod=14)  # Plus Directional Indicator
plus_dm = talib.PLUS_DM(frame[_high], frame[_low], timeperiod=14)  # Plus Directional Movement
ppo = talib.PPO(frame[_close], fastperiod=12, slowperiod=26, matype=0)  # Percentage Price Oscillator


import matplotlib.pyplot as plt
import os

fig, (ax1, ax2, ax3, ax4) = plt.subplots(nrows=4, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

file_path = __file__
file_name = os.path.basename(file_path)
fig.suptitle(file_name, fontsize='large')
fig.canvas.set_window_title(file_path)

ax1.plot(frame[_open], 'r-', label='open', alpha=0.5)
ax1.plot(frame[_high], 'g-', label='high', alpha=0.5)
ax1.plot(frame[_low], 'b-', label='low', alpha=0.5)
ax1.plot(frame[_close], 'k-', label='close')
ax2.plot(minus_di, 'r-', label='minus_di')
ax2.plot(minus_dm, 'b-', label='minus_dm')
ax3.plot(plus_di, 'r-', label='plus_di')
ax3.plot(plus_dm, 'b-', label='plus_dm')
ax4.plot(ppo, 'r-', label='ppo')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


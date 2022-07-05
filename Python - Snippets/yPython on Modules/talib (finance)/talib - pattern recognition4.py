"""
y, talib - pattern recognition4.py, 2018.7.26
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

cdlinvertedhammer = talib.CDLINVERTEDHAMMER(frame[_open], frame[_high], frame[_low], frame[_close])  # High-Wave Candle
cdlkicking = talib.CDLKICKING(frame[_open], frame[_high], frame[_low], frame[_close])  # Kicking
cdlkickingbylength = talib.CDLKICKINGBYLENGTH(frame[_open], frame[_high], frame[_low], frame[_close])  # Kicking - bull/bear determined by the longer marubozu
cdlladderbottom = talib.CDLLADDERBOTTOM(frame[_open], frame[_high], frame[_low], frame[_close])  # Ladder Bottom
cdllongleggeddoji = talib.CDLLONGLEGGEDDOJI(frame[_open], frame[_high], frame[_low], frame[_close])  # Long Legged Doji
cdllongline = talib.CDLLONGLINE(frame[_open], frame[_high], frame[_low], frame[_close])  # Long Line Candle
cdlmarubozu = talib.CDLMARUBOZU(frame[_open], frame[_high], frame[_low], frame[_close])  # Marubozu
cdlmatchinglow = talib.CDLMATCHINGLOW(frame[_open], frame[_high], frame[_low], frame[_close])  # Matching Low
cdlmathold = talib.CDLMATHOLD(frame[_open], frame[_high], frame[_low], frame[_close], penetration=0)  # Mat Hold
cdlmorningdojistar = talib.CDLMORNINGDOJISTAR(frame[_open], frame[_high], frame[_low], frame[_close], penetration=0)  # Morning Doji Star
cdlmorningstar = talib.CDLMORNINGSTAR(frame[_open], frame[_high], frame[_low], frame[_close], penetration=0)  # Morning Star


import matplotlib.pyplot as plt
import os

fig, (ax1, ax2, ax3, ax4, ax5, ax6, ax7, ax8, ax9, ax10, ax11, ax12) = plt.subplots(nrows=12, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

file_path = __file__
file_name = os.path.basename(file_path)
fig.suptitle(file_name, fontsize='large')
fig.canvas.manager.set_window_title(file_path)

ax1.plot(frame[_open], 'r-', label='open', alpha=0.5)
ax1.plot(frame[_high], 'g-', label='high', alpha=0.5)
ax1.plot(frame[_low], 'b-', label='low', alpha=0.5)
ax1.plot(frame[_close], 'k-', label='close')
ax2.plot(cdlinvertedhammer, 'r-', label='cdlinvertedhammer')
ax3.plot(cdlkicking, 'r-', label='cdlkicking')
ax4.plot(cdlkickingbylength, 'r-', label='cdlkickingbylength')
ax5.plot(cdlladderbottom, 'r-', label='cdlladderbottom')
ax6.plot(cdllongleggeddoji, 'r-', label='cdllongleggeddoji')
ax7.plot(cdllongline, 'r-', label='cdllongline')
ax8.plot(cdlmarubozu, 'r-', label='cdlmarubozu')
ax9.plot(cdlmatchinglow, 'r-', label='cdlmatchinglow')
ax10.plot(cdlmathold, 'r-', label='cdlmathold')
ax11.plot(cdlmorningdojistar, 'r-', label='cdlhomingpigeon')
ax12.plot(cdlmorningstar, 'r-', label='cdlmorningstar')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


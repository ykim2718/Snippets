"""
y, talib - pattern recognition6.py, 2018.7.26
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


cdltasukigap = talib.CDLTASUKIGAP(frame[_open], frame[_high], frame[_low], frame[_close])  # Tasuki Gap
cdlthrusting = talib.CDLTHRUSTING(frame[_open], frame[_high], frame[_low], frame[_close])  # Thrusting Pattern
cdltristar = talib.CDLTRISTAR(frame[_open], frame[_high], frame[_low], frame[_close])  # Tristar Pattern
cdlunique3river = talib.CDLUNIQUE3RIVER(frame[_open], frame[_high], frame[_low], frame[_close])  # Unique 3 River
cdlupsidegap2crows = talib.CDLUPSIDEGAP2CROWS(frame[_open], frame[_high], frame[_low], frame[_close])  # Upside Gap Two Crows
cdlxsidegap3methods = talib.CDLXSIDEGAP3METHODS(frame[_open], frame[_high], frame[_low], frame[_close])  # Upside/Downside Gap Three Methods


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
ax2.plot(cdltasukigap, 'r-', label='cdltasukigap')
ax3.plot(cdlthrusting, 'r-', label='cdlthrusting')
ax4.plot(cdltristar, 'r-', label='cdltristar')
ax5.plot(cdlunique3river, 'r-', label='cdlunique3river')
ax6.plot(cdlupsidegap2crows, 'r-', label='cdlupsidegap2crows')
ax7.plot(cdlxsidegap3methods, 'r-', label='cdlxsidegap3methods')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


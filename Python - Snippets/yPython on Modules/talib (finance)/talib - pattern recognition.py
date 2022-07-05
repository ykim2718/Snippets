"""
y, talib - pattern recognition.py, 2018.7.26
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

cdl2crows = talib.CDL2CROWS(frame[_open], frame[_high], frame[_low], frame[_close])  # Two Crows
cdl3blackcrows = talib.CDL3BLACKCROWS(frame[_open], frame[_high], frame[_low], frame[_close])  # Three Black Crows
cdl3inside = talib.CDL3INSIDE(frame[_open], frame[_high], frame[_low], frame[_close])  # Three Inside Up/Down
cdl3insidestrike = talib.CDL3LINESTRIKE(frame[_open], frame[_high], frame[_low], frame[_close])  # Three-Line Strike
cdl3outside = talib.CDL3OUTSIDE(frame[_open], frame[_high], frame[_low], frame[_close])  # Three Outside Up/Down
cdl3starsinsouth = talib.CDL3STARSINSOUTH(frame[_open], frame[_high], frame[_low], frame[_close])  # Three Stars In The South
cdl3whitesoldiers = talib.CDL3WHITESOLDIERS(frame[_open], frame[_high], frame[_low], frame[_close])  # Three Advancing White Soldiers
cdlabandonedbaby = talib.CDLABANDONEDBABY(frame[_open], frame[_high], frame[_low], frame[_close], penetration=0)  # Abandoned Baby
cdladvanceblock = talib.CDLADVANCEBLOCK(frame[_open], frame[_high], frame[_low], frame[_close])  # Advance Block
cdlbelthold = talib.CDLBELTHOLD(frame[_open], frame[_high], frame[_low], frame[_close])  # Belt-hold
cdlbreakaway = talib.CDLBREAKAWAY(frame[_open], frame[_high], frame[_low], frame[_close])  # Breakaway

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
ax2.plot(cdl2crows, 'r-', label='cdl2crows')
ax3.plot(cdl3blackcrows, 'r-', label='cdl3blackcrows')
ax4.plot(cdl3inside, 'r-', label='cdl3inside')
ax5.plot(cdl3insidestrike, 'r-', label='cdl3insidestrike')
ax6.plot(cdl3outside, 'r-', label='cdl3outside')
ax7.plot(cdl3starsinsouth, 'r-', label='cdl3starsinsouth')
ax8.plot(cdl3whitesoldiers, 'r-', label='cdl3whitesoldiers')
ax9.plot(cdlabandonedbaby, 'r-', label='cdlabandonedbaby')
ax10.plot(cdladvanceblock, 'r-', label='cdladvanceblock')
ax11.plot(cdlbelthold, 'r-', label='cdlbelthold')
ax12.plot(cdlbreakaway, 'r-', label='cdlbreakaway')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


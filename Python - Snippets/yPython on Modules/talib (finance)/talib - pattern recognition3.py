"""
y, talib - pattern recognition3.py, 2018.7.26
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

cdlgravestonedoji = talib.CDLGRAVESTONEDOJI(frame[_open], frame[_high], frame[_low], frame[_close])  # Gravestone Doji
cdlhammer = talib.CDLHAMMER(frame[_open], frame[_high], frame[_low], frame[_close])  # Hammer
cdlhangingman = talib.CDLHANGINGMAN(frame[_open], frame[_high], frame[_low], frame[_close])  # Hanging Man
cdlharami = talib.CDLHARAMI(frame[_open], frame[_high], frame[_low], frame[_close])  # Harami Pattern
cdlharamicross = talib.CDLHARAMICROSS(frame[_open], frame[_high], frame[_low], frame[_close])  # Harami Cross Pattern
cdlhighwave = talib.CDLHIGHWAVE(frame[_open], frame[_high], frame[_low], frame[_close])  # High-Wave Candle
cdlhikkake = talib.CDLHIKKAKE(frame[_open], frame[_high], frame[_low], frame[_close])  # Hikkake Pattern
cdlhikkakemod = talib.CDLHIKKAKEMOD(frame[_open], frame[_high], frame[_low], frame[_close])  # Modified Hikkake Pattern
cdlhomingpigeon = talib.CDLHOMINGPIGEON(frame[_open], frame[_high], frame[_low], frame[_close])  # Homing Pigeon
cdlidentical3crows = talib.CDLIDENTICAL3CROWS(frame[_open], frame[_high], frame[_low], frame[_close])  # Identical Three Crows
cdlinneck = talib.CDLINNECK(frame[_open], frame[_high], frame[_low], frame[_close])  # In-Neck Pattern


import matplotlib.pyplot as plt
import os

fig, (ax1, ax2, ax3, ax4, ax5, ax6, ax7, ax8, ax9, ax10, ax11, ax12) = plt.subplots(nrows=12, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

file_path = __file__
file_name = os.path.basename(file_path)
fig.suptitle(file_name, fontsize='large')
fig.canvas.set_window_title(file_path)

ax1.plot(frame[_open], 'r-', label='open', alpha=0.5)
ax1.plot(frame[_high], 'g-', label='high', alpha=0.5)
ax1.plot(frame[_low], 'b-', label='low', alpha=0.5)
ax1.plot(frame[_close], 'k-', label='close')
ax2.plot(cdlgravestonedoji, 'r-', label='cdlgravestonedoji')
ax3.plot(cdlhammer, 'r-', label='cdlhammer')
ax4.plot(cdlhangingman, 'r-', label='cdlhangingman')
ax5.plot(cdlharami, 'r-', label='cdlharami')
ax6.plot(cdlharamicross, 'r-', label='cdlharamicross')
ax7.plot(cdlhighwave, 'r-', label='cdlhighwave')
ax8.plot(cdlhikkake, 'r-', label='cdlhikkake')
ax9.plot(cdlhikkakemod, 'r-', label='cdlhikkakemod')
ax10.plot(cdlhomingpigeon, 'r-', label='cdlhomingpigeon')
ax11.plot(cdlidentical3crows, 'r-', label='cdlidentical3crows')
ax12.plot(cdlinneck, 'r-', label='cdlinneck')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


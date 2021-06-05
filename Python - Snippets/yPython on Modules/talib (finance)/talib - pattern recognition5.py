"""
y, talib - pattern recognition5.py, 2018.7.26
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

cdlonneck = talib.CDLONNECK(frame[_open], frame[_high], frame[_low], frame[_close])  # On-Neck Pattern
cdlpiercing = talib.CDLPIERCING(frame[_open], frame[_high], frame[_low], frame[_close])  # Piercing Pattern
cdlrickshawman = talib.CDLRICKSHAWMAN(frame[_open], frame[_high], frame[_low], frame[_close])  # Rickshaw Man
cdlrisefall3methods = talib.CDLRISEFALL3METHODS(frame[_open], frame[_high], frame[_low], frame[_close])  # Rising/Falling Three Methods
cdlseparatinglines = talib.CDLSEPARATINGLINES(frame[_open], frame[_high], frame[_low], frame[_close])  # Separating Lines
cdlshootingstar = talib.CDLSHOOTINGSTAR(frame[_open], frame[_high], frame[_low], frame[_close])  # Shooting Star
cdlshortline = talib.CDLSHORTLINE(frame[_open], frame[_high], frame[_low], frame[_close])  # Short Line Candle
cdlspinningtop = talib.CDLSPINNINGTOP(frame[_open], frame[_high], frame[_low], frame[_close])  # Spinning Top
cdlstalledpattern = talib.CDLSTALLEDPATTERN(frame[_open], frame[_high], frame[_low], frame[_close])  # Stalled Pattern
cdlsticksandwich = talib.CDLSTICKSANDWICH(frame[_open], frame[_high], frame[_low], frame[_close])  # Stick Sandwich
cdltakuri = talib.CDLTAKURI(frame[_open], frame[_high], frame[_low], frame[_close])  # Takuri (Dragonfly Doji with very long lower shadow)


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
ax2.plot(cdlonneck, 'r-', label='cdlonneck')
ax3.plot(cdlpiercing, 'r-', label='cdlpiercing')
ax4.plot(cdlrickshawman, 'r-', label='cdlrickshawman')
ax5.plot(cdlrisefall3methods, 'r-', label='cdlrisefall3methods')
ax6.plot(cdlseparatinglines, 'r-', label='cdlseparatinglines')
ax7.plot(cdlshootingstar, 'r-', label='cdlshootingstar')
ax8.plot(cdlshortline, 'r-', label='cdlshortline')
ax9.plot(cdlspinningtop, 'r-', label='cdlspinningtop')
ax10.plot(cdlstalledpattern, 'r-', label='cdlstalledpattern')
ax11.plot(cdlsticksandwich, 'r-', label='cdlsticksandwich')
ax12.plot(cdltakuri, 'r-', label='cdltakuri')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


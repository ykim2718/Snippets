"""
y, talib - cyclic indicators.py, 2018.7.26
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

ht_dcperiod = talib.HT_DCPERIOD(frame[_close])  # Hilbert Transform - Dominant Cycle Period
ht_dcphase = talib.HT_DCPHASE(frame[_close])  # Hilbert Transform - Dominant Cycle Phase
inphase, quadrature = talib.HT_PHASOR(frame[_close])  # Hilbert Transform - Phasor Components
sine, leadsine = talib.HT_SINE(frame[_close])  # Hilbert Transform - SineWave
ht_trendmode = talib.HT_TRENDMODE(frame[_close])  # Hilbert Transform - Trend vs Cycle Mode


import matplotlib.pyplot as plt
import os

fig, (ax1, ax2, ax3, ax4, ax5, ax6) = plt.subplots(nrows=6, sharex=True)
fig.subplots_adjust(wspace=0, hspace=0)

file_path = __file__
file_name = os.path.basename(file_path)
fig.suptitle(file_name, fontsize='large')
fig.canvas.set_window_title(file_path)

ax1.plot(frame[_open], 'r-', label='open', alpha=0.5)
ax1.plot(frame[_high], 'g-', label='high', alpha=0.5)
ax1.plot(frame[_low], 'b-', label='low', alpha=0.5)
ax1.plot(frame[_close], 'k-', label='close')
ax2.plot(ht_dcperiod, 'r-', label='ht_dcperiod')
ax3.plot(ht_dcphase, 'r-', label='ht_dcphase')
ax4.plot(inphase, 'r-', label='inphase')
ax4.plot(quadrature, 'b-', label='quadrature')
ax5.plot(sine, 'r-', label='sine')
ax5.plot(leadsine, 'b-', label='leadsine')
ax6.plot(ht_trendmode, 'r-', label='ht_trendmode')

for ax in fig.axes:
    ax.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc='upper left', fontsize='small')
plt.show()


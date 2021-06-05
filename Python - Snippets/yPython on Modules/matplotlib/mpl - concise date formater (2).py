"""
y, 2020.2.3
mpl - concise date formater
https://matplotlib.org/3.1.0/gallery/ticks_and_spines/date_concise_formatter.html
"""

import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.units as munits
import numpy as np

converter = mdates.ConciseDateConverter()
munits.registry[np.datetime64] = converter
munits.registry[dt.date] = converter
munits.registry[dt.datetime] = converter

base = dt.datetime(2005, 2, 1)
dates = np.array([base + dt.timedelta(hours=(2 * i)) for i in range(732)])
N = len(dates)
np.random.seed(19680801)
y = np.cumsum(np.random.randn(N))
lims = [(np.datetime64('2005-02'), np.datetime64('2005-04')),
        (np.datetime64('2005-02-03'), np.datetime64('2005-02-15')),
        (np.datetime64('2005-02-03 11:00'), np.datetime64('2005-02-04 13:20'))]

fig, axs = plt.subplots(3, 1) #  , constrained_layout=True, figsize=(6, 6))
for nn, ax in enumerate(axs):
    ax.plot(dates, y)
    ax.set_xlim(lims[nn])
axs[0].set_title('Concise Date Formatter')

plt.show()

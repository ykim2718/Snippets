"""
y, 2020.12.9
urllib2 - singal filtering (butterworth filter).py
https://oceanpython.org/2013/03/11/signal-filtering-butterworth-filter/
"""

import urllib.request
import io
import csv
import numpy as np
from datetime import datetime
import pandas as pd

startdate = '20111118'
startdate = '20000l01'
enddate = '20121125'

# Read data from LOBO buoy
response = urllib.request.urlopen(
    'http://lobo.satlantic.com/cgi-data/nph-data.cgi?min_date=' + startdate + '&max_date=' + enddate + '&y=temperature')
bytes = response.read()
data = io.StringIO(bytes.decode('utf-8'))
frame = pd.read_csv(data, sep='\t')
col_date = 'date [AST]'
col_temp = 'temperature [C]'
frame[col_date] = pd.to_datetime(frame[col_date])
print(f"frame.shape={frame.shape}")
print(f"frame.dtypes={frame.dtypes}")


import scipy.signal as signal
import matplotlib.pyplot as plt

# First, design the Buterworth filter
N = 2  # Filter order
Wn = 0.01  # Cutoff frequency
B, A = signal.butter(N, Wn, output='ba')

# Second, apply the filter
tempf = signal.filtfilt(B, A, frame[col_temp])

# Make plots
fig = plt.figure()
ax1 = fig.add_subplot(211)
plt.plot(frame[col_date], frame[col_temp], 'b-')
plt.plot(frame[col_date], tempf, 'r-', linewidth=2)
plt.ylabel(col_temp)
plt.legend(['Original', 'Filtered'])
plt.title("Temperature from LOBO (Halifax, Canada)")
ax1.axes.get_xaxis().set_visible(False)

ax1 = fig.add_subplot(212)
plt.plot(frame[col_date], frame[col_temp] - tempf, 'b-')
plt.ylabel(col_temp)
plt.xlabel(col_date)
plt.legend(['Residuals'])
plt.show()

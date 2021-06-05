"""
y, fbprohet - quick start.py, 2018.4.13

https://facebook.github.io/prophet/docs/quick_start.html#python-api
"""

import pandas as pd
import numpy as np
from fbprophet import Prophet

import os
file_path = './sample/A000020-day.csv'

df = pd.read_csv(file_path, parse_dates=True)
df = df.tail(1000)
df = df.reset_index(drop=False)
df['y'] = np.log(df['close'])
df.rename(columns={'date': 'ds'}, inplace=True)
print(df.head())

m = Prophet()
m.fit(df)

future = m.make_future_dataframe(periods=365)
print(future.tail())

forecast = m.predict(future)
print(forecast[['ds', 'yhat', 'yhat_lower', 'yhat_upper']].tail())

import matplotlib.pyplot as plt
m.plot(forecast)
m.plot_components(forecast)
plt.show()

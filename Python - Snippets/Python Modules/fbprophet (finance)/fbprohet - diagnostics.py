"""
y, fbprohet - diagnostics.py, 2018.4.13

https://facebook.github.io/prophet/docs/diagnostics.html
"""

import pandas as pd
import numpy as np
import fbprophet as fbp
import fbprophet.diagnostics as fbp_diagnostics

import os
file_path = './sample/A000020-day.csv'

df = pd.read_csv(file_path, parse_dates=True)
df = df.tail(1000)
df = df.reset_index(drop=True)
df['y'] = np.log(df['close'])
df.rename(columns={'date': 'ds'}, inplace=True)
# print(df.head())

m = fbp.Prophet(changepoint_prior_scale=0.5, changepoints=['2017-01-01'])
m.fit(df)
future = m.make_future_dataframe(periods=365)
# forecast = m.predict(future)
# print(forecast[['ds', 'yhat', 'yhat_lower', 'yhat_upper']].tail())

df_cv = fbp_diagnostics.cross_validation(m, horizon='100 days')
forecast = df_cv

???

import matplotlib.pyplot as plt
m.plot(forecast)
# m.plot_components(forecast)
plt.show()

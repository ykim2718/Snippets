"""
Y, pandas - datareader2.py, 2016.4.16
Y, Please go see URL below for more details
http://pandas-datareader.readthedocs.org/en/latest/remote_data.html#remote-data-yahoo
"""

from pandas_datareader import wb

print(wb.search('gdp.*capita.*const').iloc[:, :2])

from pandas_datareader.data import Options

aapl = Options('aapl', 'yahoo')
data = aapl.get_all_data()
print(data.iloc[0:5, 0:5])

data = aapl.get_near_stock_price(expiry=aapl.expiry_dates[0:3])
print(data.iloc[0:5:, 0:5])

ind = ['NY.GDP.PCAP.KD', 'IT.MOB.COV.ZS']
dat = wb.download(indicator=ind, country='all', start=2011, end=2011).dropna()
dat.columns = ['gdp', 'cellphone']
print(dat.tail())

"""
we use the statsmodels package to assess the relationship between our two variables
using ordinary least squares regression. Unsurprisingly, populations in rich countries
tend to use cellphones at a higher rate:
"""
import numpy as np
import statsmodels.formula.api as smf

mod = smf.ols("cellphone ~ np.log(gdp)", dat).fit()
print(mod.summary())

"""
OECD Statistics are avaliable via DataReader. You have to specify OECD’s data set code.
To confirm data set code, access to each data -> Export -> SDMX Query.
Following example is to download “Trade Union Density” data which set code is “UN_DEN”.
"""
import pandas_datareader.data as web
import datetime

df = web.DataReader('UN_DEN', 'oecd', end=datetime.datetime(2012, 1, 1))
print(df)

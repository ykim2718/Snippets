"""
pandas - datareader.py
http://pandas-datareader.readthedocs.org/en/latest/remote_data.html#yahoo-finance
http://www.eoddata.com/stocklist/NASDAQ/A.htm
"""
import pandas as pd
import pandas_datareader.data as web
import datetime

"""
from pandas.io import data, wb
The pandas.io.data module is moved to a separate package (pandas-datareader) and
will be removed from pandas in a future version.
After installing the pandas-datareader package (https://github.com/pydata/pandas-datareader),
you can change the import ``from pandas.io import data, wb`` to ``from pandas_datareader import data, wb``.
"""

"""
def DataReader(name, data_source=None, start=None, end=None,
               retry_count=3, pause=0.001):
    Imports data from a number of online sources.

    Currently supports Yahoo! Finance, Google Finance, St. Louis FED (FRED)
    and Kenneth French's data library.

    Parameters
    ----------
    name : str or list of strs
        the name of the dataset. Some data sources (yahoo, google, fred) will
        accept a list of names.
    data_source: {str, None}
        the data source ("yahoo", "yahoo-actions", "google", "fred", or "ff")
    start : {datetime, None}
        left boundary for range (defaults to 1/1/2010)
    end : {datetime, None}
        right boundary for range (defaults to today)
    retry_count : {int, 3}
        Number of times to retry query request.
    pause : {numeric, 0.001}
        Time, in seconds, to pause between consecutive queries of chunks. If
        single value given for symbol, represents the pause between retries.

    Examples
    ----------

    # Data from Yahoo! Finance
    gs = DataReader("GS", "yahoo")

    # Corporate Actions (Dividend and Split Data) with ex-dates from Yahoo! Finance
    gs = DataReader("GS", "yahoo-actions")

    # Data from Google Finance
    aapl = DataReader("AAPL", "google")

    # Data from FRED
    vix = DataReader("VIXCLS", "fred")

    # Data from Fama/French
    ff = DataReader("F-F_Research_Data_Factors", "famafrench")
    ff = DataReader("F-F_Research_Data_Factors_weekly", "famafrench")
    ff = DataReader("6_Portfolios_2x3", "famafrench")
    ff = DataReader("F-F_ST_Reversal_Factor", "famafrench")

    AAPL Apple
    IXIC Nasdaq Composite
    005930.KS Samsung
"""


def yGetStock(code, start, end, period):
    """
    Y, 2016.4.11-12
    :param code: stock code
    :param start: starting date
    :param end: ending date
    :param period: daily, weekly, monthly, quarterly, yearly
    :return: Pandas Dataframe (colums=['Open','High','Low','Close','Volume','AdjClose'])
    """
    df = None
    columns = ['Open', 'High', 'Low', 'Close', 'Volume', 'AdjClose']
    try:
        df = web.DataReader(code, 'yahoo', start, end)
    except:
        pass
        try:
            df = web.DataReader(code, 'google', start, end)
        except:
            pass
            df = None
            # later, from Quandl

    # merge referring to columns

    # average calculation by period

    return df


if __name__ == '__main__':

    start = datetime.datetime(2016, 1, 1)
    end = datetime.datetime(2016, 4, 13)
    code = 'AAPL'

    df = pd.DataFrame([])
    try:
        df = web.DataReader(code, 'google', start, end)
        print(df.head(2))
        df = web.DataReader(code, 'yahoo', start, end)
        print(df.head(2))
        # raise Exception('lala')
    except Exception as ex:
        print("[{0}] {1!r}".format(type(ex).__name__, ex.args))
        pass

    print(df.columns)

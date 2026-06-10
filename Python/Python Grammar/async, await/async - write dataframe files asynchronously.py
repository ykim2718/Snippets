"""
y, 2020.3.11
async - write dataframe files asynchronously.py
https://stackoverflow.com/questions/57760869/python-how-to-use-asyncio-with-huge-csv-files-to-send-asynchronous-requests-fro
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.to_pickle.html
"""

import asyncio
import pathlib
import pandas as pd
import numpy as np
import datetime as dt

frame = pd.DataFrame([[1, 2.0, 3., 4., 5., None, np.nan, pd.Timestamp.now(), 'No pain no gain']] * int(1e3))


async def write_csv(frame):
    file_path = pathlib.Path(__file__).with_suffix('.csv')
    async with asyncio.Lock():
        frame.to_csv(file_path)
    message = f"write_csv()={dt.datetime.now()}"
    return message, 'csv'


async def write_pickle(frame):
    file_path = pathlib.Path(__file__).with_suffix('.pkl')
    async with asyncio.Lock():
        frame.to_pickle(file_path, compression='gzip')
    message = f"write_pickle()={dt.datetime.now()}"
    return message, 'pickle'


async def write_hdf5(frame):
    file_path = pathlib.Path(__file__).with_suffix('.h5')
    frame = frame.fillna('NONE')  # avoid PerformanceWarning coming from NaN value, 2020.3.11
    async with asyncio.Lock():
        frame.to_hdf(file_path, 'your_key', complevel=9)
    message = f"write_hdf5()={dt.datetime.now()}"
    return message, 'hdf5'


def complete_cb(t: asyncio.Future):
    if not t.cancelled():
        x = t.result()
        print(f"complete_cb(): {x}")


async def work():
    routines = [write_csv, write_pickle, write_hdf5]
    aws = []  # awaitables
    for routine in routines:
        task = asyncio.create_task(routine(frame))
        task.add_done_callback(complete_cb)
        aws.append(task)
    await asyncio.gather(*aws)


loop = asyncio.get_event_loop()
server = loop.run_until_complete(work())

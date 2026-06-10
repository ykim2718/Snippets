"""
y, 2020.3.11
async - write dataframe files asynchronously (2).py
https://stackoverflow.com/questions/57760869/python-how-to-use-asyncio-with-huge-csv-files-to-send-asynchronous-requests-fro
https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.to_pickle.html
"""

import asyncio
import pathlib
import pandas as pd
import numpy as np
import functools

frame = pd.DataFrame([[1, 2.0, 3., 4., 5., None, np.nan, pd.Timestamp.now(), 'No pain no gain']] * int(1e3))


async def write_csv(frame):
    return frame, 'csv'


async def write_pickle(frame):
    return frame, 'pickle'


async def write_hdf5(frame):
    frame = frame.fillna('NONE')  # avoid PerformanceWarning coming from NaN value, 2020.3.11
    return frame, 'hdf5'


def cb_write(t: asyncio.Future, j):
    if t.cancelled():
        return
    frame, file_type = t.result()
    print(j, frame.shape, file_type)
    if file_type == 'csv':
        file_path = pathlib.Path(__file__).with_suffix('.csv')
        frame.to_csv(file_path)
    elif file_type == 'pickle':
        file_path = pathlib.Path(__file__).with_suffix('.pkl')
        frame.to_pickle(file_path, compression='gzip')
    elif file_type == 'hdf5':
        file_path = pathlib.Path(__file__).with_suffix('.h5')
        frame.to_hdf(file_path, 'your_key', complevel=9)


async def work():
    routines = [write_csv, write_pickle, write_hdf5]
    aws = []  # awaitables
    for j, routine in enumerate(routines):
        task = asyncio.create_task(routine(frame))
        task.add_done_callback(functools.partial(cb_write, j=j))
        aws.append(task)
    await asyncio.gather(*aws)


loop = asyncio.get_event_loop()
server = loop.run_until_complete(work())

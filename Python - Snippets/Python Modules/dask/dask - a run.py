"""
y, 2020.2.11
dask - a run.py
https://github.com/dask/distributed/issues/1308
"""

from dask import delayed
from dask.distributed import Client, progress


def run():
    client = Client()
    result = delayed(lambda x: x + 2)(3)
    future = client.compute(result)
    progress(future)
    client.close()


if __name__ == '__main__':
    run()

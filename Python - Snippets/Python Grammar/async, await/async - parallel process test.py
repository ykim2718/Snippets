"""
y, 2020.5.7
async - parallel process test.py
"""

import datetime as dt
import pandas as pd
import asyncio
import functools
import threading
import time


def cb_write(t: asyncio.Future, file_path, lock):

    if t.cancelled():
        return
    fetched = t.result()
    assert isinstance(fetched, (type(None), pd.DataFrame))
    with lock:
        print(fetched.to_dict(), dt.datetime.now())


def lazy_process(k):

    time.sleep(k)
    return k


async def fetch_one(message):

    if False:
        await asyncio.sleep(message)
    else:
        if False:
            lazy_process(message)
        else:
            lazy_worker = functools.partial(lazy_process, message)
            await loop.run_in_executor(None, lazy_worker)
    now = dt.datetime.now()
    # print(f"message={message} at {now}")
    return pd.DataFrame({message: [now]})


async def fetch_all(lock):

    aws = []  # awaitables
    start_time = dt.datetime.now()
    for j in reversed(range(5)):
        task = asyncio.create_task(fetch_one(j))
        task.add_done_callback(functools.partial(cb_write, file_path=None, lock=lock))
        aws.append(task)
    await asyncio.gather(*aws)
    now = dt.datetime.now()
    print(f"fetch_all() spent {now - start_time}")
    results = [r.result() for r in aws]
    return results


if __name__ == '__main__':

    _lock = threading.Lock()
    j = 0
    start_time = dt.datetime.now()
    while True:
        now = dt.datetime.now()
        print(f"[{j}] now={now}, elapsed={now - start_time}")
        j += 1
        if False:
            loop = asyncio.get_event_loop()
            server = loop.run_until_complete(fetch_all(_lock))
        else:
            loop = asyncio.new_event_loop()
            asyncio.set_event_loop(loop)
            results = loop.run_until_complete(fetch_all(_lock))
            loop.close()


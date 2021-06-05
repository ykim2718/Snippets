"""
y, 2020.3.23 - 25
async - with thread.py
https://stackoverflow.com/questions/46727787/runtimeerror-there-is-no-current-event-loop-in-thread-in-async-apscheduler
"""

import asyncio
import functools
import threading
import time
import random

random.seed(777)
gil = [0]  # container vulnerable to be contaminated by many async routines


async def fetch_one(query):
    k = random.randint(1, 5)
    await asyncio.sleep(k)
    return f"fetched by {query} at {time.strftime('%M:%S', time.localtime())}", k


def cb_write(t: asyncio.Future, task, lock):
    if t.cancelled():
        return
    fetched, delay = t.result()
    if False:
        with lock:
            gil[0] = task
            time.sleep(1)
            print(f"wrote [task={task}] {fetched}, delay={delay} ... {gil[0] == task}")
    else:
        gil[0] = task
        time.sleep(1)
        print(f"wrote [task={task}] {fetched}, delay={delay} ... {gil[0] == task}")


async def fetch_all(queries, lock):
    aws = []  # awaitables
    for j, query in enumerate(queries):
        task = asyncio.create_task(fetch_one(query))
        task.add_done_callback(functools.partial(cb_write, task=j, lock=lock))
        aws.append(task)
    await asyncio.gather(*aws)
    results = [r.result() for r in aws]
    return results


def worker_thread(worker, stop_event, lock):
    j = 0
    while not stop_event.is_set():
        print(f"worker={worker} beginning cycle {j} at {time.strftime('%M:%S', time.localtime())}")
        start_time = time.time()
        queries = []
        for k in range(4):
            queries.append(f"{worker}_{j}.{k}")
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        results = loop.run_until_complete(fetch_all(queries, lock))
        loop.close()
        print(f"worker={worker} end of cycle: running time="
              f"{time.strftime('%M:%S', time.gmtime(time.time() - start_time))}", results)
        j += 1
        if j > 4:
            stop_event.set()


workers = ['worker1', 'worker2']
# workers = ['worker1']

worker_threads = []
_lock = threading.Lock()
for worker in workers:
    _stop_event = threading.Event()
    worker_threads.append(threading.Thread(target=worker_thread, args=(worker, _stop_event, _lock), name=worker))
    worker_threads[-1]._stop_event = _stop_event
    worker_threads[-1].start()


def kill_threads(threads):
    for t in threads:
        if t.is_alive():
            t._stop_event.set()
            print(f"Killed thread: {t.name}")
        else:
            print(f"Found dead thread: {t.name}")


# loop forever unless any fails
j = 0
while True:
    time.sleep(1)
    all_alive = all([t.is_alive() for t in worker_threads])
    if all_alive:
        continue
    else:
        kill_threads(worker_threads)
        break
    j += 1

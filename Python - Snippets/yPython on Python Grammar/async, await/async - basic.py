"""
y, 2020.3.8 - 9
async - basic.py
[1] https://docs.python.org/ko/3.7/library/asyncio-task.html
[2] https://soooprmx.com/archives/6882
"""

import asyncio
import time


async def say_after(delay, what):
    if True:
        await asyncio.sleep(delay)
    elif False:
        time.sleep(delay)  # Note: time.sleep() blocks the current thread, ie. other coroutines [2], 2020.3.9
    else:
        for j in range(int(3.45e7) * delay):  # 1 second * delay
            pass
    print(what)  # blocks the current thread at a very short time , 2020.3.9
    return f"{what}={delay}"


async def serial_task():
    start_time = time.time()
    await say_after(2, 'hello')
    await say_after(1, 'world')
    print(f"serial task time={time.strftime('%H:%M:%S', time.gmtime(time.time() - start_time))}")


async def parallel_task():
    start_time = time.time()
    task1 = asyncio.create_task(say_after(2, 'hello'))
    task2 = asyncio.create_task(say_after(1, 'world'))
    result_1 = await task1
    result_2 = await task2
    print(f"{result_1}")
    print(f"{result_2}")
    print(f"parallel task time={time.strftime('%H:%M:%S', time.gmtime(time.time() - start_time))}")


async def parallel_task_2():
    start_time = time.time()
    task1 = asyncio.create_task(say_after(2, 'hello'))
    task2 = asyncio.create_task(say_after(1, 'world'))
    done, pending = await asyncio.wait({task1, task2})
    print(f"done={done}", task1 in done, task2 in done)
    print(f"pending={pending}")
    print(f"parallel task_2 time={time.strftime('%H:%M:%S', time.gmtime(time.time() - start_time))}")
    for f in pending:
        f.cancel()
    for f in done:
        print(await f)


asyncio.run(serial_task())
asyncio.run(parallel_task())
asyncio.run(parallel_task_2())

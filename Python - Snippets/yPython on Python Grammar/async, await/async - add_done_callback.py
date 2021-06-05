"""
y, 2020.3.9
async - add_done_callback.py
https://docs.python.org/ko/3.7/library/asyncio-future.html#asyncio.Future.add_done_callback
https://soooprmx.com/archives/6882
"""

import asyncio


def complete_cb(t: asyncio.Future):
    if not t.cancelled():
        x = t.result()
        print(f'result={x}')
    else:
        print('Cancelled')


async def lazy_sum(x: int) -> int:
    s, i = 0, 1
    while i <= x:
        await asyncio.sleep(0.1)
        i, s = i + 1, s + i
        print(s)
    return s


async def main():
    task = asyncio.create_task(lazy_sum(5))
    task.add_done_callback(complete_cb)
    await asyncio.wait_for(task, 10)


asyncio.run(main())

"""
y, 2020.3.9; 2022.7.28
async - add_done_callback.py
https://docs.python.org/ko/3.7/library/asyncio-future.html#asyncio.Future.add_done_callback
https://soooprmx.com/archives/6882
https://docs.python.org/ko/3.10/library/asyncio-task.html
"""

import asyncio
import time


def complete_cb(t: asyncio.Future):
    if not t.cancelled():
        x = t.result()
        print(f"complete_cb(): result={x} at {time.strftime('%X')}")
    else:
        print(f"Cancelled at {time.strftime('%X')}")


async def lazy_sum(x: int) -> int:
    s, i = 0, 1
    while i <= x:
        await asyncio.sleep(1)
        i, s = i + 1, s + i
        print(f"{s=} ({x=})")
    return s


async def main():
    task = asyncio.create_task(lazy_sum(5))
    task.add_done_callback(complete_cb)
    timeout = None  # timeout은 None 또는 대기할 float 나 int 초 수입니다. timeout이 None이면 퓨처가 완료될 때까지 블록합니다.
    # timeout = 4
    print(f"main(): started at {time.strftime('%X')}")
    try:
        result = await asyncio.wait_for(task, timeout)
        print(f"main(): {result=}")
    except asyncio.TimeoutError:
        print(f"timeout! at {time.strftime('%X')}")
    print(f"main(): ended at {time.strftime('%X')}")


asyncio.run(main())

"""
main(): started at 13:06:53
s=1 (x=5)
s=3 (x=5)
s=6 (x=5)
s=10 (x=5)
s=15 (x=5)
complete_cb(): result=15 at 13:06:58
main(): result=15
main(): ended at 13:06:58
"""

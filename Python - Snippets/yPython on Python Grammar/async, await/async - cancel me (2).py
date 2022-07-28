"""
y, 2020.3.9; 2022.7.28
async - cancel me (2).py
https://docs.python.org/3/library/asyncio-task.html
"""

import asyncio
import time


async def cancel_me():
    try:
        await asyncio.sleep(3600)  # 1 hour
    except asyncio.CancelledError as ex:
        print(f"cancel_me(): {ex=} at {time.strftime('%X')}")
        raise


async def main():
    task = asyncio.create_task(cancel_me())

    await asyncio.sleep(1)
    task.cancel()

    try:
        await asyncio.wait_for(task, None)
    except asyncio.CancelledError as ex:
        print(f"main(): {ex=} at {time.strftime('%X')}")


asyncio.run(main())

"""
cancel_me(): ex=CancelledError() at 13:03:47
main(): ex=CancelledError() at 13:03:47
"""

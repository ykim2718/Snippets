"""
y, 2022.9.12
asyncio - background job.py
"""

import asyncio


async def main():
    print('Hello ...')
    await asyncio.sleep(1)
    print('... World!')


print('before run')
asyncio.run(main())  # not background running, 2022.9.12 :<
print('after run')

"""
before run
Hello ...
... World!
after run
"""
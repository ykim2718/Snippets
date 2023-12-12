import asyncio


async def hello(delay=2):
    assert isinstance(delay, int)
    print('Hello, ' + '.' * delay, end=' ')
    await asyncio.sleep(delay)
    print('world!')


if False:
    loop = asyncio.get_event_loop()
    loop.run_until_complete(hello())
    loop.close()
else:
    asyncio.run(hello())

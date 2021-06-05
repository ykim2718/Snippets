"""
y, aiohttp - download.py, 2019.3.31
https://item4.github.io/2017-11-26/Asynchronous-HTTP-Request-with-aiohttp/
"""

# TODO 2019.3.31: Need to upgrade code macthing with current python version !!!

if False:
    import requests

    for i in range(128):
        res = requests.get(f'http://www.randomtext.me/api/lorem/p-1/32')
        with open(f'{i}.txt', 'w') as f:
            f.write(res.text)

else:
    import asyncio
    import aiohttp
    import aiofiles

    async def download(i: int):
        async with aiohttp.ClientSession() as session:
            async with session.get(f'http://www.randomtext.me/api/lorem/p-1/32') as resp:
                async with aiofiles.open(f'{i}.txt', 'w') as f:
                    await f.write(await resp.text())


    tasks = [download(x) for x in range(128)]
    asyncio.run(asyncio.wait(tasks))
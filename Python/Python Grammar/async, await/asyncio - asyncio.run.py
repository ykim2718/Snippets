"""
y, 2022.5.28
asyncio - asyncio.run.py
https://ryanking13.github.io/2018/07/12/python-37-whats-new.html
"""

import asyncio
import requests


async def arequest(url):
    response = requests.get(url)
    return response


urls = [
    'https://www.google.com',
    'https://www.apple.com',
    'https://www.facebook.com',
]

# python <= 3.6
# future = [arequest(url) for url in urls]
# loop = asyncio.get_event_loop()
# loop.run_until_complete(asyncio.wait(future))

# python 3.7 with asyncio.run()
future = [arequest(url) for url in urls]
print(asyncio.run(asyncio.wait(future)))

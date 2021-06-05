"""
y, python - coroutine.py, 2019.7.19
"""

def coroutine():

    hello = yield 'hello ..'
    yield hello


c = coroutine()
print(next(c))
print(c.send('world !!'))
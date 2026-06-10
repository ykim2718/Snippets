"""
y, 2020.12.7
inspect - with signature.py
"""


import inspect


def foo(bar: str, baz, span: str='eggs', *, month: str='python', **kwargs):
    pass


sig = inspect.signature(foo)
print(sig)
# (bar: str, baz, span: str = 'eggs', *, month: str = 'python', **kwargs)

for j, (key, para) in enumerate(sig.parameters.items(), start=1):
    print(j, key, type(para), para.annotation, para.annotation == inspect.Parameter.empty)
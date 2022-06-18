"""
y, 2022.6.18
typing - overload.py
https://docs.python.org/3.9/library/typing.html#typing.overload
https://peps.python.org/pep-0484/#function-method-overloading
https://stackoverflow.com/questions/52034771/overload-decorator-in-typings-module-doesnt-seem-to-behave-as-expected
"""

import typing


class Klass:

    @typing.overload
    def __init__(self, a: int) -> None:
        print(a)

    @typing.overload
    def __init__(self, a: str) -> None:
        print(a)


Klass()

"""
Traceback (most recent call last):
  File "D:\Wolf\Homo academicus\yStudy on code - Python\Python - Snippets\yPython on Modules\typing\typing - overload.py", line 21, in <module>
    Klass()
  File "C:\y\Anaconda3\lib\typing.py", line 1582, in _overload_dummy
    raise NotImplementedError(
NotImplementedError: You should not call an overloaded function. A series of @overload-decorated functions outside a stub module should always be followed by an implementation that is not @overload-ed.

Process finished with exit code 1
"""

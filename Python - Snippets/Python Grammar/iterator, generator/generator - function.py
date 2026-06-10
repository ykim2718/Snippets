"""
y, generator - function.py, 2019.1.30
https://stackoverflow.com/questions/6416538/how-to-check-if-an-object-is-a-generator-object-in-python
"""

import inspect


def generator_function():
    yield 1


print(inspect.iscoroutine(generator_function))  # False
print(inspect.isgenerator(generator_function))  # False
print(inspect.isgeneratorfunction(generator_function))  # True

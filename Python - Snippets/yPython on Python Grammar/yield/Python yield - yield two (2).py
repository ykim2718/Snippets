"""
y, Python yield - yield two.py, 2019.4.2, 4.7
https://stackoverflow.com/questions/16856251/yield-multiple-values
"""

def yield_many():

    def yield_one():

        yield 1
        yield 10

    def yield_two():

        yield 2
        yield 20

    one = yield_one()
    two = yield_two()
    return one, two


it1, it2 = yield_many()
print(it1, type(it1))
for j, k in zip(it1, it2):
    print(j, k)


import inspect

print(inspect.isgenerator(it1))          # True
print(inspect.isgeneratorfunction(it1))  # False
print(inspect.iscoroutine(it1))          # False
print(inspect.iscoroutinefunction(it1))  # False

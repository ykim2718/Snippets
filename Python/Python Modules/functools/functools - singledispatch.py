"""
y, 2022.6.18
functools - singledispatch.py
https://docs.python.org/3.9/library/typing.html#typing.overload
https://peps.python.org/pep-0484/#function-method-overloading
https://stackoverflow.com/questions/52034771/overload-decorator-in-typings-module-doesnt-seem-to-behave-as-expected
https://docs.python.org/ko/3/library/functools.html#functools.singledispatch  ★
https://docs.python.org/ko/3/library/functools.html#functools.singledispatchmethod  ★
"""

from functools import singledispatch


class Car:
    def __init__(self, color: str, brand: str) -> None:
        self.color = color
        self.brand = brand


@singledispatch
def describe_car(color: str, kind: str) -> str:
    return "Little " + color + " " + kind


@describe_car.register(Car)
def _(car: Car) -> str:
    return describe_car(car.color, car.brand)


new_car = Car("red", "corvette")

print(describe_car("green", "pinto"))
print(describe_car(new_car))

"""
y, python decorator - class as decorator.py, 2019.9.11 - 12
[1] https://www.geeksforgeeks.org/class-as-decorator-in-python/
[2] https://www.codementor.io/sheena/advanced-use-python-decorators-class-function-du107nxsv
[3] https://medium.com/@vadimpushtaev/decorator-inside-python-class-1e74d23107f6
[4] https://dev.to/apcelent/python-decorator-tutorial-with-example-529f   ★
[5] https://github.com/GrahamDumpleton/wrapt/tree/develop/blog   ★ ★
"""


class SquareDecorator:  # [1]

    def __init__(self, function):
        self.function = function

    def __call__(self, *args, **kwargs):
        result = self.function(*args, **kwargs)
        return result ** 2


@SquareDecorator
def get_square(n):
    print("Given number is:", n)
    return n


print("  Square is:", get_square(5))


class CubeDecorator:  # [4, 5]

    test = None

    def __init__(self, **kwargs):
        pass

    def __call__(self, foo, *args, **kwargs):
        def inner_func(self_, *args, **kwargs):
            result = foo(self_, *args, **kwargs)
            self.test = result
            return result ** 3
        return inner_func


class Klass:

    n = None

    def __init__(self, n):
        self.n = n

    @CubeDecorator()
    def get_cube(self):
        print("Given number is:", self.n)
        return self.n


klass = Klass(5)
print("  Cube is:", klass.get_cube())
print(CubeDecorator.test)
klass = Klass(10)
print("  Cube is:", klass.get_cube())
print(CubeDecorator.test)

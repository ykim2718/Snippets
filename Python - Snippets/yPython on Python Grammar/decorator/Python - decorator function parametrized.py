"""
y, 2016.5.19
http://stackoverflow.com/questions/5929107/python-decorators-with-parameters
three-layered wrapper
"""


def parametrized(dec):
    def layer(*args, **kwargs):
        def repl(f):
            print(id(dec), type(dec), id(f), type(f))
            return dec(f, *args, **kwargs)

        return repl

    return layer


@parametrized
def multiply(f, n):
    def aux(*xs, **kws):
        return n * f(*xs, **kws)

    return aux


@multiply(2)
def function(a):
    return 10 + a


print(function(3))  # Prints 26


@multiply(3)
def function_again(a):
    return 10 + a


print(function(3))  # Keeps printing 26
print(function_again(3))  # Prints 39, namely 3 * (10 + 3)

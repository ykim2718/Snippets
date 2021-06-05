"""
y (copyRight) 2016.4.1 - 5.7
http://stackoverflow.com/questions/13783211/python-how-to-pass-an-argument-to-a-function-pointer-parameter
http://stackoverflow.com/questions/900392/getting-the-caller-function-name-inside-another-function-in-python
"""


def repeat(function, params, times):
    for calls in range(times):
        function(*params)


def foo(a, b):
    print('{} is {}'.format(a, b))


def my_foo_1(func, params):
    func(*params)


def my_foo_2(func, *args):
    func(*args)


def my_foo_3(func, **kwargs):
    if kwargs:
        first = kwargs['first']
        second = kwargs['second']
    else:
        first = 'first'
        second = 'second'
    func(first, second)


def my_foo_4(*args):
    print(len(args), type(args))
    for index, arg in enumerate(args):
        print(index, arg)


def my_function_name():
    import inspect
    print(inspect.stack()[0][3])  # function name
    print(inspect.stack()[1][3])  # function caller name


def my_caller_function_name():
    my_function_name()


if __name__ == "__main__":
    repeat(foo, ['roses', 'red'], 1)
    repeat(foo, ['violets', 'blue'], 2)

    my_foo_1(foo, ['a', 'b'])
    my_foo_2(foo, 'blue', 'green')
    my_foo_3(foo, first='reddish', second='orangey')
    my_foo_3(foo)

    print('y, 2016.4.1', '*' * 16)
    my_function_name()

    print('y, 2016.5.7', '*' * 16)
    my_caller_function_name()

    print('y, 2016.6.4', '*' * 16)
    my_foo_4(1, 2, 3)

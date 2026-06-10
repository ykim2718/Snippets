"""
y, python try except - else finally.py, 2018.11.14; 2019.3.31
https://docs.python.org/3/tutorial/errors.html
"""

print(__doc__)


def divide(x, y):

    try:
        result = x / y
    except ZeroDivisionError:
        print("[except] division by zero!")
    else:
        print("[else] result is", result)
    finally:
        print("[finally] executing finally clause")
    return result


print('-' * 16, '\n', divide(2, 1))
print('-' * 16, '\n', divide(2, 0))
print('-' * 16, '\n', divide('2', '1'))

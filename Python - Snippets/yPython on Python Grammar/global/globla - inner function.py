"""
y, 2022.3.16
global - inner function.py
https://stackoverflow.com/questions/51662467/using-a-global-variable-inside-a-function-nested-in-a-function-in-python
"""

a = 1


def f1():
    global a  # okay
    a += 1


def f2():
    global b  # avoid NameError happening in inner function
    b = 1

    def inner():
        global b  # NameError: name 'b' is not defined
        b *= 10

    inner()
    print(b)


f1()
print(a)

f2()
print(b)  # NOTE: No error !!!

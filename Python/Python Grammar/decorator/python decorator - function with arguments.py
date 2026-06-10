"""
y, 2016.9.29 (y Birthday), python decorator - function with arguments.py

[Reference]
Python Decorators II: Decorator Arguments by Bruce Eckel, October 19, 2008
http://www.artima.com/weblogs/viewpost.jsp?thread=240845
"""

print(__doc__)


def decoratorFunctionWithArguments(*dec_args, **dec_kwargs):
    def wrap(f):
        def wrapped_f(*args, **kwargs):
            print("decorator arguments:", dec_args, dec_kwargs)
            print("function arguments:", args, kwargs)
            return f(*args, **kwargs)
        return wrapped_f
    return wrap

@decoratorFunctionWithArguments("d1", "d2", 33, kwargs=1)
# @decoratorFunctionWithArguments(kwargs=1)
# @decoratorFunctionWithArguments()
def my_func(f1, f2, f3="", f4=""):
    print("my_func arguments:", f1, f2, f3)
    return 'No pain no gain; Use your deposit time, y!'

r = my_func("f1", "f2", f4="f4", f3="f3")
print(r)


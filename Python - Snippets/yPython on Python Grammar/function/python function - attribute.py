"""
y, 2020.10.4
python function - attribute.py
"""

print(__doc__)


def my_func(a):
    my_func.a = a
    my_func.b = 999
    return my_func


# print(my_func.a, my_func.b)  # AttributeError: 'function' object has no attribute 'a'
r = my_func(1004)
print(r.a, r.b)
print(my_func.a, my_func.b)

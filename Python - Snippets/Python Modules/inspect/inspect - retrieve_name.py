"""
y, inspect - retrieve_name.py, 2017.8.26

Getting the name of a variable as a string
https://stackoverflow.com/questions/18425225/getting-the-name-of-a-variable-as-a-string

"""

import inspect


def retrieve_name(var):
    """
    Gets the name of var. Does it from the out most frame inner-wards.
    """
    for fi in reversed(inspect.stack()):
        names = [var_name for var_name, var_val in fi.frame.f_locals.items() if var_val is var]
        if len(names) > 0:
            return names[0]  # find first, y, 2017.8.27

b = 2
a = 2
print(retrieve_name(a))
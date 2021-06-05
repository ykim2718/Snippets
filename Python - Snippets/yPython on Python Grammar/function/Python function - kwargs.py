"""
y, python function - kwargs.py, 2016.5.5
"""


def my_func(func, **kwargs):
    my_args = {
        'first': 1,
        'second': 2.0
    }

    if kwargs:
        for key in my_args:

            try:
                kwargs[key]
            except KeyError:
                continue

            if isinstance(kwargs[key], type(my_args[key])) is False:
                print("%s expected but mismatched arg: %s"
                      % (type(my_args[key]), kwargs[key]))

            my_args[key] = kwargs[key]

    # main starts here

    for key, value in my_args.items():
        func(key, value)

    return 1


if __name__ == "__main__":
    import pandas as pd

    print(type(1))
    print(type(1.0))
    print(type('1.0'))
    print(type([None]))
    print(type(pd.DataFrame()))

    my_func(
        print, first='1st', second_2='2nd', third='3rd'
    )

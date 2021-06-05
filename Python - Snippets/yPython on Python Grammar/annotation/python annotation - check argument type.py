"""
y, python annotation - check argument type.py, 2019.1.3
https://blog.hannal.com/2015/03/keyword-only-arguments_and_annotations_for_python3/
"""

print(__doc__)

def check_argument_type(func):
    def wrapper(*args):
        annotations = func.__annotations__
        if (
            not isinstance(annotations, dict) or
            len(annotations) == 0
        ):
            return func(*args)

        try:
            check_index = annotations['args'].index(Ellipsis)
        except ValueError:
            check_index = len(annotations['args']) - 1

        for _i, _v in enumerate(args[:check_index]):
            _arg_type = annotations['args'][_i]

            if isinstance(_v, _arg_type):
                continue

            raise TypeError(
                "The type of '{}' does not match '{}' type".format(
                    _v, _arg_type.__name__
                )
            )
        return func(*args)
    return wrapper


@check_argument_type
def hello_func(*args: (int, int, ...)):
    print(*args)


hello_func(1, 2, '3', 'a')

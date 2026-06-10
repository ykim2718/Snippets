"""
y, python decorator - depricated.py, 2018.8.4
https://gist.github.com/kgriffs/8202106
https://stackoverflow.com/questions/20960110/how-do-i-get-warnings-warn-to-issue-a-warning-and-not-ignore-the-line
https://gist.github.com/shoveller/b4d2e1e6d33906f2a667
https://artemrudenko.wordpress.com/2013/04/15/python-why-you-need-to-use-wraps-with-decorators/
"""

import functools
import inspect
import warnings


# NOTE(kgriffs): We don't want our deprecations to be ignored by default,
# so create our own type.
class DeprecatedWarning(UserWarning):
    pass


def deprecated(instructions=None):
    """Flags a method as deprecated.
    Args:
        instructions: A human-friendly string of instructions, such
            as: 'Please migrate to add_proxy() ASAP.'
    """
    def decorator(func):
        '''This is a decorator which can be used to mark functions
        as deprecated. It will result in a warning being emitted
        when the function is used.'''
        @functools.wraps(func)
        def wrapper(*args, **kwargs):

            message = '{f}() deprecated. {i}'.format(f=func.__name__, i=instructions)

            frame = inspect.currentframe().f_back
            warnings.warn_explicit(message,
                                   category=DeprecatedWarning,
                                   filename=inspect.getfile(frame.f_code),
                                   lineno=frame.f_lineno)

            return func(*args, **kwargs)

        return wrapper

    return decorator


# @deprecated("Use another function.")
@deprecated()
def abc():
    pass


abc()
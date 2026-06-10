"""
y, decorator - log time it.py, 2017.7.20

Inspired by
-----------

. Decoration python class methods, how do I pass the instance to the decorator?
    https://stackoverflow.com/questions/2365701/decorating-python-class-methods-how-do-
        i-pass-the-instance-to-the-decorator
. Python decorator, self is mixed up
    https://stackoverflow.com/questions/5469956/python-decorator-self-is-mixed-up

"""

import datetime as dt
import logging
import functools

def yLogTimeIt(*decorator_args, **decorator_kwargs):
    """ y, 2017.7.20 """

    class _my_decorator:

        def __init__(self, func):

            self.func = func

        def __get__(self, instance, instance_type):
            """ Implement the descriptor protocol to make decorating instance method possible.
                Return a partial function with the first argument is the instance of the class decorated.
            """

            return functools.partial(self.__call__, instance)

        def __call__(self, *args, **kwargs):

            t_start = dt.datetime.now()
            self.func(*args, **kwargs)
            t_stop = dt.datetime.now()

            if 'log_function' in decorator_kwargs:
                log_function = decorator_kwargs['log_function']
                log_function('running for %s' % (t_stop - t_start))

    return _my_decorator


import time

@yLogTimeIt(log_function=logging.getLogger().critical)
def my_func(arg, **kwargs):

    time.sleep(arg)
    print('slept during %.1f secs' % arg)


import sys

log = logging.getLogger()
log.setLevel(logging.DEBUG)
ch = logging.StreamHandler(sys.stdout)
ch.setFormatter(logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s'))
log.addHandler(ch)

log.info('write here ...')
my_func(1.1, a='bc')
"""
y, 2016.7.9, Inspect - stack.py
    2016.8.15 add sys.
    2019.1.3 add current_frame, outer_frame
"""

import inspect
import sys


def foo(a, b=1):
    def bar(c, d=2):
        print("len(inspect.stack()[0])=", len(inspect.stack()[0]))
        print("inspect.stack()[0][0] = frame =", inspect.stack()[0][0])  # same as inspect.currentframe()
        print("inspect.stack()[0][1] = filename =", inspect.stack()[0][1])
        print("inspect.stack()[0][2] = line_number =", inspect.stack()[0][2])
        print("inspect.stack()[0][3] = caller =", inspect.stack()[0][3])
        print("inspect.stack()[1][3] = caller's caller =", inspect.stack()[1][3])
        print("inspect.stack()[0][4] = lines =", inspect.stack()[0][4])
        print("inspect.stack()[0][5] = index =", inspect.stack()[0][5])
        print('sys._getframe().f_code.co_name =', sys._getframe().f_code.co_name)
        current_frame = inspect.stack()[0][0]  # bar
        print(inspect.getargvalues(current_frame))
        outer_frame = inspect.stack()[1][0]  # foo
        print(inspect.getargvalues(outer_frame))
        args, varargs, keywords, _locals = inspect.getargvalues(outer_frame)
        print(args, varargs, keywords, _locals)
        arguments = {k: _locals[k] for k in args}
        print(arguments)
    bar(3)


foo(2)

"""
y, 2016.6.29, Pyqt - call periodically using qtimer.py
"""

import sys
from PyQt5 import QtWidgets, QtCore
import functools
import datetime as dt


def foo(arg, kwarg=''):
    print('foo', arg, kwarg, dt.datetime.now())


def fee():
    print('fee', time.ctime())


def call_a_function_repeatedly_using_qt5(func, start, step, stop, args=(), kwargs={}):
    call_periodically_list = []

    def func_wrapper(qtimer_id):
        # print('func_wrapper', dt.datetime.now(), len(call_periodically_list))
        if stop < dt.datetime.now():
            qtimer_id.stop()
            app.quit()
            print('qtimer_id.stop()', dt.datetime.now())
            return
        func(*args, **kwargs) if func.__code__.co_argcount else func()

    def repeat():
        # print('repeat', dt.datetime.now())
        t = QtCore.QTimer()
        timer = functools.partial(func_wrapper, qtimer_id=t)
        t.timeout.connect(timer)
        t.start(step * 1000)
        call_periodically_list.append(t)

    setup_time = start - dt.datetime.now()
    print('setup_time', setup_time.days, setup_time.seconds)
    if setup_time.days > 0:
        t = QtCore.QTimer()
        t.singleShot(setup_time.seconds * 1000, repeat)
        call_periodically_list.append(t)
    else:
        repeat()
    return call_periodically_list


def cancel_periodic_call_list(call_periodically_list):
    for t in call_periodically_list:
        t.stop()


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    now = dt.datetime.now()
    print('main', now)
    opening_today = now + dt.timedelta(seconds=0)
    closing_today = opening_today + dt.timedelta(seconds=3)
    call_list = call_a_function_repeatedly_using_qt5(
        foo, opening_today, 1, closing_today, args=('hello',), kwargs={'kwarg': 'qtimer'})
    app.exec_()
    print('done')

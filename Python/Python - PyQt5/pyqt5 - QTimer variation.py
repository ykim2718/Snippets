"""
y, 2016.6.28, Pyqt - QTimer variation.py
"""

import sys
from PyQt5 import QtWidgets
from PyQt5 import QtCore
import time
import inspect
import functools


def tick1():
    print(inspect.stack()[0][3], time.ctime())


g_count = 0


def tick2(message):
    global g_count
    g_count += 1
    print(inspect.stack()[0][3], time.ctime(), g_count, message)
    if g_count > 3:
        app.quit()


def tick3(message):
    print(inspect.stack()[0][3], time.ctime(), message)


app = QtWidgets.QApplication(sys.argv)

# QTimer 1
QtCore.QTimer.singleShot(2500, tick1)

# QTimer 2
timerCallback = functools.partial(tick2, message='my message')
t = QtCore.QTimer()
t.timeout.connect(timerCallback)
t.start(1000)


# QTimer 3
class SignalEmit(QtCore.QObject):
    signal = QtCore.pyqtSignal(str, )

    def emit(self):
        self.signal.emit(inspect.stack()[0][3])


se = SignalEmit()
se.signal.connect(tick3)
u = QtCore.QTimer()
u.timeout.connect(se.emit)
u.start(1000)

app.exec_()
print('after app.exec_()')

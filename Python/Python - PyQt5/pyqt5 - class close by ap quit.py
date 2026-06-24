"""
y, Pyqt - class close by ap quit.py, 2016.6.24
"""

from PyQt5 import QtWidgets, QtCore
import sys
import time


class AClass:
    def __del__(self):
        print('Aclass deleted ..', time.ctime())


def my_quit():
    global a
    del a
    print('my_quit()', time.ctime())
    app.quit()


a = AClass()
app = QtWidgets.QApplication(sys.argv)

# QtCore.QTimer.singleshot(1*1000, app.quit)
QtCore.QTimer.singleShot(1 * 1000, my_quit)
print('QTimer.singleShot()', time.ctime())
print('Before app.exec_()', time.ctime())
app.exec_()
print('After app.exec_()', time.ctime())

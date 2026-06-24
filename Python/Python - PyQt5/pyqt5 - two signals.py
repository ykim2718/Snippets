"""
y, Pyqt - two signals.py, 2016.6.28
Signals and Slots in PySide/ko
https://wiki.qt.io/Signals_and_Slots_in_PySide/ko
"""

import sys
from PyQt5 import QtCore


# define a new slot that receives an C 'int' or a 'str'
# and has 'saySomething' as its name
@QtCore.pyqtSlot(int)
@QtCore.pyqtSlot(str)
def saySomething(stuff):
    print(stuff)


class Communicate(QtCore.QObject):
    # create two new signals on the fly: one will handle
    # int type, the other will handle strings
    speak = QtCore.pyqtSignal((int,), (str,))


someone = Communicate()
# connect signal and slot. As 'int' is the default
# we have to specify the str when connecting the
# second signal
someone.speak.connect(saySomething)
someone.speak[str].connect(saySomething)

# emit 'speak' signal with different arguments.
# we have to specify the str as int is the default
someone.speak.emit(10)
someone.speak[str].emit("Hello everybody!")

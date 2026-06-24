"""
y, Pyqt - user signal carrying data.py, 2016.6.14

PySide/PyQt Tutorial: Creating Your Own Signals and Slots
http://pythoncentral.io/pysidepyqt-tutorial-creating-your-own-signals-and-slots/
+
Y
"""

from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot


class PunchingBag(QObject):
    ''' Represents a punching bag; when you punch it, it
        emits a signal that indicates that it was punched. '''
    punched = pyqtSignal('PyQt_PyObject', str)
    count = 0

    def __init__(self):
        # Initialize the PunchingBag as a QObject
        QObject.__init__(self)

    def punch(self):
        ''' Punch the bag '''
        self.punched.emit(self, 'in' + self.__class__.__name__)


@pyqtSlot()
def say_punched(cls, comment):
    ''' Give evidence that a bag was punched. '''
    cls.count += 1
    print('Bag was punched %d times' % cls.count, comment)


bag = PunchingBag()
# Connect the bag's punched signal to the say_punched slot
bag.punched.connect(say_punched)

# Punch the bag 10 times
for i in range(3):
    print(bag.count)
    bag.punch()

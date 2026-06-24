"""
y, Pyqt - hellow world.py, 2016.6.14
"""

import sys
from PyQt5 import QtWidgets


# define a function that will be used as a slot
def say_hello():
    print('Hello world!')


app = QtWidgets.QApplication(sys.argv)

button = QtWidgets.QPushButton('Say hello!')

# connect the clicked signal to the say_hello slot
button.clicked.connect(say_hello)
button.show()

sys.exit(app.exec_())

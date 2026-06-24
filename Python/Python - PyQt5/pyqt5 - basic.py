"""
y, 2021.6.6
pyqt5 - basic.py
"""

import sys
from PyQt5.QtWidgets import QApplication, QLabel


app = QApplication(sys.argv)
label = QLabel('Hello, PyQt ..')
label.show()


print('before event loop')
app.exec_()
print('after event loop')